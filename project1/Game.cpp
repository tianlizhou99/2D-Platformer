#include "pch.h"
#include "Game.h"
#include "Level.h"
#include "Wall.h"
#include "Platform.h"
#include "EndDoor.h"
#include "Character.h"
#include <map>
#include <tuple>
#include "Player.h"
#include "Money.h"
#include "President.h"
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

/** Draw the game
* \param graphics The GDI+ graphics context to draw on
*/
void CGame::OnDraw(Gdiplus::Graphics* graphics)
{
    if (mBackground != nullptr)
    {
        int width = static_cast<int>(mBackground->GetWidth());
        for (int iter = -width; iter <= mLevelWidth + 2 * width; iter += width)
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
                // Load level data from root
                if (root->GetName() == L"level")
                {
                    mLevelHeight = root->GetAttributeIntValue(L"height", 0);
                    mLevelWidth = root->GetAttributeIntValue(L"width", 0);
                }
                if (node->GetName() == L"declarations")
                {
                    for (auto node2 : node->GetChildren())
                    {
                        auto id = node2->GetAttributeValue(L"id", L"");
                        auto name = node2->GetName();
                        if (name == L"background")
                        {
                            background_declarations[id] = node2->GetAttributeValue(L"image", L"");
                            mBackground = unique_ptr<Gdiplus::Bitmap>(Gdiplus::Bitmap::FromFile((L"images/" + node2->GetAttributeValue(L"image", L"")).c_str()));
                        }
                        if (name == L"platform")
                        {
                            auto t = make_tuple(node2->GetAttributeValue(L"left-image", L""), node2->GetAttributeValue(L"mid-image", L""), node2->GetAttributeValue(L"right-image", L""));
                            platform_declarations[id] = t;
                        }
                        if (name == L"wall")
                        {
                            wall_declarations[id] = node2->GetAttributeValue(L"image", L"");
                        }
                        if (name == L"money")
                        {
                            auto t = make_tuple(node2->GetAttributeValue(L"image", L""), node2->GetAttributeIntValue(L"value", 0));
                            money_declarations[id] = t;
                        }
                        if (name == L"tuition-tip")
                        {
                            tuitionup_declarations[id] = node2->GetAttributeValue(L"image", L"");
                        }
                        if (name == L"door")
                        {
                            door_declarations[id] = node2->GetAttributeValue(L"image", L"");
                        }
                        if (name == L"villain")
                        {
                            villain_declarations[id] = node2->GetAttributeValue(L"image", L"");
                        }
                    }
                }
                if (node->GetName() == L"items")
                {
                    for (auto node2 : node->GetChildren())
                    {
                        auto id = node2->GetAttributeValue(L"id", L"");
                        auto name = node2->GetName();
                        if (name == L"platform")
                        {
                            auto leftimage = L"images/" + get<0>(platform_declarations[id]);
                            auto midimage = L"images/" + get<1>(platform_declarations[id]);
                            auto rightimage = L"images/" + get<2>(platform_declarations[id]);
                            auto entity = make_shared<CPlatform>(this, leftimage, midimage, rightimage);
                            entity->SetLocation(node2->GetAttributeIntValue(L"x", 0), node2->GetAttributeIntValue(L"y", 0));
                            entity->SetWidth(node2->GetAttributeIntValue(L"width", 0));
                            entity->SetHeight(node2->GetAttributeIntValue(L"height", 0));
                            Add(entity);
                        }
                        if (name == L"wall")
                        {
                            auto image = L"images/" + wall_declarations[id];
                            auto entity = make_shared<CWall>(this, image);
                            entity->SetLocation(node2->GetAttributeIntValue(L"x", 0), node2->GetAttributeIntValue(L"y", 0));
                            entity->SetWidth(node2->GetAttributeIntValue(L"width", 0));
                            entity->SetHeight(node2->GetAttributeIntValue(L"height", 0));
                            Add(entity);
                        }
                        if (name == L"money")
                        {
                            auto image = L"images/" + get<0>(money_declarations[id]);
                            auto entity = make_shared<CMoney>(this, image);
                            entity->SetLocation(node2->GetAttributeIntValue(L"x", 0), node2->GetAttributeIntValue(L"y", 0));
                            //entity->SetWorth(get<1>(money_declarations[id]));
                            Add(entity);
                        }
                        if (name == L"tuition-tip")
                        {
                            // needs to be changed to a tuitionup object
                            auto image = L"images/" + tuitionup_declarations[id];
                            auto entity = make_shared<CPresident>(this, image);
                            entity->SetLocation(node2->GetAttributeIntValue(L"x", 0), node2->GetAttributeIntValue(L"y", 0));
                            Add(entity);
                        }
                        if (name == L"door")
                        {
                            auto image = L"images/" + door_declarations[id];
                            auto entity = make_shared<CEndDoor>(this, image);
                            entity->SetLocation(node2->GetAttributeIntValue(L"x", 0), node2->GetAttributeIntValue(L"y", 0));
                            Add(entity);
                        }
                        if (name == L"villain")
                        {
                            auto image = L"images/" + villain_declarations[id];
                            auto entity = make_shared<CCharacter>(this, image);
                            entity->SetLocation(node2->GetAttributeIntValue(L"x", 0), node2->GetAttributeIntValue(L"y", 0));
                            Add(entity);
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

std::vector<double> CGame::ItemDistances(CPlayer* player)
{
    std::vector<double> pointsEarned;
    for (auto entity : mEntities)
    {
        if ((player != entity.get()) && (entity->GetWorth() != 0))
        {
            // Distance in the X and Y directions
            double dx = player->GetX() - entity->GetX();
            double dy = player->GetY() - entity->GetY();

            double distance = sqrt(dx * dx + dy * dy);
            if (distance == 0)
            {
                pointsEarned.push_back(entity->GetWorth());
            }
        }
    }
    return pointsEarned;
}

/** Accept a visitor for the collection
 * \param visitor The visitor for the collection
 *
void CGame::Accept(CVisitor* visitor)
{
    for (auto entity : mEntities)
    {
        entity->Accept(visitor);
    }
}*/