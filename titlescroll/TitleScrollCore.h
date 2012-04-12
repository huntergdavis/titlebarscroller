#include "StdAfx.h"


class TitleScrollCore
{

	public:
	TitleScrollCore();
	bool ReadInTextFile(CString TextFileName);

	int GetScrollSpeed();
	void SetScrollSpeed(int iSpeed);
	
	bool GetScrollForward();
	void SetScrollForward(bool bForward);

	int GetScrollPosition();
	void SetScrollPosition(int iPosition);

	CString GetLineAtCurrentScrollPosition();
	CString GetLineAtScrollPosition(int iPosition);

	void ClearAll();

	int GetNumberOfLinesInFile();

	private:
	CStringArray cFileToBeScrolled;
	int iScrollSpeed;
	bool bScrollForward;
	int iScrollPosition;

};

