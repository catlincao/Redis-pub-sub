
// LaserRangeDlg.h : ͷ�ļ�
//

#pragma once
#include "PubSubManager.h"

// CLaserRangeDlg �Ի���
class CLaserRangeDlg : public CDialogEx
{
// ����
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
	CLaserRangeDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_LASERRANGE_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��

// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnDestroy();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};
