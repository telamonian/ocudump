#ifndef ANIMATE_ANIMATEENUM_H_
#define ANIMATE_ANIMATEENUM_H_

#include <map>

#include "enum.h"

namespace ocudump {
namespace animate {

class AnimateElem
{
public:
//    AnimateElem();
    AnimateElem(float low=-1, float high=1, int period=600);
    AnimateElem(AnimateElem& elem);
    AnimateElem(const AnimateElem& elem);
    ~AnimateElem();

    AnimateElem& operator=(AnimateElem tmp);

    float getElem();
    // testing function to look at current elem value without altering anything (ie, counter, etc)
    float peekElem();

private:
    void init();
    void fixBaseline();

public:
    float low;
    float high;
    int period;

private:
    int counter;
    float* currentBaseline;
    int sign;
    float step;
};

typedef std::map<ocudump::PoseCoord,AnimateElem> ElemMap;

}
}

#endif /* ANIMATE_ANIMATEENUM_H_ */
