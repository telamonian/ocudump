#include <vector>
#include "Extras/OVR_Math.h"
#include "OVR_CAPI.h"

namespace ocudump
{
class OcudumpBase
{
public:
    OcudumpBase();
    virtual ~OcudumpBase();

    virtual void init();
    virtual void getPose();
    virtual bool ovrHmdCreateVersioned();
    virtual bool ovrInitializeVersioned();

public:
    ovrHmd hmd;
    static std::vector<float> nanVec;
    OVR::Quatf orientation;
    std::vector<float> pose;
    bool positionTracked;
    ovrTrackingState state;
};

class Ocudump : public OcudumpBase
{
public:
    Ocudump();
    virtual ~Ocudump() {}

    virtual void init();
};

// derived class for creating an ocudump instance that interfaces with a virtual "debug device" Oculus (rather than a real, plugged in one)
class OcudumpDebug : public OcudumpBase
{
public:
    OcudumpDebug();
    virtual ~OcudumpDebug() {}

    virtual void init();
    virtual bool ovrHmdCreateVersioned();
};
}

