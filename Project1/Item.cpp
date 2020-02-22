#include "pch.h"
#include "Item.h"


/**
 * Constructor
 * \param game The game we are in
 * \param filename Filename for the image we use
 */
CItem::CItem(CGame* game, const std::wstring& filename) :
    CEntity(game, filename)
{
}
