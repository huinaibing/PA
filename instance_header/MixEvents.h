#include "BaseManager.h"
#include "BaseMomentumManage.h"

#ifndef MIX_EVENTS_H
#define MIX_EVENTS_H
#include "TFile.h"
#include "TTree.h"
#include <vector>

class MixEvents : public BaseManager {
protected:
    BaseMomentumManage *negative_particle_momentum_manager;
    BaseMomentumManage *positive_particle_momentum_manager;
    std::string particle_name;
    double inv_mass = 0.0; // Default mass, can be set
    double rebuild_mass = 0.0; // Rebuilt mass after mixing
    std::vector<double> *data_vec = nullptr;
    void init();

public:
    MixEvents(const char* particle_name, double mass, BaseMomentumManage *negative_manager, BaseMomentumManage *positive_manager)
        : negative_particle_momentum_manager(negative_manager), positive_particle_momentum_manager(positive_manager), 
          inv_mass(mass) 
        {this->particle_name = particle_name; init();};

    std::string getParticalName() override {
        return particle_name;
    }
    Long64_t getTotalEntries() override {
        return negative_particle_momentum_manager->getTotalEntries() * 
               positive_particle_momentum_manager->getTotalEntries();
    }
    void setCurrentEntry(Long64_t entry) override {this->rebuild_mass = (*data_vec)[entry];};

    double getRebuildMass() const {
        return rebuild_mass;
    }

    void save(const char* name)
    {
        TFile *file = TFile::Open(name, "RECREATE");
        TTree *tree = new TTree("mix_tree", "Mix Events Tree");
        tree->Branch("rebuild_mass", &rebuild_mass, "rebuild_mass/D");

        for (Long64_t i = 0; i < getTotalEntries(); ++i) {
            setCurrentEntry(i);
            tree->Fill();
        }
        tree->Write();
        file->Close();
        delete file;
    }
};

#endif