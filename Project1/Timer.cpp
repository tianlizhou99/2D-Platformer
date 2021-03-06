/**
 * \file Timer.cpp
 *
 * \author Team Sprixie
 */

#include "pch.h"
#include "Timer.h"
#include <string>
#include <sstream>
#include <cmath>

using namespace Gdiplus;
using namespace std;

/**
 * Getter getting the time of the timer
 * \returns mTime the member variable representing the time
 */
double CTimer::GetTime()
{
	auto game = GetGame();
	double time = game->GetTimer();
	return time;
}

/**
 * Drawing the timer on the screen
 * \param graphics the graphics tool used to draw the timer
 */
void CTimer::Draw(Gdiplus::Graphics* graphics)
{
	FontFamily fontFamily(L"Arial");
	Gdiplus::Font font(&fontFamily, 64);

	SolidBrush pink(Color(1, 206, 209));

	int milliseconds = static_cast<int>(GetTime());

	int minutes_int = milliseconds / 60;

	int seconds_int = (milliseconds - (60 * minutes_int));
	
	wstring seconds = to_wstring(seconds_int);
	if (seconds_int < 10) seconds = L"0" + seconds;

	wstring minutes = to_wstring(minutes_int);
	if (minutes_int < 10) minutes = L"0" + minutes;

	wstring time = minutes + L":" + seconds;

	wstring wide_string = wstring(time.begin(), time.end());
	const wchar_t* result = wide_string.c_str();

	auto Game = GetGame();
	auto Player = Game->GetPlayer();
	auto PlayerX = Player->GetX() - 450;
	
	graphics->DrawString(result, -1, &font, PointF((PlayerX ), 10), &pink);
}

/// Dummy Image
const wstring TimerImageName = L"images/grass.png";

/**
 * Constructor for the timer
 * \param game The game that the timer is being added to
 */
CTimer::CTimer(CGame* game) :
	CElement(game , TimerImageName)
{
	SetLocation(0, 0);
}

/**
 * Update the timer to the current time of the time
 * \param elpased the amount of time elapsed since the last update
 *  given in milliseconds
 */
void CTimer::Update(double elpased)
{
	auto game = GetGame();
	double time = GetTime();
	time += elpased;
	game->SetTimer(time);
}
