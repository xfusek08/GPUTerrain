
#include <GeoPlanetLib/Region.h>

using namespace gp;

RegionAttribute Region::getAttribute(RegionAttributeType type)
{
    RegionAttribute res;
    auto it = attributes.find(type);
    if (it == attributes.end()) {
        res.isValid = false;
    } else {
        res.isValid = true;
        res.data = it->second;
    }
    return res;
}

void Region::setAttribute(RegionAttributeType type, RegionAttributeData data)
{
    attributes[type] = data;
}

void Region::unsetAttribute(RegionAttributeType type)
{
    attributes.erase(type);
}