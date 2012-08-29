
// b_ukDlg.cpp : файл реализации
//

//#pragma comment(lib, "hid.dll")

#include "stdafx.h"
#include "b_uk.h"
#include "b_ukDlg.h"
#include "afxdialogex.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

	// ТУТ ПОСТАВЬТЕ НАШ ДАННЫЕ
int             vid = 0x16C0;
int             pid = 0x0220;
char            vendorName[512], productName[512];
#define DATALEN		  64

#define BYTE unsigned char

#define MATRIXBUFFERSIZE 32 
//unsigned char Matrixbuffer[ MATRIXBUFFERSIZE + 2];

BYTE cicle = 0;
BYTE Increm = 0;

#pragma pack(1) 
typedef struct{
	unsigned char  Query[4];   
	unsigned char  Command;    
	unsigned char  Param;      
}_REQUEST_HED;


#pragma pack(1)
typedef struct{
	_REQUEST_HED	 hed;
  	unsigned char	 Data[ DATALEN ];
	unsigned char  	 CRC[2];	
}_REQUEST;

	//_REQUEST *req;

volatile unsigned char buffer_1[73];
unsigned char buffer_2[73];
unsigned char *IOBuffer = (unsigned char *)buffer_1;

	unsigned char SecretConstantProg[256] = 
{ 
255, 230, 253, 3, 19, 220, 14, 161, 141, 129, 160, 227, 117, 100, 196, 15, 52, 55, 
159, 96, 125, 211, 22, 249, 24, 91, 41, 113, 28, 114, 8, 116, 88, 139, 53, 226, 193, 
50, 101, 11, 40, 60, 217, 80, 239, 45, 59, 208, 44, 204, 252, 75, 74, 137, 76, 104, 150, 
49, 90, 32, 173, 61, 77, 63, 64, 233, 106, 84, 216, 144, 140, 20, 6, 190, 197, 25, 94, 
70, 78, 156, 65, 66, 86, 93, 33, 12, 10, 87, 39, 254, 34, 82, 131, 170, 163, 108, 110, 
199, 1, 119, 246, 191, 115, 31, 247, 105, 240, 147, 79, 182, 29, 56, 112, 203, 221, 183, 
5, 212, 177, 242, 192, 35, 122, 229, 146, 48, 126, 47, 228, 16, 179, 184, 132, 133, 213, 
222, 134, 155, 209, 130, 109, 164, 154, 17, 36, 121, 185, 207, 201, 102, 21, 62, 176, 57,
69, 243, 71, 245, 37, 153, 165, 157, 232, 27, 2, 135, 166, 167, 18, 169, 186, 158, 172, 
107, 174, 175, 85, 136, 97, 51, 99, 127, 72, 188, 138, 171, 181, 241, 68, 248, 23, 234, 
210, 244, 103, 178, 128, 9, 43, 152, 200, 118, 202, 13, 89, 38, 180, 205, 95, 81, 162, 235, 
73, 223, 142, 237, 54, 215, 218, 198, 206, 194, 168, 214, 224, 151, 67, 219, 92, 42, 83, 236,
123, 58, 145, 143, 4, 46, 124, 98, 26, 111, 225, 7, 30, 238, 189, 148, 195, 231, 250, 251, 
120, 187, 0, 149 
};


		unsigned char test_buf[72] =
{
0x80, 0xB2, 0x5D, 0xE6, 0xAC, 0x85, 0x88, 0xA5, 0xB1, 0x35, 0xB8, 0x21, 0x46, 0x08, 0xD6, 0xEB, 0x45,
0xEA, 0x7C, 0x6B, 0xF7, 0xFF, 0x38, 0xE1, 0xC7, 0x9F, 0x8E, 0x89, 0x4F, 0xA1, 0xAB, 0x12, 0x0A, 0x07,
0xD2, 0x5E, 0x8D, 0xA0, 0xA6, 0xA7, 0xDE, 0xA9, 0x5D, 0xB9, 0xAC, 0x3C, 0xAE, 0xAF, 0x98, 0x76, 0xC3,
0x82, 0xCE, 0xBA, 0x6D, 0x73, 0x83, 0x92, 0xAA, 0xFD, 0xB7, 0xF6, 0x49, 0x65, 0x78, 0x24, 0xDD, 0xF8,
0x0E, 0x4A, 0x4D, 0x9C
};

		unsigned char Matrixbuffer[ MATRIXBUFFERSIZE + 2] =
	{
0x41, 0x88, 0x24, 0xc4, 0xca, 0x4b, 0x40, 0x86, 0x1f, 0x12, 0x80, 0xa9, 0x8f, 
0x3e, 0x34, 0x68, 0xa1, 0xeb, 0x8c, 0x5b, 0xc7, 0xb0, 0xa5, 0xc6, 0x76, 0x18, 
0xb8, 0x6b, 0x99, 0xa6, 0x87, 0x90, 0x1a, 0xfa
	};


	



typedef PVOID HDEVINFO;

typedef struct _SP_DEVINFO_DATA {
    DWORD cbSize;
    GUID  ClassGuid;
    DWORD DevInst;    // DEVINST handle
    ULONG_PTR Reserved;
} SP_DEVINFO_DATA, *PSP_DEVINFO_DATA;

typedef struct _SP_DEVICE_INTERFACE_DATA {
    DWORD cbSize;
    GUID  InterfaceClassGuid;
    DWORD Flags;
    ULONG_PTR Reserved;
} SP_DEVICE_INTERFACE_DATA, *PSP_DEVICE_INTERFACE_DATA;

typedef struct _SP_DEVICE_INTERFACE_DETAIL_DATA_A {
    DWORD  cbSize;
    CHAR   DevicePath[ANYSIZE_ARRAY];
} SP_DEVICE_INTERFACE_DETAIL_DATA_A, *PSP_DEVICE_INTERFACE_DETAIL_DATA_A;

typedef struct _SP_DEVICE_INTERFACE_DETAIL_DATA_W {
    DWORD  cbSize;
    WCHAR  DevicePath[ANYSIZE_ARRAY];
} SP_DEVICE_INTERFACE_DETAIL_DATA_W, *PSP_DEVICE_INTERFACE_DETAIL_DATA_W;


typedef struct _HIDD_ATTRIBUTES
{
ULONG Size; // = sizeof (struct _HIDD_ATTRIBUTES)
USHORT VendorID;
USHORT ProductID;
USHORT VersionNumber;
} HIDD_ATTRIBUTES, *PHIDD_ATTRIBUTES;

typedef BOOLEAN (__stdcall *PHidD_GetProductString)(HANDLE, PVOID, ULONG);
typedef VOID	(__stdcall *PHidD_GetHidGuid)(LPGUID);
typedef BOOLEAN (__stdcall *PHidD_GetAttributes)(HANDLE, PHIDD_ATTRIBUTES);
typedef BOOLEAN (__stdcall *PHidD_SetFeature)(HANDLE, PVOID, ULONG);
typedef BOOLEAN (__stdcall *PHidD_GetFeature)(HANDLE, PVOID, ULONG);
typedef BOOLEAN (__stdcall *PHidD_FlushQueue)(HANDLE);
typedef BOOLEAN (__stdcall *PHidD_SetOutputReport)(HANDLE, PVOID, ULONG);
typedef BOOLEAN (__stdcall *PHidD_GetInputReport)(HANDLE, PVOID, ULONG);
typedef BOOLEAN (__stdcall *PHidD_GetManufacturerString)(HANDLE, PVOID, ULONG);


typedef HDEVINFO (__stdcall *PSetupDiGetClassDevs)(CONST GUID*, PCSTR, HWND, DWORD);
typedef BOOL	 (__stdcall *PSetupDiEnumDeviceInterfaces)(HDEVINFO,PSP_DEVINFO_DATA,CONST GUID*,DWORD,PSP_DEVICE_INTERFACE_DATA);
typedef BOOL	 (__stdcall *PSetupDiDestroyDeviceInfoList)(HDEVINFO);
typedef BOOL	 (__stdcall *PSetupDiGetDeviceInterfaceDetail)(HDEVINFO,PSP_DEVICE_INTERFACE_DATA,PSP_DEVICE_INTERFACE_DETAIL_DATA_W,DWORD,PDWORD,PSP_DEVINFO_DATA);

HINSTANCE hHID = NULL;
HINSTANCE hSET = NULL;

PHidD_GetProductString HidD_GetProductString = NULL;
PHidD_GetHidGuid HidD_GetHidGuid = NULL;
PHidD_GetAttributes HidD_GetAttributes = NULL;
PHidD_SetFeature HidD_SetFeature = NULL;
PHidD_GetFeature HidD_GetFeature = NULL;
PHidD_FlushQueue HidD_FlushQueue = NULL;
PHidD_SetOutputReport HidD_SetOutputReport = NULL;
PHidD_GetInputReport  HidD_GetInputReport = NULL;
PHidD_GetManufacturerString  HidD_GetManufacturerString = NULL;


//Load the library:
PSetupDiGetClassDevs SetupDiGetClassDevs = NULL;
PSetupDiEnumDeviceInterfaces SetupDiEnumDeviceInterfaces = NULL;
PSetupDiDestroyDeviceInfoList SetupDiDestroyDeviceInfoList = NULL;
PSetupDiGetDeviceInterfaceDetail SetupDiGetDeviceInterfaceDetail = NULL;


//void LoadHidFunction(void)
//{
//	hHID = LoadLibrary( _T("HID.DLL"));
//	//Update the pointers:
//	HidD_GetProductString = (PHidD_GetProductString) GetProcAddress(hHID, "HidD_GetProductString");
//	HidD_GetHidGuid = (PHidD_GetHidGuid) GetProcAddress(hHID, "HidD_GetHidGuid");
//	HidD_GetAttributes = (PHidD_GetAttributes) GetProcAddress(hHID, "HidD_GetAttributes");
//	HidD_SetFeature = (PHidD_SetFeature) GetProcAddress(hHID, "HidD_SetFeature");
//	HidD_GetFeature = (PHidD_GetFeature) GetProcAddress(hHID, "HidD_GetFeature");
//	HidD_FlushQueue = (PHidD_FlushQueue) GetProcAddress(hHID, "HidD_FlushQueue");
//	HidD_SetOutputReport = (PHidD_SetOutputReport) GetProcAddress(hHID, "HidD_SetOutputReport");
//	HidD_GetInputReport = (PHidD_GetInputReport) GetProcAddress(hHID, "HidD_GetInputReport");
//	HidD_GetManufacturerString = (PHidD_GetManufacturerString) GetProcAddress(hHID, "HidD_GetManufacturerString");
//	
//}

//void LoadSETUPAPIFunction(void)
//{
//	hSET = LoadLibrary( _T("SETUPAPI.DLL") );
//	SetupDiGetClassDevs = (PSetupDiGetClassDevs) GetProcAddress(hSET, "SetupDiGetClassDevsW");
//	SetupDiEnumDeviceInterfaces = (PSetupDiEnumDeviceInterfaces) GetProcAddress(hSET, "SetupDiEnumDeviceInterfaces");
//	SetupDiDestroyDeviceInfoList = (PSetupDiDestroyDeviceInfoList)GetProcAddress(hSET, "SetupDiDestroyDeviceInfoList");
//	SetupDiGetDeviceInterfaceDetail = (PSetupDiGetDeviceInterfaceDetail)GetProcAddress(hSET, "SetupDiGetDeviceInterfaceDetailW");
//}


#define DIGCF_DEFAULT           0x00000001  // only valid with DIGCF_DEVICEINTERFACE
#define DIGCF_PRESENT           0x00000002
#define DIGCF_ALLCLASSES        0x00000004
#define DIGCF_PROFILE           0x00000008
#define DIGCF_DEVICEINTERFACE   0x00000010

#define DIGCF_INTERFACEDEVICE DIGCF_DEVICEINTERFACE





// Диалоговое окно CAboutDlg используется для описания сведений о приложении

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Данные диалогового окна
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV

// Реализация
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// диалоговое окно Cb_ukDlg




Cb_ukDlg::Cb_ukDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(Cb_ukDlg::IDD, pParent)
	//, m_text(_T(""))
	, f_size(0)
//	, m_byte(0)
//, m_char(0)
//, m_int(0)
//, m_stroka(_T(""))
//, m_list(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_text_2 = _T("");
	//  m_list = _T("");
	m_edit_7 = _T("");
}

void Cb_ukDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//  DDX_Text(pDX, IDC_EDIT1, m_text);
	DDX_Text(pDX, IDC_EDIT2, f_size);
	//	DDX_Text(pDX, IDC_EDIT1, m_byte);
	DDX_Text(pDX, IDC_EDIT1, m_text_2);
	//  DDX_Text(pDX, IDC_EDIT6, m_char);
	//  DDX_Text(pDX, IDC_EDIT7, m_int);
	//  DDX_Text(pDX, IDC_EDIT6, m_stroka);
	//  DDX_Control(pDX, IDC_EDIT8, m_test);
	//  DDX_LBString(pDX, IDC_LIST1, m_list);
	//  DDX_LBString(pDX, IDC_LIST2, m_list);
	DDX_Control(pDX, IDC_EDIT6, m_marat);
	DDX_Text(pDX, IDC_EDIT7, m_edit_7);
}

BEGIN_MESSAGE_MAP(Cb_ukDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &Cb_ukDlg::OnBnClickedButton1)
	ON_EN_CHANGE(IDC_EDIT1, &Cb_ukDlg::OnEnChangeEdit1)
	ON_EN_CHANGE(IDC_EDIT4, &Cb_ukDlg::OnEnChangeEdit4)
	//ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST1, &Cb_ukDlg::OnLvnItemchangedList1)
//	ON_CBN_SELCHANGE(IDC_COMBO1, &Cb_ukDlg::OnCbnSelchangeCombo1)
ON_BN_CLICKED(IDC_BUTTON2, &Cb_ukDlg::OnBnClickedButton2)
ON_BN_CLICKED(IDC_BUTTON4, &Cb_ukDlg::OnBnClickedButton4)
END_MESSAGE_MAP()


// обработчики сообщений Cb_ukDlg

BOOL Cb_ukDlg::OnInitDialog()
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

	// Задает значок для этого диалогового окна. Среда делает это автоматически,
	//  если главное окно приложения не является диалоговым
	SetIcon(m_hIcon, TRUE);			// Крупный значок
	SetIcon(m_hIcon, FALSE);		// Мелкий значок

	// TODO: добавьте дополнительную инициализацию

	return TRUE;  // возврат значения TRUE, если фокус не передан элементу управления
}

void Cb_ukDlg::OnSysCommand(UINT nID, LPARAM lParam)
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
//  чтобы нарисовать значок. Для приложений MFC, использующих модель документов или представлений,
//  это автоматически выполняется рабочей областью.

void Cb_ukDlg::OnPaint()
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
HCURSOR Cb_ukDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void Cb_ukDlg::OnBnClickedButton1()
{
	// TODO: добавьте свой код обработчика уведомлений
	//m_text = "Привет!";
	//UpdateData(FALSE);
	//CFileDialog DlgOpen(TRUE,(LPCSTR)"txt",NULL, OFN_HIDEREADONLY,(LPCSTR)" Text Files (*.txt) |*.txt||");
	CFileDialog DlgOpen(TRUE);

	

	double m_test;
	unsigned long long int dlina = 0;
	unsigned int count = 0;
	CString strt = _T("  Hello ");
	char prob = ' ';
	

	

	

	//int iResult=dlgOpen.DoModal();
	
	if(DlgOpen.DoModal()==IDOK) 
   	{	
		//m_text = DlgOpen.GetPathName();
		//UpdateData(FALSE);
		
		// создание объекта и открытие файла для чтения
		//CStdioFile File(DlgOpen.GetPathName(),CFile::modeRead|CFile::typeBinary);
		// чтение из файла строки
 		//CString& ref = m_text;
 		//File.ReadString(ref); // передается ссылка на строку m_Text

		h_file.Open(DlgOpen.GetPathName(),CFile::modeRead | CFile::typeBinary);

		dlina = h_file.GetLength();
		f_size = dlina;

		m_text_2 = " ";
		
		UpdateData(FALSE);

		

		 
			//m_int = parseHEX(8);
			

	while(parseUntilColon() == ':'){
		 
        sum = 0;
        sum += lineLen = parseHEX(2);
		if(lineLen == 0){break;}
        base = address = parseHEX(4);
        sum += address >> 8;
        sum += address;
        sum += segment = parseHEX(2);  /* segment value? */
	
		//   if(segment != 0)    /* ignore lines where this byte is not 0 */
        //  continue;
	
        for(int t = 0; t < lineLen ; t++){
            d = parseHEX(2);
            buffer[address++] = d;
            sum += d;
        }
        sum += parseHEX(2);
       
		if((sum & 0xff) != 0){
          //  fprintf(stderr, "Warning: Checksum error between address 0x%x and 0x%x\n", base, address);
        }
        if(startAddr > base)
            startAddr = base;
        if(endAddr < address)
            endAddr = address;
		}

	
	for(int y=0;y<10;y++)
	{
		hex_f[y] = buffer[y];
	
	}


	
	for(int x=0;x<10;x++)
	{
		
	m_text.Format(_T("%X %c"), hex_f[x], prob);
	m_text_3+=m_text+_T("\r");
	}
	
	m_marat.SetWindowTextW(m_text_3);
	


		do
		{

			m_text.Format(_T("%X %c"), buffer[count++], prob); 
		//	m_text.Format(_T("%x %s"),  0x16, strt);
		//	m_text.Format(_T("%X"),buffer[count]);
			m_text_2+=m_text+_T("\r\n");

		


			
			

		//	count++;

		}while(count < endAddr);



    
	


		//m_list = parseHEX(8);
		
			
		

		

		/*	for(int k = 0;  k < dlina; k++)
			{
				h_file.Read(symbol, 1);
				if(symbol[0] == 0x3A)
					{
						k--;
					}else hex_f[k] = symbol[0];
				
				
			}
			

		
			do
		{
			m_text.Format(_T("%X"),hex_f[count]);
			m_text_2+=m_text+_T("\r");

			count++;

		}while(count < dlina);*/

		UpdateData(FALSE);
    
	
		h_file.Close();
		
 	} 

}


void Cb_ukDlg::OnEnChangeEdit1()
{
	// TODO:  Если это элемент управления RICHEDIT, то элемент управления не будет
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Добавьте код элемента управления
}


void Cb_ukDlg::OnEnChangeEdit4()
{
	// TODO:  Если это элемент управления RICHEDIT, то элемент управления не будет
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Добавьте код элемента управления
}


//int Cb_ukDlg::parseHex(int digits)
//{
//	int     i;
//	char    temp[9];
//
//    for(i = 0; i < digits; i++)
//	{
//    h_file.Read(symbol, 1);
//	    temp[i] = symbol[0];
//	}
//    temp[i] = 0;
//    return strtol(temp, NULL, 16);
//}


int Cb_ukDlg::parseHEX(int digits)
{
	int     i;
	char    temp[9];

    for(i = 0; i < digits; i++)
	{
       h_file.Read(symbol, 1);
	   temp[i] = symbol[0]; 
	}
    temp[i] = 0;
    return strtol(temp, NULL, 16);
}


char Cb_ukDlg::parseUntilColon(void)
{
	//int symb;

    do{
        h_file.Read(symbol, 1);
    }while(symbol[0] != ':');// && symbol[0] != 0xFF);
    return symbol[0];
}





void Cb_ukDlg::OnCbnSelchangeCombo1()
{
	// TODO: добавьте свой код обработчика уведомлений
}


void Cb_ukDlg::OnBnClickedButton2()
{

	//usbDevice_t     *dev = NULL;

	//	LoadHidFunction_1();
	//	LoadSETUPAPIFunction_1();
	//
	//	usbDevice_t  *handler; //openDevice_1();

	//	if((err = usbhidOpenDevice_1(&dev, vid, vendorName, pid, productName, 0)) != 0)
	//		{
	//		m_edit_7 = "Device not found!";
	//		UpdateData(FALSE);
	//		}else {
	//			m_edit_7 = "Device open successfully!";
	//			UpdateData(FALSE);
	//			}


	//	CloseHandle((HANDLE)dev);

	

}



//static char Cb_ukDlg::*usbErrorMessage(int errCode)
//{
//static char buffer[80];
//
//    switch(errCode){
//        case USBOPEN_ERR_ACCESS:      return 1;//"Access to device denied";
//        case USBOPEN_ERR_NOTFOUND:    return "The specified device was not found";
//        case USBOPEN_ERR_IO:          return "Communication error with device";
//        default:
//            sprintf(buffer, "Unknown USB error %d", errCode);
//            return buffer;
//    }
//    return NULL;    /* not reached */
//} 

void Cb_ukDlg::convertUniToAscii(char *buffer)
{
unsigned short  *uni = (unsigned short  *)buffer;
char            *ascii = buffer;

    while(*uni != 0){
        if(*uni >= 256){
            *ascii++ = '?';
        }else{
            *ascii++ = *uni++;
        }
    }
    *ascii++ = 0;
} 

int Cb_ukDlg::usbhidSetReport(usbDevice_t *device, unsigned char *buffer, int len)
{
BOOLEAN rval;

    rval = HidD_SetFeature((HANDLE)device, buffer, len);
    return rval == 0 ? USBOPEN_ERR_IO : 0;
}

/* ------------------------------------------------------------------------ */

int Cb_ukDlg::usbhidGetReport(usbDevice_t *device, int reportNumber, unsigned char *buffer, int *len)
{
BOOLEAN rval = 0;

    buffer[0] = reportNumber;
    rval = HidD_GetFeature((HANDLE)device, buffer, *len);
    return rval == 0 ? USBOPEN_ERR_IO : 0;
}

int Cb_ukDlg::usbhidOpenDevice_1(usbDevice_t **device, int vendor, char *vendorName, int product, char *productName, int usesReportIDs)
{
GUID                                hidGuid;        /* GUID for HID driver */
HDEVINFO                            deviceInfoList;
SP_DEVICE_INTERFACE_DATA            deviceInfo;
SP_DEVICE_INTERFACE_DETAIL_DATA_W   *deviceDetails = NULL;
DWORD                               size;
int                                 i, openFlag = 0;  /* may be FILE_FLAG_OVERLAPPED */
int                                 errorCode = USBOPEN_ERR_NOTFOUND;
HANDLE                              handle = INVALID_HANDLE_VALUE;
HIDD_ATTRIBUTES                     deviceAttributes;

				
    HidD_GetHidGuid(&hidGuid);
    deviceInfoList = SetupDiGetClassDevs(&hidGuid, NULL, NULL, DIGCF_PRESENT | DIGCF_INTERFACEDEVICE);
    deviceInfo.cbSize = sizeof(deviceInfo);
    for(i=0;;i++){
        if(handle != INVALID_HANDLE_VALUE){
            CloseHandle(handle);
            handle = INVALID_HANDLE_VALUE;
        }
        if(!SetupDiEnumDeviceInterfaces(deviceInfoList, 0, &hidGuid, i, &deviceInfo))
            break;  /* no more entries */
        /* first do a dummy call just to determine the actual size required */
        SetupDiGetDeviceInterfaceDetail(deviceInfoList, &deviceInfo, NULL, 0, &size, NULL);
        if(deviceDetails != NULL)
            free(deviceDetails);
        deviceDetails = (SP_DEVICE_INTERFACE_DETAIL_DATA_W *) malloc(size);
        deviceDetails->cbSize = 6; //sizeof(SP_DEVICE_INTERFACE_DETAIL_DATA_A);
        /* this call is for real: */
        SetupDiGetDeviceInterfaceDetail(deviceInfoList, &deviceInfo, deviceDetails, size , &size, NULL);
        //DEBUG_PRINT(("checking HID path \"%s\"\n", deviceDetails->DevicePath));
#if 0
        /* If we want to access a mouse our keyboard, we can only use feature
         * requests as the device is locked by Windows. It must be opened
         * with ACCESS_TYPE_NONE.
         */
        handle = CreateFile(deviceDetails->DevicePath, ACCESS_TYPE_NONE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, openFlag, NULL);
#endif
        /* attempt opening for R/W -- we don't care about devices which can't be accessed */
        handle = CreateFileW(deviceDetails->DevicePath, GENERIC_READ|GENERIC_WRITE, FILE_SHARE_READ|FILE_SHARE_WRITE, NULL, OPEN_EXISTING, openFlag, NULL);
        if(handle == INVALID_HANDLE_VALUE){
            errorCode = USBOPEN_ERR_ACCESS; /* opening will always fail for mouse -- ignore */
            continue;
        }
        deviceAttributes.Size = sizeof(deviceAttributes);
        HidD_GetAttributes(handle, &deviceAttributes);
       // DEBUG_PRINT(("device attributes: vid=%d pid=%d\n", deviceAttributes.VendorID, deviceAttributes.ProductID));
        if(deviceAttributes.VendorID != vendor || deviceAttributes.ProductID != product)
            continue;   /* ignore this device */
        errorCode = USBOPEN_ERR_NOTFOUND;
        if(vendorName != NULL && productName != NULL){
            char    buffer[512];
            if(!HidD_GetManufacturerString(handle, buffer, sizeof(buffer))){
                errorCode = USBOPEN_ERR_IO;
                continue;
            }
            convertUniToAscii(buffer);
            memcpy(vendorName, buffer, 512);
                
            if(!HidD_GetProductString(handle, buffer, sizeof(buffer))){
               // DEBUG_PRINT(("error obtaining product name\n"));
                errorCode = USBOPEN_ERR_IO;
                continue;
            }
            convertUniToAscii(buffer);
            //DEBUG_PRINT(("productName = \"%s\"\n", buffer));
            memcpy(productName, buffer, 512);
                
        }
        break;  /* we have found the device we are looking for! */
    }
    SetupDiDestroyDeviceInfoList(deviceInfoList);
    if(deviceDetails != NULL)
        free(deviceDetails);
    if(handle != INVALID_HANDLE_VALUE){
        *device = (usbDevice_t *)handle;
        errorCode = 0;
    }
    return errorCode;
} 

void Cb_ukDlg::LoadHidFunction_1(void)
{

	hHID = LoadLibrary( _T("HID.DLL"));
	//Update the pointers:
	HidD_GetProductString = (PHidD_GetProductString) GetProcAddress(hHID, "HidD_GetProductString");
	HidD_GetHidGuid = (PHidD_GetHidGuid) GetProcAddress(hHID, "HidD_GetHidGuid");
	HidD_GetAttributes = (PHidD_GetAttributes) GetProcAddress(hHID, "HidD_GetAttributes");
	HidD_SetFeature = (PHidD_SetFeature) GetProcAddress(hHID, "HidD_SetFeature");
	HidD_GetFeature = (PHidD_GetFeature) GetProcAddress(hHID, "HidD_GetFeature");
	HidD_FlushQueue = (PHidD_FlushQueue) GetProcAddress(hHID, "HidD_FlushQueue");
	HidD_SetOutputReport = (PHidD_SetOutputReport) GetProcAddress(hHID, "HidD_SetOutputReport");
	HidD_GetInputReport = (PHidD_GetInputReport) GetProcAddress(hHID, "HidD_GetInputReport");
	HidD_GetManufacturerString = (PHidD_GetManufacturerString) GetProcAddress(hHID, "HidD_GetManufacturerString");

	
}


void Cb_ukDlg::LoadSETUPAPIFunction_1(void)
{
	hSET = LoadLibrary( _T("SETUPAPI.DLL") );
	SetupDiGetClassDevs = (PSetupDiGetClassDevs) GetProcAddress(hSET, "SetupDiGetClassDevsW");
	SetupDiEnumDeviceInterfaces = (PSetupDiEnumDeviceInterfaces) GetProcAddress(hSET, "SetupDiEnumDeviceInterfaces");
	SetupDiDestroyDeviceInfoList = (PSetupDiDestroyDeviceInfoList)GetProcAddress(hSET, "SetupDiDestroyDeviceInfoList");
	SetupDiGetDeviceInterfaceDetail = (PSetupDiGetDeviceInterfaceDetail)GetProcAddress(hSET, "SetupDiGetDeviceInterfaceDetailW");
}


void Cb_ukDlg:: openDevice_1(void)
{
//usbDevice_t     *dev = NULL;
//int             *err_0;

 //   if((err = usbhidOpenDevice(&dev, vid, vendorName, pid, productName, 0)) != 0){
 //   return NULL;
 //   }
    
//	return *err_0;//dev;
} 


void Cb_ukDlg::OnBnClickedButton4()
{
	usbDevice_t     *dev = NULL;
	char buffer_rep[73];
	int hid_rep = 0;
	int len_rep;

	

	len_rep = sizeof(buffer_rep);

	buffer_rep[0] = 0;

		LoadHidFunction_1();
		LoadSETUPAPIFunction_1();
	
		usbDevice_t  *handler; //openDevice_1();

		if((err = usbhidOpenDevice_1(&dev, vid, vendorName, pid, productName, 0)) != 0)
			{
			m_edit_7 = "Device not found!";
			UpdateData(FALSE);
			}else {
				m_edit_7 = "Device open successfully!";
				UpdateData(FALSE);
				}
		
		handler = dev;

		//hid_rep = usbhidGetReport(handler, 0, buffer_rep, &len_rep);
		//buffer_rep[5] = 40; //get KEY_NUMBER

		//for( int i = 1; i<72; i++ ) 
		//{
		//	*((unsigned char *)req + i) = C2_index( *((unsigned char *)req + i) , (*((unsigned char *)req )) + i );
		//}

	//	memcpy(IOBuffer,test_buf,72);

		_REQUEST *req = (_REQUEST *)IOBuffer;
		

	//	for( unsigned int w = 1; w<72; w++ )
//			   *((unsigned char *)req + w) = C2_Deindex( *((unsigned char *)req + w) , (*((unsigned char *)req )) + w );

	
		


		//hid_rep = usbhidSetReport(handler, (char *)req , len_rep);

		req->hed.Query[0] = 28;
		req->hed.Query[1] = 24;
		req->hed.Query[2] = 45;
		req->hed.Query[3] = 89;
		
		

		req->hed.Command = 0x28;
		req->hed.Param = 0x0;


		for( int z = 1; z<72; z++ )  
			*((unsigned char *)req + z) = C2_index( *((unsigned char *)req + z) , (*((unsigned char *)req )) + z );


		hid_rep = usbhidSetReport(handler, IOBuffer  , len_rep);
		
	/*	for(unsigned int r = 0; r<1500; r++)
		{
			_asm {nop}
		}*/


		hid_rep = usbhidGetReport(handler, 0, IOBuffer , &len_rep);

			for( unsigned int w = 1; w<72; w++ )
			   *((unsigned char *)req + w) = C2_Deindex( *((unsigned char *)req + w) , (*((unsigned char *)req )) + w );


		CloseHandle((HANDLE)dev);
}


unsigned char Cb_ukDlg::C2_Deindex(unsigned char index, unsigned char KEY)
{
	unsigned char b = 0;
	memcpy( &b, SecretConstantProg + index, 1);
	return (b - KEY);
}


unsigned char Cb_ukDlg::C2_index(unsigned char ch, unsigned char KEY)
{
	int index = 0; 
	unsigned char Idx = 0;
	unsigned char b = 0;
	
	ch += KEY;
	for( index = 0; index < 256; index++){ 
	memcpy( &b, SecretConstantProg + index, 1);
	if( b == ch ) break;
		Idx++;
	}

	return Idx;
}


void Cb_ukDlg::decode(unsigned long  * v, unsigned long  * k, unsigned char Flag)
{
BYTE *p = (BYTE *)v; 
if (Flag == 0 ) Increm = 0;
for( cicle = 0; cicle < 8; cicle++) *(p + cicle ) += (Increm ++);

unsigned long n = 32, sum, y = v[0], z = v[1],
delta = 0x9e3779b9 ;
sum = delta<<5 ;

while (n-->0) {
z -= ((y<<4)+k[2] ^ y+sum ^ (y>>5)+k[3] );
y -= ((z<<4)+k[0] ^ z+sum ^ (z>>5)+k[1] );
sum -= delta ; }

v[0] = y ; v[1] = z ;
}
