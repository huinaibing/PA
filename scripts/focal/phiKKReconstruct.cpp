#include "AliRootFOCALEventLooper.h"
#include "AliRootHitsFOCALManager.h"
#include "Utils.h"
#include "TH1.h"
#include <iostream>

using namespace std;
using namespace xqy;

class PhiKKReconstruct : public AliRootFOCALEventLooper
{
protected:
    float K_MASS = 493.677; // MeV/c^2
public:
    using AliRootFOCALEventLooper::AliRootFOCALEventLooper; // Inherit constructor

    void reconstructQA() override
    {
        TH1F *hEnergy = new TH1F("hEnergy", "particle Energy Distribution", 1000, 900, 1200); // unit: MeV
        hEnergy->GetXaxis()->SetTitle("Reconstructed #phi Mass (MeV/c^{2})");
        hEnergy->GetYaxis()->SetTitle("Counts");
        for (Long64_t i = 0; i < this->total_events; i++)
        {
            cout << "calculating event " << i << endl;
            AliRootHitsFOCALManager *manager = new AliRootHitsFOCALManager(
                this->file_name,
                Utils::concatenate_const_char("Event", to_string(i).c_str()),
                this->kMaxFOCAL);

            // 假设粒子是K+或K-，计算每一个entry的总能量，重建母粒子
            float particle1_energy = 0.0;
            float particle2_energy = 0.0;

            manager->setCurrentEntry(0);
            for (Long64_t j = 0; j < manager->FOCAL_; j++)
            {
                particle1_energy += manager->FOCAL_fEnergy[j]; 
            }
            particle1_energy /= 1000.0; // MeV
            float particle1_momentum_sqrt = particle1_energy * particle1_energy - K_MASS * K_MASS;
            if (particle1_momentum_sqrt < 0)
            {
                delete manager;
                continue; // 说明能量不够，不能产生K介子
            }
            float particle1_momentum = sqrt(particle1_momentum_sqrt);

            manager->setCurrentEntry(1);
            for (Long64_t j = 0; j < manager->FOCAL_; j++)
            {
                particle2_energy += manager->FOCAL_fEnergy[j]; // MeV
            }
            particle2_energy /= 1000.0; // MeV
            float particle2_momentum_sqrt = particle2_energy * particle2_energy - K_MASS * K_MASS;
            if (particle2_momentum_sqrt < 0)
            {
                delete manager;
                continue; // 说明能量不够，不能产生K介子
            }
            float particle2_momentum = sqrt(particle2_momentum_sqrt);

            // 计算母粒子质量 忽略夹角（因为很小）
            float mother_mass = 2 * K_MASS * K_MASS + 2 * (particle1_energy * particle2_energy - particle1_momentum * particle2_momentum);
            mother_mass = sqrt(mother_mass);
            hEnergy->Fill(mother_mass);
            delete manager;
        }

        TCanvas *c1 = new TCanvas("c1", "c1", 800, 600);
        hEnergy->Draw();
        c1->SaveAs("phi_reconstructed_mass_0998.png");
    }
};