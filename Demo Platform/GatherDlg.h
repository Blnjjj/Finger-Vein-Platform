#pragma once


// GatherDlg �Ի���
#include "DialogDlg.h"
#include "CvvImage.h"
#include "afxwin.h"
using namespace std;
class GatherDlg : public CDialogEx
{
	DECLARE_DYNAMIC(GatherDlg)

public:
	GatherDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~GatherDlg();
	BOOL m_bImage;
	BOOL m_bClosed;
	CvCapture *capture;
 
    
	HDC hDC;
	CRect rect;
	CDC *pDC;
	IplImage *m_Frame;
	CWnd *pwnd;


// �Ի�������
	enum { IDD = IDD_GATHERDLG };

protected:
	HICON m_hIcon;
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	//�������ܼ�
	afx_msg void OnBnClickedButton5();//����
	afx_msg void OnBnClickedButton1();//������ͷ
	afx_msg void OnBnClickedButton2();//�ر�����ͷ
	afx_msg void myClose();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	//
	afx_msg void OnBnClickedButton7();
	CString address;
	//afx_msg void OnBnClickedButton3();
	CComboBox ImgType;
	CString NUM1;
	CString NUM2;
	CString Type;
	CString SIM;
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton3();
	void GetMsg();
	CString Message;
	CString modalPath;
	void getPath();
	int getLines();
	int count;
	BOOL EFIN[6];
	CString out;
	void Write();
};
