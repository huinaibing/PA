#ifndef DRAWTH1DHELPER_H
#define DRAWTH1DHELPER_H
#include "BaseDrawGraph2.h"

class DrawTH1DHelper : public BaseDrawGraph2
{
public:
    DrawTH1DHelper(BaseManager* manager, TH1* hist) : BaseDrawGraph2(manager, hist) {}


    TH1* fillHistFromManager(std::function<double()> get_data_func) override
    {
        for (Long64_t i = 0; i < this->manager->getTotalEntries(); i++)
        {
            this->manager->setCurrentEntry(i);
            double data = get_data_func();
            this->hist->Fill(data);
        }
        return this->hist;
    }

};

#endif // DRAWTH1DHELPER_H
