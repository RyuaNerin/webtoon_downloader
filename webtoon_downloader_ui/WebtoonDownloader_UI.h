
// WebtoonDownloader_UI.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.


// CWebtoonDownloader_UIApp:
// �� Ŭ������ ������ ���ؼ��� WebtoonDownloader_UI.cpp�� �����Ͻʽÿ�.
//

class CWebtoonDownloader_UIApp : public CWinAppEx
{
public:
	CWebtoonDownloader_UIApp();

// �������Դϴ�.
	public:
	virtual BOOL InitInstance();

// �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};

extern CWebtoonDownloader_UIApp theApp;