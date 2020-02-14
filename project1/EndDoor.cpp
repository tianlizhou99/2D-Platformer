#include "pch.h"
#include "EndDoor.h"


/// End Door filename
const wstring ImageNameEndDoor = L"project1/images/door.png";

/** Constructor
 * \param game The game this is a member of
*/
CEndDoor::CEndDoor(CGame* game) :
    CLevel(game, ImageNameEndDoor)
{
}