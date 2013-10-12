//  Copyright 2013 Kitti Vongsay
//
//  This file is part of Stratum.
//
//  Stratum is free software: you can redistribute it and/or modify
//  it under the terms of the GNU Lesser General Public License as
//  published by the Free Software Foundation, either version 3 of
//  the License, or(at your option) any later version.
//
//  Stratum is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU Lesser General Public License for more details.
//
//  You should have received a copy of the GNU Lesser General Public
//  License along with Stratum.   If not, see <http://www.gnu.org/licenses/>.

#ifndef CORE_H
#define CORE_H

#include "platform.h"

namespace stratum
{
    class Core
    {
    public:
		virtual ~Core() {}
        virtual const bool initialize(const uint32_t width, const uint32_t height) = 0;
        virtual void start() = 0;
        virtual void stop() = 0;
    };

    // Only one instance is allowed
    DllExport Core* CreateCore();
}

#endif // CORE_H
