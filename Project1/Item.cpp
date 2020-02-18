#include "pch.h"
#include "Item.h"

CItem::CItem(CGame* game, const std::wstring& filename) :
    CEntity(game, filename)
{
}
