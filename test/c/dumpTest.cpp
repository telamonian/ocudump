#ifdef LINUX
    #include <unistd.h>
#endif
#ifdef WINDOWS
    #include <windows.h>
#endif
#include <vector>

#include "main/ocudump.h"

using ocudump::Ocudump;
using ocudump::OcudumpBase;
using ocudump::OcudumpDebug;
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

bool debug;
vector<int> poseCoords;

void parseIntListArg(vector<int> & list, char* arg)
{
    list.clear();
    char * argbuf = new char[strlen(arg)+1];
    strcpy(argbuf,arg);
    char * pch = strtok(argbuf," ,;:\"");
    while (pch != NULL)
    {
        char * rangeDelimiter;
        if ((rangeDelimiter=strstr(pch,"-")) != NULL)
        {
            *rangeDelimiter='\0';
            int begin=atoi(pch);
            int end=atoi(rangeDelimiter+1);
            for (int i=begin; i<=end; i++)
                list.push_back(i);
        }
        else
        {
            if (strlen(pch) > 0) list.push_back(atoi(pch));
        }
        pch = strtok(NULL," ,;:");
    }
    delete[] argbuf;
}

// Parses the command line arguments.
void parseArguments(int argc, char** argv)
{
    // Set any default options.
    debug = false;

    // Parse any arguments.
    for (int i=1; i<argc; i++)
    {
        char *option = argv[i];
        while (*option == ' ') option++;

        //See if the user is trying to run in debug mode
        if (strcmp(option, "-d") == 0 || strcmp(option, "--debug") == 0) {
            debug = true;
            break;
        }

        //See if the user is trying to set animations on the pose coordingates.
        else if ((strcmp(option, "-c") == 0 || strcmp(option, "--coords") == 0) && i < (argc-1))
        {
            parseIntListArg(poseCoords, argv[++i]);
        }
        else if (strncmp(option, "--coords=", strlen("--coords=")) == 0)
        {
            parseIntListArg(poseCoords, option+strlen("--coords="));
        }
    }
}

int main(int argc, char** argv)
{
    bool animateOcu = false;
    OcudumpBase* ocudump;

    if (debug) {
        ocudump = new OcudumpDebug();
    }
    else
    {
        ocudump = new Ocudump();
    }

    if (poseCoords.size() > 0)
    {
        animateOcu = true;
        for (vector<int>::iterator it=poseCoords.begin();it!=poseCoords.end();it++)
        {
            ocudump->animate.initElem(*it, -1, 1, 600);
        }
    }

    for (int i = 0; i < 1e6; ++i) {
        animateOcu ? ocudump->getPoseAnimated() : ocudump->getPose();
        printf("Current pose - pitch %0.2f, yaw %0.2f, roll %0.2f, x %0.2f, y %0.2f, z %0.2f\n",ocudump->pose[0],ocudump->pose[1],ocudump->pose[2],ocudump->pose[3],ocudump->pose[4],ocudump->pose[5]);
        printf("len of pose %lu", ocudump->pose.size());
        MySleep(1e3/60);
    }
}
