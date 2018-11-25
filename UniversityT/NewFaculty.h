#pragma once

#include "NamedList.h"
#include "student.h"
// CNewFaculty dialog

class CNewFaculty : public CDialog
{
	DECLARE_DYNAMIC(CNewFaculty)

public:
	CNewFaculty(CWnd* pParent = NULL);   // standard constructor
	virtual ~CNewFaculty();

// Dialog Data
	CString m_Name;
	CString Title;
    CString m_SelectedGroupName;
    NamedList<NamedList<Student>> *faculty;
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DLG_NEW_FACULTY };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
	afx_msg void OnOK();
};
