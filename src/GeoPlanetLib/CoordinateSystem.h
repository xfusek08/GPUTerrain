#pragma once

namespace gp
{
    class CoordinateSystem
    {
        private:
            unsigned int resolution;
        public:
            CoordinateSystem(unsigned int resolution);

            inline unsigned int getResolution() { return resolution; }

			unsigned int totalRegionCount();
    };
}
