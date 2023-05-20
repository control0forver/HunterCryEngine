#pragma once
#include <inttypes.h>

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
    static unsigned int u_iEnginesCount;
#pragma endregion
#pragma region Public Gets
public:
    static unsigned int GetEnginesCount();
    static void GetEnginesCount(unsigned int* const p_u_iEnginesCount);
#pragma endregion


#pragma endregion


#pragma region Class Datas

#pragma region Public
public:
    const char* c_strWindowClass;
    const char* c_strWindowTitle;
    int iWidth = 0, iHeight = 0;

public:
    IHunterCry(const char* c_strWindowClass = "class", const char* c_strWindowTitle = "title", int iWidth = 800, int iHeight = 600);
    ~IHunterCry();

public:
    int InitializeEngine();
    void ReleaseEngine();

#pragma endregion
#pragma region Private
private:
    CryWindow* p_crywndWindow = nullptr;
    CryDevice* p_crydevDevice = nullptr;
#pragma endregion
#pragma region Public Gets
public:
    const CryWindow* GetWindow();
    const CryDevice* GetDevice();
#pragma endregion

#pragma endregion

}*HunterCry;
