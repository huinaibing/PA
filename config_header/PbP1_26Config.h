#ifndef PBP1_26CONFIG_H
#define PBP1_26CONFIG_H

#include "BaseConfig.h"
#include "Utils.h"
class PbP1_26Config : public BaseConfig
{
public:
    PbP1_26Config()
    {   
        this->cms_rapidity = xqy::Utils::calculate_center_of_mass_rapidity(
            collision_energy_1, collision_gamma_1,
            collision_energy_2, collision_gamma_2);
    }
    double proton_energy = 1003.3; // Proton energy in GeV

    double collision_energy_1 = 395.5; // Collision energy in GeV
    double collision_gamma_1 = 421.7;

    double collision_energy_2 = 1003.3; // Collision energy in GeV
    double collision_gamma_2 = 1069.6;

    double cms_rapidity; // Center of mass rapidity, calculated later
};





#endif // PBP1_26CONFIG_H