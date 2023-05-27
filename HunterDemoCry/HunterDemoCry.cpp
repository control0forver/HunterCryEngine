// HunterDemoCry.cpp : A Demo of Cry Game Using Hunter Cry Engine
//

#include <stdio.h>
#include <stdlib.h>
#include <thread>
#include <functional>

//#pragma comment(lib, "HunterCryEngine.lib")
#include "HunterCryEngine/HunterCry.h"
#include "Utils/fps.hpp"

#include "SDL2/SDL.h"

int RunGame();
int RunGame1();

const int iFpsLimit = 120;

int main(int argc, char** argv)
{
    // std::thread t1(RunGame1);

    int iGame1Result = RunGame();

    // if (t1.joinable())
    //     t1.join();

    exit(0);
}

int RunGame()
{
    HunterCry engine = new IHunterCry("DemoCryWindow", "HunterDemoCry", 1360, 768, 60, false);

    printf("Engines: %d\n", IHunterCry::GetEnginesCount());

    engine->PreLoadEngine();
    if (!engine->InitializeEngine())
        return -1;

    engine->InitializeSDL2();

    HWND hwndWindow = engine->GetWindow()->hwndWindowHandle;
    CryDevice* device = engine->GetDevice();
    IDirect3DDevice9* d3d9Device = *device->GetD3D9DevicePtrPtr();

    ShowWindow(hwndWindow, SW_SHOW);
    UpdateWindow(hwndWindow);

    frame_rater<60> frFPSLimiter;
    frame_counter fcFPSCounter;

    struct Vertex
    {
        FLOAT x, y, z;
        DWORD color;
    }; 
    IDirect3DVertexBuffer9* g_pVB = NULL;
    DWORD g_dwNumTriangles = 1;
    auto Render = [&]()
    {
        static float fAngle = 0.0f;
        fAngle += 0.05f;

        D3DXMATRIX matWorld, matTranslate, matRotate;
        D3DXMatrixTranslation(&matTranslate, 0.0f, 0.0f, 0.0f);
        D3DXMatrixRotationY(&matRotate, fAngle);
        matWorld = matRotate * matTranslate;
        d3d9Device->SetTransform(D3DTS_WORLD, &matWorld);

        d3d9Device->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
            D3DCOLOR_XRGB(255, 255, 255), 1.0f, 0);

        d3d9Device->BeginScene();

        d3d9Device->SetFVF(D3DFVF_XYZ | D3DFVF_DIFFUSE);
        Vertex vertices[] =
        {
            { -1.0f, 0.0f, 0.0f, D3DCOLOR_XRGB(255, 244, 0) },
            {  0.0f, 1.0f, 0.0f, D3DCOLOR_XRGB(0, 255, 0) },
            {  1.0f, 0.0f, 0.0f, D3DCOLOR_XRGB(0, 0, 255) }
        };

        if (g_pVB == NULL)
        {
            d3d9Device->CreateVertexBuffer(sizeof(vertices),
                D3DUSAGE_WRITEONLY, D3DFVF_XYZ | D3DFVF_DIFFUSE,
                D3DPOOL_DEFAULT, &g_pVB, NULL);
        }

        VOID* pVertices;
        if (SUCCEEDED(g_pVB->Lock(0, sizeof(vertices), (void**)&pVertices, 0)))
        {
            memcpy(pVertices, vertices, sizeof(vertices));
            g_pVB->Unlock();
        }

        d3d9Device->SetStreamSource(0, g_pVB, 0, sizeof(Vertex));
        d3d9Device->DrawPrimitive(D3DPT_TRIANGLELIST, 0, g_dwNumTriangles);

        d3d9Device->EndScene();

        d3d9Device->Present(NULL, NULL, NULL, NULL);
    };

    auto GameMain = [&]() {
        MSG msg{};

        while (1)
        {
            if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
            {
                TranslateMessage(&msg);
                DispatchMessage(&msg);

                if (msg.message == WM_ACTIVATEAPP) {
                    if (msg.wParam == TRUE)
                    {
                        HRESULT hr = device->Reset();
                        if (SUCCEEDED(hr))
                        {
                        }
                    }
                    else
                    {
                        device->Release();

                        ShowWindow(hwndWindow, SW_RESTORE);
                        SetWindowLong(hwndWindow, GWL_STYLE, WS_OVERLAPPEDWINDOW);
                        SetWindowPos(hwndWindow, HWND_TOP, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_FRAMECHANGED);
                    }
                }

                if (msg.message == WM_SYSKEYDOWN && msg.wParam == VK_RETURN && (HIWORD(msg.lParam) & KF_ALTDOWN)) {
                    engine->SwitchFullscreen();
                }

                if (msg.message == WM_SYSKEYDOWN && msg.wParam == VK_END && (HIWORD(msg.lParam) & KF_ALTDOWN)) {
                    MessageBox(0, "", "", NULL);
                    static bool bVSync = false;
                    engine->SwitchVSync(bVSync);
                    bVSync = !bVSync;
                }

                if (msg.message == WM_QUIT)
                    return;
            }

            /*device->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_RGBA(44, 100, 100, 255), 0, 0);
            d3d9Device->BeginScene();


            d3d9Device->EndScene();
            device->Present(NULL, NULL, NULL, NULL);*/
            Render();

            fcFPSCounter.count();
            frFPSLimiter.sleep();
        }
    };

    GameMain();

    engine->ReleaseEngine();
    printf("Engines: %d\n", IHunterCry::GetEnginesCount());

    return 0;
}

int RunGame1()
{
    HunterCry engine = new IHunterCry("DemoCryWindow1", "HunterDemoCry1");

    printf("Engines: %d\n", IHunterCry::GetEnginesCount());

    if (!engine->InitializeEngine())
        return -1;

    HWND hwndWindow = engine->GetWindow()->hwndWindowHandle;
    CryDevice* device = engine->GetDevice();

    ShowWindow(hwndWindow, SW_SHOW);
    UpdateWindow(hwndWindow);


    auto GameMain = [&]() {
        MSG msg{};

        while (true)
        {
            if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
            {
                TranslateMessage(&msg);
                DispatchMessage(&msg);

                if (msg.message == WM_QUIT)
                    return;
            }

            device->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_RGBA(100, 88, 22, 255), 0, 0);
            device->Present(NULL, NULL, NULL, NULL);

            Sleep(1000 / iFpsLimit);
        }
    };

    GameMain();

    engine->ReleaseEngine();
    printf("Engines: %d\n", IHunterCry::GetEnginesCount());

    return 0;
}
