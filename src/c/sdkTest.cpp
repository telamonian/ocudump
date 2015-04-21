#include <cstdio>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <OVR_CAPI_0_5_0.h>
#include <unistd.h>

class Tracker {
public:

    int run() {
        if (ovr_Initialize(NULL)) {
            ovrHmd hmd = ovrHmd_Create(0);
            if (!hmd || !ovrHmd_ConfigureTracking(hmd, ovrTrackingCap_Orientation | ovrTrackingCap_MagYawCorrection | ovrTrackingCap_Position, 0)) {
                fprintf(stderr,"Unable to detect Rift head tracker");
                return -1;
            }
            glm::quat o;
            glm::vec3 euler, p;
            for (int i = 0; i < 1e6; ++i) {
                ovrTrackingState state = ovrHmd_GetTrackingState(hmd, 0);
                o = glm::make_quat(&state.HeadPose.ThePose.Orientation.x);
                euler = glm::eulerAngles(o);
                if (state.StatusFlags&ovrStatus_PositionTracked && state.StatusFlags&ovrStatus_CameraPoseTracked && state.StatusFlags&ovrStatus_PositionConnected) {
                    p = glm::make_vec3(&state.HeadPose.ThePose.Position.x);
                    printf("Current orientation/position - roll %0.2f, pitch %0.2f, yaw %0.2f, x %0.2f, y %0.2f, z %0.2f\n",euler.z,euler.x,euler.y,p.x,p.y,p.z);
                }
                else
                {
                    printf("Current orientation - roll %0.2f, pitch %0.2f, yaw %0.2f\n",euler.z,euler.x,euler.y);
                }
                usleep(1e5);
            }
            ovrHmd_Destroy(hmd);
            ovr_Shutdown();
            return 0;
        }
        else
        {
            fprintf(stderr,"Unable to initialize rift anything");
            return -2;
        }
    }
};

int main(int argc, char** argv)
{
    Tracker* tracker = new Tracker();
    return tracker->run();
}
