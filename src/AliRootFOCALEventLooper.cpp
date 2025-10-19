#include "AliRootFOCALEventLooper.h"
#include "AliRootHitsFOCALManager.h"
#include "Utils.h"
#include <iostream>
#include "BaseDrawGraph.h"
#include "TH1.h"
#include <string>

using namespace std;
using namespace xqy;

void AliRootFOCALEventLooper::classCheck(int start_idx, int end_index)
{
    for (Long64_t i = start_idx; i < end_index; i++)
    {
        AliRootHitsFOCALManager* manager = new AliRootHitsFOCALManager(
            this->file_name,
            Utils::concatenate_const_char("Event", to_string(i).c_str()), 
            this->kMaxFOCAL
        );
        cout << "Event " << i << " has " << manager->getTotalEntries() << " entries." << endl;
        manager->classCheck();
        delete manager;
    }
}
