
// CCalDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "CCal.h"
#include "CCalDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CCCalDlg 대화 상자



CCCalDlg::CCCalDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CCAL_DIALOG, pParent)
{
	mCurValInt = 0;
	mPreVal = 0;
	mPreRealNumCnt = 0;
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCCalDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CCCalDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_1, &CCCalDlg::OnBnClicked1)
	ON_BN_CLICKED(IDC_2, &CCCalDlg::OnBnClicked2)
	ON_BN_CLICKED(IDC_3, &CCCalDlg::OnBnClicked3)
	ON_BN_CLICKED(IDC_4, &CCCalDlg::OnBnClicked4)
	ON_BN_CLICKED(IDC_5, &CCCalDlg::OnBnClicked5)
	ON_BN_CLICKED(IDC_6, &CCCalDlg::OnBnClicked6)
	ON_BN_CLICKED(IDC_7, &CCCalDlg::OnBnClicked7)
	ON_BN_CLICKED(IDC_8, &CCCalDlg::OnBnClicked8)
	ON_BN_CLICKED(IDC_9, &CCCalDlg::OnBnClicked9)
	ON_BN_CLICKED(IDC_0, &CCCalDlg::OnBnClicked0)
	ON_BN_CLICKED(IDC_PLUS, &CCCalDlg::OnBnClickedPlus)
	ON_BN_CLICKED(IDC_MINUS, &CCCalDlg::OnBnClickedMinus)
	ON_BN_CLICKED(IDC_MULTI, &CCCalDlg::OnBnClickedMulti)
	ON_BN_CLICKED(IDC_DIVIDE, &CCCalDlg::OnBnClickedDivide)
    ON_BN_CLICKED(IDC_BACKSPACE, &CCCalDlg::OnBnClickedBackspace)
	ON_BN_CLICKED(IDC_CLEAR, &CCCalDlg::OnBnClickedClear)
	ON_BN_CLICKED(IDC_EQUAL, &CCCalDlg::OnBnClickedEqual)
	ON_BN_CLICKED(IDC_DOT, &CCCalDlg::OnBnClickedDot)
END_MESSAGE_MAP()


// CCCalDlg 메시지 처리기

BOOL CCCalDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
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

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.
	mCurValInt = 0;
	mCurValReal = 0.0;
	mPreVal = 0.0;
	mOP = PLUS;
	mAfterDot = false;
	mIsMinus = false;
	mCurRealNumCnt = 0;
	mPreRealNumCnt = 0;
	SetDlgItemTextW(IDC_RESULT, L"0");
	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CCCalDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CCCalDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CCCalDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CCCalDlg::OnEnChangeEdit1()
{
    // TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
    // CDialogEx::OnInitDialog() 함수를 재지정 
    //하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
    // 이 알림 메시지를 보내지 않습니다.

    // TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CCCalDlg::OnBnClicked1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	PushNum(1);
}

void CCCalDlg::OnBnClicked2()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	PushNum(2);
}


void CCCalDlg::OnBnClicked3()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	PushNum(3);
}


void CCCalDlg::OnBnClicked4()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	PushNum(4);
}


void CCCalDlg::OnBnClicked5()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	PushNum(5);
}


void CCCalDlg::OnBnClicked6()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	PushNum(6);
}


void CCCalDlg::OnBnClicked7()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	PushNum(7);
}


void CCCalDlg::OnBnClicked8()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	PushNum(8);
}


void CCCalDlg::OnBnClicked9()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	PushNum(9);
}


void CCCalDlg::OnBnClicked0()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	PushNum(0);
}

void CCCalDlg::OnBnClickedPlus()
{
	CalOP(PLUS);
}

void CCCalDlg::OnBnClickedMinus()
{	
	if (mAfterDot == false && mCurValInt == 0 && mCurValReal == 0) {
		mIsMinus = true;
		SetDlgItemTextW(IDC_RESULT, L"-0");
		return;
	}
	
	CalOP(MINUS);
}

void CCCalDlg::OnBnClickedMulti()
{
	CalOP(MULTI);
}


void CCCalDlg::OnBnClickedDivide()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CalOP(DIVIDE);
}

void CCCalDlg::OnBnClickedBackspace()
{

    // TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (mCurValInt == 0 && mCurValReal == 0 && mCurRealNumCnt == 0) return;
	CString s, s2;
	if (mCurRealNumCnt == 0) {
		mCurValInt = mCurValInt / 10;
		mAfterDot = false;
	}
	else
	{
		int temp = (int)(mCurValReal * pow(10, mCurRealNumCnt));
		mCurValReal = mCurValReal - temp % 10 * pow(10, -mCurRealNumCnt);
		mCurRealNumCnt--;
	}
		
	long double temp = mCurValInt + mCurValReal;
	
	s2.Format(L"%%.%dlf", mCurRealNumCnt);
	
	s.Format(s2, temp);
	SetDlgItemTextW(IDC_RESULT, s);
}

void CCCalDlg::CalOP(int op) {
	CString s, s2;
	
	switch (mOP) {
	case PLUS:
		mPreVal = mPreVal + mCurValInt + mCurValReal;
		break;
	case MINUS:
		mPreVal = mPreVal - (mCurValInt + mCurValReal);
		break;
	case MULTI:
		mPreVal = mPreVal * (mCurValInt + mCurValReal);
		break;
	case DIVIDE:
		mPreVal = mPreVal / (mCurValInt + mCurValReal);
		break;
	case EQUAL:
		break;
	}
	mOP = op; 

	while ((long long)(mPreVal * pow(10, mPreRealNumCnt + 1)) % 10 != 0) {
		if (mPreRealNumCnt == 16)
			break;
		mPreRealNumCnt++;
	}
	while ((long long)(mPreVal * pow(10, mPreRealNumCnt)) % 10 == 0) {
		if (mPreRealNumCnt == 0) {
			break;
		}
		mPreRealNumCnt--;
	}
	
	s2.Format(L"%%.%dlf", mPreRealNumCnt);
	s.Format(s2, mPreVal);
	
	SetDlgItemTextW(IDC_RESULT, s);

	mAfterDot = false;
	mIsMinus = false;
	mCurValInt = 0;
	mCurValReal = 0.0;
	mCurRealNumCnt = 0;
}


void CCCalDlg::PushNum(long long int v) {
	if (mOP == EQUAL) {
		mPreVal = 0;
		mOP = PLUS;
	}
	if (!mIsMinus) {
		if (!mAfterDot) {
			mCurValInt = mCurValInt * 10 + v;
		}
		else {
			mCurRealNumCnt++;
			mCurValReal = mCurValReal + v * pow(10, -(mCurRealNumCnt));
		}
	}
	else {
		if (!mAfterDot) {
			mCurValInt = mCurValInt * 10 - v;
			/*SetDlgItemTextW(IDC_RESULT, L"-0");
			return;*/
		}
		else {
			mCurRealNumCnt++;
			mCurValReal = mCurValReal - v * pow(10, -(mCurRealNumCnt));
		}
	}
	
	if (mOP == MULTI) {
		mPreRealNumCnt = mPreRealNumCnt + mCurRealNumCnt;
	}else if (mPreRealNumCnt < mCurRealNumCnt) {
		mPreRealNumCnt = mCurRealNumCnt;
	}
	
	long double temp;
	
	temp = mCurValInt + mCurValReal;
	
	CString s, s2;
	s2.Format(L"%%.%dlf", mCurRealNumCnt);
	s.Format(s2, temp);
	SetDlgItemTextW(IDC_RESULT, s);
}



void CCCalDlg::OnBnClickedClear()
{
	mCurValInt = mCurValReal = mPreVal = 0.0;
	mOP = PLUS;
	mAfterDot = false;
	mIsMinus = false;
	mPreRealNumCnt = 0;
	mCurRealNumCnt = 0;
	SetDlgItemTextW(IDC_RESULT, L"0");
}


void CCCalDlg::OnBnClickedEqual()
{
	CalOP(EQUAL);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CCCalDlg::OnBnClickedDot()
{

	long double temp;
	temp = mCurValInt + mCurValReal;
	CString s, s2;
	s2.Format(L"%%.%dlf", mCurRealNumCnt);
	s.Format(s2, temp);
	if(!mAfterDot)
		SetDlgItemTextW(IDC_RESULT, s + L".");
	if(mIsMinus && mCurValInt ==0 && mCurValReal == 0){
		SetDlgItemTextW(IDC_RESULT, L"-0.");
	}
	mAfterDot = true;
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}

int CCCalDlg::GetDotNum(long double v)
{
	int t;
	int cnt = 0;
	t = (int)v;
	v = v - t;
	while (v != 0) {
		cnt++;
		v = v * 10;
		t = (int)v;
		v = v - t;
	}
	return cnt;
}
