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

#include "scripts/focal/phiKKReconstruct.cpp"
// #include "AliRootFOCALEventLooper.h"
// #include "scripts/phi_kk.cpp"

#include "TH1F.h"
#include "TF1.h"
#include "TMath.h"
#include "TFile.h"




int main()
{
    // AliRootFOCALEventLooper * manager = new AliRootFOCALEventLooper("/home/huinaibing/focal_workdir/new_my_code/sl_rho0_pipi/FOCAL.Hits.root", 20000, 40000);
    // manager->classCheck(0, 100);
    phi_kk_reconstruct_footbook();
    // PhiKK a;
    // a.Convert();
    // a.Run();

   

    return 0; // 写C++不在main函数里面return的注定会度过一个失败的人生
}
