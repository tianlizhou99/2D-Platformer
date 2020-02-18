#include "pch.h"
#include "Wall.h"

/// Wall 1 filename
const wstring ImageNameWall1 = L"project1/images/wall1.png";

/// Wall 2 filename
const wstring ImageNameWall2 = L"project1/images/wall2.png";

/** Constructor
 * \param game The game this is a member of
*/
CWall::CWall(CGame* game) :
    CLevel(game, ImageNameWall1)
{
}

CWall::CWall(CGame* game, wstring& filename) : CLevel(game, filename)
{
}
