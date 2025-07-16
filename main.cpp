/** 
 * @mainpage particle analysis
 *  
 * @section 用法：在scripts里面写主体分析代码，在这里调用，然后cmake
 */


// #include "scripts/JpsiProperty.cpp"
// #include "scripts/mixevent_muon.cpp"
// #include "scripts/remove_bkg.cpp"
// #include "scripts/muonAnalysis.cpp"

// #include "scripts/upcFig5.cpp"
// #include "TH1.h"
// #include "scripts/upcFig7.cpp"
//#include "scripts/UpcFig8.cpp"
#include "scripts/compare_coherent_incoherent.cpp"


int main()
{
    
    //jpsi_property_analysis();
    // muon_analysis();
    //mixevent_muon_analysis();
    //remove_bkg();
    //upc_fig5();
    // upc_fig_7();
    //upc_fig_8();
    compare_coherent_incoherent();

    return 0;
}
