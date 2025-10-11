#include "AliRootFOCALEventLooper.h"
#include "AliRootHitsFOCALManager.h"
#include "Utils.h"
#include <iostream>
#include <string>

using namespace std;
using namespace xqy;

void AliRootFOCALEventLooper::classCheck()
{
    for (Long64_t i = 0; i < this->total_events; i++)
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
