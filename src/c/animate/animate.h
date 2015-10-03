#include <map>
#include <vector>

#include "animate/animateElem.h"
#include "main/ocudump.h"

namespace ocudump {
namespace animate {

class Animate
{
public:
    Animate();
    virtual ~Animate();

    void initElem(ocudump::PoseCoord poseCoord, float low, float high, int period);
    std::vector<float> getPoseOffset();

private:
    ElemMap elemMap;
};

}
}
