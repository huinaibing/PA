#ifndef UPCFIG8PBPB_H
#define UPCFIG8PBPB_H

#include "BaseDoubleParticalChannelManager.h"
#include "PbPb536Config.h"
class UpcFig8PbPb : public BaseDoubleParticalChannelManager
{   
public:
    PbPb536Config *config = nullptr;
    UpcFig8PbPb(const char *file_path, const char *partical_name, float partical_mass)
        : BaseDoubleParticalChannelManager(file_path, partical_name, partical_mass)
    {
        this->config = new PbPb536Config();
    }
   
};




#endif // UPCFIG8PBPB_H


// Total cross section: 40.487 mb.

// >>> starlightStandalone::run(): Info: generating events:
//        0 of 370000
//     37000 of 370000
//     74000 of 370000
//     111000 of 370000
//     148000 of 370000
//     185000 of 370000
//     222000 of 370000
//     259000 of 370000
//     296000 of 370000
//     333000 of 370000
// >>> starlightStandalone::run(): Info: number of attempts = 15181677, number of accepted events = 370000
//  The cross section of the generated sample is 58.917 microbarn.
