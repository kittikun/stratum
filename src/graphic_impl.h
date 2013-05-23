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

#include <boost/shared_ptr.hpp>
#include <boost/utility.hpp>
#include <EGL/egl.h>

#include "options.h"
#include "platform\platform_impl.h"

namespace stratum
{
    struct GraphicContext
    {
        EGLDisplay eglDisplay;
        EGLSurface eglSurface;
        EGLContext eglContext;
    };

    class GraphicImpl : private boost::noncopyable
    {
    public:
        const bool initialize(const GraphicOptions& options, boost::shared_ptr<Platform> platform);
        void cleanUp();
        void renderLoop();

    private:
        bool createEGL(const GraphicOptions& options);
        void printGLInfo();

    private:
        GraphicContext m_context;
        boost::shared_ptr<Platform> m_platform;
    };

} // namespace stratum

#endif // GRAPHIC_IMPL_H
