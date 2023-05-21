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
IHunterCry::IHunterCry(const char* c_strWindowClass, const char* c_strWindowTitle, int iWidth, int iHeight)
{
    this->c_strWindowClass = c_strWindowClass;
    this->c_strWindowTitle = c_strWindowTitle;

    this->iWidth = iWidth;
    this->iHeight = iHeight;

    // Success
    ++u_iEnginesCount;
}

IHunterCry::~IHunterCry()
{
    p_crydevDevice->Release();

    // Success
    --u_iEnginesCount;
}



int IHunterCry::InitializeEngine()
{
    p_crywndWindow = new CryWindow(c_strWindowClass, c_strWindowTitle, iWidth, iHeight);
    if (!p_crywndWindow || !p_crywndWindow->Create(true,NULL,GetModuleHandle(0)))
        return false;

    p_crydevDevice = new CryDevice();
    if (!p_crydevDevice || !p_crydevDevice->Create(iWidth, iHeight, p_crywndWindow->hwndWindowHandle))
        return false;

    return true;
}

void IHunterCry::ReleaseEngine()
{
    delete this;
}

const CryWindow* IHunterCry::GetWindow()
{
    return p_crywndWindow;
}

const CryDevice* IHunterCry::GetDevice()
{
    return p_crydevDevice;
}

#pragma endregion
#pragma region Private

#pragma endregion

#pragma endregion