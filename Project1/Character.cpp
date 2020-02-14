#include "pch.h"
#include "Character.h"

void CCharacter::XmlLoad(const std::shared_ptr<xmlnode::CXmlNode>& node)
{
	SetLocation(node->GetAttributeDoubleValue(L"x", 0), node->GetAttributeDoubleValue(L"y", 0));
	mSpeedY = node->GetAttributeDoubleValue(L"SpeedY", 0);
	mSpeedX = node->GetAttributeDoubleValue(L"SpeedX", 0);
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
	mSpeedY = 0;
}
