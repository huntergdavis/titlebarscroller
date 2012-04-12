// titlescroll.h : main header file for the TITLESCROLL application
//

#if !defined(AFX_TITLESCROLL_H__2F227D19_DA5E_4C62_AF6A_462FF6B51FD0__INCLUDED_)
#define AFX_TITLESCROLL_H__2F227D19_DA5E_4C62_AF6A_462FF6B51FD0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CTitlescrollApp:
// See titlescroll.cpp for the implementation of this class
//

class CTitlescrollApp : public CWinApp
{
public:
	CTitlescrollApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTitlescrollApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CTitlescrollApp)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TITLESCROLL_H__2F227D19_DA5E_4C62_AF6A_462FF6B51FD0__INCLUDED_)
