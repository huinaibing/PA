#include "AliRootHitsFITManager.h"
#include "Utils.h"
#include "TH3F.h"
#include <iostream>

using namespace xqy;
using namespace std;

AliRootHitsFITManager::AliRootHitsFITManager(const char *file_name, const char *folder_name, int kMaxFIT)
{
    this->kMaxFIT = kMaxFIT;

    FIT_fUniqueID = new UInt_t[kMaxFIT];
    FIT_fBits = new UInt_t[kMaxFIT];
    FIT_fTrack = new Int_t[kMaxFIT];
    FIT_fX = new Float_t[kMaxFIT];
    FIT_fY = new Float_t[kMaxFIT];
    FIT_fZ = new Float_t[kMaxFIT];
    FIT_fVolume = new Int_t[kMaxFIT];
    FIT_fPmt = new Int_t[kMaxFIT];
    FIT_fMCP = new Int_t[kMaxFIT];
    FIT_fParticle = new Int_t[kMaxFIT];
    FIT_fEtot = new Double_t[kMaxFIT];
    FIT_fTime = new Float_t[kMaxFIT];
    FIT_fCharge = new Float_t[kMaxFIT];
    FIT_fPx = new Float_t[kMaxFIT];
    FIT_fPy = new Float_t[kMaxFIT];
    FIT_fPz = new Float_t[kMaxFIT];
    FIT_fEloss = new Float_t[kMaxFIT];
    FIT_fTlength = new Float_t[kMaxFIT];
    FIT_fNphot = new Int_t[kMaxFIT];

    TFile *f = TFile::Open(file_name);
    TDirectory *dir = (TDirectory *)f->Get(Utils::concatenate_const_char(*new vector<const char *>{file_name, ":/", folder_name}));
    dir->GetObject("TreeH", fChain);
    fCurrent = -1;

    this->fChain->SetMakeClass(1);
    this->total_entries = this->fChain->GetEntriesFast();

    fChain->SetBranchAddress("FIT", &FIT_, &b_FIT_);
    fChain->SetBranchAddress("FIT.fUniqueID", FIT_fUniqueID, &b_FIT_fUniqueID);
    fChain->SetBranchAddress("FIT.fBits", FIT_fBits, &b_FIT_fBits);
    fChain->SetBranchAddress("FIT.fTrack", FIT_fTrack, &b_FIT_fTrack);
    fChain->SetBranchAddress("FIT.fX", FIT_fX, &b_FIT_fX);
    fChain->SetBranchAddress("FIT.fY", FIT_fY, &b_FIT_fY);
    fChain->SetBranchAddress("FIT.fZ", FIT_fZ, &b_FIT_fZ);
    fChain->SetBranchAddress("FIT.fVolume", FIT_fVolume, &b_FIT_fVolume);
    fChain->SetBranchAddress("FIT.fPmt", FIT_fPmt, &b_FIT_fPmt);
    fChain->SetBranchAddress("FIT.fMCP", FIT_fMCP, &b_FIT_fMCP);
    fChain->SetBranchAddress("FIT.fParticle", FIT_fParticle, &b_FIT_fParticle);
    fChain->SetBranchAddress("FIT.fEtot", FIT_fEtot, &b_FIT_fEtot);
    fChain->SetBranchAddress("FIT.fTime", FIT_fTime, &b_FIT_fTime);
    fChain->SetBranchAddress("FIT.fCharge", FIT_fCharge, &b_FIT_fCharge);
    fChain->SetBranchAddress("FIT.fPx", FIT_fPx, &b_FIT_fPx);
    fChain->SetBranchAddress("FIT.fPy", FIT_fPy, &b_FIT_fPy);
    fChain->SetBranchAddress("FIT.fPz", FIT_fPz, &b_FIT_fPz);
    fChain->SetBranchAddress("FIT.fEloss", FIT_fEloss, &b_FIT_fEloss);
    fChain->SetBranchAddress("FIT.fTlength", FIT_fTlength, &b_FIT_fTlength);
    fChain->SetBranchAddress("FIT.fNphot", FIT_fNphot, &b_FIT_fNphot);
}


void AliRootHitsFITManager::classCheck()
{
    cout << "classCheck for AliRootHitsFITManager" << endl;
    TH3F *hist_3d = new TH3F("hist_3d", "3D Hit Position", 100, -50, 50, 100, -50, 50, 1000, 300, 400);

    for (int i = 0; i < this->total_entries; i++)
    {
        this->setCurrentEntry(i);
        for (Int_t j = 0; j < this->FIT_; j++)
        {
            hist_3d->Fill(this->FIT_fX[j],
                          this->FIT_fY[j],
                          this->FIT_fZ[j]);

            #ifdef DEBUG
            cout << FIT_ << endl;
            cout << "Entry: " << i << ", j: " << j << ", FIT_fX: " << this->FIT_fX[j]
                 << ", FIT_fY: " << this->FIT_fY[j]
                 << ", FIT_fZ: " << this->FIT_fZ[j] << endl;
            #endif 
        }
    }
    TFile *fout = new TFile("AliRootHitsFITManager_classCheck.root", "RECREATE");
    TCanvas *c1 = new TCanvas("c1", "c1", 1800, 1600);
    hist_3d->Draw("BOX2");
    c1->Write();
    fout->Close();
}