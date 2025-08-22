/**
 * @mainpage particle analysis
 * @brief 你的main函数快堆成依托答辩了，写的什么玩意
 *
 * @section 用法：在scripts里面写主体分析代码，在这里调用，然后cmake
 */

#include "scripts/drawDsigmaDy.cpp"
#include "external/nlohmann/json.hpp"

#include "TGraphErrors.h"

#define JSON_FILE_PATH "/home/huinaibing/huinaibing/PA/collision_config/neutron_tagging.json"

#define NEUTRON_TAGGING_0n0n "/home/huinaibing/huinaibing/PA/DATA_FILES/pbpb536_coherent_neutron_tagging/PbPb536_0n0n.out"
#define NEUTRON_TAGGING_0n0n_ROOT "/home/huinaibing/huinaibing/PA/DATA_FILES/pbpb536_coherent_neutron_tagging_root/PbPb536_0n0n.root"

#define NEUTRON_TAGGING_0nxn "/home/huinaibing/huinaibing/PA/DATA_FILES/pbpb536_coherent_neutron_tagging/PbPb536_0nXn.out"
#define NEUTRON_TAGGING_0nxn_ROOT "/home/huinaibing/huinaibing/PA/DATA_FILES/pbpb536_coherent_neutron_tagging_root/PbPb536_0nXn.root"

#define NEUTRON_TAGGING_xnxn "/home/huinaibing/huinaibing/PA/DATA_FILES/pbpb536_coherent_neutron_tagging/PbPb536_XnXn.out"
#define NEUTRON_TAGGING_xnxn_ROOT "/home/huinaibing/huinaibing/PA/DATA_FILES/pbpb536_coherent_neutron_tagging_root/PbPb536_XnXn.root"

int main()
{
    nlohmann::json json_data;
    (std::ifstream(JSON_FILE_PATH)) >> json_data;

    TF1 *frame = new TF1(
        "frame",
        "0", 3, 6);

    frame->SetTitle("0n0n, 0nxn, xnxn comparation");

    TGraphErrors *graph_0n0n = drawDsigmaDy(
        NEUTRON_TAGGING_0n0n,
        NEUTRON_TAGGING_0n0n_ROOT,
        "0n0n",
        json_data["0n0n"]["total_sigma"].get<double>(),
        json_data["0n0n"]["attempts"].get<long long>());

    TGraphErrors *graph_0nxn = drawDsigmaDy(
        NEUTRON_TAGGING_0nxn,
        NEUTRON_TAGGING_0nxn_ROOT,
        "0nxn+xn0n",
        json_data["0nxn"]["total_sigma"].get<double>(),
        json_data["0nxn"]["attempts"].get<long long>());

    TGraphErrors *graph_xnxn = drawDsigmaDy(
        NEUTRON_TAGGING_xnxn,
        NEUTRON_TAGGING_xnxn_ROOT,
        "xnxn",
        json_data["xnxn"]["total_sigma"].get<double>(),
        json_data["xnxn"]["attempts"].get<long long>());

    TCanvas *canvas = new TCanvas(
        "canvas", "J/psi d#sigma/dy",
        1600, 1000);

    graph_0n0n->SetMarkerColor(kRed);
    graph_0nxn->SetMarkerColor(kBlue);
    graph_xnxn->SetMarkerColor(kBlack);

    graph_0n0n->SetMarkerStyle(24);
    graph_0nxn->SetMarkerStyle(8);
    graph_xnxn->SetMarkerStyle(27);
    
    frame->SetTitle(" J/psi d#sigma/dy; Rapidity; d#sigma/dy (mb) ");

    frame->Draw();
    graph_0n0n->Draw("P SAME");
    graph_0nxn->Draw("P SAME");
    graph_xnxn->Draw("P SAME");

    TLegend *legend = new TLegend(0.6, 0.7, 0.9, 0.9);
    legend->AddEntry(graph_0n0n, "0n0n * 0.42", "P");
    legend->AddEntry(graph_0nxn, "0nxn+xn0n * 0.42", "P");
    legend->AddEntry(graph_xnxn, "xnxn * 0.42", "P");
    legend->Draw("SAME");

    canvas->SetLogy();

    canvas->SaveAs("neutron_tagging_coherent/0n0n_0nxn_xnxn_comparation.png");

    return 0; // 写C++main函数不return 0的注定会度过一个失败的人生
}

// #include "scripts/JpsiProperty.cpp"
// #include "scripts/mixevent_muon.cpp"
// #include "scripts/remove_bkg.cpp"
// #include "scripts/muonAnalysis.cpp"

// #include "scripts/upcFig5.cpp"
// #include "TH1.h"
// #include "scripts/upcFig7.cpp"
// #include "scripts/UpcFig8.cpp"
// #include "scripts/compare_coherent_incoherent.cpp"
// #include "ConstantDatas.h"

// //-----------------------------------
// //
// // jpsi
// //
// // starlight原始文件路径jpsi
// #define COHERENT_JPSI_370_000 "/home/huinaibing/huinaibing/PA/DATA_FILES/slight_out/PbPb/PbPb536coherent_370_000.out"
// #define INCOHERENT_JPSI_320_000 "/home/huinaibing/huinaibing/PA/DATA_FILES/slight_out/PbPb/PbPb536incoherent_320_000.out"
// // 转化成root后路径jpsi
// #define COHERENT_JPSI_370_000_ROOT "/home/huinaibing/huinaibing/PA/DATA_FILES/slight_out_root/PbPb/PbPb536coherent_370_000.root"
// #define INCOHERENT_JPSI_320_000_ROOT "/home/huinaibing/huinaibing/PA/DATA_FILES/slight_out_root/PbPb/PbPb536incoherent_320_000.root"
// //====================================

// //-----------------------------------
// //
// // rho0
// //
// // origin
// #define COHERENT_RHO0_SL "/home/huinaibing/huinaibing/PA/DATA_FILES/slight_out/PbPb/rho0/PbPb536_rho0_coherent_140_000.out"
// #define INCOHERENT_RHO0_SL "/home/huinaibing/huinaibing/PA/DATA_FILES/slight_out/PbPb/rho0/PbPb536_rho0_incoherent_065_590.out"
// // root
// #define COHERENT_RHO0_RT "/home/huinaibing/huinaibing/PA/DATA_FILES/slight_out_root/PbPb/rho0/PbPb536_rho0_coherent_140_000.root"
// #define INCOHERENT_RHO0_RT "/home/huinaibing/huinaibing/PA/DATA_FILES/slight_out_root/PbPb/rho0/PbPb536_rho0_incoherent_065_590.root"
// //=====================================

// //-----------------------------------
// //
// // psi2s
// //
// // origin
// #define COHERENT_PSI2S_SL "/home/huinaibing/huinaibing/PA/DATA_FILES/slight_out/PbPb/psi2s/PbPb536_psi2s_coherent_7700.out"
// #define INCOHERENT_PSI2S_SL "/home/huinaibing/huinaibing/PA/DATA_FILES/slight_out/PbPb/psi2s/PbPb536_psi2s_incoherent_7000.out"
// // root
// #define COHERENT_PSI2S_RT "/home/huinaibing/huinaibing/PA/DATA_FILES/slight_out_root/PbPb/psi2s/PbPb536_psi2s_coherent_7700.root"
// #define INCOHERENT_PSI2S_RT "/home/huinaibing/huinaibing/PA/DATA_FILES/slight_out_root/PbPb/psi2s/PbPb536_psi2s_incoherent_7000.root"
// int main()
// {

//     // jpsi_property_analysis();
//     //  muon_analysis();
//     // mixevent_muon_analysis();
//     // remove_bkg();
//     // upc_fig5();
//     //  upc_fig_7();
//     // upc_fig_8();
//     compare_coherent_incoherent(COHERENT_JPSI_370_000, COHERENT_JPSI_370_000_ROOT,
//                                 INCOHERENT_JPSI_320_000, INCOHERENT_JPSI_320_000_ROOT,
//                                 false, "jpsi", 0);

//     compare_coherent_incoherent(COHERENT_RHO0_SL, COHERENT_RHO0_RT,
//                                 INCOHERENT_RHO0_SL, INCOHERENT_RHO0_RT,
//                                 false, "rho0", 0);

//     compare_coherent_incoherent(COHERENT_PSI2S_SL, COHERENT_PSI2S_RT,
//                                 INCOHERENT_PSI2S_SL, INCOHERENT_PSI2S_RT,
//                                 true, "psi2s", 0);

//     return 0;
// }
