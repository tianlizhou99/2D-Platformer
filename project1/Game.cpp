#include "pch.h"
#include "Game.h"
#include "Level.h"
#include "Wall.h"
#include "Platform.h"
#include "EndDoor.h"
#include <map>
#include <tuple>
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
        
        // Load level data from root
        if (root->GetName() == L"level")
        {
            //mBackground = unique_ptr<Gdiplus::Bitmap>(Gdiplus::Bitmap::FromFile((L"images/" + root->GetAttributeValue(L"image", L"")).c_str()));
            mLevelHeight = root->GetAttributeIntValue(L"height", 0);
            mLevelWidth = root->GetAttributeIntValue(L"width", 0);
        }

        // Maps for declarations of each type 
        map<wstring, wstring> background_declarations;
        map<wstring, tuple<wstring, wstring, wstring>> platform_declarations;
        map<wstring, wstring> wall_declarations;
        map<wstring, tuple<wstring, int>> money_declarations;
        map<wstring, wstring> tuitionup_declarations;
        map<wstring, wstring> door_declarations;
        map<wstring, wstring> villain_declarations;

        //
        // Traverse the children of the root
        // node of the XML document in memory!!!!
        //
        for (auto node : root->GetChildren())
        {
            if (node->GetType() == NODE_ELEMENT)
            {
                if (node->GetName() == L"declarations")
                {
                    for (auto node2 : node->GetChildren())
                    {
                        if (node2->GetName() == L"background")
                        {
                            background_declarations[node2->GetAttributeValue(L"id", L"")] = node2->GetAttributeValue(L"image", L"");
                        }
                        if (node2->GetName() == L"platform")
                        {
                            auto t = make_tuple(node2->GetAttributeValue(L"left-image", L""), node2->GetAttributeValue(L"mid-image", L""), node2->GetAttributeValue(L"right-image", L""));
                            platform_declarations[node2->GetAttributeValue(L"id", L"")] = t;
                        }
                        if (node2->GetName() == L"wall")
                        {
                            wall_declarations[node2->GetAttributeValue(L"id", L"")] = node2->GetAttributeValue(L"image", L"");
                        }
                        if (node2->GetName() == L"money")
                        {
                            auto t = make_tuple(node2->GetAttributeValue(L"image", L""), node2->GetAttributeIntValue(L"value", 0));
                            money_declarations[node2->GetAttributeValue(L"id", L"")] = t;
                        }
                        if (node2->GetName() == L"tuition-tip")
                        {
                            tuitionup_declarations[node2->GetAttributeValue(L"id", L"")] = node2->GetAttributeValue(L"image", L"");
                        }
                        if (node2->GetName() == L"door")
                        {
                            door_declarations[node2->GetAttributeValue(L"id", L"")] = node2->GetAttributeValue(L"image", L"");
                        }
                        if (node2->GetName() == L"villain")
                        {
                            villain_declarations[node2->GetAttributeValue(L"id", L"")] = node2->GetAttributeValue(L"image", L"");
                        }
                    }
                }
                if (node->GetName() == L"items")
                {
                    for (auto node2 : node->GetChildren())
                    {
                        if (node2->GetName() == L"background")
                        {
                        }
                        if (node2->GetName() == L"platform")
                        {
                        }
                        if (node2->GetName() == L"wall")
                        {
                        }
                        if (node2->GetName() == L"money")
                        {
                        }
                        if (node2->GetName() == L"tuition-tip")
                        {
                        }
                        if (node2->GetName() == L"door")
                        {
                        }
                        if (node2->GetName() == L"villain")
                        {
                        }
                    }
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

/** Handle updates for animation
* \param elapsed The time since the last update
*/
void CGame::Update(double elapsed)
{
    for (auto item : mEntities)
    {
        item->Update(elapsed);
    }
}

