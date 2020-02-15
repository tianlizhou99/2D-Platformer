
// ChildView.cpp : implementation of the CChildView class
//

#include "pch.h"
#include "framework.h"
#include "project1.h"
#include "DoubleBufferDC.h"
#include "ChildView.h"

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

    /*
     * Actually Draw the game
     */
    mGame.OnDraw(&graphics);
}


/**
* Event handler for level 0
* \returns void
*/
void CChildView::OnLevelsLevel0()
{
	mGame.Load(L"levels/level0.xml");
}

/**
* Event handler for level 1
* \returns void
*/
void CChildView::OnLevelsLevel1()
{
	mGame.Load(L"levels/level1.xml");
}

/**
* Event handler for level 2
* \returns void
*/
void CChildView::OnLevelsLevel2()
{
	mGame.Load(L"levels/level2.xml");
}

/**
* Event handler for level 3
* \returns void
*/
void CChildView::OnLevelsLevel3()
{
	mGame.Load(L"levels/level3.xml");
}
