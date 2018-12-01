#pragma once

#define GROUP 5
#define STUDENT 6

// диалоговое окно ChooseLB

class ChooseLB : public CDialogEx
{
	DECLARE_DYNAMIC(ChooseLB)

public:
	ChooseLB(CWnd* pParent = NULL);   // стандартный конструктор
	virtual ~ChooseLB();

    int selectedLB;
// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DLG_CHOOSE_LIST_SEL };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV

	DECLARE_MESSAGE_MAP()
public:
    afx_msg void OnBnClickedChooseGroupButton();
    afx_msg void OnBnClickedChooseStudentButton();
};
