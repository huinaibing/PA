#ifndef ALIROOTFOCALHCLUSTERMANAGER_H
#define ALIROOTFOCALHCLUSTERMANAGER_H

#include "BaseManager.h"
#include "TTree.h"
#include "Utils.h"

using namespace std;
using namespace xqy;

#define KCHAGED_MASS 0.493677 /* GEV */
#define FOCALH_Z 771.4

class AliRootFOCALHClusterManager : public BaseManager
{
protected:
    TTree *tree;
    TFile* file;
    double x1, y1, e1;
    double x2, y2, e2;
    Long64_t total_entries;
    float son_particle_mass;

public:
    std::string getParticalName() override
    {
        return "FOCALH cluster manager";
    }
    void setCurrentEntry(Long64_t entry) override
    {
        this->tree->GetEntry(entry);
    }
    Long64_t getTotalEntries() override
    {
        return this->total_entries;
    }
    AliRootFOCALHClusterManager(const char *file_name, float son_particle_mass);

    double getReconstructMass();

    double getEnergy1() { return this->e1; }
    double getEnergy2() { return this->e2; }
};

#endif