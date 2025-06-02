#define SIG_BKG_FILE "/home/huinaibing/huinaibing/PA/BUILD/mix_event/muon_from_jpsi.root"
#define BKG_FILE "/home/huinaibing/huinaibing/PA/BUILD/mix_event/muon_mixevent.root"

#include "BaseMassAnalysis.h"
#include "BaseDrawGraph.h"
#include "TH1.h"
#include <iostream>

void remove_bkg()
{
    BaseMassAnalysis *sig_bkg = new BaseMassAnalysis(SIG_BKG_FILE, "sig_bkg", "mix_tree", "rebuild_mass");
    BaseMassAnalysis *bkg = new BaseMassAnalysis(BKG_FILE, "bkg", "mix_tree", "rebuild_mass");

    TH1D* sig_bkg_pic = BaseDrawGraph::drawFromManager(
        sig_bkg, 100, 0, 50,
        [&]() { return sig_bkg->getMass(); },
        [&](TH1D *hist) {
            hist->SetTitle("Rebuild Mass of Muon from Jpsi");
            hist->GetXaxis()->SetTitle("Rebuild Mass (GeV/c^2)");
            hist->GetYaxis()->SetTitle("Counts");
            
        },
        [](TCanvas *canvas) {
            canvas->SetCanvasSize(1600, 1000);
        },
        "rebuild_mass_sig_bkg",
        2
    );
    
    TH1D* bkg_pic = BaseDrawGraph::drawFromManager(
        bkg, 100, 0, 50,
        [&]() { return bkg->getMass(); },
        [](TH1D *hist) {
            hist->SetTitle("Rebuild Mass of Muon from Jpsi");
            hist->GetXaxis()->SetTitle("Rebuild Mass (GeV/c^2)");
            hist->GetYaxis()->SetTitle("Counts");
        },
        [](TCanvas *canvas) {
            canvas->SetCanvasSize(1600, 1000);
        },
        "rebuild_mass_bkg",
        2
    );

    // 缩放
    int min = 5;
    int max = 50;
    double bin_width = sig_bkg_pic->GetBinWidth(1);
    double scale_factors;
    for (int i = min; i <= max; i ++)
    {
        int bin_id = i / bin_width;
        scale_factors += (sig_bkg_pic->GetBinContent(bin_id) / bkg_pic->GetBinContent(bin_id));
    }
    scale_factors /= (max - min + 1.0);
    std::cout << "Scale factors: " << scale_factors << std::endl;

    sig_bkg_pic->Add(bkg_pic, -scale_factors); // Subtract background from signal
    
    TCanvas *canvas = new TCanvas("canvas", "Rebuild Mass of Muon from Jpsi", 1600, 1000);
    sig_bkg_pic->Draw();
    canvas->SetGrid();
    canvas->SaveAs("remove_bkg.png");
}