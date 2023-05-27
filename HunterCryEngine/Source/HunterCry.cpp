#include "HunterCryEngine/HunterCry.h"
#include <stdio.h>

#pragma region Static Datas

#pragma region Public
#pragma endregion
#pragma region Private
unsigned int IHunterCry::u_iEnginesCount = 0;
#pragma endregion
#pragma region Public Gets
unsigned int IHunterCry::GetEnginesCount()
{
    return u_iEnginesCount;
}
void IHunterCry::GetEnginesCount(unsigned int* const p_u_iEnginesCount)
{
    *p_u_iEnginesCount = u_iEnginesCount;
}
#pragma endregion

#pragma endregion


#pragma region Class Datas

#pragma region Public
IHunterCry::IHunterCry(const char* c_strWindowClass, const char* c_strWindowTitle, int iWidth, int iHeight, bool bFullscreen)
{
    this->c_strWindowClass = c_strWindowClass;
    this->c_strWindowTitle = c_strWindowTitle;

    this->iWidth = iWidth;
    this->iHeight = iHeight;

    this->bFullscreen = bFullscreen;

    // Success
    ++u_iEnginesCount;
}

IHunterCry::~IHunterCry()
{
    p_crydevDevice->Release();
    //p_crywndWindow->Release();

    // Success
    --u_iEnginesCount;
}



int IHunterCry::InitializeEngine()
{
    if (bIsInitialized)
        return false;

    p_crywndWindow = new CryWindow(c_strWindowClass, c_strWindowTitle, iWidth, iHeight);
    if (!p_crywndWindow || !p_crywndWindow->Create(true, NULL, GetModuleHandle(0)))
        return false;

    p_crydevDevice = new CryDevice();
    if (!p_crydevDevice || !p_crydevDevice->Create(iWidth, iHeight, bFullscreen, p_crywndWindow->hwndWindowHandle))
        return false;

    return true;
}

void IHunterCry::ReleaseEngine()
{
    delete this;
}

void IHunterCry::SwitchFullscreen()
{
    SwitchFullscreen(bFullscreen);
}

void IHunterCry::SwitchFullscreen(bool bFullscreen)
{
    SetFullscreen(bFullscreen);

    if (bFullscreen)
    {
        p_crydevDevice->iD3DWindowed = false;

        p_crydevDevice->Reset();
    }
    else
    {
        p_crydevDevice->iD3DWindowed = true;

        p_crydevDevice->Reset();
    }
}

void IHunterCry::ResizeContext(int iWidth, int iHeight)
{

}

void IHunterCry::SetWindowClass(const char* c_strWindowClass)
{
    this->c_strWindowClass = c_strWindowClass;
}

void IHunterCry::SetWindowTItle(const char* c_strWindowTitle)
{
    this->c_strWindowTitle = c_strWindowTitle;
}

void IHunterCry::SetWidthHeight(int iWidth, int iHeight)
{
    this->iWidth = iWidth;
    this->iHeight = iHeight;
}

void IHunterCry::SetFullscreen(bool bFullscreen)
{
    this->bFullscreen = bFullscreen;
}

CryWindow* IHunterCry::GetWindow()
{
    return p_crywndWindow;
}

CryDevice* IHunterCry::GetDevice()
{
    return p_crydevDevice;
}

const char* IHunterCry::GetWindowClass()
{
    return c_strWindowClass;
}

const char* IHunterCry::GetWindowTItle()
{
    return c_strWindowTitle;
}

int IHunterCry::GetWidth()
{
    return iWidth;
}

int IHunterCry::GetiHeight()
{
    return iHeight;
}

bool IHunterCry::GetFullscreen()
{
    return bFullscreen;
}

#pragma endregion
#pragma region Private

#pragma endregion

#pragma endregion