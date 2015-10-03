#ifndef ANIMATE_ANIMATE_H_
#define ANIMATE_ANIMATE_H_

#include <map>
#include <vector>

#include "enum.h"
#include "animate/animateElem.h"

namespace ocudump {
namespace animate {

class Animate
{
public:
    Animate();
    virtual ~Animate();

    void initElem(ocudump::PoseCoord poseCoord, float low, float high, int period);
    std::vector<float> getPoseOffset();

    // iterators
    typedef ElemMap::iterator iterator;
    iterator begin() {return elemMap.begin();}
    iterator end() {return elemMap.end();}

private:
    ElemMap elemMap;
};

}
}

#endif /* ANIMATE_ANIMATE_H_ */
