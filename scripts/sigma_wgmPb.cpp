#include "BaseCSVManager.h"
#include "Utils.h"
#include "DrawTGraphErrorHelper.h"

TGraphErrors *sigma_wgmPb(const char *csv_file_path,
                          const char *particle_name,
                          const char *save_file_name,
                          std::function<void(TGraphErrors *)> graph_option)
{
    BaseCSVManager *csv_manager = new BaseCSVManager(csv_file_path, particle_name, 10);

    DrawTGraphErrorHelper *sigma_wgmPb_TGraphErrors = new DrawTGraphErrorHelper(
        csv_manager,
        new TGraphErrors());

    sigma_wgmPb_TGraphErrors->fillTGraphErrorFromManager(
        [&csv_manager]()
        { return csv_manager->getDataByColumn(1); },
        [&csv_manager]()
        { return csv_manager->getDataByColumn(3); },
        [&csv_manager]()
        {
            return csv_manager->getDataByColumn(0) >= 3.4 && csv_manager->getDataByColumn(0) <= 5.8;
        });

    sigma_wgmPb_TGraphErrors->fillTGraphErrorFromManager(
        [&csv_manager]()
        { return csv_manager->getDataByColumn(5); },
        [&csv_manager]()
        { return csv_manager->getDataByColumn(7); },
        [&csv_manager]()
        {
            return csv_manager->getDataByColumn(0) >= 3.4 && csv_manager->getDataByColumn(0) <= 5.8;
        });

    sigma_wgmPb_TGraphErrors->setDrawOption([](TCanvas *cvs)
                                            {cvs->SetLogx(); cvs->SetLogy(); cvs->SetCanvasSize(1600, 1000); });
    sigma_wgmPb_TGraphErrors->getTGraphError()->SetMarkerStyle(20);
    sigma_wgmPb_TGraphErrors->getTGraphError()->GetXaxis()->SetTitle("W_{#gamma Pb} (GeV)");
    sigma_wgmPb_TGraphErrors->getTGraphError()->GetYaxis()->SetTitle("#sigma (#gamma Pb)");
    graph_option(sigma_wgmPb_TGraphErrors->getTGraphError());
    sigma_wgmPb_TGraphErrors->savePNG(save_file_name);

    return sigma_wgmPb_TGraphErrors->getTGraphError();
}

void sigma_wgmPb_main()
{
    TGraphErrors *coherent_jpsi_536 = sigma_wgmPb("/home/huinaibing/huinaibing/PA/DATA_FILES/csv_data/coherent_pbpb_536/jpsi/PbPb536_jpsi_coherent.txt",
                                                  "jpsi",
                                                  "neutron_tagging/PbPb536/PbPb536_coherent_jpsi_sigma_wgmPb.png",
                                                  [](TGraphErrors *graph)
                                                  { graph->SetTitle("coherent jpsi production at PbPb #sqrt{S_NN} = 5.36 TeV, 7nb^{-1}"); });

    TGraphErrors *incoherent_jpsi_536 = sigma_wgmPb("/home/huinaibing/huinaibing/PA/DATA_FILES/csv_data/incoherent_pbpb_536/jpsi/PbPb536_jpsi_incoherent.txt",
                                                    "jpsi",
                                                    "neutron_tagging/PbPb536/PbPb536_incoherent_jpsi_sigma_wgmPb.png",
                                                    [](TGraphErrors *graph)
                                                    { graph->SetTitle("incoherent jpsi production at PbPb #sqrt{S_NN} = 5.36 TeV, 7nb^{-1}"); });

    BaseCSVManager* paper_csv = new BaseCSVManager("/home/huinaibing/huinaibing/PA/DATA_FILES/csv_data/coherent_pbpb_536/jpsi/paper_data.csv", "jpsi", 2);
    DrawTGraphErrorHelper* paper_graph = new DrawTGraphErrorHelper(paper_csv, new TGraphErrors());

    TGraphErrors* paper_graph_filled = paper_graph->fillTGraphErrorFromManager(
        [&paper_csv](){return paper_csv->getDataByColumn(0);},
        [&paper_csv](){return paper_csv->getDataByColumn(1);}
    );

    paper_graph_filled->SetMarkerStyle(22);
    paper_graph_filled->SetMarkerSize(2);

    paper_graph_filled->SetTitle("paper");
    coherent_jpsi_536->SetTitle("coherent");
    coherent_jpsi_536->SetMarkerColor(kBlue);
    incoherent_jpsi_536->SetTitle("incoherent");
    incoherent_jpsi_536->SetMarkerColor(kRed);
    TH2D* frame = new TH2D("frame", "jpsi production at PbPb #sqrt{S_{NN}} = 5.36 TeV, 7nb^{-1}", 1000, 0, 3000, 100000, 0, 1);
    frame->SetXTitle("W_{#gamma Pb} (GeV)");
    frame->SetYTitle("#sigma(#gammaPb)");
    
    xqy::Utils::save_graphs_together(
        *(new std::vector<TH1 *>{}),
        *(new std::vector<TGraph *>{coherent_jpsi_536, incoherent_jpsi_536, paper_graph_filled}),
        frame,
        [](TCanvas *cvs)
        {cvs->SetCanvasSize(1600, 1000); cvs->SetLogx();cvs->SetLogy(); },
        [](TLegend *leg)
        {leg->SetX1(0.3);leg->SetY1(0.7);leg->SetX2(0.5);leg->SetY2(0.9); },
        "neutron_tagging/PbPb536/coherent_incoherent_compare_jpsi_sigma_wgmPb.png");
}
