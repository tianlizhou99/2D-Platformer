#include "pch.h"
#include "EndDoor.h"


/// End Door filename
const wstring ImageNameEndDoor = L"images/door.png";

/** Constructor
 * \param game The game this is a member of
*/
CEndDoor::CEndDoor(CGame* game) :
    CLevel(game, ImageNameEndDoor)
{
}

/**
* Overloaded constructor
* \param game that the door is in
* \param filename image to load from
*/
CEndDoor::CEndDoor(CGame* game, wstring& filename) : CLevel(game, filename)
{
}
