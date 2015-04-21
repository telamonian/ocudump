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
        printf("Current pose - pitch %0.2f, yaw %0.2f, roll %0.2f, x %0.2f, y %0.2f, z %0.2f\n",pose[0],pose[1],pose[2],pose[3],pose[4],pose[5]);
        usleep(1e5);
    }
}
