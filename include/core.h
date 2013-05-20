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

#include <boost/shared_ptr.hpp>

#include "platform.h"

namespace stratum {
    class Graphic;
}
    


namespace stratum
{
    class Core
    {
    public:
        virtual void initialize() = 0;

        virtual Graphic* createGraphic();
    }

    DllExport Core* CreateCore();
}

#endif // CORE_H
