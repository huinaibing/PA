#ifndef UPCFIG7_H
#define UPCFIG7_H

#include "BaseDoubleParticalChannelManager.h"
#include "Utils.h"
#include "PPbCollision8_16Config.h"

class UpcFig7JpsiPbP : public BaseDoubleParticalChannelManager
{
public:
    UpcFig7JpsiPbP(const char *file_path, const char *partical_name, float partical_mass)
        : BaseDoubleParticalChannelManager(file_path, partical_name, partical_mass)
    {
        
        this->config = new PPbCollision8_16Config();
    }

    double getWGammaP()
    {
        return xqy::Utils::calculate_w_gamma_p(this->getRebuildMass(),
                                               this->config->proton_energy,
                                               this->getMotherParticleRapidity(), -1);
    }

    double getCrossSection()
    {
        return xqy::Utils::calculate_cross_section_supplement_power_law(this->getWGammaP());
    }

protected:
    PPbCollision8_16Config *config = nullptr;
};

#endif // UPCFIG7_H