#pragma once
#ifdef _WIN32
#include <Windows.h>
#include <d3d9.h>
#include <d3dx9.h>
#pragma comment(lib, "d3d9.lib")
#ifdef _DEBUG
#pragma comment(lib, "d3dx9d.lib")
#else
#pragma comment(lib, "d3dx9.lib")
#endif
#endif

#include "LibDef.h"

class CryDevice {
private:
    bool bReleased = false;

public:
#ifdef _WIN32
    CryDevice(D3DDEVTYPE d3ddevtDeviceType = D3DDEVTYPE_HAL) {
        this->d3ddevtDeviceType = d3ddevtDeviceType;
    }
    ~CryDevice() {
        bReleased = true;

        p_id3d9D3D9->Release();
        p_id3d9devD3D9Device->Release();

        p_id3d9D3D9 = nullptr;
        p_id3d9devD3D9Device = nullptr;
        if (p_d3d9capsCaps)
            delete p_d3d9capsCaps;
        if (p_d3dpstparamD3DPresentParameters)
            delete p_d3dpstparamD3DPresentParameters;
    }
#endif

private:
#ifdef _WIN32
    int iDeviceWidth = 0;
    int iDeviceHeight = 0;

    D3DCAPS9* p_d3d9capsCaps = nullptr;
    IDirect3DDevice9* p_id3d9devD3D9Device = nullptr;
    D3DPRESENT_PARAMETERS* p_d3dpstparamD3DPresentParameters = nullptr;

#endif

public:
#ifdef _WIN32
    IDirect3D9* p_id3d9D3D9 = nullptr;
    D3DDEVTYPE d3ddevtDeviceType = (D3DDEVTYPE)NULL;
    int iVertexProcessing = NULL;

    HWND hwndD3DWindow = NULL;
    D3DFORMAT d3dfmtD3DBackbufferFormat = (D3DFORMAT)NULL;
    D3DMULTISAMPLE_TYPE d3dmltsmptD3DMultiSampleType = (D3DMULTISAMPLE_TYPE)NULL;
    D3DSWAPEFFECT d3dswpefctD3DSwapEffect = (D3DSWAPEFFECT)NULL;
    D3DFORMAT d3dfmtD3DAutoDepthStencilFormat = (D3DFORMAT)NULL;
    /* FullScreen_RefreshRateInHz must be zero for Windowed mode */
    int iD3DPresentFlags = NULL;
    int iD3DBackbuffersCount = 0;
    int iD3DFullScreen_RefreshRateInHz = NULL;
    int iD3DPresentationInterval = NULL;
    int iD3DMultiSampleQuality = NULL;
    int iD3DWindowed = NULL;
    int iD3DEnableAutoDepthStencil = NULL;
#endif

#ifdef _WIN32
private:
    HUNTERCRY_API void GetCaptures();
    HUNTERCRY_API void CheckVertexProcessing();

public:
    virtual void ErrCreatingD3D9Device(HRESULT hrResult) {}

public:
    HUNTERCRY_API void MakeD3DPstParams();
    HUNTERCRY_API inline void MakeD3DPstParams(D3DPRESENT_PARAMETERS d3dpstparamD3DPresentParameters);
    HUNTERCRY_API HRESULT Reset(bool bAutoMakePP = true);
    HUNTERCRY_API HRESULT Reset(D3DPRESENT_PARAMETERS d3dpstparamD3DPresentParameters);
#endif

public:
#ifdef _WIN32
    HUNTERCRY_API const IDirect3D9* CreateD3D9();
    HUNTERCRY_API const IDirect3DDevice9* CreateD3D9Device();

    HUNTERCRY_API int Create(int iWidth, int iHeight, bool bFullscreen, HWND hwndWindow);
    HUNTERCRY_API void Release();

    HUNTERCRY_API inline IDirect3DDevice9** GetD3D9DevicePtrPtr() { return &p_id3d9devD3D9Device; }
    HUNTERCRY_API inline D3DPRESENT_PARAMETERS GetCurrentD3DPstParams() { return *p_d3dpstparamD3DPresentParameters; }
#endif

public:
#ifdef _WIN32
    HUNTERCRY_API HRESULT Clear(const DWORD& Count, const D3DRECT* pRects, const DWORD& Flags, const D3DCOLOR& Color, const float& Z, const DWORD& Stencil);
    HUNTERCRY_API HRESULT Present(const RECT* pSourceRect, CONST RECT* pDestRect, const HWND& hDestWindowOverride, CONST RGNDATA* pDirtyRegion);
#endif
};