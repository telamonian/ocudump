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
    ~AnimateElem();

    float getElem();

private:
    void init();

public:
    float low;
    float high;
    int period;

private:
    int counter;
    int sign;
    int step;
};

typedef std::map<ocudump::PoseCoord,AnimateElem> ElemMap;

}
}

#endif /* ANIMATE_ANIMATEENUM_H_ */
