// InputStudInfo.cpp : implementation file
//

#include "stdafx.h"
#include "UniversityT.h"
#include "InputStudInfo.h"
#include "afxdialogex.h"
#include "const.h"

// InputStudInfo dialog

IMPLEMENT_DYNAMIC(InputStudInfo, CDialogEx)

InputStudInfo::InputStudInfo(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DLG_STUDENT_INFO, pParent)
{

}

InputStudInfo::~InputStudInfo()
{
}

void InputStudInfo::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CHOOSE_GROUP, groupsComboBox);
	DDX_Text(pDX, IDC_EDIT_SURNAME, surname);
	DDX_Text(pDX, IDC_EDIT_PATRONAME, patronymic);
	DDX_Text(pDX, IDC_EDIT_NAME, name);
	DDX_Text(pDX, IDC_EDIT_BIRTH, birth);
	DDV_MinMaxUInt(pDX, birth, 1900, 2100);
	DDX_Text(pDX, IDC_EDIT_MARK, mark);
	DDV_MinMaxFloat(pDX, mark, 0.f, 5.f);
}


BOOL InputStudInfo::OnInitDialog()
{

	if (changeFlag == ADD)
	{
		S = &workStud;
		isModify = true;
	}

	CDialogEx::OnInitDialog();

	CString str;

	for (int i = 0; i < groupList->GetCount(); i++) {
		groupList->GetText(i, str);
		groupsComboBox.AddString((LPCTSTR)str);
	}

	int index = groupList->GetCurSel();
	groupsComboBox.SetCurSel((index != LB_ERR) ? index : 0);

	if (changeFlag != ADD)
	{
		workStud = *S;
		setStudInfo();
		isModify = false;
		GetDlgItem(IDNEXT)->EnableWindow(FALSE);
		SetDefID(IDOK);

		UpdateData(FALSE);
	}

	SetActiveSurName();
	isNextActivated = false;

	return false;

}

BEGIN_MESSAGE_MAP(InputStudInfo, CDialogEx)
	ON_BN_CLICKED(IDOK, &InputStudInfo::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &InputStudInfo::OnBnClickedCancel)
	ON_BN_CLICKED(IDNEXT, &InputStudInfo::OnBnClickedNext)
	ON_CBN_SELCHANGE(IDC_CHOOSE_GROUP, &InputStudInfo::OnCbnSelchangeChooseGroup)
END_MESSAGE_MAP()



void InputStudInfo::SetActiveSurName()
{
	CWnd *Wnd = GetDlgItem(IDC_EDIT_SURNAME);

	Wnd->SetFocus();
	((CEdit*)(Wnd))->SetSel(0, surname.GetLength());
}

void InputStudInfo::SetActiveName()
{
    CWnd *Wnd = GetDlgItem(IDC_EDIT_NAME);

    Wnd->SetFocus();
    ((CEdit*)(Wnd))->SetSel(0, name.GetLength());
}
// InputStudInfo message handlers


bool InputStudInfo::CheckConstr()
{
	return name.GetLength() > 0 && surname.GetLength() > 0;
}

void InputStudInfo::TrimAll(CString &Str)
{
	Str.TrimLeft();
	Str.TrimRight();
}

bool InputStudInfo::AddStud()
{
	TrimAll(surname);
	TrimAll(name);
	TrimAll(patronymic);
	
	UpdateData(FALSE);

	if (CheckConstr())
	{
		int indexGroup = groupsComboBox.GetCurSel();
		groupAddStud = facultyAddStud->getElemWithID(indexGroup);
		if (changeFlag == ADD) {

			setStudInfo();
			
            if (groupAddStud->found(*S))
            {
                MessageBox(__TEXT("Such a student already exists"), __TEXT("Error"), MB_OK | MB_ICONSTOP);
                isModify = true;
                return false;
            }

			(groupAddStud->isEmpty()) ? groupAddStud->addToBegin(*S) : groupAddStud->sort_elem(*S);
			groupList->SetCurSel(indexGroup);
		}
		
		return true;
	}
	isModify = true;
	MessageBox(__TEXT("Surname or Name is empty"), __TEXT("Error"), MB_OK | MB_ICONSTOP);
    (surname.GetLength() > 0) ? SetActiveName() : SetActiveSurName();
	return false;

}

void InputStudInfo::OnBnClickedOk()
{
	if (UpdateData() == TRUE && AddStud())
		EndDialog(IDOK);
}

void InputStudInfo::setStudInfo()
{
	S->setSurname(surname.GetBuffer());
	S->setName(name.GetBuffer());
	S->setLastname(patronymic.GetBuffer());
	S->setAverMark(mark);
	S->setYearOfBirht(birth);
}


void InputStudInfo::OnBnClickedCancel()
{
	if (isModify)
		*S = workStud;

	(isNextActivated) ? CDialogEx::OnOK() : CDialogEx::OnCancel();
}


void InputStudInfo::OnBnClickedNext()
{
	if (UpdateData() == TRUE)
	{
		AddStud();
		isNextActivated = true;
	}
}


void InputStudInfo::OnCbnSelchangeChooseGroup()
{
	SetActiveSurName();
}
