
// ChildView.h : interface of the CChildView class
//


#pragma once
#include "Game.h"

/**
 * Childview class
 */
class CChildView : public CWnd
{
// Construction
public:
	CChildView();

// Attributes
public:

// Operations
public:

// Overrides
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// Implementation
public:
	virtual ~CChildView();

	// Generated message map functions
protected:
	afx_msg void OnPaint();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLevelsLevel0();
	afx_msg void OnLevelsLevel1();
	afx_msg void OnLevelsLevel2();
	afx_msg void OnLevelsLevel3();
private:
	CGame mGame; ///< Game being run
	std::shared_ptr<CPlayer> mPlayer; ///< Player being controlled
	/// True until the first time we draw
	bool mFirstDraw = true;
	
	bool mMessageDisplayBool = false; ///< if a message is being displayed
	string mMessageDisplay = ""; ///< message to display

	long long mLastTime;    ///< Last time we read the timer
	double mTimeFreq;       ///< Rate the timer updates

	double mElapsed; ///< time elapsed
	int mlevelNum = 0; ///< selected level number
public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
};

