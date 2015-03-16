
// WebtoonDownloader_UIDlg.h : ��� ����
//

#pragma once
#include "afxwin.h"


// CWebtoonDownloader_UIDlg ��ȭ ����
class CWebtoonDownloader_UIDlg : public CDialog
{
// �����Դϴ�.
public:
	CWebtoonDownloader_UIDlg(CWnd* pParent = NULL);	// ǥ�� �������Դϴ�.

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_WEBTOONDOWNLOADER_UI_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �����Դϴ�.


// �����Դϴ�.
private:
	CComboBox m_cbType;
	CEdit m_edEpisode1;
	CEdit m_edEpisode2;
	CEdit m_edTitle;
	CEdit m_edTitleID;
	CEdit m_edRssUrl;
	int m_currentType;

	void ExecuteDownload(CString cmd, CString param);

protected:
	HICON m_hIcon;

	// ������ �޽��� �� �Լ�
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnBnClickedBtStart();
	afx_msg void OnCbnSelchangeCbType();
	afx_msg void OnBnClickedBtUsage();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};
