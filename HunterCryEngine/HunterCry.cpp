#include "HunterCry.h"

#pragma region Static Datas

#pragma region Public
#pragma endregion
#pragma region Private
unsigned int HunterCry::u_iEnginesCount = 0;
#pragma endregion
#pragma region Public Gets
unsigned int HunterCry::GetEnginesCount()
{
    return u_iEnginesCount;
}
void HunterCry::GetEnginesCount(unsigned int* const p_u_iEnginesCount)
{
    *p_u_iEnginesCount = u_iEnginesCount;
}
#pragma endregion

#pragma endregion


#pragma region Class Datas

#pragma region Public
HunterCry::HunterCry()
{

    // Success
    ++u_iEnginesCount;
}

HunterCry::~HunterCry()
{

    // Success
    --u_iEnginesCount;
}

#pragma endregion
#pragma region Private
#pragma endregion

#pragma endregion