#include <unistd.h>
#include <vector>
#include "ocudump.h"

using std::vector;

int main(int argc, char** argv)
{
    vector<float> pose(6,0);
    Ocudump* ocudump = new Ocudump();
    for (int i = 0; i < 1e6; ++i) {
        pose = ocudump->getPose();
        printf("Current orientation - pitch %0.2f, yaw %0.2f, roll %0.2f\n",pose[0],pose[1],pose[2]);
//                printf("status %d\n", state.StatusFlags);
//                printf("myflag %d\n", ovrStatus_PositionTracked | ovrStatus_CameraPoseTracked | ovrStatus_PositionConnected);
//        if (state.StatusFlags&ovrStatus_PositionTracked && state.StatusFlags&ovrStatus_CameraPoseTracked && state.StatusFlags&ovrStatus_PositionConnected) {
//            p = glm::make_vec3(&state.HeadPose.ThePose.Position.x);
//            printf("Current orientation/position - roll %0.2f, pitch %0.2f, yaw %0.2f, x %0.2f, y %0.2f, z %0.2f\n",euler.z,euler.x,euler.y,p.x,p.y,p.z);
//        }
//        else
//        {
//            printf("Current orientation - roll %0.2f, pitch %0.2f, yaw %0.2f\n",euler.z,euler.x,euler.y);
//        }
        usleep(1e5);
    }
}
