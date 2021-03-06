#include <cmath>
#include <csignal>
#include <cstdio>
#include <cstring>
#include <vector>
#include "Extras/OVR_Math.h"
#include "OVR_CAPI.h"

#include "animate/animate.h"
#include "main/ocudump.h"

using ocudump::PoseCoord;
using ocudump::animate::Animate;
using std::vector;

float nanArr[] = {NAN, NAN, NAN};

namespace ocudump {
namespace main {

// initialize the static member vector nanVec, used for filling in the appropriate portion of the pose vector with NaN values when the camera fails to track the rift
vector<float> OcudumpBase::nanVec(nanArr, nanArr + (sizeof(nanArr)/sizeof(nanArr[0])));

OcudumpBase::OcudumpBase(): hmd(NULL), pose(6,0), positionTracked(false)
{

}

OcudumpBase::~OcudumpBase()
{
    ovrHmd_Destroy(hmd);
    ovr_Shutdown();
}

bool OcudumpBase::init()
{
    if (ovrInitializeVersioned())
    {
        if (!ovrHmdCreateVersioned())
        {
            fprintf(stderr, "Unable to detect Rift head tracker\n");
            return 0;
//            raise(SIGABRT);
        }
		return ovrHmd_ConfigureTracking(hmd, ovrTrackingCap_Orientation | ovrTrackingCap_MagYawCorrection | ovrTrackingCap_Position, 0);
    }
    else
    {
        fprintf(stderr, "Call to ovr_Initialize failed\n");
        return 0;
//        raise(SIGABRT);
    }
}

void OcudumpBase::initAnimateElement(PoseCoord poseCoord, float low, float high, int period)
{
    animate.initElem(poseCoord, low, high, period);
}

bool OcudumpBase::ovrInitializeVersioned()
{
#if defined(OVRSDK5)
    return ovr_Initialize(NULL) ? true : false;
#elif defined(OVRSDK6)
    return (ovr_Initialize(NULL)==ovrSuccess);
#endif
}

void OcudumpBase::getPose()
{
    state = ovrHmd_GetTrackingState(hmd, 0);
    _getPoseOrientation();
    _getPosePosition();
}

void OcudumpBase::_getPoseOrientation()
{
    // convert c-api quaternion to cpp-api quaternion so we can do the GetEulerAngles call bellow
    orientation = state.HeadPose.ThePose.Orientation;
    orientation.GetEulerAngles<OVR::Axis_X,OVR::Axis_Y,OVR::Axis_Z>(pose.data(),pose.data()+1,pose.data()+2);
}

void OcudumpBase::_getPosePosition()
{
    // check to see if the camera is currently tracking the rift...
    if (state.StatusFlags&ovrStatus_PositionTracked && state.StatusFlags&ovrStatus_CameraPoseTracked && state.StatusFlags&ovrStatus_PositionConnected)
    {
        // ...and if it is, load the position data into the pose vector
        memcpy(&pose.data()[3], &state.HeadPose.ThePose.Position.x, 3*sizeof(float));
        positionTracked = true;
    }
    else
    {
//        // ...and if it isn't, fill the position entries in pose with NaN values
//        memcpy(&pose.data()[3], &nanVec, 3*sizeof(float));
        positionTracked = false;
    }
}

void OcudumpBase::getPoseAnimated()
{
    getPose();
    for (Animate::iterator it=animate.begin();it!=animate.end();it++)
    {
        pose[it->first]+=it->second.getElem();
    }
}

void OcudumpBase::getPrintline(char* printLine)
{
    sprintf(printLine, "Current pose - pitch %0.2f, yaw %0.2f, roll %0.2f, x %0.2f, y %0.2f, z %0.2f\n",pose[0],pose[1],pose[2],pose[3],pose[4],pose[5]);
}

void OcudumpBase::print()
{
    char printline[256];
    getPrintline(printline);
    printf(printline);
}

Ocudump::Ocudump(): OcudumpBase()
{
}

bool Ocudump::ovrHmdCreateVersioned()
{
#if defined(OVRSDK5)
    hmd = ovrHmd_Create(0);
    return hmd ? true : false;
#elif defined(OVRSDK6)
    return (ovrHmd_Create(0, &hmd)==ovrSuccess);
#endif
}

OcudumpDebug::OcudumpDebug(): OcudumpBase()
{
}

bool OcudumpDebug::init()
{
    if (ovrInitializeVersioned())
    {
        if (!ovrHmdCreateVersioned())
        {
            fprintf(stderr, "Unable to detect Rift head tracker\n");
            return 0;
        }
        ovrHmd_ConfigureTracking(hmd, ovrTrackingCap_Orientation | ovrTrackingCap_MagYawCorrection | ovrTrackingCap_Position, 0);
        return 1;
    }
    else
    {
        fprintf(stderr, "Call to ovr_Initialize failed\n");
        return 0;
    }
}

bool OcudumpDebug::ovrHmdCreateVersioned()
{
#if defined(OVRSDK5)
    hmd = ovrHmd_CreateDebug(ovrHmd_DK2);
    return hmd ? true : false;
#elif defined(OVRSDK6)
    return (ovrHmd_CreateDebug(ovrHmd_DK2, &hmd)==ovrSuccess);
#endif
}

void OcudumpDebug::getPose()
{
    // can't call the base class version since it's pure virtual... le sigh
    state = ovrHmd_GetTrackingState(hmd, 0);
    _getPoseOrientation();
    _getPosePosition();
    for (Animate::iterator it=animate.begin();it!=animate.end();it++)
    {
        pose[it->first]+=it->second.getElem();
    }
}

void OcudumpDebug::getPoseAnimated()
{
    getPose();
}

void OcudumpDebug::_getPosePosition()
{
    memcpy(&pose.data()[3], &state.HeadPose.ThePose.Position.x, 3*sizeof(float));
    positionTracked = true;
}

}
}
