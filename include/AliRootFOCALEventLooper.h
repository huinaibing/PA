#ifndef ALIROOTFOCALEVENTLOOPER_H
#define ALIROOTFOCALEVENTLOOPER_H

#include "Rtypes.h"

class AliRootFOCALEventLooper
{
protected:
    Long64_t total_events;
    const char *file_name;

public:
    AliRootFOCALEventLooper(const char *file_name, Long64_t total_events)
    {
        this->file_name = file_name;
        this->total_events = total_events;
    }

    void classCheck();
};

#endif