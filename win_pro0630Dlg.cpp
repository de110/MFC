
// win_pro0630Dlg.cpp: 구현 파일
//

#include "stdafx.h"
#include "win_pro0630.h"
#include "win_pro0630Dlg.h"
#include "afxdialogex.h"

#include <iostream>
#include "XLAutomation.h"
#include "XLEzAutomation.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 추가 코드
int num=4;
struct lecture {
	CString name;
	int val;
	CString time;
	CString day;
	int day_int;
	CString field;
	//int count;
	CString grade;
	
};
lecture lec[4];

/////////////////////////////


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


// Cwinpro0630Dlg 대화 상자



Cwinpro0630Dlg::Cwinpro0630Dlg(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_WIN_PRO0630_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void Cwinpro0630Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CUSTOM1, m_Grid);
	DDX_Control(pDX, IDC_EDIT1, m_credit);
	DDX_Control(pDX, IDC_COMBO1, m_combobox);
	DDX_Control(pDX, IDC_EDIT3, m_edit_com);
	DDX_Control(pDX, IDC_EDIT8, m_remain);
	DDX_Control(pDX, IDC_EDIT4, m_rating);
	DDX_Control(pDX, IDC_EDIT5, m_major);
	DDX_Control(pDX, IDC_EDIT_TARGET, m_edit_target);
	DDX_Control(pDX, IDC_EDIT_REQUIRE, m_require);
}

BEGIN_MESSAGE_MAP(Cwinpro0630Dlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_CBN_SELCHANGE(IDC_COMBO1, &Cwinpro0630Dlg::OnSelchangeCombo1)
	ON_BN_CLICKED(IDC_BUTTON1, &Cwinpro0630Dlg::OnClickedButton1)
END_MESSAGE_MAP()
CString v[7];
// Cwinpro0630Dlg 메시지 처리기

BOOL Cwinpro0630Dlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
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

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.

	// excel -> database load

	CXLEzAutomation dataexcel(FALSE); //처리 과정 보이지 않음
	dataexcel.OpenExcelFile(_T("D:\\win_pro0630\\DataBase2.xlsx")); //엑셀 파일 열기

	for (int j = 0; j < num; j++) {
		dataexcel.GetCellValue(3, j + 2);
	}


	for (int i = 0; i < num; i++) {
		lec[i].name = dataexcel.GetCellValue(1, i + 2);
		lec[i].time = dataexcel.GetCellValue(2, i + 2).Mid(1);
		lec[i].day = dataexcel.GetCellValue(2, i + 2).Mid(0, 1);
		lec[i].field = dataexcel.GetCellValue(3, i + 2);
		lec[i].val = _ttoi(dataexcel.GetCellValue(4, i + 2));
		lec[i].grade = dataexcel.GetCellValue(6, i + 2);
		all_val += lec[i].val;
	}
	for (int idx = 0; idx < num; idx++) {
		if (lec[idx].field == "교양선택")
			slib_val += lec[idx].val;
		else if (lec[idx].field == "교양필수")
			elib_val += lec[idx].val;
		else if (lec[idx].field == "일반선택")
			gen_val += lec[idx].val;
		else if (lec[idx].field == "전공선택")
			smajor_val += lec[idx].val;
		else if (lec[idx].field == "전공심화")
			imajor_val += lec[idx].val;
	}
	GetDlgItem(IDC_CUSTOM1)->MoveWindow(1, 50, 750, 550); //시간표 위치 지정

	timetable();

	// Make cell 1,1 read-only
	m_Grid.SetItemState(1, 1, m_Grid.GetItemState(1, 1) | GVIS_READONLY);
	m_Grid.SetRowHeight(0, 2 * m_Grid.GetRowHeight(0) / 2);
	
	for(int i=0;i<10;i++)
		m_Grid.SetRowHeight(i, 80);
	for(int i=0;i<7;i++)
		m_Grid.SetColumnWidth(i, 100);

	dataexcel.ReleaseExcel();

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void Cwinpro0630Dlg::timetable()
{
	int m_nFixRows = 1;
	int m_nFixCols = 1;

	m_Grid.SetTextBkColor(RGB(255, 255, 255)); //배경색 = 흰색
	m_Grid.EnableScrollBar(ESB_ENABLE_BOTH, TRUE); //스크롤바 사용

	m_Grid.SetRowCount(10); //행 길이
	m_Grid.SetColumnCount(7); //열 길이
	m_Grid.SetFixedRowCount(m_nFixRows); 
	m_Grid.SetFixedColumnCount(1); // 분류 기준 해당 행

	DWORD dwTextStyle = DT_WORDBREAK | DT_CENTER | DT_VCENTER /*| DT_SINGLELINE*/; //텍스트 스타일 지정
	GV_ITEM Item;
	Item.mask = GVIF_TEXT | GVIF_FORMAT;
	
	for (int id = 0; id < num; id++) {
		for (int i = 0; i < lec[id].time.GetLength(); i++) {
				int days = 0;
				if (lec[id].day == "월") {lec[id].day_int = 1;}
				else if (lec[id].day == "화") {lec[id].day_int = 2;}
				else if (lec[id].day == "수") {lec[id].day_int = 3;}
				else if (lec[id].day == "목") {lec[id].day_int = 4;}
				else if (lec[id].day == "금") {lec[id].day_int = 5;}
				else if (lec[id].day == "토") {lec[id].day_int = 6;}

			for (int row = 0; row < 10; row++) {
				for (int col = 0; col < 7; col++) {
					m_Grid.SetColumnWidth(col, 100);
					if (row < 1) {
						Item.nFormat = dwTextStyle;
						Item.row = row;
						Item.col = col;
						switch (col) {
						case 0:
							Item.strText.Format(_T(" "));
							break;
						case 1:
							Item.strText.Format(_T("월"));
							break;
						case 2:
							Item.strText.Format(_T("화"));
							break;
						case 3:
							Item.strText.Format(_T("수"));
							break;
						case 4:
							Item.strText.Format(_T("목"));
							break;
						case 5:
							Item.strText.Format(_T("금"));
							break;
						case 6:
							Item.strText.Format(_T("토"));
							break;
						}
					}
					else if (col < 1) {
						Item.row = row;
						Item.col = col;
						switch (row) {
						case 0:
							Item.strText.Format(_T(" "));
							break;
						case 1:
							Item.strText.Format(_T("09:00 ~\n09:50"));
							break;
						case 2:
							Item.strText.Format(_T("10:00 ~\n10:50"));
							break;
						case 3:
							Item.strText.Format(_T("11:00 ~ 11:50"));
							break;
						case 4:
							Item.strText.Format(_T("12:00 ~ 12:50"));
							break;
						case 5:
							Item.strText.Format(_T("13:00 ~ 13:50"));
							break;
						case 6:
							Item.strText.Format(_T("14:00 ~ 14:50"));
							break;
						case 7:
							Item.strText.Format(_T("15:00 ~ 15:50"));
							break;
						case 8:
							Item.strText.Format(_T("16:00 ~ 16:50"));
							break;
						case 9:
							Item.strText.Format(_T("17:00 ~ 17:50"));
							break;
						}
					}
					
					else
					{
						Item.row = _ttoi(lec[id].time.Mid(i, 1));
						Item.col = lec[id].day_int;
						Item.strText.Format(_T("%s"), lec[id].name);
					}
					
					m_Grid.SetItem(&Item); // 텍스트 부착
				}
			}
		}
	}
	credit();
}


void Cwinpro0630Dlg::credit()
{
	//수강 학점 계산
	CString str;
	int add = 0;
	for (int id = 0; id < num; id++)
	{
		add += lec[id].val;
	}
	str.Format(_T("%d"), add);
	m_credit.SetWindowText(str);

	//분야별 이수학점
	m_combobox.AddString(TEXT("전공선택"));
	m_combobox.AddString(TEXT("전공심화"));
	m_combobox.AddString(TEXT("교양선택"));
	m_combobox.AddString(TEXT("교양필수"));
	m_combobox.AddString(TEXT("일반선택"));
}


void Cwinpro0630Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void Cwinpro0630Dlg::OnPaint()
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
		CDialog::OnPaint();
		CString major, all;
		m_rating.SetWindowTextW(Rating(major_ck=false));
		m_major.SetWindowTextW(Rating(major_ck = true));

	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR Cwinpro0630Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

float classification(int idx)
{
	if (lec[idx].grade == "A+")
		return 4.5;
	else if(lec[idx].grade == "A0")
		return 4.0;
	else if (lec[idx].grade == "B+")
		return 3.5;
	else if (lec[idx].grade == "B0")
		return 3.0;
	else if (lec[idx].grade == "C+")
		return 2.5;
	else if (lec[idx].grade == "C0")
		return 2.0;
	else if (lec[idx].grade == "D+")
		return 1.5;
	else if (lec[idx].grade == "D0")
		return 1.0;
	else if (lec[idx].grade == "F")
		return 0;
	else if (lec[idx].grade == "P")
		return 0;

	return 0;
}

CString Cwinpro0630Dlg::Rating(bool major_check)
{
	CString grd_str, mgrd_str;

	for (int idx = 0; idx < num; idx++) {
		grd += classification(idx)*lec[idx].val;
		if (lec[idx].field == "전공선택" || lec[idx].field == "전공심화") {
			mgrd += classification(idx)*lec[idx].val;
			
		}
	}

	major_val = smajor_val+imajor_val;
	
	if (major_check) {
		mgrd = mgrd / 2;
		mgrd = mgrd / (major_val);
		mgrd_str.Format(_T("%.2f"), mgrd);
		
		return mgrd_str;
	}
	else {
		grd = grd / all_val;
		grd_str.Format(_T("%.2f"), grd);
		return grd_str;
	}

}


int Cwinpro0630Dlg::CreditField(int idx)
{
	//분야별 이수학점
	if (lec[idx].field == "교양선택")
		return 1;
	else if (lec[idx].field == "교양필수")
		return 2;
	else if (lec[idx].field == "일반선택")
		return 3;
	else if (lec[idx].field == "전공선택")
		return 4;
	else if (lec[idx].field == "전공심화")
		return 5;

	return 0;
}


void Cwinpro0630Dlg::OnSelchangeCombo1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	int nIndex;
	nIndex = m_combobox.GetCurSel();

	//'교양 선택'
	int sum = 0;
	CString str1;

	int remaining = 0;
	CString rem;

	if (nIndex == 0)
	{
		str1.Format(_T("%d / 20"),slib_val);
		m_edit_com.SetWindowText(str1);

		remaining = 20 - slib_val;
		rem.Format(_T("%d"), remaining);
		m_remain.SetWindowTextW(rem);
	}

	//'교양 필수'
	else if (nIndex == 1) {
		str1.Format(_T("%d / 16"),elib_val);
		m_edit_com.SetWindowText(str1);

		remaining = 16 - elib_val;
		rem.Format(_T("%d"), remaining);
		m_remain.SetWindowTextW(rem);
	}

	// 일반 선택
	else if (nIndex == 2) {
		str1.Format(_T("%d / 20"), gen_val);
		m_edit_com.SetWindowText(str1);

		remaining = 20 - gen_val;
		rem.Format(_T("%d"), remaining);
		m_remain.SetWindowTextW(rem);
	}

	//전공 선택
	else if (nIndex == 3) {
		str1.Format(_T("%d / 74"), smajor_val);
		m_edit_com.SetWindowText(str1);

		remaining = 74 - smajor_val;
		rem.Format(_T("%d"), remaining);
		m_remain.SetWindowTextW(rem);
	}
	else if (nIndex == 4) {
			str1.Format(_T("%d / 74"), imajor_val);
			m_edit_com.SetWindowText(str1);

			remaining = 74 - imajor_val;
			rem.Format(_T("%d"), remaining);
			m_remain.SetWindowTextW(rem);
	}
}


void Cwinpro0630Dlg::OnClickedButton1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	
	CString target = _T(""); //목표
	CString temp = _T(""); 
	CString req = _T(""); //필요
	float tar = 0, re = 0, grade=0;
	m_edit_target.GetWindowTextW(target); //목표치 저장
	tar = _tstof(target); //변환
	m_rating.GetWindowTextW(temp);
	grade = _tstof(temp);
	re=((130*tar) - (grade*all_val))/(130-all_val); // 필요 평점 계산
	req.Format(_T("%.2f"), re); //필요평점
	m_require.SetWindowTextW(req); // 출력
}
