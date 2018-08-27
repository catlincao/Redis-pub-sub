
// LaserRangeDlg.h : 头文件
//

#pragma once
#include "PubSubManager.h"

// CLaserRangeDlg 对话框
class CLaserRangeDlg : public CDialogEx
{
// 构造
public:
//	DWORD m_ipAddr;
	CString m_ipAddr;
	int m_Port;
	CString m_Channel;
	CString m_message;
	static void SaveAPicture();
protected:
	PubSubManager m_psM;
	static CLaserRangeDlg *instance;

public:
	CLaserRangeDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_LASERRANGE_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持

// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnDestroy();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};
