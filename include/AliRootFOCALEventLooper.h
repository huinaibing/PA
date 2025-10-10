#ifndef ALIROOTFOCALEVENTLOOPER_H
#define ALIROOTFOCALEVENTLOOPER_H

#include "Rtypes.h"

class AliRootFOCALEventLooper
{
protected:
    Long64_t total_events;
    const char *file_name;
    int kMaxFOCAL;

public:
    AliRootFOCALEventLooper(const char *file_name, Long64_t total_events, int kMaxFOCAL)
    {
        this->file_name = file_name;
        this->kMaxFOCAL = kMaxFOCAL;
        this->total_events = total_events;
    }

    void classCheck();
};

#endif