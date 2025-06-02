#include "PPbCollision8_16Config.h"
#include "Utils.h"

PPbCollision8_16Config::PPbCollision8_16Config()
{
    this->proton_energy = 6500;
    this->collision_energy_1 = 2560;
    this->collision_gamma_1 = 2729;

    this->collision_energy_2 = 6500;
    this->collision_gamma_2 = 6930;
    
    this->cms_rapidity = xqy::Utils::calculate_center_of_mass_rapidity(collision_energy_1, collision_gamma_1, collision_energy_2, collision_gamma_2);
}

PPbCollision8_16Config::~PPbCollision8_16Config()
{
}
