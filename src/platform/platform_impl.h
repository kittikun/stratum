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

#ifndef PLATFORM_IMPL_H
#define PLATFORM_IMPL_H

#include <boost/shared_ptr.hpp>
#include <boost/utility.hpp>
#include <EGL/egl.h>
#include <stdint.h>

#if defined(_WIN32)
    #include "win.h"
#elif defined(__linux__)
    #include "linux.h"
#else
    #error "unknown platform"
#endif

namespace stratum
{
    struct GraphicOptions;

    class Platform
    {
    public:
        static boost::shared_ptr<Platform> CreatePlatform();
        virtual EGLNativeDisplayType getNativeDisplay() = 0;
        virtual EGLNativeWindowType getNativeWindow() = 0;

        virtual const bool createNativeWindow(const GraphicOptions& options, EGLConfig eglConfig) = 0;
        virtual const bool destroyNativeWindow() = 0;

        virtual const bool initializeInput() = 0;
        virtual const bool inputRead() = 0;
    };

} // namespace stratum

#endif // PLATFORM_IMPL_H
