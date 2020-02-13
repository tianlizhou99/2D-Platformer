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

class CEntity;

/**
 * class that represents the game
 */
class CGame
{
private:
    int mScore = 0;
    double mTime = 0;

    std::vector < std::shared_ptr<CEntity>> mEntities;
    /// level mLevel
    
    std::unique_ptr<Gdiplus::Bitmap> mBackground; ///< Background image

public:
    void Add(std::shared_ptr<CEntity> entity);


};

