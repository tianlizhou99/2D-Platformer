/**
 * \file Level.h
 *
 * \author Team Sprixie
 *
 * Base class for any level component in the game
 */


#pragma once
#include "Entity.h"
#include "XmlNode.h"

using namespace xmlnode;
using namespace std;


/**
 * Base class for components that make up the level
 */
class CLevel :
	public CEntity
{
public:
    /// Default constructor (disabled)
    CLevel() = delete;

    /// Copy constructor (disabled)
    CLevel(const CLevel&) = delete;

    void XmlLoad(const std::shared_ptr<xmlnode::CXmlNode>& node);

    /** Set width
    * \param width to set to
    * \returns void */
    void SetWidth(int width) { mWidth = width; }

    /** Set height
    * \param height to set to
    * \returns void */
    void SetHeight(int height) { mHeight = height; }

protected:
    CLevel(CGame* game, const std::wstring& filename);

private:
	/// The image of this level component
	std::unique_ptr<Gdiplus::Bitmap> mImage;

    int mWidth = 768; ///< width of level
    int mHeight = 1024; ///< height of level

};

