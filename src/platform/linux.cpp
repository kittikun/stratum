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

#ifdef __linux__

#include "platform.h"

#include <X11/Xlib.h>
#include <EGL/egl.h>
#include <string.h>

#include "../log.h"

namespace stratum
{

static Display* x_display = NULL;

const bool createNativeWindow(const uint32_t width, const uint32_t height, NativeInfo& outInfo)
{
    Atom wm_state;
    Window root;
    Window win;
    XEvent xev;
    XSetWindowAttributes swa;
    XSetWindowAttributes xattr;
    XWMHints hints;

    LOGP << boost::format("Creating %1%x%2% native window..") % width % height;

    x_display = XOpenDisplay(NULL);

    if (x_display == NULL) {
        LOGC << "Cannot connect to X server.";
        return false;
    }

    root = DefaultRootWindow(x_display);
    swa.event_mask = ExposureMask | PointerMotionMask | KeyPressMask;

    win = XCreateWindow(x_display, root,
                        0, 0, width, height, 0,
                        CopyFromParent, InputOutput,
                        CopyFromParent, CWEventMask,
                        &swa);

    xattr.override_redirect = False;
    XChangeWindowAttributes(x_display, win, CWOverrideRedirect, &xattr);

    hints.input = True;
    hints.flags = InputHint;
    XSetWMHints(x_display, win, &hints);

    // make the window visible on the screen
    XMapWindow(x_display, win);
    XStoreName(x_display, win, "temp title");

    // get identifiers for the provided atom name strings
    wm_state = XInternAtom(x_display, "_NET_WM_STATE", False);

    memset(&xev, 0, sizeof(xev));
    xev.type                    = ClientMessage;
    xev.xclient.window          = win;
    xev.xclient.message_type    = wm_state;
    xev.xclient.format          = 32;
    xev.xclient.data.l[0]       = 1;
    xev.xclient.data.l[1]       = False;
    XSendEvent(x_display,
               DefaultRootWindow(x_display),
               False,
               SubstructureNotifyMask,
               &xev);

    outInfo.display = x_display;
    outInfo.window = win;

    return true;
}

const bool destroyNativeWindow(const NativeInfo& info)
{
    LOGP << "Destroying native window..";

    XDestroyWindow(info.display, info.window);
    XCloseDisplay(info.display);
    x_display = NULL;
}

const bool inputRead()
{
    XEvent xev;

    XNextEvent(x_display, &xev); 
    
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

} // namepsace stratum

#endif // __linux__
