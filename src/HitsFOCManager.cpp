#include "HitsFOCManager.h"
#include <iostream>
#include "BaseDrawGraph.h"
#include "TH1F.h"
#include <fstream>
using namespace std;


void HitsFOCManager::classCheck()
{
    cout << "total_entries: " << this->total_entries << endl;
    cout << "kMaxFOCHit: " << kMaxFOCHit << endl;

    TH1F * track_id_hist = new TH1F("track_id_hist", "track_id_hist", 100, 0, 1800);
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

    this->setCurrentEntry(0);
    Int_t idx_test = 0;
    while (this->FOCHit_ == 0)
    {
        idx_test++;
        this->setCurrentEntry(idx_test);
    }

    ofstream fout("output_focal_classcheck.txt");
    for (Int_t j = 0; j < FOCHit_; j++)
    {
        fout << "FOCHit_mTrackID: " << FOCHit_mTrackID[j] << ", ";
        fout << "FOCHit_mPos_fCoordinates_fX: " << FOCHit_mPos_fCoordinates_fX[j] << ", ";
        fout << "FOCHit_mPos_fCoordinates_fY: " << FOCHit_mPos_fCoordinates_fY[j] << ", ";
        fout << "FOCHit_mPos_fCoordinates_fZ: " << FOCHit_mPos_fCoordinates_fZ[j] << ", ";
        fout << "FOCHit_mTime: " << FOCHit_mTime[j] << ", ";
        fout << "FOCHit_mHitValue: " << FOCHit_mHitValue[j] << ", ";
        fout << "FOCHit_mDetectorID: " << FOCHit_mDetectorID[j] << ", ";
        fout << "FOCHit_mSubSystem: " << FOCHit_mSubSystem[j] << ", ";
        fout << "FOCHit_mPrimary: " << FOCHit_mPrimary[j] << ", ";
        fout << "FOCHit_mInitialEnergy: " << FOCHit_mInitialEnergy[j] << endl;
        fout << "----------------------------------------" << endl;
    }
}
