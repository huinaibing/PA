#include "JpsiParticleAnalysis.h"
#include "BaseDrawGraph.h"
#include "ConstantDatas.h"
#include <iostream>
#include "TH1.h"
#include "TF1.h"
#include "TCanvas.h"
#include "TFile.h"
#include "TLegend.h"
#include "vector"
#include "Utils.h"
#define JPSI_FILE_PATH "/home/huinaibing/huinaibing/huinaibing/code/UPC_fig1/DATA_FILES/old/outputFile2.root"
#define JPSI_PARTICAL_NAME "Jpsi"
#define UPC_FIG1_FILE_PATH "/home/huinaibing/huinaibing/huinaibing/code/particalDecayAnalysis/DATA_FILES/upc_fig1_starlight.csv"

#define JPSI_FILE_PATH_5400 "/home/huinaibing/huinaibing/huinaibing/code/UPC_fig1/outputFile5400.root"

#include "PPbCollision8_16ProtonPositive.h"
#include "BaseCSVManager.h"

#define FIXED_JPSI_FILE_PATH "/home/huinaibing/huinaibing/huinaibing/code/UPC_fig1/outputFileFixed.root"

#define JPSI_FILE_PROTON_POSITIVE "/home/huinaibing/huinaibing/huinaibing/code/UPC_fig1/outputFileProtonPositive100000.root"
#define JPSI_FILE_60000 "/home/huinaibing/huinaibing/huinaibing/code/UPC_fig1/outputFileProtonPositive60000.root"

void jpsi_starlight_analysis()
{
    double cms_rapidity = xqy::Utils::calculate_center_of_mass_rapidity(
        6500, 6930, 2560, 2729);
    std::cout << "cms_rapidity: " << cms_rapidity << std::endl;

    JpsiParticleAnalysis manager(JPSI_FILE_60000, JPSI_PARTICAL_NAME, JPSI_PARTICAL_MASS, new PPbCollision8_16ProtonPositive());
    manager.classCheck();

    // 计算wgamma p
    BaseDrawGraph::drawFromManager(&manager, 1000, 1000, 2500, [&manager, cms_rapidity]()
                                   { return manager.getWGammaP(); }, "w_gamma_p", "outputProtonPositive");

    // 计算截面
    BaseDrawGraph::drawFromManager(&manager, 100, 0, 1000, [&manager]()
                                   { return manager.getCrossSection(); }, "cross_section", "outputProtonPositive");

    // 计算wgamma p和截面的关系
    TH2D *hist_w_gamma_p_cross_section = BaseDrawGraph::drawFromManagerTH2(&manager, 10, 1000, 2500, 1000, 0, 1000, [&manager]()
                                                                           { return manager.getWGammaP(); }, [&manager]()
                                                                           { return manager.getCrossSection(); }, "w_gamma_p_cross_section", "output_test");

    BaseCSVManager csv_manager(UPC_FIG1_FILE_PATH, "Jpsi_paper", 2);
    TH2D *hist = BaseDrawGraph::drawFromManagerTH2(&csv_manager, 100, 1000, 2500, 100, 0, 1000, [&csv_manager]()
                                                   { return csv_manager.getDataByColumn(0); }, [&csv_manager]()
                                                   { return csv_manager.getDataByColumn(1); }, "paper_w_gamma_p_cross_section");

    class GetErrorByHand
    {
    public:
        std::vector<double> errors;
        int idx = 0;
        GetErrorByHand()
        {
            this->errors = std::vector<double>(100, 0);
            this->errors[0] = 36.6185;
            this->errors[1] = 36.7205;
            this->errors[2] = 37.43;
            this->errors[3] = 42.86;
            this->errors[4] = 42.105;
            this->errors[5] = 44.0;
            this->errors[6] = 71.049;
            this->errors[7] = 105.686;
        }

        double get()
        {
            if (idx >= 8)
            {
                std::cout << "idx out of range" << std::endl;
                return 0;
            }
            return errors[idx++];
        }
    };

    GetErrorByHand* paper_error = new GetErrorByHand();

    TGraphErrors *hist_paper = BaseDrawGraph::turnTH2ToTGraphErrors(hist, "paper_w_gamma_p_cross_section", [paper_error](TH1 *projY)
                                                                    { return paper_error->get(); }, "output_paper_proton_positive");

    
    TGraphErrors *hist_my = BaseDrawGraph::turnTH2ToTGraphErrors(
        hist_w_gamma_p_cross_section, "my_w_gamma_p_cross_section",
        [](TH1 *projY)
        {
            std::cout << "entries" << projY->GetEntries() << std::endl;
            return TMath::Sqrt(
                (projY->GetRMS()) * (projY->GetRMS()) + (0.07 * projY->GetMean()) * (0.07 * projY->GetMean()) +  (0.15 * projY->GetMean()) * (0.15 * projY->GetMean()) / projY->GetEntries()
            );
        },
        "output_my_proton_positive");

    hist_paper->SetMarkerColor(kRed);
    hist_my->SetMarkerColor(kBlue);
    TF1 *fit_paper = new TF1("fit_paper", xqy::Utils::fit_w_gamma_p_and_cross_section, 1000, 2500, 3);
    fit_paper->SetLineColor(kRed);
    fit_paper->SetParameter(0, 26);
    fit_paper->SetParameter(1, 0.3);
    fit_paper->SetParameter(2, 0.1);
    hist_paper->Fit("fit_paper", "R");

    TF1 *fit_my = new TF1("fit_my", xqy::Utils::fit_w_gamma_p_and_cross_section, 1000, 2500, 3);
    fit_my->SetLineColor(kBlue);
    fit_my->SetParameter(0, 26);
    fit_my->SetParameter(1, 0.3);
    fit_my->SetParameter(2, 0.1);
    hist_my->Fit("fit_my", "R");

    TLegend *legend = new TLegend(0.1, 0.7, 0.3, 0.9);
    legend->AddEntry(hist_paper, "paper", "p");
    legend->AddEntry(hist_my, "my", "p");
    // 把两个图画在一起
    TCanvas *canvas = new TCanvas("canvas", "canvas", 800, 600);
    TFile *file = new TFile("output_compare_my_paper_proton_positive.root", "RECREATE");

    hist_my->Draw("P");
    hist_paper->Draw("P SAME");
    legend->Draw();
    canvas->Draw();
    canvas->Write();
    file->Close();
    delete file;
}
