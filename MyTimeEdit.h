#if !defined(AFX_MYTIMEEDIT_H__C213AE0F_0655_4194_9610_62F2601D7C41__INCLUDED_)
#define AFX_MYTIMEEDIT_H__C213AE0F_0655_4194_9610_62F2601D7C41__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MyTimeEdit.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMyTimeEdit window

class CMyTimeEdit : public CEdit
{
	// Construction
public:
	CMyTimeEdit();
	
	// Attributes
public:
	
	// Operations
public:
	BOOL MySubclassDlgItem(UINT nID, CWnd* pParent);
	BOOL Init(DWORD nTime, BYTE nHourLen, BYTE nMSLen);
	int GetTime();
	int GetHour();
	int GetMin();
	int GetSec();
	int GetMS();
	
	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyTimeEdit)
	//}}AFX_VIRTUAL
	
	// Implementation
public:
	virtual ~CMyTimeEdit();
	
	// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
private:
	int m_nValueMode;
public:
	afx_msg void OnContextMenu(CWnd* /*pWnd*/, CPoint /*point*/);
	
private:
	BOOL m_bSubClass;
	
	BYTE m_nLen;
	BYTE m_HourLen;
	BYTE m_nMinLen;
	BYTE m_nSecLen;
	BYTE m_nMSLen;
	
	BYTE m_HourStart;
	BYTE m_nMinStart;
	BYTE m_nSecStart;
	BYTE m_nMSStart;
	
	BYTE m_nFlag1Start;
	BYTE m_nFlag2Start;
	BYTE m_nFlag3Start;
	
	int GetMul(int n);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYTIMEEDIT_H__C213AE0F_0655_4194_9610_62F2601D7C41__INCLUDED_)
