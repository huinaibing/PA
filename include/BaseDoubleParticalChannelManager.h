#ifndef __BASE_DOUBLE_PARTICAL_CHANNEL_MANAGER__
#define __BASE_DOUBLE_PARTICAL_CHANNEL_MANAGER__

#include "TFile.h"
#include "BaseManager.h"
#include "TTree.h"
#include "TBranch.h"
#include "TCanvas.h"
#include "TH1.h"
#include "Utils.h"

class BaseDoubleParticalChannelManager : public BaseManager
{
protected:
    std::string partical_name;
    float partical_mass; // GeV
    TFile *root_file;
    TTree *tree;

    // 树的分支
    float negative_px;
    float negative_py;
    float negative_pz;

    float positive_px;
    float positive_py;
    float positive_pz;

    Long64_t total_entries;

public:
    BaseDoubleParticalChannelManager(const char *file_path,
                                     const char *partical_name,
                                     float partical_mass);
    ~BaseDoubleParticalChannelManager();

    void classCheck();
    void setCurrentEntry(Long64_t entry);

    float getTheoryMass();
    std::string getParticalName();
    Long64_t getTotalEntries();

    float getMotherParticlePx();
    float getMotherParticlePy();
    float getMotherParticlePz();

    float getMotherParticleMomentum();
    float getMotherParticlePt();
    float getMotherParticleEta();
    float getMotherParticleRapidity();

    float getPositiveParticleEta();
    float getNegativeParticleEta();

    float getRebuildMass();
};

#endif
