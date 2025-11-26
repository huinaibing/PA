#include "Utils.h"
#include "TF1.h"
#include <iostream>
using namespace xqy;
using namespace std;

void draw_bb_pi_k_p()
{
    double pi_z = 1, k_z = 1, p_z = 1;
    double pi_mass = 139.57; // MeV
    double k_mass = 493.67;  // MeV
    double p_mass = 938.27;  // MeV
    int material_z = 74;
    double material_a = 183.84;
    TF1 *piChargedBB = new TF1("piChargedBB", [=](double *x, double *p)
                               { return Physics::bethe_bloch(pi_z, material_z, material_a, x[0], pi_mass); }, 0, 10000, 0);
    TF1 *kChargedBB = new TF1("kChargedBB", [=](double *x, double *p)
                              { return Physics::bethe_bloch(k_z, material_z, material_a, x[0], k_mass); }, 0, 10000, 0);
    TF1 *protonBB = new TF1("protonBB", [=](double *x, double *p)
                            { return Physics::bethe_bloch(p_z, material_z, material_a, x[0], p_mass); }, 0, 10000, 0);
    TCanvas *c1 = new TCanvas("c1", "Bethe Bloch Formula", 1600, 1000);
    piChargedBB->SetLineColor(kRed);
    kChargedBB->SetLineColor(kGreen);
    protonBB->SetLineColor(kBlue);
    piChargedBB->SetTitle("Bethe Bloch Formula in Tungsten; momentum (MeV); < -dE/dx > (MeV/g/cm^{2})");
    piChargedBB->Draw();
    kChargedBB->Draw("SAME");
    protonBB->Draw("SAME");
    TLegend *leg = new TLegend(0.2, 0.7, 0.3, 0.9);
    leg->AddEntry(piChargedBB, "Pion");
    leg->AddEntry(kChargedBB, "Kaon");
    leg->AddEntry(protonBB, "Proton");
    leg->Draw();
    c1->SetLogx();
    c1->SaveAs("bethe_bloch_bb_pi_k_p.png");
}