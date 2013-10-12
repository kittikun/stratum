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
#include <dinput.h>

#include "../log.h"

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message) 
	{
		//case WM_COMMAND:
		// handle menu selections etc.
		//break;
		//case WM_PAINT:
		// draw our window - note: you must paint something here or not trap it!
		//break;
	case WM_CLOSE: {
		int i = 0;
		break;
		}
	case WM_DESTROY: {
		PostQuitMessage(0);
		break;
		}
	default:
		// We do not want to handle this message so pass back to Windows
		// to handle it in a default way
		return DefWindowProc(hwnd, message, wParam, lParam);
	}
}

namespace stratum
{
    class PlatformWin : public Platform, private boost::noncopyable
    {
    public:
        PlatformWin();
        EGLNativeDisplayType getNativeDisplay();
        EGLNativeWindowType getNativeWindow();

        const bool createNativeWindow(const GraphicOptions& options, EGLConfig eglConfig);
        const bool destroyNativeWindow();

        const bool initializeInput();
        const Keys inputRead();

    private:
        HWND m_hwnd;
        HINSTANCE m_hInstance;
        IDirectInput8* m_directInput;
        IDirectInputDevice8* m_keyboard;
        IDirectInputDevice8* m_mouse;
    };

    boost::shared_ptr<Platform> Platform::CreatePlatform()
    {
        return boost::shared_ptr<Platform>(new PlatformWin());
    }

    PlatformWin::PlatformWin()
        : m_hwnd(nullptr)
        , m_directInput(nullptr)
        , m_keyboard(nullptr)
        , m_mouse(nullptr)
    {
    }

    EGLNativeDisplayType PlatformWin::getNativeDisplay()
    {
        return EGL_DEFAULT_DISPLAY;
    }

    EGLNativeWindowType PlatformWin::getNativeWindow()
    {
        return m_hwnd;
    }

    const bool PlatformWin::createNativeWindow(const GraphicOptions&, EGLConfig)
    {
        TCHAR className[] = TEXT("Stratum");
        HDC hdc;
        HWND hwnd ;
        WNDCLASS wndclass;

        LOGP << "Creating native window..";

		m_hInstance = GetModuleHandle(NULL);

        wndclass.style         = CS_HREDRAW | CS_VREDRAW ;
        wndclass.lpfnWndProc   = WndProc ;
        wndclass.cbClsExtra    = 0 ;
        wndclass.cbWndExtra    = 0 ;
        wndclass.hInstance     = m_hInstance ;
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
            NULL, NULL, m_hInstance, NULL);

        ShowWindow(hwnd, SW_SHOWDEFAULT);
        hdc = GetDC(hwnd);

        m_hwnd = hwnd;

        return true;
    }

    const bool PlatformWin::destroyNativeWindow()
    {
        LOGP << "Destroying native window..";

        DestroyWindow(m_hwnd);

        return true;
    }

    const bool PlatformWin::initializeInput()
    {
        HRESULT res;

        LOGP << "Creating DirectInput..";
        res = DirectInput8Create(m_hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&m_directInput, NULL);
        if (FAILED(res)) {
            LOGC << "Failed to create direct input";
            return false;
        }

        LOGP << "Creating keyboard..";
        res = m_directInput->CreateDevice(GUID_SysKeyboard, &m_keyboard, NULL);
        if (FAILED(res)) {
            LOGC << "Failed to create keyboard device";
            return false;
        }

        res = m_keyboard->SetDataFormat(&c_dfDIKeyboard);
        if (FAILED(res)) {
            LOGC << "Failed to set keyboard data format";
            return false;
        }

        res = m_keyboard->SetCooperativeLevel(m_hwnd, DISCL_FOREGROUND | DISCL_EXCLUSIVE);
        if (FAILED(res)) {
            LOGC << "Failed to set keyboard cooperative level";
            return false;
        }

        res = m_keyboard->Acquire();
        if (FAILED(res)) {
            LOGC << "Failed to acquire keyboard";
            return false;
        }

        res = m_directInput->CreateDevice(GUID_SysMouse, &m_mouse, NULL);
        if (FAILED(res)) {
            LOGC << "Failed to create mouse device";
            return false;
        }

        LOGP << "Creating mouse device..";
        res = m_mouse->SetDataFormat(&c_dfDIMouse);
        if (FAILED(res)) {
            LOGC << "Failed to set mouse data format";
            return false;
        }

        res = m_mouse->SetCooperativeLevel(m_hwnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
        if (FAILED(res)) {
            LOGC << "Failed to set keyboard cooperative level";
            return false;
        }

        return true;
    }

    const Keys PlatformWin::inputRead()
    {
		uint8_t  diKeys[256];
		MSG Msg;
		HRESULT res;

		// Maybe not the best place to do this
		while (PeekMessage(&Msg, NULL, 0, 0, PM_REMOVE)) {
			TranslateMessage(&Msg);
			DispatchMessage(&Msg);
		}

		// check if we lost focus
		if (m_keyboard->Poll() != DI_OK) {
			res = m_keyboard->Acquire();
			if (FAILED(res)) {
				//LOGC << "Failed to acquire keyboard after losing focus";
				return KEY_NONE;
			}
		}

		if (m_keyboard->GetDeviceState(256, diKeys) == DI_OK) {
			if (diKeys[DIK_ESCAPE] & 0x80) { 
				return KEY_ESCAPE;
			}
		}

        return KEY_NONE;
    }

} // namespace stratum

#endif // _WIN32
