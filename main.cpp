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

// #include "scripts/tests/woodsaxon.cpp"
// #include "TH1F.h"
// #include "TF1.h"
// #include "TMath.h"
// #include "TFile.h"
#include "scripts/tests/draw_bb_pi_k_p.cpp"
int main()
{
    // AliRootFOCALEventLooper* looper = new AliRootFOCALEventLooper(
    //     "/home/huinaibing/aliroot_workdir/my_code/hijing_small/FOCAL.Hits.root",
    //     1,
    //     200000
    // );
    // looper->classCheck(0, 1);

    draw_bb_pi_k_p();

    return 0; // 写C++不在main函数里面return的注定会度过一个失败的人生
}
