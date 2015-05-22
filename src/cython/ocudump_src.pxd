cdef extern from "ocudump.h" namespace "ocudump":
    cdef cppclass CppOcudump "ocudump::Ocudump":
        CppOcudump()
        void getPose()
        
        vector[float] pose
        bool positionTracked
        
cdef extern from "ocudump.h" namespace "ocudump":
    cdef cppclass CppOcudumpDebug "ocudump::OcudumpDebug":
        CppOcudumpDebug()
        void getPose()
        
        vector[float] pose
        bool positionTracked