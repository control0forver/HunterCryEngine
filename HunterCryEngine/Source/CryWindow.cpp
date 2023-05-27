#include "HunterCryEngine/CryWindow.h"
#include <thread>


void CryWindow::CreateClass()
{
    if (p_wndclsWindowRegClass)
        delete p_wndclsWindowRegClass;

    p_wndclsWindowRegClass = new WNDCLASS();

    p_wndclsWindowRegClass->cbClsExtra = NULL;
    p_wndclsWindowRegClass->cbWndExtra = NULL;
    p_wndclsWindowRegClass->hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
    p_wndclsWindowRegClass->hCursor = LoadCursor(NULL, IDC_ARROW);
    p_wndclsWindowRegClass->hIcon = LoadIcon(NULL, IDI_APPLICATION);
    p_wndclsWindowRegClass->hInstance = hinstWindowHinstanceBind;
    p_wndclsWindowRegClass->lpfnWndProc = wndprocWndProcFuncPtr;
    p_wndclsWindowRegClass->lpszClassName = c_strWindowClass;
    p_wndclsWindowRegClass->lpszMenuName = NULL;
    p_wndclsWindowRegClass->style = CS_HREDRAW | CS_VREDRAW;
}

CryWindow::CryWindow(const char* c_strWindowClass, const char* c_strWindowTitle, int iWidth, int iHeight,int iStartX, int iStartY)
{
    this->c_strWindowClass = c_strWindowClass;
    this->c_strWindowTitle = c_strWindowTitle;

    this->iWidth = iWidth;
    this->iHeight = iHeight;

    this->iStartX = iStartX;
    this->iStartY = iStartY;
}

const HWND CryWindow::Create(bool bUseDefaultWndProc, int iWndProcFuncAddr, HINSTANCE hinstHinstance)
{
    if (bUseDefaultWndProc)
        wndprocWndProcFuncPtr = (WNDPROC)DefaultWndProc;
    else
        wndprocWndProcFuncPtr = (WNDPROC)(iWndProcFuncAddr);

    hinstWindowHinstanceBind = hinstHinstance;

    CreateClass();
    if (!RegisterClass(p_wndclsWindowRegClass))
        return NULL;

    hwndWindowHandle = CreateWindow(
        c_strWindowClass, c_strWindowTitle,
        WS_OVERLAPPEDWINDOW,
        iStartX, iStartY,
        iWidth, iHeight,
        NULL,
        NULL,
        hinstHinstance,
        NULL
    );

    return hwndWindowHandle;
}

void CryWindow::Release()
{
    DestroyWindow(hwndWindowHandle);
    UnregisterClass(c_strWindowClass, p_wndclsWindowRegClass->hInstance);

    if (p_wndclsWindowRegClass)
        delete p_wndclsWindowRegClass;
    p_wndclsWindowRegClass = nullptr;

    delete this;
}
