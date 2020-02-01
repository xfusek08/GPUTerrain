#pragma once

#include <memory>
#include <string>
#include <map>

#include <GeoPlanetLib/geoplanetlib_export.h>

#include <GeoPlanetLib/AbstactFactory.h>
#include <GeoPlanetLib/Surface.h>

namespace gp
{
    class GEOPLANETLIB_EXPORT SurfaceModifier : public AbstractFactoryBase<SurfaceModifier>
    {
        public:
            virtual bool apply(Surface surface) = 0;
    };
}
