/**
 * \file Wolverine.cpp
 *
 * \author Team Sprixie
 */

#include "pch.h"
#include "Wolverine.h"
#include<string>

using namespace std;
using namespace Gdiplus;

/// Wolverine filename
const wstring wolverineImage = L"images/UofM.png";

CWolverine::CWolverine(CGame* game) : CCharacter(game, wolverineImage)
{
    SetLocation(500, 500);
}

std::shared_ptr<xmlnode::CXmlNode> CWolverine::XmlSave(const std::shared_ptr<xmlnode::CXmlNode>& node)
{
    auto itemNode = CCharacter::XmlSave(node);
    itemNode->SetAttribute(L"type", L"Wolverine");
    return itemNode;
}
