#include "pch.h"
#include "Entity.h"
#include "XmlNode.h"
using namespace xmlnode;

using namespace Gdiplus;
//using namespace xmlnode;

void CEntity::SetLocation(double x, double y)
{
    mX = x;
    mY = y;
}

/**
 * Destructor
 */
CEntity::~CEntity()
{
}

/**
 * Constructor
 * \param game The game this Entity is a member of
 * \param filename The name of the file storing image to add
 */
CEntity::CEntity(CGame* game, const std::wstring& filename) : mGame(game)
{
    mEntityImage = std::unique_ptr<Bitmap>(Bitmap::FromFile(filename.c_str()));
    if (mEntityImage->GetLastStatus() != Ok)
    {
        std::wstring msg(L"Failed to open ");
        msg += filename;
        AfxMessageBox(msg.c_str());
    }
}

/**
 * Draw this entity
 * \param graphics Graphics device to draw on
 */
void CEntity::Draw(Gdiplus::Graphics* graphics)
{
    double wid = mEntityImage->GetWidth();
    double hit = mEntityImage->GetHeight();

    if (mYMirror)
    {
        graphics->DrawImage(mEntityImage.get(),
            float(GetX() - wid / 2), float(GetY() + hit / 2),
            (float)mEntityImage->GetWidth(), -(float)mEntityImage->GetHeight());
    }
    else
    {
        graphics->DrawImage(mEntityImage.get(),
            float(GetX() - wid / 2), float(GetY() - hit / 2),
            (float)mEntityImage->GetWidth(), (float)mEntityImage->GetHeight());
    }
}

/**
 * Load the attributes for an item node.
 * \param node The Xml node we are loading the item from
 */
void CEntity::XmlLoad(const std::shared_ptr<xmlnode::CXmlNode>& node)
{
    mX = node->GetAttributeDoubleValue(L"x", 0);
    mY = node->GetAttributeDoubleValue(L"y", 0);
}

std::shared_ptr<xmlnode::CXmlNode> CEntity::XmlSave(const std::shared_ptr<xmlnode::CXmlNode>& node)
{
    auto itemNode = node->AddChild(L"entity");

    itemNode->SetAttribute(L"x", mX);
    itemNode->SetAttribute(L"y", mY);

    return itemNode;
}
