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
using namespace xmlnode;


class CEntity;

/**
 * class that represents the game
 */
class CGame
{
private:
    int mScore = 0; ///< score of the player

    std::vector < std::shared_ptr<CEntity>> mEntities; ///< Vector of entities
    
    std::unique_ptr<Gdiplus::Bitmap> mBackground; ///< Background image
    
    int mLevelWidth = 0; ///< Level width
    int mLevelHeight = 0; ///< Level height

public:
    CGame(); 
    virtual ~CGame();
    void Add(std::shared_ptr<CEntity> entity);
    void OnDraw(Gdiplus::Graphics* graphics);
    void Load(const std::wstring& filename);
    void Clear();
    void Update(double elapsed);

    std::vector<double> PlatformDistances(CEntity* entity1);

    /** gets the current score of the game
     * \returns the current score of the game */
    int GetScore() { return mScore; };

};
