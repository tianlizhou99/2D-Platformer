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
	return mTime;
}

/**
 * Sets the time of the member variable mTime
 * \param time the time that mTime is being set to
 */
void CTimer::SetTime(double time)
{
	mTime = time;
}

/**
 * Drawing the timer on the screen
 * \param graphics the graphics tool used to draw the timer
 */
void CTimer::Draw(Gdiplus::Graphics* graphics)
{
	FontFamily fontFamily(L"Arial");
	Gdiplus::Font font(&fontFamily, 32);

	SolidBrush green(Color(0, 64, 0));

	int milliseconds = GetTime();

	int minutes_int = milliseconds / 60;

	int seconds_int = (milliseconds - (60 * minutes_int));
	
	string seconds = to_string(seconds_int);

	string minutes = to_string(minutes_int);

	
	string time = minutes+ ":" +seconds;

	wstring wide_string = wstring(time.begin(), time.end());
	const wchar_t* result = wide_string.c_str();

	
	graphics->DrawString(result, -1, &font, PointF(10, 10), &green);
}

const wstring TimerImageName = L"images/grass.png";

/**
 * Constructor for the timer
 * \param game The game that the timer is being added to
 */
CTimer::CTimer(CGame* game) :
	CElement(game , TimerImageName)
{
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
	SetTime(time);
}