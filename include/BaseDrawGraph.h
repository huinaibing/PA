/**
 * @file BaseDrawGraph.h
 * @author your name (you@domain.com)
 * @brief 一个大画图类，现在建议使用BaseDrawGraph2
 * @version 0.1
 * @date 2025-07-16
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#ifndef __BASE_DRAW_GRAPH__
#define __BASE_DRAW_GRAPH__
#include "TH1.h"
#include "TH2.h"
#include "BaseManager.h"
#include <functional>
#include <string>
#include "TGraphErrors.h"
#include "TCanvas.h"

class BaseDrawGraph
{
public:
    BaseDrawGraph();
    ~BaseDrawGraph();

    static TH1D *drawFromManager(BaseManager *manager,
                                 int bin_num, float min, float max,
                                 std::function<double()> get_data_func,
                                 std::function<void(TH1D *)> draw_option,
                                 std::function<void(TCanvas *)> canvas_option,
                                 std::string graph_name,
                                 int option = 0, std::string output_dir = "");

    // 以下函数出于代码复用性考虑，暂停使用
    // 我会重载这些函数，提供更具体的实现
    static TH1D *drawFromManager(BaseManager *manager,
                                 int bin_num, float min, float max,
                                 std::function<float()> get_data_func, std::string graph_name,
                                 std::string output_dir);

    static TH2D *drawFromManagerTH2(BaseManager *manager,
                                    int bin_num_x, float min_x, float max_x,
                                    int bin_num_y, float min_y, float max_y,
                                    std::function<float()> get_x_data_func,
                                    std::function<float()> get_y_data_func,
                                    std::string graph_name,
                                    std::string output_dir);

    static TH1D *drawFromManager(BaseManager *manager,
                                 int bin_num, float min, float max,
                                 std::function<float()> get_data_func, std::string graph_name);

    static TH2D *drawFromManagerTH2(BaseManager *manager,
                                    int bin_num_x, float min_x, float max_x,
                                    int bin_num_y, float min_y, float max_y,
                                    std::function<float()> get_x_data_func,
                                    std::function<float()> get_y_data_func,
                                    std::string graph_name);

    static TGraphErrors *turnTH2ToTGraphErrors(TH2 *hist,
                                               std::string graph_name,
                                               std::function<float(TH1 *)> get_error_func,
                                               std::string output_dir);

    static TGraphErrors *turnTH2ToTGraphErrors(TH2 *hist,
                                               std::string graph_name,
                                               std::function<float(TH1 *)> get_error_func);
};

#endif
