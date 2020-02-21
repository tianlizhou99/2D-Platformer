#include "pch.h"
#include "Player.h"
#include<string>
#include <memory>

using namespace std;
using namespace Gdiplus;

const wstring GnomeImage = L"images/gnome.png";
const wstring GnomeRight1 = L"images/gnome-walk-right-1.png";
const wstring GnomeRight2 = L"images/gnome-walk-right-2.png";
const wstring GnomeLeft1 = L"images/gnome-walk-left-1.png";
const wstring GnomeLeft2 = L"images/gnome-walk-left-2.png";
CPlayer::CPlayer(CGame* game) : CCharacter(game, GnomeImage)
{
   /// SetLocation(788, 796);
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


/**
 * updating the player based on the time elapsed
 * \param elapsed the amount of time that has passed since update was called
 */
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

    auto Game = GetGame();
    Game->CollisionTest(this);

}

void CPlayer::UpdateMove(double elapsed)
{

    SetLocation(GetX() + 500 * elapsed , GetY());
    if (elapsed > 0)
    {
        mTimer += elapsed;
    }
    else if (elapsed < 0)
    {
        mTimer += -elapsed;
    }
    mVel = elapsed;

}

/**
 * Draws the player based on the keys being pressed
 * \param graphics the graphics tool used to draw the player
 */
void CPlayer::Draw(Gdiplus::Graphics* graphics)
{
    if ((mVel == 0))
    {
        std::unique_ptr<Gdiplus::Bitmap> GnomeImage_img = unique_ptr<Bitmap>(Bitmap::FromFile(GnomeImage.c_str()));
        double wid = GetImage()->GetWidth();
        double hit = GetImage()->GetHeight();

        graphics->DrawImage(GnomeImage_img.get(),
            float(GetX() - wid / 2), float(GetY() - hit / 2),
            (float)GetImage()->GetWidth(), (float)GetImage()->GetHeight());
    }
    
    if ((mTimer >= 1))
    {
        mTimer = 0;
    }
    
    if ((mTimer <= .5) && mVel > 0)
    {
        std::unique_ptr<Gdiplus::Bitmap> GnomeRight1_image = unique_ptr<Bitmap>(Bitmap::FromFile(GnomeRight1.c_str()));
        double wid = GetImage()->GetWidth();
        double hit = GetImage()->GetHeight();

        graphics->DrawImage(GnomeRight1_image.get(),
            float(GetX() - wid / 2), float(GetY() - hit / 2),
            (float)GetImage()->GetWidth(), (float)GetImage()->GetHeight());
    }
    else if ((mTimer <= 1) && mVel > 0)
    {
        std::unique_ptr<Gdiplus::Bitmap> GnomeRight2_image = unique_ptr<Bitmap>(Bitmap::FromFile(GnomeRight2.c_str()));
        double wid = GetImage()->GetWidth();
        double hit = GetImage()->GetHeight();

        graphics->DrawImage(GnomeRight2_image.get(),
            float(GetX() - wid / 2), float(GetY() - hit / 2),
            (float)GetImage()->GetWidth(), (float)GetImage()->GetHeight());
    }

    if ((mTimer <= .5) && mVel < 0)
    {
        std::unique_ptr<Gdiplus::Bitmap> GnomeLeft1_image = unique_ptr<Bitmap>(Bitmap::FromFile(GnomeLeft1.c_str()));
        double wid = GetImage()->GetWidth();
        double hit = GetImage()->GetHeight();

        graphics->DrawImage(GnomeLeft1_image.get(),
            float(GetX() - wid / 2), float(GetY() - hit / 2),
            (float)GetImage()->GetWidth(), (float)GetImage()->GetHeight());
    }
    else if ((mTimer <= 1) && mVel < 0)
    {
        std::unique_ptr<Gdiplus::Bitmap> GnomeLeft2_image = unique_ptr<Bitmap>(Bitmap::FromFile(GnomeLeft2.c_str()));
        double wid = GetImage()->GetWidth();
        double hit = GetImage()->GetHeight();

        graphics->DrawImage(GnomeLeft2_image.get(),
            float(GetX() - wid / 2), float(GetY() - hit / 2),
            (float)GetImage()->GetWidth(), (float)GetImage()->GetHeight());
    }
    
}
