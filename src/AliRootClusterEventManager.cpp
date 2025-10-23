// #include "AliRootClusterEventManager.h"
// #include "TFile.h"
// #include "TDirectory.h"
// #include "Utils.h"
// #include "TH2F.h"
// #include <iostream>
// using namespace xqy;
// using namespace std;

// AliRootClusterEventManager::AliRootClusterEventManager(const char *file_name, const char *folder_name)
// {
//     this->folder_name = folder_name;

//     TFile *f = TFile::Open(file_name);
//     TDirectory *dir = (TDirectory *)f->Get(Utils::concatenate_const_char(*new std::vector<const char *>{file_name, ":/", folder_name}));
//     dir->GetObject("fTreeR", fChain);

//     fChain->SetMakeClass(1);
//     this->total_entries = this->fChain->GetEntriesFast();
//     fChain->SetBranchAddress("AliFOCALClusterItr", &AliFOCALClusterItr_, &b_AliFOCALClusterItr_);
//     fChain->SetBranchAddress("AliFOCALClusterItr.fUniqueID", AliFOCALClusterItr_fUniqueID, &b_AliFOCALClusterItr_fUniqueID);
//     fChain->SetBranchAddress("AliFOCALClusterItr.fBits", AliFOCALClusterItr_fBits, &b_AliFOCALClusterItr_fBits);
//     fChain->SetBranchAddress("AliFOCALClusterItr.fTracks[3]", AliFOCALClusterItr_fTracks, &b_AliFOCALClusterItr_fTracks);
//     fChain->SetBranchAddress("AliFOCALClusterItr.fX", AliFOCALClusterItr_fX, &b_AliFOCALClusterItr_fX);
//     fChain->SetBranchAddress("AliFOCALClusterItr.fY", AliFOCALClusterItr_fY, &b_AliFOCALClusterItr_fY);
//     fChain->SetBranchAddress("AliFOCALClusterItr.fZ", AliFOCALClusterItr_fZ, &b_AliFOCALClusterItr_fZ);
//     fChain->SetBranchAddress("AliFOCALClusterItr.fSigmaY2", AliFOCALClusterItr_fSigmaY2, &b_AliFOCALClusterItr_fSigmaY2);
//     fChain->SetBranchAddress("AliFOCALClusterItr.fSigmaZ2", AliFOCALClusterItr_fSigmaZ2, &b_AliFOCALClusterItr_fSigmaZ2);
//     fChain->SetBranchAddress("AliFOCALClusterItr.fSigmaYZ", AliFOCALClusterItr_fSigmaYZ, &b_AliFOCALClusterItr_fSigmaYZ);
//     fChain->SetBranchAddress("AliFOCALClusterItr.fVolumeId", AliFOCALClusterItr_fVolumeId, &b_AliFOCALClusterItr_fVolumeId);
//     fChain->SetBranchAddress("AliFOCALClusterItr.fIsMisaligned", AliFOCALClusterItr_fIsMisaligned, &b_AliFOCALClusterItr_fIsMisaligned);
//     fChain->SetBranchAddress("AliFOCALClusterItr.fSegment", AliFOCALClusterItr_fSegment, &b_AliFOCALClusterItr_fSegment);
//     fChain->SetBranchAddress("AliFOCALClusterItr.fEnergy", AliFOCALClusterItr_fEnergy, &b_AliFOCALClusterItr_fEnergy);
//     fChain->SetBranchAddress("AliFOCALClusterItr.fVariable", AliFOCALClusterItr_fVariable, &b_AliFOCALClusterItr_fVariable);
//     fChain->SetBranchAddress("AliFOCALClusterItr.fGlobPos", AliFOCALClusterItr_fGlobPos, &b_AliFOCALClusterItr_fGlobPos);
//     fChain->SetBranchAddress("AliFOCALClusterItr.fWeight", AliFOCALClusterItr_fWeight, &b_AliFOCALClusterItr_fWeight);
//     fChain->SetBranchAddress("AliFOCALClusterItr.fSegIndex[10]", AliFOCALClusterItr_fSegIndex, &b_AliFOCALClusterItr_fSegIndex);
//     fChain->SetBranchAddress("AliFOCALClusterItr.fWidth1[10]", AliFOCALClusterItr_fWidth1, &b_AliFOCALClusterItr_fWidth1);
//     fChain->SetBranchAddress("AliFOCALClusterItr.fWidth2[10]", AliFOCALClusterItr_fWidth2, &b_AliFOCALClusterItr_fWidth2);
//     fChain->SetBranchAddress("AliFOCALClusterItr.fPhi[10]", AliFOCALClusterItr_fPhi, &b_AliFOCALClusterItr_fPhi);
//     fChain->SetBranchAddress("AliFOCALClusterItr.fSegmentEnergy[10]", AliFOCALClusterItr_fSegmentEnergy, &b_AliFOCALClusterItr_fSegmentEnergy);
//     fChain->SetBranchAddress("AliFOCALClusterItr.fHCALEnergy", AliFOCALClusterItr_fHCALEnergy, &b_AliFOCALClusterItr_fHCALEnergy);
//     fChain->SetBranchAddress("AliFOCALClusterItr.fEisoR2", AliFOCALClusterItr_fEisoR2, &b_AliFOCALClusterItr_fEisoR2);
//     fChain->SetBranchAddress("AliFOCALClusterItr.fEisoR4", AliFOCALClusterItr_fEisoR4, &b_AliFOCALClusterItr_fEisoR4);
//     fChain->SetBranchAddress("AliFOCALClusterItr.fSeedEnergy[10]", AliFOCALClusterItr_fSeedEnergy, &b_AliFOCALClusterItr_fSeedEnergy);
//     fChain->SetBranchAddress("AliFOCALClusterItr.fNcells[10]", AliFOCALClusterItr_fNcells, &b_AliFOCALClusterItr_fNcells);
//     fChain->SetBranchAddress("AliFOCALCluster", &AliFOCALCluster_, &b_AliFOCALCluster_);
//     fChain->SetBranchAddress("AliFOCALCluster.fUniqueID", &AliFOCALCluster_fUniqueID, &b_AliFOCALCluster_fUniqueID);
//     fChain->SetBranchAddress("AliFOCALCluster.fBits", &AliFOCALCluster_fBits, &b_AliFOCALCluster_fBits);
//     fChain->SetBranchAddress("AliFOCALCluster.fTracks[3]", &AliFOCALCluster_fTracks, &b_AliFOCALCluster_fTracks);
//     fChain->SetBranchAddress("AliFOCALCluster.fX", &AliFOCALCluster_fX, &b_AliFOCALCluster_fX);
//     fChain->SetBranchAddress("AliFOCALCluster.fY", &AliFOCALCluster_fY, &b_AliFOCALCluster_fY);
//     fChain->SetBranchAddress("AliFOCALCluster.fZ", &AliFOCALCluster_fZ, &b_AliFOCALCluster_fZ);
//     fChain->SetBranchAddress("AliFOCALCluster.fSigmaY2", &AliFOCALCluster_fSigmaY2, &b_AliFOCALCluster_fSigmaY2);
//     fChain->SetBranchAddress("AliFOCALCluster.fSigmaZ2", &AliFOCALCluster_fSigmaZ2, &b_AliFOCALCluster_fSigmaZ2);
//     fChain->SetBranchAddress("AliFOCALCluster.fSigmaYZ", &AliFOCALCluster_fSigmaYZ, &b_AliFOCALCluster_fSigmaYZ);
//     fChain->SetBranchAddress("AliFOCALCluster.fVolumeId", &AliFOCALCluster_fVolumeId, &b_AliFOCALCluster_fVolumeId);
//     fChain->SetBranchAddress("AliFOCALCluster.fIsMisaligned", &AliFOCALCluster_fIsMisaligned, &b_AliFOCALCluster_fIsMisaligned);
//     fChain->SetBranchAddress("AliFOCALCluster.fSegment", &AliFOCALCluster_fSegment, &b_AliFOCALCluster_fSegment);
//     fChain->SetBranchAddress("AliFOCALCluster.fEnergy", &AliFOCALCluster_fEnergy, &b_AliFOCALCluster_fEnergy);
//     fChain->SetBranchAddress("AliFOCALCluster.fVariable", &AliFOCALCluster_fVariable, &b_AliFOCALCluster_fVariable);
//     fChain->SetBranchAddress("AliFOCALCluster.fGlobPos", &AliFOCALCluster_fGlobPos, &b_AliFOCALCluster_fGlobPos);
//     fChain->SetBranchAddress("AliFOCALCluster.fWeight", &AliFOCALCluster_fWeight, &b_AliFOCALCluster_fWeight);
//     fChain->SetBranchAddress("AliFOCALCluster.fSegIndex[10]", &AliFOCALCluster_fSegIndex, &b_AliFOCALCluster_fSegIndex);
//     fChain->SetBranchAddress("AliFOCALCluster.fWidth1[10]", &AliFOCALCluster_fWidth1, &b_AliFOCALCluster_fWidth1);
//     fChain->SetBranchAddress("AliFOCALCluster.fWidth2[10]", &AliFOCALCluster_fWidth2, &b_AliFOCALCluster_fWidth2);
//     fChain->SetBranchAddress("AliFOCALCluster.fPhi[10]", &AliFOCALCluster_fPhi, &b_AliFOCALCluster_fPhi);
//     fChain->SetBranchAddress("AliFOCALCluster.fSegmentEnergy[10]", &AliFOCALCluster_fSegmentEnergy, &b_AliFOCALCluster_fSegmentEnergy);
//     fChain->SetBranchAddress("AliFOCALCluster.fHCALEnergy", &AliFOCALCluster_fHCALEnergy, &b_AliFOCALCluster_fHCALEnergy);
//     fChain->SetBranchAddress("AliFOCALCluster.fEisoR2", &AliFOCALCluster_fEisoR2, &b_AliFOCALCluster_fEisoR2);
//     fChain->SetBranchAddress("AliFOCALCluster.fEisoR4", &AliFOCALCluster_fEisoR4, &b_AliFOCALCluster_fEisoR4);
//     fChain->SetBranchAddress("AliFOCALCluster.fSeedEnergy[10]", &AliFOCALCluster_fSeedEnergy, &b_AliFOCALCluster_fSeedEnergy);
//     fChain->SetBranchAddress("AliFOCALCluster.fNcells[10]", &AliFOCALCluster_fNcells, &b_AliFOCALCluster_fNcells);
//     fChain->SetBranchAddress("AliFOCALClusterHCal", &AliFOCALClusterHCal_, &b_AliFOCALClusterHCal_);
//     fChain->SetBranchAddress("AliFOCALClusterHCal.fUniqueID", &AliFOCALClusterHCal_fUniqueID, &b_AliFOCALClusterHCal_fUniqueID);
//     fChain->SetBranchAddress("AliFOCALClusterHCal.fBits", &AliFOCALClusterHCal_fBits, &b_AliFOCALClusterHCal_fBits);
//     fChain->SetBranchAddress("AliFOCALClusterHCal.fTracks[3]", &AliFOCALClusterHCal_fTracks, &b_AliFOCALClusterHCal_fTracks);
//     fChain->SetBranchAddress("AliFOCALClusterHCal.fX", &AliFOCALClusterHCal_fX, &b_AliFOCALClusterHCal_fX);
//     fChain->SetBranchAddress("AliFOCALClusterHCal.fY", &AliFOCALClusterHCal_fY, &b_AliFOCALClusterHCal_fY);
//     fChain->SetBranchAddress("AliFOCALClusterHCal.fZ", &AliFOCALClusterHCal_fZ, &b_AliFOCALClusterHCal_fZ);
//     fChain->SetBranchAddress("AliFOCALClusterHCal.fSigmaY2", &AliFOCALClusterHCal_fSigmaY2, &b_AliFOCALClusterHCal_fSigmaY2);
//     fChain->SetBranchAddress("AliFOCALClusterHCal.fSigmaZ2", &AliFOCALClusterHCal_fSigmaZ2, &b_AliFOCALClusterHCal_fSigmaZ2);
//     fChain->SetBranchAddress("AliFOCALClusterHCal.fSigmaYZ", &AliFOCALClusterHCal_fSigmaYZ, &b_AliFOCALClusterHCal_fSigmaYZ);
//     fChain->SetBranchAddress("AliFOCALClusterHCal.fVolumeId", &AliFOCALClusterHCal_fVolumeId, &b_AliFOCALClusterHCal_fVolumeId);
//     fChain->SetBranchAddress("AliFOCALClusterHCal.fIsMisaligned", &AliFOCALClusterHCal_fIsMisaligned, &b_AliFOCALClusterHCal_fIsMisaligned);
//     fChain->SetBranchAddress("AliFOCALClusterHCal.fSegment", &AliFOCALClusterHCal_fSegment, &b_AliFOCALClusterHCal_fSegment);
//     fChain->SetBranchAddress("AliFOCALClusterHCal.fEnergy", &AliFOCALClusterHCal_fEnergy, &b_AliFOCALClusterHCal_fEnergy);
//     fChain->SetBranchAddress("AliFOCALClusterHCal.fVariable", &AliFOCALClusterHCal_fVariable, &b_AliFOCALClusterHCal_fVariable);
//     fChain->SetBranchAddress("AliFOCALClusterHCal.fGlobPos", &AliFOCALClusterHCal_fGlobPos, &b_AliFOCALClusterHCal_fGlobPos);
//     fChain->SetBranchAddress("AliFOCALClusterHCal.fWeight", &AliFOCALClusterHCal_fWeight, &b_AliFOCALClusterHCal_fWeight);
//     fChain->SetBranchAddress("AliFOCALClusterHCal.fSegIndex[10]", &AliFOCALClusterHCal_fSegIndex, &b_AliFOCALClusterHCal_fSegIndex);
//     fChain->SetBranchAddress("AliFOCALClusterHCal.fWidth1[10]", &AliFOCALClusterHCal_fWidth1, &b_AliFOCALClusterHCal_fWidth1);
//     fChain->SetBranchAddress("AliFOCALClusterHCal.fWidth2[10]", &AliFOCALClusterHCal_fWidth2, &b_AliFOCALClusterHCal_fWidth2);
//     fChain->SetBranchAddress("AliFOCALClusterHCal.fPhi[10]", &AliFOCALClusterHCal_fPhi, &b_AliFOCALClusterHCal_fPhi);
//     fChain->SetBranchAddress("AliFOCALClusterHCal.fSegmentEnergy[10]", &AliFOCALClusterHCal_fSegmentEnergy, &b_AliFOCALClusterHCal_fSegmentEnergy);
//     fChain->SetBranchAddress("AliFOCALClusterHCal.fHCALEnergy", &AliFOCALClusterHCal_fHCALEnergy, &b_AliFOCALClusterHCal_fHCALEnergy);
//     fChain->SetBranchAddress("AliFOCALClusterHCal.fEisoR2", &AliFOCALClusterHCal_fEisoR2, &b_AliFOCALClusterHCal_fEisoR2);
//     fChain->SetBranchAddress("AliFOCALClusterHCal.fEisoR4", &AliFOCALClusterHCal_fEisoR4, &b_AliFOCALClusterHCal_fEisoR4);
//     fChain->SetBranchAddress("AliFOCALClusterHCal.fSeedEnergy[10]", &AliFOCALClusterHCal_fSeedEnergy, &b_AliFOCALClusterHCal_fSeedEnergy);
//     fChain->SetBranchAddress("AliFOCALClusterHCal.fNcells[10]", &AliFOCALClusterHCal_fNcells, &b_AliFOCALClusterHCal_fNcells);
//     fChain->SetBranchAddress("AliFOCALPad", &AliFOCALPad_, &b_AliFOCALPad_);
//     fChain->SetBranchAddress("AliFOCALPad.fUniqueID", &AliFOCALPad_fUniqueID, &b_AliFOCALPad_fUniqueID);
//     fChain->SetBranchAddress("AliFOCALPad.fBits", &AliFOCALPad_fBits, &b_AliFOCALPad_fBits);
//     fChain->SetBranchAddress("AliFOCALPad.fPadid", &AliFOCALPad_fPadid, &b_AliFOCALPad_fPadid);
//     fChain->SetBranchAddress("AliFOCALPad.fRow", &AliFOCALPad_fRow, &b_AliFOCALPad_fRow);
//     fChain->SetBranchAddress("AliFOCALPad.fCol", &AliFOCALPad_fCol, &b_AliFOCALPad_fCol);
//     fChain->SetBranchAddress("AliFOCALPad.fLayer", &AliFOCALPad_fLayer, &b_AliFOCALPad_fLayer);
//     fChain->SetBranchAddress("AliFOCALPad.fSegment", &AliFOCALPad_fSegment, &b_AliFOCALPad_fSegment);
//     fChain->SetBranchAddress("AliFOCALPad.fTower", &AliFOCALPad_fTower, &b_AliFOCALPad_fTower);
//     fChain->SetBranchAddress("AliFOCALPad.fX", &AliFOCALPad_fX, &b_AliFOCALPad_fX);
//     fChain->SetBranchAddress("AliFOCALPad.fY", &AliFOCALPad_fY, &b_AliFOCALPad_fY);
//     fChain->SetBranchAddress("AliFOCALPad.fZ", &AliFOCALPad_fZ, &b_AliFOCALPad_fZ);
//     fChain->SetBranchAddress("AliFOCALPad.fE", &AliFOCALPad_fE, &b_AliFOCALPad_fE);
//     fChain->SetBranchAddress("AliFOCALPad.fIsPixel", &AliFOCALPad_fIsPixel, &b_AliFOCALPad_fIsPixel);
//     fChain->SetBranchAddress("AliFOCALCell", &AliFOCALCell_, &b_AliFOCALCell_);
//     fChain->SetBranchAddress("AliFOCALCell.fUniqueID", AliFOCALCell_fUniqueID, &b_AliFOCALCell_fUniqueID);
//     fChain->SetBranchAddress("AliFOCALCell.fBits", AliFOCALCell_fBits, &b_AliFOCALCell_fBits);
//     fChain->SetBranchAddress("AliFOCALCell.fCellid", AliFOCALCell_fCellid, &b_AliFOCALCell_fCellid);
//     fChain->SetBranchAddress("AliFOCALCell.fRow", AliFOCALCell_fRow, &b_AliFOCALCell_fRow);
//     fChain->SetBranchAddress("AliFOCALCell.fCol", AliFOCALCell_fCol, &b_AliFOCALCell_fCol);
//     fChain->SetBranchAddress("AliFOCALCell.fSegment", AliFOCALCell_fSegment, &b_AliFOCALCell_fSegment);
//     fChain->SetBranchAddress("AliFOCALCell.fTower", AliFOCALCell_fTower, &b_AliFOCALCell_fTower);
//     fChain->SetBranchAddress("AliFOCALCell.fX", AliFOCALCell_fX, &b_AliFOCALCell_fX);
//     fChain->SetBranchAddress("AliFOCALCell.fY", AliFOCALCell_fY, &b_AliFOCALCell_fY);
//     fChain->SetBranchAddress("AliFOCALCell.fZ", AliFOCALCell_fZ, &b_AliFOCALCell_fZ);
//     fChain->SetBranchAddress("AliFOCALCell.fE", AliFOCALCell_fE, &b_AliFOCALCell_fE);
//     fChain->SetBranchAddress("AliFOCALCell.fWeight", AliFOCALCell_fWeight, &b_AliFOCALCell_fWeight);
//     fChain->SetBranchAddress("AliFOCALCell.fSeedEnergy", AliFOCALCell_fSeedEnergy, &b_AliFOCALCell_fSeedEnergy);
//     fChain->SetBranchAddress("AliFOCALCell.fCenter", AliFOCALCell_fCenter, &b_AliFOCALCell_fCenter);
// }

// AliRootClusterEventManager::~AliRootClusterEventManager()
// {
//     delete fChain->GetCurrentFile();
// }

// void AliRootClusterEventManager::classCheck()
// {
//     TFile *f = TFile::Open(
//         Utils::concatenate_const_char(*new std::vector<const char *>{"classCheck4FOCALCluster/", folder_name, "_clusterAna.root"}),
//         "RECREATE");
//     TH2F *h2 = new TH2F("h2", "h2", 300, -50, 50, 300, -50, 50);
//     cout << "Checking class AliRootClusterEventManager ..." << endl;
//     assert(this->total_entries == 1);

//     for (Long64_t i = 0; i < this->total_entries; i++)
//     {
//         this->setCurrentEntry(i);
//         // cout << "Entry " << i << ": AliFOCALClusterItr_ = " << AliFOCALClusterItr_ << endl;
//         for (int j = 0; j < this->AliFOCALClusterItr_; j++)
//         {
//             h2->Fill(AliFOCALClusterItr_fX[j], AliFOCALClusterItr_fY[j]);
//         }
//     }
//     TCanvas *c1 = new TCanvas("c1", "c1", 1800, 1600);
//     h2->Draw();
//     c1->Write();
//     f->Close();
//     delete c1;
// }
