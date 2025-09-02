#include "DrawTGraphErrorHelper.h"

TGraphErrors *DrawTGraphErrorHelper::fillTGraphErrorFromManager(std::function<double()> get_x_func,
                                                                std::function<double()> get_y_func,
                                                                std::function<bool()> filter_function)
{
    for (Long64_t i = 0; i < this->manager->getTotalEntries(); i++)
    {
        this->manager->setCurrentEntry(i);

        if (!filter_function())
            continue;
        this->tgraph_error->SetPoint(this->valid_point, get_x_func(), get_y_func());
        this->valid_point++;
    }
    return this->tgraph_error;
}

void DrawTGraphErrorHelper::saveFile(const char *file_name)
{
    TFile *file = new TFile(file_name, "RECREATE");
    TCanvas *canvas = new TCanvas();
    this->draw_option(canvas);
    this->tgraph_error->Draw("PA");
    canvas->Write();
    file->Close();
}

void DrawTGraphErrorHelper::savePNG(const char *file_name)
{
    TCanvas *canvas = new TCanvas();
    this->draw_option(canvas);
    this->tgraph_error->Draw("PA");
    canvas->SaveAs(file_name);
    delete canvas;
}
