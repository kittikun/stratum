//  This file is part of Stratum.
//
//  Stratum is free software: you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation, either version 3 of the License, or
//  (at your option) any later version.
//
//  Stratum is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//
//  You should have received a copy of the GNU General Public License
//  along with Stratum.  If not, see <http://www.gnu.org/licenses/>.

#ifndef GRAPHIC_H
#define GRAPHIC_H

#include <boost/thread.hpp>
#include <EGL/egl.h>

#include "platform/platform.h"

namespace Stratum
{
    class Graphic
    {
    private:
        struct Context
        {
            NativeInfo nativeInfo;
            EGLDisplay eglDisplay; 
            EGLSurface eglSurface; 
            EGLContext eglContext; 
        };

    public:
        bool initialize();
        void cleanUp();

    private:
        bool createContext();
        void RenderLoop();

    private:
        boost::thread_group m_threads;
        Context m_context;
    };

} // namespace Stratum

#endif // GRAPHIC_H
