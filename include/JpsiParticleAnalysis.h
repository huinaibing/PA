#ifndef JPSI_PARTICLE_ANALYSIS_H
#define JPSI_PARTICLE_ANALYSIS_H
#include "BaseDoubleParticalChannelManager.h"
#include "BasePpb8_16Config.h"

class JpsiParticleAnalysis : public BaseDoubleParticalChannelManager
{
public:
    JpsiParticleAnalysis(const char *file_path,
                         const char *partical_name,
                         float partical_mass,
                         BasePpb8_16Config *config);
    ~JpsiParticleAnalysis();

    float getWGammaP();

    float getCrossSection();

private:
    BasePpb8_16Config *config;
};

#endif
