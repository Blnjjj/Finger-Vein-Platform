#pragma once


// RegisterDlg �Ի���
#include "Engine.h"
#include "DialogDlg.h"
#include "CvvImage.h"
#include "MsgDlg.h"
#include <iostream>
#include <fstream>
#include "ImageProcess.h"

using namespace std;
UINT TrainThreadProc(LPVOID lpParam);

class RegisterDlg : public CDialogEx
{
	DECLARE_DYNAMIC(RegisterDlg)

public:
	RegisterDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~RegisterDlg();
	//����ͷ��ر���
	BOOL m_bImage;
	BOOL m_bClosed;
	CvCapture *capture;
 
    
	HDC hDC;
	CRect rect;
	CDC *pDC;
	IplImage *m_Frame;
	CWnd *pwnd;
	//����ģ����ر���
	IplImage *finImg1[3];
	IplImage *finImg2[6];
	int finNum;
	int counter;
	int imgcounter;
	BOOL EFin[6];
	CString modalPath;
	CString codePath;
	CString name;
	//�û���Ϣ����
	Messages msg;
	MsgDlg msgdlg;
	

// �Ի�������
	enum { IDD = IDD_REGISTERDLG };

protected:
	HICON m_hIcon;
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton3();
	afx_msg void myClose();
	afx_msg void OnBnClickedButton6();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton1();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	CString Message;
	void ReadMessage();
	void WriteMessage();
	void getPath();
	void train(CString name);
	BOOL Saved(CString name);
	afx_msg void OnBnClickedButton5();
};
