#include "BaseManager.h"
#include "TFile.h"
#include "TTree.h"
#ifndef BASE_MOMENTUM_MANAGE_H
#define BASE_MOMENTUM_MANAGE_H
class BaseMomentumManage : public BaseManager {
public:
    BaseMomentumManage(
        const char* file_path, 
        const char* particle_name,
        const char* tree_name = "tree", 
        const char* leaf_name_x = "px",
        const char* leaf_name_y = "py",
        const char* leaf_name_z = "pz"
    )
    {
        this->particle_name = particle_name;

        this->root_file = TFile::Open(file_path);
        this->tree = (TTree *)this->root_file->Get(tree_name);
        
        this->tree->SetBranchAddress(leaf_name_x, &this->px);
        this->tree->SetBranchAddress(leaf_name_y, &this->py);
        this->tree->SetBranchAddress(leaf_name_z, &this->pz);
    
        this->total_entries = this->tree->GetEntries();
    }
    virtual ~BaseMomentumManage() = default;

    double getMomentum() const {return std::sqrt(px * px + py * py + pz * pz);}
    double getPt() const {return std::sqrt(px * px + py * py);}
    double getPx() const {return px;}
    double getPy() const {return py;}
    double getPz() const {return pz;}
    std::string getParticalName() override {return particle_name;}
    Long64_t getTotalEntries() override {return total_entries;}
    void setCurrentEntry(Long64_t entry) override {tree->GetEntry(entry);}

protected:
    std::string particle_name;
    std::string tree_name;
    TFile* root_file = nullptr;
    TTree* tree = nullptr;
    double px;
    double py;
    double pz;

    Long64_t total_entries = 0;
};

#endif // BASE_MOMENTUM_MANAGE_H
