#ifndef ALIROOTHITSFITMANAGER_H
#define ALIROOTHITSFITMANAGER_H

#include "BaseManager.h"
#include "TFile.h"
#include "TTree.h"
#include "TBranch.h"

class AliRootHitsFITManager : public BaseManager
{
protected:
    TTree *fChain;  //! pointer to the analyzed TTree or TChain
    Int_t fCurrent; //! current Tree number in a TChain
    // List of branches
    TBranch *b_FIT_;          //!
    TBranch *b_FIT_fUniqueID; //!
    TBranch *b_FIT_fBits;     //!
    TBranch *b_FIT_fTrack;    //!
    TBranch *b_FIT_fX;        //!
    TBranch *b_FIT_fY;        //!
    TBranch *b_FIT_fZ;        //!
    TBranch *b_FIT_fVolume;   //!
    TBranch *b_FIT_fPmt;      //!
    TBranch *b_FIT_fMCP;      //!
    TBranch *b_FIT_fParticle; //!
    TBranch *b_FIT_fEtot;     //!
    TBranch *b_FIT_fTime;     //!
    TBranch *b_FIT_fCharge;   //!
    TBranch *b_FIT_fPx;       //!
    TBranch *b_FIT_fPy;       //!
    TBranch *b_FIT_fPz;       //!
    TBranch *b_FIT_fEloss;    //!
    TBranch *b_FIT_fTlength;  //!
    TBranch *b_FIT_fNphot;    //!

    Long64_t total_entries;

public:
    Int_t kMaxFIT;

    Int_t FIT_;
    UInt_t *FIT_fUniqueID; //[FIT_]
    UInt_t *FIT_fBits;     //[FIT_]
    Int_t *FIT_fTrack;     //[FIT_]
    Float_t *FIT_fX;       //[FIT_]
    Float_t *FIT_fY;       //[FIT_]
    Float_t *FIT_fZ;       //[FIT_]
    Int_t *FIT_fVolume;    //[FIT_]
    Int_t *FIT_fPmt;       //[FIT_]
    Int_t *FIT_fMCP;       //[FIT_]
    Int_t *FIT_fParticle;  //[FIT_]
    Double_t *FIT_fEtot;   //[FIT_]
    Float_t *FIT_fTime;    //[FIT_]
    Float_t *FIT_fCharge;  //[FIT_]
    Float_t *FIT_fPx;      //[FIT_]
    Float_t *FIT_fPy;      //[FIT_]
    Float_t *FIT_fPz;      //[FIT_]
    Float_t *FIT_fEloss;   //[FIT_]
    Float_t *FIT_fTlength; //[FIT_]
    Int_t *FIT_fNphot;     //[FIT_]

    AliRootHitsFITManager(const char *file_name, const char *folder_name, int kMaxFIT);

    std::string getParticalName() override
    {
        return "AliRootHitsFIT";
    }

    Long64_t getTotalEntries() override
    {
        return this->total_entries;
    }

    void setCurrentEntry(Long64_t entry) override
    {
        this->fChain->GetEntry(entry);
    }

    void classCheck();
};

#endif