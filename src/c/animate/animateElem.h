#include <map>

#include "main/ocudump.h"

namespace ocudump {
namespace animate {

class AnimateElem
{
public:
    AnimateElem();
    AnimateElem(float low, float high, int period);
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
