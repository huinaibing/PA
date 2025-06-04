#include "BaseDoubleParticalChannelManager.h"
#include "PPbCollision8_16ProtonPositive.h"
#include "Utils.h"

class UpcFig5JpsiAnd2S : public BaseDoubleParticalChannelManager
{
public:
    UpcFig5JpsiAnd2S(const char *file_path, const char *partical_name, float partical_mass)
        : BaseDoubleParticalChannelManager(file_path, partical_name, partical_mass)
    {
        this->classCheck();
        this->config = new PPbCollision8_16ProtonPositive();
    }

    double getWGammaP()
    {
        return xqy::Utils::calculate_w_gamma_p(this->getRebuildMass(),
                                               this->config->proton_energy,
                                               this->getMotherParticleRapidity());
    }

    double getCrossSection(float sigma_p, float epsilon, float VM_mass)
    {
        return xqy::Utils::calculate_cross_section_supplement_power_law(this->getWGammaP(), sigma_p, epsilon, VM_mass);
    }

protected:
    PPbCollision8_16ProtonPositive *config = nullptr;
};
