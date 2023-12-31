
// win_pro0630Dlg.h: 헤더 파일
//

#pragma once

#include "GridCtrl.h"
#include "afxwin.h"
// Cwinpro0630Dlg 대화 상자
class Cwinpro0630Dlg : public CDialog
{
// 생성입니다.
public:
	Cwinpro0630Dlg(CWnd* pParent = NULL);	// 표준 생성자입니다.
	CGridCtrl m_Grid;
	int row;

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_WIN_PRO0630_DIALOG };
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
	afx_msg void timetable();
	afx_msg CString Rating(bool major_check);
	//afx_msg void MajorRating();
	afx_msg void credit();
	afx_msg int CreditField(int idx);
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CEdit m_credit;
	CComboBox m_combobox;
	afx_msg void OnSelchangeCombo1();
	CEdit m_edit_com;
	CEdit m_remain;
	CEdit m_rating;
	CEdit m_major;
	int all_val;
	int major_val, imajor_val, smajor_val, elib_val, slib_val,gen_val;

	float grd,mgrd;
	bool major_ck;
	CEdit m_edit_target;
	CEdit m_require;
	afx_msg void OnClickedButton1();
};
