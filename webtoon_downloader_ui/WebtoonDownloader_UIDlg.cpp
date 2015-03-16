
// WebtoonDownloader_UIDlg.cpp : ���� ����
//

#include "stdafx.h"
#include "WebtoonDownloader_UI.h"
#include "WebtoonDownloader_UIDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CWebtoonDownloader_UIDlg ��ȭ ����


CWebtoonDownloader_UIDlg::CWebtoonDownloader_UIDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CWebtoonDownloader_UIDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_currentType = 0;
}

void CWebtoonDownloader_UIDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CB_TYPE, m_cbType);
	DDX_Control(pDX, IDC_ED_EP1, m_edEpisode1);
	DDX_Control(pDX, IDC_ED_EP2, m_edEpisode2);
	DDX_Control(pDX, IDC_ED_TITLEID, m_edTitleID);
	DDX_Control(pDX, IDC_ED_RSSURL, m_edRssUrl);
	DDX_Control(pDX, IDC_ED_TITLE, m_edTitle);
}

BEGIN_MESSAGE_MAP(CWebtoonDownloader_UIDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BT_START, &CWebtoonDownloader_UIDlg::OnBnClickedBtStart)
	ON_CBN_SELCHANGE(IDC_CB_TYPE, &CWebtoonDownloader_UIDlg::OnCbnSelchangeCbType)
	ON_BN_CLICKED(IDC_BT_USAGE, &CWebtoonDownloader_UIDlg::OnBnClickedBtUsage)
END_MESSAGE_MAP()


// CWebtoonDownloader_UIDlg �޽��� ó����

BOOL CWebtoonDownloader_UIDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// �� ��ȭ ������ �������� �����մϴ�. ���� ���α׷��� �� â�� ��ȭ ���ڰ� �ƴ� ��쿡��
	//  �����ӿ�ũ�� �� �۾��� �ڵ����� �����մϴ�.
	SetIcon(m_hIcon, TRUE);			// ū �������� �����մϴ�.
	SetIcon(m_hIcon, FALSE);		// ���� �������� �����մϴ�.

	m_cbType.InsertString(0, _T("Naver Webtoon"));
	m_cbType.InsertString(1, _T("Naver Best Challenge - BETA"));
	m_cbType.InsertString(2, _T("Daum Webtoon"));	
	m_cbType.SetCurSel(0);

	m_edEpisode1.SetWindowTextW(_T("1"));
	m_edEpisode2.SetWindowTextW(_T("3"));

	CheckDlgButton(IDC_CK_MERGE, TRUE);
	CheckDlgButton(IDC_CK_PNG, FALSE);

	m_edRssUrl.EnableWindow(FALSE);

	return TRUE;  // ��Ŀ���� ��Ʈ�ѿ� �������� ������ TRUE�� ��ȯ�մϴ�.
}

// ��ȭ ���ڿ� �ּ�ȭ ���߸� �߰��� ��� �������� �׸�����
//  �Ʒ� �ڵ尡 �ʿ��մϴ�. ����/�� ���� ����ϴ� MFC ���� ���α׷��� ��쿡��
//  �����ӿ�ũ���� �� �۾��� �ڵ����� �����մϴ�.

void CWebtoonDownloader_UIDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // �׸��⸦ ���� ����̽� ���ؽ�Ʈ

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Ŭ���̾�Ʈ �簢������ �������� ����� ����ϴ�.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// �������� �׸��ϴ�.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// ����ڰ� �ּ�ȭ�� â�� ���� ���ȿ� Ŀ���� ǥ�õǵ��� �ý��ۿ���
//  �� �Լ��� ȣ���մϴ�.
HCURSOR CWebtoonDownloader_UIDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CWebtoonDownloader_UIDlg::OnBnClickedBtStart()
{
	CString ep1, ep2, title, titleid, rssurl, param;

	m_edEpisode1.GetWindowText(ep1);
	m_edEpisode2.GetWindowText(ep2);

	ep1 = ep1.Trim();
	ep2 = ep2.Trim();

	if (ep1.GetLength() == 0 || ep2.GetLength() == 0) {
		MessageBox(_T("Input episode range"), _T("Warning"), MB_OK | MB_ICONWARNING);
		return;
	}

	BOOL isMerge = IsDlgButtonChecked(IDC_CK_MERGE);
	BOOL isPng = IsDlgButtonChecked(IDC_CK_PNG);
	switch (m_currentType) {
		case 0: // naver
		case 1:
			m_edTitle.GetWindowText(title);
			m_edTitleID.GetWindowText(titleid);
			title = title.Trim();
			titleid = titleid.Trim();
			if (title.GetLength() == 0 || titleid.GetLength() == 0) {
				MessageBox(_T("Input Title or TitleID"), _T("Warning"), MB_OK | MB_ICONWARNING);
				return;
			}
			param.Format(_T("-e %s-%s -t %s -n %s -w naver"), ep1, ep2, titleid, title);
			if (m_currentType == 1)
				param += " -b";
			break;
		case 2: // daum
			m_edRssUrl.GetWindowText(rssurl);
			rssurl = rssurl.Trim();
			if (rssurl.GetLength() == 0) {
				MessageBox(_T("Input Rss Url"), _T("Warning"), MB_OK | MB_ICONWARNING);
				return;
			}
			param.Format(_T("-e %s-%s -r %s -w daum"), ep1, ep2, rssurl);
			break;
	}

	if (isMerge)
		param += " -m";
	if (isPng)
		param += " -p";

	ExecuteDownload(_T(".\\downloader.exe"), param);
}

void CWebtoonDownloader_UIDlg::OnCbnSelchangeCbType()
{
	m_currentType = m_cbType.GetCurSel();

	switch (m_currentType) {
		case 0: // naver
		case 1: // naver best challenge
			m_edTitle.EnableWindow(TRUE);
			m_edTitleID.EnableWindow(TRUE);
			m_edRssUrl.EnableWindow(FALSE);
			break;
		case 2: // daum
			m_edTitle.EnableWindow(FALSE);
			m_edTitleID.EnableWindow(FALSE);
			m_edRssUrl.EnableWindow(TRUE);
			break;
	}
}

void CWebtoonDownloader_UIDlg::OnBnClickedBtUsage()
{
	ShellExecute(NULL, _T("open"), _T("http://blog.naver.com/liush79/60191630812"), _T(""), _T(""), SW_SHOW);	
}

void CWebtoonDownloader_UIDlg::ExecuteDownload(CString cmd, CString param)
{
	SHELLEXECUTEINFO si = {0,};

	si.cbSize = sizeof(SHELLEXECUTEINFO);
	si.hwnd = NULL;
	si.fMask = SEE_MASK_FLAG_DDEWAIT;
	si.lpVerb = _T("runas");
	si.lpFile = cmd;
	si.lpParameters = param;
	si.nShow = SW_SHOWNORMAL;
	si.lpDirectory = 0;

	ShellExecuteEx(&si);
}
BOOL CWebtoonDownloader_UIDlg::PreTranslateMessage(MSG* pMsg)
{
	switch (pMsg->message)
	{
	case WM_KEYDOWN:
		if (pMsg->wParam == VK_ESCAPE || pMsg->wParam == VK_RETURN)
			return FALSE;
		break;
	default:
		break;
	}

	return CDialog::PreTranslateMessage(pMsg);
}
