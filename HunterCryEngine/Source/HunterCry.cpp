#include "HunterCryEngine/HunterCry.h"
#include <stdio.h>

#pragma region Static Datas

#pragma region Public
#pragma endregion
#pragma region Private
static unsigned int u_iEnginesCount = 0;
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
#pragma region Private
void IHunterCry::ECADD()
{
    u_iEnginesCount++;
}
void IHunterCry::ECSUB()
{
    u_iEnginesCount--;
}
#pragma endregion

#pragma region Public

void IHunterCry::PreLoadEngine()
{
    if (!p_crywndWindow)
        p_crywndWindow = new CryWindow(c_strWindowClass, c_strWindowTitle, iWidth, iHeight);

    if (!p_crydevDevice)
        p_crydevDevice = new CryDevice();
}

int IHunterCry::InitializeEngine()
{
    if (bIsInitialized)
        return false;

    if (!p_crywndWindow || !p_crywndWindow->Create(true, NULL, GetModuleHandle(0)))
        return false;

    if (!p_crydevDevice || !p_crydevDevice->Create(iWidth, iHeight, bFullscreen, p_crywndWindow->hwndWindowHandle))
        return false;

    return true;
}

void IHunterCry::ReleaseEngine()
{
    delete this;
}

int IHunterCry::InitializeSDL2()
{
    return  SDL_Init(SDL_INIT_EVERYTHING);
}

void IHunterCry::ReleaseSDL2()
{
    SDL_Quit();
}

void IHunterCry::SwitchVSync(bool bUseVSync)
{
    if (bUseVSync) {
        p_crydevDevice->iD3DPresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;
        p_crydevDevice->d3dswpefctD3DSwapEffect = D3DSWAPEFFECT_FLIP;
    }
    else {
        p_crydevDevice->iD3DPresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;
        p_crydevDevice->d3dswpefctD3DSwapEffect = D3DSWAPEFFECT_DISCARD;
    }

    p_crydevDevice->Reset();
}

void IHunterCry::SwitchFullscreen()
{
    bFullscreen = !bFullscreen;
    SwitchFullscreen(bFullscreen);
}

void IHunterCry::SwitchFullscreen(bool bFullscreen)
{
    SetFullscreen(bFullscreen);

    if (bFullscreen)
    {
        p_crydevDevice->iD3DWindowed = false;
        p_crydevDevice->iD3DFullScreen_RefreshRateInHz = iRefreshRateHz;

        p_crydevDevice->Reset();
    }
    else
    {
        p_crydevDevice->iD3DWindowed = true;
        p_crydevDevice->iD3DFullScreen_RefreshRateInHz = 0;

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

void IHunterCry::SetRefreshRateHz(int iRefreshRateHz)
{
    this->iRefreshRateHz = iRefreshRateHz;
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

int IHunterCry::GetHeight()
{
    return iHeight;
}

int IHunterCry::GetRefreshRateHz()
{
    return iRefreshRateHz;
}

bool IHunterCry::GetFullscreen()
{
    return bFullscreen;
}

#pragma endregion

#pragma endregion