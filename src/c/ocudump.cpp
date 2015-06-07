#include <cmath>
#include <csignal>
#include <cstdio>
#include <cstring>
#include <vector>
#include "Extras/OVR_Math.h"
#include "ocudump.h"
#include "OVR_CAPI_0_5_0.h"

using std::vector;

float nanArr[] = {NAN, NAN, NAN};

namespace ocudump
{
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

void OcudumpBase::getPose()
{
    state = ovrHmd_GetTrackingState(hmd, 0);
    // convert c-api quaternion to cpp-api quaternion so we can do the GetEulerAngles call bellow
    orientation = state.HeadPose.ThePose.Orientation;
    orientation.GetEulerAngles<OVR::Axis_X,OVR::Axis_Y,OVR::Axis_Z>(pose.data(),pose.data()+1,pose.data()+2);
    // check to see if the camera is currently tracking the rift...
    if (state.StatusFlags&ovrStatus_PositionTracked && state.StatusFlags&ovrStatus_CameraPoseTracked && state.StatusFlags&ovrStatus_PositionConnected)
    {
        // ...and if it is, load the position data into the pose vector
        memcpy(&pose.data()[3], &state.HeadPose.ThePose.Position.x, 3*sizeof(float));
        positionTracked = true;
    }
    else
    {
        // ...and if it isn't, fill the position entries in pose with NaN values
        memcpy(&pose.data()[3], &nanVec, 3*sizeof(float));
        positionTracked = false;
    }
}

Ocudump::Ocudump(): OcudumpBase()
{
    init();
}

void Ocudump::init()
{
    if (ovr_Initialize(NULL))
    {
        hmd = ovrHmd_Create(0);
        if (!hmd || !ovrHmd_ConfigureTracking(hmd, ovrTrackingCap_Orientation | ovrTrackingCap_MagYawCorrection | ovrTrackingCap_Position, 0))
        {
            fprintf(stderr,"Unable to detect Rift head tracker");
            raise(SIGABRT);
        }
    }
}

OcudumpDebug::OcudumpDebug(): OcudumpBase()
{
    init();
}

void OcudumpDebug::init()
{
    if (ovr_Initialize(NULL))
    {
        hmd = ovrHmd_CreateDebug(ovrHmd_DK2);
        if (!hmd || !ovrHmd_ConfigureTracking(hmd, ovrTrackingCap_Orientation | ovrTrackingCap_MagYawCorrection | ovrTrackingCap_Position, 0))
        {
            fprintf(stderr,"Unable to detect Rift head tracker");
            raise(SIGABRT);
        }
    }
}
}
