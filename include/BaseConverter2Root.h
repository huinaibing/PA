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

class BaseConverter2Root
{
public:
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
};

#endif