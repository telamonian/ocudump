#ifndef MAIN_OCUDUMP_H_
#define MAIN_OCUDUMP_H_

#include <vector>
#include "Extras/OVR_Math.h"
#include "OVR_CAPI.h"

#include "animate/animate.h"

namespace ocudump {

class OcudumpBase
{
public:
    OcudumpBase();
    virtual ~OcudumpBase();

    virtual bool init();
    virtual void getPose();
    virtual void getPoseAnimated();
    virtual bool ovrHmdCreateVersioned()=0;
    virtual bool ovrInitializeVersioned();

public:
    OVR::Quatf orientation;
    std::vector<float> pose;
    bool positionTracked;
    ovrTrackingState state;

protected:
    ocudump::animate::Animate animate;
    ovrHmd hmd;
    static std::vector<float> nanVec;
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

#endif /* MAIN_OCUDUMP_H_ */
