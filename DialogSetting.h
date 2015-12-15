#if !defined(AFX_DIALOGSETTING_H__C8EDB3C4_7A25_40EC_84AF_B124D0D2D957__INCLUDED_)
#define AFX_DIALOGSETTING_H__C8EDB3C4_7A25_40EC_84AF_B124D0D2D957__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DialogSetting.h : ヘッダー ファイル
//

#include "ACString.h"
#include "ACProfileManager.h"
#include "ACCompBase.h"

/////////////////////////////////////////////////////////////////////////////
// DialogSetting ダイアログ

class DialogSetting : public CDialog
{
// コンストラクション
public:
	DialogSetting(CWnd* pParent = NULL);   // 標準のコンストラクタ

// ダイアログ データ
	//{{AFX_DATA(DialogSetting)
	enum { IDD = IDD_DLG_SETTING };
	CEdit	m_edtTol;
	//}}AFX_DATA


// オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。
	//{{AFX_VIRTUAL(DialogSetting)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート
	//}}AFX_VIRTUAL

// インプリメンテーション
protected:

	// 生成されたメッセージ マップ関数
	//{{AFX_MSG(DialogSetting)
	virtual void OnCancel();
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_DIALOGSETTING_H__C8EDB3C4_7A25_40EC_84AF_B124D0D2D957__INCLUDED_)
