#pragma once

#include <GeoPlanetLib/modifiers/FaceColorModifier.h>

using namespace gp;
using namespace gp::modifiers;
using namespace glm;

FaceColorModifier::FaceColorModifier()
{
}

bool FaceColorModifier::apply(std::shared_ptr<Surface> surface)
{
    unsigned int regPerFace = surface->getResolution() * surface->getResolution();

	for (auto region : surface->getRegions()) {
        uvec3 color = uvec3(255, 255, 255);
        switch (region->position.getFaceID())
        {
            case FACE_FRONT: color = uvec3(71, 220, 54); break;
            case FACE_RIGHT: color = uvec3(220, 54, 76); break;
            case FACE_BACK:  color = uvec3(220, 132, 54); break;
            case FACE_LEFT:  color = uvec3(51, 188, 255); break;
            case FACE_NORTH: color = uvec3(255, 204, 51); break;
            case FACE_SOUTH: color = uvec3(137, 54, 220); break;
        }

        float c = float(region->getID() % regPerFace) / float(regPerFace);

        RegionAttribute attr = RegionAttribute();
        attr.data.uVector3 = mix(color, uvec3(255.0f * vec3(c)), 0.5);

        region->attributes[RegionAttributeType::Color] = attr;
    }
	return true;
}
