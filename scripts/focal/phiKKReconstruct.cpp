#include "AliRootFOCALHClusterManager.h"
#include "BaseDrawGraph.h"
#include "TFile.h"

void phi_kk_reconstruct_footbook()
{
    AliRootFOCALHClusterManager *manager = new AliRootFOCALHClusterManager(
        "/home/huinaibing/git_repo/PA/DATA_FILES/focal/reconstruct_mass_from_clusters/FOCAL_ClusterCenters.root",
        KCHAGED_MASS);

    BaseDrawGraph::drawFromManager(manager, 1000, 0, 5000, [&manager]()
                                   { return manager->getReconstructMass() * 1000; }, [](TH1D *) {}, [](TCanvas *) {}, "Phi Reconstruct Mass", 1, "reconstructMass");

    AliRootFOCALHClusterManager *manager_fake = new AliRootFOCALHClusterManager(
        "/home/huinaibing/git_repo/PA/DATA_FILES/focal/reconstruct_mass_from_clusters/FOCAL_ClusterCenters.root",
        0.13957);

    BaseDrawGraph::drawFromManager(manager_fake, 1000, 0, 5000, [&manager_fake]()
                                   { return manager_fake->getReconstructMass() * 1000; }, [](TH1D *) {}, [](TCanvas *) {}, "Reconstruct Mass assuming particle are pi", 1, "reconstructMass");

    TFile *file = TFile::Open("cluster_energy_check.root", "RECREATE");
    TH1D *h_energy_kaon = new TH1D("h_energy_kaon", "Cluster Energy Distribution;Energy (GeV);Counts", 240, 0, 60);
    for (int i = 0; i < manager->getTotalEntries(); i++)
    {
        manager->setCurrentEntry(i);
        double e1_kaon = manager->getEnergy1();
        double e2_kaon = manager->getEnergy2();
        h_energy_kaon->Fill(e1_kaon);
        h_energy_kaon->Fill(e2_kaon);
        // printf("Entry %d: E1 kaon: %f, E2 kaon: %f, E1 pi: %f, E2 pi: %f\n", i, e1_kaon, e2_kaon, e1_pi, e2_pi);
    }
    h_energy_kaon->Write();
    file->Close();

    // AliRootFOCALHClusterManager *manager_pi = new AliRootFOCALHClusterManager(
    //     "/home/huinaibing/git_repo/PA/DATA_FILES/focal/reconstruct_mass_from_clusters/FOCAL_ClusterCenters_rho0topi.root",
    //     0.13957);

    // BaseDrawGraph::drawFromManager(manager_pi, 1000, 0, 5000, [&manager_pi]()
    //                                { return manager_pi->getReconstructMass() * 1000; },
    //                                 [](TH1D *) {}, [](TCanvas *) {}, "rho0 Reconstruct Mass", 1, "reconstructMass");

    // AliRootFOCALHClusterManager *manager_fake_pi = new AliRootFOCALHClusterManager(
    //     "/home/huinaibing/git_repo/PA/DATA_FILES/focal/reconstruct_mass_from_clusters/FOCAL_ClusterCenters_rho0topi.root",
    //     KCHAGED_MASS);

    // BaseDrawGraph::drawFromManager(manager_fake_pi, 1000, 0, 5000, [&manager_fake_pi]()
    //                                { return manager_fake_pi->getReconstructMass() * 1000; },
    //                                 [](TH1D *) {}, [](TCanvas *) {}, "Reconstruct Mass from rho0 assuming particle are kaon", 1, "reconstructMass");
}