/**
 * \file Money.h
 *
 * \author Team Sprixie
 *
 * Class that implements money
 */

#pragma once
#include "Item.h"
#include <string>
using namespace std;

class CMoney :
	public CItem
{
public:
    /// Default constructor (disabled)
    CMoney() = delete;

    /// Copy constructor (disabled)
    CMoney(const CMoney&) = delete;

    CMoney(CGame* game, wstring& filename);
};

