cdef extern from "enum.h" namespace "ocudump":
    cdef enum _PoseCoord:
        xrot = 0
        yrot = 1
        zrot = 2
        x = 3
        y = 4
        z = 5
    ctypedef _PoseCoord PoseCoord

cdef extern from "main/ocudump.h" namespace "ocudump::main":
    cdef cppclass CppOcudump "ocudump::main::Ocudump":
        CppOcudump()
        void initAnimateElement(PoseCoord,float,float,int)
        void getPose()
        void getPoseAnimated()
        void ocudumpPrint 'print' ()
        
        vector[float] pose
        bool positionTracked
        
cdef extern from "main/ocudump.h" namespace "ocudump::main":
    cdef cppclass CppOcudumpDebug "ocudump::main::OcudumpDebug":
        CppOcudumpDebug()
        void initAnimateElement(PoseCoord,float,float,int)
        void getPose()
        void getPoseAnimated()
        void ocudumpPrint 'print' ()
        
        vector[float] pose
        bool positionTracked