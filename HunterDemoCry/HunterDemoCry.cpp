// HunterDemoCry.cpp : A Demo of Cry Game Using Hunter Cry Engine
//

#include <stdio.h>
#include <stdlib.h>
#include <thread>
#include <functional>

#pragma comment(lib, "HunterCryEngine.lib")
#include "HunterCryEngine/HunterCry.h"

int RunGame();
int RunGame1();

const int iFpsLimit = 15;

int main(int argc, char** argv)
{
    std::thread t1(RunGame1);
    t1.detach();

    int iGame1Result = RunGame();

    if (t1.joinable())
        t1.join();

    exit(0);
}

LRESULT CALLBACK DefaultWndProc(HWND hwndWindow, UINT iMessage, WPARAM wparamWParam, LPARAM lparamLParam) {
    switch (iMessage)
    {
    case WM_PAINT:
        //ValidateRect(hwndWindow, NULL);
        break;
    case WM_DESTROY:
        PostQuitMessage(wparamWParam);
        break;
    }
    return DefWindowProc(hwndWindow, iMessage, wparamWParam, lparamLParam);
}

LRESULT CALLBACK DefaultWndProc1(HWND hwndWindow, UINT iMessage, WPARAM wparamWParam, LPARAM lparamLParam) {
    switch (iMessage)
    {
    case WM_PAINT:
        //ValidateRect(hwndWindow, NULL);
        break;
    case WM_DESTROY:
        PostQuitMessage(wparamWParam);
        break;
    }
    return DefWindowProc(hwndWindow, iMessage, wparamWParam, lparamLParam);
}

int RunGame()
{
    HunterCry engine = new IHunterCry("DemoCryWindow", "HunterDemoCry");

    printf("Engines: %d\n", IHunterCry::GetEnginesCount());

    if (!engine->InitializeEngine())
        return -1;

    HWND hwndWindow = engine->GetWindow()->hwndWindowHandle;
    IDirect3DDevice9* device = engine->GetDevice()->p_id3d9devD3D9Device;

    ShowWindow(hwndWindow, SW_SHOW);
    UpdateWindow(hwndWindow);


    auto GameMain = [&]() {
        MSG msg{};

        while (1)
        {
            if (PeekMessage(&msg, hwndWindow, 0, 0, PM_REMOVE))
            {
                TranslateMessage(&msg);
                DispatchMessage(&msg);

                if (msg.message == WM_QUIT)
                    return;
            }

            device->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_RGBA(44, 100, 100, 255), 0, 0);
            device->Present(NULL, NULL, NULL, NULL);
            
            Sleep(1000/ iFpsLimit);
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
    IDirect3DDevice9* device = engine->GetDevice()->p_id3d9devD3D9Device;

    ShowWindow(hwndWindow, SW_SHOW);
    UpdateWindow(hwndWindow);


    auto GameMain = [&]() {
        MSG msg{};

        while (true)
        {
            if (PeekMessage(&msg, hwndWindow, 0, 0, PM_REMOVE))
            {
                TranslateMessage(&msg);
                DispatchMessage(&msg);

                if (msg.message == WM_QUIT)
                    return;
            }

            device->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_RGBA(100, 88, 22, 255), 0, 0);
            device->Present(NULL, NULL, NULL, NULL);

            Sleep(1000/ iFpsLimit);
        }
    };

    GameMain();

    engine->ReleaseEngine();
    printf("Engines: %d\n", IHunterCry::GetEnginesCount());

    return 0;
}
