#ifndef HITSFOCMANAGER_H
#define HITSFOCMANAGER_H

#include "BaseManager.h"
#include "TFile.h"
#include "TTree.h"
#include "TBranch.h"
#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include "Math/GenVector/Cartesian3D.h"

class HitsFOCManager : public BaseManager
{
protected:
    TTree *fChain;  //! pointer to the analyzed TTree or TChain
    Int_t fCurrent; //! current Tree number in a TChain

    // List of branches
    TBranch *b_FOCHit_;                     //!
    TBranch *b_FOCHit_mTrackID;             //!
    TBranch *b_FOCHit_mPos_fCoordinates_fX; //!
    TBranch *b_FOCHit_mPos_fCoordinates_fY; //!
    TBranch *b_FOCHit_mPos_fCoordinates_fZ; //!
    TBranch *b_FOCHit_mTime;                //!
    TBranch *b_FOCHit_mHitValue;            //!
    TBranch *b_FOCHit_mDetectorID;          //!
    TBranch *b_FOCHit_mSubSystem;           //!
    TBranch *b_FOCHit_mPrimary;             //!
    TBranch *b_FOCHit_mInitialEnergy;       //!

    Long64_t total_entries;

public:
    Int_t kMaxFOCHit;

    Int_t FOCHit_;
    Int_t *FOCHit_mTrackID;
    Float_t *FOCHit_mPos_fCoordinates_fX;
    Float_t *FOCHit_mPos_fCoordinates_fY;
    Float_t *FOCHit_mPos_fCoordinates_fZ;
    Float_t *FOCHit_mTime;
    Float_t *FOCHit_mHitValue;
    Short_t *FOCHit_mDetectorID;
    Int_t *FOCHit_mSubSystem;
    Int_t *FOCHit_mPrimary;
    Double_t *FOCHit_mInitialEnergy;
    
    std::string getParticalName() override
    {
        return "HitsFOC";
    }

    Long64_t getTotalEntries() override
    {
        return this->total_entries;
    }

    void setCurrentEntry(Long64_t entry) override
    {
        this->fChain->GetEntry(entry);
    }

    HitsFOCManager(const char *file_name, int kMaxFOCHit)
    {
        this->kMaxFOCHit = kMaxFOCHit;

        FOCHit_mTrackID = new Int_t[kMaxFOCHit];
        FOCHit_mPos_fCoordinates_fX = new Float_t[kMaxFOCHit];
        FOCHit_mPos_fCoordinates_fY = new Float_t[kMaxFOCHit];
        FOCHit_mPos_fCoordinates_fZ = new Float_t[kMaxFOCHit];
        FOCHit_mTime = new Float_t[kMaxFOCHit];
        FOCHit_mHitValue = new Float_t[kMaxFOCHit];
        FOCHit_mDetectorID = new Short_t[kMaxFOCHit];
        FOCHit_mSubSystem = new Int_t[kMaxFOCHit];
        FOCHit_mPrimary = new Int_t[kMaxFOCHit];
        FOCHit_mInitialEnergy = new Double_t[kMaxFOCHit];

        TTree *tree;
        TFile *f = new TFile(file_name);
        f->GetObject("o2sim", tree);
        fChain = tree;
        fCurrent = -1;
        fChain->SetMakeClass(1);

        fChain->SetBranchAddress("FOCHit", &FOCHit_, &b_FOCHit_);
        fChain->SetBranchAddress("FOCHit.mTrackID", FOCHit_mTrackID, &b_FOCHit_mTrackID);
        fChain->SetBranchAddress("FOCHit.mPos.fCoordinates.fX", FOCHit_mPos_fCoordinates_fX, &b_FOCHit_mPos_fCoordinates_fX);
        fChain->SetBranchAddress("FOCHit.mPos.fCoordinates.fY", FOCHit_mPos_fCoordinates_fY, &b_FOCHit_mPos_fCoordinates_fY);
        fChain->SetBranchAddress("FOCHit.mPos.fCoordinates.fZ", FOCHit_mPos_fCoordinates_fZ, &b_FOCHit_mPos_fCoordinates_fZ);
        fChain->SetBranchAddress("FOCHit.mTime", FOCHit_mTime, &b_FOCHit_mTime);
        fChain->SetBranchAddress("FOCHit.mHitValue", FOCHit_mHitValue, &b_FOCHit_mHitValue);
        fChain->SetBranchAddress("FOCHit.mDetectorID", FOCHit_mDetectorID, &b_FOCHit_mDetectorID);
        fChain->SetBranchAddress("FOCHit.mSubSystem", FOCHit_mSubSystem, &b_FOCHit_mSubSystem);
        fChain->SetBranchAddress("FOCHit.mPrimary", FOCHit_mPrimary, &b_FOCHit_mPrimary);
        fChain->SetBranchAddress("FOCHit.mInitialEnergy", FOCHit_mInitialEnergy, &b_FOCHit_mInitialEnergy);
        this->total_entries = this->fChain->GetEntriesFast();
    }

    void classCheck();
};

#endif
