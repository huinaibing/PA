#include "TCanvas.h"
#include "TH1.h"
#include "TF1.h"
#include "TLegend.h"
#include "Utils.h"
#include "BaseConverter2Root.h"
#include "UpcFig7JpsiPbP.h"
#include "DrawTH2DHelper.h"
#include "DrawTH1DHelper.h"

#define JPSI_SLIGHT_PB_P "/home/huinaibing/huinaibing/PA/DATA_FILES/slight_out/PbPslightjpsi.out"
#define JPSI_ROOT_PB_P "/home/huinaibing/huinaibing/PA/DATA_FILES/slight_out_root/PbPslightjpsi.root"

#define JPSI_SLIGHT_PBP_1_26 "/home/huinaibing/huinaibing/PA/DATA_FILES/slight_out/PbPslightjpsi1_26.out"
#define JPSI_ROOT_PBP_1_26 "/home/huinaibing/huinaibing/PA/DATA_FILES/slight_out_root/PbPslightjpsi1_26.root"

double func(double * x, double * par)
{
    return xqy::Utils::calculate_cross_section_supplement_power_law(x[0]);
}

void upc_fig_7()
{
    BaseConverter2Root::convert2rootfile(JPSI_SLIGHT_PB_P, JPSI_ROOT_PB_P);
    BaseConverter2Root::convert2rootfile(JPSI_SLIGHT_PBP_1_26, JPSI_ROOT_PBP_1_26);

    UpcFig7JpsiPbP jpsi(JPSI_ROOT_PB_P, "Jpsi", 3.096916);
    UpcFig7jpsiPbP1_26 jpsi126(JPSI_ROOT_PBP_1_26, "jpsi", 3.096916);
    TF1* starlight = new TF1("starlight", func, 4, 40);

    DrawTH2DHelper jpsi_cross_section_graph(&jpsi, new TH2D("jpsi_wgmp_cross_section_Pb_p", "J/psi", 40, 0, 40, 200, 0, 100));
    // DrawTH1DHelper wgmp_dis(&jpsi, new TH1D("jpsi_wgmp_dis", "j/psi", 100, 0, 100));

    // wgmp_dis.fillHistFromManager(
    //     [&jpsi](){return jpsi.getWGammaP();}
    // );
    // wgmp_dis.savePNG("UPCFIG7/wgmp_dis.png");
    jpsi_cross_section_graph.fillHistFromManager(
        [&jpsi]() {return jpsi.getWGammaP(); },
        [&jpsi]() { return jpsi.getCrossSection(); }
    );
    // jpsi_cross_section_graph.savePNG("UPCFIG7/TH2D.png");

    DrawTH2DHelper jpsi_cross_section_graph_126(&jpsi126, new TH2D("jpsi_wgmp_cross_section_Pb_p_126", "J/psi", 40, 0, 40, 200, 0, 100));
    DrawTH1DHelper wgmp_dis_126(&jpsi126, new TH1D("jpsi_wgmp_dis", "j/psi", 100, 0, 100));

    wgmp_dis_126.fillHistFromManager(
        [&jpsi126](){return jpsi126.getWGammaP();}
    );
    wgmp_dis_126.savePNG("UPCFIG7/wgmp_dis_126.png");
    jpsi_cross_section_graph_126.fillHistFromManager(
        [&jpsi126]() {return jpsi126.getWGammaP(); },
        [&jpsi126]() { return jpsi126.getCrossSection(); }
    );

    TGraphErrors* graph = BaseDrawGraph::turnTH2ToTGraphErrors((TH2*)jpsi_cross_section_graph.getHist(), "graph", [](TH1*){return 0.0;});
    TGraphErrors* graph126 = BaseDrawGraph::turnTH2ToTGraphErrors((TH2*)jpsi_cross_section_graph_126.getHist(), "graph126", [](TH1*){return 0.0;});
   
    TCanvas* canvas = new TCanvas("canvas", "Starlight Cross Section", 800, 600);
    starlight->SetTitle("Starlight Cross Section; W_{#gamma p} (GeV); Cross Section (mb)");
    starlight->SetLineColor(kRed);
    starlight->SetLineWidth(2);
    starlight->GetXaxis()->SetName("W_{#gamma p} (GeV)");
    starlight->GetYaxis()->SetName("Cross Section (mb)");
    starlight->Draw();
    graph->Draw("same P");
    graph126->SetMarkerColor(kBlue);
    graph126->Draw("same P");

    canvas->SetLogy();
    canvas->SetLogx();
    canvas->SetGrid();
    canvas->SaveAs("upc_fig_7.png");
}