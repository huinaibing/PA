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
// #define JPSI_FILE_PATH "/home/huinaibing/huinaibing/huinaibing/code/UPC_fig1/DATA_FILES/old/outputFile2.root"
#define JPSI_PARTICAL_NAME "Jpsi"
// #define UPC_FIG1_FILE_PATH "/home/huinaibing/huinaibing/huinaibing/code/particalDecayAnalysis/DATA_FILES/upc_fig1_starlight.csv"
#include "PPbCollision8_16Config.h"
#include "BaseCSVManager.h"
#define TEST_FILE_PATH "/home/huinaibing/huinaibing/huinaibing/code/UPC_fig1/outputFileTest.root"
#define UPC_FIG1_FILE_PATH "/home/huinaibing/huinaibing/huinaibing/code/particalDecayAnalysis/DATA_FILES/upc_fig1_starlight.csv"

void test()
{
    double cms_rapidity = xqy::Utils::calculate_center_of_mass_rapidity(
        COLLISION_ENERGY_1, COLLISION_GAMMA_1, COLLISION_ENERGY_2, COLLISION_GAMMA_2);
    std::cout << "cms_rapidity: " << cms_rapidity << std::endl;

    BaseCSVManager csv_manager(UPC_FIG1_FILE_PATH, "Jpsi_paper", 2);
    TH2D *hist = BaseDrawGraph::drawFromManagerTH2(&csv_manager, 100, 1000, 4000, 100, 0, 1000, [&csv_manager]()
                                                   { return csv_manager.getDataByColumn(0); }, [&csv_manager]()
                                                   { return csv_manager.getDataByColumn(1); }, "paper_w_gamma_p_cross_section");

    TGraphErrors *hist_paper = BaseDrawGraph::turnTH2ToTGraphErrors(hist, "paper_w_gamma_p_cross_section",
                                                                    [](TH1 *projY)
                                                                    { return 0; });

    TF1* function = new TF1("function", "4.06 * TMath::Power(x, 0.65)", 1000, 2500);
    TCanvas *canvas = new TCanvas("canvas", "canvas", 800, 600);
    TFile *file = new TFile("114514.root", "RECREATE");
    hist_paper->Draw("AP");
    function->Draw("same");
    canvas->Write();
    file->Close();
}
