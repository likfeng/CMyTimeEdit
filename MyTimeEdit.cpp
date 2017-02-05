// MyTimeEdit.cpp : implementation file
//

#include "stdafx.h"
#include "MyTimeEdit.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyTimeEdit

CMyTimeEdit::CMyTimeEdit()
{
	m_bSubClass = FALSE;

	m_nLen = 14;
	m_HourLen = 4;
	m_nMinLen = 2;
	m_nSecLen = 2;
	m_nMSLen = 3;
	
	m_HourStart = 0;
	m_nMinStart = 5;
	m_nSecStart = 8;
	m_nMSStart = 11;
	
	m_nFlag1Start = 4;
	m_nFlag2Start = 7;
	m_nFlag3Start = 10;
}

CMyTimeEdit::~CMyTimeEdit()
{
}


BEGIN_MESSAGE_MAP(CMyTimeEdit, CEdit)
	//{{AFX_MSG_MAP(CMyTimeEdit)
	ON_WM_CHAR()
	ON_WM_KEYDOWN()
	ON_WM_CONTEXTMENU()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyTimeEdit message handlers


BOOL CMyTimeEdit::MySubclassDlgItem(UINT nID, CWnd* pParent)
{
	if (m_bSubClass)
	{
		UnsubclassWindow();
	}
	m_bSubClass = TRUE;
	return SubclassDlgItem(nID, pParent);
}

BOOL CMyTimeEdit::Init(DWORD nTime, BYTE nHourLen, BYTE nMSLen)
{
	int nMSMode = GetMul(nMSLen);
	if (nMSMode < 0)
	{
		return FALSE;
	}

	int nHour = nTime / nMSMode / 60 / 60;
	if (nHourLen <= 0)
	{
		return FALSE;
	}
	else if (nHourLen == 1 && nHour >= 10)
	{
		return FALSE;
	}
	else if (nHourLen == 2 && nHour >= 100)
	{
		return FALSE;
	}
	else if (nHourLen == 3 && nHour >= 1000)
	{
		return FALSE;
	}
	else if (nHourLen == 4 && nHour >= 10000)
	{
		return FALSE;
	}
	int nMin = nTime / nMSMode / 60 % 60;
	int nSec = nTime / nMSMode % 60;
	int nMS = nTime % nMSMode;

	CString strTime;
	CString strTimeFormat;

	if (nMSMode == 1)
	{
		strTimeFormat.Format(_T("%%0%dd:%%02d:%%02d"), nHourLen, nMSLen);
		strTime.Format(strTimeFormat, nHour, nMin, nSec);
	}
	else
	{
		strTimeFormat.Format(_T("%%0%dd:%%02d:%%02d.%%0%dd"), nHourLen, nMSLen);
		strTime.Format(strTimeFormat, nHour, nMin, nSec, nMS);
	}

	SetWindowText(strTime);

	SetLimitText(strTime.GetLength());

	m_nLen = m_nLen - (3 - nMSLen) - (4 - nHourLen);
	m_HourLen = nHourLen;
	m_nMSLen = nMSLen;
	
	m_nMinStart -= (4 - nHourLen);
	m_nSecStart -= (4 - nHourLen);
	m_nMSStart -= (4 - nHourLen);
	
	m_nFlag1Start -= (4 - nHourLen);
	m_nFlag2Start -= (4 - nHourLen);
	m_nFlag3Start -= (4 - nHourLen);

	return TRUE;
}

int CMyTimeEdit::GetTime()
{
	int nHour = GetHour();
	int nMin = GetMin();
	int nSec = GetSec();
	int nMS = GetMS();
	int nMul = GetMul(m_nMSLen);
	int nTime = (nHour * 3600 + nMin * 60 + nSec) * nMul + nMS;
	return nTime;
}

int CMyTimeEdit::GetHour()
{
	CString str;
	GetWindowText(str);
	CString strHour;
	strHour = str.Left(m_nFlag1Start);
	int nHour = atoi(strHour);
	return nHour;
}

int CMyTimeEdit::GetMin()
{
	CString str;
	GetWindowText(str);
	CString strMin;
	strMin = str.Left(m_nFlag2Start).Right(m_nMinLen);
	int nMin = atoi(strMin);
	return nMin;
}

int CMyTimeEdit::GetSec()
{
	CString str;
	GetWindowText(str);
	CString strSec;
	strSec = str.Left(m_nFlag3Start).Right(m_nSecLen);
	int nSec = atoi(strSec);
	return nSec;
}

int CMyTimeEdit::GetMS()
{
	if (m_nMSLen <= 0)
	{
		return 0;
	}
	else
	{
		CString str;
		GetWindowText(str);
		CString strMS;
		strMS = str.Right(m_nMSLen);
		int nMS = atoi(strMS);
		return nMS;
	}
}

int CMyTimeEdit::GetMul(int n)
{
	int nRet;
	switch(n)
	{
	case 0:
		nRet = 1;
		break;
	case 1:
		nRet = 10;
		break;
	case 2:
		nRet = 100;
		break;
	case 3:
		nRet = 1000;
		break;
	default:
		nRet = -1;
	}
	return nRet;
}

void CMyTimeEdit::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	int nStartChar;
	int nEndChar;
	
	GetSel(nStartChar, nEndChar);
	nEndChar = nStartChar;
	
	CString str;
	GetWindowText(str);
	
	if ( nChar >= '0' && nChar <= '9' )
	{
		if (nStartChar == m_nFlag1Start || nStartChar == m_nFlag2Start || (nStartChar == m_nFlag3Start && m_nMSLen > 0))
		{
			nStartChar++;
			nEndChar = nStartChar + 1;
		}
		if (nStartChar == m_nMinStart || nStartChar == m_nSecStart)
		{
			if ( nChar >= '0' && nChar <= '5' )
			{
				str.Delete(nStartChar,1);
				SetWindowText(str);
				SetSel(nStartChar, nStartChar);
				CEdit::OnChar(nChar, nRepCnt, nFlags);
			}
		}
		else
		{
			str.Delete(nStartChar,1);
			SetWindowText(str);
			SetSel(nStartChar, nStartChar);
			CEdit::OnChar(nChar, nRepCnt, nFlags);
			nStartChar++;
			nEndChar = nStartChar + 1;
			if (nStartChar == m_nFlag1Start || nStartChar == m_nFlag2Start || (nStartChar == m_nFlag3Start && m_nMSLen > 0))
			{
				nStartChar++;
				nEndChar = nStartChar + 1;
				SetSel(nStartChar, nStartChar);
			}
		}
		if (m_nMSLen == 3 && m_HourLen == 4 && nStartChar <= m_nFlag1Start + 1)
		{
			int nHour = GetHour();
			if (nHour > 1000)
			{
				GetWindowText(str);
				str.SetAt(0, '0');
				str.SetAt(1, '0');
				str.SetAt(2, '0');
				str.SetAt(3, '0');
				SetWindowText(str);
			}
		}
	}
	else
	{
		if ( nChar==VK_BACK )
		{
			if (nStartChar == m_nFlag1Start + 1 || nStartChar == m_nFlag2Start + 1 || (nStartChar == m_nFlag3Start + 1 && m_nMSLen > 0))
			{
				nStartChar--;
				nEndChar = nStartChar + 1;
			}
			if (nStartChar > 0 && nStartChar <= m_nLen)
			{
				str.Delete(nStartChar-1, 1);
				str.Insert(nStartChar-1, '0');
				SetWindowText(str);
				nStartChar--;
				nEndChar = nStartChar + 1;
				if (nStartChar == m_nFlag1Start + 1 || nStartChar == m_nFlag2Start + 1 || (nStartChar == m_nFlag3Start + 1 && m_nMSLen > 0))
				{
					nStartChar--;
					nEndChar = nStartChar + 1;
				}
				SetSel(nStartChar, nStartChar);
			}
		}
	}
}

void CMyTimeEdit::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	int nStartChar;
	int nEndChar;
	
	GetSel(nStartChar, nEndChar);
	nEndChar = nStartChar;

	CString str;
	GetWindowText(str);
	
	if ( nChar==VK_DELETE )
	{
		if (nStartChar == m_nFlag1Start || nStartChar == m_nFlag2Start || (nStartChar == m_nFlag3Start && m_nMSLen > 0))
		{
			nStartChar++;
			nEndChar = nStartChar + 1;
		}
		if (nStartChar >= 0 && nStartChar < m_nLen)
		{
			str.Delete(nStartChar, 1);
			str.Insert(nStartChar, '0');
			SetWindowText(str);
			nStartChar++;
			nEndChar = nStartChar + 1;
			if (nStartChar == m_nFlag1Start || nStartChar == m_nFlag2Start || (nStartChar == m_nFlag3Start && m_nMSLen > 0))
			{
				nStartChar++;
				nEndChar = nStartChar + 1;
			}
			SetSel(nStartChar, nStartChar);
		}
	}
	else
	{
		CEdit::OnKeyDown(nChar, nRepCnt, nFlags);
	}
}

void CMyTimeEdit::OnContextMenu(CWnd* pWnd, CPoint point)
{
	//CEdit::OnContextMenu(pWnd, point);//No right menu
}