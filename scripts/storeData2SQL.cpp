/**
 * @file storeData2SQL.cpp
 * @author your name (you@domain.com)
 * @brief 处理5.52TeV的jpsi coherent的数据,画图
 * @details 将数据转换一下存入sql
 * @version 0.1
 * @date 2025-09-10
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include "AllInOne.h"
using namespace std;


#define JPSI_552_0n0n "/home/huinaibing/huinaibing/PA/DATA_FILES/slight_out/PbPb/pbpb552coherent/jpsi/jpsi_552_0n0n.out"
#define JPSI_552_0nxn "/home/huinaibing/huinaibing/PA/DATA_FILES/slight_out/PbPb/pbpb552coherent/jpsi/jpsi_552_0nxn.out"
#define JPSI_552_xnxn "/home/huinaibing/huinaibing/PA/DATA_FILES/slight_out/PbPb/pbpb552coherent/jpsi/jpsi_552_xnxn.out"

#define ROOT_JPSI_552_0n0n "/home/huinaibing/huinaibing/PA/DATA_FILES/slight_out_root/PbPb/pbpb552coherent/jpsi/jpsi_552_0n0n.root"
#define ROOT_JPSI_552_0nxn "/home/huinaibing/huinaibing/PA/DATA_FILES/slight_out_root/PbPb/pbpb552coherent/jpsi/jpsi_552_0nxn.root"
#define ROOT_JPSI_552_xnxn "/home/huinaibing/huinaibing/PA/DATA_FILES/slight_out_root/PbPb/pbpb552coherent/jpsi/jpsi_552_xnxn.root"

void insert_sql()
{
    BaseDoubleParticalChannelManager* jpsi_0n0n = new BaseDoubleParticalChannelManager(ROOT_JPSI_552_0n0n, "jpsi");
    BaseDoubleParticalChannelManager* jpsi_0nxn = new BaseDoubleParticalChannelManager(ROOT_JPSI_552_0nxn, "jpsi");
    BaseDoubleParticalChannelManager* jpsi_xnxn = new BaseDoubleParticalChannelManager(ROOT_JPSI_552_xnxn, "jpsi");
    
    TH1D* jpsi_0n0n_graph = BaseDrawGraph::drawFromManager(
        jpsi_0n0n,
        200,
        -9,
        9,
        [&jpsi_0n0n](){ return jpsi_0n0n->getMotherParticleRapidity(); },
        [](TH1D*){},
        [](TCanvas*){},
        "jpsi_0n0n_rapidity_distribution",
        2
    );

    TH1D* jpsi_0nxn_graph = BaseDrawGraph::drawFromManager(
        jpsi_0nxn,
        200,
        -9,
        9,
        [&jpsi_0nxn](){ return jpsi_0nxn->getMotherParticleRapidity(); },
        [](TH1D*){},
        [](TCanvas*){},
        "jpsi_0nxn_rapidity_distribution",
        2
    );

    TH1D* jpsi_xnxn_graph = BaseDrawGraph::drawFromManager(
        jpsi_xnxn,
        200,
        -9,
        9,
        [&jpsi_xnxn](){ return jpsi_xnxn->getMotherParticleRapidity(); },
        [](TH1D*){},
        [](TCanvas*){},
        "jpsi_xnxn_rapidity_distribution",
        2
    );
    
    DataBaseManager* db = new DataBaseManager();
    db->init("pbpb552jpsicoherent");
    

    for (int i = 1; i <= jpsi_0n0n_graph->GetNbinsX(); i++)
    {
        string sql = "insert into jpsi552_0n0n_cut_eta_y_bincontent(y, bincontent) "
                     "values("
                     + to_string(xqy::Utils::round_to_decimal(jpsi_0n0n_graph->GetBinCenter(i), 2)) +
                     ","
                     + to_string(jpsi_0n0n_graph->GetBinContent(i)) +
                     ");";
        
        db->simpleGetResultFromSQL(sql);
        // cout << sql << endl;
    }

    for (int i = 1; i <= jpsi_0nxn_graph->GetNbinsX(); i++)
    {
        string sql = "insert into jpsi552_0nxn_cut_eta_y_bincontent(y, bincontent) "
                     "values("
                     + to_string(xqy::Utils::round_to_decimal(jpsi_0nxn_graph->GetBinCenter(i), 2)) +
                     ","
                     + to_string(jpsi_0nxn_graph->GetBinContent(i)) +
                     ");";
        
        db->simpleGetResultFromSQL(sql);
        // cout << sql << endl;
    }

    for (int i = 1; i <= jpsi_xnxn_graph->GetNbinsX(); i++)
    {
        string sql = "insert into jpsi552_xnxn_cut_eta_y_bincontent(y, bincontent) "
                     "values("
                     + to_string(xqy::Utils::round_to_decimal(jpsi_xnxn_graph->GetBinCenter(i), 2)) +
                     ","
                     + to_string(jpsi_xnxn_graph->GetBinContent(i)) +
                     ");";
        
        db->simpleGetResultFromSQL(sql);
        // cout << sql << endl;
    }
}

void query_data_fill_graph()
{
    string sql = R"(select 
                        a.wgp1,
                        a.sigma2_gamA,
                        a.wgp2,
                        a.sigma1_gamA
                    FROM
                        jpsi552all a
                        INNER join 
                            jpsi552_0n0n_cut_eta_y_bincontent b on a.y = b.y
                        INNER JOIN
                            jpsi552_0nxn_cut_eta_y_bincontent c ON a.y = c.y
                        INNER join
                            jpsi552_xnxn_cut_eta_y_bincontent d on a.y = d.y
                    WHERE
                        (b.bincontent * 0.42 * 0.6) > 80
                        AND (c.bincontent * 0.42 * 0.6) > 80
                        and (d.bincontent * 0.42 * 0.6) > 80;
    )";
    BaseDataBaseReader* db_reader = new BaseDataBaseReader(sql, "pbpb552jpsicoherent");

    DrawTGraphErrorHelper *sigma_wgmPb_TGraphErrors = new DrawTGraphErrorHelper(
        db_reader,
        new TGraphErrors()
    );

    sigma_wgmPb_TGraphErrors->fillTGraphErrorFromManager(
        [&db_reader](){return db_reader->getDataByColumn(0);},
        [&db_reader](){return db_reader->getDataByColumn(1);}
    );


    TGraphErrors* res_graph = sigma_wgmPb_TGraphErrors->fillTGraphErrorFromManager(
        [&db_reader](){return db_reader->getDataByColumn(2);},
        [&db_reader](){return db_reader->getDataByColumn(3);}
    );


    res_graph->SetMarkerStyle(20);
    res_graph->SetMarkerSize(1);
    res_graph->SetTitle("coherent");
    res_graph->SetMarkerColor(kRed);

    TH2D *frame = new TH2D("frame", "jpsi production at PbPb #sqrt{S_{NN}} = 5.52 TeV, 33.6nb^{-1}", 1000, 0, 3000, 100000, 0, 1);
    frame->SetXTitle("W_{#gamma Pb} (GeV)");
    frame->SetYTitle("#sigma(#gammaPb)");

    xqy::Utils::save_graphs_together(
        *(new std::vector<TH1 *>{}),
        *(new std::vector<TGraph *>{res_graph}),
        frame,
        [](TCanvas *cvs)
        {cvs->SetCanvasSize(1600, 1000); cvs->SetLogx();cvs->SetLogy(); },
        [](TLegend *leg)
        {leg->SetX1(0.3);leg->SetY1(0.7);leg->SetX2(0.5);leg->SetY2(0.9); },
        "neutron_tagging/pbpb552_filted/552tev_jpsi_sigma_wgmPb_filted.png");
}

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
    db->init("pbpb552jpsicoherent");
    BaseCSVManager* jpsi = new BaseCSVManager(
        "/home/huinaibing/huinaibing/PA/DATA_FILES/csv_data/coherent_pbpb_552/jpsi/PbPb552_jpsi_coherent.csv",
        "jpsi",
        10
    );
    db->dataInsertor(jpsi, "jpsi552all");
}

void store_data2sql_main()
{
   query_data_fill_graph();
}
