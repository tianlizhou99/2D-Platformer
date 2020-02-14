#include "pch.h"
#include "Wolverine.h"
#include<string>

using namespace std;
using namespace Gdiplus;

const wstring wolverineImage = L"project1/images/wolverine.png";
CWolverine::CWolverine(CGame* game) : CCharacter(game, wolverineImage)
{
}

std::shared_ptr<xmlnode::CXmlNode> CWolverine::XmlSave(const std::shared_ptr<xmlnode::CXmlNode>& node)
{
    auto itemNode = CCharacter::XmlSave(node);
    itemNode->SetAttribute(L"type", L"Wolverine");
    return itemNode;
}
