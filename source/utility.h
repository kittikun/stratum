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

#ifndef UTILITY_H
#define UTILITY_H

#include <EGL/egl.h>
#include <GLES2/gl2.h>
#include <string>


// Enable VERIFY_GL_ON in order to get detailed information about failing tests,
// such as the line number and failure circumstances.
#define VERIFY_GL_ON 1

#if VERIFY_GL_ON
    #define VERIFYGL() VerifyGL(GL_NO_ERROR, __FILE__, __LINE__)
    #define VERIFYEGL() VerifyEGL(EGL_SUCCESS, __FILE__, __LINE__)
#else
    #define VERIFYGL() (true)
    #define VERIFYEGL() (true)
#endif

namespace Stratum {

    const std::string eglErrorEnumToString(EGLint err);
    const bool VerifyEGL(EGLint expectedError, const char *file, unsigned line);
    const bool VerifyGL(GLenum expectedError, const char *file, unsigned line);
    
     
} // namespace Stratum

#endif // UTILITY_H
