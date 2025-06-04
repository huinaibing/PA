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
    BaseManager* manager;
    TH1* hist = nullptr;
    std::function<void(TCanvas*)> draw_option;

public:
    BaseDrawGraph2(BaseManager* manager, TH1* hist) {
        this->manager = manager;
        this->hist = hist;
        this->draw_option = [](TCanvas* canvas) {
        };
    }

    TH1* fillHistFromManager(std::function<double()> get_data_func);
    
    void setDrawOption(std::function<void(TCanvas*)> draw_option)
    {
        this->draw_option = draw_option;
    }

    void saveFile(const char* file_name)
    {
        TFile* file = new TFile(file_name, "RECREATE");
        TCanvas* canvas = new TCanvas();
        this->draw_option(canvas);
        file->Close();
        delete file;
    }
    
    void savePNG(const char* file_name)
    {
        TCanvas* canvas = new TCanvas();
        this->draw_option(canvas);
        this->hist->Draw();
        canvas->SaveAs(file_name);
        delete canvas;
    }

    TH1* getHist() {
        return this->hist;
    }
};

#endif // BASEDRAWGRAPH2_H
