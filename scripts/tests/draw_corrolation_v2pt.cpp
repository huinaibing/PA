#include <iostream>

#include "TFile.h"
#include "TProfile.h"
#include "TCanvas.h"
#include "TH1.h"
using namespace std;
void draw_corrolation_v2pt()
{
    TFile *file = TFile::Open("/home/huinaibing/Downloads/AnalysisResults1.root");

    TDirectory *dir = (TDirectory *)file->Get("flow-gfw-omega-xi");

    TProfile *h_cov_v2pt = (TProfile *)dir->Get("covVnPt_diffpt");
    TProfile *h_ptAve = (TProfile *)dir->Get("ptAve");
    TProfile *h_ptSquareAve = (TProfile *)dir->Get("ptSquareAve");
    TProfile *h_c22 = (TProfile *)dir->Get("c22");
    TProfile *h_c24 = (TProfile *)dir->Get("c24");

    TH1D *tmp = new TH1D("v2ptcorre", "v2ptcorre", 10, new double[11]{0, 5, 10, 20, 30, 40, 50, 60, 70, 80, 90});
    for (int i = 1; i <= h_cov_v2pt->GetNbinsX(); ++i)
    {
        double cov = h_cov_v2pt->GetBinContent(i);
        double sigma_cov = h_cov_v2pt->GetBinError(i);

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

        cout << v2ptcorre << endl;

        tmp->SetBinContent(i, v2ptcorre);
        tmp->SetBinError(i, sigma_v2ptcorre);
    }

    TCanvas *c1 = new TCanvas("c1", "c1", 1800, 1000);
    tmp->Draw();
    tmp->GetXaxis()->SetTitle("cent %");
    tmp->GetYaxis()->SetTitle("#rho");
    tmp->SetTitle("");
    c1->SaveAs("v2ptcorre_from_diffpt.png");
}
