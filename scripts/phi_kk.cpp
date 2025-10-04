#include "DoubleParticleReconstructManager.h"
#include "BaseConverter2Root.h"

#define PHI_KK_SL "/home/huinaibing/git_repo/PA/DATA_FILES/PhiKK/phi_kk.out"
#define PHI_KK_ROOT "/home/huinaibing/git_repo/PA/DATA_FILES/PhiKK/phi_kk.root"

class PhiKK {
public:
    void Convert()
    {
        BaseConverter2Root::convert2rootfile(PHI_KK_SL, PHI_KK_ROOT, 321, -321);
    }

    void Run()
    {
        DoubleParticleReconstructManager manager(PHI_KK_ROOT, "phi", 0.493677, 0.493677);
        manager.classCheck();
    }

};
