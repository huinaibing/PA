#include "BaseDoubleParticalChannelManager.h"
#include "TFile.h"
#include "TH1.h"
#include "TSystem.h"
#include "BaseDrawGraph.h"
#include "ConstantDatas.h"
BaseDoubleParticalChannelManager::BaseDoubleParticalChannelManager(
    const char *file_path,
    const char *partical_name,
    float partical_mass)
{
    this->partical_name = partical_name;
    this->partical_mass = partical_mass;

    this->root_file = TFile::Open(file_path);
    this->tree = (TTree *)this->root_file->Get("events");
    this->tree->SetBranchAddress("e_px", &this->negative_px);
    this->tree->SetBranchAddress("e_py", &this->negative_py);
    this->tree->SetBranchAddress("e_pz", &this->negative_pz);

    this->tree->SetBranchAddress("p_px", &this->positive_px);
    this->tree->SetBranchAddress("p_py", &this->positive_py);
    this->tree->SetBranchAddress("p_pz", &this->positive_pz);
    this->total_entries = this->tree->GetEntries();
}

BaseDoubleParticalChannelManager::~BaseDoubleParticalChannelManager()
{
    this->root_file->Close();
}

void BaseDoubleParticalChannelManager::classCheck()
{
    // draw momentum
    BaseDrawGraph::drawFromManager(this, 100, 0, 1000, [this]()
                                   { return this->getMotherParticleMomentum(); }, "momentum", "classCheckOutput");
    // draw pt
    BaseDrawGraph::drawFromManager(this, 100, 0, 10, [this]()
                                   { return this->getMotherParticlePt(); }, "pt", "classCheckOutput");

    // draw mass
    BaseDrawGraph::drawFromManager(this, 100, 0, 10, [this]()
                                   { return this->getRebuildMass(); }, "mass", "classCheckOutput");
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

void BaseDoubleParticalChannelManager::setCurrentEntry(Long64_t entry)
{
    this->tree->GetEntry(entry);
}

std::string BaseDoubleParticalChannelManager::getParticalName()
{
    return this->partical_name;
}

Long64_t BaseDoubleParticalChannelManager::getTotalEntries()
{
    return this->total_entries;
}

float BaseDoubleParticalChannelManager::getTheoryMass()
{
    return this->partical_mass;
}

float BaseDoubleParticalChannelManager::getMotherParticlePx()
{
    return this->negative_px + this->positive_px;
}

float BaseDoubleParticalChannelManager::getMotherParticlePy()
{
    return this->negative_py + this->positive_py;
}

float BaseDoubleParticalChannelManager::getMotherParticlePz()
{
    return this->negative_pz + this->positive_pz;
}

float BaseDoubleParticalChannelManager::getMotherParticleMomentum()
{
    return xqy::Utils::calculate_momentum(this->getMotherParticlePx(), this->getMotherParticlePy(), this->getMotherParticlePz());
}

float BaseDoubleParticalChannelManager::getMotherParticlePt()
{
    return xqy::Utils::calculate_pt(this->getMotherParticlePx(), this->getMotherParticlePy());
}

float BaseDoubleParticalChannelManager::getMotherParticleEta()
{
    return xqy::Utils::calculate_eta(this->getMotherParticlePx(), this->getMotherParticlePy(), this->getMotherParticlePz());
}

float BaseDoubleParticalChannelManager::getMotherParticleRapidity()
{
    float energy = xqy::Utils::calculate_energy(this->getMotherParticlePx(), this->getMotherParticlePy(), this->getMotherParticlePz(), this->getTheoryMass());
    return xqy::Utils::calculate_rapidity(energy, this->getMotherParticlePz());
}

float BaseDoubleParticalChannelManager::getRebuildMass()
{
    float positive_particle_energy = xqy::Utils::calculate_energy(this->positive_px, this->positive_py, this->positive_pz, ELECTRON_PARTICAL_MASS);
    float negative_particle_energy = xqy::Utils::calculate_energy(this->negative_px, this->negative_py, this->negative_pz, ELECTRON_PARTICAL_MASS);
    float total_energy = positive_particle_energy + negative_particle_energy;

    return TMath::Sqrt(total_energy * total_energy - this->getMotherParticleMomentum() * this->getMotherParticleMomentum());
}

float BaseDoubleParticalChannelManager::getPositiveParticleEta()
{
    return xqy::Utils::calculate_eta(this->positive_px, this->positive_py, this->positive_pz);
}

float BaseDoubleParticalChannelManager::getNegativeParticleEta()
{
    return xqy::Utils::calculate_eta(this->negative_px, this->negative_py, this->negative_pz);
}
