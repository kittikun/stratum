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

#include "utility.h"

#include <stdio.h>

#include "log.h"

namespace Stratum {

    const std::string eglErrorEnumToString(EGLint err)
    {
        switch (err) {
            case EGL_SUCCESS:
                return "EGL_SUCCESS: Function succeeded.";
            case EGL_NOT_INITIALIZED:
                return "EGL_NOT_INITIALIZED: EGL is not initialized, or could not be initialized, for the specified display. Any command may generate this error.";
            case EGL_BAD_ACCESS:
                return "EGL_BAD_ACCESS: EGL cannot access a requested resource (for example, a context is bound in another thread). Any command accessing a named resource may generate this error";
            case EGL_BAD_ALLOC:
                return "EGL_BAD_ALLOC: EGL failed to allocate resources for the requested operation. Any command allocating resources may generate this error.";
            case EGL_BAD_ATTRIBUTE:
                return "EGL_BAD_ATTRIBUTE: An unrecognized attribute or attribute value was passed in an attribute list. Any command taking an attribute parameter or attribute list may generate this error.";
            case EGL_BAD_CONTEXT:
                return "EGL_BAD_CONTEXT: An EGLContext argument does not name a valid EGLContext. Any command taking an EGLContext parameter may generate this error.";
            case EGL_BAD_CONFIG:
                return "EGL_BAD_CONFIG: An EGLConfig argument does not name a valid EGLConfig. Any command taking an EGLConfig parameter may generate this error.";
            case EGL_BAD_CURRENT_SURFACE:
                return "EGL_BAD_CURRENT_SURFACE: The current surface of the calling thread is a window, pbuffer, or pixmap that is no longer valid.";
            case EGL_BAD_DISPLAY:
                return "EGL_BAD_DISPLAY: An EGLDisplay argument does not name a valid EGLDisplay. Any command taking an EGLDisplay parameter may generate this error.";
            case EGL_BAD_SURFACE:
                return "EGL_BAD_SURFACE: An EGLSurface argument does not name a valid surface (window, pbuffer, or pixmap) configured for rendering. Any command taking an EGL Surface parameter may generate this error.";
            case EGL_BAD_MATCH:
                return "EGL_BAD_MATCH: Arguments are inconsistent; for example, an otherwise valid context requires buffers (e.g. depth or stencil) not allocated by an otherwise valid surface.";
            case EGL_BAD_PARAMETER:
                return "EGL_BAD_PARAMETER: One or more argument values are invalid. Any command taking parameters may generate this error.";
            case EGL_BAD_NATIVE_PIXMAP:
                return "EGL_BAD_NATIVE_PIXMAP: An EGLNativePixmapType argument does not refer to a valid native pixmap. Any command taking an EGLNativePixmapType parameter may generate this error.";
            case EGL_BAD_NATIVE_WINDOW:
                return "EGL_BAD_NATIVE_WINDOW: An EGLNativeWindowType argument does not refer to a valid native window. Any command taking an EGLNativeWindowType parameter may generate this error.";
            case EGL_CONTEXT_LOST:
                return "EGL_CONTEXT_LOST: A power management event has occurred. The application must destroy all contexts and reinitialise client API state and objects to continue rendering, as described in section 2.6. Any command may generate this error.";
            default:
                {
                    char buff[30];
                    snprintf(buff, 30, "Unknown EGL error %#4X", (unsigned int)err);
                    return buff;
                }
        }

        return "Unknown EGL error";
    }

    const bool VerifyEGL(EGLint expectedError, const char *file, unsigned line) {
        EGLint eglError = eglGetError();
        if (eglError != expectedError) {
            LOGE << "Unexpected EGL_Error at " << file << ":" << line << ":" << "Got " << eglErrorEnumToString(eglError) << " expected " << eglErrorEnumToString(expectedError);
            return false;
        }
        return true;
    }


} // namespace Stratum
