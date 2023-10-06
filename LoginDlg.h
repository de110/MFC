#pragma once
class LoginDlg : public CDialog
{
public:
	LoginDlg(CWnd* pParent = NULL);
	~LoginDlg();
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_LOGIN};
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.

protected:
	HICON m_hIcon;
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

};

