#include "DoubleParticleReconstructManager.h"
#include "Utils.h"
#include "TMath.h"
#include "BaseDrawGraph.h"
#include <iostream>

DoubleParticleReconstructManager::DoubleParticleReconstructManager(
    const char *file_path,
    const char *particle_name,
    double positive_mass,
    double negative_mass,

    const char* tree_name,
    const char* negative_px_branch,
    const char* negative_py_branch,
    const char* negative_pz_branch,
    const char* positive_px_branch,
    const char* positive_py_branch,
    const char* positive_pz_branch
)
{
    this->particle_name = particle_name;
    this->positive_mass = positive_mass;
    this->negative_mass = negative_mass;

    this->root_file = TFile::Open(file_path);
    this->tree = (TTree *)this->root_file->Get(tree_name);
    this->tree->SetBranchAddress(negative_px_branch, &this->negative_px);
    this->tree->SetBranchAddress(negative_py_branch, &this->negative_py);
    this->tree->SetBranchAddress(negative_pz_branch, &this->negative_pz);

    this->tree->SetBranchAddress(positive_px_branch, &this->positive_px);
    this->tree->SetBranchAddress(positive_py_branch, &this->positive_py);
    this->tree->SetBranchAddress(positive_pz_branch, &this->positive_pz);
    this->total_entries = this->tree->GetEntries();
}

double DoubleParticleReconstructManager::getMotherParticlePx()
{
    return this->negative_px + this->positive_px;
}

double DoubleParticleReconstructManager::getMotherParticlePy()
{
    return this->negative_py + this->positive_py;
}

double DoubleParticleReconstructManager::getMotherParticlePz()
{
    return this->negative_pz + this->positive_pz;
}

double DoubleParticleReconstructManager::getMotherParticleMomentum()
{
    return xqy::Utils::calculate_momentum(this->getMotherParticlePx(), this->getMotherParticlePy(), this->getMotherParticlePz());
}

double DoubleParticleReconstructManager::getMotherParticlePt()
{
    return xqy::Utils::calculate_pt(this->getMotherParticlePx(), this->getMotherParticlePy());
}

double DoubleParticleReconstructManager::getMotherParticleEta()
{
    return xqy::Utils::calculate_eta(this->getMotherParticlePx(), this->getMotherParticlePy(), this->getMotherParticlePz());
}

double DoubleParticleReconstructManager::getMotherParticleRapidity()
{
    double energy = xqy::Utils::calculate_energy(this->getMotherParticlePx(), this->getMotherParticlePy(), this->getMotherParticlePz(), this->getReconstructMass());
    return xqy::Utils::calculate_rapidity(energy, this->getMotherParticlePz());
}

double DoubleParticleReconstructManager::getReconstructMass()
{
    double positive_particle_energy = xqy::Utils::calculate_energy(this->positive_px, this->positive_py, this->positive_pz, this->positive_mass);
    double negative_particle_energy = xqy::Utils::calculate_energy(this->negative_px, this->negative_py, this->negative_pz, this->negative_mass);
    double total_energy = positive_particle_energy + negative_particle_energy;

    return TMath::Sqrt(total_energy * total_energy - this->getMotherParticleMomentum() * this->getMotherParticleMomentum());
}

double DoubleParticleReconstructManager::getPositiveParticleEta()
{
    return xqy::Utils::calculate_eta(this->positive_px, this->positive_py, this->positive_pz);
}

double DoubleParticleReconstructManager::getNegativeParticleEta()
{
    return xqy::Utils::calculate_eta(this->negative_px, this->negative_py, this->negative_pz);
}

double DoubleParticleReconstructManager::getMotherParticleTheta()
{
    return xqy::Utils::calculate_theta(this->getMotherParticlePx(), this->getMotherParticlePy(), this->getMotherParticlePz());
}

double DoubleParticleReconstructManager::getMotherParticlePhi()
{
    return xqy::Utils::calculate_phi(this->getMotherParticlePx(), this->getMotherParticlePy());
}


void DoubleParticleReconstructManager::classCheck()
{
    std::cout << "Class Check: DoubleParticleReconstructManager" << std::endl;
    std::cout << "Particle Name: " << this->particle_name << std::endl;
    std::cout << "Positive Mass: " << this->positive_mass << std::endl;
    std::cout << "Negative Mass: " << this->negative_mass << std::endl;
    std::cout << "Total Entries: " << this->total_entries << std::endl;

    BaseDrawGraph::drawFromManager(this, 240, 0, 10, [this]()
                                   { return TMath::Abs(this->getNegativeParticleEta() - this->getPositiveParticleEta()); }, "delta_eta", "classCheckOutput");

    // draw momentum
    BaseDrawGraph::drawFromManager(this, 100, 0, 1000, [this]()
                                   { return this->getMotherParticleMomentum(); }, "momentum", "classCheckOutput");
    // draw pt
    BaseDrawGraph::drawFromManager(this, 100, 0, 10, [this]()
                                   { return this->getMotherParticlePt(); }, "pt", "classCheckOutput");

    // draw mass
    BaseDrawGraph::drawFromManager(this, 100, 0, 10, [this]()
                                   { return this->getReconstructMass(); }, "mass", "classCheckOutput");
    // positive particle eta
    BaseDrawGraph::drawFromManager(this, 100, -10, 10, [this]()
                                   { return this->getPositiveParticleEta(); }, "positive_particle_eta", "classCheckOutput");
    // negative particle eta
    BaseDrawGraph::drawFromManager(this, 100, -10, 10, [this]()
                                   { return this->getNegativeParticleEta(); }, "negative_particle_eta", "classCheckOutput");

    // eta
    BaseDrawGraph::drawFromManager(this, 100, -10, 10, [this]()
                                   { return this->getMotherParticleEta(); }, "mother_particle_eta", "classCheckOutput");

    // rapidity
    BaseDrawGraph::drawFromManager(this, 100, -10, 10, [this]()
                                   { return this->getMotherParticleRapidity(); }, "mother_particle_rapidity", "classCheckOutput");
}
