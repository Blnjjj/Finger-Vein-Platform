#pragma once

#include <iostream>
#include <fstream>
//#include "RegisterDlg.h"
using namespace std;
// MsgDlg �Ի���
struct Messages
{
	CString NAME;
	CString JOB;
	CString NUMBER;

	int fingers[6];
	int quantity[2];
	
};
class MsgDlg : public CDialogEx
{
	DECLARE_DYNAMIC(MsgDlg)

public:
	MsgDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~MsgDlg();
	Messages msg;
// �Ի�������
	enum { IDD = IDD_MSGDLG };

protected:
	HICON m_hIcon;
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	void getPath();
	int getLines();
	CString NAME;
	CString JOB;
		//������Ϣ
	CString modalPath;
	CString Pnum;
};
