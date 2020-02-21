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
private:
    int mScore = 0; ///< score of the player

    std::vector <std::shared_ptr<CEntity>> mEntities; ///< Vector of entities
    
    std::unique_ptr<Gdiplus::Bitmap> mBackground; ///< Background image
    
    int mLevelWidth = 0; ///< Level width
    int mLevelHeight = 0; ///< Level height
    bool mTuitionIncrease = false;
    float mScale = 1; ///<Window scale

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
    std::vector<double> ItemDistances(CPlayer* player);

    /** gets the current score of the game
     * \returns the current score of the game */
    int GetScore() { return mScore; };

    /** gets the current score of the game
     * \returns the current score of the game */
    void SetScore(int score) { mScore = score; };

};
