/**
 * \file Game.h
 *
 * \author Team Sprixie
 *
 * class that contains all of the game objects
 */

#pragma once

#include<memory>
#include<vector>
#include<string>
#include "XmlNode.h"
#include "Player.h"
using namespace xmlnode;
using namespace std;


class CEntity;

/**
 * class that represents the game
 */
class CGame
{
public:
    ///possible game states
    enum GameState { start = 0, progress = 1, end = 2, loss = 3, money = 4 };
private:
    int mScore = 0; ///< score of the player
    GameState mGameState = start; ///< current state of the game
    double mTimer = 0; ///< timer of current level

    std::vector <std::shared_ptr<CEntity>> mEntities; ///< Vector of entities
    
    std::unique_ptr<Gdiplus::Bitmap> mBackground; ///< Background image
    
    int mLevelWidth = 0; ///< Level width
    int mLevelHeight = 0; ///< Level height
    float mVScale = 1; ///< Vertical window scale
    float mHScale = 1; ///< Horizontal window scale
    int mStartX = 0;
    int mStartY = 0;

    bool mTuitionIncrease = false;

public:
    CGame(); 
    virtual ~CGame();
    void Add(std::shared_ptr<CEntity> entity);
    void OnDraw(Gdiplus::Graphics* graphics, int width, int height, int scrollX);
    void Load(const std::wstring& filename);
    void Clear();
    virtual void Update(double elapsed);
    void LoadPlatform(wstring leftimage, wstring midimage, wstring rightimage, int x, int y, int width, int height);
    void LoadWall(wstring image, int x, int y, int width, int height);
    //void Accept(CVisitor* visitor);

    void CollisionTest(CPlayer* player);
    //std::vector<double> ItemDistances(CPlayer* player);

    /** gets the current state of the game
     * \returns the current state of the game */
    int GetState() { return mGameState; };

    /** sets the current state of the game
     * \param gameState the current state of the game */
    void SetState(GameState gameState) { mGameState = gameState; };

    /** gets the current score of the game
     * \returns the current score of the game */
    int GetScore() { return mScore; };

    /** gets the current score of the game
     * \param score the current score of the game */
    void SetScore(int score) { mScore = score; };

    /** gets the current timerr of the game
    * \returns the current time of the game */
    double GetTimer() { return mTimer; };

    /** gets the current timer of the game
     * \param timer the current timer of the game */
    void SetTimer(double timer) { mTimer = timer; };

    bool GetTuitionIncrease() { return mTuitionIncrease; }

    void SetTuitionIncrease(bool tuitionIncrease) { mTuitionIncrease = tuitionIncrease; }

    int GetStartY() { return mStartY; }

    int GetStartX() { return mStartX; }

    /** gets the height of the current level
    * \returns the heights of the current level */
    int GetLevelHeight() { return mLevelHeight; };

    /** gets the current entities of the game
    * \returns the current entities of the game */
    auto GetEntities() { return mEntities; };

};
