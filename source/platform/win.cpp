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

#ifdef _WIN32

#include "platform.h"

#include <Windows.h>

#include "../log.h"

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    return DefWindowProc(hwnd, message, wParam, lParam);
}

namespace Stratum
{

const bool createNativeWindow(NativeInfo& info)
{
    TCHAR className[] = TEXT("Stratum");
    HDC hdc;
    HWND hwnd ;
    //int  iPixelFormat;
    WNDCLASS wndclass;

    LOGN << "Creating native window..";

    wndclass.style         = CS_HREDRAW | CS_VREDRAW ;
    wndclass.lpfnWndProc   = WndProc ;
    wndclass.cbClsExtra    = 0 ;
    wndclass.cbWndExtra    = 0 ;
    wndclass.hInstance     = NULL ;
    wndclass.hIcon         = LoadIcon(NULL, IDI_APPLICATION) ;
    wndclass.hCursor       = LoadCursor(NULL, IDC_ARROW) ;
    wndclass.hbrBackground = (HBRUSH) (COLOR_WINDOW + 1) ;
    wndclass.lpszMenuName  = NULL ;
    wndclass.lpszClassName = className ;

    if (!RegisterClass(&wndclass))
    {
        LOGC << "This program requires Windows NT!";
        return 0 ;
    }

    hwnd = CreateWindowEx(NULL, className, TEXT ("Test"), WS_OVERLAPPEDWINDOW, 
        CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
        NULL, NULL, NULL, NULL);

    ShowWindow(hwnd, SW_SHOWDEFAULT);
    hdc = GetDC(hwnd);

    info.display = EGL_DEFAULT_DISPLAY;
    info.window = hwnd;

    return true;
}


//int main(int, char**)
//{
//
//    //PIXELFORMATDESCRIPTOR pfd = { 
//    //    sizeof(PIXELFORMATDESCRIPTOR),   // size of this pfd  
//    //    1,                     // version number  
//    //    PFD_DRAW_TO_WINDOW |   // support window  
//    //    PFD_SUPPORT_OPENGL |   // support OpenGL  
//    //    PFD_DOUBLEBUFFER,      // double buffered  
//    //    PFD_TYPE_RGBA,         // RGBA type  
//    //    24,                    // 24-bit color depth excluding alpha
//    //    0, 0, 0, 0, 0, 0,      // color bits ignored  
//    //    8,                     // no alpha buffer  
//    //    0,                     // shift bit ignored  
//    //    0,                     // no accumulation buffer  
//    //    0, 0, 0, 0,            // accum bits ignored  
//    //    16,                    // 32-bit z-buffer  
//    //    0,                     // no stencil buffer  
//    //    0,                     // no auxiliary buffer  
//    //    0,                     // ignored. 
//    //    0,                     // reserved  
//    //    0, 0, 0                // layer masks ignored  
//    //};
//    //iPixelFormat = ChoosePixelFormat(hdc, &pfd);
//    //ret = SetPixelFormat(hdc, iPixelFormat, &pfd);
//
//    EGLint major, minor;
//    EGLDisplay display;
//    EGLint configSize;
//    EGLConfig eglConfig;
//    EGLSurface eglSurface;
//    EGLContext eglContext;
//    EGLint eglConfigAttribs[] = {
//        EGL_RED_SIZE, 8,
//        EGL_GREEN_SIZE, 8,
//        EGL_BLUE_SIZE, 8,
//        EGL_ALPHA_SIZE, 8,
//        EGL_DEPTH_SIZE, 16,
//        EGL_RENDERABLE_TYPE, EGL_OPENGL_ES2_BIT,
//        EGL_SURFACE_TYPE, EGL_WINDOW_BIT,
//        EGL_NONE
//    };
//    EGLint eglContectAttribs[] = {
//        EGL_CONTEXT_CLIENT_VERSION, 1
//    };
//
//    display = eglGetDisplay(EGL_DEFAULT_DISPLAY);
//    assert(display != EGL_NO_DISPLAY);
//    ret = eglInitialize(display, &major, &minor);
//    assert(ret == EGL_TRUE);
//    ret = eglChooseConfig(display, eglConfigAttribs, &eglConfig, 1, &configSize); 
//    assert(ret == EGL_TRUE);
//    eglSurface = eglCreateWindowSurface(display, eglConfig, hwnd, NULL);
//    eglContext = eglCreateContext(display, eglConfig, EGL_NO_CONTEXT, eglContectAttribs);
//    ret = eglMakeCurrent(display, eglSurface, eglSurface, eglContext);
//    assert(ret == EGL_TRUE);
//
//    while (GetMessage (&msg, NULL, 0, 0))
//    {
//        TranslateMessage (&msg) ;
//        DispatchMessage (&msg) ;
//    }
//
//    eglTerminate(display);
//    //ReleaseDC(hwnd, hdc);
//
//    return msg.wParam ;
//}

} // namespace Stratum

#endif // _WIN32
