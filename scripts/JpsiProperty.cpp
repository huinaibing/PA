#include "BaseMassAnalysis.h"
#include "BaseMomentumManage.h"
#include "BaseDrawGraph.h"
#include "TCanvas.h"

void jpsi_property_analysis()
{
    BaseMassAnalysis jpsi_analysis("../DATA_FILES/jpsi_mc/jpsi_info_milion.root", "jpsi");
    BaseMomentumManage jpsi_momentum_analysis("../DATA_FILES/jpsi_mc/jpsi_info_milion.root", "jpsi");
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
}
