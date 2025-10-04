#include "TH3F.h"
#include "HitsFOCManager.h"
#include "TCanvas.h"
#include "TFile.h"
#include "TStyle.h"

class TestData
{
private:
    const char *file_path = "/home/huinaibing/git_repo/PA/DATA_FILES/focal/phi_kk/o2sim_HitsFOC.root";

public:
    TH3F *draw_hist_3d(Long64_t entry)
    {
        HitsFOCManager manager(file_path, 902);
        manager.setCurrentEntry(entry);

        TH3F *hist_3d = new TH3F("hist_3d", "3D Hit Position", 100, -50, 50, 100, -50, 50, 1600, 690, 850);
        Int_t idx_test = entry;
        while (manager.FOCHit_ == 0)
        {
            idx_test++;
            manager.setCurrentEntry(idx_test);
        }

        for (Int_t j = 0; j < manager.FOCHit_; j++)
        {
            hist_3d->Fill(manager.FOCHit_mPos_fCoordinates_fX[j],
                          manager.FOCHit_mPos_fCoordinates_fY[j],
                          manager.FOCHit_mPos_fCoordinates_fZ[j]);
        }

        return hist_3d;
    }

    void run()
    {
        gStyle->SetOptStat(0);
        TH3F *hist_3d = draw_hist_3d(1145);
        TFile* output_file = new TFile("/home/huinaibing/git_repo/PA/build/test_focal_data/output_focal_3d_hist.root", "RECREATE");
        TCanvas* c1 = new TCanvas("c1", "3D Hit Position", 800, 600);
        hist_3d->Draw("BOX2");
        c1->Write();
        output_file->Close();
    }
};