
// UniversityTDlg.cpp : файл реализации
//

#include "stdafx.h"
#include "UniversityT.h"
#include "UniversityTDlg.h"
#include "afxdialogex.h"

#include "const.h"
#include "NewFaculty.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// Диалоговое окно CAboutDlg используется для описания сведений о приложении

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV

// Реализация
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// диалоговое окно CUniDlg



CUniDlg::CUniDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_UNIVERSITYT_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CUniDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_GROUPS, m_GroupsList);
	DDX_Control(pDX, IDC_LIST_STUDENTS, m_StudentsList);
	DDX_Control(pDX, IDC_LIST_INFO, m_StudInfoList);
}

BEGIN_MESSAGE_MAP(CUniDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_ADD_STUDENT, &CUniDlg::OnBnClickedAddStudent)
	ON_BN_CLICKED(IDC_ADD_STUDENT, &CUniDlg::OnBnClickedAddStudent)
	ON_BN_CLICKED(IDC_CREATE_FACULTY, &CUniDlg::OnBnClickedCreateFaculty)
	ON_BN_CLICKED(IDC_ADD_GROUP, &CUniDlg::OnBnClickedAddGroup)
	ON_BN_CLICKED(IDC_GET_FACULTY, &CUniDlg::OnBnClickedGetFaculty)
	ON_COMMAND(ID_HELP_ABOUT, &CUniDlg::OnHelpAbout)
	ON_COMMAND(ID_FILE_EXIT, &CUniDlg::OnFileExit)
	ON_BN_CLICKED(IDC_exit, &CUniDlg::OnBnClickedexit)
	ON_BN_CLICKED(IDC_DEL_FACULTY, &CUniDlg::OnBnClickedDelFaculty)
	ON_BN_CLICKED(IDC_CHG_FACULTY, &CUniDlg::OnBnClickedChgFaculty)
	ON_BN_CLICKED(IDC_DEL_ALL_GROUPS, &CUniDlg::OnBnClickedDelAllGroups)
END_MESSAGE_MAP()


// обработчики сообщений CUniDlg

BOOL CUniDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Добавление пункта "О программе..." в системное меню.

	// IDM_ABOUTBOX должен быть в пределах системной команды.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Задает значок для этого диалогового окна.  Среда делает это автоматически,
	//  если главное окно приложения не является диалоговым
	SetIcon(m_hIcon, TRUE);			// Крупный значок
	SetIcon(m_hIcon, FALSE);		// Мелкий значок

	// TODO: добавьте дополнительную инициализацию

	if (!m_menu.LoadMenu(IDR_MENU1))
		AfxThrowResourceException();
	SetMenu(&m_menu);

	CWnd *hWnd = GetDlgItem(IDD_DLG_NEW_FACULTY);
	if (hWnd != NULL)
		hWnd->SetFocus();

	inputStudInfo.groupList = &m_GroupsList;
	inputStudInfo.facultyAddStud = &faculty;
	S = NULL;
	inputStudInfo.S = S;

	m_GroupsList.EnableWindow(false);
	m_StudentsList.EnableWindow(false);
	m_StudInfoList.EnableWindow(false);


	return TRUE;  // возврат значения TRUE, если фокус не передан элементу управления
}

void CUniDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// При добавлении кнопки свертывания в диалоговое окно нужно воспользоваться приведенным ниже кодом,
//  чтобы нарисовать значок.  Для приложений MFC, использующих модель документов или представлений,
//  это автоматически выполняется рабочей областью.

void CUniDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // контекст устройства для рисования

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Выравнивание значка по центру клиентского прямоугольника
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Нарисуйте значок
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// Система вызывает эту функцию для получения отображения курсора при перемещении
//  свернутого окна.
HCURSOR CUniDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CUniDlg::OnBnClickedAddStudent()
{
	inputStudInfo.changeFlag = ADD;
	if (inputStudInfo.DoModal() == IDOK) {
		m_StudentsList.EnableWindow(true);
	}

	OutStud();
}


void CUniDlg::OnBnClickedCreateFaculty()
{
	// Open modal window to edit faculty
	addFaculty.Title = __TEXT("Faculty");
	if (addFaculty.DoModal() == IDOK)
	{
		SetFacultyActions(TRUE);
		faculty.setListName(addFaculty.m_Name.GetBuffer());
		SetFacultyActions(true);
		SetAddFAction(false);
	}
}


void CUniDlg::OnBnClickedAddGroup()
{
	// Open modal window to edit group
	addFaculty.Title = __TEXT("Group");
	if (addFaculty.DoModal() == IDOK) {
		SetGroupActions(TRUE);
		m_GroupsList.EnableWindow(true);
		group.setListName(addFaculty.m_Name.GetBuffer());
		
		(faculty.isEmpty()) ? faculty.addToBegin(group) : faculty.sort_elem(group);

		int index = m_GroupsList.AddString(group.getListName().c_str());
		CorrectListHScrlPart(m_GroupsList, MaxExtListGroup, index);

	}
}


void CUniDlg::OnBnClickedGetFaculty()
{
	// Open GerFaculty MessageBox
	MessageBox(faculty.getListName().c_str(), __TEXT("Faculty name"));
}


void CUniDlg::OnHelpAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}


//EXIT
/*************************************************/
void CUniDlg::OnFileExit()
{
	OnOK();
}


void CUniDlg::OnBnClickedexit()
{
	OnOK();
}
/*************************************************/

void CUniDlg::OutStud()
{
	DelStudentList();
	int indexGroup = m_GroupsList.GetCurSel();
	
	group = *faculty.getElemWithID(indexGroup);

	if (SetStudActions(!group))
	{
		group.setCurrToHead();
		S = &group.getCurrInf();
		Student *headStud = S;
		OutStr(*S);
		++group;
		for (S = &group.getCurrInf(); S != headStud; OutStr(*S), ++group, S = &group.getCurrInf());
		//group.GetHeadTailInf(S);
		//OutStudInfo(*S);
		OldStudSelect = LB_ERR;
	}
}

void CUniDlg::OutStr(Student &S)
{
	CString surname = S.getSurname().c_str();
	CString name = S.getSurname().c_str();
	CString lastname = S.getSurname().c_str();
	CString res = surname + _T(' ') + name[0] + _T('.') + lastname[0] + _T('.');
	CorrectListHScrlPart(m_StudentsList, MaxExtListStud, m_StudentsList.AddString(res));
}


/* CUniDlg::OutStudInfo(Student &S)
{
	CString Buf;

	DelStudInfoList();

	Buf.Format(__TEXT("Surname         : %s"), S.SName);
	m_ListStudInfo.AddString((LPCTSTR)Buf);s

	Buf.Format(__TEXT("Name             : %s"), S.Name);
	m_ListStudInfo.AddString((LPCTSTR)Buf);

	Buf.Format(__TEXT("PatroName      : %s"), S.PName);
	m_ListStudInfo.AddString((LPCTSTR)Buf);

	Buf.Format(__TEXT("Birth Year       : %i"), S.BY);
	m_ListStudInfo.AddString((LPCTSTR)Buf);

	Buf.Format(__TEXT("Average Mark : %4.2f"), S.AM);
	m_ListStudInfo.AddString((LPCTSTR)Buf);

	CorrectListHScrl(m_ListStudInfo);
}*/

void CUniDlg::DelStudentList()
{
	DelStudInfoList();
	m_StudentsList.ResetContent();
	CorrectListHScrl(m_StudentsList);
	SetSelectedActions();
	m_StudentsList.EnableWindow(false);
	GetDlgItem(IDC_ADD_STUDENT)->SetFocus();
}

void CUniDlg::DelStudInfoList()
{
	/*m_ListStudInfo.ResetContent();
	CorrectListHScrl(m_ListStudInfo);*/
}

//disable buttons
/*************************************************/
void CUniDlg::SetButtonState(WORD wID[], WORD len, bool State) //len - lenght of array wID[]
{
	for (WORD i = 0; i<len; i++)
		GetDlgItem(wID[i])->EnableWindow(State);
}

void CUniDlg::SetAddFAction(bool State)
{
	WORD wID[] = { IDC_CREATE_FACULTY };

	SetButtonState(wID, _LEN(wID, WORD), State);
}

bool CUniDlg::SetStudActions(bool State)
{
	WORD wID[] = { IDC_DEL_ALL_STUD,
		IDC_EDIT_STUDENTS,
		IDC_LIST_STUDENTS,
		IDC_LIST_INFO,
	};

	SetButtonState(wID, _LEN(wID, WORD), State);
	return State;
}

void CUniDlg::SetGroupActions(bool State)
{
	WORD wID[] = { IDC_CHG_SELECTED,
		IDC_DEL_SELECTED,
		IDC_DEL_ALL_GROUPS,
		IDC_ADD_STUDENT,
	};

	SetButtonState(wID, _LEN(wID, WORD), State);

	SetAddFAction(!State);
}

void CUniDlg::SetFacultyActions(bool State)
{
	WORD wID[] = { IDC_CHG_FACULTY,
		IDC_DEL_FACULTY,
		IDC_GET_FACULTY,
		IDC_ADD_GROUP,
	};

	SetButtonState(wID, _LEN(wID, WORD), State);

	SetAddFAction(!State);
}

void CUniDlg::SetSelectedActions()
{

	WORD wID[] = { IDC_DEL_SELECTED,
		IDC_CHG_SELECTED,
	};

	SetButtonState(wID, _LEN(wID, WORD), m_StudentsList.GetCurSel() != LB_ERR);

}

void CUniDlg::DisableFaculty()
{
	SetStudActions(false);
	SetFacultyActions(false);
	SetAddFAction(true);
}

/*************************************************/

void CUniDlg::OnBnClickedDelFaculty()
{
	faculty.del_all();
	m_GroupsList.ResetContent();
	DisableFaculty();
}


void CUniDlg::OnBnClickedChgFaculty()
{
	OnBnClickedCreateFaculty();
}


void CUniDlg::OnBnClickedDelAllGroups()
{
	faculty.del_all();
	m_GroupsList.ResetContent();
	SetGroupActions(false);
	SetAddFAction(false);
}

// -----------------------------------Horizontal Scroll for ListBox---------------------------------------------

void CUniDlg::CorrectListHScrl(CListBox &ListBox)
{
	int dx = 0;
	if (ListBox.GetCount() > 0)
	{
		CDC *pDC = ListBox.GetDC();
		CFont *pOldFont = pDC->SelectObject(ListBox.GetFont());
		CString str;
		CSize sz;

		for (int i = 0; i < ListBox.GetCount(); i++)
		{
			ListBox.GetText(i, str);
			sz = pDC->GetTextExtent(str);
			if (sz.cx > dx)
				dx = sz.cx;
		}
		pDC->SelectObject(pOldFont);
		ListBox.ReleaseDC(pDC);
		dx += FontAveChar;
	}
	ListBox.SetHorizontalExtent(dx);
}


void CUniDlg::CorrectListHScrlPart(CListBox &ListBox, int &MaxExtCx, int Index)
{
	bool IsModify = true;
	if (ListBox.GetCount() > 0)
	{
		CDC *pDC = ListBox.GetDC();
		CFont *pOldFont = pDC->SelectObject(ListBox.GetFont());
		CString str;
		CSize sz;

		ListBox.GetText(Index, str);
		sz = pDC->GetTextExtent(str);
		if ((IsModify = sz.cx + FontAveChar > MaxExtCx))
			MaxExtCx = sz.cx + FontAveChar;
		pDC->SelectObject(pOldFont);
		ListBox.ReleaseDC(pDC);
	}
	else
		MaxExtCx = 0;
	if (IsModify)
		ListBox.SetHorizontalExtent(MaxExtCx);
}


void CUniDlg::CorrectListHScrlDel(CListBox &ListBox, int &MaxExtCx, int Index)
{
	CDC *pDC = ListBox.GetDC();
	CFont *pOldFont = pDC->SelectObject(ListBox.GetFont());
	CString str;
	CSize sz;

	ListBox.GetText(Index, str);
	sz = pDC->GetTextExtent(str);
	ListBox.DeleteString(Index);
	if (sz.cx + FontAveChar == MaxExtCx)
	{
		MaxExtCx = 0;
		for (int i = 0; i < ListBox.GetCount(); i++)
		{
			ListBox.GetText(i, str);
			sz = pDC->GetTextExtent(str);
			if (sz.cx > MaxExtCx)
				MaxExtCx = sz.cx;
		}
		MaxExtCx += FontAveChar;
		ListBox.SetHorizontalExtent(MaxExtCx);
	}
	pDC->SelectObject(pOldFont);
	ListBox.ReleaseDC(pDC);
}