#include "BaseDrawGraph.h"
#include "TSystem.h"
#include "BaseManager.h"
#include <iostream>
#include <functional>
#include "TFile.h"
#include "TCanvas.h"
#include "TH1.h"
#include "TH2.h"
#include "TGraphErrors.h"

BaseDrawGraph::BaseDrawGraph()
{
}

BaseDrawGraph::~BaseDrawGraph()
{
}

TH1D *BaseDrawGraph::drawFromManager(BaseManager *manager,
                                     int bin_num, float min, float max,
                                     std::function<float()> get_data_func,
                                     std::string graph_name,
                                     std::string output_dir)
// 这是画的TH1直方图
{

    TH1D *hist = new TH1D(
        (manager->getParticalName() + "_" + graph_name).c_str(),
        (manager->getParticalName() + " " + graph_name).c_str(),
        bin_num, min, max);

    for (Long64_t i = 0; i < manager->getTotalEntries(); i++)
    {
        manager->setCurrentEntry(i);
        float data = get_data_func();
        hist->Fill(data);
    }

    // Create output directory if it doesn't exist
    gSystem->mkdir(output_dir.c_str(), true);

    // Create and save to output file
    TFile *output_file = new TFile(
        (output_dir + "/" + manager->getParticalName() + "_" + graph_name + ".root").c_str(),
        "RECREATE");

    TCanvas *canvas = new TCanvas(
        (manager->getParticalName() + "_" + graph_name + "_canvas").c_str(),
        (manager->getParticalName() + " " + graph_name + " canvas").c_str(),
        800, 600);
    hist->Draw();
    canvas->Write();
    output_file->Close();
    delete output_file;

    return hist;
}

TH2D *BaseDrawGraph::drawFromManagerTH2(BaseManager *manager,
                                        int bin_num_x, float min_x, float max_x,
                                        int bin_num_y, float min_y, float max_y,
                                        std::function<float()> get_x_data_func,
                                        std::function<float()> get_y_data_func,
                                        std::string graph_name,
                                        std::string output_dir)
{
    TH2D *hist = new TH2D(
        (manager->getParticalName() + "_" + graph_name).c_str(),
        (manager->getParticalName() + " " + graph_name).c_str(),
        bin_num_x, min_x, max_x, bin_num_y, min_y, max_y);

    for (Long64_t i = 0; i < manager->getTotalEntries(); i++)
    {
        manager->setCurrentEntry(i);
        float x_data = get_x_data_func();
        float y_data = get_y_data_func();
        hist->Fill(x_data, y_data);
    }

    // Create output directory if it doesn't exist
    gSystem->mkdir(output_dir.c_str(), true);

    // Create and save to output file
    TFile *output_file = new TFile(
        (output_dir + "/" + manager->getParticalName() + "_" + graph_name + ".root").c_str(),
        "RECREATE");

    TCanvas *canvas = new TCanvas(
        (manager->getParticalName() + "_" + graph_name + "_canvas").c_str(),
        (manager->getParticalName() + " " + graph_name + " canvas").c_str(),
        800, 600);
    hist->Draw();
    canvas->Write();
    output_file->Close();
    delete output_file;
    return hist;
}

TH1D *BaseDrawGraph::drawFromManager(BaseManager *manager,
                                     int bin_num, float min, float max,
                                     std::function<float()> get_data_func,
                                     std::string graph_name)
// 这个和上面的函数类似，但是没有输出文件，只返回hist
{
    TH1D *hist = new TH1D(
        (manager->getParticalName() + "_" + graph_name).c_str(),
        (manager->getParticalName() + " " + graph_name).c_str(),
        bin_num, min, max);

    for (Long64_t i = 0; i < manager->getTotalEntries(); i++)
    {
        manager->setCurrentEntry(i);
        float data = get_data_func();
        hist->Fill(data);
    }
    return hist;
}

TH2D *BaseDrawGraph::drawFromManagerTH2(BaseManager *manager,
                                        int bin_num_x, float min_x, float max_x,
                                        int bin_num_y, float min_y, float max_y,
                                        std::function<float()> get_x_data_func,
                                        std::function<float()> get_y_data_func,
                                        std::string graph_name)
{
    TH2D *hist = new TH2D(
        (manager->getParticalName() + "_" + graph_name).c_str(),
        (manager->getParticalName() + " " + graph_name).c_str(),
        bin_num_x, min_x, max_x, bin_num_y, min_y, max_y);

    for (Long64_t i = 0; i < manager->getTotalEntries(); i++)
    {
        manager->setCurrentEntry(i);
        float x_data = get_x_data_func();
        float y_data = get_y_data_func();
        hist->Fill(x_data, y_data);
    }

    return hist;
}

TGraphErrors *BaseDrawGraph::turnTH2ToTGraphErrors(TH2 *hist, std::string graph_name, std::function<float(TH1 *)> get_error_func, std::string output_dir)
{
    // First count the number of valid points
    int valid_points = 0;
    for (int i = 1; i <= hist->GetNbinsX(); i++) {
        TH1D *projY = hist->ProjectionY("_py", i, i);
        if (projY->GetEntries() > 0) {
            valid_points++;
        }
    }
    
    TGraphErrors *graph = new TGraphErrors(valid_points);
    graph->SetTitle(graph_name.c_str());  // Set the title/name of the graph
    
    int point_index = 0;
    for (int i = 1; i <= hist->GetNbinsX(); i++)
    {
        TH1D *projY = hist->ProjectionY("_py", i, i);
        if (projY->GetEntries() == 0)
        {
            continue;
        }

        double x = hist->GetXaxis()->GetBinCenter(i);
        double y = projY->GetMean();
        double y_err = get_error_func(projY);

        graph->SetPoint(point_index, x, y);
        graph->SetPointError(point_index, 0, y_err);
        point_index++;
    }

    // Set marker properties after all points are added
    graph->SetMarkerSize(1.0);
    graph->SetMarkerStyle(20); // Add marker style for better visibility

    // Create output directory if it doesn't exist
    gSystem->mkdir(output_dir.c_str(), true);

    // Create and save to output file
    TFile *output_file = new TFile(
        (output_dir + "/" + graph_name + ".root").c_str(), "RECREATE");

    TCanvas *canvas = new TCanvas(
        (graph_name + "_canvas").c_str(),
        (graph_name + " canvas").c_str(),
        800, 600);
    graph->Draw("AP");
    canvas->Write();
    output_file->Close();
    delete output_file;
    return graph;
}

TGraphErrors *BaseDrawGraph::turnTH2ToTGraphErrors(TH2 *hist,
                                                   std::string graph_name,
                                                   std::function<float(TH1 *)> get_error_func)
// 不创建文件
{
    // First count the number of valid points
    int valid_points = 0;
    for (int i = 1; i <= hist->GetNbinsX(); i++) {
        TH1D *projY = hist->ProjectionY("_py", i, i);
        if (projY->GetEntries() > 0) {
            valid_points++;
        }
    }

    // Create graph with exact number of points needed
    TGraphErrors *graph = new TGraphErrors(valid_points);
    graph->SetTitle(graph_name.c_str());

    int point_index = 0;
    for (int i = 1; i <= hist->GetNbinsX(); i++)
    {
        TH1D *projY = hist->ProjectionY("_py", i, i);
        if (projY->GetEntries() == 0)
        {
            continue;
        }

        double x = hist->GetXaxis()->GetBinCenter(i);
        double y = projY->GetMean();
        double y_err = get_error_func(projY);

        graph->SetPoint(point_index, x, y);
        graph->SetPointError(point_index, 0, y_err);
        point_index++;
    }

    // Set marker properties after all points are added
    graph->SetMarkerSize(1.0);
    graph->SetMarkerStyle(20); // Add marker style for better visibility

    return graph;
}
