
// ChildView.cpp : implementation of the CChildView class
//

#include "pch.h"
#include <memory>
#include "framework.h"
#include "project1.h"
#include "DoubleBufferDC.h"
#include "ChildView.h"
#include "Timer.h"
#include "Scoreboard.h"
#include "Badger.h"
#include "Player.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

using namespace Gdiplus;
using namespace std;

/// Frame duration in milliseconds
const int FrameDuration = 30;

// CChildView

CChildView::CChildView()
{
	OnLevelsLevel0();
}

CChildView::~CChildView()
{
}


BEGIN_MESSAGE_MAP(CChildView, CWnd)
	ON_WM_PAINT()
	ON_COMMAND(ID_LEVELS_LEVEL0, &CChildView::OnLevelsLevel0)
	ON_COMMAND(ID_LEVELS_LEVEL1, &CChildView::OnLevelsLevel1)
	ON_COMMAND(ID_LEVELS_LEVEL2, &CChildView::OnLevelsLevel2)
	ON_COMMAND(ID_LEVELS_LEVEL3, &CChildView::OnLevelsLevel3)
	ON_WM_TIMER()
	ON_WM_ERASEBKGND()
	ON_WM_KEYDOWN()
	ON_WM_KEYUP()
END_MESSAGE_MAP()



// CChildView message handlers

/**
* This function is called before the window is created.
* \param cs A structure with the window creation parameters
* \returns TRUE
*/
BOOL CChildView::PreCreateWindow(CREATESTRUCT& cs) 
{
	if (!CWnd::PreCreateWindow(cs))
		return FALSE;

	cs.dwExStyle |= WS_EX_CLIENTEDGE;
	cs.style &= ~WS_BORDER;
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS, 
		::LoadCursor(nullptr, IDC_ARROW), reinterpret_cast<HBRUSH>(COLOR_WINDOW+1), nullptr);

	return TRUE;
}

/**
* Function to paint objects
* \returns void
*/
void CChildView::OnPaint() 
{
	CPaintDC paintDC(this); // device context for painting
	CDoubleBufferDC dc(&paintDC); // device context for painting
	
	Graphics graphics(dc.m_hDC);
	graphics.Clear(Color(0, 0, 0));


	// Do not call CWnd::OnPaint() for painting messages

    if (mFirstDraw)
    {
        mFirstDraw = false;

		SetTimer(1, FrameDuration, nullptr);

        /*
        * Initialize the elapsed time system
        */
        LARGE_INTEGER time, freq;
        QueryPerformanceCounter(&time);
        QueryPerformanceFrequency(&freq);

        mLastTime = time.QuadPart;
        mTimeFreq = double(freq.QuadPart);

		/// add the timer to the game
		mGame.SetTimer(0);
		auto timer = make_shared<CTimer>(&mGame);
		mGame.Add(timer);

		/// add the scoreboard to the game
		auto scorebaord = make_shared<CScoreboard>(&mGame);
		mGame.Add(scorebaord);

		// add player to the game
		auto player = make_shared<CPlayer>(&mGame);
		mPlayer = player;
		mGame.Add(player);
    }

    // Get the size of the window
    CRect rect;
    GetClientRect(&rect);

	/*
	 * Compute the elapsed time since the last draw
	 */
	LARGE_INTEGER time;
	QueryPerformanceCounter(&time);
	long long diff = time.QuadPart - mLastTime;
	double elapsed = double(diff) / mTimeFreq;
	mLastTime = time.QuadPart;


	mGame.Update(elapsed);

    /*
     * Actually Draw the game
     */
	int xOffset = static_cast<int>((float)-mPlayer->GetX() + rect.Width()/2.0f);
    mGame.OnDraw(&graphics, rect.Width(), rect.Height(), xOffset);

	/*
	 * Display message
	 */
	double timer = 0;
	
	FontFamily fontFamily(L"Arial");
	Gdiplus::Font font(&fontFamily, 100);

	SolidBrush pink(Color(255, 105, 180));

	if (!mMessageDisplayBool)
	{
		switch (mGame.GetState())
		{
		case 0:
			mMessageDisplay = ("LEVEL " + to_string(mlevelNum) + " BEGIN");
			timer = mGame.GetTimer();
			mMessageDisplayBool = true;
			break;
		case 2:
			mMessageDisplay = "LEVEL COMPLETE";
			timer = mGame.GetTimer();
			mMessageDisplayBool = true;
			break;
		case 3:
			mMessageDisplay = "YOU LOSE";
			timer = mGame.GetTimer();
			mMessageDisplayBool = true;
		}
	}

	wstring wide_string = wstring(mMessageDisplay.begin(), mMessageDisplay.end());
	const wchar_t* result = wide_string.c_str();
	
	if (mMessageDisplayBool)
	{
		graphics.DrawString(result, -1, &font, PointF(500, 500), &pink);
		if (mGame.GetTimer() - timer >= 2) mMessageDisplayBool = false;
	}
}


/**
* Event handler for level 0
* \returns void
*/
void CChildView::OnLevelsLevel0()
{
	mGame.Load(L"levels/level0.xml");
	mFirstDraw = true;
	mlevelNum = 0;
}

/**
* Event handler for level 1
* \returns void
*/
void CChildView::OnLevelsLevel1()
{
	mGame.Load(L"levels/level1.xml");
	mFirstDraw = true;
	mlevelNum = 1;
}

/**
* Event handler for level 2
* \returns void
*/
void CChildView::OnLevelsLevel2()
{
	mGame.Load(L"levels/level2.xml");
	mFirstDraw = true;
	mlevelNum = 2;
}

/**
* Event handler for level 3
* \returns void
*/
void CChildView::OnLevelsLevel3()
{
	mGame.Load(L"levels/level3.xml");
	mFirstDraw = true;
	mlevelNum = 3;
}

/**
 * Handle timer events
 * \param nIDEvent The timer event ID
 * \returns void
*/
void CChildView::OnTimer(UINT_PTR nIDEvent)
{
	
	Invalidate();
	CWnd::OnTimer(nIDEvent);
}

/**
 * Erase the background
 *
 * This is disabled to eliminate flicker
 * \param pDC Device context
 * \returns FALSE
 */
BOOL CChildView::OnEraseBkgnd(CDC* pDC)
{
	return FALSE;
}

/**
 * Handle key press down
 * \param nChar
 * \param nRepCnt
 * \param nFlags
 * \returns void
*/
void CChildView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	LARGE_INTEGER time;
	QueryPerformanceCounter(&time);
	long long diff = time.QuadPart - mLastTime;
	double elapsed = double(diff) / mTimeFreq;
	mLastTime = time.QuadPart;
	/// Maximum amount of time to allow for elapsed
	const double MaxElapsed = 0.050;
	switch (nChar)
	{

	case VK_RIGHT:
		// right arrow pressed

	//
	// Prevent tunnelling
	//
		while (elapsed > MaxElapsed)
		{
			mPlayer->UpdateMove(MaxElapsed);
			mGame.Update(elapsed);

			elapsed -= MaxElapsed;
		}

		// Consume any remaining time
		if (elapsed > 0)
		{
			mPlayer->UpdateMove(elapsed);
		}
		break;

	case VK_LEFT:
		// left arrow pressed
	//
	// Prevent tunnelling
	//
		while (elapsed > MaxElapsed)
		{
			mPlayer->UpdateMove(-MaxElapsed);
			mGame.Update(elapsed);

			elapsed -= MaxElapsed;
		}

		// Consume any remaining time
		if (elapsed > 0)
		{
			mPlayer->UpdateMove(-elapsed);
		}
		break;

	case VK_SPACE:
		// space bar pressed
	
		break;
	}
}

/**
 * Handle key press up
 * \param nChar
 * \param nRepCnt
 * \param nFlags
 * \returns void
*/
void CChildView::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: Add your message handler code here and/or call default
	switch (nChar)
	{
	case VK_RIGHT:

	case VK_LEFT:

		// left or right arrow released
		break;
	}
}
