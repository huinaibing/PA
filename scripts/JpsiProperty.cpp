#include "BaseMassAnalysis.h"
#include "BaseMomentumManage.h"
#include "BaseDrawGraph.h"
#include "TCanvas.h"
#include "Utils.h"


#define JPSI_PATH "/home/huinaibing/huinaibing/PA/DATA_FILES/jpsi_mc/jpsi_info_milion.root"

void jpsi_property_analysis()
{
    BaseMassAnalysis jpsi_analysis(JPSI_PATH, "jpsi");
    BaseMomentumManage jpsi_momentum_analysis(JPSI_PATH, "jpsi");
    BaseDrawGraph::drawFromManager(
        &jpsi_analysis,
        300, 0, 5, 
        [&jpsi_analysis]()
        { 
            return jpsi_analysis.getMass(); 
        }, 
        [](TH1D *hist)
        {
            hist->SetXTitle("Jpsi Mass (GeV/c^2)");
            hist->SetYTitle("Counts"); 
        }, 
        [](TCanvas *canvas)
        {
            canvas->SetCanvasSize(1600, 1000);
        },
        "Jpsi Mass Distribution",
        1, "jpsi_property");

    BaseDrawGraph::drawFromManager(
        &jpsi_momentum_analysis,
        300, 0, 20, 
        [&jpsi_momentum_analysis]()
        { 
            return jpsi_momentum_analysis.getPt(); 
        }, 
        [](TH1D *hist)
        {
            hist->SetXTitle("Jpsi Transverse Momentum (GeV/c)");
            hist->SetYTitle("Counts"); 
        }, 
        [](TCanvas *canvas)
        {
            canvas->SetCanvasSize(1600, 1000);
        },
        "Jpsi Transverse Momentum Distribution",
        1, "jpsi_property");

    BaseDrawGraph::drawFromManager(
        &jpsi_momentum_analysis, 
        200, -10, 10,
        [&jpsi_momentum_analysis]()
        {
            return xqy::Utils::calculate_eta(jpsi_momentum_analysis.getPx(), 
                                             jpsi_momentum_analysis.getPy(), 
                                             jpsi_momentum_analysis.getPz());
        },
        [](TH1D* hist)
        {
            hist->SetXTitle("Jpsi Pseudorapidity (eta)");
            hist->SetYTitle("Counts");
        },
        [](TCanvas* canvas)
        {
            canvas->SetCanvasSize(1600, 1000);
        },
        "Jpsi Pseudorapidity Distribution",
        1, "jpsi_property");
}
