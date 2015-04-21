#include <cstdio>
#include <cmath>
#include <vector>
#include "Extras/OVR_Math.h"
#include "ocudump.h"
#include "OVR_CAPI_0_5_0.h"

using std::vector;

Ocudump::Ocudump(): hmd(NULL), pose(6,0)
{
    Init();
}

Ocudump::~Ocudump()
{
    ovrHmd_Destroy(hmd);
    ovr_Shutdown();
}

void Ocudump::Init()
{
    if (ovr_Initialize(NULL))
    {
        ovrHmd hmd = ovrHmd_Create(0);
        if (!hmd || !ovrHmd_ConfigureTracking(hmd, ovrTrackingCap_Orientation | ovrTrackingCap_MagYawCorrection | ovrTrackingCap_Position, 0))
        {
            fprintf(stderr,"Unable to detect Rift head tracker");
//                raise(SIGABRT);
        }
    }
}

vector<float> Ocudump::getPose()
{
    state = ovrHmd_GetTrackingState(hmd, 0);
    // convert c-api quaternion to cpp-api quaternion
    orientation = state.HeadPose.ThePose.Orientation;
    orientation.GetEulerAngles<OVR::Axis_X,OVR::Axis_Y,OVR::Axis_Z>(pose.data(),pose.data()+1,pose.data()+2);
    return pose;
}
