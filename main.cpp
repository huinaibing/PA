#include "scripts/JpsiProperty.cpp"
#include "scripts/mixevent_muon.cpp"
#include "scripts/remove_bkg.cpp"

int main()
{
    
    // jpsi_property_analysis();
    mixevent_muon_analysis();
    remove_bkg();
    return 0;
}
