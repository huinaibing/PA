/**
 * @mainpage particle analysis
 * @brief 别往main函数堆分析代码！！！别往main函数堆分析代码！！！别往main函数堆分析代码！！！
 *
 *
 *                       _oo0oo_
 *                      o8888888o
 *                      88" . "88
 *                      (| -_- |)
 *                      0\  =  /0
 *                    ___/`---'\___
 *                  .' \\|     | * '.
 *                 / \\|||  :  ||| * \
 *                / _||||| -:- |||||- \
 *               |   | \\\  -  /// |   |
 *               | \_|  ''\---/''  |_/ |
 *               \  .-\__  '-'  ___/-. /
 *             ___'. .'  /--.--\  `. .'___
 *          ."" '<  `.___\_<|>_/___.' >' "".
 *         | | :  `- \`.;`\ _ /`;.`/ - ` : | |
 *         \  \ `_.   \_ __\ /__ _/   .-` /  /
 *     =====`-.____`.___ \_____/___.-`___.-'=====
 *                       `=---='
 *
 *
 *     ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *
 *               佛祖保佑         永无BUG
 *
 *
 *
 *
 * @section 用法：在scripts里面写主体分析代码，在这里调用，然后cmake
 */

#include "AllInOne.h"
#include "AliRootHitsFOCALManager.h"
#include "AliRootFOCALEventLooper.h"
#include "TTree.h"
#include "scripts/focal/phiKKReconstruct.cpp"


// #include "scripts/test.cpp"

int main()
{
    // PhiKKReconstruct looper("/home/huinaibing/focal_workdir/new_my_code/sl_phi_kk_geo_7mhcal/FOCAL.Hits.root", 20000, 40000);
    // // manager.classCheck();
    // looper.reconstructQA();
    AliRootHitsFOCALManager manager("/home/huinaibing/focal_workdir/new_my_code/sl_phi_kk_geo_7mhcal/FOCAL.Hits.root", "Event12", 40000);
    manager.classCheck();
    
    
    return 0; // 写C++不在main函数里面return的注定会度过一个失败的人生
}
