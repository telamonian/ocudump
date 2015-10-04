#include <algorithm>

#include "animate/animateElem.h"

using std::swap;

namespace ocudump {
namespace animate {

//AnimateElem::AnimateElem(): low(0.0), high(0.0), period(0), counter(0), sign(1), step(0)
//{
//    init();
//}

AnimateElem::AnimateElem(float low, float high, int period): low(low), high(high), period(period), counter(0), currentBaseline(NULL), sign(1), step(0.0)
{
    init();
}

// copy constructor to deal with the raw member pointer currentBaseline
AnimateElem::AnimateElem(AnimateElem& other): low(other.low), high(other.high), period(other.period), counter(other.counter), currentBaseline(NULL), sign(other.sign), step(other.step)
{
    fixBaseline();
}

// copy constructor to deal with the raw member pointer currentBaseline
AnimateElem::AnimateElem(const AnimateElem& other): low(other.low), high(other.high), period(other.period), counter(other.counter), currentBaseline(NULL), sign(other.sign), step(other.step)
{
    fixBaseline();
}


AnimateElem::~AnimateElem()
{
}

// assignment operator to deal with the raw member pointer currentBaseline
AnimateElem& AnimateElem::operator=(AnimateElem tmp)
{
    swap(low, tmp.low);
    swap(high, tmp.high);
    swap(period, tmp.period);
    swap(counter, tmp.counter);
    swap(sign, tmp.sign);
    swap(step, tmp.step);
    fixBaseline();
    return *this;
}

void AnimateElem::init()
{
    counter = period/2;
    step = (high - low)/period;
    currentBaseline = &low;
}

void AnimateElem::fixBaseline()
{
    currentBaseline = sign > 0 ? &low : &high;
}

float AnimateElem::getElem()
{
    counter++;
    if (counter > period)
    {
        sign*=-1;
        counter = 0;
        fixBaseline();
    }
    return *currentBaseline + sign*counter*step;
}

float AnimateElem::peekElem()
{
    return *currentBaseline;// + sign*counter*step;
}

}
}
