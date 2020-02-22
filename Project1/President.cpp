#include "pch.h"
#include "President.h"

/**
* Constructor for CPresident
* \param game to add money to
* \param filename of the image to load
*/
CPresident::CPresident(CGame* game, wstring& filename) :
	CItem(game, filename)
{
}