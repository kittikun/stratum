//  Copyright 2013 Kitti Vongsay
//
//  This file is part of stratum.
//
//  stratum is free software: you can redistribute it and/or modify
//  it under the terms of the GNU Lesser General Public License as
//  published by the Free Software Foundation, either version 3 of
//  the License, or(at your option) any later version.
//
//  stratum is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU Lesser General Public License for more details.
//
//  You should have received a copy of the GNU Lesser General Public
//  License along with stratum.   If not, see <http://www.gnu.org/licenses/>.


// See http://cgit.freedesktop.org/mesa/demos/tree/src/egl/opengles2/es2tri.c

#ifdef __linux__

    #include "platform_impl.h"

    #include <boost/utility.hpp>
    #include <EGL/egl.h>
    #include <X11/Xlib.h>
    #include <cstring>

    #include <graphic.h>

    #include "../log.h"
    #include "../utility.h"

namespace stratum
{

class PlatformLinux : public Platform, boost::noncopyable
{
public:
    PlatformLinux();
    EGLNativeDisplayType getNativeDisplay(); 
    EGLNativeWindowType getNativeWindow(); 
    virtual const bool createNativeWindow(const GraphicOptions& options, EGLConfig eglConfig); 
    const bool destroyNativeWindow(); 
    
    void initializeInput(); 
    const bool inputRead(); 

private:
    Display *m_dpy;
    Window m_win;
};

Platform& GetPlatform()
{
    static PlatformLinux instance;

    return instance;
}

PlatformLinux::PlatformLinux()
: m_dpy(NULL) 
, m_win(-1)
{

}

EGLNativeDisplayType PlatformLinux::getNativeDisplay()
{
    if (m_dpy == nullptr) {
        m_dpy = XOpenDisplay(NULL);

        if (m_dpy == NULL) {
            LOGC << "Cannot connect to X server.";
            return false;
        }
    }

    return m_dpy;
}

EGLNativeWindowType PlatformLinux::getNativeWindow()
{
    return m_win;
}

const bool PlatformLinux::createNativeWindow(const GraphicOptions& options, EGLConfig eglConfig)
{
    Window root;
    unsigned long mask;
    XSetWindowAttributes swa;
    XVisualInfo *visInfo, visTemplate;
    int num_visuals;
    EGLDisplay eglDisplay;
    EGLint vid;

    LOGP << boost::format("Creating %1%x%2% native window..") % options.width % options.height;

    root = DefaultRootWindow(m_dpy);

    eglDisplay = eglGetDisplay(m_dpy);
    if (eglDisplay == EGL_NO_DISPLAY) {
        return VERIFYEGL();
    }

    if (!eglGetConfigAttrib(eglDisplay, eglConfig, EGL_NATIVE_VISUAL_ID, &vid)) {
        return VERIFYEGL();
    }

    /* The X window visual must match the EGL config */
    visTemplate.visualid = vid; 
    visInfo = XGetVisualInfo(m_dpy, VisualIDMask, &visTemplate, &num_visuals); 
    if (!visInfo) {
        LOGC << "couldn't get X visual"; 
        return false;
    }


    /* window attributes */
    swa.background_pixel = 0;
    swa.border_pixel = 0;
    swa.colormap = XCreateColormap(m_dpy, root, visInfo->visual, AllocNone);
    swa.event_mask = StructureNotifyMask | ExposureMask | KeyPressMask;
    mask = CWBackPixel | CWBorderPixel | CWColormap | CWEventMask;

    m_win = XCreateWindow(m_dpy, root,
                        0, 0, options.width, options.height, 0,
                        visInfo->depth, InputOutput,
                        visInfo->visual, mask, &swa);

    /* set hints and properties */
    XSizeHints sizehints;

    sizehints.x = 0;
    sizehints.y = 0;
    sizehints.width  = options.width;
    sizehints.height = options.height;
    sizehints.flags = USSize | USPosition;
    XSetNormalHints(m_dpy, m_win, &sizehints);
    XSetStandardProperties(m_dpy, m_win, "testo", "none",
                           None, (char **)NULL, 0, &sizehints);

    XMapWindow(m_dpy, m_win);

    return true;
}

const bool PlatformLinux::destroyNativeWindow()
{
    LOGP << "Destroying native window..";

    XDestroyWindow(m_dpy, m_win);
    XCloseDisplay(m_dpy);
    m_dpy = NULL;

    return true;
}

const bool PlatformLinux::inputRead()
{
    XEvent xev;

    XNextEvent(m_dpy, &xev);

    if (xev.type == Expose) {
//      XGetWindowAttributes(x_display, win, &gwa);
// todo: handle graphic resize
    } else if (xev.type == KeyPress) {
        return true;
    } else if (xev.type == DestroyNotify) {
        return true;
    }

    return false;
}

void PlatformLinux::initializeInput()
{

}

} // namepsace stratum

#endif // __linux__
