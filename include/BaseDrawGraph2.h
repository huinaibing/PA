#ifndef BASEDRAWGRAPH2_H
#define BASEDRAWGRAPH2_H

#include "BaseDrawGraph.h"
#include "BaseManager.h"
#include "TH1.h"
#include "TCanvas.h"
#include "TFile.h"

class BaseDrawGraph2 : public BaseDrawGraph
{
protected:
    BaseManager *manager;
    TH1 *hist = nullptr;
    std::function<void(TCanvas *)> draw_option;
    std::function<void(TH1 *)> hist_option;

public:
    BaseDrawGraph2(BaseManager *manager, TH1 *hist)
    {
        this->manager = manager;
        this->hist = hist;
        this->draw_option = [](TCanvas *canvas) {};
        this->hist_option = [](TH1 *hist) {};
    }

    /**
     * @brief Construct a new Base Draw Graph 2 object
     * @details 你可以使用上面的函数，在初始化的时候直接初始化hist，也可以后续在用setHist去初始化
     *
     * @param manager
     */
    BaseDrawGraph2(BaseManager *manager)
    {
        this->manager = manager;
        this->draw_option = [](TCanvas *canvas) {};
        this->hist_option = [](TH1 *hist) {};
    }

    /**
     * @brief 适用于填充一维图的函数，从manager里面获取数据
     *
     * @param get_data_func
     * @return TH1*
     */
    virtual TH1 *fillHistFromManager(std::function<double()> get_data_func) { return nullptr; }

    /**
     * @brief 二维图的填充函数，同上
     *
     * @param get_x_func
     * @param get_y_func
     * @return TH1*
     */
    virtual TH1 *fillHistFromManager(std::function<double()> get_x_func,
                                     std::function<double()> get_y_func) { return nullptr; }

    /**
     * @brief 加了一个过滤器，其他一样
     *
     * @param get_x_func
     * @param get_y_func
     * @param filter_function 返回false的话说明这个数据不要
     * @return TH1*
     */
    virtual TH1 *fillHistFromManager(std::function<double()> get_x_func,
                                     std::function<double()> get_y_func,
                                     std::function<bool()> filter_function) { return nullptr; }

    /**
     * @brief 一维图专用，只填充一个数据
     *
     * @param data
     * @return TH1*
     */
    virtual TH1 *fillOneData(double data)
    {
        this->hist->Fill(data);
        return this->hist;
    }

    /**
     * @brief 二维图专用，只填充一个数据
     *
     * @param x_data
     * @param y_data
     * @return TH1*
     */
    virtual TH1 *fillOneData(double x_data, double y_data)
    {
        this->hist->Fill(x_data, y_data);
        return this->hist;
    }

    /**
     * @brief Set the Draw Option object
     * @details 接受设置canvas的lambda函数，在保存成文件的时候会使用这些设置
     *
     * @param draw_option lambda函数，用于设置canvas
     */
    void setDrawOption(std::function<void(TCanvas *)> draw_option)
    {
        this->draw_option = draw_option;
    }

    /**
     * @brief Set the Hist Option object
     * @details 用于设置hist的代码，和上面的函数一个样子
     *
     * @param hist_option
     */
    void setHistOption(std::function<void(TH1 *)> hist_option)
    {
        this->hist_option = hist_option;
    }

    /**
     * @brief 保存成ROOT文件
     *
     * @param file_name
     */
    virtual void saveFile(const char *file_name)
    {
        TFile *file = new TFile(file_name, "RECREATE");
        TCanvas *canvas = new TCanvas();
        this->draw_option(canvas);
        this->hist_option(this->hist);
        this->hist->Draw();
        canvas->Write();
        file->Close();
    }

    /**
     * @brief 保存成PNG
     *
     * @param file_name
     */
    virtual void savePNG(const char *file_name)
    {
        TCanvas *canvas = new TCanvas();
        this->draw_option(canvas);
        this->hist_option(this->hist);
        this->hist->Draw();
        canvas->SaveAs(file_name);
        delete canvas;
    }

    TH1 *getHist()
    {
        return this->hist;
    }

    void setHist(TH1 *hist)
    {
        this->hist = hist;
    }
};

#endif // BASEDRAWGRAPH2_H
