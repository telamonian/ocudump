#include <vector>
#include "Extras/OVR_Math.h"
#include "OVR_CAPI.h"

namespace ocudump {

enum PoseCoord
{
    xrot = 0,
    yrot = 1,
    zrot = 2,
    x = 3,
    y = 4,
    z = 5
};

class OcudumpBase
{
public:
    OcudumpBase();
    virtual ~OcudumpBase();

    virtual bool init();
    virtual void getPose();
    virtual bool ovrHmdCreateVersioned()=0;
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
//    virtual ~Ocudump() {}

    virtual bool ovrHmdCreateVersioned();
};

// derived class for creating an ocudump instance that interfaces with a virtual "debug device" Oculus (rather than a real, plugged in one)
class OcudumpDebug : public OcudumpBase
{
public:
    OcudumpDebug();
//    virtual ~OcudumpDebug() {}

    virtual bool ovrHmdCreateVersioned();
};
}

