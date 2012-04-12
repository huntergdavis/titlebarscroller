#if !defined(AFX_ALARMDIALOG_H__E946B0DD_81A3_421D_89F5_3C67B63D1BF2__INCLUDED_)
#define AFX_ALARMDIALOG_H__E946B0DD_81A3_421D_89F5_3C67B63D1BF2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AlarmDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// AlarmDialog dialog

class AlarmDialog : public CDialog
{
// Construction
public:
	AlarmDialog(CWnd* pParent = NULL);   // standard constructor
	void SetActive();

// Dialog Data
	//{{AFX_DATA(AlarmDialog)
	enum { IDD = IDD_ALARM_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(AlarmDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(AlarmDialog)
	afx_msg void OnCheck1();
	afx_msg void OnCheck2();
	afx_msg void OnCheck3();
	afx_msg void OnCheck4();
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ALARMDIALOG_H__E946B0DD_81A3_421D_89F5_3C67B63D1BF2__INCLUDED_)
