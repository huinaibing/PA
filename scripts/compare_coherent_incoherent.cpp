/**
 * @file compare_coherent_incoherent.cpp
 * @author Qiuyu Xia (qiu_yu@mails.ccnu.edu.cn)
 * @brief
 * @version 0.1
 * @date 2025-07-20
 *
 * @copyright Copyright (c) 2025
 *
 */

// // starlight原始文件路径
// #define COHERENT_JPSI_370_000 "/home/huinaibing/huinaibing/PA/DATA_FILES/slight_out/PbPb/PbPb536coherent_370_000.out"
// #define INCOHERENT_JPSI_320_000 "/home/huinaibing/huinaibing/PA/DATA_FILES/slight_out/PbPb/PbPb536incoherent_320_000.out"

// // 转化成root后路径
// #define COHERENT_JPSI_370_000_ROOT "/home/huinaibing/huinaibing/PA/DATA_FILES/slight_out_root/PbPb/PbPb536coherent_370_000.root"
// #define INCOHERENT_JPSI_320_000_ROOT "/home/huinaibing/huinaibing/PA/DATA_FILES/slight_out_root/PbPb/PbPb536incoherent_320_000.root"

#include <nlohmann/json.hpp>
#include "BaseConverter2Root.h"
#include "UpcFig8PbPb.h"
#include "ConstantDatas.h"
#include "DrawTH1DHelper.h"
#include "TCanvas.h"
#include <iostream>
#include "TLegend.h"
#include "TMath.h"
#include <string.h>

class PbPb536manager : public UpcFig8PbPb
{
    /**
     * @brief 这个是管理所有粒子的: rho0 jpsi psi2s(upsilon的截面太小了没必要,phi没法用starlight模拟)
     *
     */
public:
    PbPb536manager(const char *file_path, const char *particle_name, float particle_mass)
        : UpcFig8PbPb(file_path, particle_name, particle_mass)
    {
    }
};

/**
 * @brief 用于处理coherent和incoherent的代码，会计算eta，theta，phi，pT
 *
 * @param input_file_starlight_coherent starlight的原始输出文件
 * @param output_file_root_coherent 原始输出文件被转为root后的路径
 * @param input_file_starlight_incoherent
 * @param output_file_root_incoherent
 * @param need_convert 是否需要转化，True则会将原始输出文件转为root，只需要运行一次转化程序即可
 * @param particle_name
 * @param particle_mass
 */
void compare_coherent_incoherent(
    const char *input_file_starlight_coherent,
    const char *output_file_root_coherent,
    const char *input_file_starlight_incoherent,
    const char *output_file_root_incoherent,
    bool need_convert,
    const char *particle_name,
    double particle_mass)
{

    if (need_convert)
    {
        BaseConverter2Root::convert2rootfile(input_file_starlight_coherent, output_file_root_coherent);
        BaseConverter2Root::convert2rootfile(input_file_starlight_incoherent, output_file_root_incoherent);
    }

    PbPb536manager coherent(output_file_root_coherent,
                            xqy::Utils::concatenate_const_char("coherent_", particle_name),
                            particle_mass);
    PbPb536manager incoherent(output_file_root_incoherent,
                              xqy::Utils::concatenate_const_char("incoherent_", particle_name),
                              particle_mass);

    coherent.classCheck();
    incoherent.classCheck();

    DrawTH1DHelper *draw_mana_coherent = new DrawTH1DHelper(&coherent, nullptr);
    DrawTH1DHelper *draw_mana_incoherent = new DrawTH1DHelper(&incoherent, nullptr);

    draw_mana_coherent->setHist(
        new TH1D(
            xqy::Utils::concatenate_const_char("draw_mana_coherent_pt", particle_name),
            xqy::Utils::concatenate_const_char("coherent pT", particle_name),
            100, 0, 2));
    draw_mana_incoherent->setHist(
        new TH1D(
            xqy::Utils::concatenate_const_char("draw_mana_incoherent_pt", particle_name),
            xqy::Utils::concatenate_const_char("incoherent pT", particle_name),
            100, 0, 2));

    TCanvas *cvs_pt = new TCanvas("cvs_pt", "", 1600, 1000);
    draw_mana_coherent->fillHistFromManager(
        [&coherent]()
        {
            return coherent.getMotherParticlePt();
        });

    draw_mana_incoherent->fillHistFromManager(
        [&incoherent]()
        {
            return incoherent.getMotherParticlePt();
        });

    draw_mana_coherent->getHist()->SetLineColor(kBlue);
    draw_mana_incoherent->getHist()->SetLineColor(kRed);
    draw_mana_coherent->getHist()->SetStats(0);
    draw_mana_incoherent->getHist()->SetStats(0);

    draw_mana_coherent->getHist()->SetLineWidth(2);
    draw_mana_incoherent->getHist()->SetLineWidth(2);

    draw_mana_coherent->getHist()->SetTitle(
        xqy::Utils::concatenate_const_char("coherent/incoherent production pT comparation", particle_name));
    draw_mana_coherent->getHist()->SetXTitle("pT");

    draw_mana_coherent->getHist()->Draw();
    draw_mana_incoherent->getHist()->Draw("same");

    TLegend *leg_pt = new TLegend(0.6, 0.6, 0.8, 0.8);
    leg_pt->SetBorderSize(0);
    leg_pt->AddEntry(draw_mana_coherent->getHist(), "coherent");
    leg_pt->AddEntry(draw_mana_incoherent->getHist(), "incoherent");
    leg_pt->Draw("same");
    cvs_pt->SetLogy();
    cvs_pt->SaveAs(
        xqy::Utils::concatenate_const_char(
            "cmp_coherent_incoherent/",
            xqy::Utils::concatenate_const_char(particle_name, "_coherent_incoherent_compare_pt.png")));

    // -----------------------------------------------
    draw_mana_coherent->setHist(
        new TH1D(
            xqy::Utils::concatenate_const_char("draw_mana_coherent_eta", particle_name),
            xqy::Utils::concatenate_const_char("coherent #eta", particle_name),
            100, 3, 10));
    draw_mana_incoherent->setHist(
        new TH1D(
            xqy::Utils::concatenate_const_char("draw_mana_incoherent_eta", particle_name),
            xqy::Utils::concatenate_const_char("incoherent eta", particle_name),
            100, 3, 10));

    TCanvas *cvs_eta = new TCanvas("cvs_eta", "", 1600, 1000);
    draw_mana_coherent->fillHistFromManager(
        [&coherent]()
        {
            return coherent.getMotherParticleEta();
        });

    draw_mana_incoherent->fillHistFromManager(
        [&incoherent]()
        {
            return incoherent.getMotherParticleEta();
        });

    draw_mana_coherent->getHist()->SetLineColor(kBlue);
    draw_mana_incoherent->getHist()->SetLineColor(kRed);
    draw_mana_coherent->getHist()->SetStats(0);
    draw_mana_incoherent->getHist()->SetStats(0);

    draw_mana_coherent->getHist()->SetLineWidth(2);
    draw_mana_incoherent->getHist()->SetLineWidth(2);

    draw_mana_coherent->getHist()->SetTitle(
        xqy::Utils::concatenate_const_char("coherent/incoherent production #eta comparation", particle_name));
    draw_mana_coherent->getHist()->SetXTitle("#eta");

    draw_mana_coherent->getHist()->Draw();
    draw_mana_incoherent->getHist()->Draw("same");

    TLegend *leg_eta = new TLegend(0.2, 0.6, 0.4, 0.8);
    leg_eta->SetBorderSize(0);
    leg_eta->AddEntry(draw_mana_coherent->getHist(), "coherent");
    leg_eta->AddEntry(draw_mana_incoherent->getHist(), "incoherent");
    leg_eta->Draw("same");

    cvs_eta->SaveAs(
        xqy::Utils::concatenate_const_char(
            "cmp_coherent_incoherent/",
            xqy::Utils::concatenate_const_char(particle_name, "_coherent_incoherent_compare_eta.png")));

    // -----------------------------------------------
    draw_mana_coherent->setHist(
        new TH1D(
            xqy::Utils::concatenate_const_char("draw_mana_coherent_theta", particle_name),
            xqy::Utils::concatenate_const_char("coherent #theta", particle_name),
            100, 0, 0.03));
    draw_mana_incoherent->setHist(
        new TH1D(
            xqy::Utils::concatenate_const_char("draw_mana_incoherent_theta", particle_name),
            xqy::Utils::concatenate_const_char("incoherent theta", particle_name),
            100, 0, 0.03));

    TCanvas *cvs_theta = new TCanvas("cvs_theta", "", 1600, 1000);
    draw_mana_coherent->fillHistFromManager(
        [&coherent]()
        {
            return coherent.getMotherParticleTheta();
        });

    draw_mana_incoherent->fillHistFromManager(
        [&incoherent]()
        {
            return incoherent.getMotherParticleTheta();
        });

    draw_mana_coherent->getHist()->SetLineColor(kBlue);
    draw_mana_incoherent->getHist()->SetLineColor(kRed);
    draw_mana_coherent->getHist()->SetStats(0);
    draw_mana_incoherent->getHist()->SetStats(0);

    draw_mana_coherent->getHist()->SetLineWidth(2);
    draw_mana_incoherent->getHist()->SetLineWidth(2);

    draw_mana_coherent->getHist()->SetTitle(
        xqy::Utils::concatenate_const_char("coherent/incoherent production #theta comparation", particle_name));
    draw_mana_coherent->getHist()->SetXTitle("#theta");

    draw_mana_coherent->getHist()->Draw();
    draw_mana_incoherent->getHist()->Draw("same");

    TLegend *leg_theta = new TLegend(0.6, 0.6, 0.8, 0.8);
    leg_theta->SetBorderSize(0);
    leg_theta->AddEntry(draw_mana_coherent->getHist(), "coherent");
    leg_theta->AddEntry(draw_mana_incoherent->getHist(), "incoherent");
    leg_theta->Draw("same");
    cvs_theta->SetLogy();
    cvs_theta->SaveAs(
        xqy::Utils::concatenate_const_char(
            "cmp_coherent_incoherent/",
            xqy::Utils::concatenate_const_char(particle_name, "_coherent_incoherent_compare_theta.png")));

    // -----------------------------------------------
    draw_mana_coherent->setHist(
        new TH1D(
            xqy::Utils::concatenate_const_char("draw_mana_coherent_phi", particle_name),
            xqy::Utils::concatenate_const_char("coherent #phi", particle_name),
            100, -TMath::Pi() / 2, TMath::Pi() / 2));
    draw_mana_incoherent->setHist(
        new TH1D(
            xqy::Utils::concatenate_const_char("draw_mana_incoherent_phi", particle_name),
            xqy::Utils::concatenate_const_char("incoherent phi", particle_name),
            100, -TMath::Pi() / 2, TMath::Pi() / 2));

    TCanvas *cvs_phi = new TCanvas("cvs_phi", "", 1600, 1000);
    draw_mana_coherent->fillHistFromManager(
        [&coherent]()
        {
            return coherent.getMotherParticlePhi();
        });

    draw_mana_incoherent->fillHistFromManager(
        [&incoherent]()
        {
            return incoherent.getMotherParticlePhi();
        });

    draw_mana_coherent->getHist()->SetLineColor(kBlue);
    draw_mana_incoherent->getHist()->SetLineColor(kRed);
    draw_mana_coherent->getHist()->SetStats(0);
    draw_mana_incoherent->getHist()->SetStats(0);

    draw_mana_coherent->getHist()->SetLineWidth(2);
    draw_mana_incoherent->getHist()->SetLineWidth(2);

    draw_mana_coherent->getHist()->SetTitle(
        xqy::Utils::concatenate_const_char("coherent/incoherent production #phi comparation", particle_name));
    draw_mana_coherent->getHist()->SetXTitle("#phi");

    draw_mana_coherent->getHist()->Draw();
    draw_mana_incoherent->getHist()->Draw("same");

    TLegend *leg_phi = new TLegend(0.6, 0.3, 0.8, 0.5);
    leg_phi->SetBorderSize(0);
    leg_phi->AddEntry(draw_mana_coherent->getHist(), "coherent");
    leg_phi->AddEntry(draw_mana_incoherent->getHist(), "incoherent");
    leg_phi->Draw("same");
    cvs_phi->SetLogy();
    cvs_phi->SaveAs(
        xqy::Utils::concatenate_const_char(
            "cmp_coherent_incoherent/",
            xqy::Utils::concatenate_const_char(particle_name, "_coherent_incoherent_compare_phi.png")));
}