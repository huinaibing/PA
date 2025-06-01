#include "JpsiParticleAnalysis.h"
#include <iostream>

JpsiParticleAnalysis::JpsiParticleAnalysis(const char *file_path, const char *partical_name, float partical_mass, BasePpb8_16Config *config)
    : BaseDoubleParticalChannelManager(file_path, partical_name, partical_mass)
{
  this->config = config;
  std::cout << "config->proton_energy: " << this->config->proton_energy << std::endl;
  std::cout << "config->cms_rapidity: " << this->config->cms_rapidity << std::endl;
}

JpsiParticleAnalysis::~JpsiParticleAnalysis()
{
}

float JpsiParticleAnalysis::getWGammaP()
{
  return xqy::Utils::calculate_w_gamma_p(this->getRebuildMass(),
                                         this->config->proton_energy,
                                         this->getMotherParticleRapidity() - this->config->cms_rapidity,
                                         1);
}

float JpsiParticleAnalysis::getCrossSection()
{
  return xqy::Utils::calculate_cross_section_supplement_power_law(this->getWGammaP());
}
