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
    double mTime = 0; ///< time elapsed

    std::vector < std::shared_ptr<CEntity>> mEntities; ///< Vector of entities
    
    std::unique_ptr<Gdiplus::Bitmap> mBackground; ///< Background image
    
    int mLevelWidth = 0; ///< Level width
    int mLevelHeight = 0; ///< Level height

public:
    CGame(); 
    virtual ~CGame();
    void Add(std::shared_ptr<CEntity> entity);
    void XmlLevel(const std::shared_ptr<xmlnode::CXmlNode>& node);
    void OnDraw(Gdiplus::Graphics* graphics);
    void Load(const std::wstring& filename);
    void Clear();

    /** retrieve the time state of the game
     * \returns mTime the time state of the game */
    double GetTime() { return mTime; };

    /** sets the time of the game
     * \param time the time the game is beign set to
     **/
    void SetTime(double time) { mTime = time; };
};
