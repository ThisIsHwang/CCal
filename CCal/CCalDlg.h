
// CCalDlg.h: 헤더 파일
//

#pragma once

#define PLUS 1
#define MINUS 2
#define MULTI 3
#define DIVIDE 4
#define EQUAL 5



// CCCalDlg 대화 상자
class CCCalDlg : public CDialogEx
{
// 생성입니다.
public:
	bool isDotClicked;
	long long int mCurValInt;
	long double mPreVal;
	long double mCurValReal;

	int mOP;
	bool mAfterDot;
	bool mIsMinus;
	int mPreRealNumCnt;
	int mRealNumCnt;
	CCCalDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CCAL_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
    afx_msg void OnEnChangeEdit1();

    afx_msg void OnBnClicked1();
	void PushNum(long long int v);
	afx_msg void OnBnClicked2();
	afx_msg void OnBnClicked3();
	afx_msg void OnBnClicked4();
	afx_msg void OnBnClicked5();
	afx_msg void OnBnClicked6();
	afx_msg void OnBnClicked7();
	afx_msg void OnBnClicked8();
	afx_msg void OnBnClicked9();
	afx_msg void OnBnClicked0();
	afx_msg void OnBnClickedPlus();
	void CCCalDlg::CalOP(int);
	afx_msg void OnBnClickedMinus();
	afx_msg void OnBnClickedMulti();
	afx_msg void OnBnClickedDivide();
	afx_msg void OnBnClickedBackspace();
	afx_msg void OnBnClickedClear();
	afx_msg void OnBnClickedEqual();
	afx_msg void OnBnClickedDot();
	int GetDotNum(long double);
};


