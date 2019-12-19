
#include <TerrainLib/PlanetSurface.h>
#include <TerrainLib/PlanetCoordinateSystem.h>

#include <map>

#include <iostream>

using namespace std;
using namespace tl;
using namespace glm;

PlanetSurface::PlanetSurface(SurfaceConfig config) : _config(config)
{
    _coordinateSystem = make_shared<PlanetCoordinateSystem>(_config.resolution);
    initRegions();
}

void PlanetSurface::setConfig(SurfaceConfig config)
{
	if (config.resolution != _config.resolution) {
		_config = config;
		_coordinateSystem = make_shared<PlanetCoordinateSystem>(_config.resolution);
		initRegions();
	} else if (config.jitter != _config.jitter || config.showFaceColor != _config.showFaceColor) {
		for (int i = 0; i < _regions.size(); ++i) {
			SurfaceRegion region = _regions[i];
			if (config.jitter != _config.jitter) {
				region.randomizeLocalPoint(config.jitter);
			} else {
				if (config.showFaceColor) {
					region.setColor(getFaceColorForRegion(region));
				} else {
					region.randomizeColor();
				}
			}
			_regions[i] = region;
		}
	}
	_config = config;
}

SurfaceRegion PlanetSurface::getRegion(RegionID regionId) const
{
    if (regionId != INVALID_REGION_ID && regionId < _coordinateSystem->getTotalRegionCount()) {
        return _regions[regionId];
    }
    return SurfaceRegion();
}

SurfaceRegion PlanetSurface::getNearestRegionByPoint(FaceID faceId, glm::vec2 faceCoords, bool *onEdge)
{
	SurfaceRegion closestRegion = getRegion(faceId, faceCoords);
	vec3 act3dPosition = _coordinateSystem->localFaceCoordsToGlobal(faceId, faceCoords);

	map<float, SurfaceRegion> sortedNeighbors;
	sortedNeighbors[distance(closestRegion.get3dPosition(), act3dPosition)] = closestRegion;

	for (auto neighbor : getRegionNeighbors(closestRegion)) {
		sortedNeighbors[distance(neighbor.get3dPosition(), act3dPosition)] = neighbor;
	}

	auto closestDistance        = sortedNeighbors.begin()->first;
	auto secondCloseestDistance = (++sortedNeighbors.begin())->first;
	auto closestPosition        = sortedNeighbors.begin()->second.get3dPosition();
	auto secondCloseestposition = (++sortedNeighbors.begin())->second.get3dPosition();

	auto pres = (1.0 / double(10 * _config.resolution));

	vec3 n1 = cross(closestPosition, secondCloseestposition);
	vec3 n2 = normalize(cross(n1, 0.5f * (normalize(closestPosition) + normalize(secondCloseestposition))));
	auto b = abs(dot(act3dPosition, n2));

	*onEdge = closestDistance < pres || b < pres;
	return sortedNeighbors.begin()->second;
}

vector<SurfaceRegion> PlanetSurface::getRegionNeighbors(SurfaceRegion region)
{
    vector<SurfaceRegion> res;
    for (int offsetY = -1; offsetY <= 1; ++offsetY) {
        for (int offsetX = -1; offsetX <= 1; ++offsetX) {
            if (offsetX == 0 && offsetY == 0) {
                continue;
            }

			auto offset = ivec2(region.getGridCoords()) + ivec2(offsetX, offsetY);

			SurfaceRegion neighbor = getRegion(region.getFaceId(), offset);
            if (!neighbor.isInvalid()) {
                res.push_back(neighbor);
            }
        }
    }
    return res;
}

// ============================== Private ======================================

void PlanetSurface::initRegions()
{
	_regions.clear();
    for (RegionID i = 0; i < _coordinateSystem->getTotalRegionCount(); ++i) {
        SurfaceRegion r = SurfaceRegion(_coordinateSystem, i);
		r.randomizeLocalPoint(_config.jitter);
		if (_config.showFaceColor) {
			r.setColor(getFaceColorForRegion(r));
		}
		_regions.push_back(r);
    }
}

glm::uvec4 PlanetSurface::getFaceColorForRegion(SurfaceRegion region)
{
	uvec4 color = uvec4(255, 255, 255, 0);
	switch (region.getFaceId())
	{
		case FACE_FRONT: color = uvec4(71, 220, 54, 0); break;
		case FACE_RIGHT: color = uvec4(220, 54, 76, 0); break;
		case FACE_BACK:  color = uvec4(220, 132, 54, 0); break;
		case FACE_LEFT:  color = uvec4(51, 188, 255, 0); break;
		case FACE_NORTH: color = uvec4(255, 204, 51, 0); break;
		case FACE_SOUTH: color = uvec4(137, 54, 220, 0); break;
	}
	float c = float(region.getId() % (_coordinateSystem->getTotalRegionCount() / 6)) / float(_config.resolution * _config.resolution);
	return mix(color, uvec4(c * 255, c * 255, c * 255, 1), 0.5);
}
