// titlescrollDlg.cpp : implementation file
//

#include "stdafx.h"
#include "titlescroll.h"
#include "titlescrollDlg.h"
#include "TitleScrollCore.h"
#include "AlarmDialog.h"
#include ".\titlescrolldlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

TitleScrollCore TSC;
bool ActiveWindow;
int iTimerIndex;
int iLoad;
int iScroll;
int iCharacters;
int iLineWrap;
bool PlayState;
CWnd * LastFrontWindow;
CString LastWindowText;

CString Edit1, Edit2, Edit3, Edit4;
int AlarmDisplayTime;
CTime Time1, Time2, Time3, Time4;
bool Alarm1, Alarm2, Alarm3, Alarm4;
bool Alarm1Go,Alarm2Go,Alarm3Go,Alarm4Go;
int CheckAlarm;
int AlarmTimerIndex;
int Random;

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTitlescrollDlg dialog

CTitlescrollDlg::CTitlescrollDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTitlescrollDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTitlescrollDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTitlescrollDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTitlescrollDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CTitlescrollDlg, CDialog)
	//{{AFX_MSG_MAP(CTitlescrollDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_LOAD_TEXT_FILE, OnButtonLoadTextFile)
	ON_BN_CLICKED(IDC_BUTTON_BACK_10, OnButtonBack10)
	ON_BN_CLICKED(IDC_BUTTON_REWIND, OnButtonRewind)
	ON_BN_CLICKED(IDC_BUTTON_PLAY_PAUSE, OnButtonPlayPause)
	ON_BN_CLICKED(IDC_BUTTON_GOTO_LINE, OnButtonGotoLine)
	ON_BN_CLICKED(IDC_BUTTON_FORWARD_10, OnButtonForward10)
	ON_BN_CLICKED(IDC_BUTTON_HELP_ABOUT, OnButtonHelpAbout)
	ON_BN_CLICKED(IDC_CHECK_ACTIVE_WINDOW, OnCheckActiveWindow)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_SCROLL_SPEED, OnDeltaposSpinScrollSpeed)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON_NEXT, OnButtonNext)
	ON_BN_CLICKED(IDC_RADIO_SCROLL, OnRadioScroll)
	ON_BN_CLICKED(IDC_RADIO_APPEAR, OnRadioAppear)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_CHARACTERS, OnDeltaposSpinCharacters)
	ON_BN_CLICKED(IDC_CHECK_LINE_WRAP, OnCheckLineWrap)
	ON_BN_CLICKED(IDC_BUTTON_ALARM, OnButtonAlarm)
	ON_BN_CLICKED(IDC_CHECK_ALARMS, OnCheckAlarms)
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_CHECK_RANDOM, OnBnClickedCheckRandom)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTitlescrollDlg message handlers

BOOL CTitlescrollDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	Alarm1 = Alarm2 = Alarm3 = Alarm4 = 0;
	AlarmTimerIndex = 0;
	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	SetDlgItemText(IDC_EDIT_SCROLLING_SPEED,"1");

	//set dialog items to be disabled before loading a file
	GetDlgItem(IDC_BUTTON_BACK_10)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_REWIND)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_PLAY_PAUSE)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_GOTO_LINE)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_FORWARD_10)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT_CURRENT_LINE)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_NEXT)->EnableWindow(FALSE);
	

	//set status
	SetStatus("  Ready");
	ActiveWindow = 0;
	iTimerIndex = 0;
	PlayState = 0;
	LastFrontWindow = NULL;
	LastWindowText = "";
	iLoad = 1;
	iScroll = 1;
	iCharacters = 30;
	iLineWrap = 0;
	SetDlgItemText(IDC_EDIT_CHARACTERS,"30");

	CButton * scroller;
	scroller = (CButton*)GetDlgItem(IDC_RADIO_SCROLL);
	scroller->SetCheck(1);
	GetDlgItem(IDC_CHECK_RANDOM)->EnableWindow(FALSE);
	CheckAlarm = 0;
	Random = 0;


	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CTitlescrollDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CTitlescrollDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

HCURSOR CTitlescrollDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CTitlescrollDlg::OnButtonLoadTextFile() 
{
		// luanch the file selection dialog 
		CFileDialog *fdlg = (CFileDialog *) new CFileDialog(TRUE,_T("*"),NULL,OFN_HIDEREADONLY,_T("Txt Files (.txt/.*)|*"), NULL);

		if(fdlg->DoModal() == IDOK)
		{
			AfxGetApp()->DoWaitCursor(1);
			CString FileName = fdlg->GetPathName();
			KillTimer(1);
			TSC.ClearAll();
			bool bDidItWork = TSC.ReadInTextFile(FileName);
			if(bDidItWork == 0)
			{
				if(PlayState == 1)
					OnButtonPlayPause();
				SetDlgItemText(IDC_STATIC_LOADED_FILE,"Loaded File:");
				SetDlgItemText(IDC_EDIT_CURRENT_LINE,"0");
				SetDlgItemText(IDC_EDIT_SCROLLING_SPEED,"1");
				//set dialog items to be disabled before loading a file
				GetDlgItem(IDC_BUTTON_BACK_10)->EnableWindow(FALSE);
				GetDlgItem(IDC_BUTTON_REWIND)->EnableWindow(FALSE);
				GetDlgItem(IDC_BUTTON_PLAY_PAUSE)->EnableWindow(FALSE);
				GetDlgItem(IDC_BUTTON_GOTO_LINE)->EnableWindow(FALSE);
				GetDlgItem(IDC_BUTTON_FORWARD_10)->EnableWindow(FALSE);
				GetDlgItem(IDC_EDIT_CURRENT_LINE)->EnableWindow(FALSE);
				GetDlgItem(IDC_BUTTON_NEXT)->EnableWindow(FALSE);

				//set status
				SetStatus("  Ready");
				ActiveWindow = 0;
				iTimerIndex = 0;
				PlayState = 0;
				LastFrontWindow = NULL;
				LastWindowText = "";
				iLoad = 1;
				iScroll = 1;
				iLineWrap = 0;

				CButton * scroller;
				scroller = (CButton*)GetDlgItem(IDC_RADIO_SCROLL);
				scroller->SetCheck(1);
				
				CButton * checker;
				checker = (CButton*)GetDlgItem(IDC_CHECK_ACTIVE_WINDOW);
				checker->SetCheck(0);

				CButton * appearer;
				appearer = (CButton*)GetDlgItem(IDC_RADIO_APPEAR);
				appearer->SetCheck(0);

				SetWindowText("TitleScroller");
				AfxMessageBox("Could Not Load Selected Text File");

			}
			else
			{
				iLoad = 0;
				if(PlayState == 1)
					OnButtonPlayPause();
				FileName = FileName.Right(FileName.GetLength() - FileName.ReverseFind('\\') - 1);
				SetDlgItemText(IDC_STATIC_LOADED_FILE,FileName);

				//set dialog items to be disabled before loading a file
				GetDlgItem(IDC_BUTTON_BACK_10)->EnableWindow(TRUE);
				GetDlgItem(IDC_BUTTON_REWIND)->EnableWindow(TRUE);
				GetDlgItem(IDC_BUTTON_PLAY_PAUSE)->EnableWindow(TRUE);
				GetDlgItem(IDC_BUTTON_GOTO_LINE)->EnableWindow(TRUE);
				GetDlgItem(IDC_BUTTON_FORWARD_10)->EnableWindow(TRUE);
				GetDlgItem(IDC_EDIT_CURRENT_LINE)->EnableWindow(TRUE);
				GetDlgItem(IDC_BUTTON_NEXT)->EnableWindow(TRUE);
				SetCurrentLineDlg(TSC.GetScrollPosition());
				SetStatus("  File Loaded");
				SetWindowText("TitleScroller");
			}
		}

	AfxGetApp()->DoWaitCursor(-1);	
}

void CTitlescrollDlg::OnButtonBack10() 
{
	if(TSC.GetScrollPosition() < 10)
	{
		TSC.SetScrollPosition(0);
	}
	else
	{
		int scroll;
		scroll = TSC.GetScrollPosition();
		scroll -= 10;
		TSC.SetScrollPosition(scroll);
	}
	SetCurrentLineDlg(TSC.GetScrollPosition());
}

void CTitlescrollDlg::OnButtonRewind() 
{
	if(TSC.GetScrollPosition() < 1)
	{
		TSC.SetScrollPosition(0);
	}
	else
		TSC.SetScrollPosition(TSC.GetScrollPosition() - 1);

	SetCurrentLineDlg(TSC.GetScrollPosition());	
}

void CTitlescrollDlg::OnButtonPlayPause() 
{
	if(PlayState == 0)
	{

		SetDlgItemText(IDC_BUTTON_PLAY_PAUSE,"Pause");
		PlayState = 1;
		SetStatus("Playing");
		int iScrSpd = TSC.GetScrollSpeed();
		if(iScrSpd == 1)
			iScrSpd = 200;
		if(iScrSpd == 0)
			iScrSpd = 400;
		if(iScrSpd == 2)
			iScrSpd = 100;
		if(iScrSpd == 3)
			iScrSpd = 50;
		if(iScrSpd == 4)
			iScrSpd = 25;
		
		if(iScroll == 1)
		{	
			VERIFY(SetTimer(1, iScrSpd, NULL) != 0);
		}
		else
		{
			VERIFY(SetTimer(1, iScrSpd*40, NULL) != 0);
		}
	}
	else
	{
		PlayState = 0;
		SetDlgItemText(IDC_BUTTON_PLAY_PAUSE,"Play");		
		
		
		KillTimer(1);
		
		SetStatus("Paused");
	}
}

void CTitlescrollDlg::OnButtonGotoLine() 
{
	CString CurrentLine;
	GetDlgItemText(IDC_EDIT_CURRENT_LINE,CurrentLine);
	if(atoi(CurrentLine) > TSC.GetNumberOfLinesInFile())
	{
		TSC.SetScrollPosition(TSC.GetNumberOfLinesInFile());
		SetCurrentLineDlg(TSC.GetNumberOfLinesInFile());
	}
	else
	{
		TSC.SetScrollPosition(atoi(CurrentLine));
		SetCurrentLineDlg(atoi(CurrentLine));
	}
}

void CTitlescrollDlg::OnButtonForward10() 
{
	if((TSC.GetNumberOfLinesInFile() - TSC.GetScrollPosition()) < 10)
	{
		TSC.SetScrollPosition(TSC.GetNumberOfLinesInFile());
	}
	else
	{
		int scroll;
		scroll = TSC.GetScrollPosition();
		scroll += 10;
		TSC.SetScrollPosition(scroll);
	}
	SetCurrentLineDlg(TSC.GetScrollPosition());	
}

void CTitlescrollDlg::OnOK() 
{
		
	CDialog::OnOK();
}

void CTitlescrollDlg::OnButtonHelpAbout() 
{
	CAboutDlg cabd;
	cabd.DoModal();	
}

void CTitlescrollDlg::OnCheckActiveWindow() 
{
	if(ActiveWindow == 1)
		ActiveWindow = 0;
	else
		ActiveWindow = 1;
}

BOOL CTitlescrollDlg::PreTranslateMessage(MSG* pMsg) 
{
	switch (pMsg->message)
	{
	case WM_KEYDOWN:
		{
			switch (pMsg->wParam)
			{
			case VK_RETURN:
				{
					CString CurrentLine;
					GetDlgItemText(IDC_EDIT_CURRENT_LINE,CurrentLine);
					if(atoi(CurrentLine) > TSC.GetNumberOfLinesInFile())
					{
						TSC.SetScrollPosition(TSC.GetNumberOfLinesInFile());
						SetCurrentLineDlg(TSC.GetNumberOfLinesInFile());
					}
					else
					{
						TSC.SetScrollPosition(atoi(CurrentLine));
						SetCurrentLineDlg(atoi(CurrentLine));
					}
				}
			case VK_PAUSE:
				{
					return 0;
					break;
				}
			case VK_ESCAPE:
				{
					return 0;
					break;
				}
				
			}
		}
	}
	
	return CDialog::PreTranslateMessage(pMsg);
}

void CTitlescrollDlg::SetCurrentLineDlg(int iLine)
{
	CString LineNumber = "";
	LineNumber.Format("%d",iLine);
	SetDlgItemText(IDC_EDIT_CURRENT_LINE,LineNumber);
}

void CTitlescrollDlg::OnDeltaposSpinScrollSpeed(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_UPDOWN* pNMUpDown = (NM_UPDOWN*)pNMHDR;
	// TODO: Add your control notification handler code here

	CString Speed;
	GetDlgItemText(IDC_EDIT_SCROLLING_SPEED,Speed);

		if(pNMUpDown->iDelta == -1)
		{	
			if(Speed == "0")
			{
				SetDlgItemText(IDC_EDIT_SCROLLING_SPEED,"1");
				TSC.SetScrollSpeed(1);
			}
			else if(Speed == "1")
			{
				SetDlgItemText(IDC_EDIT_SCROLLING_SPEED,"2");
				TSC.SetScrollSpeed(2);
			}
			else if(Speed == "2")
			{
				SetDlgItemText(IDC_EDIT_SCROLLING_SPEED,"3");
				TSC.SetScrollSpeed(3);
			}
			else if(Speed == "3")
			{
				SetDlgItemText(IDC_EDIT_SCROLLING_SPEED,"4");
				TSC.SetScrollSpeed(4);
			}
		}
		else
		{
			if(Speed == "4")
			{
				SetDlgItemText(IDC_EDIT_SCROLLING_SPEED,"3");
				TSC.SetScrollSpeed(3);
			}
			else if(Speed == "3")
			{
				SetDlgItemText(IDC_EDIT_SCROLLING_SPEED,"2");
				TSC.SetScrollSpeed(2);
			}
			else if(Speed == "2")
			{
				SetDlgItemText(IDC_EDIT_SCROLLING_SPEED,"1");
				TSC.SetScrollSpeed(1);
			}
			else if(Speed == "1")
			{
				SetDlgItemText(IDC_EDIT_SCROLLING_SPEED,"0");
				TSC.SetScrollSpeed(0);
			}		
		}

		int iScrSpd = TSC.GetScrollSpeed();
		if(iScrSpd == 1)
			iScrSpd = 200;
		if(iScrSpd == 0)
			iScrSpd = 400;
		if(iScrSpd == 2)
			iScrSpd = 100;
		if(iScrSpd == 3)
			iScrSpd = 50;
		if(iScrSpd == 4)
			iScrSpd = 25;

		if(iScroll == 1)
		{
			PlayState = 0;
			SetDlgItemText(IDC_BUTTON_PLAY_PAUSE,"Play");		
			KillTimer(1);
			SetStatus("Paused");
			GetDlgItem(IDC_CHECK_LINE_WRAP)->EnableWindow(FALSE);
		}
		else
		{
			PlayState = 0;
			SetDlgItemText(IDC_BUTTON_PLAY_PAUSE,"Play");		
			KillTimer(1);
			SetStatus("Paused");
			GetDlgItem(IDC_CHECK_LINE_WRAP)->EnableWindow(FALSE);
		}


	*pResult = 0;
}
void CTitlescrollDlg::SetStatus(CString cStatus)
{
	SetDlgItemText(IDC_STATIC_STATUS_INDICATOR,cStatus);
}
int CTitlescrollDlg::GetEndingTime(int Hour,int Minute,int &EndHour, int &EndMinute)
{
	int Hours = Hour;
	int Minutes = Minute + AlarmDisplayTime;
	while(Minutes > 60)
	{
		Minutes -= 60;
		Hours++;
	}
	if(Hours > 24)
		Hours = Hours - 24;

	EndHour = Hours;
	EndMinute = Minutes;
	return 1;
}
void CTitlescrollDlg::OnTimer(UINT nIDEvent) 
{

	if(nIDEvent == 69)
	{
		SYSTEMTIME systime;
		GetLocalTime(&systime);
		CTime CurrentTime(systime.wYear,systime.wMonth,systime.wDay, systime.wHour, systime.wMinute, systime.wSecond, -1);
		int CurrentHour;
		int CurrentMinute;
		int Hour1 = 0, Hour2 = 0, Hour3 = 0, Hour4 = 0;
		int Minute1 = 0, Minute2 = 0, Minute3 = 0, Minute4 = 0;

		int EndingHour1, EndingHour2, EndingHour3,EndingHour4;
		int EndingMinute1,EndingMinute2,EndingMinute3,EndingMinute4;

		CurrentHour = CurrentTime.GetHour();
		CurrentMinute = CurrentTime.GetMinute();
		Hour1 = Time1.GetHour();
		Minute1 = Time1.GetMinute();
		Hour2 = Time2.GetHour();
		Minute2 = Time2.GetMinute();
		Hour3 = Time3.GetHour();
		Minute3 = Time3.GetMinute();
		Hour4 = Time4.GetHour();
		Minute4 = Time4.GetMinute();		
		
		GetEndingTime(Hour1,Minute1,EndingHour1, EndingMinute1);
		GetEndingTime(Hour2,Minute2,EndingHour2, EndingMinute2);
		GetEndingTime(Hour3,Minute3,EndingHour3, EndingMinute3);
		GetEndingTime(Hour4,Minute4,EndingHour4, EndingMinute4);

/*		CString Crap;
		Crap.Format("CurHr %d, CurMin %d,Hour1 %d,Min1 %d",CurrentHour,CurrentMinute,Hour1,Minute1);
		MessageBox(Crap);
*/
		if(Alarm1 == 1)
		{
			if(CurrentHour > Hour1)
				Alarm1Go = 1;
			
			if(CurrentHour == Hour1)
				if(CurrentMinute > Minute1)
					Alarm1Go = 1;

			if(CurrentHour > EndingHour1)
			{
				Alarm1Go = 0;
				AlarmTimerIndex = 0;
			}
			
			if(CurrentHour == EndingHour1)
				if(CurrentMinute > EndingMinute1)
				{
					Alarm1Go = 0;
					AlarmTimerIndex = 0;
				}
		}
		if(Alarm2 == 1)
		{
			if(CurrentHour > Hour2)
				Alarm2Go = 1;
			
			if(CurrentHour == Hour2)
				if(CurrentMinute > Minute2)
					Alarm2Go = 1;

			if(CurrentHour > EndingHour2)
			{
				Alarm2Go = 0;
				AlarmTimerIndex = 0;
			}
			
			if(CurrentHour == EndingHour2)
				if(CurrentMinute > EndingMinute2)
				{
					Alarm2Go = 0;						
					AlarmTimerIndex = 0;
				}
		}
		if(Alarm3 == 1)
		{
			if(CurrentHour > Hour3)
				Alarm3Go = 1;
			
			if(CurrentHour == Hour3)
				if(CurrentMinute > Minute3)
					Alarm3Go = 1;

			if(CurrentHour > EndingHour3)
			{
				Alarm3Go = 0;
				AlarmTimerIndex = 0;
			}
			
			if(CurrentHour == EndingHour3)
				if(CurrentMinute > EndingMinute3)
				{
					Alarm3Go = 0;						
					AlarmTimerIndex = 0;
				}
		}
		if(Alarm4 == 1)
		{
			if(CurrentHour > Hour4)
				Alarm4Go = 1;
			
			if(CurrentHour == Hour4)
				if(CurrentMinute > Minute4)
					Alarm4Go = 1;

			if(CurrentHour > EndingHour4)
			{
				Alarm4Go = 0;
				AlarmTimerIndex = 0;
				}
			
			if(CurrentHour == EndingHour4)
				if(CurrentMinute > EndingMinute4)
				{
					Alarm4Go = 0;						
					AlarmTimerIndex = 0;
				}
		}



	}
	else
	{
		
		CString poop = "";
		CString cCurrentLine = TSC.GetLineAtCurrentScrollPosition();
		int iCurrentLineLength = cCurrentLine.GetLength();

	if(Alarm1Go == 1 || Alarm2Go == 1 || Alarm3Go == 1 || Alarm4Go == 1)
	{
		CString ConglomerateAlarmText = "";
		if(Alarm1Go == 1)
		{
			ConglomerateAlarmText += "Alarm 1 : ";
			ConglomerateAlarmText += Edit1;
		}
		if(Alarm2Go == 1)
		{
			ConglomerateAlarmText += "Alarm 2 : ";
			ConglomerateAlarmText += Edit2;
		}
		if(Alarm3Go == 1)
		{
			ConglomerateAlarmText += "Alarm 3 : ";
			ConglomerateAlarmText += Edit3;
		}
		if(Alarm4Go == 1)
		{
			ConglomerateAlarmText += "Alarm 4 : ";
			ConglomerateAlarmText += Edit4;
		}

		int ConglomerateLength = ConglomerateAlarmText.GetLength();
		if(iScroll == 1)
		{
			if(AlarmTimerIndex > ConglomerateLength)
			{
				AlarmTimerIndex = 0;
			}
			else
			{
				AlarmTimerIndex++;
			}
			CString cTitle = "";
			cTitle = ConglomerateAlarmText.Right(ConglomerateAlarmText.GetLength() - AlarmTimerIndex);
			if(ActiveWindow == 1)
				SetTitleTextOnCurrentWindow(cTitle);
			else
				SetTitleText(cTitle);

		}
		else
		{
			if((AlarmTimerIndex + iCharacters) > ConglomerateLength)
			{
				AlarmTimerIndex = 0;
			}
			else
			{
				AlarmTimerIndex += iCharacters;
			}
			CString cTitle = "";
			cTitle = ConglomerateAlarmText.Right(ConglomerateAlarmText.GetLength() - AlarmTimerIndex);
			if(ActiveWindow == 1)
				SetTitleTextOnCurrentWindow(cTitle);
			else
				SetTitleText(cTitle);
			
		
		}
	}
	else
	{
			if(iScroll == 1)
			{
				if(iTimerIndex > iCurrentLineLength)
				{
					iTimerIndex = 0;
					if(TSC.GetScrollPosition() < TSC.GetNumberOfLinesInFile())
					{
						TSC.SetScrollPosition(TSC.GetScrollPosition() + 1);
						SetCurrentLineDlg(TSC.GetScrollPosition() + 1);
					}
					else
					{
						TSC.SetScrollPosition(0);
						SetCurrentLineDlg(0);		
					}
				}

				CString cTitle = GetTextForTitle();
				
				if(ActiveWindow == 1)
					SetTitleTextOnCurrentWindow(cTitle);
				else
					SetTitleText(cTitle);


				iTimerIndex++;
			}
			else
			{
				if(iTimerIndex > iCurrentLineLength)
				{
					iTimerIndex = 0;
					if(TSC.GetScrollPosition() < TSC.GetNumberOfLinesInFile())
					{
						TSC.SetScrollPosition(TSC.GetScrollPosition() + 1);
						SetCurrentLineDlg(TSC.GetScrollPosition() + 1);
					}
					else
					{
						TSC.SetScrollPosition(0);
						SetCurrentLineDlg(0);		
					}
				}
	if(Random == 1)
	{
		int newlineguy = rand()%TSC.GetNumberOfLinesInFile();
		TSC.SetScrollPosition(newlineguy);
		SetCurrentLineDlg(newlineguy);
	}
				CString cTitle = GetTextForTitle();
				
				if(ActiveWindow == 1)
					SetTitleTextOnCurrentWindow(cTitle);
				else
					SetTitleText(cTitle);


				iTimerIndex+=iCharacters;	
			}
		}
	}
	CDialog::OnTimer(nIDEvent);
}
void CTitlescrollDlg::SetTitleText(CString cTitleText)
{
	SetWindowText(cTitleText);
}
void CTitlescrollDlg::SetTitleTextOnCurrentWindow(CString cTitleText)
{
	CWnd * FrontWindow;
	FrontWindow = GetForegroundWindow();

	if(FrontWindow == NULL)
	{
		FrontWindow = GetForegroundWindow();
		iTimerIndex--;
	}
	else
	{
		CString WindowText;
		FrontWindow->GetWindowText(WindowText);
		if(WindowText == "About titlescroll")
		{
			FrontWindow = GetForegroundWindow();
			iTimerIndex--;
		}
		else
		{
			if((LastFrontWindow != NULL) && (LastFrontWindow != FrontWindow))
			{
				LastFrontWindow->SetWindowText(LastWindowText);	
				FrontWindow->GetWindowText(LastWindowText);
			}	
			LastFrontWindow = FrontWindow;
			FrontWindow->SetWindowText(cTitleText);
		}
	}
	
}

CString CTitlescrollDlg::GetTextForTitle()
{

		if(iScroll == 1)
		{
			CString CurrentLine = TSC.GetLineAtCurrentScrollPosition();
			int iCurrentLineLength = CurrentLine.GetLength();
			int iDiff = (iCurrentLineLength - iTimerIndex);
			if( (iDiff < iCharacters) && (iLineWrap == 1))
			{
				CString cTitle = CurrentLine.Right(iCurrentLineLength - iTimerIndex);
				cTitle += " ";
				if(TSC.GetScrollPosition() < TSC.GetNumberOfLinesInFile())
				{
					CString cTemp = TSC.GetLineAtScrollPosition(TSC.GetScrollPosition() + 1);
					cTemp = cTemp.Left(iCharacters - iDiff);
					cTitle += cTemp;
				}
				return "     " + cTitle;
			}
			else
			{
				CurrentLine = CurrentLine.Left(iTimerIndex + iCharacters);
				CString cTitle = CurrentLine.Right(CurrentLine.GetLength() - iTimerIndex);
				return "     " + cTitle;
			}
		}
		else
		{
			CString CurrentLine = TSC.GetLineAtCurrentScrollPosition();
			int iCurrentLineLength = CurrentLine.GetLength();
			if( (iCurrentLineLength - iTimerIndex) < iCharacters)
			{
				CString cTitle = CurrentLine.Right(iCurrentLineLength - iTimerIndex);
				cTitle += " ";
				return "     " + cTitle;
			}
			else
			{
				CurrentLine = CurrentLine.Left(iTimerIndex + iCharacters);
				CString cTitle = CurrentLine.Right(CurrentLine.GetLength() - iTimerIndex);
				int forstop = 0;;
				for(int i = 0;i<cTitle.GetLength();i++)
				{
					if(cTitle.GetAt(i) == ' ')
						forstop = i;
				}			
				if(forstop != 0)
				{
					iTimerIndex -= (cTitle.GetLength() - forstop);
					cTitle = cTitle.Left(forstop);

				}
				return "     " + cTitle;
			}	
		}
	

}

void CTitlescrollDlg::OnButtonNext() 
{
	if((TSC.GetNumberOfLinesInFile() - TSC.GetScrollPosition()) > 1)
	{
		TSC.SetScrollPosition(TSC.GetScrollPosition() + 1);
	}
	else
		TSC.SetScrollPosition(0);

	SetCurrentLineDlg(TSC.GetScrollPosition());	
}

void CTitlescrollDlg::OnRadioScroll() 
{
	CButton * appearer;
	appearer = (CButton*)GetDlgItem(IDC_RADIO_APPEAR);
	appearer->SetCheck(0);
	iScroll = 1;

	PlayState = 0;
	SetDlgItemText(IDC_BUTTON_PLAY_PAUSE,"Play");		
	KillTimer(1);
	SetStatus("Paused");	
	GetDlgItem(IDC_CHECK_LINE_WRAP)->EnableWindow(TRUE);
	GetDlgItem(IDC_CHECK_RANDOM)->EnableWindow(FALSE);
}

void CTitlescrollDlg::OnRadioAppear() 
{
	CButton * scroller;
	scroller = (CButton*)GetDlgItem(IDC_RADIO_SCROLL);
	scroller->SetCheck(0);	
	iScroll = 0;

	PlayState = 0;
	SetDlgItemText(IDC_BUTTON_PLAY_PAUSE,"Play");		
	KillTimer(1);
	SetStatus("Paused");
	GetDlgItem(IDC_CHECK_LINE_WRAP)->EnableWindow(FALSE);
	GetDlgItem(IDC_CHECK_RANDOM)->EnableWindow(TRUE);
}

void CTitlescrollDlg::OnDeltaposSpinCharacters(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_UPDOWN* pNMUpDown = (NM_UPDOWN*)pNMHDR;

	CString cToSet;

	if(pNMUpDown->iDelta == -1)
	{	
		if(iCharacters < 100)
		{
			iCharacters +=10;
			cToSet.Format("%d",iCharacters);
			SetDlgItemText(IDC_EDIT_CHARACTERS,cToSet);
		}
	}
	else
	{
		if(iCharacters > 0)
		{
			iCharacters -=10;
			cToSet.Format("%d",iCharacters);
			SetDlgItemText(IDC_EDIT_CHARACTERS,cToSet);
		}
	
	}


	*pResult = 0;
}

void CTitlescrollDlg::OnCheckLineWrap() 
{
	if(iLineWrap == 1)
	{
		iLineWrap = 0;
	}
	else
	{
		iLineWrap = 1;
	}
}

void CTitlescrollDlg::OnButtonAlarm() 
{
	if(PlayState == 1)
	{
		PlayState = 0;
		SetDlgItemText(IDC_BUTTON_PLAY_PAUSE,"Play");		
		
		KillTimer(1);
		
		SetStatus("Paused");

	}
	AlarmDialog alm;
	alm.DoModal();
	CString cActiveAlarms = "";
	if(Alarm1 == 1)
		cActiveAlarms += " 1 ";
	if(Alarm2 == 1)
		cActiveAlarms += " 2 ";
	if(Alarm3 == 1)
		cActiveAlarms += " 3 ";
	if(Alarm4 == 1)
		cActiveAlarms += " 4 ";

	SetDlgItemText(IDC_STATIC_ALARM_NEXT,cActiveAlarms);
}

void CTitlescrollDlg::OnCheckAlarms() 
{
	if(CheckAlarm == 0)
	{	
		CheckAlarm = 1;
		AlarmTimerIndex = 0;
	if(PlayState == 1)
	{
		PlayState = 0;
		SetDlgItemText(IDC_BUTTON_PLAY_PAUSE,"Play");		
		
		KillTimer(1);
		
		SetStatus("Paused");

	}

		SetTimer(69, 6000, NULL);
		if(iLoad == 1)
		{
			MessageBox("Alarms will only activate if a text file is currently playing, If you won't want the distraction, load the blankalarms.txt file in this directory");
		}
	}
	else
	{
		KillTimer(69);
		Alarm1Go = 0;
		Alarm2Go = 0;
		Alarm3Go = 0;
		Alarm4Go = 0;
		CheckAlarm = 0;
		AlarmTimerIndex = 0;
	}
}

void CTitlescrollDlg::OnBnClickedCheckRandom()
{
	if(Random == 1)
		Random = 0;
	else
		Random = 1;
}
