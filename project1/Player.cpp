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

const double JumpSpeed = -750;
const double Gravity = 750;

CPlayer::CPlayer(CGame* game) : CCharacter(game, GnomeImage)
{
}

std::shared_ptr<xmlnode::CXmlNode> CPlayer::XmlSave(const std::shared_ptr<xmlnode::CXmlNode>& node)
{
    auto itemNode = CCharacter::XmlSave(node);
    itemNode->SetAttribute(L"type", L"Player");
    return itemNode;
}

/**
 * cause player to jump
 */
void CPlayer::Jump()
{
    mGroundContact = false;

    auto Game = GetGame();
    Game->CollisionTest(this);

    if (mGroundContact)
    {
        SetLocation(GetX(), GetY() - 1);
        mVelY = JumpSpeed;
    }
}

void CPlayer::Loss()
{
    mGroundContact = false;
}

/**
 * updating the player based on the time elapsed
 * \param elapsed the amount of time that has passed since update was called
 */
void CPlayer::Update(double elapsed)
{
    mTimer += (elapsed > 0) ? elapsed : -elapsed;

    ///Update position based on gravity and current velocity
    SetLocation(GetX() + (mDistanceX * mVelX), GetY() + mVelY * elapsed + .5 * Gravity * elapsed * elapsed);

    ///Update y velocity based on gravity and current y velocity
    mVelY += Gravity * elapsed;

    auto Game = GetGame();
    Game->CollisionTest(this);
}

/**
 * Draws the player based on the keys being pressed
 * \param graphics the graphics tool used to draw the player
 */
void CPlayer::Draw(Gdiplus::Graphics* graphics)
{
    if ((mVelX == 0))
    {
        std::unique_ptr<Gdiplus::Bitmap> GnomeImage_img = unique_ptr<Bitmap>(Bitmap::FromFile(GnomeImage.c_str()));
        double wid = GetImage()->GetWidth();
        double hit = GetImage()->GetHeight();

        graphics->DrawImage(GnomeImage_img.get(),
            float(GetX() - wid / 2), float(GetY() - hit / 2),
            (float)GetImage()->GetWidth(), (float)GetImage()->GetHeight());
    }
    else if ((mVelY != 0) && (mVelX > 0))
    {
        mTimer = 0;

        std::unique_ptr<Gdiplus::Bitmap> GnomeRight1_image = unique_ptr<Bitmap>(Bitmap::FromFile(GnomeRight1.c_str()));
        double wid = GetImage()->GetWidth();
        double hit = GetImage()->GetHeight();

        graphics->DrawImage(GnomeRight1_image.get(),
            float(GetX() - wid / 2), float(GetY() - hit / 2),
            (float)GetImage()->GetWidth(), (float)GetImage()->GetHeight());
    }
    else if ((mVelY != 0) && (mVelX < 0))
    {
        mTimer = 0;
        std::unique_ptr<Gdiplus::Bitmap> GnomeLeft1_image = unique_ptr<Bitmap>(Bitmap::FromFile(GnomeLeft1.c_str()));
        double wid = GetImage()->GetWidth();
        double hit = GetImage()->GetHeight();

        graphics->DrawImage(GnomeLeft1_image.get(),
            float(GetX() - wid / 2), float(GetY() - hit / 2),
            (float)GetImage()->GetWidth(), (float)GetImage()->GetHeight());
    }

    if ((mTimer >= 1))
    {
        mTimer = 0;
    }

    if ((mTimer <= .5) && mVelX > 0)
    {
        std::unique_ptr<Gdiplus::Bitmap> GnomeRight1_image = unique_ptr<Bitmap>(Bitmap::FromFile(GnomeRight1.c_str()));
        double wid = GetImage()->GetWidth();
        double hit = GetImage()->GetHeight();

        graphics->DrawImage(GnomeRight1_image.get(),
            float(GetX() - wid / 2), float(GetY() - hit / 2),
            (float)GetImage()->GetWidth(), (float)GetImage()->GetHeight());
    }
    else if ((mTimer <= 1) && mVelX > 0)
    {
        std::unique_ptr<Gdiplus::Bitmap> GnomeRight2_image = unique_ptr<Bitmap>(Bitmap::FromFile(GnomeRight2.c_str()));
        double wid = GetImage()->GetWidth();
        double hit = GetImage()->GetHeight();

        graphics->DrawImage(GnomeRight2_image.get(),
            float(GetX() - wid / 2), float(GetY() - hit / 2),
            (float)GetImage()->GetWidth(), (float)GetImage()->GetHeight());
    }

    if ((mTimer <= .5) && mVelX < 0)
    {
        std::unique_ptr<Gdiplus::Bitmap> GnomeLeft1_image = unique_ptr<Bitmap>(Bitmap::FromFile(GnomeLeft1.c_str()));
        double wid = GetImage()->GetWidth();
        double hit = GetImage()->GetHeight();

        graphics->DrawImage(GnomeLeft1_image.get(),
            float(GetX() - wid / 2), float(GetY() - hit / 2),
            (float)GetImage()->GetWidth(), (float)GetImage()->GetHeight());
    }
    else if ((mTimer <= 1) && mVelX < 0)
    {
        std::unique_ptr<Gdiplus::Bitmap> GnomeLeft2_image = unique_ptr<Bitmap>(Bitmap::FromFile(GnomeLeft2.c_str()));
        double wid = GetImage()->GetWidth();
        double hit = GetImage()->GetHeight();

        graphics->DrawImage(GnomeLeft2_image.get(),
            float(GetX() - wid / 2), float(GetY() - hit / 2),
            (float)GetImage()->GetWidth(), (float)GetImage()->GetHeight());
    }

}
