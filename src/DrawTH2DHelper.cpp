#include "DrawTH2DHelper.h"

TH1 *DrawTH2DHelper::fillHistFromManager(std::function<double()> get_x_func,
                                         std::function<double()> get_y_func,
                                         std::function<bool()> filter_function)
{
    for (Long64_t i = 0; i < this->manager->getTotalEntries(); i++)
    {
        this->manager->setCurrentEntry(i);
        if (!filter_function())
        {
            continue;
        }

        double x_data = get_x_func();
        double y_data = get_y_func();
        this->hist->Fill(x_data, y_data);
    }
    return this->hist;
}
