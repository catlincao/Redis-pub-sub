
// LaserRangeDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "LaserRange.h"
#include "LaserRangeDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CLaserRangeDlg �Ի���

CLaserRangeDlg *CLaserRangeDlg::instance = NULL;

CLaserRangeDlg::CLaserRangeDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CLaserRangeDlg::IDD, pParent)
{
	instance = this;
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	WSAData wsaData;
	WSAStartup(MAKEWORD(1, 1), &wsaData);
}

void CLaserRangeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CLaserRangeDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_DESTROY()
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CLaserRangeDlg ��Ϣ�������

BOOL CLaserRangeDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO:  �ڴ���Ӷ���ĳ�ʼ������
	//��ʼ������
	m_ipAddr = _T("127.0.0.1");
	m_Port = 6377;
	if (!m_psM.Connect(m_ipAddr, m_Port))
	{
		AfxMessageBox("δ������redis���ݿ�");
		ExitProcess(1);
	}
	//Ĭ�ϼ���CCDCaptureSyncƵ��
	m_Channel = "CCDCaptureSync";
	m_psM.Subscribe(m_Channel);
	//��һ����ʱ������100ms��ʱ��������Ƿ�����Ϣ����
	SetTimer(1001, 100, NULL);
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CLaserRangeDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CLaserRangeDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CLaserRangeDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CLaserRangeDlg::OnDestroy()
{
	CDialogEx::OnDestroy();
	m_psM.Unsubscribe(m_Channel);
	// TODO:  �ڴ˴������Ϣ����������
}


void CLaserRangeDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	//ÿ��ʱ�䵽��ʹ��PubSubManager��Ĵ��������ж��Ƿ�����Ϣ����
	m_psM.OnTimer();
	CDialogEx::OnTimer(nIDEvent);
}

void CLaserRangeDlg::SaveAPicture()
{
	//save a picture here
	//����������д���ͼ������

	//������Щ���ǵ����õĴ��룬�����ı䴰�ڵ�title
	CTime t = CTime::GetCurrentTime();
	CString s = t.Format("%H-%M-%S");
	instance->SetWindowText(s);
}

void SAVEAPICTURE()
{
	//ȫ�ֺ�������PubSubManager���������Ϣ����ص��������е���
	CLaserRangeDlg::SaveAPicture();
}