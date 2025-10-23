#include "DoubleParticleReconstructManager.h"
#include "BaseConverter2Root.h"

#define PHI_KK_SL "/home/huinaibing/starlight/starlight_r313/build/rho_pipi.out"
#define PHI_KK_ROOT "/home/huinaibing/starlight/starlight_r313/build/rho_pipi.root"

class PhiKK {
public:
    void Convert()
    {
        BaseConverter2Root::convert2rootfile(PHI_KK_SL, PHI_KK_ROOT, 211, -211);
    }

    void Run()
    {
        DoubleParticleReconstructManager manager(PHI_KK_ROOT, "rho0", 0.13957, 0.13957);
        manager.classCheck();
    }

};
