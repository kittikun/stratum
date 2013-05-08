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
    EGLint major, minor;
    EGLint configSize; 
    EGLConfig eglConfig; 
    EGLBoolean ret; 

    EGLint eglConfigAttribs[] = { 
        EGL_BUFFER_SIZE, 32, 
        EGL_DEPTH_SIZE, 16, 
        EGL_RENDERABLE_TYPE, EGL_OPENGL_ES2_BIT, 
        EGL_SURFACE_TYPE, EGL_WINDOW_BIT,
        EGL_NONE
    };

    EGLint eglSurfaceAttribs[] = {
        EGL_RENDER_BUFFER, EGL_BACK_BUFFER,
        EGL_NONE
    };

    EGLint eglContextAttribs[] = { 
        EGL_CONTEXT_CLIENT_VERSION, 2,
        EGL_NONE
    };

    if (!createNativeWindow(m_context.nativeInfo)) {
        LOGC << "createNativeWindow failed.";
        return false;
    }

    m_context.eglDisplay = eglGetDisplay(m_context.nativeInfo.display);
    if (m_context.eglDisplay == EGL_NO_DISPLAY) {
        return VERIFYEGL();
    }

    ret = eglInitialize(m_context.eglDisplay, &major, &minor);
    if (ret != EGL_TRUE) {
        return VERIFYEGL();
    }

    LOGGFX << "EGL " << major << "." << minor << " initialized.";

    ret = eglBindAPI(EGL_OPENGL_ES_API);
    if (ret != EGL_TRUE) {
        return VERIFYEGL();
    }

    ret = eglChooseConfig(m_context.eglDisplay, eglConfigAttribs, &eglConfig, 1, &configSize);
    assert(configSize == 1);
    if (ret != EGL_TRUE) {
        return VERIFYEGL();
    }

    m_context.eglSurface = eglCreateWindowSurface(m_context.eglDisplay, eglConfig, m_context.nativeInfo.window, eglSurfaceAttribs);
    if (m_context.eglSurface == EGL_NO_SURFACE) {
        return VERIFYEGL();
    }

    m_context.eglContext = eglCreateContext(m_context.eglDisplay, eglConfig, EGL_NO_CONTEXT, eglContextAttribs);
    if (m_context.eglContext == EGL_NO_CONTEXT) {
        return VERIFYEGL();
    }

    ret = eglMakeCurrent(m_context.eglDisplay, m_context.eglSurface, m_context.eglSurface, m_context.eglContext);
    if (ret != EGL_TRUE) {
        return VERIFYEGL();
    }

    return true;
}

bool Graphic::initialize()
{
    bool ret;

    ret = createContext();
    if (!ret) {
        LOGC << "Could not initialize graphic engine.";
        return ret;
    }

    LOGGFX << "Creating thread..";
    m_threads.create_thread(boost::bind(&Graphic::RenderLoop, this));

    return ret;
}

void Graphic::RenderLoop()
{
    bool ret;

    while (1) {
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        LOGGFX << "swap buffer";
        eglSwapBuffers(m_context.eglDisplay, m_context.eglSurface);
        ret = VERIFYEGL();
        assert(ret);
    }
}

} // namespace Stratum
