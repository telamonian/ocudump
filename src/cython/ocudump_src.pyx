cdef class Ocudump:
    cdef CppOcudump* thisptr      # hold a C++ instance which we're wrapping
    def __cinit__(self):
        self.thisptr = new CppOcudump()
    def __dealloc__(self):
        del self.thisptr
    def getPose(self):
        self.thisptr.getPose()
    
    property pose:
        def __get__(self): return self.thisptr.pose
#         def __set__(self, pose): self.thisptr.pose = pose
        
    property positionTracked:
        def __get__(self): return self.thisptr.positionTracked
        
cdef class OcudumpDebug:
    cdef CppOcudumpDebug* thisptr      # hold a C++ instance which we're wrapping
    def __cinit__(self):
        self.thisptr = new CppOcudumpDebug()
    def __dealloc__(self):
        del self.thisptr
    def getPose(self):
        self.thisptr.getPose()
    
    property pose:
        def __get__(self): return self.thisptr.pose
        
    property positionTracked:
        def __get__(self): return self.thisptr.positionTracked