
// UniversityTDlg.cpp : файл реализации
//

#include "stdafx.h"
#include "UniversityT.h"
#include "UniversityTDlg.h"
#include "afxdialogex.h"

#include "const.h"

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
    DDX_Control(pDX, IDC_EDIT_GROUP, m_SearchGroupEdit);
    DDX_Control(pDX, IDC_EDIT_STUDENTS, m_SearchStudentEdit);
    DDX_Text(pDX, IDC_EDIT_STUDENTS, m_StudName);
    DDX_Text(pDX, IDC_EDIT_GROUP, m_GroupName);
    DDV_MaxChars(pDX, m_GroupName, 7);
}

BEGIN_MESSAGE_MAP(CUniDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_ADD_STUDENT, &CUniDlg::OnBnClickedAddStudent)
	ON_BN_CLICKED(IDC_CREATE_FACULTY, &CUniDlg::OnBnClickedCreateFaculty)
	ON_BN_CLICKED(IDC_ADD_GROUP, &CUniDlg::OnBnClickedAddGroup)
	ON_BN_CLICKED(IDC_GET_FACULTY, &CUniDlg::OnBnClickedGetFaculty)
	ON_COMMAND(ID_FILE_EXIT, &CUniDlg::OnFileExit)
	ON_BN_CLICKED(IDC_exit, &CUniDlg::OnBnClickedexit)
	ON_BN_CLICKED(IDC_DEL_FACULTY, &CUniDlg::OnBnClickedDelFaculty)
	ON_BN_CLICKED(IDC_CHG_FACULTY, &CUniDlg::OnBnClickedChgFaculty)
	ON_BN_CLICKED(IDC_DEL_ALL_GROUPS, &CUniDlg::OnBnClickedDelAllGroups)
	ON_BN_CLICKED(IDC_DEL_ALL_STUD, &CUniDlg::OnBnClickedDelAllStud)
    ON_LBN_SELCHANGE(IDC_LIST_GROUPS, &CUniDlg::OnLbnSelchangeListGroups)
    ON_LBN_SELCHANGE(IDC_LIST_STUDENTS, &CUniDlg::OnLbnSelchangeListStudents)
    ON_BN_CLICKED(IDC_DEL_SELECTED, &CUniDlg::OnBnClickedDelSelected)
    ON_BN_CLICKED(IDC_CHG_SELECTED, &CUniDlg::OnBnClickedChgSelected)
    ON_EN_CHANGE(IDC_EDIT_GROUP, &CUniDlg::OnEnChangeEditGroup)
    ON_EN_CHANGE(IDC_EDIT_STUDENTS, &CUniDlg::OnEnChangeEditStudents)
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


	CWnd *hWnd = GetDlgItem(IDD_DLG_NEW_FACULTY);
	if (hWnd != NULL)
		hWnd->SetFocus();

	inputStudInfo.groupList = &m_GroupsList;
	inputStudInfo.facultyAddStud = &faculty;
	S = NULL;
	inputStudInfo.S = S;
    addFaculty.faculty = &faculty;
    addFaculty.m_SelectedGroupName = _T("");

	m_GroupsList.EnableWindow(false);
	m_StudentsList.EnableWindow(false);
	m_StudInfoList.EnableWindow(false);
	

	TEXTMETRIC tm;
	CDC *pDC = m_StudentsList.GetDC();
	CFont *pOldFont = pDC->SelectObject(m_StudentsList.GetFont());
	pDC->GetTextMetrics(&tm);
	pDC->SelectObject(pOldFont);
	m_StudentsList.ReleaseDC(pDC);
	FontAveChar = tm.tmAveCharWidth;
    OldGroupSelect = OldStudSelect = LB_ERR;

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
	if (inputStudInfo.DoModal() == IDOK && inputStudInfo.workStud.getSurname().length() > 0) {
		OutStud();
        OutStudInfo(inputStudInfo.workStud);
        OldStudSelect = m_StudentsList.GetCurSel();
	}
    SetFocus();
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

        GetDlgItem(IDC_ADD_GROUP)->SetFocus();
        SetDefID(IDC_ADD_GROUP);
	}
}


void CUniDlg::OnBnClickedAddGroup()
{
	// Open modal window to edit group
	addFaculty.Title = __TEXT("Group");
    addFaculty.m_SelectedGroupName = _T("");
	if (addFaculty.DoModal() == IDOK) 
    {
		group.del_all();
		group.setListName(addFaculty.m_Name.GetBuffer());
		
		(faculty.isEmpty()) ? faculty.addToBegin(group) : faculty.sort_elem(group);

		int index = m_GroupsList.AddString(group.getListName().c_str());

		CorrectListHScrlPart(m_GroupsList, MaxExtListGroup, index);
        m_GroupsList.EnableWindow(true);

        if (m_GroupsList.GetCurSel() == LB_ERR)
            SetGroupActions(TRUE);

        OldGroupSelect = m_GroupsList.GetCurSel();

        if (m_GroupsList.GetCount() == 1)
        {
            m_GroupsList.SetCurSel(index); 
        }
	}
    SetFocus();
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

	group.del_all();
	group = *faculty.getElemWithID(indexGroup);

	if (SetStudActions(!group))
	{
		group.setCurrToHead();
		S = &group.getCurrInf();
		Student *headStud = S;
		OutStr(*S);
		++group;
		
		for (S = &group.getCurrInf(); S != headStud; ++group, S = &group.getCurrInf())
		{
			OutStr(*S);	
		}
		
        m_StudentsList.EnableWindow(true);
		CorrectListHScrl(m_StudentsList);
	}
}

void CUniDlg::OutStr(Student &S)
{
	CString surname = S.getSurname().c_str();
	CString name = S.getName().c_str();
	CString lastname = S.getLastname().c_str();
	CString res = surname + _T(' ') + name[0] + _T('.') + lastname[0] + _T('.');

	int index = m_StudentsList.AddString(res);

    if (S == inputStudInfo.workStud)
    {
        m_StudentsList.SetCurSel(index);
    }
}


void CUniDlg::OutStudInfo(Student &S)
{
	CString Buf;

	DelStudInfoList();

	Buf.Format(__TEXT("Surname             : %s"), S.getSurname().c_str());
	m_StudInfoList.AddString((LPCTSTR)Buf);

	Buf.Format(__TEXT("Name                  : %s"), S.getName().c_str());
	m_StudInfoList.AddString((LPCTSTR)Buf);
    
	Buf.Format(__TEXT("PatroName        : %s"), S.getLastname().c_str());
	m_StudInfoList.AddString((LPCTSTR)Buf);

	Buf.Format(__TEXT("Birth Year            : %i"), S.getYearOfBirht());
	m_StudInfoList.AddString((LPCTSTR)Buf);

	Buf.Format(__TEXT("Average Mark   : %4.2f"), S.getAverMark());
	m_StudInfoList.AddString((LPCTSTR)Buf);

    m_StudInfoList.EnableWindow(true);
	CorrectListHScrl(m_StudInfoList);
}

void CUniDlg::DelStudentList()
{
	DelStudInfoList();
	m_StudentsList.ResetContent();
	CorrectListHScrl(m_StudentsList);
	SetSelectedActions();
	m_StudentsList.EnableWindow(false);
    OldStudSelect = LB_ERR;
}

void CUniDlg::DelStudInfoList()
{
	m_StudInfoList.ResetContent();
	CorrectListHScrl(m_StudInfoList);
    m_StudInfoList.EnableWindow(false);
}

void CUniDlg::DelAllGroups()
{
	faculty.del_all();
	group.del_all();
	m_GroupsList.ResetContent();
    DelStudentList();
	CorrectListHScrl(m_GroupsList);
	MaxExtListGroup = 0;
	MaxExtListStud = 0;
	GetDlgItem(IDC_DEL_ALL_GROUPS)->EnableWindow(false);
    m_SearchGroupEdit.SetWindowTextW(_T(""));
    m_SearchStudentEdit.SetWindowTextW(_T(""));
    SetFocus();
}

void CUniDlg::OnBnClickedDelAllStud()
{
	int indexGroup = m_GroupsList.GetCurSel();
	
	faculty.getElemWithID(indexGroup)->del_all();
	group.del_all();

	DelStudentList();
	SetStudActions(false);
    m_SearchStudentEdit.SetWindowTextW(_T(""));
	UpdateData(FALSE);
}

void CUniDlg::actionOnSelectedItem(function<void(CUniDlg&, int)> actionOnGroup, function<void(CUniDlg&, int, int)> actionOnStudent)
{
    int indexOfGroup = m_GroupsList.GetCurSel(),
        indexOfStudent = m_StudentsList.GetCurSel();


    if (indexOfGroup != LB_ERR && indexOfStudent != LB_ERR)
    {
        if (ChooseListBox.DoModal() == IDOK)
        {
            if (ChooseListBox.selectedLB == GROUP)
            {
                actionOnGroup(*this, indexOfGroup);
            }
            else
            {
                actionOnStudent(*this, indexOfGroup, indexOfStudent);
            }
        }
        else
        {
            SetFocus();
            return;
        }
    }
    else if (indexOfGroup != LB_ERR)
    {
        actionOnGroup(*this, indexOfGroup);
    }
    else
    {
        actionOnStudent(*this, indexOfGroup, indexOfStudent);
    }
}

void CUniDlg::delGroup(int groupIndex)
{
    group = *faculty.getElemWithID(groupIndex);

    faculty.del_Inf(group);
    faculty.sort();

    DelStudentList();

    CorrectListHScrlDel(m_GroupsList, MaxExtListGroup, groupIndex);
    
    OldGroupSelect = LB_ERR;

    int sizeOfListGroups = m_GroupsList.GetCount();
    if (sizeOfListGroups == 0)
    {
        SetGroupActions(false);
        SetStudActions(false);
        m_SearchGroupEdit.SetWindowTextW(_T(""));
        m_SearchStudentEdit.SetWindowTextW(_T(""));
    }
    else
    {
        GetDlgItem(IDC_ADD_STUDENT)->EnableWindow(true);
        (sizeOfListGroups - 1 >= groupIndex) ? m_GroupsList.SetCurSel(groupIndex) : m_GroupsList.SetCurSel(groupIndex - 1);

        OnLbnSelchangeListGroups();
    }

    SetFocus();
}

void CUniDlg::delStudent(int groupIndex, int studIndex)
{
    NamedList<Student> *gr = faculty.getElemWithID(groupIndex);
    S = gr->getElemWithID(studIndex);

    gr->del_Inf(*S);
    S = NULL;

    DelStudInfoList();

    CorrectListHScrlDel(m_StudentsList, MaxExtListStud, studIndex);

    OldStudSelect = LB_ERR;

    int sizeOfListStudents = m_StudentsList.GetCount();

    if (sizeOfListStudents == 0)
    {
        DelStudentList();
        SetStudActions(false);
        m_SearchStudentEdit.SetWindowTextW(_T(""));
    }
    else
    {
        (sizeOfListStudents - 1 >= studIndex) ? m_StudentsList.SetCurSel(studIndex) : m_StudentsList.SetCurSel(studIndex - 1);
        OnLbnSelchangeListStudents();
    }
}

void CUniDlg::changeGroup(int index)
{
    m_GroupsList.GetText(index, addFaculty.m_Name);
    addFaculty.Title = _T("Group");
    if (addFaculty.DoModal() == IDOK)
    {
        CString name = addFaculty.m_Name;
        if (name != addFaculty.m_SelectedGroupName)
        {
            CorrectListHScrlDel(m_GroupsList, MaxExtListGroup, index);

            faculty.getElemWithID(index)->setListName(name.GetBuffer());

            faculty.sort();

            CorrectListHScrlPart(m_GroupsList, MaxExtListGroup, index = m_GroupsList.AddString(name));
            m_GroupsList.SetCurSel(index);
        }
    }
}

void CUniDlg::changeStudent(int indexGroup, int indexStud)
{
    inputStudInfo.changeFlag = CHANGE;
    S = faculty.getElemWithID(indexGroup)->getElemWithID(indexStud);
    inputStudInfo.S = S;
    if (inputStudInfo.DoModal() == IDOK)
    {
        CString surname = S->getSurname().c_str();
        CString name = S->getName().c_str();
        CString patronymic = S->getLastname().c_str();

        CString outStr = surname
            + _T(' ') + name.GetAt(0)
            + _T('.') + patronymic.GetAt(0) + _T('.');

        CorrectListHScrlDel(m_StudentsList, MaxExtListStud, indexStud);
        indexStud = m_StudentsList.AddString(outStr);
        CorrectListHScrlPart(m_StudentsList, MaxExtListStud, indexStud);

        m_StudentsList.SetCurSel(indexStud);
        OldStudSelect = LB_ERR;

        OutStudInfo(*S);
    }
}

void CUniDlg::OnBnClickedDelSelected()
{
    function<void(CUniDlg&, int)> groupAct = &CUniDlg::delGroup;
    function<void(CUniDlg&, int, int)> studentAct = &CUniDlg::delStudent;

    actionOnSelectedItem(groupAct, studentAct);
    SetFocus();
}

void CUniDlg::OnBnClickedChgSelected()
{
    function<void(CUniDlg&, int)> groupAct = &CUniDlg::changeGroup;
    function<void(CUniDlg&, int, int)> studentAct = &CUniDlg::changeStudent;

    actionOnSelectedItem(groupAct, studentAct);
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
        IDC_EDIT_GROUP,
		IDC_DEL_SELECTED,
		IDC_DEL_ALL_GROUPS,
		IDC_ADD_STUDENT,
        IDC_LIST_GROUPS
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

	SetButtonState(wID, _LEN(wID, WORD), m_StudentsList.GetCurSel() != LB_ERR || m_GroupsList.GetCurSel() != LB_ERR);

}

void CUniDlg::DisableFaculty()
{
    SetGroupActions(false);
	SetStudActions(false);
	SetFacultyActions(false);
	SetAddFAction(true);
}

void CUniDlg::OnLbnSelchangeListGroups()
{
    int indexOfGroup = m_GroupsList.GetCurSel();

    if (indexOfGroup != LB_ERR && indexOfGroup != OldGroupSelect)
    {
        DelStudentList();
        SetStudActions(false);

        if (!faculty.getElemWithID(indexOfGroup)->isEmpty())
        {
            m_StudentsList.EnableWindow(true);
            OutStud();
            m_StudentsList.SetCurSel(LB_ERR);
            SetStudActions(true);
            SetSelectedActions();
        }

        OldGroupSelect = indexOfGroup;
        OldStudSelect = LB_ERR;
    }
}

void CUniDlg::OnLbnSelchangeListStudents()
{
    int indexOfStudent = m_StudentsList.GetCurSel();

    if (indexOfStudent != LB_ERR && indexOfStudent != OldStudSelect)
    {
        group = *faculty.getElemWithID(m_GroupsList.GetCurSel());
        DelStudInfoList();
        OutStudInfo(*group.getElemWithID(indexOfStudent));
        OldStudSelect = indexOfStudent;
    }
}

/*************************************************/

void CUniDlg::OnBnClickedDelFaculty()
{
	DelAllGroups();
	DisableFaculty();
}


void CUniDlg::OnBnClickedChgFaculty()
{
	OnBnClickedCreateFaculty();
}


void CUniDlg::OnBnClickedDelAllGroups()
{
	DelAllGroups();
	SetGroupActions(false);
	SetAddFAction(false);
	SetStudActions(false);
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


void CUniDlg::OnEnChangeEditGroup()
{
    UpdateData(TRUE);

    int searchResultIndex = m_GroupsList.FindString(LB_ERR, m_GroupName);

    if (searchResultIndex != OldGroupSelect)
    {
        DelStudentList();
        SetStudActions(false);
    }
    else
    {
        m_StudentsList.EnableWindow(true);
    }

    m_GroupsList.SetCurSel(searchResultIndex);
    OnLbnSelchangeListGroups();

    OldGroupSelect = searchResultIndex;
}


void CUniDlg::OnEnChangeEditStudents()
{
    UpdateData(TRUE);

    int searchResultIndex = m_StudentsList.FindString(LB_ERR, m_StudName);

    if (searchResultIndex != OldStudSelect)
    {
        DelStudInfoList();
    }
    else
    {
        m_StudInfoList.EnableWindow(true);
    }

    m_StudentsList.SetCurSel(searchResultIndex);
    OnLbnSelchangeListStudents();

    OldStudSelect = searchResultIndex;
}
