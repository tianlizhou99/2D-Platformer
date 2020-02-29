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
#include "FarmLaneWalkSign.h"
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
* Add an item to the game, loads later than other objects
* \param entity New item to add
*/
void CGame::AddFront(std::shared_ptr<CEntity> entity)
{
    mEntities.insert(mEntities.begin(), entity);
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
    mVScale = float(height) / float(1024);
    mHScale = float(width) / float(1024);
    graphics->ScaleTransform(mVScale, mVScale);

    // Determine the virtual width
    float virtualWidth = (float)width * mHScale;
    float virtualHeight = (float)height * mVScale;

    // Save current settings
    auto save = graphics->Save();


    // Keep centered on half virtual window width
    graphics->TranslateTransform(scrollX + virtualWidth/virtualHeight, 0);

    if (mBackground != nullptr)
    {
        //Infinite background based on how stretched the screen is
        int width = static_cast<int>(mBackground->GetWidth());
        for (int iter = -width * (int)(2 / mVScale); iter <= mLevelWidth + (int)(2 / mVScale) * width; iter += width - (int)(2 / mVScale))
        {
            graphics->DrawImage(mBackground.get(), iter - 1 , 0,
                mBackground->GetWidth(), mBackground->GetHeight());
        }

    }

    for (auto entity : mEntities)
    {
        //Frustum Culling: only renders the elements that should be in view to save resources and improve performance
        if (entity->GetX() < -scrollX + (int)(2 / mVScale) * virtualWidth && entity->GetX() > scrollX - virtualWidth * (int)(2 / mVScale))
        {
            entity->Draw(graphics);
        }
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
        mGameState = start;
        // Open the document to read
        std::shared_ptr<CXmlNode> root = CXmlNode::OpenDocument(filename);

        // Once we know it is open, clear the existing data
        Clear();
      

        // Maps for declarations of each type 
        map<wstring, tuple<wstring, wstring, wstring>> platformDeclarations;
        map<wstring, wstring> wallDeclarations;
        map<wstring, tuple<wstring, int>> moneyDeclarations;
        map<wstring, wstring> tuitionupDeclarations;
        map<wstring, wstring> doorDeclarations;
        map<wstring, wstring> villainDeclarations;
        map<wstring, tuple<wstring, wstring>> signDeclarations;

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
                            mBackground = unique_ptr<Gdiplus::Bitmap>(Gdiplus::Bitmap::FromFile((L"images/" + node2->GetAttributeValue(L"image", L"")).c_str()));
                        }
                        if (name == L"platform")
                        {
                            platformDeclarations[id] = make_tuple(node2->GetAttributeValue(L"left-image", L""), node2->GetAttributeValue(L"mid-image", L""), node2->GetAttributeValue(L"right-image", L""));
                        }
                        if (name == L"wall")
                        {
                            wallDeclarations[id] = node2->GetAttributeValue(L"image", L"");
                        }
                        if (name == L"money")
                        {
                            moneyDeclarations[id] = make_tuple(node2->GetAttributeValue(L"image", L""), node2->GetAttributeIntValue(L"value", 0));
                        }
                        if (name == L"tuition-up")
                        {
                            tuitionupDeclarations[id] = node2->GetAttributeValue(L"image", L"");
                        }
                        if (name == L"door")
                        {
                            doorDeclarations[id] = node2->GetAttributeValue(L"image", L"");
                        }
                        if (name == L"villain")
                        {
                            villainDeclarations[id] = node2->GetAttributeValue(L"image", L"");
                        }
                        if (name == L"sign")
                        {
                            signDeclarations[id] = make_tuple(node2->GetAttributeValue(L"walk-image", L""), node2->GetAttributeValue(L"stop-image", L""));
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
                            auto leftimage = L"images/" + get<0>(platformDeclarations[id]);
                            auto midimage = L"images/" + get<1>(platformDeclarations[id]);
                            auto rightimage = L"images/" + get<2>(platformDeclarations[id]);
                            auto x = node2->GetAttributeIntValue(L"x", 0);
                            auto y = node2->GetAttributeIntValue(L"y", 0);
                            auto width = node2->GetAttributeIntValue(L"width", 0);
                            auto height = node2->GetAttributeIntValue(L"height", 0);
                            LoadPlatform(leftimage, midimage, rightimage, x, y, width, height);
                        }
                        if (name == L"wall")
                        {
                            auto image = L"images/" + wallDeclarations[id];
                            auto x = node2->GetAttributeIntValue(L"x", 0);
                            auto y = node2->GetAttributeIntValue(L"y", 0);
                            auto width = node2->GetAttributeIntValue(L"width", 0);
                            auto height = node2->GetAttributeIntValue(L"height", 0);
                            LoadWall(image, x, y, width, height);
                        }
                        if (name == L"money")
                        {
                            auto image = L"images/" + get<0>(moneyDeclarations[id]);
                            auto entity = make_shared<CMoney>(this, image);
                            entity->SetLocation(node2->GetAttributeIntValue(L"x", 0), node2->GetAttributeIntValue(L"y", 0));
                            entity->SetTextLocation(node2->GetAttributeIntValue(L"x", 0), node2->GetAttributeIntValue(L"y", 0));
                            entity->SetInitialWorth(get<1>(moneyDeclarations[id]));
                            entity->SetWorth(get<1>(moneyDeclarations[id]));
                            Add(entity);
                        }
                        if (name == L"tuition-up")
                        {
                            // needs to be changed to a tuitionup object
                            auto image = L"images/" + tuitionupDeclarations[id];
                            auto entity = make_shared<CPresident>(this, image);
                            entity->SetLocation(node2->GetAttributeIntValue(L"x", 0), node2->GetAttributeIntValue(L"y", 0));
                            entity->SetTextLocation(node2->GetAttributeIntValue(L"x", 0), node2->GetAttributeIntValue(L"y", 0));
                            Add(entity);
                        }
                        if (name == L"door")
                        {
                            auto image = L"images/" + doorDeclarations[id];
                            auto entity = make_shared<CEndDoor>(this, image);
                            entity->SetLocation(node2->GetAttributeIntValue(L"x", 0), node2->GetAttributeIntValue(L"y", 0));
                            Add(entity);
                        }
                        if (name == L"villain")
                        {
                            auto image = L"images/" + villainDeclarations[id];
                            auto entity = make_shared<CCharacter>(this, image);
                            entity->SetLocation(node2->GetAttributeIntValue(L"x", 0), node2->GetAttributeIntValue(L"y", 0));
                            entity->SetStart(node2->GetAttributeIntValue(L"y", 0));
                            Add(entity);
                        }
                        if (name == L"sign")
                        {
                            auto walkImage = L"images/" + get<0>(signDeclarations[id]);
                            auto stopImage = L"images/" + get<1>(signDeclarations[id]);
                            auto entity = make_shared<CFarmLaneWalkSign>(this, stopImage);
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
* \return void
*/
void CGame::Update(double elapsed)
{
    for (auto item : mEntities)
    {
        item->Update(elapsed);

    }
    if (mGameState == end)
    {
        LoadNextLevel();
    }
    else if (mGameState != loss) {
        if (mTimer < 0.5) mGameState = start;
        else if (mTimer > 0.5) mGameState = progress;
    }
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
    double leftx = x - (((double)width / 32 - 1) / 2) * 32;
    double rightx = x + (((double)width / 32 - 1) / 2) * 32;
    auto leftplatform = make_shared<CPlatform>(this, leftimage, -1);
    leftplatform->SetLocation(leftx, y);
    Add(leftplatform);
    auto rightplatform = make_shared<CPlatform>(this, rightimage, 1);
    rightplatform->SetLocation(rightx, y);
    Add(rightplatform);
    for (double i = 32 - (int)(2 / mVScale); i <= width; i += 32 - (int)(2 / mVScale))
    {
        auto midplatform = make_shared<CPlatform>(this, midimage);
        double offset = i;
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
    double topy = y - ((height / 32 - 1) / 2) * 32;
    for (double i = 0; i <= height; i += 32 - (int)(2 / mVScale))
    {
        auto wall = make_shared<CWall>(this, image);
        wall->SetLocation(x, topy + i);
        AddFront(wall);
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
        if (mGameState != loss)
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

            else if ((PlayerY + PlayerHeight >= EntityY - EntityHeight) && (PlayerY + PlayerHeight <= EntityY + EntityWidth))
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
            else if ((PlayerY - PlayerHeight >= mLevelHeight)) {
                mGameState = loss;
            }
        }
        else {
            player->Loss();
            break;
        }
    }

}

/**
  * Load next level
  */
void CGame::LoadNextLevel()
{
    if (mLevelNum == 0)
    {
        Load(L"levels/level1.xml");
        mLevelNum = 1;
    }
    else if (mLevelNum == 1)
    {
        Load(L"levels/level2.xml");
        mLevelNum = 2;
    }
    else if (mLevelNum == 2)
    {
        Load(L"levels/level3.xml");
        mLevelNum = 3;
    }
    else if (mLevelNum == 3)
    {
        Load(L"levels/level3.xml");
        mLevelNum = 3;
    }
    mFirstDraw = true;
}
