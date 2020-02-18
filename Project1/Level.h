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

protected:
    CLevel(CGame* game, const std::wstring& filename);

private:
	/// The image of this level component
	std::unique_ptr<Gdiplus::Bitmap> mImage;

    double mWidth = 0; ///< width of level
    double mHeight = 0; ///< height of level

};

