#ifndef __UTILS__
#define __UTILS__

#include "TMath.h"
#include "TGraphErrors.h"
#include "TH2D.h"
#include <string.h>
#include "TCanvas.h"
#include "TLegend.h"

namespace xqy
{
    class Utils
    {
    public:
        static constexpr float sigma_p_jpsi = 4.06;
        static constexpr float epsilon_jpsi = 0.65;
        static constexpr float proton_mass = 0.938272; // GeV
        static constexpr float jpsi_mass = 3.0969;     // GeV
        static constexpr float psi2s_mass = 3.686097;  // GeV

        static double vectorAngleCosine(double x1, double y1, double z1,
                                 double x2, double y2, double z2)
        {
            // 计算点积
            double dotProduct = x1 * x2 + y1 * y2 + z1 * z2;

            // 计算两个向量的模长
            double mag1 = std::sqrt(x1 * x1 + y1 * y1 + z1 * z1);
            double mag2 = std::sqrt(x2 * x2 + y2 * y2 + z2 * z2);

            // 处理零向量（模长接近0，避免除零）
            if (mag1 < 1e-9 || mag2 < 1e-9)
            {
                throw std::domain_error("向量不能为零向量（模长为0）");
            }

            // 返回夹角余弦值
            return dotProduct / (mag1 * mag2);
        }

        /**
         * @brief 四舍五入
         *
         * @param value 传入的值
         * @param decimal_places 保留几位有效数字
         * @example round_to_decimal(8.955, 2); 结果: 8.96
         * @return double
         */
        static double round_to_decimal(double value, int decimal_places)
        {
            double scale = pow(10.0, decimal_places); // 计算缩放比例（10^n）
            return round(value * scale) / scale;      // 缩放后四舍五入，再还原
        }

        /**
         * @brief 把很多图画在一起， 由于TGraph和TH1不是继承同一个，所以要单独弄
         *
         * @param th1
         * @param graph
         * @param frame_option
         * @param canvas_option
         * @param leg_option
         * @param file_name
         */
        static void save_graphs_together(std::vector<TH1 *> th1,
                                         std::vector<TGraph *> graph,
                                         TH1 *frame,
                                         std::function<void(TCanvas *)> canvas_option,
                                         std::function<void(TLegend *)> leg_option,
                                         const char *file_name)
        {
            TLegend *leg = new TLegend();
            TCanvas *cvs = new TCanvas();
            canvas_option(cvs);
            leg_option(leg);
            frame->SetStats(0);
            frame->Draw();

            for (auto i : th1)
            {
                leg->AddEntry(i);
                i->Draw("P SAME");
            }

            for (auto i : graph)
            {
                leg->AddEntry(i);
                i->Draw("P SAME");
            }
            leg->Draw("SAME");

            cvs->SaveAs(file_name);
        }

        static int get_no_zero_points(TH1D *hist)
        {
            // 获取TH1D中非零点的数量
            // 这里的非零点是指bin内容不为0的点
            int no_zero_points = 0;
            for (int i = 1; i <= hist->GetNbinsX(); i++)
            {
                if (hist->GetBinContent(i) > 0)
                {
                    no_zero_points++;
                }
            }
            return no_zero_points;
        }

        static int get_valid_points(TH2D *hist)
        // 从TH2D中获取有效点的数量
        // 有效点是指在每个x bin中，y bin有数据的点
        {
            int valid_points = 0;
            for (int i = 1; i <= hist->GetNbinsX(); i++)
            {
                TH1D *projY = hist->ProjectionY("_py", i, i);
                if (projY->GetEntries() > 0)
                {
                    valid_points++;
                }
            }
            return valid_points;
        }

        static float calculate_momentum(float px, float py, float pz)
        // 计算粒子的动量
        {
            return TMath::Sqrt(px * px + py * py + pz * pz);
        }

        static double fit_w_gamma_p_and_cross_section(
            double *x,
            double *par)
        {
            return par[0] / (1 / TMath::Power(x[0], par[1]) + par[2]);
        }

        template <typename T>
        static T calculate_sqrt_error(TH1 *projY)
        // 计算平方根误差
        // 对应于poisson分布
        {
            return TMath::Sqrt(projY->GetMean());
        }

        static float calculate_cross_section_supplement_power_law(
            float w_gamma_p,
            float sigma_p = xqy::Utils::sigma_p_jpsi,
            float epsilon = xqy::Utils::epsilon_jpsi,
            float VM_mass = xqy::Utils::jpsi_mass)
        // 计算J/psi, psi', upsilon的截面
        // 默认参数是J/psi的
        // 公式见STARlight论文的公式（23）
        {
            // (m_p + m_V)^2 / W^2
            float mid_term_right = TMath::Power(xqy::Utils::proton_mass + VM_mass, 2) / (w_gamma_p * w_gamma_p);
            // (1 - (m_p + m_V)^2 / W^2)^2
            float mid_term = (1 - mid_term_right) * (1 - mid_term_right);

            return sigma_p * mid_term * TMath::Power(w_gamma_p, epsilon);
        }

        static double calculate_center_of_mass_rapidity(
            double E1, double gamma1,
            double E2, double gamma2)
        // 计算质心系的快度（相对于实验室系的）、
        // 这里默认粒子1方向为正，粒子2方向为负
        {
            double beta1 = TMath::Sqrt(1 - 1 / (gamma1 * gamma1));
            double beta2 = TMath::Sqrt(1 - 1 / (gamma2 * gamma2));

            double beta_cms = (E1 * beta1 - E2 * beta2) / (E1 + E2);

            return xqy::Utils::calculate_rapidity(beta_cms);
        }

        static float calculate_rapidity(float E, float pz)
        // 计算粒子的快度
        {
            return 0.5 * TMath::Log((E + pz) / (E - pz));
        }

        static float calculate_rapidity(double beta)
        // 计算粒子的快度
        // 和上面的函数不同的是，这里是直接传入beta
        {
            return 0.5 * TMath::Log((1 + beta) / (1 - beta));
        }

        static float calculate_energy(float px, float py, float pz, float mass)
        // 计算粒子的能量
        {
            return TMath::Sqrt(px * px + py * py + pz * pz + mass * mass);
        }

        static float calculate_pt(float px, float py)
        // 计算粒子的横动量pt
        {
            return TMath::Sqrt(px * px + py * py);
        }

        static float calculate_eta(float px, float py, float pz)
        // 计算粒子的伪快度eta
        {
            float p = TMath::Sqrt(px * px + py * py + pz * pz);
            return 0.5 * TMath::Log((p + pz) / (p - pz));
        }

        static float calculate_w_gamma_p_jpsi(float E_proton, float y, int direction = 1)
        // 计算Wgammap，也就是这个质心系能量
        // 单位取GeV
        // 备注，第一个图的E_proton是6800GeV
        // y是快度，应该是在实验室系下的快度（AI也是这么说的，先尝试一下）
        {
            float m_jpsi = 3.0969; // J/psi mass GeV
            return TMath::Sqrt(2 * E_proton * m_jpsi * TMath::Exp(direction * y));
        }

        static float calculate_w_gamma_p(float mass, float E_proton, float y, int direction = 1)
        {
            return TMath::Sqrt(2 * E_proton * mass * TMath::Exp(direction * y));
        }

        static double calculate_theta(double px, double py, double pz)
        {
            double pT = xqy::Utils::calculate_pt(px, py);
            return TMath::ATan(pT / pz);
        }

        static double calculate_phi(double px, double py)
        {
            return TMath::ATan(py / px);
        }

        /**
         * @brief 沙比c str 还有沙比root非要用const char *，程序员都该沙了
         *
         * @param str1
         * @param str2
         * @return const char*
         */
        static const char *concatenate_const_char(const char *str1, const char *str2)
        {
            std::string temp = std::string(str1) + str2;
            char *buffer = new char[temp.size() + 1];
            std::strcpy(buffer, temp.c_str());
            return buffer; // 调用者必须delete[]
        }

        static const char *concatenate_const_char(std::vector<const char *> strs)
        {
            const char *str_tmp = strs[0];

            for (int i = 1; i < strs.size(); i++)
            {
                str_tmp = Utils::concatenate_const_char(str_tmp, strs[i]);
            }

            return str_tmp;
        }

        /**
         * @brief Get the photon flux 只能用于AA碰撞
         *        公式详情见The Physics of Ultraperipheral Collisions at the LHC中6
         *
         * @param k 光子的波数（就是能量，自然单位），单位为fm-1
         * @param big_Z 光子源的Z，默认是铅核
         * @param gamma_L 光子源的lorentz因子，默认参数是5.36TeV的PbPb
         * @param r_A 光子源的半径，默认参数为7fm-1
         * @return double
         */
        static double get_photon_flux_AA(double k, int big_Z = 82, int gamma_L = 2857, int r_A = 7)
        {
            double omega = 2 * k * r_A / gamma_L;
            double coef = 2 * big_Z * big_Z * (1 / 137) / TMath::Pi() / k;

            double first_term = omega * TMath::BesselK0(omega) * TMath::BesselK1(omega);
            double second_term = omega * omega / 2 * (TMath::BesselK1(omega) * TMath::BesselK1(omega) - TMath::BesselK0(omega) * TMath::BesselK0(omega));

            return coef * (first_term - second_term);
        }
    };
}

#endif
