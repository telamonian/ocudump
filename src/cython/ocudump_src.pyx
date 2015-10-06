cdef class Ocudump:
# boilerplate
    cdef CppOcudump* thisptr      # hold a C++ instance which we're wrapping
    def __cinit__(self):
        self.thisptr = new CppOcudump()
    def __dealloc__(self):
        del self.thisptr

# functions
    def init(self):
        return self.thisptr.init()

    def initAnimateElement(self, PoseCoord poseCoord, float low, float high, int period):
        self.thisptr.initAnimateElement(poseCoord, low, high, period)
    
    def getPose(self):
        self.thisptr.getPose()
        
    def getPoseAnimated(self):
        self.thisptr.getPoseAnimated()
    
    def printInfo(self):
        self.thisptr.ocudumpPrint()

# properties
    property pose:
        def __get__(self): 
            return self.thisptr.pose
#         def __set__(self, pose): self.thisptr.pose = pose
        
    property positionTracked:
        def __get__(self): 
            return self.thisptr.positionTracked
        
cdef class OcudumpDebug:
# boilerplate
    cdef CppOcudumpDebug* thisptr      # hold a C++ instance which we're wrapping
    def __cinit__(self):
        self.thisptr = new CppOcudumpDebug()
    def __dealloc__(self):
        del self.thisptr
    
# functions
    def init(self):
        return self.thisptr.init()
    
    def initAnimateElement(self, PoseCoord poseCoord, float low, float high, int period):
        self.thisptr.initAnimateElement(poseCoord, low, high, period)
    
    def getPose(self):
        self.thisptr.getPose()
    
    def getPoseAnimated(self):
        self.thisptr.getPoseAnimated()

    def printInfo(self):
        self.thisptr.ocudumpPrint()

# properties
    property pose:
        def __get__(self): 
            return self.thisptr.pose
        
    property positionTracked:
        def __get__(self): 
            return self.thisptr.positionTracked