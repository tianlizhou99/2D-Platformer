
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

// CChildView

CChildView::CChildView()
{
	OnLevelLevel0();
}

CChildView::~CChildView()
{
}


BEGIN_MESSAGE_MAP(CChildView, CWnd)
	ON_WM_PAINT()
	ON_COMMAND(ID_LEVEL_LEVEL0, &CChildView::OnLevelLevel0)
	ON_COMMAND(ID_LEVEL_LEVEL1, &CChildView::OnLevelLevel1)
	ON_COMMAND(ID_LEVEL_LEVEL2, &CChildView::OnLevelLevel2)
	ON_COMMAND(ID_LEVEL_LEVEL3, &CChildView::OnLevelLevel3)
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
     * Actually Draw the game
     */
    mGame.OnDraw(&graphics);
}



void CChildView::OnLevelLevel0()
{
	mGame.Load(L"levels/level0.xml");
}


void CChildView::OnLevelLevel1()
{
	mGame.Load(L"levels/level1xml");
}


void CChildView::OnLevelLevel2()
{
	mGame.Load(L"levels/level2.xml");
}


void CChildView::OnLevelLevel3()
{
	mGame.Load(L"levels/level3.xml");
}
