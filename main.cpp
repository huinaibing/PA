/**
 * @mainpage particle analysis
 *
 * @section 用法：在scripts里面写主体分析代码，在这里调用，然后cmake
 */

// #include "scripts/JpsiProperty.cpp"
// #include "scripts/mixevent_muon.cpp"
// #include "scripts/remove_bkg.cpp"
// #include "scripts/muonAnalysis.cpp"

// #include "scripts/upcFig5.cpp"
// #include "TH1.h"
// #include "scripts/upcFig7.cpp"
// #include "scripts/UpcFig8.cpp"
#include "scripts/compare_coherent_incoherent.cpp"
#include "ConstantDatas.h"

//-----------------------------------
//
// jpsi
//
// starlight原始文件路径jpsi
#define COHERENT_JPSI_370_000 "/home/huinaibing/huinaibing/PA/DATA_FILES/slight_out/PbPb/PbPb536coherent_370_000.out"
#define INCOHERENT_JPSI_320_000 "/home/huinaibing/huinaibing/PA/DATA_FILES/slight_out/PbPb/PbPb536incoherent_320_000.out"
// 转化成root后路径jpsi
#define COHERENT_JPSI_370_000_ROOT "/home/huinaibing/huinaibing/PA/DATA_FILES/slight_out_root/PbPb/PbPb536coherent_370_000.root"
#define INCOHERENT_JPSI_320_000_ROOT "/home/huinaibing/huinaibing/PA/DATA_FILES/slight_out_root/PbPb/PbPb536incoherent_320_000.root"
//====================================

//-----------------------------------
//
// rho0
//
// origin
#define COHERENT_RHO0_SL "/home/huinaibing/huinaibing/PA/DATA_FILES/slight_out/PbPb/rho0/PbPb536_rho0_coherent_140_000.out"
#define INCOHERENT_RHO0_SL "/home/huinaibing/huinaibing/PA/DATA_FILES/slight_out/PbPb/rho0/PbPb536_rho0_incoherent_065_590.out"
// root
#define COHERENT_RHO0_RT "/home/huinaibing/huinaibing/PA/DATA_FILES/slight_out_root/PbPb/rho0/PbPb536_rho0_coherent_140_000.root"
#define INCOHERENT_RHO0_RT "/home/huinaibing/huinaibing/PA/DATA_FILES/slight_out_root/PbPb/rho0/PbPb536_rho0_incoherent_065_590.root"
//=====================================

//-----------------------------------
//
// psi2s
//
// origin
#define COHERENT_PSI2S_SL "/home/huinaibing/huinaibing/PA/DATA_FILES/slight_out/PbPb/psi2s/PbPb536_psi2s_coherent_7700.out"
#define INCOHERENT_PSI2S_SL "/home/huinaibing/huinaibing/PA/DATA_FILES/slight_out/PbPb/psi2s/PbPb536_psi2s_incoherent_7000.out"
// root
#define COHERENT_PSI2S_RT "/home/huinaibing/huinaibing/PA/DATA_FILES/slight_out_root/PbPb/psi2s/PbPb536_psi2s_coherent_7700.root"
#define INCOHERENT_PSI2S_RT "/home/huinaibing/huinaibing/PA/DATA_FILES/slight_out_root/PbPb/psi2s/PbPb536_psi2s_incoherent_7000.root"
int main()
{

    // jpsi_property_analysis();
    //  muon_analysis();
    // mixevent_muon_analysis();
    // remove_bkg();
    // upc_fig5();
    //  upc_fig_7();
    // upc_fig_8();
    compare_coherent_incoherent(COHERENT_JPSI_370_000, COHERENT_JPSI_370_000_ROOT,
                                INCOHERENT_JPSI_320_000, INCOHERENT_JPSI_320_000_ROOT,
                                false, "jpsi", 0);

    compare_coherent_incoherent(COHERENT_RHO0_SL, COHERENT_RHO0_RT,
                                INCOHERENT_RHO0_SL, INCOHERENT_RHO0_RT,
                                false, "rho0", 0);

    compare_coherent_incoherent(COHERENT_PSI2S_SL, COHERENT_PSI2S_RT,
                                INCOHERENT_PSI2S_SL, INCOHERENT_PSI2S_RT,
                                true, "psi2s", 0);

    return 0;
}
