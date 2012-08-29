
// b_ukDlg.h : файл заголовка
//

#pragma once
#include "afxwin.h"
#include "hiddata.h"


// диалоговое окно Cb_ukDlg
class Cb_ukDlg : public CDialogEx
{
// Создание
public:
	Cb_ukDlg(CWnd* pParent = NULL);	// стандартный конструктор

// Данные диалогового окна
	enum { IDD = IDD_B_UK_DIALOG };

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
	afx_msg void OnBnClickedButton1();
	afx_msg void OnEnChangeEdit1();

	
//	CString m_text;
	unsigned char hex_f[10];
	ULONGLONG f_size;
	afx_msg void OnEnChangeEdit4();
	CString m_text;
	CString m_text_2;
	CString m_text_3;
	
//	char m_char;
//	int m_int;
	CFile h_file;
	unsigned char symbol[1];

//	static int parseHex(int digits);
	int parseHEX(int digits);
//	CString m_stroka;
//	CEdit m_test;
//	CString m_list;
	 char parseUntilColon(void);
	int     address, base, d, segment, i, lineLen, sum;
	unsigned char buffer[65536 + 256];
	int  startAddr, endAddr;
	afx_msg void OnLvnItemchangedList1(NMHDR *pNMHDR, LRESULT *pResult);
//	CString m_list;
	afx_msg void OnCbnSelchangeCombo1();
	CEdit m_marat;

	void LoadHidFunction(void);
	void LoadSETUPAPIFunction(void);
    void convertUniToAscii(char *buffer);
	//static char *usbErrorMessage(int errCode);
	//static usbDevice_t  *openDevice(void);
	static void hexdump(char *buffer, int len);

	int usbhidOpenDevice_1(usbDevice_t **device, int vendor, char *vendorName, int product, char *productName, int usesReportIDs);
	int usbhidSetReport(usbDevice_t *device, unsigned char *buffer, int len);
	int usbhidGetReport(usbDevice_t *device, int reportNumber, unsigned char *buffer, int *len);


	afx_msg void OnBnClickedButton2();
	CString m_edit_7;
	void LoadHidFunction_1(void);
	void LoadSETUPAPIFunction_1(void);
	void openDevice_1(void);
	int             err;
	afx_msg void OnBnClickedButton4();


	unsigned char C2_Deindex(unsigned char index, unsigned char KEY);
	unsigned char C2_index(unsigned char ch, unsigned char KEY);
	void decode(unsigned long  * v, unsigned long  * k, unsigned char Flag);
};
