#include "HunterCryEngine/CryDevice.h"

#pragma region  Private Methods

void CryDevice::GetCaptures()
{
    p_d3d9capsCaps = new D3DCAPS9();

    p_id3d9D3D9->GetDeviceCaps(D3DADAPTER_DEFAULT, d3ddevtDeviceType, p_d3d9capsCaps);
}

void CryDevice::CheckVertexProcessing()
{
    if (!p_d3d9capsCaps)
        GetCaptures();

    if (p_d3d9capsCaps->DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT)
        iVertexProcessing = D3DCREATE_HARDWARE_VERTEXPROCESSING;
    else
        iVertexProcessing = D3DCREATE_SOFTWARE_VERTEXPROCESSING;
}

#pragma endregion

void CryDevice::MakeD3DPstParams()
{
    p_d3dpstparamD3DPresentParameters = new D3DPRESENT_PARAMETERS{
        (unsigned int)iDeviceWidth, (unsigned int)iDeviceHeight,
        d3dfmtD3DBackbufferFormat, (unsigned int)iD3DBackbuffersCount,
        d3dmltsmptD3DMultiSampleType, (unsigned int)iD3DMultiSampleQuality,
        d3dswpefctD3DSwapEffect,
        hwndD3DWindow, iD3DWindowed,
        iD3DEnableAutoDepthStencil, d3dfmtD3DAutoDepthStencilFormat,
        (unsigned int)iD3DPresentFlags,
        (unsigned int)iD3DFullScreen_RefreshRateInHz,(unsigned int)iD3DPresentationInterval
    };
}

inline void CryDevice::MakeD3DPstParams(D3DPRESENT_PARAMETERS d3dpstparamD3DPresentParameters)
{
    *p_d3dpstparamD3DPresentParameters = d3dpstparamD3DPresentParameters;
}

void CryDevice::Reset(bool bAutoMakePP)
{
    if (bAutoMakePP)
        MakeD3DPstParams();

    p_id3d9devD3D9Device->Reset(p_d3dpstparamD3DPresentParameters);
}

void CryDevice::Reset(D3DPRESENT_PARAMETERS p_d3dpstparamD3DPresentParameters)
{
    p_id3d9devD3D9Device->Reset(&p_d3dpstparamD3DPresentParameters);
}


const IDirect3D9* CryDevice::CreateD3D9()
{
    if (p_id3d9D3D9) {
        p_id3d9D3D9->Release();
        delete p_id3d9D3D9;
    }

    p_id3d9D3D9 = Direct3DCreate9(D3D_SDK_VERSION);
    if (!p_id3d9D3D9)
        return NULL;

    CheckVertexProcessing();

    return p_id3d9D3D9;
}

const IDirect3DDevice9* CryDevice::CreateD3D9Device()
{
    HRESULT hrResultHandle =
        p_id3d9D3D9->CreateDevice(
            D3DADAPTER_DEFAULT,
            d3ddevtDeviceType,
            hwndD3DWindow,
            iVertexProcessing,
            p_d3dpstparamD3DPresentParameters,
            &p_id3d9devD3D9Device
        );

    if (FAILED(hrResultHandle))
        ErrCreatingD3D9Device(hrResultHandle);

    return p_id3d9devD3D9Device;
}

int CryDevice::Create(int iWidth, int iHeight, bool bFullscreen, HWND hwndWindow)
{
    if (!CreateD3D9())
        return false;

    this->iD3DBackbuffersCount = 1;
    this->iDeviceWidth = iWidth;
    this->iDeviceHeight = iHeight;
    this->hwndD3DWindow = hwndWindow;
    this->iD3DPresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;
    this->iD3DWindowed = !bFullscreen;
    this->iD3DEnableAutoDepthStencil = true;
    this->d3dfmtD3DBackbufferFormat = D3DFMT_A8R8G8B8;
    this->d3dfmtD3DAutoDepthStencilFormat = D3DFMT_D24S8;
    this->d3dswpefctD3DSwapEffect = D3DSWAPEFFECT_DISCARD;
    MakeD3DPstParams();

    if (!CreateD3D9Device())
        return false;

    return true;
}

void CryDevice::Release()
{
    delete this;
}

HRESULT CryDevice::Clear(const DWORD & Count, const D3DRECT * pRects,const DWORD & Flags, const D3DCOLOR & Color, const float& Z, const DWORD & Stencil)
{
    if (!bReleased)
        return p_id3d9devD3D9Device->Clear(Count, pRects, Flags, Color, Z, Stencil);
    return 0;
}

HRESULT CryDevice::Present(const RECT * pSourceRect, CONST RECT * pDestRect, const HWND & hDestWindowOverride, CONST RGNDATA * pDirtyRegion)
{
    if (!bReleased)
        return p_id3d9devD3D9Device->Present(pSourceRect, pDestRect, hDestWindowOverride, pDirtyRegion);
    return 0;
}
