#include "AliRootFOCALEventLooper.h"
#include "AliRootHitsFOCALManager.h"
#include "Utils.h"
#include <iostream>
#include "BaseDrawGraph.h"
#include "TH1.h"
#include <string>
#include <fstream>

using namespace std;
using namespace xqy;

void AliRootFOCALEventLooper::classCheck(int start_idx, int end_index)
{
    ofstream ofs;
    ofs.open("classcheck_energy_FOCAL.txt", ios::out);
    for (Long64_t i = start_idx; i < end_index; i++)
    {
        AliRootHitsFOCALManager* manager = new AliRootHitsFOCALManager(
            this->file_name,
            Utils::concatenate_const_char("Event", to_string(i).c_str()), 
            this->kMaxFOCAL
        );
        cout << "Event " << i << " has " << manager->getTotalEntries() << " entries." << endl;
        manager->classCheck();
        double total_energy = manager->getSumOfHitsEnergy();
        ofs << total_energy << endl;
        delete manager;
    }
    ofs.close();
}
