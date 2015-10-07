#!/usr/bin/env python
import os,sys
from time import sleep

# t_e block accounts for path differences on windows
try:
    from src.cython.ocudump import Ocudump, OcudumpDebug
except ImportError:
    try:
        from src.cython.Release.ocudump import Ocudump, OcudumpDebug
    except ImportError:
        from src.cython.Debug.ocudump import Ocudump, OcudumpDebug

# globals for cmd options
debug = False
poseCoords = []

def parseIntListFromArg(arg):
    vals = arg.split('-')
    if len(vals)==2:
        return range(int(vals[0]), int(vals[1]))
    elif len(vals) > 2:
        raise
    else:
        vals = arg.split(',')
        return [int(x) for x in vals]

def parseArgs(argv):
    global debug,poseCoords
    i = 1
    while i < len(argv):
        if argv[i]=='-h' or argv[i]=='--help':
            printUsage()
            sys.exit()
        elif argv[i]=='-d':
            debug = True
        elif argv[i]=='-c':
            i+=1
            poseCoords = parseIntListFromArg(argv[i])
        i+=1

def printUsage():
    print "Usage: python dumpTest [-d] [-c]\n"
    print "-d starts in debug mode, which will run properly without a connected rift\n"
    print "-c allows you to specify a list or range (eg 0,1,2 or 0-2) of pose coordinates that will become animated\n"

if __name__=='__main__':
    animateOcudump = False
    parseArgs(sys.argv)
    
    if debug:
        o = OcudumpDebug()
    else:
        o = Ocudump()
    if not o.init():
        sys.exit()
    
    if len(poseCoords) > 0:
        animateOcudump = True
        for poseCoord in poseCoords:
            o.initAnimateElement(poseCoord, -1, 1, 60)
    
    for i in range(int(1e3)):
        o.getPose()
        o.printInfo()
        sleep(1/60)
