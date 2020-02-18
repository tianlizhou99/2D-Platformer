#include "pch.h"
#include "Money.h"

CMoney::CMoney(CGame* game, wstring& filename) :
	CItem(game, filename)
{
}

int CMoney::Worth()
{
	return 100;
}

