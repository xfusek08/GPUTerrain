#pragma once

#include <memory>

#include <GeoPlanetLib/geoplanetlib_export.h>

#include <GeoPlanetLib/AbstactFactory.h>
#include <GeoPlanetLib/Surface.h>

namespace gp
{
    class GEOPLANETLIB_EXPORT SurfaceModifier : public AbstractFactoryBase<SurfaceModifier>
    {
    public:
        virtual bool apply(std::shared_ptr<Surface> surface) = 0;
    };
}
