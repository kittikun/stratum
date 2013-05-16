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

#ifdef _WIN32

#include "platform_impl.h"

#include <Windows.h>

#include "../log.h"

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    return DefWindowProc(hwnd, message, wParam, lParam);
}

namespace stratum
{

const bool createNativeWindow(const uint32_t, const uint32_t, NativeInfo& outInfo)
{
    TCHAR className[] = TEXT("Stratum");
    HDC hdc;
    HWND hwnd ;
    WNDCLASS wndclass;

    LOGP << "Creating native window..";

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
        return false;
    }

    hwnd = CreateWindowEx(NULL, className, TEXT ("Test"), WS_OVERLAPPEDWINDOW, 
        CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
        NULL, NULL, NULL, NULL);

    ShowWindow(hwnd, SW_SHOWDEFAULT);
    hdc = GetDC(hwnd);

    outInfo.display = EGL_DEFAULT_DISPLAY;
    outInfo.window = hwnd;

    return true;
}

const bool destroyNativeWindow(const NativeInfo& info)
{
    LOGP << "Destroying native window..";

    DestroyWindow(info.window);

    return true;
}

void initializeInput()
{
}

const bool inputRead()
{
    return false;
}

} // namespace stratum

#endif // _WIN32
