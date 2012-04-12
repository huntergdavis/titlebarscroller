// titlescrollDlg.h : header file
//

#if !defined(AFX_TITLESCROLLDLG_H__FBCBFD63_F0BD_445C_86C7_9B438F628DEB__INCLUDED_)
#define AFX_TITLESCROLLDLG_H__FBCBFD63_F0BD_445C_86C7_9B438F628DEB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CTitlescrollDlg dialog

class CTitlescrollDlg : public CDialog
{
// Construction
public:
	CTitlescrollDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CTitlescrollDlg)
	enum { IDD = IDD_TITLESCROLL_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTitlescrollDlg)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL
	void SetCurrentLineDlg(int iLine);
	void SetStatus(CString cStatus);
	void SetTitleText(CString cTitleText);
	void SetTitleTextOnCurrentWindow(CString cTitleText);
	CString GetTextForTitle();
	int GetEndingTime(int Hour,int Minute,int &EndHour, int &EndMinute);

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CTitlescrollDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnButtonLoadTextFile();
	afx_msg void OnButtonBack10();
	afx_msg void OnButtonRewind();
	afx_msg void OnButtonPlayPause();
	afx_msg void OnButtonGotoLine();
	afx_msg void OnButtonForward10();
	virtual void OnOK();
	afx_msg void OnButtonHelpAbout();
	afx_msg void OnCheckActiveWindow();
	afx_msg void OnDeltaposSpinScrollSpeed(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnButtonNext();
	afx_msg void OnRadioScroll();
	afx_msg void OnRadioAppear();
	afx_msg void OnDeltaposSpinCharacters(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnCheckLineWrap();
	afx_msg void OnButtonAlarm();
	afx_msg void OnCheckAlarms();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedCheckRandom();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TITLESCROLLDLG_H__FBCBFD63_F0BD_445C_86C7_9B438F628DEB__INCLUDED_)
