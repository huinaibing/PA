#ifndef DOUBLEPARTICLERECONSTRUCTMANAGER_H
#define DOUBLEPARTICLERECONSTRUCTMANAGER_H
#include "BaseManager.h"
#include "TFile.h"
#include "TTree.h"
#include "TBranch.h"

class DoubleParticleReconstructManager : public BaseManager {
protected:
    std::string particle_name;
    TFile *root_file;
    TTree *tree;

    // 树的分支
    double negative_px;
    double negative_py;
    double negative_pz;

    double negative_mass;

    double positive_px;
    double positive_py;
    double positive_pz;

    double positive_mass;

    Long64_t total_entries;
public:
    DoubleParticleReconstructManager(
        const char *file_path,
        const char *particle_name,
        double positive_mass,
        double negative_mass,

        const char* tree_name = "events",
        const char* negative_px_branch = "neg_px",
        const char* negative_py_branch = "neg_py",
        const char* negative_pz_branch = "neg_pz",
        const char* positive_px_branch = "pos_px",
        const char* positive_py_branch = "pos_py",
        const char* positive_pz_branch = "pos_pz"
    );

    double getMotherParticlePx();
    double getMotherParticlePy();
    double getMotherParticlePz();

    double getMotherParticleMomentum();
    double getMotherParticlePt();
    double getMotherParticleEta();
    double getMotherParticleRapidity();

    double getPositiveParticleEta();
    double getNegativeParticleEta();

    double getMotherParticleTheta();
    double getMotherParticlePhi();
    double getReconstructMass();

    void setCurrentEntry(Long64_t entry) override {
        this->tree->GetEntry(entry);
    }
    Long64_t getTotalEntries() override {
        return this->total_entries;
    }
    std::string getParticalName() override {
        return this->particle_name;
    }

    void classCheck();
};

#endif