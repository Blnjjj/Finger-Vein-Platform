// PBBMThread.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Dialog.h"
#include "PBBMThread.h"


// PBBMThread

IMPLEMENT_DYNCREATE(PBBMThread, CWinThread)

PBBMThread::PBBMThread()
{
}

PBBMThread::~PBBMThread()
{
}

BOOL PBBMThread::InitInstance()
{
	// TODO: �ڴ�ִ���������̳߳�ʼ��
	return TRUE;
}

int PBBMThread::ExitInstance()
{
	// TODO: �ڴ�ִ���������߳�����
	return CWinThread::ExitInstance();
}

BEGIN_MESSAGE_MAP(PBBMThread, CWinThread)
END_MESSAGE_MAP()


// PBBMThread ��Ϣ�������
