#pragma once


// MatchDlg �Ի���
#include "DialogDlg.h"
#include "CvvImage.h"
#include "ImageProcess.h"
using namespace std;
UINT MatchThreadProc(LPVOID lpParam);
class MatchDlg : public CDialogEx
{
	DECLARE_DYNAMIC(MatchDlg)

public:
	MatchDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~MatchDlg();
	BOOL m_bImage;
	BOOL m_bClosed;
	CvCapture *capture;
 
    
	HDC hDC;
	CRect rect;
	CDC *pDC;
	IplImage *m_Frame;
	CWnd *pwnd;

	//ƥ������
	IplImage* dst;
// �Ի�������
	enum { IDD = IDD_MATCHDLG };

protected:
	HICON m_hIcon;
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	//�������ܼ�
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton4();
	afx_msg void myClose();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedButton2();
	//
	afx_msg void OnBnClickedButton3();
};
