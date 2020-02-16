#include "pch.h"
#include "Timer.h"
#include <string>
#include <sstream>

using namespace Gdiplus;
using namespace std;

double CTimer::GetTime()
{
	auto game = GetGame();
	return game->GetTime();
}

void CTimer::SetTime(double time)
{
	auto game = GetGame();
	game->SetTime(time);
}

void CTimer::Draw(Gdiplus::Graphics* graphics)
{
	FontFamily fontFamily(L"Arial");
	Gdiplus::Font font(&fontFamily, 16);

	SolidBrush green(Color(0, 64, 0));

	string time = to_string(GetTime());

	wstring wide_string = wstring(time.begin(), time.end());
	const wchar_t* result = wide_string.c_str();

	
	graphics->DrawString(result, -1, &font, PointF(2, 2), &green);
}

const wstring TimerImageName = L"images/grass.png";

CTimer::CTimer(CGame* game) :
	CElement(game , TimerImageName)
{
	
}
