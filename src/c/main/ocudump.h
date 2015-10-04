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
    virtual bool ovrInitializeVersioned();
    virtual bool ovrHmdCreateVersioned()=0;

    virtual void getPose();
    virtual void getPoseAnimated();
    virtual void getPrintline(char*);
    virtual void print();

protected:
    virtual void _getPoseOrientation();
    virtual void _getPosePosition();

public:
    ocudump::animate::Animate animate;
    OVR::Quatf orientation;
    std::vector<float> pose;
    bool positionTracked;
    ovrTrackingState state;

protected:
    ovrHmd hmd;
    static std::vector<float> nanVec;
};

class Ocudump : public OcudumpBase
{
public:
    Ocudump();

    virtual bool ovrHmdCreateVersioned();
};

// derived class for creating an ocudump instance that interfaces with a virtual "debug device" Oculus (rather than a real, plugged in one)
class OcudumpDebug : public OcudumpBase
{
public:
    OcudumpDebug();

    virtual bool ovrHmdCreateVersioned();

protected:
    virtual void _getPosePosition() {}
};
}

#endif /* MAIN_OCUDUMP_H_ */
