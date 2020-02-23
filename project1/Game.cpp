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

/// Game area height in virtual pixels
const static int Height = 1024;

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
* \param width The width of the screen
* \param height The height of the screen
* \param scrollX The amount of scrolling done through game
*/
void CGame::OnDraw(Gdiplus::Graphics* graphics, int width, int height, int scrollX)
{
    //
    // Automatic Scaling
    //
    mScale = float(height) / float(Height);
    graphics->ScaleTransform(mScale, mScale);

    // Determine the virtual width
    float virtualWidth = (float)width / mScale;

    // Save current settings
    auto save = graphics->Save();


    // Keep centered on half virtual window width
    graphics->TranslateTransform(scrollX + virtualWidth/2, 0);

    if (mBackground != nullptr)
    {
       
        int width = static_cast<int>(mBackground->GetWidth());
        for (int iter = -width * 5; iter <= mLevelWidth + 5 * width; iter += width - 5)
        {
            graphics->DrawImage(mBackground.get(), iter , 0,
                mBackground->GetWidth(), mBackground->GetHeight());

        }

    }
    // Keep centered on half virtual window width
    graphics->TranslateTransform(-virtualWidth / 3, 0);
    for (auto entity : mEntities)
    {
        entity->Draw(graphics);
       
        
    }

    // Remove centering on half virtual window width
    graphics->Restore(save);
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
                    mStartX = root->GetAttributeIntValue(L"start-x", 0);
                    mStartY = root->GetAttributeIntValue(L"start-y", 0);
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
                        if (name == L"tuition-up")
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
                            auto x = node2->GetAttributeIntValue(L"x", 0);
                            auto y = node2->GetAttributeIntValue(L"y", 0);
                            auto width = node2->GetAttributeIntValue(L"width", 0);
                            auto height = node2->GetAttributeIntValue(L"height", 0);
                            LoadPlatform(leftimage, midimage, rightimage, x, y, width, height);
                        }
                        if (name == L"wall")
                        {
                            auto image = L"images/" + wall_declarations[id];
                            auto x = node2->GetAttributeIntValue(L"x", 0);
                            auto y = node2->GetAttributeIntValue(L"y", 0);
                            auto width = node2->GetAttributeIntValue(L"width", 0);
                            auto height = node2->GetAttributeIntValue(L"height", 0);
                            LoadWall(image, x, y, width, height);
                        }
                        if (name == L"money")
                        {
                            auto image = L"images/" + get<0>(money_declarations[id]);
                            auto entity = make_shared<CMoney>(this, image);
                            entity->SetLocation(node2->GetAttributeIntValue(L"x", 0), node2->GetAttributeIntValue(L"y", 0));
                            entity->SetTextLocation(node2->GetAttributeIntValue(L"x", 0), node2->GetAttributeIntValue(L"y", 0));
                            entity->SetWorth(get<1>(money_declarations[id]));
                            Add(entity);
                        }
                        if (name == L"tuition-up")
                        {
                            // needs to be changed to a tuitionup object
                            auto image = L"images/" + tuitionup_declarations[id];
                            auto entity = make_shared<CPresident>(this, image);
                            entity->SetLocation(node2->GetAttributeIntValue(L"x", 0), node2->GetAttributeIntValue(L"y", 0));
                            entity->SetTextLocation(node2->GetAttributeIntValue(L"x", 0), node2->GetAttributeIntValue(L"y", 0));
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
                            entity->SetStart(node2->GetAttributeIntValue(L"y", 0));
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
* \return void
*/
void CGame::Update(double elapsed)
{
    for (auto item : mEntities)
    {
        item->Update(elapsed);

    }

    if (mTimer < 0.5) mGameState = start;
    else if (mTimer > 0.5) mGameState = progress;
    //TODO other game state detections
}



/**
 * Handles loading platform into Game class
 * \param leftimage Left image to use
 * \param midimage Middle image to use
 * \param rightimage Right image to use
 * \param x X position of center of platform
 * \param y Y position of center of platform
 * \param width Width of platform
 * \param height Height of platform
 */
void CGame::LoadPlatform(wstring leftimage, wstring midimage, wstring rightimage, int x, int y, int width, int height)
{
    double count = width / 32;
    double leftx = x - ((count - 1) / 2) * 32;
    double rightx = x + ((count - 1) / 2) * 32;
    auto leftplatform = make_shared<CPlatform>(this, leftimage);
    leftplatform->SetLocation(leftx, y);
    Add(leftplatform);
    auto rightplatform = make_shared<CPlatform>(this, rightimage);
    rightplatform->SetLocation(rightx, y);
    Add(rightplatform);
    for (double i = 1; i <= count - 2; i++)
    {
        auto midplatform = make_shared<CPlatform>(this, midimage);
        double offset = i * 32;
        midplatform->SetLocation(leftx + offset, y);
        Add(midplatform);
    }
}

/**
 * Handles loading wall into Game class
 * \param image Image to use
 * \param x X position of center of wall
 * \param y Y position of center of wall
 * \param width Width of wall
 * \param height Height of wall
 */
void CGame::LoadWall(wstring image, int x, int y, int width, int height)
{
    double count = height / 32;
    double topy = y - ((count - 1) / 2) * 32;
    for (double i = 0; i <= count - 1; i++)
    {
        auto wall = make_shared<CWall>(this, image);
        double offset = i * 32;
        wall->SetLocation(x, topy + offset);
        Add(wall);
    }
}

/**
 * Checks for player collision with entity
 * \param player Height of wall
 */
void CGame::CollisionTest(CPlayer* player)
{
    double PlayerX = player->GetX();
    double PlayerY = player->GetY();
    double PlayerHeight = player->GetHeight() / 2;
    double PlayerWidth = player->GetWidth() / 2;

    for (auto entity : mEntities)
    {
        double EntityX = entity->GetX();
        double EntityY = entity->GetY();
        double EntityHeight = entity->GetHeight() / 2;
        double EntityWidth = entity->GetWidth() / 2;

        if (entity.get() == player)
        {
            continue;
        }

        if ((PlayerX + PlayerWidth >= EntityX - EntityWidth) && (PlayerX + PlayerWidth <= EntityX + EntityWidth))
        {
            if ((EntityY + EntityHeight >= PlayerY - PlayerHeight) && (EntityY + EntityHeight <= PlayerY + PlayerHeight))
            {
                entity->Collision(player);
            }
            else if ((EntityY - EntityHeight >= PlayerY - PlayerHeight) && (EntityY - EntityHeight <= PlayerY + PlayerHeight))
            {
                entity->Collision(player);
            }
        }
        else if ((PlayerX - PlayerWidth >= EntityX - EntityWidth) && (PlayerX - PlayerWidth <= EntityX + EntityWidth))
        {
            if ((EntityY + EntityHeight >= PlayerY - PlayerHeight) && (EntityY + EntityHeight <= PlayerY + PlayerHeight))
            {
                entity->Collision(player);
            }
            else if ((EntityY - EntityHeight >= PlayerY - PlayerHeight) && (EntityY - EntityHeight <= PlayerY + PlayerHeight))
            {
                entity->Collision(player);
            }
        }

        if((PlayerY + PlayerHeight >= EntityY - EntityHeight) && (PlayerY + PlayerHeight <= EntityY + EntityWidth))
        {
            if ((EntityX + EntityWidth >= PlayerX - PlayerWidth) && (EntityX + EntityWidth <= PlayerX + PlayerWidth))
            {
                entity->Collision(player);
            }
            else if ((EntityX - EntityWidth >= PlayerX - PlayerWidth) && (EntityX - EntityWidth <= PlayerX + PlayerWidth))
            {
                entity->Collision(player);
            }
        }
        else if ((PlayerY - PlayerHeight >= EntityY - EntityHeight) && (PlayerY - PlayerHeight <= EntityY + EntityWidth))
        {
            if ((EntityX + EntityWidth >= PlayerX - PlayerWidth) && (EntityX + EntityWidth <= PlayerX + PlayerWidth))
            {
                entity->Collision(player);
            }
            else if ((EntityX - EntityWidth >= PlayerX - PlayerWidth) && (EntityX - EntityWidth <= PlayerX + PlayerWidth))
            {
                entity->Collision(player);
            }
        }
    }

}