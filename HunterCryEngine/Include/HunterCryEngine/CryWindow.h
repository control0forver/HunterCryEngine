#pragma once
#ifdef _WIN32
#include <Windows.h>
#endif

#include "LibDef.h"

class CryWindow {
#ifdef _WIN32
public:
    static LRESULT CALLBACK DefaultWndProc(HWND hwndWindow, UINT iMessage, WPARAM wparamWParam, LPARAM lparamLParam) {
        switch (iMessage)
        {
        case WM_PAINT:
            //ValidateRect(hwndWindow, NULL);
            break;
        case WM_DESTROY:
            PostQuitMessage(wparamWParam);
            break;
        }
        return DefWindowProc(hwndWindow, iMessage, wparamWParam, lparamLParam);
    }
#endif

public:
#ifdef _WIN32
    const char* c_strWindowClass;
    const char* c_strWindowTitle;
    int iWidth = 0, iHeight = 0;
    int iStartX = 0, iStartY = 0;

    HINSTANCE hinstWindowHinstanceBind = NULL;
    HWND hwndWindowHandle = NULL;
    WNDPROC wndprocWndProcFuncPtr = NULL;

    WNDCLASS* p_wndclsWindowRegClass = nullptr;

    void (*LoopProcessing)(bool) = [](bool bGetMessage) {
        MSG msg;
        ZeroMemory(&msg, sizeof(msg));
        while (msg.message != WM_QUIT)
        {
            if (bGetMessage ? GetMessage(&msg, NULL, 0, 0) : PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
            {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
        }
    };

#endif

#ifdef _WIN32
    HUNTERCRY_API void CreateClass();
#endif

public:
#ifdef _WIN32
    CryWindow(const char* c_strWindowClass, const char* c_strWindowTitle, int iWidth, int iHeight, int iStartX = CW_USEDEFAULT, int iStartY = CW_USEDEFAULT) {
        this->c_strWindowClass = c_strWindowClass;
        this->c_strWindowTitle = c_strWindowTitle;

        this->iWidth = iWidth;
        this->iHeight = iHeight;

        this->iStartX = iStartX;
        this->iStartY = iStartY;
    }

    ~CryWindow() {}

    HUNTERCRY_API const HWND Create(bool bUseDefaultWndProc = true, int iWndProcFuncAddr = NULL, HINSTANCE hinstHinstance = NULL);

    HUNTERCRY_API void Release();
#endif
};