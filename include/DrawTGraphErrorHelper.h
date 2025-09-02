#ifndef DRAWTGRAPHERRORHELPER_H
#define DRAWTGRAPHERRORHELPER_H

#include "BaseDrawGraph2.h"

class DrawTGraphErrorHelper : public BaseDrawGraph2
{
protected:
    TGraphErrors *tgraph_error;
    int valid_point = 0;

public:
    DrawTGraphErrorHelper(BaseManager *manager, TGraphErrors *tgraph_error) : BaseDrawGraph2(manager)
    {
        this->tgraph_error = tgraph_error;
    }

    void setTGraphError(TGraphErrors *tgraph_error)
    {
        this->tgraph_error = tgraph_error;
    }

    TGraphErrors *fillTGraphErrorFromManager(std::function<double()> get_x_func,
                                             std::function<double()> get_y_func,
                                             std::function<bool()> filter_function);

    TGraphErrors *fillTGraphErrorFromManager(std::function<double()> get_x_func,
                                             std::function<double()> get_y_func)
    {
        return this->fillTGraphErrorFromManager(get_x_func, get_y_func, []()
                                                { return true; });
    }

    void savePNG(const char *file_name) override;
    void saveFile(const char *file_name) override;

    TGraphErrors *getTGraphError()
    {
        return this->tgraph_error;
    }
};

#endif