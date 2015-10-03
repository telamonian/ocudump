#include "animate/animateElem.h"

namespace ocudump {
namespace animate {

//AnimateElem::AnimateElem(): low(0.0), high(0.0), period(0), counter(0), sign(1), step(0)
//{
//    init();
//}

AnimateElem::AnimateElem(float low, float high, int period): low(low), high(high), period(period), counter(0), sign(1), step(0)
{
    init();
}

AnimateElem::~AnimateElem()
{
}

void AnimateElem::init()
{
    step = (high - low)/step;
}

float AnimateElem::getElem()
{
    counter++;
    if (counter > period) sign*=-1;
    return sign*step;
}

}
}
