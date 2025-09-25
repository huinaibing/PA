#include "HitsFOCManager.h"
#include <iostream>
#include "BaseDrawGraph.h"
#include "TH1F.h"

using namespace std;


void HitsFOCManager::classCheck()
{
    cout << "total_entries: " << this->total_entries << endl;
    cout << "kMaxFOCHit: " << kMaxFOCHit << endl;

    TH1F * track_id_hist = new TH1F("track_id_hist", "track_id_hist", 100, 0, 180);
    for (Long64_t i = 0; i < this->total_entries; i++)
    {
        this->setCurrentEntry(i);
        for (Int_t j = 0; j < FOCHit_; j++)
        {
            track_id_hist->Fill(FOCHit_mTrackID[j]);
        }
    }

    TFile * output_file = new TFile("output_focal_classcheck.root", "RECREATE");
    output_file->cd();
    track_id_hist->Write();
    output_file->Close();
}
