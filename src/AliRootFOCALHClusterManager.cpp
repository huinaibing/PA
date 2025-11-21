#include "AliRootFOCALHClusterManager.h"
#include "TFile.h"

using namespace xqy;

AliRootFOCALHClusterManager::AliRootFOCALHClusterManager(const char *file_name, float son_particle_mass)
{
    this->file = TFile::Open(file_name);
    this->tree = (TTree *)this->file->Get("events");

    this->tree->SetBranchAddress("x1", &this->x1);
    this->tree->SetBranchAddress("y1", &this->y1);
    this->tree->SetBranchAddress("energy1", &this->e1);

    this->tree->SetBranchAddress("x2", &this->x2);
    this->tree->SetBranchAddress("y2", &this->y2);
    this->tree->SetBranchAddress("energy2", &this->e2);
    this->total_entries = this->tree->GetEntriesFast();
    this->son_particle_mass = son_particle_mass;
}

double AliRootFOCALHClusterManager::getReconstructMass()
{
    double cos_theta = Utils::vectorAngleCosine(x1, y1, FOCALH_Z,
                                                x2, y2, FOCALH_Z);

    double val =  sqrt(
        2 * son_particle_mass * son_particle_mass + 2 * e1 * e2 - 2 \
        * sqrt(e1 * e1 - son_particle_mass * son_particle_mass) \
        * sqrt(e2 * e2 - son_particle_mass * son_particle_mass) * cos_theta
    );

    if (std::isnan(val))
    {
        return 0.09;
    }
    return val;
}