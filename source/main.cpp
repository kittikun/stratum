//  This file is part of Stratum.
//
//  Stratum is free software: you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation, either version 3 of the License, or
//  (at your option) any later version.
//
//  Foobar is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//
//  You should have received a copy of the GNU General Public License
//  along with Stratum.  If not, see <http://www.gnu.org/licenses/>.

#define BOOST_LIB_DIAGNOSTIC

#include <boost/thread.hpp>
#include <EGL/egl.h>
#include <EGL/eglplatform.h>

#include "platform/platform.h"
#include "log.h"

int main(int, char**)
{
    Stratum::NativeInfo info;
    EGLint major, minor; 
    EGLDisplay display; 
    EGLint configSize; 
    EGLConfig eglConfig; 
    EGLSurface eglSurface; 
    EGLContext eglContext; 
    EGLNativeDisplayType nativeDisplay;
    EGLNativeWindowType nativeWindow;
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

    EGLint eglContectAttribs[] = { 
        EGL_CONTEXT_CLIENT_VERSION, 1
    }; 
 
    Stratum::CreateWindow(info);
       
    display = eglGetDisplay(info.display);
    assert(display != EGL_NO_DISPLAY);
    ret = eglInitialize(display, &major, &minor);
    assert(ret == EGL_TRUE);
    ret = eglChooseConfig(display, eglConfigAttribs, &eglConfig, 1, &configSize);
    assert(ret == EGL_TRUE);
    eglSurface = eglCreateWindowSurface(info.display, eglConfig, info.window, NULL);
//  eglContext = eglCreateContext(display, eglConfig, EGL_NO_CONTEXT, eglContectAttribs);
//  ret = eglMakeCurrent(display, eglSurface, eglSurface, eglContext);
//  assert(ret == EGL_TRUE);
    
    return 0; 
}
