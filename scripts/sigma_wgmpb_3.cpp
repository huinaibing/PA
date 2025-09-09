#include <iostream>
#include "BaseConverter2Root.h"
#include "BaseDoubleParticalChannelManager.h"
#include "BaseDrawGraph.h"
#include "TH1D.h"
#include "TH1.h"
#include "TClass.h"
#include "AllInOne.h"
using namespace std;

#define JPSI_0N0N "/home/huinaibing/huinaibing/PA/DATA_FILES/pbpb536_coherent_neutron_tagging/old_cuted_eta/PbPb536_0n0n.out"
#define JPSI_0NXN "/home/huinaibing/huinaibing/PA/DATA_FILES/pbpb536_coherent_neutron_tagging/old_cuted_eta/PbPb536_0nXn.out"
#define JPSI_XNXN "/home/huinaibing/huinaibing/PA/DATA_FILES/pbpb536_coherent_neutron_tagging/old_cuted_eta/PbPb536_XnXn.out"

#define ROOT_JPSI_0N0N "/home/huinaibing/huinaibing/PA/DATA_FILES/pbpb536_coherent_neutron_tagging/old_cuted_eta/root/PbPb536_0n0n.root"
#define ROOT_JPSI_0NXN "/home/huinaibing/huinaibing/PA/DATA_FILES/pbpb536_coherent_neutron_tagging/old_cuted_eta/root/PbPb536_0nXn.root"
#define ROOT_JPSI_XNXN "/home/huinaibing/huinaibing/PA/DATA_FILES/pbpb536_coherent_neutron_tagging/old_cuted_eta/root/PbPb536_XnXn.root"


void convert_data2root()
{
    BaseConverter2Root::convert2rootfile(JPSI_0N0N, ROOT_JPSI_0N0N);
    BaseConverter2Root::convert2rootfile(JPSI_0NXN, ROOT_JPSI_0NXN);
    BaseConverter2Root::convert2rootfile(JPSI_XNXN, ROOT_JPSI_XNXN);
}

void check_electron()
{
    BaseDoubleParticalChannelManager* jpsi_0n0n = new BaseDoubleParticalChannelManager(ROOT_JPSI_0N0N, "jpsi_0n0n");
    BaseDoubleParticalChannelManager* jpsi_0nxn = new BaseDoubleParticalChannelManager(ROOT_JPSI_0NXN, "jpsi_0nxn");
    BaseDoubleParticalChannelManager* jpsi_xnxn = new BaseDoubleParticalChannelManager(ROOT_JPSI_XNXN, "jpsi_xnxn");

    jpsi_0n0n->classCheck();
    jpsi_0nxn->classCheck();
    jpsi_xnxn->classCheck();
}

void insert_sql()
{
    BaseDoubleParticalChannelManager* jpsi_0n0n = new BaseDoubleParticalChannelManager(ROOT_JPSI_0N0N, "jpsi");
    BaseDoubleParticalChannelManager* jpsi_0nxn = new BaseDoubleParticalChannelManager(ROOT_JPSI_0NXN, "jpsi");
    BaseDoubleParticalChannelManager* jpsi_xnxn = new BaseDoubleParticalChannelManager(ROOT_JPSI_XNXN, "jpsi");
    
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
    db->init("pbpb536jpsicoherent");
    // for (int i = 1; i <= jpsi_0n0n_graph->GetNbinsX(); i++)
    // {
    //     cout << xqy::Utils::round_to_decimal(jpsi_0n0n_graph->GetBinCenter(i), 2) << "\t" << jpsi_0n0n_graph->GetBinContent(i) << endl;
    // }

    for (int i = 1; i <= jpsi_xnxn_graph->GetNbinsX(); i++)
    {
        string sql = "insert into jpsi536xnxn_cut_eta_y_bincontent(y, bincontent) "
                     "values("
                     + to_string(xqy::Utils::round_to_decimal(jpsi_xnxn_graph->GetBinCenter(i), 2)) +
                     ","
                     + to_string(jpsi_xnxn_graph->GetBinContent(i)) +
                     ");";
        
        db->simpleGetResultFromSQL(sql);
        // cout << sql << endl;
    }
}

/**
 * @brief main函数不要堆代码，新开一个函数
 * 
 */
void sigma_wgmpb_3_main()
{

}