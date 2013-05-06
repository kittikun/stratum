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

// code inspired from https://code.google.com/p/opengles-book-samples/source/browse/trunk/LinuxX11/Common/esUtil.c

#ifdef __linux__

#include "platform.h"

#include <X11/Xlib.h>
#include <EGL/egl.h>
#include <string.h>

#include "../log.h"

namespace Stratum
{

const bool CreateWindow(Stratum::NativeInfo& info)
{
    Atom wm_state;
    Display* x_display = NULL;
    Window root;
    Window win;
    XEvent xev;
    XSetWindowAttributes swa;
    XSetWindowAttributes xattr;
    XWMHints hints;

    LOGN << "Creating native window..";
    x_display = XOpenDisplay(NULL);

    if (x_display == NULL) {
        LOGC << "Cannot connect to X server";
        return false;
    }

    root = DefaultRootWindow(x_display);
    swa.event_mask = ExposureMask | PointerMotionMask | KeyPressMask;

    win = XCreateWindow(x_display, root,
                        0, 0, 640, 480, 0,
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

    info.display = x_display;
    info.window = win;

    return true;
}

} // namepsace Stratum

#endif // __linux__
