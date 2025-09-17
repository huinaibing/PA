/**
 * @file BaseConverter2Root.h
 * @author Autumnrain Summer (you@domain.com)
 * @brief 本文件针对starlight的一般输出格式设计，只对starlight有用
 * @version 0.1
 * @date 2025-07-16
 * 
 * @copyright Copyright (c) 2025
 * 
 */


#ifndef BASE_CONVERTER_2_ROOT_H
#define BASE_CONVERTER_2_ROOT_H


#include "TFile.h"
#include "TTree.h"
#include <iostream>
#include <vector>
#include <fstream>

struct eventdata
{
    float p_px;
    float p_py;
    float p_pz;

    float e_px;
    float e_py;
    float e_pz;
};

struct neg_pos_p
{
    double neg_px;
    double neg_py;
    double neg_pz;

    double pos_px;
    double pos_py;
    double pos_pz;
};

class BaseConverter2Root
{
public:
    /**
     * @brief notice that this function only works for e+e- situation
     * 
     * @param input_file_path 
     * @param output_file_name 
     */
    static void convert2rootfile(const char *input_file_path, const char *output_file_name)
    {
        TFile *f = new TFile(output_file_name, "RECREATE");
        TTree *tree = new TTree("events", "positive/negative particle Separated Data");

        eventdata data;

        tree->Branch("p_px", &data.p_px, "p_px/F");
        tree->Branch("p_py", &data.p_py, "p_py/F");
        tree->Branch("p_pz", &data.p_pz, "p_pz/F");

        tree->Branch("e_px", &data.e_px, "e_px/F");
        tree->Branch("e_py", &data.e_py, "e_py/F");
        tree->Branch("e_pz", &data.e_pz, "e_pz/F");

        std::ifstream infile(input_file_path);
        std::string line;
        bool newEvent = false;

        while (std::getline(infile, line))
        {
            if (line.find("EVENT:") != std::string::npos)
            {
                if (newEvent)
                {
                    tree->Fill();
                }
                newEvent = true;
            }
            else if (line.find("TRACK") != std::string::npos)
            {
                int id;
                float x, y, z;
                std::sscanf(line.c_str(), "TRACK: %d %f %f %f %*d %*d %*d %*d", &id, &x, &y, &z);

                if (id == 3) // electron
                {
                    data.e_px = x;
                    data.e_py = y;
                    data.e_pz = z;
                }
                else if (id == 2) // positron
                {
                    data.p_px = x;
                    data.p_py = y;
                    data.p_pz = z;
                }
            }
        }

        if (newEvent)
        {
            tree->Fill();
        }

        f->Write();
        f->Close();

        infile.close();
    }

    /**
     * @brief need to input positive particle id and negative particle id PDG, K+ is 321 
     * 
     * @param input_file_path 
     * @param output_file_name 
     * @param positive_id 
     * @param negative_id 
     */
    static void convert2rootfile(const char *input_file_path, const char *output_file_name, int positive_id, int negative_id)
    {
        TFile *f = new TFile(output_file_name, "RECREATE");
        TTree *tree = new TTree("events", "positive/negative particle Separated Data");

        neg_pos_p data;

        tree->Branch("neg_px", &data.neg_px, "neg_px/D");
        tree->Branch("neg_py", &data.neg_py, "neg_py/D");
        tree->Branch("neg_pz", &data.neg_pz, "neg_pz/D");

        tree->Branch("pos_px", &data.pos_px, "pos_px/D");
        tree->Branch("pos_py", &data.pos_py, "pos_py/D");
        tree->Branch("pos_pz", &data.pos_pz, "pos_pz/D");

        std::ifstream infile(input_file_path);
        std::string line;
        bool newEvent = false;

        while (std::getline(infile, line))
        {
            if (line.find("EVENT:") != std::string::npos)
            {
                if (newEvent)
                {
                    tree->Fill();
                }
                newEvent = true;
            }
            else if (line.find("TRACK") != std::string::npos)
            {
                int id;
                float x, y, z;
                std::sscanf(line.c_str(), "TRACK: %*d %f %f %f %*d %*d %*d %d", &x, &y, &z, &id);

                if (id == negative_id) // negative
                {
                    data.neg_px = x;
                    data.neg_py = y;
                    data.neg_pz = z;
                }
                else if (id == positive_id) // positive
                {
                    data.pos_px = x;
                    data.pos_py = y;
                    data.pos_pz = z;
                }
                else
                {
                    throw std::invalid_argument("particle id not find!!");
                }
            }
        }

        if (newEvent)
        {
            tree->Fill();
        }

        f->Write();
        f->Close();

        infile.close();
    }
};

#endif
