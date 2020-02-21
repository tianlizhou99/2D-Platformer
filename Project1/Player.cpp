#include "pch.h"
#include "Player.h"
#include<string>

using namespace std;
using namespace Gdiplus;

const wstring GnomeImage = L"images/gnome.png";
CPlayer::CPlayer(CGame* game) : CCharacter(game, GnomeImage)
{
    SetLocation(521, 521);
}

std::shared_ptr<xmlnode::CXmlNode> CPlayer::XmlSave(const std::shared_ptr<xmlnode::CXmlNode>& node)
{
    auto itemNode = CCharacter::XmlSave(node);
    itemNode->SetAttribute(L"type", L"Player");
    return itemNode;
}

void CPlayer::Jump()
{
    mJumping = true;
}


void CPlayer::Update(double elapsed)
{
    if (mJumping)
    {
        // update time in jumping state
        mTime += elapsed;
        // set new vertical position
        SetLocation(GetX(), GetY() + elapsed * 10);
        // end jumping state after some point in time
        if (mTime == 1.5)
        {
            mTime = 0;
            mJumping = false;
        }
    }

}

void CPlayer::UpdateMove(double elapsed)
{

    SetLocation(GetX() + 500 * elapsed , GetY());

}