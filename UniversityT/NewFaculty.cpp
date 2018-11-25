// NewFaculty.cpp : implementation file
//

#include "stdafx.h"
#include "UniversityT.h"
#include "NewFaculty.h"
#include "afxdialogex.h"

#include "const.h"
// CNewFaculty dialog

IMPLEMENT_DYNAMIC(CNewFaculty, CDialog)

CNewFaculty::CNewFaculty(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_DLG_NEW_FACULTY, pParent)
{

}

CNewFaculty::~CNewFaculty()
{
}

void CNewFaculty::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_NEW_NAME, m_Name);

	
}


BEGIN_MESSAGE_MAP(CNewFaculty, CDialog)
	ON_BN_CLICKED(IDOK, &CNewFaculty::OnBnClickedOk)
END_MESSAGE_MAP()


// CNewFaculty message handlers


BOOL CNewFaculty::OnInitDialog()
{
	CDialog::OnInitDialog();

	CString OutTitle = __TEXT("Input Name of ") + Title;
	SetWindowText((LPCTSTR)OutTitle);
	UpdateData(FALSE);

	
	CWnd *Wnd = this->GetDlgItem(IDC_EDIT_NEW_NAME);
	Wnd->SetFocus();
	((CEdit*)(Wnd))->SetSel(0, m_Name.GetLength());

    m_SelectedGroupName = m_Name;
	
	return FALSE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}


void CNewFaculty::OnBnClickedOk()
{
	UpdateData(TRUE);
	m_Name.TrimLeft();
	m_Name.TrimRight();
    NamedList<Student> group(m_Name.GetBuffer());
    if (m_Name != __TEXT(""))
    {
        if (!faculty->isEmpty() && m_Name == m_SelectedGroupName || faculty->found(group))
        {
            MessageBox(_T("Such a group already exists!"), _T("Error"), MB_ICONERROR);

            CWnd *Wnd = GetDlgItem(IDC_EDIT_NEW_NAME);

            Wnd->SetFocus();
            ((CEdit*)(Wnd))->SetSel(0, m_Name.GetLength());
            return;
        }
        CDialog::OnOK();
    }
	else
		this->MessageBox(__TEXT("You must not enter empty string!"), __TEXT("Error"), MB_OK | MB_ICONSTOP);
}

void CNewFaculty::OnOK()
{
	
}