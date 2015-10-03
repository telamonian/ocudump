#include <vector>

#include "animate/animate.h"
#include "animate/animateElem.h"

using std::vector;

namespace ocudump {
namespace animate {

Animate::Animate()
{
}

Animate::~Animate()
{
}

void Animate::initElem(ocudump::PoseCoord poseCoord, float low, float high, int period)
{
    AnimateElem elem(low, high, period);
    elemMap[poseCoord] = elem;
}

std::vector<float> Animate::getPoseOffset()
{
    vector<float> po(6,0);
    for (ElemMap::iterator it=elemMap.begin();it!=elemMap.end();it++)
    {
        po[it->first] = it->second.getElem();
    }
    return po;
}

}
}
