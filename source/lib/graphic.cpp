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

#include "graphic.h"

#include <EGL/eglplatform.h>
#include <GLES2/gl2.h>

#include "platform/platform.h"
#include "log.h"
#include "utility.h"

namespace Stratum
{

void Graphic::cleanUp()
{
    m_threads.join_all();
    eglMakeCurrent(m_context.eglDisplay, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
    eglDestroyContext(m_context.nativeInfo.display, m_context.eglContext);
    eglDestroySurface(m_context.nativeInfo.display, m_context.eglSurface);
    eglTerminate(m_context.eglDisplay);

    destroyNativeWindow(m_context.nativeInfo);
}

bool Graphic::createContext()
{
    const char* str;
    EGLBoolean ret; 
    EGLConfig eglConfig; 
    EGLContext eglContext;
    EGLDisplay eglDisplay;
    EGLint configSize; 
    EGLSurface eglSurface;

    EGLint eglConfigAttribs[] = { 
        EGL_RED_SIZE, 1,
        EGL_GREEN_SIZE, 1,
        EGL_BLUE_SIZE, 1,
        EGL_DEPTH_SIZE, 1,
        EGL_RENDERABLE_TYPE, EGL_OPENGL_ES2_BIT,
        EGL_NONE
    };

    EGLint eglContextAttribs[] = { 
        EGL_CONTEXT_CLIENT_VERSION, 2,
        EGL_NONE
    };

    eglDisplay = eglGetDisplay(m_context.nativeInfo.display);
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
    LOGGFX << "EGL_CLIENT_APIS = " << str;

    ret = eglBindAPI(EGL_OPENGL_ES_API);
    if (ret != EGL_TRUE) {
        return VERIFYEGL();
    }

    ret = eglChooseConfig(eglDisplay, eglConfigAttribs, &eglConfig, 1, &configSize);
    assert(configSize == 1);
    if (ret != EGL_TRUE) {
        return VERIFYEGL();
    }

    eglSurface = eglCreateWindowSurface(eglDisplay, eglConfig, m_context.nativeInfo.window, NULL);
    if (eglSurface == EGL_NO_SURFACE) {
        return VERIFYEGL();
    }

    eglContext = eglCreateContext(eglDisplay, eglConfig, EGL_NO_CONTEXT, eglContextAttribs);
    if (eglContext == EGL_NO_CONTEXT) {
        return VERIFYEGL();
    }

    ret = eglMakeCurrent(eglDisplay, eglSurface, eglSurface, eglContext);
    if (ret != EGL_TRUE) {
        return VERIFYEGL();
    }

    m_context.eglDisplay = eglDisplay;
    m_context.eglSurface = eglSurface;
    m_context.eglContext = eglContext;

    return true;
}

const bool Graphic::initialize(const uint32_t width, const uint32_t height)
{
    bool ret;

    if (!createNativeWindow(width, height, m_context.nativeInfo)) {
        LOGC << "createNativeWindow failed.";
        return false;
    }

    ret = createContext();
    if (!ret) {
        LOGC << "Could not initialize graphic engine.";
        return ret;
    }

    LOGGFX << "Creating graphic thread..";
    m_threads.create_thread(boost::bind(&Graphic::RenderLoop, this));

    return ret;
}

void Graphic::RenderLoop()
{
    bool ret;

    //while (1) {
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        LOGGFX << "swap buffer";
        eglSwapBuffers(m_context.eglDisplay, m_context.eglSurface);
        ret = VERIFYGL();
        assert(ret);
    //}
}

} // namespace Stratum
