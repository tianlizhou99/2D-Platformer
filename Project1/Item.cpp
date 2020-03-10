/**
 * \file Item.cpp
 *
 * \author Team Sprixie
 */

#include "pch.h"
#include "Item.h"

/**
 * Constructor
 * \param game The game this Item is a member of
 * \param filename The name of the file storing image to add
 */
CItem::CItem(CGame* game, const std::wstring& filename) :
    CEntity(game, filename)
{
}
