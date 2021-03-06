
// UniversityTDlg.h : файл заголовка
//

#pragma once

#include "namedList.h"
#include "Student.h"
#include "NewFaculty.h"
#include "InputStudInfo.h"
#include "ChooseLB.h"
#include <functional>

using std::function;

// диалоговое окно CUniDlg
class CUniDlg : public CDialogEx
{
// Создание
public:
	CUniDlg(CWnd* pParent = NULL);	// стандартный конструктор
	CMenu m_menu;


// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_UNIVERSITYT_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// поддержка DDX/DDV


// Реализация
protected:
	HICON m_hIcon;

	CNewFaculty addFaculty;
	CListBox m_GroupsList;
	CListBox m_StudentsList;
	CListBox m_StudInfoList;
    CEdit m_SearchGroupEdit;
    CEdit m_SearchStudentEdit;

    CString m_GroupName;
    CString m_StudName;

	InputStudInfo  inputStudInfo;
    ChooseLB ChooseListBox;

	NamedList<NamedList<Student>> faculty;
	NamedList<Student> group;
	Student *S;

	int FontAveChar, MaxExtListStud, MaxExtListGroup, OldGroupSelect, OldStudSelect;

	void OutStudInfo(Student &S);
	void OutStud();
	void DelStudentList();
	void DelStudInfoList();
	void CorrectListHScrl(CListBox &ListBox);
	void CorrectListHScrlPart(CListBox &ListBox, int &MaxExtCx, int Index);
	void CorrectListHScrlDel(CListBox &ListBox, int &MaxExtCx, int Index);
	void SetSelectedActions();
	void OutStr(Student &S);
	void DelAllGroups();
    void actionOnSelectedItem(function<void(CUniDlg&, int)>, function<void(CUniDlg&, int, int)>);
    void delGroup(int groupIndex);
    void delStudent(int groupIndex, int studIndex);
    void changeGroup(int index);
    void changeStudent(int indexGroup, int indexStud = 0);

	// Созданные функции схемы сообщений
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedAddStudent();
	afx_msg void OnBnClickedCreateFaculty();
	afx_msg void OnBnClickedAddGroup();
	afx_msg void OnBnClickedGetFaculty();
	afx_msg void OnHelpAbout();
	afx_msg void OnFileExit();
	afx_msg void OnBnClickedexit();
	/*disable buttons*/
	afx_msg void SetButtonState(WORD wID[], WORD len, bool State);
	afx_msg void SetAddFAction(bool State);
	afx_msg bool SetStudActions(bool State);
	afx_msg void SetGroupActions(bool State);
	afx_msg void SetFacultyActions(bool State);
	afx_msg void DisableFaculty();
	afx_msg void OnBnClickedDelFaculty();
	afx_msg void OnBnClickedChgFaculty();
	afx_msg void OnBnClickedDelAllGroups();
	afx_msg void OnBnClickedDelAllStud();
    afx_msg void OnLbnSelchangeListGroups();
    afx_msg void OnLbnSelchangeListStudents();
    afx_msg void OnBnClickedDelSelected();
    afx_msg void OnBnClickedChgSelected();
    afx_msg void OnEnChangeEditGroup();
    afx_msg void OnEnChangeEditStudents();
};
