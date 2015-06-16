#ifdef LINUX
    #include <unistd.h>
#endif
#ifdef WINDOWS
    #include <windows.h>
#endif
#include <vector>
#include "ocudump.h"

using ocudump::Ocudump;
using std::vector;

void MySleep(int sleepMs)
{
#ifdef LINUX
    usleep(sleepMs * 1000);   // usleep takes sleep time in us (1 millionth of a second)
#endif
#ifdef WINDOWS
    Sleep(sleepMs);
#endif
}

int main(int argc, char** argv)
{
    Ocudump* ocudump = new Ocudump();
    for (int i = 0; i < 1e6; ++i) {
        ocudump->getPose();
        printf("Current pose - pitch %0.2f, yaw %0.2f, roll %0.2f, x %0.2f, y %0.2f, z %0.2f\n",ocudump->pose[0],ocudump->pose[1],ocudump->pose[2],ocudump->pose[3],ocudump->pose[4],ocudump->pose[5]);
        printf("len of pose %lu", ocudump->pose.size());
        MySleep(1e1);
    }
}
