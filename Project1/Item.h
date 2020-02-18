/**
 * \file Item.h
 *
 * \author Team Sprixie
 *
 * Base class for any item in the game
 */

#pragma once
#include "Entity.h"

/**
* base class for any item in the game
*/
class CItem :
	public CEntity
{
public:
    /// Default constructor (disabled)
    CItem() = delete;

    /// Copy constructor (disabled)
    CItem(const CItem&) = delete;




protected:
    CItem(CGame* game, const std::wstring& filename);
};

