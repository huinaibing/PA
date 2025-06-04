#define MUON_FROM_JPSI "/home/huinaibing/huinaibing/PA/DATA_FILES/muon_jpsi/muonfromjpsi.root"

#include "BaseMassAnalysis.h"
#include "BaseMomentumManage.h"
#include "BaseDrawGraph.h"
#include "TCanvas.h"
#include "Utils.h"

void muon_analysis()
{
    BaseMomentumManage muon_analysis_sig_bkg_positive_muon(MUON_FROM_JPSI, "muon", "tree_positive", "positive_px", "positive_py", "positive_pz");
    BaseMomentumManage muon_analysis_sig_bkg_negative_muon(MUON_FROM_JPSI, "muon", "tree_negative", "negative_px", "negative_py", "negative_pz");


    BaseDrawGraph::drawFromManager(
        &muon_analysis_sig_bkg_positive_muon,
        100, 0, 30,
        [&muon_analysis_sig_bkg_positive_muon]()
        {
            return muon_analysis_sig_bkg_positive_muon.getPt();
        },
        [](TH1D *hist)
        {
            hist->SetXTitle("Anti Muon Transverse Momentum (signal + background) (GeV/c)");
            hist->SetYTitle("Counts");
        },
        [](TCanvas *canvas)
        {
            canvas->SetCanvasSize(1600, 1000);
        },
        "Anti Muon Transverse Momentum Distribution (signal + background)",
        1, "muon_analysis");

   
    BaseDrawGraph::drawFromManager(
        &muon_analysis_sig_bkg_positive_muon,
        200, -10, 10,
        [&muon_analysis_sig_bkg_positive_muon]()
        {
            return xqy::Utils::calculate_eta(muon_analysis_sig_bkg_positive_muon.getPx(),
                                             muon_analysis_sig_bkg_positive_muon.getPy(),
                                             muon_analysis_sig_bkg_positive_muon.getPz());
        },
        [](TH1D *hist)
        {
            hist->SetXTitle("Anti Muon Pseudorapidity (signal + background)");
            hist->SetYTitle("Counts");
        },
        [](TCanvas *canvas)
        {
            canvas->SetCanvasSize(1600, 1000);
        },
        "Anti Muon Pseudorapidity Distribution (signal + background)",
        1, "muon_analysis");

    BaseDrawGraph::drawFromManager(
        &muon_analysis_sig_bkg_negative_muon,
        100, 0, 30,
        [&muon_analysis_sig_bkg_negative_muon]()
        {
            return muon_analysis_sig_bkg_negative_muon.getPt();
        },
        [](TH1D *hist)
        {
            hist->SetXTitle("Muon Transverse Momentum (signal + background) (GeV/c)");
            hist->SetYTitle("Counts");
        },
        [](TCanvas *canvas)
        {
            canvas->SetCanvasSize(1600, 1000);
        },
        "Muon Transverse Momentum Distribution (signal + background)",
        1, "muon_analysis");
    BaseDrawGraph::drawFromManager(
        &muon_analysis_sig_bkg_negative_muon,
        200, -10, 10,
        [&muon_analysis_sig_bkg_negative_muon]()
        {
            return xqy::Utils::calculate_eta(muon_analysis_sig_bkg_negative_muon.getPx(),
                                             muon_analysis_sig_bkg_negative_muon.getPy(),
                                             muon_analysis_sig_bkg_negative_muon.getPz());
        },
        [](TH1D *hist)
        {
            hist->SetXTitle("Muon Pseudorapidity (signal + background)");
            hist->SetYTitle("Counts");
        },
        [](TCanvas *canvas)
        {
            canvas->SetCanvasSize(1600, 1000);
        },
        "Muon Pseudorapidity Distribution (signal + background)",
        1, "muon_analysis");
}
