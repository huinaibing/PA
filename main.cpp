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

// #include "scripts/focal/phiKKReconstruct.cpp"
// #include "AliRootFOCALEventLooper.h"
// #include "scripts/phi_kk.cpp"

#include "scripts/tests/woodsaxon.cpp"
#include "TH1F.h"
#include "TF1.h"
#include "TMath.h"
#include "TFile.h"

int main()
{
    // AliRootFOCALEventLooper* looper = new AliRootFOCALEventLooper(
    //     "/home/huinaibing/focal_workdir/new_my_code/sl_phi_kk_geo_7mhcal/FOCAL.Hits.root",
    //     1000,
    //     20000
    // );
    // looper->classCheck(0, 20000);

    woodsaxon();

    return 0; // 写C++不在main函数里面return的注定会度过一个失败的人生
}
