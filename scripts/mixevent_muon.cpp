#include "MixEvents.h"
#include "TMath.h"
#define MUON_PATH "/home/huinaibing/huinaibing/PA/DATA_FILES/muon_jpsi/muon_mixevent.root"
#define MUON_FROM_JPSI "/home/huinaibing/huinaibing/PA/DATA_FILES/muon_jpsi/muonfromjpsi.root"

void mixevent_muon_analysis()
{
    BaseMomentumManage positive = BaseMomentumManage(
        MUON_PATH, 
        "muon_positive", 
        "tree_positive", 
        "positive_px", 
        "positive_py", 
        "positive_pz"
    );

    BaseMomentumManage negative = BaseMomentumManage(
        MUON_PATH, 
        "muon_negative", 
        "tree_negative", 
        "negative_px", 
        "negative_py", 
        "negative_pz"
    );
    MixEvents mix_events = MixEvents(
        "muon",
        0.1056583745, // Muon mass in GeV/c^2
        &negative,
        &positive
    );
    mix_events.save("mix_event/muon_mixevent.root");

    BaseMomentumManage positive_from_jpsi = BaseMomentumManage(
        MUON_FROM_JPSI, 
        "muon_positive", 
        "tree_positive", 
        "positive_px", 
        "positive_py", 
        "positive_pz"
    );

    BaseMomentumManage negative_from_jpsi = BaseMomentumManage(
        MUON_FROM_JPSI, 
        "muon_negative", 
        "tree_negative", 
        "negative_px", 
        "negative_py", 
        "negative_pz"
    );
    MixEvents mix_events_from_jpsi = MixEvents(
        "muon",
        0.1056583745, // Muon mass in GeV/c^2
        &negative_from_jpsi,
        &positive_from_jpsi
    );
    mix_events_from_jpsi.save("mix_event/muon_from_jpsi.root");
}
