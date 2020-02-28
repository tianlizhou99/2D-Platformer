#include "pch.h"
#include "Platform.h"

/// Left Industrial Platform filename
const wstring ImageNameIndLeft = L"project1/images/platformIndustrial_059.png";

/// Center Industrial Platform filename
const wstring ImageNameIndCenter = L"project1/images/platformIndustrial_060.png";

/// Right Industrial Platform filename
const wstring ImageNameIndRight = L"project1/images/platformIndustrial_061.png";

/** Constructor
 * \param game The game this is a member of
*/
CPlatform::CPlatform(CGame* game) :
    CLevel(game, ImageNameIndCenter)
{
}

/**
 * Constructor
 * \param game The game we are in
 * \param filename Filename for the image we use
 */
CPlatform::CPlatform(CGame* game, const std::wstring& filename) : CLevel(game, filename)
{
}

void CPlatform::Collision(CPlayer* player)
{
    player->SetPlatformContact(true);


    double PlayerX = player->GetX();
    double PlayerY = player->GetY();
    double PlayerHeight = player->GetHeight() / 2;
    double PlayerWidth = player->GetWidth() / 2;
    double PlayerVelX = player->GetVelX();
    double PlayerVelY = player->GetVelY();

    double PlatformX = GetX();
    double PlatformY = GetY();
    double PlatformHeight = GetHeight() / 2;
    double PlatformWidth = GetWidth() / 2;

    if (PlayerVelY > 0)
    {
        player->SetLocation(PlayerX, PlatformY - PlatformHeight - PlayerHeight);
        
    }
    else if (PlayerVelY < 0)
    {
        player->SetLocation(PlayerX, PlatformY + PlatformHeight + PlayerHeight + 1);
    }
}
