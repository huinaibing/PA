/**
 * @file drawDsigmaDy.cpp
 * @author Summer Autumn Rain
 * @brief 这是用UpcFig8那个文件改得，用于画d#sigma/dy，计划是画出d(0n0n)/dy、d(0nxn)/dy、d(xnxn)/dy ，
 *        目前只适用于jpsi，以后可能会扩展到其他粒子，但那是以后的事情
 * @version 0.1
 * @date 2025-08-22
 *
 * @copyright Copyright (c) 2025
 *
 */

#include "UpcFig8PbPb.h"
#include "BaseConverter2Root.h"
#include "DrawTH1DHelper.h"
#include "TGraphErrors.h"
#include "BaseCSVManager.h"
#include "TF1.h"
#include "TLegend.h"
#include "Utils.h"

using namespace xqy;

/**
 * @brief 说明已经在文件开头写了
 *
 * @param slight_out starlight原始文件
 * @param root_file_path root文件，由前面一个文件转化来的
 * @param graph_name 图像名字
 * @param total_cross_section 总的截面
 * @param total_events 总事例数
 * @param dir_path 文件夹的路径
 * @param gluon_shadowing 如果需要核胶子遮蔽效应的那个系数的话就是true，论文里面是0.42
 * @param need_convert 如果需要把原始文件转化为root文件，就是true，默认值为true
 */
TGraphErrors* drawDsigmaDy(
    const char *slight_out,
    const char *root_file_path,
    const char *graph_name,
    double total_cross_section,
    long long total_events,
    const char *dir_path = "neutron_tagging_coherent",
    bool gluon_shadowing = true,
    bool need_convert = true)
{
    if (need_convert)
    {
        BaseConverter2Root::convert2rootfile(slight_out, root_file_path);
    }

    UpcFig8PbPb jpsi = UpcFig8PbPb(root_file_path, "J/psi", 114514);

    DrawTH1DHelper rapidity_dis(&jpsi, new TH1D("jpsi_rapidity", "J/psi", 60, 0, 6));

    rapidity_dis.fillHistFromManager(
        [&jpsi]()
        { return jpsi.getMotherParticleRapidity(); });

    TH1D *rap_his = (TH1D *)rapidity_dis.getHist();

    int no_zero_points = xqy::Utils::get_no_zero_points(rap_his);

    TGraphErrors *graph = new TGraphErrors(no_zero_points);

    double sigma_total = total_cross_section; // mb, total cross section for PbPb at 5.36 TeV
    long long N_total_events = total_events;
    double bin_width = rap_his->GetBinWidth(1);
    int point_index = 0;

    for (int i = 1; i <= rap_his->GetNbinsX(); i++)
    {
        int bin_content = rap_his->GetBinContent(i);
        if (bin_content > 0)
        {
            double x = rap_his->GetBinCenter(i);
            double dsigmady = sigma_total * bin_content / N_total_events / bin_width; // d#sigma/dy

            if (gluon_shadowing)
            {
                dsigmady *= 0.42;
            }

            graph->SetPoint(point_index, x, dsigmady);
            point_index++;
        }
    }

    // 为了防止root报重名警告，这里都要concatenate一下
    // 我真是有先见之明，给concatenate写了个函数哈哈
    // tmd函数名字写这么长，你是不是有并
    // tmd函数名字写短了你又看不懂了，流汗了
    // 你tmd的写个concatenate多个字符串不行吗
    // tmd你自己跟自己吵架干什么？？？？？
    TCanvas *canvas = new TCanvas(
        Utils::concatenate_const_char("canvas ", graph_name),
        Utils::concatenate_const_char("J/psi d#sigma/dy ", graph_name),
        1600, 1000);
    TF1 *frame = new TF1(
        Utils::concatenate_const_char("frame", graph_name),
        "0", 0, 6);
    // canvas->SetLogy();
    frame->SetTitle(Utils::concatenate_const_char(graph_name, " J/psi d#sigma/dy; Rapidity; d#sigma/dy (mb) "));
    graph->SetMarkerStyle(20);
    frame->SetLineColor(kWhite);
    
    frame->Draw();
    graph->Draw("P SAME");
    TLegend *legend = new TLegend(0.6, 0.7, 0.9, 0.9);
    legend->AddEntry(graph, "J/psi d#sigma/dy", "P");

    legend->Draw("SAME");

    canvas->SaveAs(
        Utils::concatenate_const_char(*(new std::vector<const char *>{dir_path, "/", graph_name, "_dsigmady.png"})));
    rapidity_dis.savePNG(
        Utils::concatenate_const_char(*(new std::vector<const char *>{dir_path, "/", graph_name, "_rapidity_dis.png"})));

    return graph;
}
