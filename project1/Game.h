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
    int mScore = 0;
    double mTime = 0;

    std::vector < std::shared_ptr<CEntity>> mEntities;
    /// level mLevel
    
    std::unique_ptr<Gdiplus::Bitmap> mBackground; ///< Background image
    
    int mLevelWidth = 0, mLevelHeight = 0; /// Level width and height

public:
    CGame();
    virtual ~CGame();
    void Add(std::shared_ptr<CEntity> entity);
    void XmlLevel(const std::shared_ptr<xmlnode::CXmlNode>& node);
    void OnDraw(Gdiplus::Graphics* graphics);
    void Load(const std::wstring& filename);
    void Clear();
};
