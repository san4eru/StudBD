
// StudBDDlg.cpp: файл реализации
//

#include "pch.h"
#include "framework.h"
#include "StudBD.h"
#include "StudBDDlg.h"
#include "afxdialogex.h"

#include <fstream> 
#include <vector>

using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

int clk = 0;
struct Student
{
	CString Surname, 
			Name, 
			Patr,
			YearEnter,
			Kaf,
			Group,
			NumZ,
			Gender;
	
	COleDateTime DataBoth;
	
	bool flag;
}student[300];

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


// Диалоговое окно CStudBDDlg



CStudBDDlg::CStudBDDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_STUDBD_DIALOG, pParent)
	, DataBorth(COleDateTime::GetCurrentTime())
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CStudBDDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_MonthCalCtrl(pDX, IDC_MONTHCALENDAR_DataBoth, DataBorth);
	DDX_Control(pDX, IDC_LIST, ListStud);
}

BEGIN_MESSAGE_MAP(CStudBDDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_Refresh, &CStudBDDlg::OnBnClickedButtonRefresh)
	ON_BN_CLICKED(IDC_BUTTON_ReadF, &CStudBDDlg::OnBnClickedButtonReadf)
	ON_BN_CLICKED(IDC_BUTTON_New, &CStudBDDlg::OnBnClickedButtonNew)
	ON_BN_CLICKED(IDC_BUTTON_Clear, &CStudBDDlg::OnBnClickedButtonClear)
	ON_BN_CLICKED(IDC_BUTTON_Get, &CStudBDDlg::OnBnClickedButtonGet)
	ON_BN_CLICKED(IDC_BUTTON_Change, &CStudBDDlg::OnBnClickedButtonChange)
	ON_BN_CLICKED(IDC_BUTTON_Del, &CStudBDDlg::OnBnClickedButtonDel)
END_MESSAGE_MAP()


// Обработчики сообщений CStudBDDlg

BOOL CStudBDDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Добавление пункта "О программе..." в системное меню.

	// IDM_ABOUTBOX должен быть в пределах системной команды.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
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

	return TRUE;  // возврат значения TRUE, если фокус не передан элементу управления
}

void CStudBDDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CStudBDDlg::OnPaint()
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
HCURSOR CStudBDDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


//////////////////////////////////////////////////////////////////////////////////

void CStudBDDlg::OnBnClickedButtonRefresh() // Обновление данных
{
	CString  Information;
	CString X("  "), Y("."), Z("\r\n");

	bool flag = true;
	for (int i = 0; i < clk; i++)
	{
		if (student[i].flag) continue; // Удаленная информация о студентах
		flag = false;
		Information += student[i].Surname + X +
			student[i].Name + X +
			student[i].Patr + X +
			student[i].YearEnter + X +
			student[i].Kaf + X +
			student[i].Group + X +
			student[i].NumZ + X +
			student[i].Gender + X +
			+Z;
			//student[i].DataBoth.GetDay + Y +
			//student[i].DataBoth.GetMonth + Y +
			//student[i].DataBoth.GetYear + Z;
	}
	if (flag)
	{
		MessageBox(_T("Запрос информации о студенте не выполнен!"));
	}
	else
	{
		ListStud.ResetContent();
		ListStud.InsertString(0, Information);
		MessageBox(_T("Запрос информации о студентах успешно!"));
	}
}


void CStudBDDlg::OnBnClickedButtonReadf() // Чтение файла
{
	ifstream in("mydata.txt");

	if (!in)
	{
		MessageBox(_T("Не удалось прочитать информацию о студенте!"));
	}
	else
	{
		vector<string> arr;
		string word;
		while (in >> word)
		{
			if (word == "ПУСТОЙ!");
			arr.push_back(word);
		}
		in.close();
		
		CString Surname,
			Name,
			Patr,
			YearEnter,
			Kaf,
			Group,
			NumZ,
			Gender;
		COleDateTime DataBoth;
		clk = 0;
		
		for (int i = 0; i < arr.size(); i++)
		{
			if (i % 8 == 0) Surname = arr[i].c_str();
			if (i % 8 == 1) Name = arr[i].c_str();
			if (i % 8 == 2) Patr = arr[i].c_str();
			if (i % 8 == 3) YearEnter = arr[i].c_str();
			if (i % 8 == 4) Kaf = arr[i].c_str();
			if (i % 8 == 5) Group = arr[i].c_str();
			if (i % 8 == 6) NumZ = arr[i].c_str();
			if (i % 8 == 7) Gender = arr[i].c_str();
			if (i % 8 == 7)  student[clk++] = { Surname,
				Name,
				Patr,
				YearEnter,
				Kaf,
				Group,
				NumZ,
				Gender,
				DataBoth,
				false };
		}
		MessageBox(_T("Информация о студенте прочитана успешно!"));
	}
}


void CStudBDDlg::OnBnClickedButtonNew()
{
	CString Surname,
		Name,
		Patr,
		YearEnter,
		Kaf,
		Group,
		NumZ,
		Gender;
	COleDateTime DataBoth;

	GetDlgItemText(IDC_EDIT_Surname, Surname);
	GetDlgItemText(IDC_EDIT_Name, Name);
	GetDlgItemText(IDC_EDIT_Patr, Patr);
	GetDlgItemText(IDC_EDIT_YearEnter, YearEnter);
	GetDlgItemText(IDC_EDIT_Kaf, Kaf);
	GetDlgItemText(IDC_EDIT_Group, Group);
	GetDlgItemText(IDC_EDIT_NumZ, NumZ);
	GetDlgItemText(IDC_EDIT_Gender, Gender);

	bool flag = true;
	CString X = CString("");

	if (Surname != X &&
		Name != X &&
		Patr != X &&
		YearEnter != X &&
		Kaf != X &&
		Group != X &&
		NumZ != X &&
		Gender != X)
	{
		for (int i = 0; i < clk; i++)
		{
			if (student[i].flag) continue; //Удаленная информация о студентах
			if (NumZ == student[i].NumZ)
			{
				flag = false;
			}
		}
	}
	if (flag)
	{
		student[clk++] = { Surname,
				Name,
				Patr,
				YearEnter,
				Kaf,
				Group,
				NumZ,
				Gender,
				DataBoth,
				false };
		MessageBox(_T("Успешно создана новая информация о студентах!"));
	}
	else
	{
		MessageBox(_T("Идентификатор студента уже существует или информация неполная!"));
	}
}


void CStudBDDlg::OnBnClickedButtonClear()
{
	ofstream out("mydata.txt");
	if (!out)
	{
		MessageBox(_T("Ошибка записи информации об ученике!"));
	}
	else
	{
		string X = "", Y = "";
		for (int i = 0; i < clk; i++)
		{
			if (!student[i].flag)
			{
				Y = string(CW2A(student[i].Surname.GetString()));
				X += Y + " ";
				Y = string(CW2A(student[i].Name.GetString()));
				X += Y + " ";
				Y = string(CW2A(student[i].Patr.GetString()));
				X += Y + " ";
				Y = string(CW2A(student[i].YearEnter.GetString()));
				X += Y + " ";
				Y = string(CW2A(student[i].Kaf.GetString()));
				X += Y + " ";
				Y = string(CW2A(student[i].Group.GetString()));
				X += Y + " ";
				Y = string(CW2A(student[i].NumZ.GetString()));
				X += Y + " ";
				Y = string(CW2A(student[i].Gender.GetString()));
				X += Y + "\r\n";
			}
		}
		out << X;
		out << "ПУСТОЙ!" << endl;
		out.close();
		MessageBox(_T("Информация о студенте написана успешно!"));
	}
}


void CStudBDDlg::OnBnClickedButtonGet()
{
	CString Surname,
		Name,
		Patr,
		YearEnter,
		Kaf,
		Group,
		NumZ,
		Gender;

	GetDlgItemText(IDC_EDIT_Surname, Surname);
	GetDlgItemText(IDC_EDIT_Name, Name);
	GetDlgItemText(IDC_EDIT_Patr, Patr);
	GetDlgItemText(IDC_EDIT_YearEnter, YearEnter);
	GetDlgItemText(IDC_EDIT_Kaf, Kaf);
	GetDlgItemText(IDC_EDIT_Group, Group);
	GetDlgItemText(IDC_EDIT_NumZ, NumZ);
	GetDlgItemText(IDC_EDIT_Gender, Gender);

	bool flag = true;
	CString X = CString("");
	if (NumZ != X && Surname != X)
	{
		for (int i = 0; i < clk; i++)
		{
			if (student[i].flag) continue;//Удаленная информация о студентах
			if (NumZ == student[i].NumZ && Surname == student[i].Surname)
			{
				flag = false;
				SetDlgItemText(IDC_EDIT_Surname, Surname);
				SetDlgItemText(IDC_EDIT_Name, Name);
				SetDlgItemText(IDC_EDIT_Patr, Patr);
				SetDlgItemText(IDC_EDIT_YearEnter, YearEnter);
				SetDlgItemText(IDC_EDIT_Kaf, Kaf);
				SetDlgItemText(IDC_EDIT_Group, Group);
				SetDlgItemText(IDC_EDIT_NumZ, NumZ);
				SetDlgItemText(IDC_EDIT_Gender, Gender);
				MessageBox(_T("Запрос информации о студентах успешно!"));
			}
		}
	}
	if (flag)
	{
		MessageBox(_T("Запрос информации о студенте не выполнен! Пожалуйста, перепроверьте номер студента!"));
	}
}


void CStudBDDlg::OnBnClickedButtonChange()
{
	CString Surname,
		Name,
		Patr,
		YearEnter,
		Kaf,
		Group,
		NumZ,
		Gender;
	COleDateTime DataBoth;

	GetDlgItemText(IDC_EDIT_Surname, Surname);
	GetDlgItemText(IDC_EDIT_Name, Name);
	GetDlgItemText(IDC_EDIT_Patr, Patr);
	GetDlgItemText(IDC_EDIT_YearEnter, YearEnter);
	GetDlgItemText(IDC_EDIT_Kaf, Kaf);
	GetDlgItemText(IDC_EDIT_Group, Group);
	GetDlgItemText(IDC_EDIT_NumZ, NumZ);
	GetDlgItemText(IDC_EDIT_Gender, Gender);

	bool flag = true;
	CString X = CString("");
	if (
		Surname != X &&
		Name != X &&
		Patr != X &&
		YearEnter != X &&
		Kaf != X &&
		Group != X &&
		NumZ != X &&
		Gender != X)
	{
		for (int i = 0; i < clk; i++)
		{
			if (student[i].flag) continue;//Удаленная информация о студентах
			if (NumZ == student[i].NumZ && Surname == student[i].Surname)
			{
				flag = false;
				student[i] = { 
					Surname,
					Name,
					Patr,
					YearEnter,
					Kaf,
					Group,
					NumZ,
					Gender,
					DataBoth,
					false
				};
				MessageBox(_T("Успешно измененная информация об ученике!"));
				break;
			}
		}
	}
	if (flag)
	{
		MessageBox(_T("Не удалось изменить информацию о студенте! Пожалуйста, перепроверьте номер студента! Или полная информация!"));
	}
}


void CStudBDDlg::OnBnClickedButtonDel()
{
	CString Surname,
		Name,
		Patr,
		YearEnter,
		Kaf,
		Group,
		NumZ,
		Gender;

	GetDlgItemText(IDC_EDIT_Surname, Surname);
	GetDlgItemText(IDC_EDIT_Name, Name);
	GetDlgItemText(IDC_EDIT_Patr, Patr);
	GetDlgItemText(IDC_EDIT_YearEnter, YearEnter);
	GetDlgItemText(IDC_EDIT_Kaf, Kaf);
	GetDlgItemText(IDC_EDIT_Group, Group);
	GetDlgItemText(IDC_EDIT_NumZ, NumZ);
	GetDlgItemText(IDC_EDIT_Gender, Gender);

	bool flag = true;
	CString X = CString("");
	if (NumZ != X && Surname != X)
	{
		for (int i = 0; i < clk; i++)
		{
			if (student[i].flag) continue;//Удаленная информация о студентах
			if (NumZ == student[i].NumZ && Surname == student[i].Surname)
			{
				flag = false;
				student[i].flag = true;
				MessageBox(_T("Информация об ученике успешно удалена!"));
			}
		}
	}
	if (flag)
	{
		MessageBox(_T("Не удалось удалить информацию о студенте! Пожалуйста, перепроверьте номер или имя студента!"));
	}
}
