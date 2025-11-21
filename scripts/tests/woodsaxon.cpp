/**
 * @file woodsaxon.cpp
 * @author xqy
 * @brief 第四次作业第一题 woodsaxon分布函数
 * @version 0.1
 * @date 2025-11-20
 *
 * @copyright Copyright (c) 2025
 *
 */

#include "Utils.h"
#include "TF1.h"

using namespace xqy;
using namespace std;

void woodsaxon()
{
    // 参数
    double r_au = 6.38, d_au = 0.535;
    double r_cu = 4.20641, d_cu = 0.5977;
    double r_pb = 6.62, d_pb = 0.546;

    // 令rho0 = 1
    double rho0 = 1.0;

    TCanvas *c1 = new TCanvas("c1", "Wood Saxon Distribution", 1600, 1000);
    TF1 *func_au = new TF1("wood_saxon_distribution_Au", [=](double *x, double *p)
                         { return Physics::wood_saxon(x[0], r_au, d_au, rho0); }, 0, 15, 0);

    TF1 *func_cu = new TF1("wood_saxon_distribution_Cu", [=](double *x, double *p)
                         { return Physics::wood_saxon(x[0], r_cu, d_cu, rho0); }, 0, 15, 0);

    TF1 *func_pb = new TF1("wood_saxon_distribution_Pb", [=](double *x, double *p)
                         { return Physics::wood_saxon(x[0], r_pb, d_pb, rho0); }, 0, 15, 0);

    func_au->SetLineColor(kRed);
    func_cu->SetLineColor(kGreen);
    func_pb->SetLineColor(kBlue);

    func_au->SetTitle("Wood Saxon Distribution; r (fm); #rho(r)");
    func_au->Draw();
    func_cu->Draw("SAME");
    func_pb->Draw("SAME");

    TLegend *leg = new TLegend(0.6, 0.7, 0.9, 0.9);
    leg->AddEntry(func_au, "Au");
    leg->AddEntry(func_cu, "Cu");
    leg->AddEntry(func_pb, "Pb");
    leg->Draw();

    c1->SaveAs("woodsaxon_distribution.png");
}