#ifndef DRAWTTH2DHELPER_H
#define DRAWTTH2DHELPER_H

#include "BaseDrawGraph2.h"

class DrawTH2DHelper : public BaseDrawGraph2
{
public:
    DrawTH2DHelper(BaseManager *manager, TH2D *hist) : BaseDrawGraph2(manager, hist) {}

    TH1 *fillHistFromManager(std::function<double()> get_x_func,
                             std::function<double()> get_y_func) override
    {
        for (Long64_t i = 0; i < this->manager->getTotalEntries(); i++)
        {
            this->manager->setCurrentEntry(i);
            double x_data = get_x_func();
            double y_data = get_y_func();
            this->hist->Fill(x_data, y_data);
        }
        return this->hist;
    }

    TH1 *fillHistFromManager(std::function<double()> get_x_func,
                             std::function<double()> get_y_func,
                             std::function<bool()> filter_function) override;
};

#endif
