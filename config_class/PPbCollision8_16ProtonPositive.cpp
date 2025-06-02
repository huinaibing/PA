#include "PPbCollision8_16ProtonPositive.h"
#include "Utils.h"
PPbCollision8_16ProtonPositive::PPbCollision8_16ProtonPositive()
{
    this->proton_energy = 6500;
    this->collision_energy_1 = 6500;
    this->collision_gamma_1 = 6930;

    this->collision_energy_2 = 2560;
    this->collision_gamma_2 = 2729;
    this->cms_rapidity = xqy::Utils::calculate_center_of_mass_rapidity(collision_energy_1, collision_gamma_1, collision_energy_2, collision_gamma_2);
}

PPbCollision8_16ProtonPositive::~PPbCollision8_16ProtonPositive()
{
}
