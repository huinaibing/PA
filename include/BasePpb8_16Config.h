#ifndef __BASE_PPB_8_16_CONFIG__
#define __BASE_PPB_8_16_CONFIG__

#include "BaseConfig.h"
class BasePpb8_16Config : public BaseConfig
{
public:
    double proton_energy;
    double cms_rapidity;
    double collision_energy_1;
    double collision_gamma_1;
    double collision_energy_2;
    double collision_gamma_2;
};

#endif
