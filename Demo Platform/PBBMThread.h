#pragma once



// PBBMThread

class PBBMThread : public CWinThread
{
	DECLARE_DYNCREATE(PBBMThread)

protected:
	PBBMThread();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~PBBMThread();

public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

protected:
	DECLARE_MESSAGE_MAP()
};


