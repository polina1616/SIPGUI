// ChooseLB.cpp: файл реализации
//

#include "stdafx.h"
#include "UniversityT.h"
#include "ChooseLB.h"
#include "afxdialogex.h"


// диалоговое окно ChooseLB

IMPLEMENT_DYNAMIC(ChooseLB, CDialogEx)

ChooseLB::ChooseLB(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DLG_CHOOSE_LIST_SEL, pParent)
{
    selectedLB = LB_ERR;
}

ChooseLB::~ChooseLB()
{
}

void ChooseLB::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(ChooseLB, CDialogEx)
    ON_BN_CLICKED(ID_CHOOSE_GROUP_BUTTON, &ChooseLB::OnBnClickedChooseGroupButton)
    ON_BN_CLICKED(ID_CHOOSE_STUDENT_BUTTON, &ChooseLB::OnBnClickedChooseStudentButton)
END_MESSAGE_MAP()


// обработчики сообщений ChooseLB


void ChooseLB::OnBnClickedChooseGroupButton()
{
    selectedLB = GROUP;
    CDialog::EndDialog(IDOK);
}


void ChooseLB::OnBnClickedChooseStudentButton()
{
    selectedLB = STUDENT;
    CDialog::EndDialog(IDOK);
}
