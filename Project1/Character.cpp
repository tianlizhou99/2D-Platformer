#include "pch.h"
#include "Character.h"

void CCharacter::XmlLoad(const std::shared_ptr<xmlnode::CXmlNode>& node)
{
	SetLocation(node->GetAttributeDoubleValue(L"x", 0), node->GetAttributeDoubleValue(L"y", 0));
	mTime = 0;
}

std::shared_ptr<xmlnode::CXmlNode> CCharacter::XmlSave(const std::shared_ptr<xmlnode::CXmlNode>& node)
{
	return std::shared_ptr<xmlnode::CXmlNode>();
}

void CCharacter::SetSpeedX(double x)
{
	mSpeedX = x;
}

void CCharacter::SetSpeedY(double y)
{
	mSpeedY = y;
}

CCharacter::CCharacter(CGame* game, const std::wstring& filename) : CEntity(game, filename)
{
	mSpeedX = 0;
	mSpeedY = -240;
}

void CCharacter::Collision(CPlayer* player)
{
	auto game = GetGame();
	game->SetState(CGame::loss);
}

void CCharacter::Update(double elapsed) {
	SetLocation(GetX(), GetY() + mSpeedY * elapsed);
	if (GetY() < mStartY-300) {
		SetSpeedY(240);
	}
	else if (GetY() > mStartY) {
		SetSpeedY(-240);
	}
}

void CCharacter::SetStart(double start) {
	mStartY = start;
}