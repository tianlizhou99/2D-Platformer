#include "pch.h"
#include "Badger.h"
#include<string>

using namespace std;
using namespace Gdiplus;

const wstring badgerImage = L"images/wisc.png";
CBadger::CBadger(CGame* game) : CCharacter(game, badgerImage)
{
    SetLocation(500, 500);
    SetSpeedY(50);
}

std::shared_ptr<xmlnode::CXmlNode> CBadger::XmlSave(const std::shared_ptr<xmlnode::CXmlNode>& node)
{
    auto itemNode = CCharacter::XmlSave(node);
    itemNode->SetAttribute(L"type", L"Wolverine");
    return itemNode;
}
