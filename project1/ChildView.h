
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

	/// True until the first time we draw
	bool mFirstDraw = true;

	long long mLastTime = 0;    ///< Last time we read the timer
	double mTimeFreq = 0;       ///< Rate the timer updates
};

