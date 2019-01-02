// MatchDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Dialog.h"
#include "MatchDlg.h"
#include "afxdialogex.h"


// MatchDlg �Ի���

IMPLEMENT_DYNAMIC(MatchDlg, CDialogEx)

MatchDlg::MatchDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(MatchDlg::IDD, pParent)
	,m_Frame(NULL)
	,m_bImage(false)
	,m_bClosed(false)
{

}

MatchDlg::~MatchDlg()
{
	if(m_bClosed)
	{
		cvReleaseCapture(&capture);
		m_bImage=FALSE;
		m_bClosed=FALSE;
		CString str;
	 }
}

void MatchDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(MatchDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &MatchDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON4, &MatchDlg::OnBnClickedButton4)
	ON_MESSAGE_VOID(WM_CLOSE,myClose)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON2, &MatchDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &MatchDlg::OnBnClickedButton3)
END_MESSAGE_MAP()


// MatchDlg ��Ϣ�������

BOOL MatchDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
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
	ModifyStyleEx(0,WS_EX_APPWINDOW);
	SetIcon(m_hIcon, TRUE);			
	SetIcon(m_hIcon, FALSE);		
 
	pwnd=GetDlgItem(IDC_PIC);
	pDC=pwnd->GetDC();
	hDC=pDC->GetSafeHdc();
	pwnd->GetClientRect(&rect);
	return TRUE;  
}
void MatchDlg::OnBnClickedButton1()
{
	//������ͷ
	// TODO: �ڴ���ӿؼ�֪ͨ����������
		if(!m_bImage)
	{
	capture=cvCaptureFromCAM(1);
	MessageBox(_T("����ͷ�򿪳ɹ�"));
	m_bClosed=TRUE;
	}
	if(m_bImage)
	{
		
		MessageBox(_T(""));
		return;
	}
	m_Frame=cvQueryFrame(capture);
	if(!m_Frame)
	{
		return;
	}
	CvvImage m_CvvImage;
	m_CvvImage.CopyOf(m_Frame,3);
	m_CvvImage.DrawToHDC(hDC,&rect);
	SetTimer(1,1,NULL);
}


void MatchDlg::OnBnClickedButton4()
{
	//����
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if(m_bClosed)
	{
		cvReleaseCapture(&capture);
		m_bImage=FALSE;
		m_bClosed=FALSE;
		CString str;
	 }
	CDialogDlg *pDlg;
	pDlg=(CDialogDlg*)GetParent();
	pDlg->DisplayWindow(TRUE);
	CDialog::OnOK();
}
void MatchDlg::myClose()
{
        //AfxMessageBox("exit");
        //ExitProcess(-1);
        

        //if(::MessageBox(NULL,_T( "Save the current interface before exit��"),_T("Program Exit"), MB_YESNO) == IDYES)
        //
                //������һЩ�������ݵĶ���
	CDialogDlg *pDlg;
	pDlg=(CDialogDlg*)GetParent();
	pDlg->DisplayWindow(TRUE);
    this->OnClose();
}

void MatchDlg::OnBnClickedButton2()
{
	//�ر�����ͷ
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if(m_bClosed)
	{
		cvReleaseCapture(&capture);
		m_bImage=FALSE;
		m_bClosed=FALSE;
		CString str;
	 }
}
void MatchDlg::OnTimer(UINT_PTR nIDEvent)
{

	// TODO:
	m_Frame=cvQueryFrame(capture);
	CvvImage m_CvvImage;
	m_CvvImage.CopyOf(m_Frame,3);
	m_CvvImage.DrawToHDC(hDC,&rect);

	CDialogEx::OnTimer(nIDEvent);
}

void MatchDlg::OnBnClickedButton3()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if(!m_bClosed)
	{
		MessageBox(_T("���ȴ�����ͷ��"));
		return;
	}

	dst=cvCreateImage(cvGetSize(m_Frame),m_Frame->depth,1);


	cvCvtColor(m_Frame,dst,CV_BGR2GRAY);

	//AfxBeginThread((AFX_THREADPROC)MatchThreadProc,this);
	//MessageBox(imp.Pmsg[1].Mid(7,1));
	//MessageBox(imp.Pmsg[2].Mid(15,1));
	//MessageBox(imp.Pmsg[3]);
	if(m_bClosed)
	{
		cvReleaseCapture(&capture);
		m_bImage=FALSE;
		m_bClosed=FALSE;
		CString str;
	 }
	ImageProcess imp;
	imp.matchevery(dst);
	if(imp.score[imp.person[0]][0]<0.167)
		MessageBox(_T("δƥ�䵽��Ӧָ"));
	else{
		CString mes;
		mes=_T("��ţ�")+imp.Pmsg[imp.person[0]].Mid(0,3)+_T("\r\n")+
			_T("��Ϣ��")+imp.Pmsg[imp.person[0]].Mid(14,(imp.Pmsg[imp.person[0]].GetLength()-14))+_T("\r\n");
		if(imp.person[1]==1) 
			mes+=_T("ȡ��ָ������ʳָ");
		if(imp.person[1]==2)
			mes+=_T("ȡ��ָ��������ָ");
		if(imp.person[1]==3)
			mes+=_T("ȡ��ָ����������ָ");
		if(imp.person[1]==4)
			mes+=_T("ȡ��ָ������ʳָ");
		if(imp.person[1]==5)
			mes+=_T("ȡ��ָ��������ָ");
		if(imp.person[1]==6)
			mes+=_T("ȡ��ָ����������ָ");
		MessageBox(mes);
	}

}

UINT MatchThreadProc(LPVOID lpParam)
{
	MatchDlg *pMDLG=(MatchDlg*)lpParam;
	if (pMDLG == NULL ||
        !pMDLG->IsKindOf(RUNTIME_CLASS(MatchDlg)))
    return 1;
	ImageProcess imp;
	
	imp.matchevery(pMDLG->dst);


	return 0;
}