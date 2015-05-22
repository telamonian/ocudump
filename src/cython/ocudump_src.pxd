cdef extern from "ocudump.h" namespace "ocudump":
    cdef cppclass CppOcudump "ocudump::Ocudump":
        CppOcudump()
        void getPose()
        
        vector[float] pose
        bool positionTracked