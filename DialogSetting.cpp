// DialogSetting.cpp : インプリメンテーション ファイル
//

#include "StdAfx.h"
#include "resource.h"
#include "DialogSetting.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// DialogSetting ダイアログ


DialogSetting::DialogSetting(CWnd* pParent /*=NULL*/)
	: CDialog(DialogSetting::IDD, pParent)
{
	//{{AFX_DATA_INIT(DialogSetting)
		// メモ - ClassWizard はこの位置にマッピング用のマクロを追加または削除します。
	//}}AFX_DATA_INIT
}


void DialogSetting::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(DialogSetting)
	DDX_Control(pDX, IDC_EDIT_TOL, m_edtTol);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(DialogSetting, CDialog)
	//{{AFX_MSG_MAP(DialogSetting)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// DialogSetting メッセージ ハンドラ

void DialogSetting::OnCancel() 
{
	// TODO: この位置に特別な後処理を追加してください。
	
	CDialog::OnCancel();
}

void DialogSetting::OnOK() 
{
	// TODO: この位置にその他の検証用のコードを追加してください
	CString strInput;
	double  dRet;

	m_edtTol.GetWindowText(strInput);

	if (!ACString::StringToNumber(strInput, dRet)) {
		CString strTitle;
		this->GetWindowText(strTitle);
		MessageBox(_T("入力した数値は無効です。"), strTitle, MB_OK | MB_ICONWARNING);//2006.07.20
		return;
	}	

	ACProfileManager pMng;
	
	// 許容誤差をプロファイルに書き込む。
	pMng.SetUserTol(dRet);
	ACCompBase::SetTol(dRet);

	CDialog::OnOK();
}

BOOL DialogSetting::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: この位置に初期化の補足処理を追加してください	
	ACProfileManager pMng;
	CString strTol;
	double dTol;

	dTol = pMng.GetUserTol();
	
	strTol = ACString::NumberToString(dTol);
	
	// 画面の入力ボックスと比較クラスに、取得した許容誤差をセットする。
	m_edtTol.SetWindowText(strTol);
	//ACCompBase::SetTol(dTol);

	return TRUE;  // コントロールにフォーカスを設定しないとき、戻り値は TRUE となります
	              // 例外: OCX プロパティ ページの戻り値は FALSE となります
}
