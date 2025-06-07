#ifndef PBPB536CONFIG_H
#define PBPB536CONFIG_H
#include "BaseConfig.h"
class PbPb536Config: public BaseConfig
{
public:
    double gamma; // Lorentz factor
    double energy; // Energy in GeV
    double cms_rapidity = 0.0; // Center of mass rapidity
    PbPb536Config()
    {
        this->gamma = 2857.14;
        this->energy = 2680;
    }
};

#endif // PBPB536CONFIG_H