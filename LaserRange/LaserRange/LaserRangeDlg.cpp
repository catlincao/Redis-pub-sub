
// LaserRangeDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "LaserRange.h"
#include "LaserRangeDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
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


// CLaserRangeDlg 对话框

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


// CLaserRangeDlg 消息处理程序

BOOL CLaserRangeDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO:  在此添加额外的初始化代码
	//初始化连接
	m_ipAddr = _T("127.0.0.1");
	m_Port = 6377;
	if (!m_psM.Connect(m_ipAddr, m_Port))
	{
		AfxMessageBox("未能连接redis数据库");
		ExitProcess(1);
	}
	//默认监听CCDCaptureSync频道
	m_Channel = "CCDCaptureSync";
	m_psM.Subscribe(m_Channel);
	//打开一个定时器，以100ms的时间来检测是否有信息进来
	SetTimer(1001, 100, NULL);
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CLaserRangeDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CLaserRangeDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CLaserRangeDlg::OnDestroy()
{
	CDialogEx::OnDestroy();
	m_psM.Unsubscribe(m_Channel);
	// TODO:  在此处添加消息处理程序代码
}


void CLaserRangeDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	//每次时间到都使用PubSubManager类的处理函数来判断是否有消息发布
	m_psM.OnTimer();
	CDialogEx::OnTimer(nIDEvent);
}

void CLaserRangeDlg::SaveAPicture()
{
	//save a picture here
	//可以在这里写入存图的内容

	//下面这些都是调试用的代码，用来改变窗口的title
	CTime t = CTime::GetCurrentTime();
	CString s = t.Format("%H-%M-%S");
	instance->SetWindowText(s);
}

void SAVEAPICTURE()
{
	//全局函数，供PubSubManager类里面的消息处理回调函数进行调用
	CLaserRangeDlg::SaveAPicture();
}