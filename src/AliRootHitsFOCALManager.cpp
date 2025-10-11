#include "AliRootHitsFOCALManager.h"
#include "TFile.h"
#include "TDirectory.h"
#include "Utils.h"
#include <vector>
#include <iostream>
#include "TH3F.h"

using namespace xqy;
using namespace std;

AliRootHitsFOCALManager::AliRootHitsFOCALManager(const char *file_name, const char *folder_name, int kMaxFOCAL)
{
    this->kMaxFOCAL = kMaxFOCAL;
    this->folder_name = folder_name;

    FOCAL_fUniqueID = new UInt_t[kMaxFOCAL];
    FOCAL_fBits = new UInt_t[kMaxFOCAL];
    FOCAL_fTrack = new Int_t[kMaxFOCAL];
    FOCAL_fX = new Float_t[kMaxFOCAL];
    FOCAL_fY = new Float_t[kMaxFOCAL];
    FOCAL_fZ = new Float_t[kMaxFOCAL];
    FOCAL_fIndex = new ULong64_t[kMaxFOCAL];
    FOCAL_fVolume = new Int_t *[kMaxFOCAL];
    for (int i = 0; i < kMaxFOCAL; i++)
    {
        FOCAL_fVolume[i] = new Int_t[4];
    }
    FOCAL_fEnergy = new Float_t[kMaxFOCAL];
    FOCAL_fTime = new Float_t[kMaxFOCAL];

    TFile *f = TFile::Open(file_name);
    TDirectory *dir = (TDirectory *)f->Get(Utils::concatenate_const_char(*new vector<const char *>{file_name, ":/", folder_name}));
    dir->GetObject("TreeH", fChain);
    fCurrent = -1;

    this->fChain->SetMakeClass(1);
    this->total_entries = this->fChain->GetEntriesFast();

    fChain->SetBranchAddress("FOCAL", &FOCAL_, &b_FOCAL_);
    fChain->SetBranchAddress("FOCAL.fUniqueID", FOCAL_fUniqueID, &b_FOCAL_fUniqueID);
    fChain->SetBranchAddress("FOCAL.fBits", FOCAL_fBits, &b_FOCAL_fBits);
    fChain->SetBranchAddress("FOCAL.fTrack", FOCAL_fTrack, &b_FOCAL_fTrack);
    fChain->SetBranchAddress("FOCAL.fX", FOCAL_fX, &b_FOCAL_fX);
    fChain->SetBranchAddress("FOCAL.fY", FOCAL_fY, &b_FOCAL_fY);
    fChain->SetBranchAddress("FOCAL.fZ", FOCAL_fZ, &b_FOCAL_fZ);
    fChain->SetBranchAddress("FOCAL.fIndex", FOCAL_fIndex, &b_FOCAL_fIndex);
    fChain->SetBranchAddress("FOCAL.fVolume[4]", FOCAL_fVolume, &b_FOCAL_fVolume);
    fChain->SetBranchAddress("FOCAL.fEnergy", FOCAL_fEnergy, &b_FOCAL_fEnergy);
    fChain->SetBranchAddress("FOCAL.fTime", FOCAL_fTime, &b_FOCAL_fTime);
}

void AliRootHitsFOCALManager::classCheck()
{
    cout << "Checking class AliRootHitsFOCALManager ..." << endl;
    TH3F *h3 = new TH3F("h3", "h3", 300, -50, 50, 300, -50, 50, 100, 600, 800);

    for (int i = 0; i < this->total_entries; i++)
    {
        this->setCurrentEntry(i);
        for (int j = 0; j < FOCAL_; j++)
        {
            h3->Fill(FOCAL_fX[j], FOCAL_fY[j], FOCAL_fZ[j]);
        }
    }

    TFile *fout = TFile::Open(
        Utils::concatenate_const_char(
            "classcheck4FOCAL/",
            Utils::concatenate_const_char(
                this->folder_name, 
                "_AliRootHitsFOCALManager_classCheck.root"
            )
        ),
        "RECREATE"
    );
    TCanvas *c1 = new TCanvas("c1", "c1", 1800, 1600);
    h3->Draw("BOX2");
    c1->Write();
    fout->Close();
    delete c1;
    delete h3;
}

AliRootHitsFOCALManager::~AliRootHitsFOCALManager()
{

    // // 释放一维动态数组
    // delete[] FOCAL_fUniqueID;
    // delete[] FOCAL_fBits;
    // delete[] FOCAL_fTrack;
    // delete[] FOCAL_fX;
    // delete[] FOCAL_fY;
    // delete[] FOCAL_fZ;
    // delete[] FOCAL_fIndex;
    // delete[] FOCAL_fEnergy;
    // delete[] FOCAL_fTime;

    // // 释放二维动态数组FOCAL_fVolume（先释放内层，再释放外层）
    // if (FOCAL_fVolume != nullptr)
    // { // 避免空指针访问
    //     for (int i = 0; i < kMaxFOCAL; ++i)
    //     {
    //         delete[] FOCAL_fVolume[i]; // 释放每个内层数组
    //     }
    //     delete[] FOCAL_fVolume; // 释放外层数组
    // }
}
