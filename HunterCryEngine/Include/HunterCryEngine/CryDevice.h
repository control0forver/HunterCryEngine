#pragma once
#ifdef _WIN32
#include <Windows.h>
#include <d3d9.h>
#pragma comment(lib, "d3d9.lib")
#endif

class CryDevice {
public:
#ifdef _WIN32
    CryDevice(D3DDEVTYPE d3ddevtDeviceType = D3DDEVTYPE_HAL) {
        this->d3ddevtDeviceType = d3ddevtDeviceType;
    }
    ~CryDevice() {
        p_id3d9D3D9->Release();
        p_id3d9devD3D9Device->Release();
    }
#endif

public:
    // !Do not try to change these items!
    int iDeviceWidth = 0;
    int iDeviceHeight = 0;

#ifdef _WIN32
    IDirect3D9* p_id3d9D3D9 = nullptr;
    D3DCAPS9* p_d3d9capsCaps = nullptr;
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

    D3DPRESENT_PARAMETERS* p_d3dpstparamD3DPresentParameters = nullptr;
    IDirect3DDevice9* p_id3d9devD3D9Device = nullptr;
#endif

private:
    void GetCaptures();
    void CheckVertexProcessing();

public:
    virtual void ErrCreatingD3D9Device(HRESULT hrResult) {}

public:
    void MakeD3DPstParams();

public:
#ifdef _WIN32
    const IDirect3D9* CreateD3D9();
    const IDirect3DDevice9* CreateD3D9Device();

    int Create(int iWidth, int iHeight, HWND hwndWindow);

    void Release();
#endif
};