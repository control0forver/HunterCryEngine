#pragma once
#include <inttypes.h>
#include <stdio.h>

#include "LibDef.h"
#include "CryWindow.h"
#include "CryDevice.h"

typedef class IHunterCry {
#pragma region Const Datas

#pragma region Public
public:
#pragma endregion
#pragma region Private
private:
#pragma endregion

#pragma endregion

#pragma region Static Datas

#pragma region Public
public:
#pragma endregion
#pragma region Private
private:
#pragma endregion
#pragma region Public Gets
public:
    HUNTERCRY_API static unsigned int GetEnginesCount();
    HUNTERCRY_API static void GetEnginesCount(unsigned int* const p_u_iEnginesCount);
#pragma endregion


#pragma endregion


#pragma region Class Datas
#pragma region Private
private:
    CryWindow* p_crywndWindow = nullptr;
    CryDevice* p_crydevDevice = nullptr;
private:
    bool bIsInitialized = false;
    const char* c_strWindowClass;
    const char* c_strWindowTitle;
    int iWidth = 0, iHeight = 0;
    bool bFullscreen = 0;

private:
    HUNTERCRY_API void ECADD();
    HUNTERCRY_API void ECSUB();
#pragma endregion

#pragma region Public

public:
    IHunterCry(const char* c_strWindowClass = "class", const char* c_strWindowTitle = "title", int iWidth = 800, int iHeight = 600, bool bFullscreen = false)
    {
        this->c_strWindowClass = c_strWindowClass;
        this->c_strWindowTitle = c_strWindowTitle;

        this->iWidth = iWidth;
        this->iHeight = iHeight;

        this->bFullscreen = bFullscreen;

        // Success
        ECADD();
    }
    ~IHunterCry()
    {
        p_crydevDevice->Release();
        //p_crywndWindow->Release();

        // Success
        ECSUB();
    }

public:

    HUNTERCRY_API int InitializeEngine();
    HUNTERCRY_API void ReleaseEngine();

    HUNTERCRY_API int InitializeSDL2();
    HUNTERCRY_API void ReleaseSDL2();

    HUNTERCRY_API inline void SwitchFullscreen();
    HUNTERCRY_API void SwitchFullscreen(bool bFullscreen);
    HUNTERCRY_API void ResizeContext(int iWidth, int iHeight);

    HUNTERCRY_API inline void SetWindowClass(const char* c_strWindowClass);
    HUNTERCRY_API inline void SetWindowTItle(const char* c_strWindowTitle);
    HUNTERCRY_API inline void SetWidthHeight(int iWidth, int iHeight);
    HUNTERCRY_API inline void SetFullscreen(bool bFullscreen);


#pragma endregion
#pragma region Public Gets
public:
    HUNTERCRY_API CryWindow* GetWindow();
    HUNTERCRY_API CryDevice* GetDevice();

    HUNTERCRY_API inline const char* GetWindowClass();
    HUNTERCRY_API inline const char* GetWindowTItle();
    HUNTERCRY_API inline int GetWidth();
    HUNTERCRY_API inline int GetiHeight();
    HUNTERCRY_API inline bool GetFullscreen();
#pragma endregion

#pragma endregion

}*HunterCry;
