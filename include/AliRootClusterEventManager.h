#ifndef ALIROOTCLUSTEREVENTMANAGER_H
#define ALIROOTCLUSTEREVENTMANAGER_H

#include "BaseManager.h"
#include "TTree.h"
#include "TVector3.h"
#include <iostream>
using namespace std;

class AliRootClusterEventManager : public BaseManager
{
protected:
    const char *folder_name;
    Long64_t total_entries;
    TTree *fChain; //! pointer to the analyzed TTree or TChain

    TBranch *b_AliFOCALClusterItr_;                //!
    TBranch *b_AliFOCALClusterItr_fUniqueID;       //!
    TBranch *b_AliFOCALClusterItr_fBits;           //!
    TBranch *b_AliFOCALClusterItr_fTracks;         //!
    TBranch *b_AliFOCALClusterItr_fX;              //!
    TBranch *b_AliFOCALClusterItr_fY;              //!
    TBranch *b_AliFOCALClusterItr_fZ;              //!
    TBranch *b_AliFOCALClusterItr_fSigmaY2;        //!
    TBranch *b_AliFOCALClusterItr_fSigmaZ2;        //!
    TBranch *b_AliFOCALClusterItr_fSigmaYZ;        //!
    TBranch *b_AliFOCALClusterItr_fVolumeId;       //!
    TBranch *b_AliFOCALClusterItr_fIsMisaligned;   //!
    TBranch *b_AliFOCALClusterItr_fSegment;        //!
    TBranch *b_AliFOCALClusterItr_fEnergy;         //!
    TBranch *b_AliFOCALClusterItr_fVariable;       //!
    TBranch *b_AliFOCALClusterItr_fGlobPos;        //!
    TBranch *b_AliFOCALClusterItr_fWeight;         //!
    TBranch *b_AliFOCALClusterItr_fSegIndex;       //!
    TBranch *b_AliFOCALClusterItr_fWidth1;         //!
    TBranch *b_AliFOCALClusterItr_fWidth2;         //!
    TBranch *b_AliFOCALClusterItr_fPhi;            //!
    TBranch *b_AliFOCALClusterItr_fSegmentEnergy;  //!
    TBranch *b_AliFOCALClusterItr_fHCALEnergy;     //!
    TBranch *b_AliFOCALClusterItr_fEisoR2;         //!
    TBranch *b_AliFOCALClusterItr_fEisoR4;         //!
    TBranch *b_AliFOCALClusterItr_fSeedEnergy;     //!
    TBranch *b_AliFOCALClusterItr_fNcells;         //!
    TBranch *b_AliFOCALCluster_;                   //!
    TBranch *b_AliFOCALCluster_fUniqueID;          //!
    TBranch *b_AliFOCALCluster_fBits;              //!
    TBranch *b_AliFOCALCluster_fTracks;            //!
    TBranch *b_AliFOCALCluster_fX;                 //!
    TBranch *b_AliFOCALCluster_fY;                 //!
    TBranch *b_AliFOCALCluster_fZ;                 //!
    TBranch *b_AliFOCALCluster_fSigmaY2;           //!
    TBranch *b_AliFOCALCluster_fSigmaZ2;           //!
    TBranch *b_AliFOCALCluster_fSigmaYZ;           //!
    TBranch *b_AliFOCALCluster_fVolumeId;          //!
    TBranch *b_AliFOCALCluster_fIsMisaligned;      //!
    TBranch *b_AliFOCALCluster_fSegment;           //!
    TBranch *b_AliFOCALCluster_fEnergy;            //!
    TBranch *b_AliFOCALCluster_fVariable;          //!
    TBranch *b_AliFOCALCluster_fGlobPos;           //!
    TBranch *b_AliFOCALCluster_fWeight;            //!
    TBranch *b_AliFOCALCluster_fSegIndex;          //!
    TBranch *b_AliFOCALCluster_fWidth1;            //!
    TBranch *b_AliFOCALCluster_fWidth2;            //!
    TBranch *b_AliFOCALCluster_fPhi;               //!
    TBranch *b_AliFOCALCluster_fSegmentEnergy;     //!
    TBranch *b_AliFOCALCluster_fHCALEnergy;        //!
    TBranch *b_AliFOCALCluster_fEisoR2;            //!
    TBranch *b_AliFOCALCluster_fEisoR4;            //!
    TBranch *b_AliFOCALCluster_fSeedEnergy;        //!
    TBranch *b_AliFOCALCluster_fNcells;            //!
    TBranch *b_AliFOCALClusterHCal_;               //!
    TBranch *b_AliFOCALClusterHCal_fUniqueID;      //!
    TBranch *b_AliFOCALClusterHCal_fBits;          //!
    TBranch *b_AliFOCALClusterHCal_fTracks;        //!
    TBranch *b_AliFOCALClusterHCal_fX;             //!
    TBranch *b_AliFOCALClusterHCal_fY;             //!
    TBranch *b_AliFOCALClusterHCal_fZ;             //!
    TBranch *b_AliFOCALClusterHCal_fSigmaY2;       //!
    TBranch *b_AliFOCALClusterHCal_fSigmaZ2;       //!
    TBranch *b_AliFOCALClusterHCal_fSigmaYZ;       //!
    TBranch *b_AliFOCALClusterHCal_fVolumeId;      //!
    TBranch *b_AliFOCALClusterHCal_fIsMisaligned;  //!
    TBranch *b_AliFOCALClusterHCal_fSegment;       //!
    TBranch *b_AliFOCALClusterHCal_fEnergy;        //!
    TBranch *b_AliFOCALClusterHCal_fVariable;      //!
    TBranch *b_AliFOCALClusterHCal_fGlobPos;       //!
    TBranch *b_AliFOCALClusterHCal_fWeight;        //!
    TBranch *b_AliFOCALClusterHCal_fSegIndex;      //!
    TBranch *b_AliFOCALClusterHCal_fWidth1;        //!
    TBranch *b_AliFOCALClusterHCal_fWidth2;        //!
    TBranch *b_AliFOCALClusterHCal_fPhi;           //!
    TBranch *b_AliFOCALClusterHCal_fSegmentEnergy; //!
    TBranch *b_AliFOCALClusterHCal_fHCALEnergy;    //!
    TBranch *b_AliFOCALClusterHCal_fEisoR2;        //!
    TBranch *b_AliFOCALClusterHCal_fEisoR4;        //!
    TBranch *b_AliFOCALClusterHCal_fSeedEnergy;    //!
    TBranch *b_AliFOCALClusterHCal_fNcells;        //!
    TBranch *b_AliFOCALPad_;                       //!
    TBranch *b_AliFOCALPad_fUniqueID;              //!
    TBranch *b_AliFOCALPad_fBits;                  //!
    TBranch *b_AliFOCALPad_fPadid;                 //!
    TBranch *b_AliFOCALPad_fRow;                   //!
    TBranch *b_AliFOCALPad_fCol;                   //!
    TBranch *b_AliFOCALPad_fLayer;                 //!
    TBranch *b_AliFOCALPad_fSegment;               //!
    TBranch *b_AliFOCALPad_fTower;                 //!
    TBranch *b_AliFOCALPad_fX;                     //!
    TBranch *b_AliFOCALPad_fY;                     //!
    TBranch *b_AliFOCALPad_fZ;                     //!
    TBranch *b_AliFOCALPad_fE;                     //!
    TBranch *b_AliFOCALPad_fIsPixel;               //!
    TBranch *b_AliFOCALCell_;                      //!
    TBranch *b_AliFOCALCell_fUniqueID;             //!
    TBranch *b_AliFOCALCell_fBits;                 //!
    TBranch *b_AliFOCALCell_fCellid;               //!
    TBranch *b_AliFOCALCell_fRow;                  //!
    TBranch *b_AliFOCALCell_fCol;                  //!
    TBranch *b_AliFOCALCell_fSegment;              //!
    TBranch *b_AliFOCALCell_fTower;                //!
    TBranch *b_AliFOCALCell_fX;                    //!
    TBranch *b_AliFOCALCell_fY;                    //!
    TBranch *b_AliFOCALCell_fZ;                    //!
    TBranch *b_AliFOCALCell_fE;                    //!
    TBranch *b_AliFOCALCell_fWeight;               //!
    TBranch *b_AliFOCALCell_fSeedEnergy;           //!
    TBranch *b_AliFOCALCell_fCenter;               //!

public:
    static constexpr Int_t kMaxAliFOCALClusterItr = 40;
    static constexpr Int_t kMaxAliFOCALCluster = 1;
    static constexpr Int_t kMaxAliFOCALClusterHCal = 1;
    static constexpr Int_t kMaxAliFOCALPad = 1;
    static constexpr Int_t kMaxAliFOCALCell = 62;

    Int_t AliFOCALClusterItr_;
    UInt_t AliFOCALClusterItr_fUniqueID[kMaxAliFOCALClusterItr];     //[AliFOCALClusterItr_]
    UInt_t AliFOCALClusterItr_fBits[kMaxAliFOCALClusterItr];         //[AliFOCALClusterItr_]
    Int_t AliFOCALClusterItr_fTracks[kMaxAliFOCALClusterItr][3];     //[AliFOCALClusterItr_]
    Float_t AliFOCALClusterItr_fX[kMaxAliFOCALClusterItr];           //[AliFOCALClusterItr_]
    Float_t AliFOCALClusterItr_fY[kMaxAliFOCALClusterItr];           //[AliFOCALClusterItr_]
    Float_t AliFOCALClusterItr_fZ[kMaxAliFOCALClusterItr];           //[AliFOCALClusterItr_]
    Float_t AliFOCALClusterItr_fSigmaY2[kMaxAliFOCALClusterItr];     //[AliFOCALClusterItr_]
    Float_t AliFOCALClusterItr_fSigmaZ2[kMaxAliFOCALClusterItr];     //[AliFOCALClusterItr_]
    Float_t AliFOCALClusterItr_fSigmaYZ[kMaxAliFOCALClusterItr];     //[AliFOCALClusterItr_]
    UShort_t AliFOCALClusterItr_fVolumeId[kMaxAliFOCALClusterItr];   //[AliFOCALClusterItr_]
    Bool_t AliFOCALClusterItr_fIsMisaligned[kMaxAliFOCALClusterItr]; //[AliFOCALClusterItr_]
    Int_t AliFOCALClusterItr_fSegment[kMaxAliFOCALClusterItr];       //[AliFOCALClusterItr_]
    Float_t AliFOCALClusterItr_fEnergy[kMaxAliFOCALClusterItr];      //[AliFOCALClusterItr_]
    Bool_t AliFOCALClusterItr_fVariable[kMaxAliFOCALClusterItr];     //[AliFOCALClusterItr_]
    TVector3 AliFOCALClusterItr_fGlobPos[kMaxAliFOCALClusterItr];
    Float_t AliFOCALClusterItr_fWeight[kMaxAliFOCALClusterItr];            //[AliFOCALClusterItr_]
    Int_t AliFOCALClusterItr_fSegIndex[kMaxAliFOCALClusterItr][10];        //[AliFOCALClusterItr_]
    Float_t AliFOCALClusterItr_fWidth1[kMaxAliFOCALClusterItr][10];        //[AliFOCALClusterItr_]
    Float_t AliFOCALClusterItr_fWidth2[kMaxAliFOCALClusterItr][10];        //[AliFOCALClusterItr_]
    Float_t AliFOCALClusterItr_fPhi[kMaxAliFOCALClusterItr][10];           //[AliFOCALClusterItr_]
    Float_t AliFOCALClusterItr_fSegmentEnergy[kMaxAliFOCALClusterItr][10]; //[AliFOCALClusterItr_]
    Float_t AliFOCALClusterItr_fHCALEnergy[kMaxAliFOCALClusterItr];        //[AliFOCALClusterItr_]
    Float_t AliFOCALClusterItr_fEisoR2[kMaxAliFOCALClusterItr];            //[AliFOCALClusterItr_]
    Float_t AliFOCALClusterItr_fEisoR4[kMaxAliFOCALClusterItr];            //[AliFOCALClusterItr_]
    Float_t AliFOCALClusterItr_fSeedEnergy[kMaxAliFOCALClusterItr][10];    //[AliFOCALClusterItr_]
    Int_t AliFOCALClusterItr_fNcells[kMaxAliFOCALClusterItr][10];          //[AliFOCALClusterItr_]
    Int_t AliFOCALCluster_;
    UInt_t AliFOCALCluster_fUniqueID[kMaxAliFOCALCluster];     //[AliFOCALCluster_]
    UInt_t AliFOCALCluster_fBits[kMaxAliFOCALCluster];         //[AliFOCALCluster_]
    Int_t AliFOCALCluster_fTracks[kMaxAliFOCALCluster][3];     //[AliFOCALCluster_]
    Float_t AliFOCALCluster_fX[kMaxAliFOCALCluster];           //[AliFOCALCluster_]
    Float_t AliFOCALCluster_fY[kMaxAliFOCALCluster];           //[AliFOCALCluster_]
    Float_t AliFOCALCluster_fZ[kMaxAliFOCALCluster];           //[AliFOCALCluster_]
    Float_t AliFOCALCluster_fSigmaY2[kMaxAliFOCALCluster];     //[AliFOCALCluster_]
    Float_t AliFOCALCluster_fSigmaZ2[kMaxAliFOCALCluster];     //[AliFOCALCluster_]
    Float_t AliFOCALCluster_fSigmaYZ[kMaxAliFOCALCluster];     //[AliFOCALCluster_]
    UShort_t AliFOCALCluster_fVolumeId[kMaxAliFOCALCluster];   //[AliFOCALCluster_]
    Bool_t AliFOCALCluster_fIsMisaligned[kMaxAliFOCALCluster]; //[AliFOCALCluster_]
    Int_t AliFOCALCluster_fSegment[kMaxAliFOCALCluster];       //[AliFOCALCluster_]
    Float_t AliFOCALCluster_fEnergy[kMaxAliFOCALCluster];      //[AliFOCALCluster_]
    Bool_t AliFOCALCluster_fVariable[kMaxAliFOCALCluster];     //[AliFOCALCluster_]
    TVector3 AliFOCALCluster_fGlobPos[kMaxAliFOCALCluster];
    Float_t AliFOCALCluster_fWeight[kMaxAliFOCALCluster];            //[AliFOCALCluster_]
    Int_t AliFOCALCluster_fSegIndex[kMaxAliFOCALCluster][10];        //[AliFOCALCluster_]
    Float_t AliFOCALCluster_fWidth1[kMaxAliFOCALCluster][10];        //[AliFOCALCluster_]
    Float_t AliFOCALCluster_fWidth2[kMaxAliFOCALCluster][10];        //[AliFOCALCluster_]
    Float_t AliFOCALCluster_fPhi[kMaxAliFOCALCluster][10];           //[AliFOCALCluster_]
    Float_t AliFOCALCluster_fSegmentEnergy[kMaxAliFOCALCluster][10]; //[AliFOCALCluster_]
    Float_t AliFOCALCluster_fHCALEnergy[kMaxAliFOCALCluster];        //[AliFOCALCluster_]
    Float_t AliFOCALCluster_fEisoR2[kMaxAliFOCALCluster];            //[AliFOCALCluster_]
    Float_t AliFOCALCluster_fEisoR4[kMaxAliFOCALCluster];            //[AliFOCALCluster_]
    Float_t AliFOCALCluster_fSeedEnergy[kMaxAliFOCALCluster][10];    //[AliFOCALCluster_]
    Int_t AliFOCALCluster_fNcells[kMaxAliFOCALCluster][10];          //[AliFOCALCluster_]
    Int_t AliFOCALClusterHCal_;
    UInt_t AliFOCALClusterHCal_fUniqueID[kMaxAliFOCALClusterHCal];     //[AliFOCALClusterHCal_]
    UInt_t AliFOCALClusterHCal_fBits[kMaxAliFOCALClusterHCal];         //[AliFOCALClusterHCal_]
    Int_t AliFOCALClusterHCal_fTracks[kMaxAliFOCALClusterHCal][3];     //[AliFOCALClusterHCal_]
    Float_t AliFOCALClusterHCal_fX[kMaxAliFOCALClusterHCal];           //[AliFOCALClusterHCal_]
    Float_t AliFOCALClusterHCal_fY[kMaxAliFOCALClusterHCal];           //[AliFOCALClusterHCal_]
    Float_t AliFOCALClusterHCal_fZ[kMaxAliFOCALClusterHCal];           //[AliFOCALClusterHCal_]
    Float_t AliFOCALClusterHCal_fSigmaY2[kMaxAliFOCALClusterHCal];     //[AliFOCALClusterHCal_]
    Float_t AliFOCALClusterHCal_fSigmaZ2[kMaxAliFOCALClusterHCal];     //[AliFOCALClusterHCal_]
    Float_t AliFOCALClusterHCal_fSigmaYZ[kMaxAliFOCALClusterHCal];     //[AliFOCALClusterHCal_]
    UShort_t AliFOCALClusterHCal_fVolumeId[kMaxAliFOCALClusterHCal];   //[AliFOCALClusterHCal_]
    Bool_t AliFOCALClusterHCal_fIsMisaligned[kMaxAliFOCALClusterHCal]; //[AliFOCALClusterHCal_]
    Int_t AliFOCALClusterHCal_fSegment[kMaxAliFOCALClusterHCal];       //[AliFOCALClusterHCal_]
    Float_t AliFOCALClusterHCal_fEnergy[kMaxAliFOCALClusterHCal];      //[AliFOCALClusterHCal_]
    Bool_t AliFOCALClusterHCal_fVariable[kMaxAliFOCALClusterHCal];     //[AliFOCALClusterHCal_]
    TVector3 AliFOCALClusterHCal_fGlobPos[kMaxAliFOCALClusterHCal];
    Float_t AliFOCALClusterHCal_fWeight[kMaxAliFOCALClusterHCal];            //[AliFOCALClusterHCal_]
    Int_t AliFOCALClusterHCal_fSegIndex[kMaxAliFOCALClusterHCal][10];        //[AliFOCALClusterHCal_]
    Float_t AliFOCALClusterHCal_fWidth1[kMaxAliFOCALClusterHCal][10];        //[AliFOCALClusterHCal_]
    Float_t AliFOCALClusterHCal_fWidth2[kMaxAliFOCALClusterHCal][10];        //[AliFOCALClusterHCal_]
    Float_t AliFOCALClusterHCal_fPhi[kMaxAliFOCALClusterHCal][10];           //[AliFOCALClusterHCal_]
    Float_t AliFOCALClusterHCal_fSegmentEnergy[kMaxAliFOCALClusterHCal][10]; //[AliFOCALClusterHCal_]
    Float_t AliFOCALClusterHCal_fHCALEnergy[kMaxAliFOCALClusterHCal];        //[AliFOCALClusterHCal_]
    Float_t AliFOCALClusterHCal_fEisoR2[kMaxAliFOCALClusterHCal];            //[AliFOCALClusterHCal_]
    Float_t AliFOCALClusterHCal_fEisoR4[kMaxAliFOCALClusterHCal];            //[AliFOCALClusterHCal_]
    Float_t AliFOCALClusterHCal_fSeedEnergy[kMaxAliFOCALClusterHCal][10];    //[AliFOCALClusterHCal_]
    Int_t AliFOCALClusterHCal_fNcells[kMaxAliFOCALClusterHCal][10];          //[AliFOCALClusterHCal_]
    Int_t AliFOCALPad_;
    UInt_t AliFOCALPad_fUniqueID[kMaxAliFOCALPad]; //[AliFOCALPad_]
    UInt_t AliFOCALPad_fBits[kMaxAliFOCALPad];     //[AliFOCALPad_]
    Int_t AliFOCALPad_fPadid[kMaxAliFOCALPad];     //[AliFOCALPad_]
    Int_t AliFOCALPad_fRow[kMaxAliFOCALPad];       //[AliFOCALPad_]
    Int_t AliFOCALPad_fCol[kMaxAliFOCALPad];       //[AliFOCALPad_]
    Int_t AliFOCALPad_fLayer[kMaxAliFOCALPad];     //[AliFOCALPad_]
    Int_t AliFOCALPad_fSegment[kMaxAliFOCALPad];   //[AliFOCALPad_]
    Int_t AliFOCALPad_fTower[kMaxAliFOCALPad];     //[AliFOCALPad_]
    Float_t AliFOCALPad_fX[kMaxAliFOCALPad];       //[AliFOCALPad_]
    Float_t AliFOCALPad_fY[kMaxAliFOCALPad];       //[AliFOCALPad_]
    Float_t AliFOCALPad_fZ[kMaxAliFOCALPad];       //[AliFOCALPad_]
    Float_t AliFOCALPad_fE[kMaxAliFOCALPad];       //[AliFOCALPad_]
    Bool_t AliFOCALPad_fIsPixel[kMaxAliFOCALPad];  //[AliFOCALPad_]
    Int_t AliFOCALCell_;
    UInt_t AliFOCALCell_fUniqueID[kMaxAliFOCALCell];    //[AliFOCALCell_]
    UInt_t AliFOCALCell_fBits[kMaxAliFOCALCell];        //[AliFOCALCell_]
    Int_t AliFOCALCell_fCellid[kMaxAliFOCALCell];       //[AliFOCALCell_]
    Int_t AliFOCALCell_fRow[kMaxAliFOCALCell];          //[AliFOCALCell_]
    Int_t AliFOCALCell_fCol[kMaxAliFOCALCell];          //[AliFOCALCell_]
    Int_t AliFOCALCell_fSegment[kMaxAliFOCALCell];      //[AliFOCALCell_]
    Int_t AliFOCALCell_fTower[kMaxAliFOCALCell];        //[AliFOCALCell_]
    Float_t AliFOCALCell_fX[kMaxAliFOCALCell];          //[AliFOCALCell_]
    Float_t AliFOCALCell_fY[kMaxAliFOCALCell];          //[AliFOCALCell_]
    Float_t AliFOCALCell_fZ[kMaxAliFOCALCell];          //[AliFOCALCell_]
    Float_t AliFOCALCell_fE[kMaxAliFOCALCell];          //[AliFOCALCell_]
    Float_t AliFOCALCell_fWeight[kMaxAliFOCALCell];     //[AliFOCALCell_]
    Float_t AliFOCALCell_fSeedEnergy[kMaxAliFOCALCell]; //[AliFOCALCell_]
    Bool_t AliFOCALCell_fCenter[kMaxAliFOCALCell];      //[AliFOCALCell_]

    AliRootClusterEventManager(const char *file_name, const char *folder_name);
    ~AliRootClusterEventManager() override;
    void classCheck();

    std::string getParticalName() override { return "AliFOCALClusterItr"; };
    Long64_t getTotalEntries() override { return this->total_entries; };
    void setCurrentEntry(Long64_t entry) override
    {
        fChain->GetEntry(entry);
    }
};

#endif