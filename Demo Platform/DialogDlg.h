
// DialogDlg.h : ͷ�ļ�
//

#pragma once
#include "RegisterDlg.h"
#include "MatchDlg.h"
#include "GatherDlg.h"
#include "engine.h"

// CDialogDlg �Ի���
class CDialogDlg : public CDialogEx
{
// ����
public:
	CDialogDlg(CWnd* pParent = NULL);	// ��׼���캯��
	~CDialogDlg();

	void DisplayWindow( BOOL bShow );
// �Ի�������
	enum { IDD = IDD_DIALOG_DIALOG };



	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��
	virtual void OnWindowPosChanging( WINDOWPOS* lpwndpos );


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
private:
	BOOL m_Visible;
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton2();
};
