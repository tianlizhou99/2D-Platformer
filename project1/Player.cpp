#include "pch.h"
#include "Player.h"
#include<string>

using namespace std;
using namespace Gdiplus;

const wstring GnomeImage = L"project1/images/gnome.png";
CPlayer::CPlayer(CGame* game) : CCharacter(game, GnomeImage)
{
}

std::shared_ptr<xmlnode::CXmlNode> CPlayer::XmlSave(const std::shared_ptr<xmlnode::CXmlNode>& node)
{
    auto itemNode = CPlayer::XmlSave(node);
    itemNode->SetAttribute(L"type", L"Player");
    return itemNode;
}
