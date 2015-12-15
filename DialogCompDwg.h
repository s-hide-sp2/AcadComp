#if !defined(AFX_DIALOGCOMPDWG_H__B75418AF_4A76_4D62_B9E0_4C0ADFF01290__INCLUDED_)
#define AFX_DIALOGCOMPDWG_H__B75418AF_4A76_4D62_B9E0_4C0ADFF01290__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DialogCompDwg.h : ヘッダー ファイル
//

//[ADD]???
#include "resource.h"
#include "ListGrid.h"
#include "ACCommandReactor.h"
#include "ACRetType.h"

//#define DCD_DUMMY_COMMAND "11ss\n"
#define DCD_DUMMY_COMMAND _T("\033\033")
#define DCD_MAX_OUTPUT    2000
#define DCD_INVALID       -1

/////////////////////////////////////////////////////////////////////////////
// DialogCompDwg ダイアログ



class DialogCompDwg : public CDialog
{
// コンストラクション
public:
	static void CreateInstance();
	static void DeleteInstance();

	// ユーザーのズーム処理が終了したときにリアクタから呼び出される。
	static void HighlightEnd();

	DialogCompDwg(CWnd* pParent = NULL);   // 標準のコンストラクタ	

// ダイアログ データ
	//{{AFX_DATA(DialogCompDwg)
	enum { IDD = IDD_DLG_COMP };
	CButton	m_chkRectComp;
	CButton	m_statCsv;
	CButton	m_statComp;
	CButton	m_btnCsv;
	CButton	m_chkResDwg;
	CButton	m_chkExcel;
	CButton	m_stat2;
	CButton	m_stat1;
	CStatic	m_lbl1;
	CStatic	m_lbl2;
	CButton	m_btnCancel;
	CButton	m_btnSel2;
	CButton	m_btnSel1;
	CButton	m_btnRef2;
	CButton	m_btnRef1;
	CButton	m_btnComp;
	CComboBox	m_cboList2;
	CComboBox	m_cboList1;
	ListGrid	m_lstGrid;
	//}}AFX_DATA


// オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。
	//{{AFX_VIRTUAL(DialogCompDwg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート
	//}}AFX_VIRTUAL

// インプリメンテーション
protected:

	// 生成されたメッセージ マップ関数
	//{{AFX_MSG(DialogCompDwg)	
	virtual BOOL OnInitDialog();
	afx_msg void OnColumnclickListGrid(NMHDR* pNMHDR, LRESULT* pResult);
//	afx_msg LONG onAcadKeepFocus(UINT, LONG);
	afx_msg LRESULT onAcadKeepFocus(WPARAM, LPARAM);
	afx_msg void OnItemclickListGrid(NMHDR* pNMHDR, LRESULT* pResult);	
	afx_msg void OnBtnComp();
	afx_msg void OnDropdownCboDwgList1();
	afx_msg void OnDropdownCboDwgList2();
	virtual void OnCancel();
	afx_msg void OnBtnSel();
	afx_msg void OnBtnSel2();
	afx_msg void OnBtnRef1();
	afx_msg void OnBtnRef2();
	afx_msg void OnMnuSetting();		
	afx_msg void OnSize(UINT nType, int cx, int cy);	
	afx_msg void OnBtnCsv();		
	afx_msg void OnBtnTest1();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	// 比較結果のCSVを指定したパスに出力する。
	void WriteCSV(LPCTSTR strCSVPath);

	// モードレスフォームのインスタンスを保持する。
	static DialogCompDwg *m_pDlgCompDwg;

	// コンボボックスに項目を追加する。
	void SetComboItem(CComboBox &cboList, AcDbObjectIdArray &idaryBlkTbl);	

	// グリッドで選択中の行に対応する図形をハイライトする。
	//  rceDwgType: FIRST: dwg1の図形、SECOND: dwg2の図形
	bool SelEntities(ResultCompEntity::RCE_FIELD_OBJID rceDwgType); 

	// ファイル選択ダイアログボックスを表示する。ユーザーが選択したパスを返す。
	bool SelectFileDialog(LPCTSTR strTitle, LPCTSTR strDefaultPath, CString &strRetPath); 

	// 名前を付けて保存ダイアログボックスを表示する。ユーザーが選択したパスを返す。
	bool SaveFileDialog(LPCTSTR strTitle, LPCTSTR strDefaultPath, LPCTSTR strDefaultExt, CString &strRetPath);	
	
	void OnBtnSel0(ResultCompEntity::RCE_FIELD_OBJID);
	
	// 選択行のキーを得る。
	bool GetSelectedKey(CMap<int, int, int, int> &imapRetKey);

	static int CALLBACK SortDataString(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort);
	static int CALLBACK SortDataDouble(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort);
	//bool m_bAsc;
	
	// ウィンドウがフォーカスを保持し続けるか否か
	static bool m_bFocus; 

	// 比較結果のデータセット
	ResultCompEntity m_rce;
	
	// ファイル選択ダイアログを開く。、ユーザーに図面を選択させ、その図面を開く
	bool SelectDwgOpen(CComboBox &cboList, AcDbObjectIdArray &idaryBlkTbl);

	// Acadドキュメントウィンドウを左右に分割して表示する。
	// iShowDocNum: 表示するドキュメントの番号 1 or 2
	void SetDocumentSize(int iShowDocNum);
	
	// 警告メッセージの表示
	void ShowAlert(LPCTSTR lpszMsg); 

	// エラーメッセージの表示
	void ShowError(LPCTSTR lpszMsg); 	

	//// オートメーションを使ってズームを実行する。
	//bool AutomationZoom(const AcGePoint2d &pt2LB, const AcGePoint2d &pt2RT);	

	CMenu *m_pMenu;

	// 図形ハイライト→確認で、
	// ユーザーのズームコマンドの終了を知るため、リアクタを使う。
	// リアクタから本クラスのハイライト終了処理を呼び出すときに、以下のスタティックメンバを使う。
	//static bool ms_bUserZoom;
	//static CMap<int, int, AcDbObjectId, AcDbObjectId> ms_idmapHighlight;
	//static DialogCompDwg *ms_pthis;
	//static ACCommandReactor *ms_pCmdReac;
	//static AcApDocument *ms_pDocUserZoom;

	CMap<int, int, int, int> m_imapTest;
	void TestMakeMap(CMap<int, int, int, int> &imapRet) ;
	int m_iPreWidth, m_iPreHeitht;

	// 各ドキュメントを識別するため、データベースのブロックテーブルのID列を使う。
	AcDbObjectIdArray m_idaryBlkTbl1;
	AcDbObjectIdArray m_idaryBlkTbl2;
	//CMap<int, int, AcDbObjectId, AcDbObjectId> m_mappBlkTblId;

	void SetControlPosition(
		CWnd &wndControl, 
		int iRightDist  = DCD_INVALID,  // ウィンドウの右からの距離 コントロールの幅も考慮する。指定しない場合は、DCD_INVALIDを渡す。
		int iLeftDist   = DCD_INVALID,  // ウィンドウの左からの距離 指定しない場合は、DCD_INVALIDを渡す。
		int iTopDist    = DCD_INVALID,  // ウィンドウの上からの距離 指定しない場合は、DCD_INVALIDを渡す。
		int iBottomDist = DCD_INVALID,  // ウィンドウの下からの距離 コントロールの高さも考慮する。指定しない場合は、DCD_INVALIDを渡す。
		int iWidthNew   = DCD_INVALID,  // コントロールの幅 指定しない場合は、DCD_INVALIDを渡す。
		int iHeightNew  = DCD_INVALID   // コントロールの高さ 指定しない場合は、DCD_INVALIDを渡す。
	);
};



//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_DIALOGCOMPDWG_H__B75418AF_4A76_4D62_B9E0_4C0ADFF01290__INCLUDED_)
