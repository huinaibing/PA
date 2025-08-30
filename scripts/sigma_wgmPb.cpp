#include "BaseCSVManager.h"
#include "DrawTH2DHelper.h"

void sigma_wgmPb(const char *csv_file_path, const char *particle_name)
{
    BaseCSVManager *csv_manager = new BaseCSVManager(csv_file_path, particle_name, 10);

    DrawTH2DHelper *sigma_wgmPb_TH2D = new DrawTH2DHelper(
        csv_manager,
        new TH2D("sigma_wgmpb", "#sigma (#gamma Pb)-W #gamma Pb",
                 100, 0, 3000,
                 200, 0, 1));

    sigma_wgmPb_TH2D->fillHistFromManager(
        [&csv_manager](){return csv_manager->getDataByColumn(1);},
        [&csv_manager](){return csv_manager->getDataByColumn(3);}
    );

    sigma_wgmPb_TH2D->fillHistFromManager(
        [&csv_manager](){return csv_manager->getDataByColumn(5);},
        [&csv_manager](){return csv_manager->getDataByColumn(7);}
    );

    sigma_wgmPb_TH2D->setDrawOption([](TCanvas* cvs){cvs->SetLogx();cvs->SetLogy();});
    sigma_wgmPb_TH2D->savePNG("PbPb536_coherent_jpsi_sigma_wgmPb.png");
}


void sigma_wgmPb_main()
{
    sigma_wgmPb("/home/huinaibing/huinaibing/PA/DATA_FILES/csv_data/coherent_pbpb_536/jpsi/PbPb536_jpsi_coherent.txt", "jpsi");
}