#include "UpcFig8PbPb.h"
#include "BaseConverter2Root.h"
#include "DrawTH1DHelper.h"
#include "TGraphErrors.h"
#include "BaseCSVManager.h"
#include "TF1.h"

#define JPSI_SLIGHT_PBPB "/home/huinaibing/huinaibing/PA/DATA_FILES/slight_out/PbPb536slight.out"
#define JPSI_ROOT_PBPB "/home/huinaibing/huinaibing/PA/DATA_FILES/slight_out_root/PbPb536slight.root"
#define JPSI_PAPER_DATA "/home/huinaibing/huinaibing/PA/DATA_FILES/paper_data/UPCfig8data.csv"


void upc_fig_8()
{
    BaseConverter2Root::convert2rootfile(JPSI_SLIGHT_PBPB, JPSI_ROOT_PBPB);
    UpcFig8PbPb jpsi = UpcFig8PbPb(JPSI_ROOT_PBPB, "J/psi", 3.096916);

    DrawTH1DHelper rapidity_dis(&jpsi, new TH1D("jpsi_rapidity", "J/psi", 60, 0, 6));

    rapidity_dis.fillHistFromManager(
        [&jpsi]() { return jpsi.getMotherParticleRapidity(); }
    );

    TH1D* rap_his = (TH1D*)rapidity_dis.getHist();

    int no_zero_points = xqy::Utils::get_no_zero_points(rap_his);

    TGraphErrors* graph = new TGraphErrors(no_zero_points);

    double sigma_total = 39; // mb, total cross section for PbPb at 5.36 TeV
    int N_total_events = 15181677;
    double bin_width = rap_his->GetBinWidth(1);
    int point_index = 0;

    for (int i = 1; i <= rap_his->GetNbinsX(); i ++)
    {
        int bin_content = rap_his->GetBinContent(i);
        if (bin_content > 0)
        {
            double x = rap_his->GetBinCenter(i);
            double dsigmady = sigma_total * bin_content / N_total_events / bin_width; // d#sigma/dy
            dsigmady *= 0.42;
            graph->SetPoint(point_index, x, dsigmady);
            point_index++;
        }
    }

    BaseCSVManager paper_data = BaseCSVManager(
        JPSI_PAPER_DATA, "J/psi", 2
    );

    TGraphErrors* paper_graph = new TGraphErrors(paper_data.getTotalEntries());
    for (int i = 0; i < paper_data.getTotalEntries(); i ++)
    {
        paper_data.setCurrentEntry(i);
        paper_graph->SetPoint(
            i, 
            paper_data.getDataByColumn(0), // Rapidity
            paper_data.getDataByColumn(1)  // d#sigma/dy
        );
    }

    TCanvas* canvas = new TCanvas("canvas", "J/psi d#sigma/dy", 1600, 1000);
    TF1* frame = new TF1("frame", "0", 0, 6);
    //canvas->SetLogy();
    graph->SetTitle("J/psi d#sigma/dy; Rapidity; d#sigma/dy (mb)");
    graph->SetMarkerStyle(20);
    
    paper_graph->SetMarkerStyle(24);
    paper_graph->SetMarkerColor(kRed);
    paper_graph->Draw("PA");
    graph->Draw("P SAME");
    canvas->SaveAs("UPCFIG8/jpsi_rapidity.png");

    rapidity_dis.savePNG("UPCFIG8/rapidity_dis.png");

}