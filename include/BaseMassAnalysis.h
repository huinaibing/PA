#include "BaseManager.h"
#include "TFile.h"
#include "TTree.h"

#ifndef __BASE_MASS_ANALYSIS__
#define __BASE_MASS_ANALYSIS__

class BaseMassAnalysis: public BaseManager
// 这个类继承自BaseManager，
// 处理对象为mass
// 只要你的root文件有上面这个东西，就可以用这个接口
{
public:
    BaseMassAnalysis(
        const char* file_path,
        const char* particle_name,
        const char* tree_name = "tree", const char* leaf_name = "mass")
    {
        this->particle_name = particle_name;
        this->root_file = TFile::Open(file_path);
        this->tree = (TTree *)this->root_file->Get(tree_name);
        this->tree->SetBranchAddress(leaf_name, &this->mass);
        this->total_entries = this->tree->GetEntries();
    }

    
    double getMass() const { return mass; }
    
    Long64_t getTotalEntries() override { return total_entries; }
    std::string getParticalName() override { return particle_name; }
    void setCurrentEntry(Long64_t entry) override {tree->GetEntry(entry);}
    
protected:
    std::string particle_name;
    TFile *root_file;
    TTree *tree;

    // 树的分支
    double mass;
    Long64_t total_entries;
};


#endif