#ifndef __BASE_DRAW_GRAPH__
#define __BASE_DRAW_GRAPH__
#include "TH1.h"
#include "TH2.h"
#include "BaseManager.h"
#include <functional>
#include <string>
#include "TGraphErrors.h"

class BaseDrawGraph
{
public:
    BaseDrawGraph();
    ~BaseDrawGraph();

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
