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

//    int run() {
//
//            glm::quat o;
//            glm::vec3 euler, p;
//            for (int i = 0; i < 1e6; ++i) {
//                ovrTrckingState state = ovrHmd_GetTrackingState(hmd, 0);
//                o = glm::make_quat(&state.HeadPose.ThePose.Orientation.x);
//                euler = glm::eulerAngles(o);
////                printf("status %d\n", state.StatusFlags);
////                printf("myflag %d\n", ovrStatus_PositionTracked | ovrStatus_CameraPoseTracked | ovrStatus_PositionConnected);
//                if (state.StatusFlags&ovrStatus_PositionTracked && state.StatusFlags&ovrStatus_CameraPoseTracked && state.StatusFlags&ovrStatus_PositionConnected) {
//                    p = glm::make_vec3(&state.HeadPose.ThePose.Position.x);
//                    printf("Current orientation/position - roll %0.2f, pitch %0.2f, yaw %0.2f, x %0.2f, y %0.2f, z %0.2f\n",euler.z,euler.x,euler.y,p.x,p.y,p.z);
//                }
//                else
//                {
//                    printf("Current orientation - roll %0.2f, pitch %0.2f, yaw %0.2f\n",euler.z,euler.x,euler.y);
//                }
//                usleep(1e5);
//            }
//            return 0;
//        }
//        else
//        {
//            fprintf(stderr,"Unable to initialize rift anything");
//            return -2;
//        }
public:
    ovrHmd hmd;
    static std::vector<float> nanVec;
    OVR::Quatf orientation;
    std::vector<float> pose;
    bool positionTracked;
    ovrTrackingState state;
};
