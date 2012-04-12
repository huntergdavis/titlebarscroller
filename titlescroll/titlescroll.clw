; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=AlarmDialog
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "titlescroll.h"

ClassCount=4
Class1=CTitlescrollApp
Class2=CTitlescrollDlg
Class3=CAboutDlg

ResourceCount=4
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Resource3=IDD_TITLESCROLL_DIALOG
Class4=AlarmDialog
Resource4=IDD_ALARM_DIALOG

[CLS:CTitlescrollApp]
Type=0
HeaderFile=titlescroll.h
ImplementationFile=titlescroll.cpp
Filter=N

[CLS:CTitlescrollDlg]
Type=0
HeaderFile=titlescrollDlg.h
ImplementationFile=titlescrollDlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC
LastObject=CTitlescrollDlg

[CLS:CAboutDlg]
Type=0
HeaderFile=titlescrollDlg.h
ImplementationFile=titlescrollDlg.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_TITLESCROLL_DIALOG]
Type=1
Class=CTitlescrollDlg
ControlCount=29
Control1=IDOK,button,1342242817
Control2=IDC_CHECK_ACTIVE_WINDOW,button,1342242819
Control3=IDC_STATIC_LOADED_FILE,static,1342308352
Control4=IDC_BUTTON_LOAD_TEXT_FILE,button,1342242816
Control5=IDC_SPIN_SCROLL_SPEED,msctls_updown32,1342177312
Control6=IDC_STATIC,static,1342308352
Control7=IDC_EDIT_SCROLLING_SPEED,edit,1484783744
Control8=IDC_STATIC_CURRENT_LINE,static,1342308352
Control9=IDC_STATIC,button,1342177287
Control10=IDC_BUTTON_PLAY_PAUSE,button,1342242816
Control11=IDC_BUTTON_GOTO_LINE,button,1342242816
Control12=IDC_BUTTON_REWIND,button,1342242816
Control13=IDC_BUTTON_BACK_10,button,1342242816
Control14=IDC_BUTTON_FORWARD_10,button,1342242816
Control15=IDC_BUTTON_HELP_ABOUT,button,1342242816
Control16=IDC_STATIC_STATUS,button,1342177287
Control17=IDC_STATIC_STATUS_INDICATOR,static,1342308352
Control18=IDC_EDIT_CURRENT_LINE,edit,1350639744
Control19=IDC_BUTTON_NEXT,button,1342242816
Control20=IDC_RADIO_SCROLL,button,1342177289
Control21=IDC_RADIO_APPEAR,button,1342177289
Control22=IDC_STATIC,static,1342308352
Control23=IDC_EDIT_CHARACTERS,edit,1484783744
Control24=IDC_SPIN_CHARACTERS,msctls_updown32,1342177312
Control25=IDC_CHECK_LINE_WRAP,button,1342242819
Control26=IDC_CHECK_ALARMS,button,1342242819
Control27=IDC_BUTTON_ALARM,button,1342242816
Control28=IDC_STATIC_STATUS2,button,1342177287
Control29=IDC_STATIC_ALARM_NEXT,static,1342308352

[DLG:IDD_ALARM_DIALOG]
Type=1
Class=AlarmDialog
ControlCount=20
Control1=IDOK,button,1342242817
Control2=IDC_CHECK1,button,1342242819
Control3=IDC_DATETIMEPICKER1,SysDateTimePick32,1342242857
Control4=IDC_EDIT1,edit,1350631492
Control5=IDC_STATIC,button,1342177287
Control6=IDC_CHECK2,button,1342242819
Control7=IDC_DATETIMEPICKER2,SysDateTimePick32,1342242857
Control8=IDC_EDIT2,edit,1350631492
Control9=IDC_STATIC,button,1342177287
Control10=IDC_CHECK3,button,1342242819
Control11=IDC_DATETIMEPICKER3,SysDateTimePick32,1342242857
Control12=IDC_EDIT3,edit,1350631492
Control13=IDC_STATIC,button,1342177287
Control14=IDC_CHECK4,button,1342242819
Control15=IDC_DATETIMEPICKER4,SysDateTimePick32,1342242857
Control16=IDC_EDIT4,edit,1350631492
Control17=IDC_STATIC,button,1342177287
Control18=IDC_STATIC,static,1342308352
Control19=IDC_EDIT_TIME,edit,1350639744
Control20=IDC_STATIC,static,1342308352

[CLS:AlarmDialog]
Type=0
HeaderFile=AlarmDialog.h
ImplementationFile=AlarmDialog.cpp
BaseClass=CDialog
Filter=D
LastObject=AlarmDialog
VirtualFilter=dWC

