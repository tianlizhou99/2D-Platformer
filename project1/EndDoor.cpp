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

/**
 * Handle end door collision behavior
 * \param player of game
 */
void CEndDoor::Collision(CPlayer* player)
{
    auto PlayerX = player->GetX();
    auto PlayerY = player->GetY();
    auto DoorX = GetX();
    auto DoorY = GetY();
    auto DistanceX = PlayerX - DoorX;
    auto DistanceY = PlayerY - DoorY;
    double radius = 16;

    if (DistanceX * DistanceX + DistanceY * DistanceY <= radius * radius)
    {
        auto game = GetGame();
        game->SetState(CGame::end);
    }
}
