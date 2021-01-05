
// StudBDDlg.h: файл заголовка
//

#pragma once


// Диалоговое окно CStudBDDlg
class CStudBDDlg : public CDialogEx
{
// Создание
public:
	CStudBDDlg(CWnd* pParent = nullptr);	// стандартный конструктор

// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_STUDBD_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// поддержка DDX/DDV


// Реализация
protected:
	HICON m_hIcon;

	// Созданные функции схемы сообщений
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonRefresh();
	COleDateTime DataBorth;
	CListBox ListStud;
	afx_msg void OnBnClickedButtonReadf();
	afx_msg void OnBnClickedButtonNew();
	afx_msg void OnBnClickedButtonClear();
	afx_msg void OnBnClickedButtonGet();
	afx_msg void OnBnClickedButtonChange();
	afx_msg void OnBnClickedButtonDel();
};
