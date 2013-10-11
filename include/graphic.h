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

#ifndef GRAPHIC_H
#define GRAPHIC_H

#include <boost/shared_ptr.hpp>

#include <platform.h>

namespace stratum
{
    class Graphic
    {
    public:
        virtual const bool initialize(const uint32_t width, const uint32_t height) = 0;
        virtual void cleanUp() = 0;
    };

    DllExport boost::shared_ptr<Graphic> getGraphic();

} // namespace stratum

#endif // GRAPHIC_H
