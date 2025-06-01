#include "JpsiParticleAnalysis.h"
#include "BaseDrawGraph.h"
#include "ConstantDatas.h"
#include <iostream>
#include "TH1.h"
#include "TF1.h"
#include "TCanvas.h"
#include "TFile.h"
#include "TLegend.h"
#include "Utils.h"
#define JPSI_FILE_PATH "/home/huinaibing/huinaibing/huinaibing/code/UPC_fig1/DATA_FILES/old/outputFile2.root"
#define JPSI_PARTICAL_NAME "Jpsi"
#define UPC_FIG1_FILE_PATH "/home/huinaibing/huinaibing/huinaibing/code/particalDecayAnalysis/DATA_FILES/upc_fig1_starlight.csv"
#include "PPbCollision8_16Config.h"
#include "BaseCSVManager.h"


void changeDirection()
{
    double cms_rapidity = xqy::Utils::calculate_center_of_mass_rapidity(
        COLLISION_ENERGY_1, COLLISION_GAMMA_1, COLLISION_ENERGY_2, COLLISION_GAMMA_2);
    std::cout << "cms_rapidity: " << cms_rapidity << std::endl;
    // 计算wgamma p
    JpsiParticleAnalysis manager(JPSI_FILE_PATH, JPSI_PARTICAL_NAME, JPSI_PARTICAL_MASS, new PPbCollision8_16Config());
    manager.classCheck();
    
    // 计算wgamma p
    BaseDrawGraph::drawFromManager(&manager, 100, 0, 40, [&manager, cms_rapidity]()
                                   { return manager.getWGammaP(); }, "w_gamma_p", "changeDirection");
}
