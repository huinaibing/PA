#include <iostream>

#include "TFile.h"
#include "TProfile.h"
#include "TCanvas.h"
#include "TH1.h"
using namespace std;
void draw_corrolation_v2pt()
{
    TFile *file = TFile::Open("/home/huinaibing/Downloads/AnalysisResults3.root");

    TDirectory *dir = (TDirectory *)file->Get("pid-flow-pt-corr");

    TProfile *h_cov_v2pt_diffpt = (TProfile *)dir->Get("covV2Pt_diffpt"); // 对应代码块1
    TProfile *h_ptAve = (TProfile *)dir->Get("ptAve");
    TProfile *h_ptSquareAve = (TProfile *)dir->Get("ptSquareAve");
    TProfile *h_c22 = (TProfile *)dir->Get("c22");
    TProfile *h_c24 = (TProfile *)dir->Get("c24");

    TProfile *h_cov_v2pt = (TProfile *)dir->Get("covV2Pt"); // 对应代码块2

    /**
     * @brief 代码块1,直接是用cov(v2,pt) / (sqrt(var(pt)) * sqrt(var(v2)))计算rho(v2,pt)
     *
     */
    {
        TH1D *tmp = new TH1D("v2ptcorre", "v2ptcorre", 10, new double[11]{0, 5, 10, 20, 30, 40, 50, 60, 70, 80, 90});
        for (int i = 1; i <= h_cov_v2pt_diffpt->GetNbinsX(); ++i)
        {
            double cov = h_cov_v2pt_diffpt->GetBinContent(i);
            double sigma_cov = h_cov_v2pt_diffpt->GetBinError(i);

            double ptAve = h_ptAve->GetBinContent(i);
            double sigma_ptAve = h_ptAve->GetBinError(i);

            double ptSquareAve = h_ptSquareAve->GetBinContent(i);
            double sigma_ptSqureAve = h_ptSquareAve->GetBinError(i);

            double c22 = h_c22->GetBinContent(i);
            double sigma_c22 = h_c22->GetBinContent(i);

            double c24 = h_c24->GetBinContent(i);
            double sigma_c24 = h_c24->GetBinContent(i);

            double v2ptcorre = cov / sqrt(ptSquareAve - ptAve * ptAve) / sqrt(c24 - c22 * c22);

            double A = ptSquareAve - ptAve * ptAve;
            double B = c24 - c22 * c22;
            double sigma_A = sqrt(sigma_ptSqureAve * sigma_ptSqureAve + 4 * ptAve * ptAve * sigma_ptAve * sigma_ptAve);
            double sigma_B = sqrt(sigma_c24 * sigma_c24 + 4 * c22 * c22 * sigma_c22 * sigma_c22);

            double sigma_v2ptcorre = v2ptcorre * sqrt(sigma_cov * sigma_cov / cov / cov + sigma_A * sigma_A / 2 / A / 2 / A + sigma_B * sigma_B / 2 / 2 / B / B);

            tmp->SetBinContent(i, v2ptcorre);
            tmp->SetBinError(i, sigma_v2ptcorre);
        }

        TCanvas *c1 = new TCanvas("c1", "c1", 1800, 1000);
        tmp->Draw();
        tmp->GetXaxis()->SetTitle("cent %");
        tmp->GetYaxis()->SetTitle("#rho");
        tmp->SetTitle("");
        c1->SaveAs("v2ptcorre_from_diffpt_3.png");
    }

    /**
     * @brief 代码块2,使用<<v2pt>> - <pt> * <v2>去算，这个误差可能很大
     *
     */
    {
        TH1D *tmp = new TH1D("v2ptcorre_mean", "v2ptcorre_mean", 10, new double[11]{0, 5, 10, 20, 30, 40, 50, 60, 70, 80, 90});
        for (int i = 1; i <= h_cov_v2pt->GetNbinsX(); ++i)
        {
            // calculate value
            double cov_v2pt = h_cov_v2pt->GetBinContent(i);
            double c22 = h_c22->GetBinContent(i);
            double ptAve = h_ptAve->GetBinContent(i);
            double c24 = h_c24->GetBinContent(i);
            double ptSquareAve = h_ptSquareAve->GetBinContent(i);

            double sigma_cov_v2pt = h_cov_v2pt->GetBinError(i);
            double sigma_c22 = h_c22->GetBinError(i);
            double sigma_ptAve = h_ptAve->GetBinError(i);
            double sigma_c24 = h_c24->GetBinError(i);
            double sigma_ptSquareAve = h_ptSquareAve->GetBinError(i);

            double v2ptcorre = (cov_v2pt - ptAve * c22) / sqrt(ptSquareAve - ptAve * ptAve) / sqrt(c24 - c22 * c22);

            tmp->SetBinContent(i, v2ptcorre);
            // end calculate value

            // calculate error
            double partial_cov_v2pt = 1.0 / sqrt(ptSquareAve - ptAve * ptAve) / sqrt(c24 - c22 * c22);
            double partial_ptAve = (-c22) / sqrt(ptSquareAve - ptAve * ptAve) / sqrt(c24 - c22 * c22) + (cov_v2pt - ptAve * c22) * ptAve / (ptSquareAve - ptAve * ptAve) / sqrt(ptSquareAve - ptAve * ptAve) / sqrt(c24 - c22 * c22);
            double partial_c22 = (-ptAve) / sqrt(ptSquareAve - ptAve * ptAve) / sqrt(c24 - c22 * c22) + (cov_v2pt - ptAve * c22) * c22 / (c24 - c22 * c22) / sqrt(ptSquareAve - ptAve * ptAve) / sqrt(c24 - c22 * c22);
            double partial_ptSquareAve = -(cov_v2pt - ptAve * c22) / 2 / (ptSquareAve - ptAve * ptAve) / sqrt(ptSquareAve - ptAve * ptAve) / sqrt(c24 - c22 * c22);
            double partial_c24 = -(cov_v2pt - ptAve * c22) / 2 / (c24 - c22 * c22) / sqrt(ptSquareAve - ptAve * ptAve) / sqrt(c24 - c22 * c22);

            double sigma_v2ptcorre = sqrt(
                partial_cov_v2pt * partial_cov_v2pt * sigma_cov_v2pt * sigma_cov_v2pt +
                partial_ptAve * partial_ptAve * sigma_ptAve * sigma_ptAve +
                partial_c22 * partial_c22 * sigma_c22 * sigma_c22 +
                partial_ptSquareAve * partial_ptSquareAve * sigma_ptSquareAve * sigma_ptSquareAve +
                partial_c24 * partial_c24 * sigma_c24 * sigma_c24);
            tmp->SetBinError(i, sigma_v2ptcorre);

            // end calculate error
        }
        TCanvas *c2 = new TCanvas("c2", "c2", 1800, 1000);
        tmp->Draw();
        tmp->GetXaxis()->SetTitle("cent %");
        tmp->GetYaxis()->SetTitle("#rho");
        tmp->SetTitle("");
        c2->SaveAs("v2ptcorre_from_mean.png");
    }
}
