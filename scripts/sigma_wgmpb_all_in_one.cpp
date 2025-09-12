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

}
