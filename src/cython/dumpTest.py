#!/usr/bin/env python

from time import sleep
try:
    from src.cython.ocudump import Ocudump
except ImportError:
    try:
        from src.cython.Release.ocudump import Ocudump
    except ImportError:
        from src.cython.Debug.ocudump import Ocudump
            

if __name__=='__main__':
    o = Ocudump()
    while True:
        o.getPose()
        print("Current pose - pitch %0.2f, yaw %0.2f, roll %0.2f, x %0.2f, y %0.2f, z %0.2f" % tuple(o.pose))
        sleep(.1)
