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

#ifndef PLATFORM_H
#define PLATFORM_H

#include <EGL/egl.h>


#if defined(_WIN32)
    #include "win.h"
#elif defined(__linux__)
    #include "linux.h"
#else
    #error "unknown platform"
#endif

namespace Stratum
{
    struct NativeInfo
    {
        EGLNativeDisplayType display;
        EGLNativeWindowType window;
    };

    extern const bool createNativeWindow(const uint32_t width, const uint32_t height, NativeInfo& outInfo);
    extern const bool destroyNativeWindow(const NativeInfo& info);
    extern void initializeInput();
    extern const bool inputRead();

} // namespace Stratum

#endif // PLATFORM_H
