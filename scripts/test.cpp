#include "DoubleParticleReconstructManager.h"
#include "BaseConverter2Root.h"

#define TEST_FILE "/home/huinaibing/git_repo/PA/DATA_FILES/slight_out/PbPb/PbPb536coherent_370_000.out"
#define TEST_FILE_root "/home/huinaibing/git_repo/PA/DATA_FILES/slight_out/PbPb/PbPb536coherent_370_000.root"

class Test
{
public:
    void Run()
    {
        BaseConverter2Root::convert2rootfile(TEST_FILE, TEST_FILE_root, -11, 11);
        DoubleParticleReconstructManager mgr(TEST_FILE_root, "jpsi", 0.000511, 0.000511,
                                             "events",
                                             "neg_px", "neg_py", "neg_pz",
                                             "pos_px", "pos_py", "pos_pz");
        mgr.classCheck();
    }
};