#include "UpcFig5JpsiAnd2S.h"
#include "BaseConverter2Root.h"
#include "DrawTH1DHelper.h"
#include "DrawTH2DHelper.h"
#include "TProfile.h"
#include "TStyle.h"
#include "TGraphErrors.h"

#define JPSI_SLIGHT_PATH "/home/huinaibing/huinaibing/PA/DATA_FILES/slight_out/Jpsislight.out"
#define PSI2S_SLIGHT_PATH "/home/huinaibing/huinaibing/PA/DATA_FILES/slight_out/psi2Sslight.out"

#define JPSI_ROOT_PATH "/home/huinaibing/huinaibing/PA/DATA_FILES/slight_out_root/Jpsiroot.root"
#define PSI2S_ROOT_PATH "/home/huinaibing/huinaibing/PA/DATA_FILES/slight_out_root/Psi2Sroot.root"

void upc_fig5()
{
    // 下面这个转化运行一次就行
    // 跑完记得注释掉
    // BaseConverter2Root::convert2rootfile(JPSI_SLIGHT_PATH, JPSI_ROOT_PATH);
    // BaseConverter2Root::convert2rootfile(PSI2S_SLIGHT_PATH, PSI2S_ROOT_PATH);

    UpcFig5JpsiAnd2S jpsi(JPSI_ROOT_PATH, "Jpsi", 3.096916);
    UpcFig5JpsiAnd2S psi2s(PSI2S_ROOT_PATH, "Psi2S", 3.686109);

    DrawTH1DHelper jpsi_w_gamma_p_graph(&jpsi, new TH1D("jpsi_w_gamma_p", "J/psi W_{#gamma p}", 100, 0, 3000));
    DrawTH1DHelper psi2s_w_gamma_p_graph(&psi2s, new TH1D("psi2s_w_gamma_p", "Psi(2S) W_{#gamma p}", 100, 0, 3000));

    jpsi_w_gamma_p_graph.fillHistFromManager([&]() {
        return jpsi.getWGammaP();
    });
    psi2s_w_gamma_p_graph.fillHistFromManager([&]() {
        return psi2s.getWGammaP();
    });

    jpsi_w_gamma_p_graph.savePNG("wgmp_dis/jpsi_w_gamma_p_distribution.png");
    psi2s_w_gamma_p_graph.savePNG("wgmp_dis/psi2s_w_gamma_p_distribution.png");

    DrawTH2DHelper jpsi_cross_section_graph(&jpsi, new TH2D("jpsi_wgmp_cross_section", "J/psi", 10, 0, 3000, 1000, 0, 1000));
    DrawTH2DHelper psi2s_cross_section_graph(&psi2s, new TH2D("psi2s_wgmp_cross_section", "Psi(2S)", 10, 0, 3000, 1000, 0, 1000));

    jpsi_cross_section_graph.fillHistFromManager(
        [&]() { return jpsi.getWGammaP(); },
        [&]() { return jpsi.getCrossSection(4.06, 0.65, 3.096916); }
    );

    psi2s_cross_section_graph.fillHistFromManager(
        [&]() { return psi2s.getWGammaP(); },
        [&]() { return psi2s.getCrossSection(0.674, 0.65, 3.686109); }
    );

    jpsi_cross_section_graph.savePNG("wgmp_cross_section/jpsi_wgmp_cross_section.png");
    psi2s_cross_section_graph.savePNG("wgmp_cross_section/psi2s_wgmp_cross_section.png");

    int jpsi_valid_points = xqy::Utils::get_valid_points((TH2D*)jpsi_cross_section_graph.getHist());
    int psi2s_valid_points = xqy::Utils::get_valid_points((TH2D*)psi2s_cross_section_graph.getHist());

    std::cout << "valid point in jpsi TH2D:" << jpsi_valid_points << std::endl;
    std::cout << "valid point in psi2s TH2D:" << psi2s_valid_points<< std::endl;

    TGraphErrors* jpsi2psi2Sratio = new TGraphErrors(jpsi_valid_points < psi2s_valid_points ? jpsi_valid_points : psi2s_valid_points);

    TH2D* jpsiTH2D = (TH2D*)jpsi_cross_section_graph.getHist()->Clone("jpsiTH2D");
    TH2D* psi2sTH2D = (TH2D*)psi2s_cross_section_graph.getHist()->Clone("psi2sTH2D");

    int point_index = 0;
    for (int i = 1; i <= jpsi_cross_section_graph.getHist()->GetNbinsX(); i++)
    {
        TH1D* projY_jpsi = jpsiTH2D->ProjectionY("projY_jpsi", i, i);
        TH1D* projY_psi2s = psi2sTH2D->ProjectionY("projY_psi2s", i, i); 

        if (projY_jpsi->GetEntries() == 0 || projY_psi2s->GetEntries() == 0)
        {
            continue; // 跳过没有数据的点
        }
        double x = jpsiTH2D->GetXaxis()->GetBinCenter(i);
        double y = projY_psi2s->GetMean() / projY_jpsi->GetMean();

        jpsi2psi2Sratio->SetPoint(point_index, x, y);
        point_index++;
    }
    TCanvas* canvas = new TCanvas("canvas", "Psi(2S) Ratio to J/psi", 800, 600);
    jpsi2psi2Sratio->SetTitle("Psi(2S) to J/psi Ratio; W_{#gamma p} (GeV); Ratio");
    jpsi2psi2Sratio->SetMarkerStyle(20);
    jpsi2psi2Sratio->Draw("AP");
    canvas->SaveAs("wgmp_cross_section/psi2S_jpsi_ratio.png");
}
    