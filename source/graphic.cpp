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

#include "graphic.h"

#include <EGL/eglplatform.h>
#include <GLES2/gl2.h>

#include "platform/platform.h"
#include "log.h"

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
    EGLint major, minor;
    EGLint configSize; 
    EGLConfig eglConfig; 
    EGLBoolean ret; 

    EGLint eglConfigAttribs[] = { 
        EGL_RED_SIZE, 8, 
        EGL_GREEN_SIZE, 8, 
        EGL_BLUE_SIZE, 8, 
        EGL_ALPHA_SIZE, 8, 
        EGL_DEPTH_SIZE, 16, 
        EGL_RENDERABLE_TYPE, EGL_OPENGL_ES2_BIT, 
        EGL_SURFACE_TYPE, EGL_WINDOW_BIT,
        EGL_NONE
    };

    EGLint eglContextAttribs[] = { 
        EGL_CONTEXT_CLIENT_VERSION, 2
    };

    if (!createNativeWindow(m_context.nativeInfo)) {
        LOGC << "createNativeWindow failed.";
        return false;
    }

    m_context.eglDisplay = eglGetDisplay(m_context.nativeInfo.display);
    LOGC << "eglGetError " << std::hex << eglGetError();
    LOG << "eglDisplay " << std::hex << m_context.eglDisplay;
    assert(m_context.eglDisplay != EGL_NO_DISPLAY);
    ret = eglInitialize(m_context.eglDisplay, &major, &minor);
    LOGC << "eglGetError " << std::hex << eglGetError();
    if (ret != EGL_TRUE) {
        LOGC << "eglInitialize failed.";
        return false;
    }

    ret = eglChooseConfig(m_context.eglDisplay, eglConfigAttribs, &eglConfig, 1, &configSize);
    LOGC << "eglGetError " << std::hex << eglGetError();
    if (ret != EGL_TRUE) {
        LOGC << "eglChooseConfig failed.";
        return false;
    }

    m_context.eglSurface = eglCreateWindowSurface(m_context.nativeInfo.display, eglConfig, m_context.nativeInfo.window, NULL);
    LOG << "eglSurface " << std::hex << m_context.eglSurface;
    LOGC << "eglGetError " << std::hex << eglGetError();
    assert(m_context.eglSurface); 
    m_context.eglContext = eglCreateContext(m_context.eglDisplay, eglConfig, EGL_NO_CONTEXT, eglContextAttribs);
    LOGC << "eglGetError " << std::hex << eglGetError();
    assert(m_context.eglContext);
    ret = eglMakeCurrent(m_context.eglDisplay, m_context.eglSurface, m_context.eglSurface, m_context.eglContext);
    LOGC << "eglGetError " << std::hex << eglGetError();
    if (ret != EGL_TRUE) {
        LOGC << "eglMakeCurrent failed.";
        return false;
    }
}

bool Graphic::initialize()
{
    bool ret;

    LOGN << "creating renderer main thread";
    ret = createContext();
    m_threads.create_thread(boost::bind(&Graphic::RenderLoop, this));

    return ret;
}

void Graphic::RenderLoop()
{
    while (1) {
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        LOG << "swap buffer";
        EGLBoolean ret = eglSwapBuffers(m_context.eglDisplay, m_context.eglSurface);
        LOGC << ret;
        LOGC <<  std::hex << eglGetError();
        assert(ret);
    }
}

} // namespace Stratum
