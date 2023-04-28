// HunterDemoCry.cpp : A Demo of Cry Game Using Hunter Cry Engine
//

#include <stdio.h>
#include <stdlib.h>

#pragma comment(lib, "HunterCryEngine.lib")
#include "HunterCryEngine/HunterCry.h"

int RunGame();

int main(int argc, char** argv)
{
    int iResult = RunGame();

    printf("Cry Finished: Returns %d\n", iResult);
    printf("Press Enter to Continue.\n");
    int _i = getchar();

    exit(iResult);
}

int RunGame()
{
    HunterCry engine;
    HunterCry engine1;

    printf("Engines: %d\n", HunterCry::GetEnginesCount());

    return 0;
}
