#include "pch.h"
#include "Game.h"
#include "Level.h"
#include "Wall.h"
#include "Platform.h"
#include "EndDoor.h"
using namespace std;

CGame::CGame()
{
    mLevelWidth = 0;
    mLevelHeight = 0;
}

CGame::~CGame()
{
}

/**
* Add an item to the game
* \param entity New item to add
*/
void CGame::Add(std::shared_ptr<CEntity> entity)
{
	mEntities.push_back(entity);
}

/**
* Handle a level node.
* \param node Pointer to XML node we are handling
*/
void CGame::XmlLevel(const std::shared_ptr<xmlnode::CXmlNode>& node)
{
    // A pointer for the item we are loading
    shared_ptr<CLevel> item;
}

/** Draw the game
* \param graphics The GDI+ graphics context to draw on
*/
void CGame::OnDraw(Gdiplus::Graphics* graphics)
{
    if (mBackground != nullptr)
    {
        for (int iter = -(int)mBackground->GetWidth(); iter * mBackground->GetWidth() < mLevelWidth + 2 * mBackground->GetWidth(); iter += mBackground->GetWidth())
        {
            graphics->DrawImage(mBackground.get(), iter, 0,
                mBackground->GetWidth(), mBackground->GetHeight());
        }
    }

    for (auto entity : mEntities)
    {
        entity->Draw(graphics);
    }
}

/** Loads a level
* \param filename The level file to load
* \returns void
*/
void CGame::Load(const std::wstring& filename)
{
    // We surround with a try/catch to handle errors
    try
    {
        // Open the document to read
        std::shared_ptr<CXmlNode> root = CXmlNode::OpenDocument(filename);

        // Once we know it is open, clear the existing data
        Clear();

        //
        // Traverse the children of the root
        // node of the XML document in memory!!!!
        //
        for (auto node : root->GetChildren())
        {
            if (node->GetType() == NODE_ELEMENT)
            {
                //setting the background image
                if (node->GetName() == L"background")
                {
                    mBackground = unique_ptr<Gdiplus::Bitmap>(Gdiplus::Bitmap::FromFile((L"images/" + node->GetAttributeValue(L"image", L"")).c_str()));
                }
                //setting the level width and height
                if (node->GetName() == L"level")
                {
                    mLevelHeight = node->GetAttributeIntValue(L"height", 0);
                    mLevelWidth = node->GetAttributeIntValue(L"width", 0);
                }
            }
        }

    }
    catch (CXmlNode::Exception ex)
    {
        AfxMessageBox(ex.Message().c_str());
    }

}

/**
 * Clear the game data.
 *
 * Deletes all known entities in the game.
 */
void CGame::Clear()
{
    mEntities.clear();
}

