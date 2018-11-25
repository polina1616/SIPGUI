#pragma once

#include "Student.h"
#include "namedList.h"
// InputStudInfo dialog

class InputStudInfo : public CDialogEx
{
	DECLARE_DYNAMIC(InputStudInfo)

public:
	InputStudInfo(CWnd* pParent = NULL);   // standard constructor
	virtual ~InputStudInfo();

	CListBox *groupList;
	NamedList<NamedList<Student>> *facultyAddStud;
	NamedList<Student> *groupAddStud;

	Student *S;
	Student workStud;
	int changeFlag;
	

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DLG_STUDENT_INFO };
#endif

protected:

	CComboBox groupsComboBox;
	CString surname, name, patronymic;
	int birth;
	double mark;
	bool isModify;
	bool isNextActivated;

	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	void SetActiveSurName();
	bool CheckConstr();
	void TrimAll(CString &Str);
	bool AddStud();
	void setStudInfo();

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedNext();
	afx_msg void OnCbnSelchangeChooseGroup();
};
