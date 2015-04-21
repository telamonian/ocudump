#include <vector>
#include "Extras/OVR_Math.h"
#include "OVR_CAPI_0_5_0.h"

class Ocudump
{
public:
    Ocudump();
    virtual ~Ocudump();

    virtual void Init();
    virtual std::vector<float> getPose();

public:
    ovrHmd hmd;
    static std::vector<float> nanVec;
    OVR::Quatf orientation;
    std::vector<float> pose;
    bool positionTracked;
    ovrTrackingState state;
};
