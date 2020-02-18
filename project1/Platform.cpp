#include "pch.h"
#include "Platform.h"
#include "Game.h"

/// Left Industrial Platform filename
const wstring ImageNameIndLeft = L"images/platformIndustrial_059.png";

/// Center Industrial Platform filename
const wstring ImageNameIndCenter = L"images/platformIndustrial_060.png";

/// Right Industrial Platform filename
const wstring ImageNameIndRight = L"images/platformIndustrial_061.png";

/** Constructor
 * \param game The game this is a member of
*/
CPlatform::CPlatform(CGame* game) :
    CLevel(game, ImageNameIndCenter)
{
}

/**
 * Determines whether or not a platform is the left end
 * \param distances List of x axis distances between this platform and every other entity
 * \returns True if platform is not near another entity, false otherwise
 *
bool CPlatform::Left(std::vector<double> distances)
{
    for (double dist : distances)
    {
        if (dist == 32)
        {
            return false;
        }
    }
    return true;
}

/**
 * Determines whether or not a platform is the right end
 * \param distances List of x axis distances between this platform and every other entity
 * \returns True if platform is not near another entity, false otherwise
 *
bool CPlatform::Right(std::vector<double> distances)
{
    for (double dist : distances)
    {
        if (dist == -32)
        {
            return false;
        }
    }
    return true;
}

/**
 * Draw this item
 * \param graphics Graphics device to draw on
 *
void CPlatform::Draw(Gdiplus::Graphics* graphics)
{
    double wid = mPlatform->GetWidth();
    double hit = mPlatform->GetHeight();

    CGame* gamePointer = GetGame();

    std::vector<double> distances = gamePointer->PlatformDistances(this);
    bool left = Left(distances);
    bool right = Right(distances);

    if (left)
    {
        graphics->DrawImage(mPlatformLeft.get(),
            float(GetX() - wid / 2), float(GetY() - hit / 2),
            (float)mPlatform->GetWidth(), (float)mPlatform->GetHeight());
    }
    else if (right)
    {
        graphics->DrawImage(mPlatformRight.get(),
            float(GetX() - wid / 2), float(GetY() - hit / 2),
            (float)mPlatform->GetWidth(), (float)mPlatform->GetHeight());
    }
    else
    {
        graphics->DrawImage(mPlatform.get(),
            float(GetX() - wid / 2), float(GetY() - hit / 2),
            (float)mPlatform->GetWidth(), (float)mPlatform->GetHeight());
    }
}

/**
 * Load the attributes for a wall node.
 *
 * \param node The Xml node we are loading the entity from
 */
void CPlatform::XmlLoad(const std::shared_ptr<xmlnode::CXmlNode>& node)
{
    CEntity::XmlLoad(node);

    mHeight = node->GetAttributeDoubleValue(L"height", 0);
    mWidth = node->GetAttributeDoubleValue(L"width", 0);
}