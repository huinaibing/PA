#include "AliRootFOCALHClusterManager.h"
#include "BaseDrawGraph.h"

void phi_kk_reconstruct_footbook()
{
    // AliRootFOCALHClusterManager *manager = new AliRootFOCALHClusterManager(
    //     "/home/huinaibing/git_repo/PA/DATA_FILES/focal/reconstruct_mass_from_clusters/FOCAL_ClusterCenters.root",
    //     KCHAGED_MASS);

    // BaseDrawGraph::drawFromManager(manager, 1000, 0, 5000, [&manager]()
    //                                { return manager->getReconstructMass() * 1000; },
    //                                 [](TH1D *) {}, [](TCanvas *) {}, "Phi Reconstruct Mass", 1, "reconstructMass");
    
    // AliRootFOCALHClusterManager *manager_fake = new AliRootFOCALHClusterManager(
    //     "/home/huinaibing/git_repo/PA/DATA_FILES/focal/reconstruct_mass_from_clusters/FOCAL_ClusterCenters.root",
    //     0.13957);

    // BaseDrawGraph::drawFromManager(manager_fake, 1000, 0, 5000, [&manager_fake]()
    //                                { return manager_fake->getReconstructMass() * 1000; },
    //                                 [](TH1D *) {}, [](TCanvas *) {}, "Reconstruct Mass assuming particle are pi", 1, "reconstructMass");


    AliRootFOCALHClusterManager *manager_pi = new AliRootFOCALHClusterManager(
        "/home/huinaibing/git_repo/PA/DATA_FILES/focal/reconstruct_mass_from_clusters/FOCAL_ClusterCenters_rho0topi.root",
        0.13957);

    BaseDrawGraph::drawFromManager(manager_pi, 1000, 0, 5000, [&manager_pi]()
                                   { return manager_pi->getReconstructMass() * 1000; },
                                    [](TH1D *) {}, [](TCanvas *) {}, "rho0 Reconstruct Mass", 1, "reconstructMass");
    
    AliRootFOCALHClusterManager *manager_fake_pi = new AliRootFOCALHClusterManager(
        "/home/huinaibing/git_repo/PA/DATA_FILES/focal/reconstruct_mass_from_clusters/FOCAL_ClusterCenters_rho0topi.root",
        KCHAGED_MASS);

    BaseDrawGraph::drawFromManager(manager_fake_pi, 1000, 0, 5000, [&manager_fake_pi]()
                                   { return manager_fake_pi->getReconstructMass() * 1000; },
                                    [](TH1D *) {}, [](TCanvas *) {}, "Reconstruct Mass from rho0 assuming particle are kaon", 1, "reconstructMass");
}