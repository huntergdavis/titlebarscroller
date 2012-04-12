// AlarmDialog.cpp : implementation file
//

#include "stdafx.h"
#include "titlescroll.h"
#include "AlarmDialog.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern CString Edit1, Edit2, Edit3, Edit4;
extern int AlarmDisplayTime;
extern CTime Time1, Time2, Time3, Time4;
extern bool Alarm1, Alarm2, Alarm3, Alarm4;

/////////////////////////////////////////////////////////////////////////////
// AlarmDialog dialog


AlarmDialog::AlarmDialog(CWnd* pParent /*=NULL*/)
	: CDialog(AlarmDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(AlarmDialog)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void AlarmDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(AlarmDialog)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(AlarmDialog, CDialog)
	//{{AFX_MSG_MAP(AlarmDialog)
	ON_BN_CLICKED(IDC_CHECK1, OnCheck1)
	ON_BN_CLICKED(IDC_CHECK2, OnCheck2)
	ON_BN_CLICKED(IDC_CHECK3, OnCheck3)
	ON_BN_CLICKED(IDC_CHECK4, OnCheck4)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// AlarmDialog message handlers

void AlarmDialog::OnCheck1() 
{
	if(Alarm1 == 0)
		Alarm1 = 1;
	else
		Alarm1 = 0;
	
	SetActive();
}

void AlarmDialog::OnCheck2() 
{
	if(Alarm2 == 0)
		Alarm2 = 1;
	else
		Alarm2 = 0;

	SetActive();	
}

void AlarmDialog::OnCheck3() 
{
	if(Alarm3 == 0)
		Alarm3 = 1;
	else
		Alarm3 = 0;	

	SetActive();
}

void AlarmDialog::OnCheck4() 
{
	if(Alarm4 == 0)
		Alarm4 = 1;
	else
		Alarm4 = 0;	

	SetActive();
}

void AlarmDialog::OnOK() 
{
	GetDlgItemText(IDC_EDIT1,Edit1);
	GetDlgItemText(IDC_EDIT2,Edit2);
	GetDlgItemText(IDC_EDIT3,Edit3);
	GetDlgItemText(IDC_EDIT4,Edit4);
	CString temptime = "";
	GetDlgItemText(IDC_EDIT_TIME,temptime);
	if(temptime == "")
	{
		MessageBox("No Alarm Interval Time Set, Will Default to 15 minutes");
		SetDlgItemText(IDC_EDIT_TIME,"15");
	}
	AlarmDisplayTime = atoi(temptime);

	CDateTimeCtrl *DTC1, *DTC2, *DTC3, *DTC4;

	DTC1 = (CDateTimeCtrl*)GetDlgItem(IDC_DATETIMEPICKER1);
	DTC2 = (CDateTimeCtrl*)GetDlgItem(IDC_DATETIMEPICKER2);
	DTC3 = (CDateTimeCtrl*)GetDlgItem(IDC_DATETIMEPICKER3);
	DTC4 = (CDateTimeCtrl*)GetDlgItem(IDC_DATETIMEPICKER4);

	DTC1->GetTime(Time1);
	DTC2->GetTime(Time2);
	DTC3->GetTime(Time3);
	DTC4->GetTime(Time4);


	CDialog::OnOK();
}

BOOL AlarmDialog::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	SetActive();
	if(AlarmDisplayTime = 0)
		AlarmDisplayTime = 15;
	SetDlgItemText(IDC_EDIT_TIME,"15");

	CDateTimeCtrl *DTC1, *DTC2, *DTC3, *DTC4;
	DTC1 = (CDateTimeCtrl*)GetDlgItem(IDC_DATETIMEPICKER1);
	DTC2 = (CDateTimeCtrl*)GetDlgItem(IDC_DATETIMEPICKER2);
	DTC3 = (CDateTimeCtrl*)GetDlgItem(IDC_DATETIMEPICKER3);
	DTC4 = (CDateTimeCtrl*)GetDlgItem(IDC_DATETIMEPICKER4);


	if(Alarm1 == 1)
	{
		DTC1->SetTime(&Time1);
		SetDlgItemText(IDC_EDIT1,Edit1);
	}
	if(Alarm2 == 1)
	{
		DTC2->SetTime(&Time2);
		SetDlgItemText(IDC_EDIT2,Edit2);
	}
	if(Alarm3 == 1)
	{
		DTC3->SetTime(&Time3);
		SetDlgItemText(IDC_EDIT3,Edit3);
	}
	if(Alarm1 == 1)
	{
		DTC4->SetTime(&Time4);
		SetDlgItemText(IDC_EDIT4,Edit4);
	}
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
void AlarmDialog::SetActive()
{
	CButton* pCheck;
	if(Alarm1 == 0)
	{
		GetDlgItem(IDC_DATETIMEPICKER1)->EnableWindow(0);
		GetDlgItem(IDC_EDIT1)->EnableWindow(0);		
	}
	else
	{
		pCheck = (CButton*)GetDlgItem(IDC_CHECK1);
		pCheck->SetCheck(1);
		GetDlgItem(IDC_DATETIMEPICKER1)->EnableWindow(1);
		GetDlgItem(IDC_EDIT1)->EnableWindow(1);	
	}
	if(Alarm2 == 0)
	{
		GetDlgItem(IDC_DATETIMEPICKER2)->EnableWindow(0);
		GetDlgItem(IDC_EDIT2)->EnableWindow(0);	
	}
	else
	{
		pCheck = (CButton*)GetDlgItem(IDC_CHECK2);
		pCheck->SetCheck(1);
		GetDlgItem(IDC_DATETIMEPICKER2)->EnableWindow(1);
		GetDlgItem(IDC_EDIT2)->EnableWindow(1);	
	}
	if(Alarm3 == 0)
	{
		GetDlgItem(IDC_DATETIMEPICKER3)->EnableWindow(0);
		GetDlgItem(IDC_EDIT3)->EnableWindow(0);	
	}
	else
	{
		pCheck = (CButton*)GetDlgItem(IDC_CHECK3);
		pCheck->SetCheck(1);
		GetDlgItem(IDC_DATETIMEPICKER3)->EnableWindow(1);
		GetDlgItem(IDC_EDIT3)->EnableWindow(1);	
	}
	if(Alarm4 == 0)
	{
		GetDlgItem(IDC_DATETIMEPICKER4)->EnableWindow(0);
		GetDlgItem(IDC_EDIT4)->EnableWindow(0);	
	}
	else
	{
		pCheck = (CButton*)GetDlgItem(IDC_CHECK4);
		pCheck->SetCheck(1);
		GetDlgItem(IDC_DATETIMEPICKER4)->EnableWindow(1);
		GetDlgItem(IDC_EDIT4)->EnableWindow(1);	
	}
}