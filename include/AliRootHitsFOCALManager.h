#ifndef ALIROOTHITSFOCALMANAGER_H
#define ALIROOTHITSFOCALMANAGER_H

#include "BaseManager.h"
#include "TTree.h"

class AliRootHitsFOCALManager : public BaseManager
{
protected:
    const char *folder_name;

    TTree *fChain;  //! pointer to the analyzed TTree or TChain
    Int_t fCurrent; //! current Tree number in a TChain

    // List of branches
    TBranch *b_FOCAL_;          //!
    TBranch *b_FOCAL_fUniqueID; //!
    TBranch *b_FOCAL_fBits;     //!
    TBranch *b_FOCAL_fTrack;    //!
    TBranch *b_FOCAL_fX;        //!
    TBranch *b_FOCAL_fY;        //!
    TBranch *b_FOCAL_fZ;        //!
    TBranch *b_FOCAL_fIndex;    //!
    TBranch *b_FOCAL_fVolume;   //!
    TBranch *b_FOCAL_fEnergy;   //!
    TBranch *b_FOCAL_fTime;     //!

    Long64_t total_entries;

public:
    Int_t kMaxFOCAL;

    // Declaration of leaf types
    Int_t FOCAL_;
    UInt_t *FOCAL_fUniqueID; //[FOCAL_]
    UInt_t *FOCAL_fBits;     //[FOCAL_]
    Int_t *FOCAL_fTrack;     //[FOCAL_]
    Float_t *FOCAL_fX;       //[FOCAL_]
    Float_t *FOCAL_fY;       //[FOCAL_]
    Float_t *FOCAL_fZ;       //[FOCAL_]
    ULong64_t *FOCAL_fIndex; //[FOCAL_]
    Int_t **FOCAL_fVolume;   //[FOCAL_]
    Float_t *FOCAL_fEnergy;  //[FOCAL_]
    Float_t *FOCAL_fTime;    //[FOCAL_]

    AliRootHitsFOCALManager(const char *file_name, const char *folder_name, int kMaxFOCAL);
    ~AliRootHitsFOCALManager() override;
    std::string getParticalName() override { return "FOCAL"; };
    Long64_t getTotalEntries() override { return this->total_entries; };
    void setCurrentEntry(Long64_t entry) override { fChain->GetEntry(entry); };

    void classCheck();
    double getSumOfHitsEnergy();
};

#endif