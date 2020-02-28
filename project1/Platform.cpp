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

/**
 * Constructor
 * \param game The game we are in
 * \param filename Filename for the image we use
 * \param type The type of plaform this is
 */
CPlatform::CPlatform(CGame* game, const std::wstring& filename, int type) : CLevel(game, filename)
{
    mType = type;
}

/**
  * Handle behavior on player collision
  */
void CPlatform::Collision(CPlayer* player)
{

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

    double PlayerLeft = PlayerX - PlayerWidth;
    double PlayerRight = PlayerX + PlayerWidth;
    double PlayerTop = PlayerY - PlayerHeight;
    double PlayerBottom = PlayerY + PlayerHeight;
    double PlatformLeft = PlatformX - PlatformWidth;
    double PlatformRight = PlatformX + PlatformWidth;
    double PlatformTop = PlatformY - PlatformHeight;
    double PlatformBottom = PlatformY + PlatformHeight;

    double spacer = 32;

    if (mType == -1 && PlayerRight - PlatformLeft <= spacer)
    {
        player->SetLocation(PlatformLeft - PlayerWidth, PlayerY);
    }
    else if (mType == 1 && PlatformRight - PlayerLeft <= spacer)
    {
        player->SetLocation(PlatformRight + PlayerWidth, PlayerY);
    }
    else if (PlayerVelY > 0)
    {
        player->SetLocation(PlayerX, PlatformTop - PlayerHeight);
        player->SetVelY(0);
    }
    else if (PlayerVelY < 0)
    {
        player->SetLocation(PlayerX, PlatformBottom + PlayerHeight + 1);
        player->SetVelY(0);
    }
    else 
    {
        player->SetGroundContact(true);
    }
}
