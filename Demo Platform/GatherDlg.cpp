// GatherDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Dialog.h"
#include "GatherDlg.h"
#include "afxdialogex.h"


// GatherDlg �Ի���

IMPLEMENT_DYNAMIC(GatherDlg, CDialogEx)

GatherDlg::GatherDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(GatherDlg::IDD, pParent)
	,m_Frame(NULL)
	,m_bImage(false)
	,m_bClosed(false)
	, address(_T(""))
	//, NUM1(_T(""))
	//, NUM2(_T(""))
	, Type(_T(""))
	//, SIM(_T(""))
	, Message(_T(""))
	,out(_T(""))
{
	count=0;
	EFIN[0]=FALSE;
	EFIN[1]=FALSE;
	EFIN[2]=FALSE;
	EFIN[3]=FALSE;
	EFIN[4]=FALSE;
	EFIN[5]=FALSE;
	setlocale(LC_ALL,"chinese");
}

GatherDlg::~GatherDlg()
{
	if(m_bClosed)
	{
		cvReleaseCapture(&capture);
		m_bImage=FALSE;
		m_bClosed=FALSE;
		CString str;
	 }
}

void GatherDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_ADR, address);
	DDX_Control(pDX, IDC_COMBO1, ImgType);
	//DDX_Text(pDX, IDC_NUM1, NUM1);
	//DDX_Text(pDX, IDC_NUM2, NUM2);
	DDX_CBString(pDX, IDC_COMBO1, Type);
	//DDX_Text(pDX, IDC_SIM, SIM);
	DDX_Text(pDX, IDC_MSG, Message);
}


BEGIN_MESSAGE_MAP(GatherDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON5, &GatherDlg::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON1, &GatherDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &GatherDlg::OnBnClickedButton2)
	ON_MESSAGE_VOID(WM_CLOSE,myClose)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON7, &GatherDlg::OnBnClickedButton7)
	//ON_BN_CLICKED(IDC_BUTTON3, &GatherDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &GatherDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON3, &GatherDlg::OnBnClickedButton3)
END_MESSAGE_MAP()

BOOL GatherDlg::OnInitDialog()
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
	ModifyStyleEx(0,WS_EX_APPWINDOW);//����������ʾ
	SetIcon(m_hIcon, TRUE);			
	SetIcon(m_hIcon, FALSE);		
	CButton* radio=(CButton*)GetDlgItem(IDC_THREE);
	radio->SetCheck(1);
	UpdateData(FALSE);
	
	pwnd=GetDlgItem(IDC_PIC);
	pDC=pwnd->GetDC();
	hDC=pDC->GetSafeHdc();
	pwnd->GetClientRect(&rect);


	ImgType.AddString(_T(".bmp"));
	ImgType.AddString(_T(".jpg"));
	ImgType.AddString(_T(".jpeg"));
	ImgType.AddString(_T(".gif"));
	//ImgType.AddString(_T(".bmp"));
	GetMsg();
	return TRUE;  
}
// GatherDlg ��Ϣ�������


void GatherDlg::OnBnClickedButton5()
{
	//����
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CDialogDlg *pDlg;
	pDlg=(CDialogDlg*)GetParent();
	pDlg->DisplayWindow(TRUE);
	CDialog::OnOK();
}


void GatherDlg::OnBnClickedButton1()
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
	m_CvvImage.CopyOf(m_Frame,1);
	m_CvvImage.DrawToHDC(hDC,&rect);
	SetTimer(1,1,NULL);
}


void GatherDlg::OnBnClickedButton2()
{
	//�ر�����ͷ
	// TODO: �ڴ���ӿؼ�֪ͨ����������
		// TODO: �ڴ���ӿؼ�֪ͨ����������
	if(m_bClosed)
	{
		cvReleaseCapture(&capture);
		m_bImage=FALSE;
		m_bClosed=FALSE;
		CString str;
	 }
}

void GatherDlg::myClose()
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
void GatherDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO:
	m_Frame=cvQueryFrame(capture);
	CvvImage m_CvvImage;
	m_CvvImage.CopyOf(m_Frame,1);
	m_CvvImage.DrawToHDC(hDC,&rect);

	CDialogEx::OnTimer(nIDEvent);
}

void GatherDlg::OnBnClickedButton7()
{
	UpdateData(TRUE);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	char szPath[MAX_PATH];     //���ѡ���Ŀ¼·�� 
	CString str;

	ZeroMemory(szPath, sizeof(szPath));   

	BROWSEINFO bi;   
	bi.hwndOwner = m_hWnd;   
	bi.pidlRoot = NULL;   
	bi.pszDisplayName = (LPWSTR)szPath;   
	bi.lpszTitle = _T("��ѡ����Ҫ�����Ŀ¼��");   
	bi.ulFlags = 0;   
	bi.lpfn = NULL;   
	bi.lParam = 0;   
	bi.iImage = 0;   
	//����ѡ��Ŀ¼�Ի���
	LPITEMIDLIST lp = SHBrowseForFolder(&bi);   

	if(lp && SHGetPathFromIDList(lp, (LPWSTR)szPath))   
	{
		address=(LPWSTR)szPath;
		UpdateData(FALSE);
	}

}


//void GatherDlg::OnBnClickedButton3()
//{
//	if(!m_bClosed)
//	{
//		MessageBox(_T("���ȴ�����ͷ��"));
//		return;
//	}
//	UpdateData(TRUE);
//	if(address==""){
//		MessageBox(_T("������洢·����"));
//		return;
//	}
//	if(NUM1==""){
//		MessageBox(_T("���������"));
//		return;
//	}
//	if(NUM2==""){
//		MessageBox(_T("���������"));
//		return;
//	}
//	if(SIM==""){
//		MessageBox(_T("�������������"));
//		return;
//	}
//	int SleNum=ImgType.GetCurSel();
//	if(SleNum==-1){
//		MessageBox(_T("��ѡ��洢��ʽ��"));
//		return;
//	}
//	// TODO: �ڴ���ӿؼ�֪ͨ����������
//	IplImage* dst=cvCreateImage(cvGetSize(m_Frame),m_Frame->depth,1);
//	cvCvtColor(m_Frame,dst,CV_BGR2GRAY);
//	CString name=address+_T("\\");
//	CString num1,num2,sim,imgtype;
//	GetDlgItem(IDC_NUM1)->GetWindowTextW(num1);
//	GetDlgItem(IDC_NUM2)->GetWindowTextW(num2);
//	GetDlgItem(IDC_SIM)->GetWindowTextW(sim);
//	ImgType.GetLBText(SleNum,imgtype);
//	//GetDlgItem(IDC_COMBO1)->
//	name+=num1+sim+num2+imgtype;
//	int n = name.GetLength(); //���ַ����㣬str�ĳ���
//	int len = WideCharToMultiByte(CP_ACP,0,name,n,NULL,0,NULL,NULL);//��Byte����str����
//	char*temp = new char[len+1];//���ֽ�Ϊ��λ
//	WideCharToMultiByte(CP_ACP,0,name,n,temp,len,NULL,NULL);//���ֽ�ת��Ϊ���ֽڱ���
//	temp[len] = '\0';
//	cvSaveImage(temp,dst);
//	MessageBox(_T("�ɹ���"));
//}
//

void GatherDlg::OnBnClickedButton4()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	MessageBox(_T("��д�������Ϣ����ȡ�����вɼ���"));
}



void GatherDlg::getPath()
{
		wchar_t fileName[_MAX_FNAME], Dir[_MAX_DIR], Drive[_MAX_DRIVE], Ext[_MAX_EXT], newPath[_MAX_PATH];
	wchar_t* pgmptr;
	_get_wpgmptr(&pgmptr);
	_wsplitpath_s(pgmptr, Drive, Dir, fileName, Ext);

	_wmakepath_s(newPath, Drive, Dir, NULL, NULL);
	modalPath=newPath;
	modalPath+="modal\\";
}
int GatherDlg::getLines()
{
	char buffer[50];
	int n=0;
	ifstream ReadLines;
	ReadLines.open(modalPath+_T("Gatherlog.txt"),ios::in);
	if(ReadLines.fail())
		return 0;
	else
	{
		while(ReadLines.getline(buffer,50))
			n++;
	}
	ReadLines.close();
	return n;
	
}
void GatherDlg::GetMsg(){
	getPath();
	int n=getLines();
	Message.Format(_T("%.3d"),n+1);
	Message=_T("ȡ�����:")+Message+_T("\r\n");
	UpdateData(FALSE);
}


void GatherDlg::Write()
{
	wofstream write;
	write.open(modalPath+_T("Gatherlog.txt"),ios::app);

	write<<CStringA(out)<<'\n';

	write.close();
}
void GatherDlg::OnBnClickedButton3()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	UpdateData(TRUE);
	if(!m_bClosed)
	{
		MessageBox(_T("���ȿ�������ͷ��"));
		return;
	}
	if(IsDlgButtonChecked(IDC_FL1)==BST_UNCHECKED
		&&IsDlgButtonChecked(IDC_FL2)==BST_UNCHECKED
		&&IsDlgButtonChecked(IDC_FL3)==BST_UNCHECKED
		&&IsDlgButtonChecked(IDC_FR1)==BST_UNCHECKED
		&&IsDlgButtonChecked(IDC_FR2)==BST_UNCHECKED
		&&IsDlgButtonChecked(IDC_FR3)==BST_UNCHECKED)
	{
		MessageBox(_T("������ѡ��һ����ָ��Ϊȡ��ָ��"));
		return;
	}
	int SleNum=ImgType.GetCurSel();
	if(SleNum==-1){
		MessageBox(_T("��ѡ��洢��ʽ��"));
		return;
	}
	if(address==""){
		MessageBox(_T("������洢·����"));
		return;
	}
	if(count==0){
		if(IDCANCEL==MessageBox(_T("ȷ��Ҫ����ȡ����"), _T("ȷ��ȡ��"), MB_OKCANCEL | MB_ICONQUESTION))
			return;
		count++;
		out.Format(_T("%.3d"),getLines()+1);
		out+=_T(" ");
		if(GetCheckedRadioButton(IDC_THREE,IDC_SIX)==IDC_THREE){
			Message+=_T("ȡ������3\r\n");
			out+="10 ";
		}else{
			Message+=_T("ȡ������6\r\n");
			out+="01 ";
		}
		Message+="ȡ����ָ��\r\n";
		if(IsDlgButtonChecked(IDC_FL1)){
			Message+=_T("����ʳָ   ");
			EFIN[0]=TRUE;
			out+="1";
		}else
			out+="0";
		if(IsDlgButtonChecked(IDC_FL2)){
			Message+=_T("������ָ   ");
			EFIN[1]=TRUE;
				out+="1";
		}else
			out+="0";
		if(IsDlgButtonChecked(IDC_FL3)){
			Message+=_T("��������ָ   ");
			EFIN[2]=TRUE;
			out+="1";
		}else
			out+="0";
		if(IsDlgButtonChecked(IDC_FR1)){
			Message+=_T("����ʳָ   ");
			EFIN[3]=TRUE;
			out+="1";
		}else
			out+="0";
		if(IsDlgButtonChecked(IDC_FR2)){
			Message+=_T("������ָ   ");
				EFIN[4]=TRUE;
			out+="1";
		}else
			out+="0";
		if(IsDlgButtonChecked(IDC_FR3)){
			Message+=_T("��������ָ   ");
			EFIN[5]=TRUE;
			out+="1";
		}else
			out+="0";
		UpdateData(FALSE);
		Write();
		out="";
		GetDlgItem(IDC_THREE)->EnableWindow(FALSE);
		GetDlgItem(IDC_SIX)->EnableWindow(FALSE);
		GetDlgItem(IDC_FL1)->EnableWindow(FALSE);
		GetDlgItem(IDC_FL2)->EnableWindow(FALSE);
		GetDlgItem(IDC_FL3)->EnableWindow(FALSE);
		GetDlgItem(IDC_FR1)->EnableWindow(FALSE);
		GetDlgItem(IDC_FR2)->EnableWindow(FALSE);
		GetDlgItem(IDC_FR3)->EnableWindow(FALSE);
		GetDlgItem(IDC_COMBO1)->EnableWindow(FALSE);
		GetDlgItem(IDC_ADR)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON5)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON7)->EnableWindow(FALSE);
	}else{
		IplImage* dst=cvCreateImage(cvGetSize(m_Frame),m_Frame->depth,1);
		cvCvtColor(m_Frame,dst,CV_BGR2GRAY);
		UpdateData(TRUE);
		CString name;
		name=address+_T("\\");
		if(GetCheckedRadioButton(IDC_THREE,IDC_SIX)==IDC_THREE){
			if(EFIN[0]==TRUE)
				if(count<3){
					CString num;
					num.Format(_T("%.3d"),getLines());
					name+=num+_T("_L1_");
					num.Format(_T("%d"),count);
					name+=num;
					name=name+Type;

					int n = name.GetLength(); //���ַ����㣬str�ĳ���
					int len = WideCharToMultiByte(CP_ACP,0,name,n,NULL,0,NULL,NULL);//��Byte����str����
					char*temp = new char[len+1];//���ֽ�Ϊ��λ
					WideCharToMultiByte(CP_ACP,0,name,n,temp,len,NULL,NULL);//���ֽ�ת��Ϊ���ֽڱ���
					temp[len] = '\0';
					cvSaveImage(temp,dst);
					delete[] temp;
					MessageBox(_T("�ѱ��棺  ����ʳָ")+num+_T("/3"));
					count++;
					return;
				}else{
					CString num;
					num.Format(_T("%.3d"),getLines());
					name+=num+_T("_L1_");
					num.Format(_T("%d"),count);
					name+=num;
					name=name+Type;

					int n = name.GetLength(); //���ַ����㣬str�ĳ���
					int len = WideCharToMultiByte(CP_ACP,0,name,n,NULL,0,NULL,NULL);//��Byte����str����
					char*temp = new char[len+1];//���ֽ�Ϊ��λ
					WideCharToMultiByte(CP_ACP,0,name,n,temp,len,NULL,NULL);//���ֽ�ת��Ϊ���ֽڱ���
					temp[len] = '\0';
					cvSaveImage(temp,dst);
					delete[] temp;
					MessageBox(_T("�ѱ��棺  ����ʳָ")+num+_T("/3"));

					count=1;
					EFIN[0]=FALSE;
					if(!EFIN[0]&&!EFIN[1]&&!EFIN[2]&&!EFIN[3]&&!EFIN[4]&&!EFIN[5]){
						GetDlgItem(IDC_THREE)->EnableWindow(TRUE);
						GetDlgItem(IDC_SIX)->EnableWindow(TRUE);
						GetDlgItem(IDC_FL1)->EnableWindow(TRUE);
						GetDlgItem(IDC_FL2)->EnableWindow(TRUE);
						GetDlgItem(IDC_FL3)->EnableWindow(TRUE);
						GetDlgItem(IDC_FR1)->EnableWindow(TRUE);
						GetDlgItem(IDC_FR2)->EnableWindow(TRUE);
						GetDlgItem(IDC_FR3)->EnableWindow(TRUE);
						GetDlgItem(IDC_COMBO1)->EnableWindow(TRUE);
						GetDlgItem(IDC_ADR)->EnableWindow(TRUE);
						GetDlgItem(IDC_BUTTON5)->EnableWindow(TRUE);
						GetDlgItem(IDC_BUTTON7)->EnableWindow(TRUE);
						GetMsg();
						count=0;
					}
					return;

				}
			if(EFIN[1]==TRUE)
				if(count<3){
					CString num;
					num.Format(_T("%.3d"),getLines());
					name+=num+_T("_L2_");
					num.Format(_T("%d"),count);
					name+=num;
					name=name+Type;

					int n = name.GetLength(); //���ַ����㣬str�ĳ���
					int len = WideCharToMultiByte(CP_ACP,0,name,n,NULL,0,NULL,NULL);//��Byte����str����
					char*temp = new char[len+1];//���ֽ�Ϊ��λ
					WideCharToMultiByte(CP_ACP,0,name,n,temp,len,NULL,NULL);//���ֽ�ת��Ϊ���ֽڱ���
					temp[len] = '\0';
					cvSaveImage(temp,dst);
					delete[] temp;
					MessageBox(_T("�ѱ��棺  ������ָ")+num+_T("/3"));
					count++;
					return;
				}else{
					CString num;
					num.Format(_T("%.3d"),getLines());
					name+=num+_T("_L2_");
					num.Format(_T("%d"),count);
					name+=num;
					name=name+Type;

					int n = name.GetLength(); //���ַ����㣬str�ĳ���
					int len = WideCharToMultiByte(CP_ACP,0,name,n,NULL,0,NULL,NULL);//��Byte����str����
					char*temp = new char[len+1];//���ֽ�Ϊ��λ
					WideCharToMultiByte(CP_ACP,0,name,n,temp,len,NULL,NULL);//���ֽ�ת��Ϊ���ֽڱ���
					temp[len] = '\0';
					cvSaveImage(temp,dst);
					delete[] temp;
					MessageBox(_T("�ѱ��棺  ������ָ")+num+_T("/3"));
					count=1;
					EFIN[1]=FALSE;
					if(!EFIN[0]&&!EFIN[1]&&!EFIN[2]&&!EFIN[3]&&!EFIN[4]&&!EFIN[5]){
						GetDlgItem(IDC_THREE)->EnableWindow(TRUE);
						GetDlgItem(IDC_SIX)->EnableWindow(TRUE);
						GetDlgItem(IDC_FL1)->EnableWindow(TRUE);
						GetDlgItem(IDC_FL2)->EnableWindow(TRUE);
						GetDlgItem(IDC_FL3)->EnableWindow(TRUE);
						GetDlgItem(IDC_FR1)->EnableWindow(TRUE);
						GetDlgItem(IDC_FR2)->EnableWindow(TRUE);
						GetDlgItem(IDC_FR3)->EnableWindow(TRUE);
						GetDlgItem(IDC_COMBO1)->EnableWindow(TRUE);
						GetDlgItem(IDC_ADR)->EnableWindow(TRUE);
						GetDlgItem(IDC_BUTTON5)->EnableWindow(TRUE);
						GetDlgItem(IDC_BUTTON7)->EnableWindow(TRUE);
						GetMsg();
						count=0;
					}
					return;
				}
			if(EFIN[2]==TRUE)
				if(count<3){
					CString num;
					num.Format(_T("%.3d"),getLines());
					name+=num+_T("_L3_");
					num.Format(_T("%d"),count);
					name+=num;
					name=name+Type;

					int n = name.GetLength(); //���ַ����㣬str�ĳ���
					int len = WideCharToMultiByte(CP_ACP,0,name,n,NULL,0,NULL,NULL);//��Byte����str����
					char*temp = new char[len+1];//���ֽ�Ϊ��λ
					WideCharToMultiByte(CP_ACP,0,name,n,temp,len,NULL,NULL);//���ֽ�ת��Ϊ���ֽڱ���
					temp[len] = '\0';
					cvSaveImage(temp,dst);
					delete[] temp;
					MessageBox(_T("�ѱ��棺  ��������ָ")+num+_T("/3"));
					count++;
					return;
				}else{
					CString num;
					num.Format(_T("%.3d"),getLines());
					name+=num+_T("_L3_");
					num.Format(_T("%d"),count);
					name+=num;
					name=name+Type;

					int n = name.GetLength(); //���ַ����㣬str�ĳ���
					int len = WideCharToMultiByte(CP_ACP,0,name,n,NULL,0,NULL,NULL);//��Byte����str����
					char*temp = new char[len+1];//���ֽ�Ϊ��λ
					WideCharToMultiByte(CP_ACP,0,name,n,temp,len,NULL,NULL);//���ֽ�ת��Ϊ���ֽڱ���
					temp[len] = '\0';
					cvSaveImage(temp,dst);
					delete[] temp;
					MessageBox(_T("�ѱ��棺  ��������ָ")+num+_T("/3"));
					count=1;
					EFIN[2]=FALSE;
					if(!EFIN[0]&&!EFIN[1]&&!EFIN[2]&&!EFIN[3]&&!EFIN[4]&&!EFIN[5]){
						GetDlgItem(IDC_THREE)->EnableWindow(TRUE);
						GetDlgItem(IDC_SIX)->EnableWindow(TRUE);
						GetDlgItem(IDC_FL1)->EnableWindow(TRUE);
						GetDlgItem(IDC_FL2)->EnableWindow(TRUE);
						GetDlgItem(IDC_FL3)->EnableWindow(TRUE);
						GetDlgItem(IDC_FR1)->EnableWindow(TRUE);
						GetDlgItem(IDC_FR2)->EnableWindow(TRUE);
						GetDlgItem(IDC_FR3)->EnableWindow(TRUE);
						GetDlgItem(IDC_COMBO1)->EnableWindow(TRUE);
						GetDlgItem(IDC_ADR)->EnableWindow(TRUE);
						GetDlgItem(IDC_BUTTON5)->EnableWindow(TRUE);
						GetDlgItem(IDC_BUTTON7)->EnableWindow(TRUE);
						GetMsg();
						count=0;
					}
					return;
				}
			if(EFIN[3]==TRUE)
				if(count<3){
					CString num;
					num.Format(_T("%.3d"),getLines());
					name+=num+_T("_R1_");
					num.Format(_T("%d"),count);
					name+=num;
					name=name+Type;

					int n = name.GetLength(); //���ַ����㣬str�ĳ���
					int len = WideCharToMultiByte(CP_ACP,0,name,n,NULL,0,NULL,NULL);//��Byte����str����
					char*temp = new char[len+1];//���ֽ�Ϊ��λ
					WideCharToMultiByte(CP_ACP,0,name,n,temp,len,NULL,NULL);//���ֽ�ת��Ϊ���ֽڱ���
					temp[len] = '\0';
					cvSaveImage(temp,dst);
					delete[] temp;
					MessageBox(_T("�ѱ��棺  ����ʳָ")+num+_T("/3"));
					count++;
					return;
				}else{
					CString num;
					num.Format(_T("%.3d"),getLines());
					name+=num+_T("_R1_");
					num.Format(_T("%d"),count);
					name+=num;
					name=name+Type;

					int n = name.GetLength(); //���ַ����㣬str�ĳ���
					int len = WideCharToMultiByte(CP_ACP,0,name,n,NULL,0,NULL,NULL);//��Byte����str����
					char*temp = new char[len+1];//���ֽ�Ϊ��λ
					WideCharToMultiByte(CP_ACP,0,name,n,temp,len,NULL,NULL);//���ֽ�ת��Ϊ���ֽڱ���
					temp[len] = '\0';
					cvSaveImage(temp,dst);
					delete[] temp;
					MessageBox(_T("�ѱ��棺  ����ʳָ")+num+_T("/3"));
					count=1;
					EFIN[3]=FALSE;
					if(!EFIN[0]&&!EFIN[1]&&!EFIN[2]&&!EFIN[3]&&!EFIN[4]&&!EFIN[5]){
						GetDlgItem(IDC_THREE)->EnableWindow(TRUE);
						GetDlgItem(IDC_SIX)->EnableWindow(TRUE);
						GetDlgItem(IDC_FL1)->EnableWindow(TRUE);
						GetDlgItem(IDC_FL2)->EnableWindow(TRUE);
						GetDlgItem(IDC_FL3)->EnableWindow(TRUE);
						GetDlgItem(IDC_FR1)->EnableWindow(TRUE);
						GetDlgItem(IDC_FR2)->EnableWindow(TRUE);
						GetDlgItem(IDC_FR3)->EnableWindow(TRUE);
						GetDlgItem(IDC_COMBO1)->EnableWindow(TRUE);
						GetDlgItem(IDC_ADR)->EnableWindow(TRUE);
						GetDlgItem(IDC_BUTTON5)->EnableWindow(TRUE);
						GetDlgItem(IDC_BUTTON7)->EnableWindow(TRUE);
						GetMsg();
						count=0;
					}
					return;
				}
			if(EFIN[4]==TRUE)
				if(count<3){
					CString num;
					num.Format(_T("%.3d"),getLines());
					name+=num+_T("_R2_");
					num.Format(_T("%d"),count);
					name+=num;
					name=name+Type;

					int n = name.GetLength(); //���ַ����㣬str�ĳ���
					int len = WideCharToMultiByte(CP_ACP,0,name,n,NULL,0,NULL,NULL);//��Byte����str����
					char*temp = new char[len+1];//���ֽ�Ϊ��λ
					WideCharToMultiByte(CP_ACP,0,name,n,temp,len,NULL,NULL);//���ֽ�ת��Ϊ���ֽڱ���
					temp[len] = '\0';
					cvSaveImage(temp,dst);
					delete[] temp;
					MessageBox(_T("�ѱ��棺  ������ָ")+num+_T("/3"));
					count++;
					return;
				}else{
					CString num;
					num.Format(_T("%.3d"),getLines());
					name+=num+_T("_R2_");
					num.Format(_T("%d"),count);
					name+=num;
					name=name+Type;

					int n = name.GetLength(); //���ַ����㣬str�ĳ���
					int len = WideCharToMultiByte(CP_ACP,0,name,n,NULL,0,NULL,NULL);//��Byte����str����
					char*temp = new char[len+1];//���ֽ�Ϊ��λ
					WideCharToMultiByte(CP_ACP,0,name,n,temp,len,NULL,NULL);//���ֽ�ת��Ϊ���ֽڱ���
					temp[len] = '\0';
					cvSaveImage(temp,dst);
					delete[] temp;
					MessageBox(_T("�ѱ��棺  ������ָ")+num+_T("/3"));
					count=1;
					EFIN[4]=FALSE;
					if(!EFIN[0]&&!EFIN[1]&&!EFIN[2]&&!EFIN[3]&&!EFIN[4]&&!EFIN[5]){
						GetDlgItem(IDC_THREE)->EnableWindow(TRUE);
						GetDlgItem(IDC_SIX)->EnableWindow(TRUE);
						GetDlgItem(IDC_FL1)->EnableWindow(TRUE);
						GetDlgItem(IDC_FL2)->EnableWindow(TRUE);
						GetDlgItem(IDC_FL3)->EnableWindow(TRUE);
						GetDlgItem(IDC_FR1)->EnableWindow(TRUE);
						GetDlgItem(IDC_FR2)->EnableWindow(TRUE);
						GetDlgItem(IDC_FR3)->EnableWindow(TRUE);
						GetDlgItem(IDC_COMBO1)->EnableWindow(TRUE);
						GetDlgItem(IDC_ADR)->EnableWindow(TRUE);
						GetDlgItem(IDC_BUTTON5)->EnableWindow(TRUE);
						GetDlgItem(IDC_BUTTON7)->EnableWindow(TRUE);
						GetMsg();
						count=0;
					}
					return;
				}
		if(EFIN[5]==TRUE)
				if(count<3){
					CString num;
					num.Format(_T("%.3d"),getLines());
					name+=num+_T("_R3_");
					num.Format(_T("%d"),count);
					name+=num;
					name=name+Type;

					int n = name.GetLength(); //���ַ����㣬str�ĳ���
					int len = WideCharToMultiByte(CP_ACP,0,name,n,NULL,0,NULL,NULL);//��Byte����str����
					char*temp = new char[len+1];//���ֽ�Ϊ��λ
					WideCharToMultiByte(CP_ACP,0,name,n,temp,len,NULL,NULL);//���ֽ�ת��Ϊ���ֽڱ���
					temp[len] = '\0';
					cvSaveImage(temp,dst);
					delete[] temp;
					MessageBox(_T("�ѱ��棺  ��������ָ")+num+_T("/3"));
					count++;
					return;
				}else{
					CString num;
					num.Format(_T("%.3d"),getLines());
					name+=num+_T("_R3_");
					num.Format(_T("%d"),count);
					name+=num;
					name=name+Type;

					int n = name.GetLength(); //���ַ����㣬str�ĳ���
					int len = WideCharToMultiByte(CP_ACP,0,name,n,NULL,0,NULL,NULL);//��Byte����str����
					char*temp = new char[len+1];//���ֽ�Ϊ��λ
					WideCharToMultiByte(CP_ACP,0,name,n,temp,len,NULL,NULL);//���ֽ�ת��Ϊ���ֽڱ���
					temp[len] = '\0';
					cvSaveImage(temp,dst);
					delete[] temp;
					MessageBox(_T("�ѱ��棺  ��������ָ")+num+_T("/3"));
					count=1;
					EFIN[5]=FALSE;
					if(!EFIN[0]&&!EFIN[1]&&!EFIN[2]&&!EFIN[3]&&!EFIN[4]&&!EFIN[5]){
						GetDlgItem(IDC_THREE)->EnableWindow(TRUE);
						GetDlgItem(IDC_SIX)->EnableWindow(TRUE);
						GetDlgItem(IDC_FL1)->EnableWindow(TRUE);
						GetDlgItem(IDC_FL2)->EnableWindow(TRUE);
						GetDlgItem(IDC_FL3)->EnableWindow(TRUE);
						GetDlgItem(IDC_FR1)->EnableWindow(TRUE);
						GetDlgItem(IDC_FR2)->EnableWindow(TRUE);
						GetDlgItem(IDC_FR3)->EnableWindow(TRUE);
						GetDlgItem(IDC_COMBO1)->EnableWindow(TRUE);
						GetDlgItem(IDC_ADR)->EnableWindow(TRUE);
						GetDlgItem(IDC_BUTTON5)->EnableWindow(TRUE);
						GetDlgItem(IDC_BUTTON7)->EnableWindow(TRUE);
						GetMsg();
						count=0;
					}
					return;
				}
		}else{
			if(EFIN[0]==TRUE)
				if(count<6){
					CString num;
					num.Format(_T("%.3d"),getLines());
					name+=num+_T("_L1_");
					num.Format(_T("%d"),count);
					name+=num;
					name=name+Type;

					int n = name.GetLength(); //���ַ����㣬str�ĳ���
					int len = WideCharToMultiByte(CP_ACP,0,name,n,NULL,0,NULL,NULL);//��Byte����str����
					char*temp = new char[len+1];//���ֽ�Ϊ��λ
					WideCharToMultiByte(CP_ACP,0,name,n,temp,len,NULL,NULL);//���ֽ�ת��Ϊ���ֽڱ���
					temp[len] = '\0';
					cvSaveImage(temp,dst);
					delete[] temp;
					MessageBox(_T("�ѱ��棺  ����ʳָ")+num+_T("/6"));
					count++;
					return;
				}else{
					CString num;
					num.Format(_T("%.3d"),getLines());
					name+=num+_T("_L1_");
					num.Format(_T("%d"),count);
					name+=num;
					name=name+Type;

					int n = name.GetLength(); //���ַ����㣬str�ĳ���
					int len = WideCharToMultiByte(CP_ACP,0,name,n,NULL,0,NULL,NULL);//��Byte����str����
					char*temp = new char[len+1];//���ֽ�Ϊ��λ
					WideCharToMultiByte(CP_ACP,0,name,n,temp,len,NULL,NULL);//���ֽ�ת��Ϊ���ֽڱ���
					temp[len] = '\0';
					cvSaveImage(temp,dst);
					delete[] temp;
					MessageBox(_T("�ѱ��棺  ����ʳָ")+num+_T("/6"));

					count=1;
					EFIN[0]=FALSE;
					if(!EFIN[0]&&!EFIN[1]&&!EFIN[2]&&!EFIN[3]&&!EFIN[4]&&!EFIN[5]){
						GetDlgItem(IDC_THREE)->EnableWindow(TRUE);
						GetDlgItem(IDC_SIX)->EnableWindow(TRUE);
						GetDlgItem(IDC_FL1)->EnableWindow(TRUE);
						GetDlgItem(IDC_FL2)->EnableWindow(TRUE);
						GetDlgItem(IDC_FL3)->EnableWindow(TRUE);
						GetDlgItem(IDC_FR1)->EnableWindow(TRUE);
						GetDlgItem(IDC_FR2)->EnableWindow(TRUE);
						GetDlgItem(IDC_FR3)->EnableWindow(TRUE);
						GetDlgItem(IDC_COMBO1)->EnableWindow(TRUE);
						GetDlgItem(IDC_ADR)->EnableWindow(TRUE);
						GetDlgItem(IDC_BUTTON5)->EnableWindow(TRUE);
						GetDlgItem(IDC_BUTTON7)->EnableWindow(TRUE);
						GetMsg();
						count=0;
					}
					return;
				}
			if(EFIN[1]==TRUE)
				if(count<6){
					CString num;
					num.Format(_T("%.3d"),getLines());
					name+=num+_T("_L2_");
					num.Format(_T("%d"),count);
					name+=num;
					name=name+Type;

					int n = name.GetLength(); //���ַ����㣬str�ĳ���
					int len = WideCharToMultiByte(CP_ACP,0,name,n,NULL,0,NULL,NULL);//��Byte����str����
					char*temp = new char[len+1];//���ֽ�Ϊ��λ
					WideCharToMultiByte(CP_ACP,0,name,n,temp,len,NULL,NULL);//���ֽ�ת��Ϊ���ֽڱ���
					temp[len] = '\0';
					cvSaveImage(temp,dst);
					delete[] temp;
					MessageBox(_T("�ѱ��棺  ������ָ")+num+_T("/6"));
					count++;
					return;
				}else{
					CString num;
					num.Format(_T("%.3d"),getLines());
					name+=num+_T("_L2_");
					num.Format(_T("%d"),count);
					name+=num;
					name=name+Type;

					int n = name.GetLength(); //���ַ����㣬str�ĳ���
					int len = WideCharToMultiByte(CP_ACP,0,name,n,NULL,0,NULL,NULL);//��Byte����str����
					char*temp = new char[len+1];//���ֽ�Ϊ��λ
					WideCharToMultiByte(CP_ACP,0,name,n,temp,len,NULL,NULL);//���ֽ�ת��Ϊ���ֽڱ���
					temp[len] = '\0';
					cvSaveImage(temp,dst);
					delete[] temp;
					MessageBox(_T("�ѱ��棺  ������ָ")+num+_T("/6"));
					count=1;
					EFIN[1]=FALSE;
					if(!EFIN[0]&&!EFIN[1]&&!EFIN[2]&&!EFIN[3]&&!EFIN[4]&&!EFIN[5]){
						GetDlgItem(IDC_THREE)->EnableWindow(TRUE);
						GetDlgItem(IDC_SIX)->EnableWindow(TRUE);
						GetDlgItem(IDC_FL1)->EnableWindow(TRUE);
						GetDlgItem(IDC_FL2)->EnableWindow(TRUE);
						GetDlgItem(IDC_FL3)->EnableWindow(TRUE);
						GetDlgItem(IDC_FR1)->EnableWindow(TRUE);
						GetDlgItem(IDC_FR2)->EnableWindow(TRUE);
						GetDlgItem(IDC_FR3)->EnableWindow(TRUE);
						GetDlgItem(IDC_COMBO1)->EnableWindow(TRUE);
						GetDlgItem(IDC_ADR)->EnableWindow(TRUE);
						GetDlgItem(IDC_BUTTON5)->EnableWindow(TRUE);
						GetDlgItem(IDC_BUTTON7)->EnableWindow(TRUE);
						GetMsg();
						count=0;
					}
					return;
				}
			if(EFIN[2]==TRUE)
				if(count<6){
					CString num;
					num.Format(_T("%.3d"),getLines());
					name+=num+_T("_L3_");
					num.Format(_T("%d"),count);
					name+=num;
					name=name+Type;

					int n = name.GetLength(); //���ַ����㣬str�ĳ���
					int len = WideCharToMultiByte(CP_ACP,0,name,n,NULL,0,NULL,NULL);//��Byte����str����
					char*temp = new char[len+1];//���ֽ�Ϊ��λ
					WideCharToMultiByte(CP_ACP,0,name,n,temp,len,NULL,NULL);//���ֽ�ת��Ϊ���ֽڱ���
					temp[len] = '\0';
					cvSaveImage(temp,dst);
					delete[] temp;
					MessageBox(_T("�ѱ��棺  ��������ָ")+num+_T("/6"));
					count++;
					return;
				}else{
					CString num;
					num.Format(_T("%.3d"),getLines());
					name+=num+_T("_L3_");
					num.Format(_T("%d"),count);
					name+=num;
					name=name+Type;

					int n = name.GetLength(); //���ַ����㣬str�ĳ���
					int len = WideCharToMultiByte(CP_ACP,0,name,n,NULL,0,NULL,NULL);//��Byte����str����
					char*temp = new char[len+1];//���ֽ�Ϊ��λ
					WideCharToMultiByte(CP_ACP,0,name,n,temp,len,NULL,NULL);//���ֽ�ת��Ϊ���ֽڱ���
					temp[len] = '\0';
					cvSaveImage(temp,dst);
					delete[] temp;
					MessageBox(_T("�ѱ��棺  ��������ָ")+num+_T("/6"));
					count=1;
					EFIN[2]=FALSE;
					if(!EFIN[0]&&!EFIN[1]&&!EFIN[2]&&!EFIN[3]&&!EFIN[4]&&!EFIN[5]){
						GetDlgItem(IDC_THREE)->EnableWindow(TRUE);
						GetDlgItem(IDC_SIX)->EnableWindow(TRUE);
						GetDlgItem(IDC_FL1)->EnableWindow(TRUE);
						GetDlgItem(IDC_FL2)->EnableWindow(TRUE);
						GetDlgItem(IDC_FL3)->EnableWindow(TRUE);
						GetDlgItem(IDC_FR1)->EnableWindow(TRUE);
						GetDlgItem(IDC_FR2)->EnableWindow(TRUE);
						GetDlgItem(IDC_FR3)->EnableWindow(TRUE);
						GetDlgItem(IDC_COMBO1)->EnableWindow(TRUE);
						GetDlgItem(IDC_ADR)->EnableWindow(TRUE);
						GetDlgItem(IDC_BUTTON5)->EnableWindow(TRUE);
						GetDlgItem(IDC_BUTTON7)->EnableWindow(TRUE);
						GetMsg();
						count=0;
					}
					return;
				}
			if(EFIN[3]==TRUE)
				if(count<6){
					CString num;
					num.Format(_T("%.3d"),getLines());
					name+=num+_T("_R1_");
					num.Format(_T("%d"),count);
					name+=num;
					name=name+Type;

					int n = name.GetLength(); //���ַ����㣬str�ĳ���
					int len = WideCharToMultiByte(CP_ACP,0,name,n,NULL,0,NULL,NULL);//��Byte����str����
					char*temp = new char[len+1];//���ֽ�Ϊ��λ
					WideCharToMultiByte(CP_ACP,0,name,n,temp,len,NULL,NULL);//���ֽ�ת��Ϊ���ֽڱ���
					temp[len] = '\0';
					cvSaveImage(temp,dst);
					delete[] temp;
					MessageBox(_T("�ѱ��棺  ����ʳָ")+num+_T("/6"));
					count++;
					return;
				}else{
					CString num;
					num.Format(_T("%.3d"),getLines());
					name+=num+_T("_R1_");
					num.Format(_T("%d"),count);
					name+=num;
					name=name+Type;

					int n = name.GetLength(); //���ַ����㣬str�ĳ���
					int len = WideCharToMultiByte(CP_ACP,0,name,n,NULL,0,NULL,NULL);//��Byte����str����
					char*temp = new char[len+1];//���ֽ�Ϊ��λ
					WideCharToMultiByte(CP_ACP,0,name,n,temp,len,NULL,NULL);//���ֽ�ת��Ϊ���ֽڱ���
					temp[len] = '\0';
					cvSaveImage(temp,dst);
					delete[] temp;
					MessageBox(_T("�ѱ��棺  ����ʳָ")+num+_T("/3"));
					count=1;
					EFIN[3]=FALSE;
					if(!EFIN[0]&&!EFIN[1]&&!EFIN[2]&&!EFIN[3]&&!EFIN[4]&&!EFIN[5]){
						GetDlgItem(IDC_THREE)->EnableWindow(TRUE);
						GetDlgItem(IDC_SIX)->EnableWindow(TRUE);
						GetDlgItem(IDC_FL1)->EnableWindow(TRUE);
						GetDlgItem(IDC_FL2)->EnableWindow(TRUE);
						GetDlgItem(IDC_FL3)->EnableWindow(TRUE);
						GetDlgItem(IDC_FR1)->EnableWindow(TRUE);
						GetDlgItem(IDC_FR2)->EnableWindow(TRUE);
						GetDlgItem(IDC_FR3)->EnableWindow(TRUE);
						GetDlgItem(IDC_COMBO1)->EnableWindow(TRUE);
						GetDlgItem(IDC_ADR)->EnableWindow(TRUE);
						GetDlgItem(IDC_BUTTON5)->EnableWindow(TRUE);
						GetDlgItem(IDC_BUTTON7)->EnableWindow(TRUE);
						GetMsg();
						count=0;
					}
					return;
				}
			if(EFIN[4]==TRUE)
				if(count<6){
					CString num;
					num.Format(_T("%.3d"),getLines());
					name+=num+_T("_R2_");
					num.Format(_T("%d"),count);
					name+=num;
					name=name+Type;

					int n = name.GetLength(); //���ַ����㣬str�ĳ���
					int len = WideCharToMultiByte(CP_ACP,0,name,n,NULL,0,NULL,NULL);//��Byte����str����
					char*temp = new char[len+1];//���ֽ�Ϊ��λ
					WideCharToMultiByte(CP_ACP,0,name,n,temp,len,NULL,NULL);//���ֽ�ת��Ϊ���ֽڱ���
					temp[len] = '\0';
					cvSaveImage(temp,dst);
					delete[] temp;
					MessageBox(_T("�ѱ��棺  ������ָ")+num+_T("/6"));
					count++;
					return;
				}else{
					CString num;
					num.Format(_T("%.3d"),getLines());
					name+=num+_T("_R2_");
					num.Format(_T("%d"),count);
					name+=num;
					name=name+Type;

					int n = name.GetLength(); //���ַ����㣬str�ĳ���
					int len = WideCharToMultiByte(CP_ACP,0,name,n,NULL,0,NULL,NULL);//��Byte����str����
					char*temp = new char[len+1];//���ֽ�Ϊ��λ
					WideCharToMultiByte(CP_ACP,0,name,n,temp,len,NULL,NULL);//���ֽ�ת��Ϊ���ֽڱ���
					temp[len] = '\0';
					cvSaveImage(temp,dst);
					delete[] temp;
					MessageBox(_T("�ѱ��棺  ������ָ")+num+_T("/6"));
					count=1;
					EFIN[4]=FALSE;
					if(!EFIN[0]&&!EFIN[1]&&!EFIN[2]&&!EFIN[3]&&!EFIN[4]&&!EFIN[5]){
						GetDlgItem(IDC_THREE)->EnableWindow(TRUE);
						GetDlgItem(IDC_SIX)->EnableWindow(TRUE);
						GetDlgItem(IDC_FL1)->EnableWindow(TRUE);
						GetDlgItem(IDC_FL2)->EnableWindow(TRUE);
						GetDlgItem(IDC_FL3)->EnableWindow(TRUE);
						GetDlgItem(IDC_FR1)->EnableWindow(TRUE);
						GetDlgItem(IDC_FR2)->EnableWindow(TRUE);
						GetDlgItem(IDC_FR3)->EnableWindow(TRUE);
						GetDlgItem(IDC_COMBO1)->EnableWindow(TRUE);
						GetDlgItem(IDC_ADR)->EnableWindow(TRUE);
						GetDlgItem(IDC_BUTTON5)->EnableWindow(TRUE);
						GetDlgItem(IDC_BUTTON7)->EnableWindow(TRUE);
						GetMsg();
						count=0;
					}
					return;
				}
		if(EFIN[5]==TRUE)
				if(count<6){
					CString num;
					num.Format(_T("%.3d"),getLines());
					name+=num+_T("_R3_");
					num.Format(_T("%d"),count);
					name+=num;
					name=name+Type;

					int n = name.GetLength(); //���ַ����㣬str�ĳ���
					int len = WideCharToMultiByte(CP_ACP,0,name,n,NULL,0,NULL,NULL);//��Byte����str����
					char*temp = new char[len+1];//���ֽ�Ϊ��λ
					WideCharToMultiByte(CP_ACP,0,name,n,temp,len,NULL,NULL);//���ֽ�ת��Ϊ���ֽڱ���
					temp[len] = '\0';
					cvSaveImage(temp,dst);
					delete[] temp;
					MessageBox(_T("�ѱ��棺  ��������ָ")+num+_T("/6"));
					count++;
					return;
				}else{
					CString num;
					num.Format(_T("%.3d"),getLines());
					name+=num+_T("_R3_");
					num.Format(_T("%d"),count);
					name+=num;
					name=name+Type;

					int n = name.GetLength(); //���ַ����㣬str�ĳ���
					int len = WideCharToMultiByte(CP_ACP,0,name,n,NULL,0,NULL,NULL);//��Byte����str����
					char*temp = new char[len+1];//���ֽ�Ϊ��λ
					WideCharToMultiByte(CP_ACP,0,name,n,temp,len,NULL,NULL);//���ֽ�ת��Ϊ���ֽڱ���
					temp[len] = '\0';
					cvSaveImage(temp,dst);
					delete[] temp;
					MessageBox(_T("�ѱ��棺  ��������ָ")+num+_T("/6"));
					count=1;
					EFIN[5]=FALSE;
					if(!EFIN[0]&&!EFIN[1]&&!EFIN[2]&&!EFIN[3]&&!EFIN[4]&&!EFIN[5]){
						GetDlgItem(IDC_THREE)->EnableWindow(TRUE);
						GetDlgItem(IDC_SIX)->EnableWindow(TRUE);
						GetDlgItem(IDC_FL1)->EnableWindow(TRUE);
						GetDlgItem(IDC_FL2)->EnableWindow(TRUE);
						GetDlgItem(IDC_FL3)->EnableWindow(TRUE);
						GetDlgItem(IDC_FR1)->EnableWindow(TRUE);
						GetDlgItem(IDC_FR2)->EnableWindow(TRUE);
						GetDlgItem(IDC_FR3)->EnableWindow(TRUE);
						GetDlgItem(IDC_COMBO1)->EnableWindow(TRUE);
						GetDlgItem(IDC_ADR)->EnableWindow(TRUE);
						GetDlgItem(IDC_BUTTON5)->EnableWindow(TRUE);
						GetDlgItem(IDC_BUTTON7)->EnableWindow(TRUE);
						GetMsg();
						count=0;
					}
					return;
				}
		
		
		
		}
	
	
	
	}
	
}