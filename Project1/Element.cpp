#include "pch.h"
#include "Element.h"

/**
 * Draw funciton being passed on to all the screen elements  below
 * \param graphics the graphics tool being used to draw these images
 */
void CElement::Draw(Gdiplus::Graphics* graphics)
{
}

/**
 * Constructor being passed to the screen elements below
 * \param game  the game the object will be added to
 * \param filename The file form of the element for loading
 */
CElement::CElement(CGame* game, const std::wstring& filename) :
	CEntity(game, filename)
{
}
