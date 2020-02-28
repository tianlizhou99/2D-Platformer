#include "pch.h"
#include "Wall.h"


/// Wall 1 filename
const wstring ImageNameWall1 = L"project1/images/wall1.png";

/// Wall 2 filename
const wstring ImageNameWall2 = L"project1/images/wall2.png";

/** Constructor
 * \param game The game this is a member of
*/
CWall::CWall(CGame* game) :
    CLevel(game, ImageNameWall1)
{
}

/**
 * Constructor
 * \param game The game we are in
 * \param filename Filename for the image we use
 */
CWall::CWall(CGame* game, wstring& filename) : CLevel(game, filename)
{
}

/// Small value to ensure we do not stay in collision
const double Epsilon = 0.01;

void CWall::Collision(CPlayer* player)
{
    auto PlayerVel = player->GetVelX();
    double Width = (this->GetWidth()) / 2;
    auto XLocation = this->GetX();
    double PlayerWidth = player->GetWidth() / 2;
    double PlayerY = player->GetY();
    double PlayerX = player->GetX();
    double PlayerHeight = player->GetHeight() / 2;
    auto YLocation = this->GetY();
    double Height = this->GetHeight() / 2;
    

     if (((PlayerY - PlayerHeight < YLocation - Height) && (PlayerY + PlayerHeight > YLocation - Height)) &&
         (PlayerY + PlayerHeight < YLocation ))
    {
        player->SetLocation(player->GetX(),YLocation - Height - Epsilon - PlayerHeight);
        player->SetVelY(0);
    }
    else if ((PlayerVel > 0) && (PlayerX < XLocation))
    {
        player->SetLocation(XLocation - Width - Epsilon - PlayerWidth, player->GetY());
        player->SetVelX(0);
    }
    else if ((PlayerVel < 0) && (PlayerX > XLocation))
    {
        player->SetLocation(XLocation + Width + Epsilon + PlayerWidth, player->GetY());
        player->SetVelX(0);
    }
}
