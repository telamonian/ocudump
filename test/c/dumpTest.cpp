#include <iostream>
#ifdef LINUX
    #include <unistd.h>
#endif
#ifdef WINDOWS
    #include <windows.h>
#endif
#include <vector>

#include "enum.h"
#include "main/ocudump.h"

using ocudump::main::Ocudump;
using ocudump::main::OcudumpBase;
using ocudump::main::OcudumpDebug;
using std::cout;
using std::endl;
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

// declare option variables
bool debug;
vector<int> poseCoords;

void parseIntListArg(vector<int>& list, char* arg)
{
    list.clear();
    char* argbuf = new char[strlen(arg)+1];
    strcpy(argbuf,arg);
    char* pch = strtok(argbuf," ,;:\"");
    while (pch != NULL)
    {
        char* rangeDelimiter;
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
    parseArguments(argc, argv);

    bool animateOcu = false;
    OcudumpBase* ocudu;

    if (debug) {
        ocudu = new OcudumpDebug();
    }
    else
    {
        ocudu = new Ocudump();
    }
    ocudu->init();

    if (poseCoords.size() > 0)
    {
        animateOcu = true;
        for (vector<int>::iterator it=poseCoords.begin();it!=poseCoords.end();it++)
        {
            ocudu->animate.initElem(static_cast<ocudump::PoseCoord>(*it), -1, 1, 6);
        }
    }

    for (int i = 0; i < 1e3; ++i) {
        ocudu->getPose();
        ocudu->print();
        MySleep(1e3/60);
    }

    delete ocudu;
}

/**
 * Prints the usage for the program.
 */
void printUsage(int argc, char** argv)
{
    cout << "Usage: dumpTest [-d] [-c]" << endl;
    cout << "-d starts in debug mode, which will run properly without a connected rift" << endl;
    cout << "-c allows you to specify a list or range (eg 0,1,2 or 0-2) of pose coordinates that will become animated" << endl;
}

