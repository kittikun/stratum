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

#include "graphic_impl.h"

#include <EGL/eglplatform.h>
#include <GLES2/gl2.h>

#include "log.h"
#include "utility.h"

namespace stratum
{
    void GraphicImpl::cleanUp()
    {
        eglMakeCurrent(m_context.eglDisplay, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
        eglDestroyContext(m_context.eglDisplay, m_context.eglContext);
        eglDestroySurface(m_context.eglDisplay, m_context.eglSurface);
        eglTerminate(m_context.eglDisplay);

        m_platform->destroyNativeWindow();
    }

    bool GraphicImpl::createEGL(const GraphicOptions& options)
    {
        const char* str;
        EGLBoolean ret;
        EGLConfig eglConfig;
        EGLContext eglContext;
        EGLDisplay eglDisplay;
        EGLint configSize;
        EGLSurface eglSurface;

        EGLint eglConfigAttribs[] = {
            EGL_RED_SIZE, 8,
            EGL_GREEN_SIZE, 8,
            EGL_BLUE_SIZE, 8,
            EGL_DEPTH_SIZE, options.depthSize,
            EGL_RENDERABLE_TYPE, EGL_OPENGL_ES2_BIT,
            EGL_NONE
        };

        EGLint eglContextAttribs[] = {
            EGL_CONTEXT_CLIENT_VERSION, 2,
            EGL_NONE
        };

        LOGGFX << "Initializiting EGL..";

        eglDisplay = eglGetDisplay(m_platform->getNativeDisplay());
        if (eglDisplay == EGL_NO_DISPLAY) {
            return VERIFYEGL();
        }

        ret = eglInitialize(eglDisplay, NULL, NULL);
        if (ret != EGL_TRUE) {
            return VERIFYEGL();
        }

        str = eglQueryString(eglDisplay, EGL_VERSION);
        LOGGFX << "EGL_VERSION = " << str;

        str = eglQueryString(eglDisplay, EGL_VENDOR);
        LOGGFX << "EGL_VENDOR = " << str;

        str = eglQueryString(eglDisplay, EGL_EXTENSIONS);
        LOGGFX << "EGL_EXTENSIONS = " << str;

        str = eglQueryString(eglDisplay, EGL_CLIENT_APIS);
        LOGGFX << "EGL_CLIENT_APIS = " << nullToStr(str);

        ret = eglChooseConfig(eglDisplay, eglConfigAttribs, &eglConfig, 1, &configSize);
        assert(configSize == 1);
        if (ret != EGL_TRUE) {
            return VERIFYEGL();
        }

        m_platform->createNativeWindow(options, eglConfig);

        ret = eglBindAPI(EGL_OPENGL_ES_API);
        if (ret != EGL_TRUE) {
            return VERIFYEGL();
        }

        eglSurface = eglCreateWindowSurface(eglDisplay, eglConfig, m_platform->getNativeWindow(), NULL);
        if (eglSurface == EGL_NO_SURFACE) {
            return VERIFYEGL();
        }

        eglContext = eglCreateContext(eglDisplay, eglConfig, EGL_NO_CONTEXT, eglContextAttribs);
        if (eglContext == EGL_NO_CONTEXT) {
            return VERIFYEGL();
        }

//      ret = eglMakeCurrent(eglDisplay, eglSurface, eglSurface, eglContext);
//      if (ret != EGL_TRUE) {
//          return VERIFYEGL();
//      }

        m_context.eglDisplay = eglDisplay;
        m_context.eglSurface = eglSurface;
        m_context.eglContext = eglContext;

        return true;
    }

    void GraphicImpl::printGLInfo()
    {
//      LOGGFX << "GL_RENDERER " << (char)glGetString(GL_RENDERER);
//      LOGGFX << "GL_VERSION " << glGetString(GL_RENDERER);
//      LOGGFX << "GL_VENDOR " << glGetString(GL_RENDERER);
//      LOGGFX << "GL_EXTENSIONS " << glGetString(GL_RENDERER);
    }

    const bool GraphicImpl::initialize(const GraphicOptions& options, boost::shared_ptr<Platform> platform)
    {
        bool ret;

        m_platform = platform;
        ret = createEGL(options);
        if (!ret) {
            LOGC << "Could not initialize EGL engine.";
            return ret;
        }

        printGLInfo();

        return ret;
    }

    void GraphicImpl::renderLoop()
    {
        bool ret;
        LOGGFX << "Entering render loop";
        LOGGFX << m_context.eglDisplay << " " << m_context.eglSurface << " " << m_context.eglSurface << " " << m_context.eglContext;
        ret = eglMakeCurrent(m_context.eglDisplay, m_context.eglSurface, m_context.eglSurface, m_context.eglContext);
        VERIFYEGL();
        LOGGFX << "Entering render loopu";

        while (1) {
            glClearColor(0.0f, 1.0f, 0.0f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);
            ret = VERIFYGL();

            eglSwapBuffers(m_context.eglDisplay, m_context.eglSurface);
            LOGGFX << "swap";
            ret = VERIFYEGL();
            assert(ret);
        }
    }

} // namespace stratum
