#include "MixEvents.h"
#include "TMath.h"
#include "TTree.h"
#include "Utils.h"

void MixEvents::init() {
    this->data_vec = new std::vector<double>();
    
    for (int i = 0; i < negative_particle_momentum_manager->getTotalEntries(); i++)
    {
        for (int j = 0; j < positive_particle_momentum_manager->getTotalEntries(); j++)
        {
            negative_particle_momentum_manager->setCurrentEntry(i);
            positive_particle_momentum_manager->setCurrentEntry(j);

            double px = negative_particle_momentum_manager->getPx() + positive_particle_momentum_manager->getPx();
            double py = negative_particle_momentum_manager->getPy() + positive_particle_momentum_manager->getPy();
            double pz = negative_particle_momentum_manager->getPz() + positive_particle_momentum_manager->getPz();

            double positive_energy = xqy::Utils::calculate_energy(
                positive_particle_momentum_manager->getPx(),
                positive_particle_momentum_manager->getPy(),
                positive_particle_momentum_manager->getPz(),
                inv_mass
            );
            double negative_energy = xqy::Utils::calculate_energy(
                negative_particle_momentum_manager->getPx(),
                negative_particle_momentum_manager->getPy(),
                negative_particle_momentum_manager->getPz(),
                inv_mass
            );
            double energy = positive_energy + negative_energy;
            // 重新计算质量
            rebuild_mass = TMath::Sqrt(
                energy * energy - (px * px + py * py + pz * pz)
            );
            this->data_vec->push_back(rebuild_mass);
        }
        
    }
}
