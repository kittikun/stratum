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

#ifndef GRAPHIC_IMPL_H
#define GRAPHIC_IMPL_H

#include <boost/thread.hpp>
#include <boost/utility.hpp>
#include <EGL/egl.h>

#include <graphic.h>

namespace stratum
{
    class GraphicImpl : public Graphic, private boost::noncopyable
    {
    private:
        struct Context
        {
            EGLDisplay eglDisplay;
            EGLSurface eglSurface;
            EGLContext eglContext;
        };

    public:
        const bool initialize(const GraphicOptions& options);
        void cleanUp();

    private:
        bool createEGL(const GraphicOptions& options);
        void printGLInfo();
        void renderLoop();

    private:
        boost::thread_group m_threads;
        Context m_context;
    };

} // namespace stratum

#endif // GRAPHIC_IMPL_H
