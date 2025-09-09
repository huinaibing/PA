#include "DataBaseManager.h"
#include "BaseCSVManager.h"
#include "BaseDataBaseReader.h"
#include "DrawTGraphErrorHelper.h"
#include "Utils.h"
#include "TLegend.h"
using namespace std;

class SigmaWgmPbDataManager : public DataBaseManager
{
public:
    void dataInsertor(BaseCSVManager* manager, string table_name)
    {
        for (Long64_t i = 0; i < manager->getTotalEntries(); i ++)
        {
            manager->setCurrentEntry(i);

            string sql = "INSERT INTO " + table_name + " ("
                 "y, wgp1, k_dn1_dk, sigma2_gamA, dsig1_dy, "
                 "wgp2, k_dn2_dk, sigma1_gamA, dsig2_dy, dsig_dy"
                 ") VALUES ("
                 + to_string(manager->getDataByColumn(0)) + ", "
                 + to_string(manager->getDataByColumn(1)) + ", "
                 + to_string(manager->getDataByColumn(2)) + ", "
                 + to_string(manager->getDataByColumn(3)) + ", "
                 + to_string(manager->getDataByColumn(4)) + ", "
                 + to_string(manager->getDataByColumn(5)) + ", "
                 + to_string(manager->getDataByColumn(6)) + ", "
                 + to_string(manager->getDataByColumn(7)) + ", "
                 + to_string(manager->getDataByColumn(8)) + ", "
                 + to_string(manager->getDataByColumn(9))
                 + ");";
            this->simpleGetResultFromSQL(sql);
        }

    }
};


void insert_data_all()
{
    SigmaWgmPbDataManager* db = new SigmaWgmPbDataManager();
    db->init("pbpb536jpsicoherent");
    BaseCSVManager* jpsi = new BaseCSVManager(
        "/home/huinaibing/huinaibing/PA/DATA_FILES/csv_data/coherent_pbpb_536/jpsi/PbPb536_jpsi_coherent.txt",
        "jpsi",
        10
    );
    db->dataInsertor(jpsi, "jpsi536all");
}

/**
 * @brief 往数据库插入数据，只能运行一次！！！！！！！！！！！
 * 
 */
void sigma_wgmpb_insert_data()
{
    SigmaWgmPbDataManager* db = new SigmaWgmPbDataManager();
    db->init("pbpb536jpsicoherent");

    BaseCSVManager* jpsi_0n0n = new BaseCSVManager(
        "/home/huinaibing/huinaibing/PA/DATA_FILES/csv_data/coherent_pbpb_536/jpsi_neutron_info/jpsi_0n0n.csv",
        "jpsi",
        10
    );

    BaseCSVManager* jpsi_0nxn = new BaseCSVManager(
        "/home/huinaibing/huinaibing/PA/DATA_FILES/csv_data/coherent_pbpb_536/jpsi_neutron_info/jpsi_0nxn.csv",
        "jpsi",
        10
    );

    BaseCSVManager* jpsi_xnxn = new BaseCSVManager(
        "/home/huinaibing/huinaibing/PA/DATA_FILES/csv_data/coherent_pbpb_536/jpsi_neutron_info/jpsi_xnxn.csv",
        "jpsi",
        10
    );

    db->dataInsertor(jpsi_0n0n, "jpsi5360n0n");
    db->dataInsertor(jpsi_0nxn, "jpsi5360nxn");
    db->dataInsertor(jpsi_xnxn, "jpsi536xnxn");

}

void query_data_fill_graph()
{
    string sql = R"(SELECT 
                        a.wgp1, 
                        a.sigma2_gamA 
                    FROM 
                        jpsi536all a
                    INNER JOIN jpsi5360n0n b ON a.id = b.id
                    INNER JOIN jpsi5360nxn c ON a.id = c.id
                    INNER JOIN jpsi536xnxn d ON a.id = d.id
                    WHERE  
                        (b.dsig1_dy * 0.09 * 7000000) > 80
                        AND (c.dsig1_dy * 0.09 * 7000000) > 80
                        AND (d.dsig1_dy * 0.09 * 7000000) > 80;
    )";
    BaseDataBaseReader* db_reader = new BaseDataBaseReader(sql, "pbpb536jpsicoherent");

    DrawTGraphErrorHelper *sigma_wgmPb_TGraphErrors = new DrawTGraphErrorHelper(
        db_reader,
        new TGraphErrors()
    );

    sigma_wgmPb_TGraphErrors->fillTGraphErrorFromManager(
        [&db_reader](){return db_reader->getDataByColumn(0);},
        [&db_reader](){return db_reader->getDataByColumn(1);}
    );

    string sql2 = R"(SELECT 
                        a.wgp2, 
                        a.sigma1_gamA 
                    FROM 
                        jpsi536all a
                    INNER JOIN jpsi5360n0n b ON a.id = b.id
                    INNER JOIN jpsi5360nxn c ON a.id = c.id
                    INNER JOIN jpsi536xnxn d ON a.id = d.id
                    WHERE  
                        (b.dsig2_dy * 0.09 * 7000000) > 80 
                        AND (c.dsig2_dy * 0.09 * 7000000) > 80
                        AND (d.dsig2_dy * 0.09 * 7000000) > 80;
    )";

    BaseDataBaseReader* db_reader2 = new BaseDataBaseReader(sql2, "pbpb536jpsicoherent");
    sigma_wgmPb_TGraphErrors->setManager(db_reader2);

    TGraphErrors* res_graph = sigma_wgmPb_TGraphErrors->fillTGraphErrorFromManager(
        [&db_reader2](){return db_reader2->getDataByColumn(0);},
        [&db_reader2](){return db_reader2->getDataByColumn(1);}
    );

    BaseCSVManager *paper_csv = new BaseCSVManager("/home/huinaibing/huinaibing/PA/DATA_FILES/csv_data/coherent_pbpb_536/jpsi/paper_data.csv", "jpsi", 2);
    DrawTGraphErrorHelper *paper_graph = new DrawTGraphErrorHelper(paper_csv, new TGraphErrors());

    TGraphErrors *res_paper_graph = paper_graph->fillTGraphErrorFromManager(
        [&paper_csv]()
        { return paper_csv->getDataByColumn(0); },
        [&paper_csv]()
        { return paper_csv->getDataByColumn(1); }
    );

    res_paper_graph->SetMarkerStyle(22);
    res_paper_graph->SetMarkerSize(2);
    res_paper_graph->SetTitle("paper");
    res_paper_graph->SetMarkerColor(kBlue);
    res_graph->SetMarkerStyle(22);
    res_graph->SetMarkerSize(2);
    res_graph->SetTitle("coherent");
    res_graph->SetMarkerColor(kRed);

    TH2D *frame = new TH2D("frame", "jpsi production at PbPb #sqrt{S_{NN}} = 5.36 TeV, 7nb^{-1}", 1000, 0, 3000, 100000, 0, 1);
    frame->SetXTitle("W_{#gamma Pb} (GeV)");
    frame->SetYTitle("#sigma(#gammaPb)");

    xqy::Utils::save_graphs_together(
        *(new std::vector<TH1 *>{}),
        *(new std::vector<TGraph *>{res_paper_graph, res_graph}),
        frame,
        [](TCanvas *cvs)
        {cvs->SetCanvasSize(1600, 1000); cvs->SetLogx();cvs->SetLogy(); },
        [](TLegend *leg)
        {leg->SetX1(0.3);leg->SetY1(0.7);leg->SetX2(0.5);leg->SetY2(0.9); },
        "neutron_tagging/pbpb536_filted/jpsi_sigma_wgmPb_filted_compare2paper.png");
}