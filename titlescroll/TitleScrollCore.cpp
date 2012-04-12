#include "StdAfx.h"
#include "TitleScrollCore.h"
#include <afx.h>


TitleScrollCore::TitleScrollCore()
{
	iScrollSpeed = 1;
	bScrollForward = 1;
	iScrollPosition = 0;
}
bool TitleScrollCore::ReadInTextFile(CString TextFileName)
{
	CStdioFile fileIn;

	if (fileIn.Open(TextFileName, CFile::modeRead | CFile::shareDenyWrite))
	{
	   CString strTemp;

	   while (fileIn.ReadString(strTemp))
		  cFileToBeScrolled.Add(strTemp);

	   fileIn.Close();
	}
	else
	{
	   return 0;
	}

	return 1;
}
int TitleScrollCore::GetScrollSpeed()
{
	return iScrollSpeed;
}
void TitleScrollCore::SetScrollSpeed(int iSpeed)
{
	iScrollSpeed = iSpeed;
}
bool TitleScrollCore::GetScrollForward()
{
	return bScrollForward;
}
void TitleScrollCore::SetScrollForward(bool bForward)
{
	bScrollForward = bForward;
}
int TitleScrollCore::GetScrollPosition()
{
	return iScrollPosition;
}
void TitleScrollCore::SetScrollPosition(int iPosition)
{
	iScrollPosition = iPosition;
}
CString TitleScrollCore::GetLineAtCurrentScrollPosition()
{
	return cFileToBeScrolled.GetAt(iScrollPosition);
}
CString TitleScrollCore::GetLineAtScrollPosition(int iPosition)
{
	return cFileToBeScrolled.GetAt(iPosition);
}
int TitleScrollCore::GetNumberOfLinesInFile()
{
	return cFileToBeScrolled.GetSize()-1;
}
void TitleScrollCore::ClearAll()
{
	cFileToBeScrolled.RemoveAll();
	iScrollSpeed = 1;
	bScrollForward = 1;
	iScrollPosition = 0;
}