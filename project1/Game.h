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
    enum GameState { start = 0, progress = 1, end = 2, loss = 3};
private:
    int mScore = 0; ///< score of the player
    GameState mGameState = start; ///< current state of the game
    double mTimer = 0; ///< timer of current level
    double mEndTime = 0; ///< time that player lost

    std::vector <std::shared_ptr<CEntity>> mEntities; ///< Vector of entities
    
    std::unique_ptr<Gdiplus::Bitmap> mBackground; ///< Background image
    
    int mLevelWidth = 0; ///< Level width
    int mLevelHeight = 0; ///< Level height
    float mVScale = 1; ///< Vertical window scale
    float mHScale = 1; ///< Horizontal window scale
    int mStartX = 0; ///< starting x position for the player
    int mStartY = 0; ///< starting Y position for the player

    std::shared_ptr<CEntity> mPlayer = nullptr; ///< Pointer to player object

    int mTuitionIncrease = 0; ///< Tuition increase

    int mLevelNum = 0; ///< current level number
    bool mFirstDraw = true; ///<first draw status

public:
    CGame(); 
    virtual ~CGame();
    void Add(std::shared_ptr<CEntity> entity);
    void AddFront(std::shared_ptr<CEntity> entity);

    void OnDraw(Gdiplus::Graphics* graphics, int width, int height, int scrollX);
    void Load(const std::wstring& filename);
    void Clear();
    virtual void Update(double elapsed);
    void LoadPlatform(wstring leftimage, wstring midimage, wstring rightimage, int x, int y, int width, int height);
    void LoadWall(wstring image, int x, int y, int width, int height);

    void CollisionTest(CPlayer* player);

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

    /** sets the current timer of the game
     * \param timer the current timer of the game */
    void SetTimer(double timer) { mTimer = timer; };

    /** Getter for Tuition Increase
     * \returns tuition increase*/
    int GetTuitionIncrease() { return mTuitionIncrease; }

    /** Setter for the Tuition Increase
     * \param tuitionIncrease new tuition increase*/
    void SetTuitionIncrease(int tuitionIncrease) { mTuitionIncrease = tuitionIncrease; }

    /** gets the starting position of the player
    * \returns the starting x position of the player */
    int GetStartY() { return mStartY; }

    /** gets the starting position of the player
    * \returns the starting Y position of the player */
    int GetStartX() { return mStartX; }

    /** gets the height of the current level
    * \returns the heights of the current level */
    int GetLevelHeight() { return mLevelHeight; };

    /** gets the current entities of the game
    * \returns the current entities of the game */
    auto GetEntities() { return mEntities; };

    /** sets the pointer to the player character
    * \param player the player that player is being set to */
    void SetPlayer(std::shared_ptr<CEntity> player) { mPlayer = player; }

    /** gets the current player object of the game
    * \returns the current player object of the game */
    std::shared_ptr<CEntity> GetPlayer() { return mPlayer; }
    /** gets the current level number of the game
    * \returns the current levelnumber of the game */
    auto GetLevelNum() { return mLevelNum; };

    /** sets the current level number of the game
     * \param num the new level number of the game */
    void SetLevelNum(int num) { mLevelNum = num; };

    /** gets the first draw status of the game
    * \returns the first draw status of the game */
    auto GetFirst() { return mFirstDraw; };
    
    /** sets the first draw status of the game
     * \param first the new first draw status of the game */
    void SetFirst(bool first) { mFirstDraw = first; };

    void LoadNextLevel();
};
