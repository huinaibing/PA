#ifndef BASEDRAWGRAPH2_H
#define BASEDRAWGRAPH2_H

#include "BaseDrawGraph.h"
#include "BaseManager.h"
#include "TH1.h"
#include "TCanvas.h"
#include "TFile.h"

class BaseDrawGraph2 : public BaseDrawGraph
{
protected:
    BaseManager *manager;
    TH1 *hist = nullptr;
    std::function<void(TCanvas *)> draw_option;
    std::function<void(TH1 *)> hist_option;

public:
    BaseDrawGraph2(BaseManager *manager, TH1 *hist)
    {
        this->manager = manager;
        this->hist = hist;
        this->draw_option = [](TCanvas *canvas) {};
        this->hist_option = [](TH1 *hist) {};
    }

    virtual TH1 *fillHistFromManager(std::function<double()> get_data_func) { return nullptr; }

    virtual TH1 *fillHistFromManager(std::function<double()> get_x_func,
                                     std::function<double()> get_y_func) { return nullptr; }

    virtual TH1 *fillOneData(double data)
    {
        this->hist->Fill(data);
        return this->hist;
    }

    virtual TH1 *fillOneData(double x_data, double y_data)
    {
        this->hist->Fill(x_data, y_data);
        return this->hist;
    }

    void setDrawOption(std::function<void(TCanvas *)> draw_option)
    {
        this->draw_option = draw_option;
    }

    void setHistOption(std::function<void(TH1 *)> hist_option)
    {
        this->hist_option = hist_option;
    }

    void saveFile(const char *file_name)
    {
        TFile *file = new TFile(file_name, "RECREATE");
        TCanvas *canvas = new TCanvas();
        this->draw_option(canvas);
        this->hist_option(this->hist);
        this->hist->Draw();
        canvas->Write();
        file->Close();
    }

    void savePNG(const char *file_name)
    {
        TCanvas *canvas = new TCanvas();
        this->draw_option(canvas);
        this->hist_option(this->hist);
        this->hist->Draw();
        canvas->SaveAs(file_name);
        delete canvas;
    }

    TH1 *getHist()
    {
        return this->hist;
    }

    void setHist(TH1 *hist)
    {
        this->hist = hist;
    }
};

#endif // BASEDRAWGRAPH2_H
