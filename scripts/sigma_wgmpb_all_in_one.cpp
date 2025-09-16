#include "AllInOne.h"

/**
 * @brief 
 * 
 * @param particle_name 
 * @param root_0n0n 
 * @param root_0nxn 
 * @param root_xnxn 
 * @param database_name 
 * @param table_name_0n0n 
 * @param table_name_0nxn 
 * @param table_name_xnxn 
 */
void insert_sql_y_bincontent(
    const char* particle_name, 
    const char* root_0n0n, 
    const char* root_0nxn, 
    const char* root_xnxn,
    const char* database_name,
    const char* table_name_0n0n,
    const char* table_name_0nxn,
    const char* table_name_xnxn
)
{
    BaseDoubleParticalChannelManager* jpsi_0n0n = new BaseDoubleParticalChannelManager(root_0n0n, particle_name);
    BaseDoubleParticalChannelManager* jpsi_0nxn = new BaseDoubleParticalChannelManager(root_0nxn, particle_name);
    BaseDoubleParticalChannelManager* jpsi_xnxn = new BaseDoubleParticalChannelManager(root_xnxn, particle_name);
    
    TH1D* jpsi_0n0n_graph = BaseDrawGraph::drawFromManager(
        jpsi_0n0n,
        200,
        -9,
        9,
        [&jpsi_0n0n](){ return jpsi_0n0n->getMotherParticleRapidity(); },
        [](TH1D*){},
        [](TCanvas*){},
        "0n0n_rapidity_distribution",
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
        "0nxn_rapidity_distribution",
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
        "xnxn_rapidity_distribution",
        2
    );
    
    DataBaseManager* db = new DataBaseManager();
    db->init(database_name);

    // 0n0n
    for (int i = 1; i <= jpsi_0n0n_graph->GetNbinsX(); i++)
    {
        string sql = "insert into "
                     + string(table_name_0n0n) +
                     "(y, bincontent) "
                     "values("
                     + to_string(xqy::Utils::round_to_decimal(jpsi_0n0n_graph->GetBinCenter(i), 2)) +
                     ","
                     + to_string(jpsi_0n0n_graph->GetBinContent(i)) +
                     ");";
        
        db->simpleGetResultFromSQL(sql);
    }

    // 0nxn
    for (int i = 1; i <= jpsi_0nxn_graph->GetNbinsX(); i++)
    {
        string sql = "insert into "
                     + string(table_name_0nxn) +
                     "(y, bincontent) "
                     "values("
                     + to_string(xqy::Utils::round_to_decimal(jpsi_0nxn_graph->GetBinCenter(i), 2)) +
                     ","
                     + to_string(jpsi_0nxn_graph->GetBinContent(i)) +
                     ");";
        
        db->simpleGetResultFromSQL(sql);
    }

    // xnxn
    for (int i = 1; i <= jpsi_xnxn_graph->GetNbinsX(); i++)
    {
        string sql = "insert into "
                     + string(table_name_xnxn) +
                     "(y, bincontent) "
                     "values("
                     + to_string(xqy::Utils::round_to_decimal(jpsi_xnxn_graph->GetBinCenter(i), 2)) +
                     ","
                     + to_string(jpsi_xnxn_graph->GetBinContent(i)) +
                     ");";
        
        db->simpleGetResultFromSQL(sql);
    }
}

/**
 * @brief 
 * 
 * @param particle_name 
 * @param databse_name 
 * @param csv_name 
 * @param table_name 
 */
void insert_data_print_vm(
    const char* particle_name, 
    const char* databse_name, 
    const char* csv_name, 
    const char* table_name
)
{
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
    SigmaWgmPbDataManager* db = new SigmaWgmPbDataManager();
    db->init(databse_name);
    BaseCSVManager* jpsi = new BaseCSVManager(
        csv_name,
        particle_name,
        10
    );
    db->dataInsertor(jpsi, table_name);
}

TGraphErrors* draw_graph(
    BaseDataBaseReader* db_reader,
    const char* graph_title,
    const char* save_file_name
) 
{
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

    TH2D *frame = new TH2D("frame", graph_title, 1000, 0, 3000, 100000, 0, 10);
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
        save_file_name);
    
    return res_graph; 
}

TGraphErrors* draw_psi2s_536()
{
    string sql_536_psi2s = R"(select 
                                a.wgp1,
                                a.sigma2_gamA,
                                a.wgp2,
                                a.sigma1_gamA
                            FROM
                                psi2sall a
                                INNER join 
                                    psi2s_0n0n_cut_eta_y_bincontent b on a.y = b.y
                                INNER JOIN
                                    psi2s_0nxn_cut_eta_y_bincontent c ON a.y = c.y
                            WHERE
                                (b.bincontent) > 80
                                AND (c.bincontent) > 80;
                                
    )";
    BaseDataBaseReader* psi2s_536_dbreader = new BaseDataBaseReader(
        sql_536_psi2s, "pbpb536psi2scoherent"
    );
    return draw_graph(
        psi2s_536_dbreader, 
        "#Psi(2S) production at PbPb 5.36TeV",
        "/home/huinaibing/huinaibing/PA/BUILD/neutron_tagging/psi2s/536/Psi(2S)_coherent_536.png"
    );
}

TGraphErrors* draw_psi2s_552()
{
    string sql_552_psi2s = R"(select 
                                a.wgp1,
                                a.sigma2_gamA,
                                a.wgp2,
                                a.sigma1_gamA
                            FROM
                                psi2sall a
                                INNER join 
                                    psi2s_0n0n_cut_eta_y_bincontent b on a.y = b.y
                                INNER JOIN
                                    psi2s_0nxn_cut_eta_y_bincontent c ON a.y = c.y
                                INNER JOIN
                                    psi2s_xnxn_cut_eta_y_bincontent d ON a.y = d.y
                            WHERE
                                (b.bincontent) > 80
                                AND (c.bincontent) > 80
                                and (d.bincontent) > 80;
                                
    )";
    BaseDataBaseReader* psi2s_552_dbreader = new BaseDataBaseReader(
        sql_552_psi2s, "pbpb552psi2scoherent"
    );
    return draw_graph(
        psi2s_552_dbreader, 
        "#Psi(2S) production at PbPb 5.52TeV",
        "/home/huinaibing/huinaibing/PA/BUILD/neutron_tagging/psi2s/552/Psi(2S)_coherent_552.png"
    );
}

// #define RHO0_552_0n0n "/home/huinaibing/huinaibing/PA/DATA_FILES/slight_out/neutron_tagging/rho0/552/rho0_552_0n0n.out"
// #define RHO0_552_0nxn "/home/huinaibing/huinaibing/PA/DATA_FILES/slight_out/neutron_tagging/rho0/552/rho0_552_0nxn.out"
// #define RHO0_552_xnxn "/home/huinaibing/huinaibing/PA/DATA_FILES/slight_out/neutron_tagging/rho0/552/rho0_552_xnxn.out"

// #define ROOT_RHO0_552_0n0n "/home/huinaibing/huinaibing/PA/DATA_FILES/slight_out/neutron_tagging/rho0/552_root/rho0_552_0n0n.root"
// #define ROOT_RHO0_552_0nxn "/home/huinaibing/huinaibing/PA/DATA_FILES/slight_out/neutron_tagging/rho0/552_root/rho0_552_0nxn.root"
// #define ROOT_RHO0_552_xnxn "/home/huinaibing/huinaibing/PA/DATA_FILES/slight_out/neutron_tagging/rho0/552_root/rho0_552_xnxn.root"

TGraphErrors* draw_rho0_536()
{
    string sql_536_rho0 = R"(select 
                                a.wgp1,
                                a.sigma2_gamA,
                                a.wgp2,
                                a.sigma1_gamA
                            FROM
                                rho0all a
                                INNER join 
                                    rho0_0n0n_cut_eta_y_bincontent b on a.y = b.y
                                INNER JOIN
                                    rho0_0nxn_cut_eta_y_bincontent c ON a.y = c.y
                                INNER JOIN
                                    rho0_xnxn_cut_eta_y_bincontent d ON a.y = d.y
                            WHERE
                                (b.bincontent) > 80
                                AND (c.bincontent) > 80
                                and (d.bincontent) > 80;
                                
    )";
    BaseDataBaseReader* rho0_536_dbreader = new BaseDataBaseReader(
        sql_536_rho0, "pbpb536rho0coherent"
    );
    return draw_graph(
        rho0_536_dbreader, 
        "#rho0 production at PbPb 5.36TeV",
        "/home/huinaibing/huinaibing/PA/BUILD/neutron_tagging/rho0/536/rho0_coherent_536.png"
    );
}

TGraphErrors* draw_rho0_552()
{
    string sql_552_rho0 = R"(select 
                                a.wgp1,
                                a.sigma2_gamA,
                                a.wgp2,
                                a.sigma1_gamA
                            FROM
                                rho0all a
                                INNER join 
                                    rho0_0n0n_cut_eta_y_bincontent b on a.y = b.y
                                INNER JOIN
                                    rho0_0nxn_cut_eta_y_bincontent c ON a.y = c.y
                                INNER JOIN
                                    rho0_xnxn_cut_eta_y_bincontent d ON a.y = d.y
                            WHERE
                                (b.bincontent) > 80
                                AND (c.bincontent) > 80
                                and (d.bincontent) > 80;
                                
    )";
    BaseDataBaseReader* rho0_552_dbreader = new BaseDataBaseReader(
        sql_552_rho0, "pbpb552rho0coherent"
    );
    return draw_graph(
        rho0_552_dbreader, 
        "rho0 production at PbPb 5.52TeV",
        "/home/huinaibing/huinaibing/PA/BUILD/neutron_tagging/rho0/552/rho0_coherent_552.png"
    );
}

/**
 * @details 
 * ## 存储数据
 * 
 * 1. 转换数据到root（3个）
 *    - input：
 *      1. starlight原始文件（x3）
 * 
 * 2. 从三个图提取y和bincontent信息存入数据库
 *    - 输入：
 *      1. root文件（x3）
 *      2. 数据库名
 *      3. 表名（x3）需要和root文件对应
 * 
 * 3. 将print_vm的输出导入数据库
 *    - 输入
 *      1. 数据库名字
 *      2. csv文件
 *      3. 表名字
 * 
 * ## 分析数据
 * 
 * 输入：
 * 
 * 1. 数据库名字
 * 2. 表名字x4
 * 
 */
void sigma_wgmpb_allinone_main()
{
    draw_rho0_536();
    draw_rho0_552();

}
