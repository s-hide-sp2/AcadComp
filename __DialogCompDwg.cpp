// DialogCompDwg.cpp : インプリメンテーション ファイル
//

#include "StdAfx.h"
#include "resource.h"
#include "DialogCompDwg.h"

//[ADD]
#include "ResultRecord.h"
#include "LVSortInfo.h"
#include "ACDocManager.h"
#include "ACUIManager.h"
#include "DialogSetting.h"
//#include "acad.h"
#include "ACFinally.h"
#include "ACErrorInfo.h"
#include <io.h>


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// 静的メンバの初期化
DialogCompDwg *DialogCompDwg::m_pDlgCompDwg = NULL;

//bool DialogCompDwg::ms_bUserZoom = false;
bool DialogCompDwg::m_bFocus = true; 
//DialogCompDwg *DialogCompDwg::ms_pthis = NULL;
//CMap<int, int, AcDbObjectId, AcDbObjectId> DialogCompDwg::ms_idmapHighlight;
//ACCommandReactor *DialogCompDwg::ms_pCmdReac = NULL;
//AcApDocument *DialogCompDwg::ms_pDocUserZoom = NULL;
/////////////////////////////////////////////////////////////////////////////
// DialogCompDwg ダイアログ


DialogCompDwg::DialogCompDwg(CWnd* pParent /*=NULL*/)
	: CDialog(DialogCompDwg::IDD, pParent)
{
	//{{AFX_DATA_INIT(DialogCompDwg)
	//}}AFX_DATA_INIT

	//m_bFocus = true;
	
}


void DialogCompDwg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(DialogCompDwg)
	DDX_Control(pDX, IDC_STAT_CSV, m_statCsv);
	DDX_Control(pDX, IDC_STAT_COMP, m_statComp);
	DDX_Control(pDX, IDC_BTN_CSV, m_btnCsv);
	DDX_Control(pDX, IDC_CHK_RESDWG, m_chkResDwg);
	DDX_Control(pDX, IDC_CHK_EXCEL, m_chkExcel);
	DDX_Control(pDX, IDC_STAT_2, m_stat2);
	DDX_Control(pDX, IDC_STAT_1, m_stat1);
	DDX_Control(pDX, IDCANCEL, m_btnCancel);
	DDX_Control(pDX, IDC_BTN_SEL2, m_btnSel2);
	DDX_Control(pDX, IDC_BTN_SEL, m_btnSel1);
	DDX_Control(pDX, IDC_BTN_REF2, m_btnRef2);
	DDX_Control(pDX, IDC_BTN_REF1, m_btnRef1);
	DDX_Control(pDX, IDC_BTN_COMP, m_btnComp);
	DDX_Control(pDX, IDC_CBO_DWG_LIST2, m_cboList2);
	DDX_Control(pDX, IDC_CBO_DWG_LIST1, m_cboList1);
	DDX_Control(pDX, IDC_LIST_GRID, m_lstGrid);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(DialogCompDwg, CDialog)
	//{{AFX_MSG_MAP(DialogCompDwg)		
	ON_NOTIFY(LVN_COLUMNCLICK, IDC_LIST_GRID, OnColumnclickListGrid)
	ON_MESSAGE(WM_ACAD_KEEPFOCUS, onAcadKeepFocus)
	ON_NOTIFY(HDN_ITEMCLICK, IDC_LIST_GRID, OnItemclickListGrid)	
	ON_BN_CLICKED(IDC_BTN_COMP, OnBtnComp)
	ON_CBN_DROPDOWN(IDC_CBO_DWG_LIST1, OnDropdownCboDwgList1)
	ON_CBN_DROPDOWN(IDC_CBO_DWG_LIST2, OnDropdownCboDwgList2)
	ON_BN_CLICKED(IDC_BTN_SEL, OnBtnSel)
	ON_BN_CLICKED(IDC_BTN_SEL2, OnBtnSel2)
	ON_BN_CLICKED(IDC_BTN_REF1, OnBtnRef1)
	ON_BN_CLICKED(IDC_BTN_REF2, OnBtnRef2)
	ON_COMMAND(ID_MNU_SETTING, OnMnuSetting)				
	ON_WM_SIZE()
	ON_BN_CLICKED(IDC_BTN_CSV, OnBtnCsv)		
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// DialogCompDwg メッセージ ハンドラ

/*
void DialogCompDwg::OnBtnTest01() 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	AcApDocManager *pDocMng = acDocManager;
	AcApDocumentIterator *pDocItr = pDocMng->newAcApDocumentIterator(); 
	Acad::ErrorStatus es;

	// 現在開かれているドキュメントを走査する。
	for (; !pDocItr->done(); pDocItr->step()) {
		AcApDocument *pDoc = pDocItr->document();
		
		acutPrintf("\ndoc: %s", pDoc->fileName());
		//pDocMng->activateDocument(pDoc);
		//pDocMng->lockDocument(pDoc, AcAp::kRead);

		AcDbDatabase *pDb = pDoc->database();
		AcDbBlockTable *pBlkTable;

		es = pDb->getBlockTable(pBlkTable, AcDb::kForRead);
		if (es == Acad::eOk) {
			AcDbBlockTableIterator *pBlkItr;	
			//AcDbBlockTableRecordIterator *pBlkRecItr;

			pBlkTable->newIterator(pBlkItr); 
			for (pBlkItr->start(); !pBlkItr->done(); pBlkItr->step()) {
				AcDbBlockTableRecord *pBlkRec;				
				es = pBlkItr->getRecord(pBlkRec, AcDb::kForRead);

				char *pName;
				pBlkRec->getName(pName);
				acutPrintf("\nblkTable: %s", pName);

				acutDelString(pName);
				if (es == Acad::eOk) {
					AcDbBlockTableRecordIterator *pBlkRecItr;
					pBlkRec->newIterator(pBlkRecItr);
					for (pBlkRecItr->start(); !pBlkRecItr->done(); pBlkRecItr->step()) {						
						AcDbEntity *pEnt;	
						es = pBlkRecItr->getEntity(pEnt, AcDb::kForRead);
						if (es == Acad::eOk) {
							AcDbHandle hdlEnt;

							char cBuff[20];							
							pEnt->getAcDbHandle(hdlEnt);
							hdlEnt.getIntoAsciiBuffer(cBuff);

							acutPrintf("\n%s: %s", cBuff, pEnt->isA()->name());
							//delete pcBuff;
							//acutDelString(pName);
							pEnt->close();
						}
					}
					delete pBlkRecItr;
					pBlkRec->close();					
				}
			}
			//ACDB_MODEL_SPACE
			//ACDB_PAPER_SPACE
			delete pBlkItr;			
			pBlkTable->close();			
		}		
	}
	delete pDocItr;
	
	acutPrintf("\nEnd");
}
*/

BOOL DialogCompDwg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: この位置に初期化の補足処理を追加してください
	InitCommonControls();

	m_pMenu = new CMenu();
	m_pMenu->LoadMenu(IDR_MNU_COMP);	 
	this->SetMenu(m_pMenu);
	
	// コンボボックスに図面名の項目を加える。
	SetComboItem(m_cboList1, m_idaryBlkTbl1);
	SetComboItem(m_cboList2, m_idaryBlkTbl2);
	
	// コンボ2は違う図面を選択する。
	if (m_cboList2.GetCount() > 1)
		m_cboList2.SetCurSel(1);
	
	// 列項目を設定する。
	m_lstGrid.InitGridCompEntity();
	
	// フォーカスを得る。
	m_bFocus = true;

	return TRUE;  // コントロールにフォーカスを設定しないとき、戻り値は TRUE となります
	              // 例外: OCX プロパティ ページの戻り値は FALSE となります
}

void DialogCompDwg::OnColumnclickListGrid(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	
	
	// ソートメソッドに渡す引数を作成
    LVSortInfo sortInfo;    
    sortInfo.m_iIdx = pNMListView->iSubItem;
	sortInfo.m_bAsc = m_lstGrid.m_bOrderAsc[sortInfo.m_iIdx];
	sortInfo.m_pListGrid = &m_lstGrid;
	
	// lParamを振りなおす
	m_lstGrid.SetlParam();

	m_lstGrid.SortItems( SortDataString, (DWORD)&sortInfo);

	m_lstGrid.m_bOrderAsc[sortInfo.m_iIdx] = 
		!m_lstGrid.m_bOrderAsc[sortInfo.m_iIdx];
    // ソートを行う

	//if (sortInfo.m_iIdx == 0) {
	//	m_lstGrid.SortItems( SortDataString, (DWORD)&sortInfo);
	//}

	//else if (sortInfo.m_iIdx == 1) {
	//	m_lstGrid.SortItems( SortDataDouble, (DWORD)&sortInfo);
	//}	

	*pResult = 0;
}

// ダイアログのフォーカスの制御
afx_msg LONG DialogCompDwg::onAcadKeepFocus(UINT ui, LONG l)
{
	// TRUE: モードレスフォームにフォーカスを持たせる。
	// FALSE: Acadにフォーカスを戻す。
	return m_bFocus;
}

void DialogCompDwg::OnItemclickListGrid(NMHDR* pNMHDR, LRESULT* pResult) 
{
	HD_NOTIFY *phdn = (HD_NOTIFY *) pNMHDR;
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	
	*pResult = 0;
}


int CALLBACK DialogCompDwg::SortDataString(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort)
{
	// １番目と２番目には、
    // 比較するデータのアドレスが入っている。
    // InsertItemを行った際のLPARAMである
	
    // lParam1, lParam2はグリッドアイテムの
	// インデックスやアイテムのソースデータのポインタ等をセットしておく。

	// Modelessなので、このやり方だとACADのメインウィンドウをとってしまう。
	//DialogCompDwg* pDlg = (DialogCompDwg*)AfxGetMainWnd();

	// ３番目には、
    // SortItemsの最後の引数のアドレスが入っている。
    LVSortInfo *pData = (LVSortInfo *)lParamSort;

	ListGrid *plstGrid = pData->m_pListGrid;
	

	CString str1 = plstGrid->GetItemText(lParam1, pData->m_iIdx);
	CString str2 = plstGrid->GetItemText(lParam2, pData->m_iIdx);

    int nSort = str1.CompareNoCase((LPCTSTR)str2);	

    // 昇順
    if( pData->m_bAsc)
        return nSort;
	// 降順
	else    
		return nSort * -1;

}

// XXX
int CALLBACK DialogCompDwg::SortDataDouble(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort)
{
	// １番目と２番目には、
    // 比較するデータのアドレスが入っている。
    // InsertItemを行った際のLPARAMである
    double *pdData1 = (double *)lParam1;
    double *pdData2 = (double *)lParam2;

    // ３番目には、
    // SortItemsの最後の引数のアドレスが入っている。
    LVSortInfo *pData = (LVSortInfo *)lParamSort;

    int nSort = (*pdData1 > *pdData2);

    // 昇順
    if( pData->m_bAsc == TRUE)
    {
        return nSort * -1;
    }

    // 降順
    return nSort;
}

// コンボボックスに項目を追加する。
void DialogCompDwg::SetComboItem(CComboBox &cboList, AcDbObjectIdArray &idaryBlkTbl)
{		
	// 現在選択している項目のテキストを保持する。
	CString strCurText;
	cboList.GetLBText(cboList.GetCurSel(), strCurText);

	// 内容をリセットする。
	cboList.ResetContent();	
	
	// 現在開いている図面のパスリストを得て、セットする。
	ACDocManager docMng;	
	CStringArray saryRet;	
	CUIntArray   uiarySortedIdx;
	
	docMng.GetDocPaths(saryRet, idaryBlkTbl);		
		
	uiarySortedIdx.SetSize(saryRet.GetSize());
	for (int i = 0; i < saryRet.GetSize(); i++) {
		int iRet = cboList.AddString(saryRet[i]);
		if (iRet != CB_ERR)
			uiarySortedIdx.InsertAt(iRet, i);
			
	}
	
	for (int j = 0; j < saryRet.GetSize(); j++) 
		cboList.SetItemData(j, uiarySortedIdx[j]);

	// 開いている図面がない場合は終了する。
	if (saryRet.GetSize() == 0)
		return;

	// リセット前に選択していた項目のインデックスをセットする。
	// 選択していた項目が存在していない場合は最初の項目をセットする。
	int iSelIdx;
	iSelIdx = cboList.FindString(-1, strCurText);
	
	if (iSelIdx == CB_ERR) 
		iSelIdx = 0;

	cboList.SetCurSel(iSelIdx);	
}

// 比較実行
void DialogCompDwg::OnBtnComp() 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	ACDocManager docMng;		

	try {	
		
		// カレント図面を保持する。
		docMng.SetCurDoc();

		this->BeginWaitCursor();
		// 比較ボタンはコマンド実行中のみ使用不可とする。それ以外は、結果が存在し、成功した場合のみ使用可にする。
		m_btnComp.EnableWindow(FALSE);		
		m_btnSel1.EnableWindow(FALSE);
		m_btnSel2.EnableWindow(FALSE);
		m_btnCsv.EnableWindow(FALSE);

		// グリッド行を削除する。	
		m_lstGrid.DeleteAllItems();		

		// 選択している図面のチェックを行う。
		// 問題があった場合は、警告をスローする。		
		int iCurIdx1, iCurIdx2;		

		if ((iCurIdx1 = m_cboList1.GetCurSel()) == CB_ERR)
			throw (new ACErrorInfo(ACErrorInfo::ALERT, "図面1を選択してください。"));

		if ((iCurIdx2 = m_cboList2.GetCurSel()) == CB_ERR)
			throw (new ACErrorInfo(ACErrorInfo::ALERT, "図面2を選択してください。"));
		
		// 図面のブロックテーブルIDを比較して、同じ図面かどうか判断する。
		AcDbObjectId idBlkTbl1, idBlkTbl2;
		idBlkTbl1 = m_idaryBlkTbl1[m_cboList1.GetItemData(iCurIdx1)];
		idBlkTbl2 = m_idaryBlkTbl2[m_cboList2.GetItemData(iCurIdx2)];				

		if (!idBlkTbl1.isValid())
			throw (new ACErrorInfo(ACErrorInfo::ALERT, "図面1は無効です。"));
		if (!idBlkTbl2.isValid())
			throw (new ACErrorInfo(ACErrorInfo::ALERT, "図面2は無効です。"));

		if (idBlkTbl1 == idBlkTbl2) 
			throw (new ACErrorInfo(ACErrorInfo::ALERT, "違う図面を選択してください。"));
				
		// 図面が有効であるか、コマンド使用中でないかのチェック
		ACRetType::ACRETTYPE rType;				
		
		if ((rType = docMng.CheckDwg(idBlkTbl1)) != ACRetType::rOk) {	
			ACRetType::SetI1(1);
			throw (new ACErrorInfo(ACErrorInfo::ALERT, ACRetType::GetMsg(rType)));
		}		
		
		if ((rType = docMng.CheckDwg(idBlkTbl2)) != ACRetType::rOk) {	
			ACRetType::SetI1(2);
			throw (new ACErrorInfo(ACErrorInfo::ALERT, ACRetType::GetMsg(rType)));
		}						

		// 図面の全図形のエンティティを得る。図面パスが無効のときは終了する。
		CMap<int, int, AcDbObjectId, AcDbObjectId> idmapRet1, idmapRet2;
		
		if (!docMng.GetDwgAllEntityIds(idBlkTbl1, idmapRet1)) 
			throw (new ACErrorInfo(ACErrorInfo::ALERT, "図面1は無効です。"));					

		if (!docMng.GetDwgAllEntityIds(idBlkTbl2, idmapRet2)) 
			throw (new ACErrorInfo(ACErrorInfo::ALERT, "図面2は無効です。"));									
		
		//####
		//for (int k = 0; k < 1000; k++) {
		// オブジェクトハンドルでソートする。
		docMng.SortEntities(idmapRet1);
		docMng.SortEntities(idmapRet2);
		
		// 全ての要素を削除後、サイズを設定する。
		m_rce.RemoveAll();
		m_rce.SetHashTableSize(idmapRet1.GetCount() + idmapRet2.GetCount());  
			
		// 比較実行
		docMng.CompDwgs(idmapRet1, idmapRet2, m_rce);		
		//####
		//}
				
		// 違いがない場合
		if (m_rce.GetCount() == 0) 			
			throw (new ACErrorInfo(ACErrorInfo::INFO, "同じ図面です。"));
			//throw (new ACErrorInfo(ACErrorInfo::ALERT, ""));
		
		//////////////////////////////
		// ---- 結果を表示する。---- //
		//////////////////////////////
		m_lstGrid.ShowResultCompEntity(m_rce);		

		// 合成図面作成チェックが付いているときは合成図面を作成する。
		if (m_chkResDwg.GetCheck() == 1) {		
			bool bRes;
			docMng.CreateNewDwg();
			docMng.SetCurDoc();
			bRes = docMng.DrawResultDwg(idBlkTbl2, idBlkTbl1, m_rce);
			docMng.UnlockCurDoc();
			docMng.AutomationCommand("zoom e ");

			if (!bRes)
				throw (new ACErrorInfo(ACErrorInfo::ERR, "合成図面の描画に失敗しました。"));			
			
		}		

		docMng.ReturnCurDoc();
		this->EndWaitCursor();
		m_btnComp.EnableWindow(TRUE);		
		m_btnSel1.EnableWindow(TRUE);
		m_btnSel2.EnableWindow(TRUE);
		m_btnCsv.EnableWindow(TRUE);
		//__except (GetExceptionInformation()) {
	}	
	catch (ACErrorInfo *pEI) {
		CString strCaption;		
						
		this->EndWaitCursor();			
		m_btnComp.EnableWindow(TRUE);				

		this->GetWindowText(strCaption);
		MessageBox(pEI->m_strMsg, strCaption, pEI->GetMBType(pEI->m_eiType));
		//ShowAlert(pEI->m_strMsg);		
		delete pEI;		
	}
	catch (CException *pExc) {
		char cBuff[256];
						
		this->EndWaitCursor();
		m_btnComp.EnableWindow(TRUE);				

		pExc->GetErrorMessage(cBuff, 256);
		ShowError(cBuff);
		delete pExc;
	}

//	__finally {
	
}

//void DialogCompDwg::CheckDwgs()
//{}

void DialogCompDwg::OnDropdownCboDwgList1() 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	SetComboItem(m_cboList1, m_idaryBlkTbl1);		
}

void DialogCompDwg::OnDropdownCboDwgList2() 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	SetComboItem(m_cboList2, m_idaryBlkTbl2);			
}

void DialogCompDwg::CreateInstance()
{
	CAcModuleResourceOverride resOverride;	

	/*
	if (m_pDlgCompDwg == NULL) {
		//delete m_pDlgCompDwg;		
		m_pDlgCompDwg = new DialogCompDwg();			
	}
	*/

	if (m_pDlgCompDwg == NULL || m_pDlgCompDwg->m_hWnd == NULL) {
		delete m_pDlgCompDwg;		
		m_pDlgCompDwg = new DialogCompDwg();			
		m_pDlgCompDwg->Create(IDD_DLG_COMP); 				
	}
		
	//if (m_pDlgCompDwg->IsIconic() == TRUE)
	m_pDlgCompDwg->ShowWindow(SW_SHOWNORMAL);			
}

void DialogCompDwg::OnCancel() 
{
	// TODO: この位置に特別な後処理を追加してください。
	
	//CDialog::OnCancel();
	m_bFocus = false;
	
	m_rce.RemoveAll();	
	//ms_idmapHighlight.RemoveAll();
	//ms_idmapHighlight.InitHashTable(0);
	m_pMenu->DestroyMenu();
	m_pDlgCompDwg->DestroyWindow();	
}

void DialogCompDwg::DeleteInstance()
{
	if (m_pDlgCompDwg != NULL) 
		delete m_pDlgCompDwg;
}

// グリッドで選択した図形をハイライトする。
void DialogCompDwg::OnBtnSel() 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	OnBtnSel0(ResultCompEntity::FIRST);	
}

// グリッドで選択した図形をハイライトする。
void DialogCompDwg::OnBtnSel2() 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	OnBtnSel0(ResultCompEntity::SECOND);
}

void DialogCompDwg::OnBtnSel0(ResultCompEntity::RCE_FIELD_OBJID rceObjType)
{
	// 選択行がない場合は終了する。
	UINT uiSelCount = m_lstGrid.GetSelectedCount();
	if (uiSelCount == 0) {
		ShowAlert("ハイライトする図形の行を選択してください。");
		return;
	}
	
	// フォーカスをAcadに渡す
	m_bFocus = false;		
	CWnd *pWndAcad = AcUiMainWindow();	
	// ウィンドウを非表示にする。
	this->SetWindowPos(pWndAcad, 
		0, 0, 0, 0, SWP_HIDEWINDOW | SWP_NOACTIVATE | SWP_NOMOVE | SWP_NOSIZE);	
	
	// リアクタが存在しない場合は作成する。
	//	if (ms_pCmdReac == NULL) {
	//			ms_pCmdReac = new ACCommandReactor();
	//			//ACCommandReactor *pCmdReac= new ACCommandReactor();
	//			acedEditor->addReactor(ms_pCmdReac);
	//#ifdef _DEBUG
	//			acutPrintf("\nadd command reactor");
	//#endif
	//		}

	try {
		SelEntities(rceObjType);

		// フォーカスをウィンドウが保持する
		m_bFocus = true;
		// ウィンドウを再表示する。		
		this->SetWindowPos(NULL, 0, 0, 100, 100, SWP_SHOWWINDOW |SWP_NOMOVE | SWP_NOSIZE);		
	}
	catch (ACErrorInfo *pErrInfo) {
		m_bFocus = true;
		this->SetWindowPos(NULL, 0, 0, 100, 100, SWP_SHOWWINDOW |SWP_NOMOVE | SWP_NOSIZE);
		ShowAlert(pErrInfo->m_strMsg);
		delete pErrInfo;
	}
}

// 選択できない場合も考える。
// 選択行に有効な図形がないときはfalseを返す。
bool DialogCompDwg::SelEntities(ResultCompEntity::RCE_FIELD_OBJID rceDwgType) 
{	
	// 選択行のキーを得る。
	CMap<int, int, int, int> imapKey;
	GetSelectedKey(imapKey);

	if (imapKey.GetCount() == 0)
		throw (new ACErrorInfo(ACErrorInfo::ALERT, "ハイライトする図形の行を選択してください。"));		

	ACDocManager acDocMng;
	CMap<int, int, AcDbObjectId, AcDbObjectId> idmapTmp1, idmapHighlight1;
	
	// 選択行に対応するAcDbObjectId列を得る。	
	m_rce.GetSelId(imapKey, rceDwgType, idmapTmp1);

	// 同じ空間に属する図形のみを得る。
	if (!acDocMng.GetSameSpaceEntities(idmapTmp1, idmapHighlight1))
		throw (new ACErrorInfo(ACErrorInfo::ALERT, "選択できる図形はありませんでした。"));		
		
	ACUIManager acUIMng;		
	AcGePoint2d pt2LB, pt2RT;
	
	// 選択した図形の範囲を拡張した範囲を得る。
	acDocMng.GetEntityExtents(idmapHighlight1, pt2LB, pt2RT);	
	acDocMng.Extents(pt2LB, pt2RT);			

	// ID列の最初の図形の図面をアクティブにし、属する空間に切り替える。
	if (!acDocMng.ChangeToFirstEntitySpace(idmapHighlight1))
		throw (new ACErrorInfo(ACErrorInfo::ALERT, 
			"ズームに失敗しました。\nコマンド実行中の可能性があります。"));				
	
	// 拡張した選択図形範囲でズーム			
	acDocMng.AutomationZoom(pt2LB, pt2RT);	

	// 選択した図形をハイライトする。
	if (!acDocMng.HighlightEntities(idmapHighlight1, true))	
		throw (new ACErrorInfo(ACErrorInfo::ALERT, "ハイライトに失敗しました。"));				
	
	// ユーザーがキーを押すまで待つ
	acUIMng.ReqSomeKey("\nEnterまたはEscで終了: ");

	// 選択した図形をアンハイライトする。
	acDocMng.HighlightEntities(idmapHighlight1, false);	

	return true;
}

// 選択行のキーを得る。
bool DialogCompDwg::GetSelectedKey(CMap<int, int, int, int> &imapRetKey)
{
	int iItemIdx = -1;
	int iFlags   = LVNI_ALL | LVNI_SELECTED;
	int i = -1; 	

	imapRetKey.InitHashTable((int)((double)m_lstGrid.GetSelectedCount() * 1.2));
	
	// 選択している行のキー(結果セットのインデックス)を得る。
	while ((iItemIdx = m_lstGrid.GetNextItem(iItemIdx, iFlags)) != -1) {
		LVITEM lvItem;
		char cBuff[20];
		int iAdd;

		lvItem.mask = LVIF_TEXT; // | LVIF_IMAGE | LVIF_STATE;
		lvItem.iItem = iItemIdx;		
		lvItem.pszText = cBuff;
		lvItem.cchTextMax = sizeof(cBuff);
		//lvItem.stateMask = 0xFFFF;		
		lvItem.iSubItem = ListGrid::KEY;
		m_lstGrid.GetItem(&lvItem);
						
		iAdd = atoi(cBuff);
		i++;	
		imapRetKey[i] = iAdd;
	}	

	if (i == -1)
		return false;
	else
		return true;
}

void DialogCompDwg::OnBtnRef1() 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	if (!SelectDwgOpen(m_cboList1, m_idaryBlkTbl1))
		return;

	SetDocumentSize(1);

	// ADD 2004/08/30 Eズームコマンドを送る。
	ACDocManager docMng;
	docMng.AutomationCommand("zoom e ");
}

void DialogCompDwg::OnBtnRef2() 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください	
	if (!SelectDwgOpen(m_cboList2, m_idaryBlkTbl2))
		return;
	
	SetDocumentSize(2);

	// ADD 2004/08/30 Eズームコマンドを送る。
	ACDocManager docMng;
	docMng.AutomationCommand("zoom e ");
}

// ユーザーに図面を選択させ、その図面を開く。
bool DialogCompDwg::SelectDwgOpen(CComboBox &cboList, AcDbObjectIdArray &idaryBlkTbl)
{
	ACProfileManager proMng;
	CString strRetPath, strDefDir;	
	
	// プロファイルからオープンディレクトリパスを得る。
	// そのパスが有効でないときは、空文字をセットする。
	strDefDir = proMng.GetUserOpenDirPath();
	if (_access(strDefDir, 0) == -1)
		strDefDir = "";
	
	// 図面ファイル選択ダイアログを表示する。
	if (!SelectFileDialog("図面ﾌｧｲﾙを選択", strDefDir, strRetPath)) {		
		// キャンセルされた場合は、アクティブであった図面がなぜかコマンド使用中になるため、
		// 意味のないコマンドを送る。
		acDocManager->sendStringToExecute(acDocManager->mdiActiveDocument(), DCD_DUMMY_COMMAND, false, true, false);
		//acDocManager->unlockDocument(acDocManager->mdiActiveDocument());	
		return false;					
	}
	
	this->EnableWindow(FALSE);
	AcApDocument *pDocBefore, *pDocAfter;
	pDocBefore = acDocManager->mdiActiveDocument();	
	// 図面を開く ヘルプにない関数(以前のバージョン？)
	acDocManager->appContextOpenDocument(strRetPath);	
		
	pDocAfter = acDocManager->mdiActiveDocument();
	
	// 既に開いていた図面をコマンド終了状態にするため、意味のないコマンドを送る。

	////// acDocManager->activateDocument(pDocBefore);	
	
	//AcDbDatabase *pDbBefore = pDocBefore->database();
	//acdbSendInitialDwgFileOpenComplete(pDbBefore);
	//acdbHostApplicationServices()->
	
	//acDocManager->sendStringToExecute(pDocBefore, "1sa\t", true, false);
	acDocManager->sendStringToExecute(pDocBefore, DCD_DUMMY_COMMAND, false, true, false);
	// 新しく開いた図面をアクティブにする。
	acDocManager->activateDocument(pDocAfter);
	
	// コンボボックスに選択したパスを表示する。
	SetComboItem(cboList, idaryBlkTbl);
	//cboList.SelectString(-1, pDocAfter->fileName());
	cboList.SelectString(-1, pDocAfter->docTitle());
	
	
	// 選択パスをプロファイルにセットする。
	strDefDir = ACString::GetSegmentR(strRetPath, '\\', false, false);
	strDefDir = strDefDir + '\\';
	proMng.SetUserOpenDirPath(strDefDir);
	
	this->EnableWindow(TRUE);
	
	this->SetFocus();

	return true;
}

// ファイル選択ダイアログボックスを表示する。ユーザーが選択したパスを返す。
bool DialogCompDwg::SelectFileDialog(LPCTSTR strTitle, LPCTSTR strDefaultPath, CString &strRetPath) 
{	
	struct resbuf* rbuf;
	bool   bRes = true;
	int    iFlags;

	rbuf = acutNewRb(RTSTR);		
	iFlags = 8 | 16 | 32 | 256 | 512;

	// ダイアログを表示する。キャンセルされたときはRTERRORが返る。
	if (acedGetFileNavDialog(strTitle, strDefaultPath, "dwg", "ACSELECTDLG", iFlags, &rbuf) == RTERROR)
		bRes = false;				

	if (bRes)
		strRetPath = rbuf->resval.rstring;	

	acutRelRb(rbuf);

	return bRes;		
}

// 名前を付けて保存ダイアログボックスを表示する。ユーザーが選択したパスを返す。
bool DialogCompDwg::SaveFileDialog(LPCTSTR strTitle, LPCTSTR strDefaultPath, LPCTSTR strDefaultExt, CString &strRetPath)
{
	struct resbuf* rbuf;
	bool   bRes = true;
	int    iFlags;

	rbuf = acutNewRb(RTSTR);		
	iFlags = 1 | 8 | 16 | 64 | 128 | 256 | 512;  //8 | 16 | 32 | 256 | 512;

	// ダイアログを表示する。キャンセルされたときはRTERRORが返る。	
	if (acedGetFileNavDialog(strTitle, strDefaultPath, strDefaultExt, "ACSAVEDLG", iFlags, &rbuf) == RTERROR)
		bRes = false;						

	if (bRes)
		strRetPath = rbuf->resval.rstring;	

	acutRelRb(rbuf);

	return bRes;		
} 


/*
bool DialogCompDwg::OpenFile(LPCTSTR strPath)
{

	try
	{
		IAcadApplication IApp;
		IAcadDocument IDoc;
		IAcadModelSpace IMSpace;
		IDispatch *pDisp; 

		pDisp = acedGetAcadWinApp()->GetIDispatch(TRUE); //AddRef is called on the pointer
		IApp.AttachDispatch(pDisp); // does not call AddRef()
		IApp.SetVisible(true);

		pDisp = IApp.GetActiveDocument(); //AddRef is called
		IDoc.AttachDispatch(pDisp);
		pDisp = IDoc.GetModelSpace(); //AddRef is called
		IMSpace.AttachDispatch(pDisp);

		SAFEARRAYBOUND rgsaBound;
		rgsaBound.lLbound = 0L;
		rgsaBound.cElements = 3;
		SAFEARRAY* pStartPoint = NULL;
		pStartPoint = SafeArrayCreate(VT_R8, 1, &rgsaBound);
		// X value
		long i = 0;
		double value = 4.0;
		SafeArrayPutElement(pStartPoint, &i, &value);
		// Y value
		i++;
		value = 2.0;
		SafeArrayPutElement(pStartPoint, &i, &value);
		// Z value
		i++;
		value = 0.0;
		SafeArrayPutElement(pStartPoint, &i, &value);

		VARIANT pt1;
		VariantInit(&pt1);
		V_VT(&pt1) = VT_ARRAY | VT_R8;
		V_ARRAY(&pt1) = pStartPoint;
		IMSpace.AddCircle(pt1, 2.0);

		VariantClear(&pt1);
		// Release() is called implicitly on the local objects
		// the local objects
	}
	catch(COleDispatchException,e) 
	{
			e->ReportError();
			e->Delete();
	}	
}
*/

void DialogCompDwg::OnMnuSetting() 
{
	// TODO: この位置にコマンド ハンドラ用のコードを追加してください
	DialogSetting dlgSet;

	dlgSet.DoModal();
}

//#include "ACSort.h"
//#include "ACCMap.h"

/*
void DialogCompDwg::OnBtnTest5() 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	CMap<int, int, CString, CString> strmapTmp;
	CMap<int, int, int, int> imapRet;

	ACSort sort;
	
	strmapTmp[0] = "aa";		
	strmapTmp[1] = "Aa";		
	strmapTmp[2] = "ab";			
	strmapTmp[3] = "ac";			
	strmapTmp[4] = "ba";			
	strmapTmp[5] = "Bb";			
	strmapTmp[6] = "cc";			
	strmapTmp[7] = "ac";			
	strmapTmp[8] = "a";			
	strmapTmp[9] = "e";			

	sort.QSort(strmapTmp, imapRet);

	CString strRes;
	for (int i = 0; i < imapRet.GetCount(); i++) {
		//strRes += ACCMap::GetKeyVal(strmapTmp, ACCMap::GetKeyVal(imapRet, i)) + '\n';
		strRes += ACCMap::GetKeyVal(strmapTmp, i) + '\n';
	}

	ShowAlert(strRes);
}
*/

// Acadドキュメントウィンドウを左右に分割して表示する。
// iShowDocNum: 表示するドキュメントの番号 1 or 2
void DialogCompDwg::SetDocumentSize(int iShowDocNum)
{
	CMDIFrameWnd *pWndFrm = acedGetAcadFrame();	
	CMDIChildWnd *pWndChild;	
	
	pWndChild = pWndFrm->MDIGetActive();	

	
	// クライアント領域を取得	
	//RECT rectCli;
	//pWndFrm->GetClientRect(&rectCli);		

	// コマンドラインウィンドウの高さが分からないため、一度ウィンドウを最大化し、
	// そのサイズを得て、左右に当分した幅を計算する。	
	RECT rectChild;	
	pWndChild->ShowWindow(SW_SHOWMAXIMIZED);		
	pWndChild->GetWindowRect(&rectChild);

	pWndChild->ShowWindow(SW_SHOWNORMAL);

	// 最大化した高さ-ウィンドウキャプションの高さ　をドキュメントウィンドウの高さとする。
	// 左右の幅についてもスクロールバーを考慮する。
	pWndChild->SetWindowPos(&wndTopMost, 
		(iShowDocNum - 1) * ceil((rectChild.right - rectChild.left) / 2 - 6), 
		0, 
		ceil((rectChild.right - rectChild.left) / 2 - 6), 
		rectChild.bottom - rectChild.top - 30, 
		SWP_NOZORDER | SWP_SHOWWINDOW | SWP_FRAMECHANGED);	
}

/*
void DialogCompDwg::OnBtnTest12() 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	//AcDbViewport *pVp;
	AcDbObjectId idCVPort = acedGetCurViewportObjectId();
	//Acad::ErrorStatus es;
	//int iVpNum;
	
	struct resbuf rb;
    int rt = acedGetVar("CVPORT", &rb);
    if(rt != RTNORM)
    {
        //acutPrintf("\nError acquiring sysvar \"CVPORT\" value.");
        return;
    }

	int iVportNum = rb.resval.rint;
    AcGsView *pView = acgsGetGsView(iVportNum, true);    
	
	if (pView == NULL)
		return;
	

	// ビューの設定
	//AcGePoint3d pt1, pt2;
	//acedDwgPoint pt1, pt2;
    //if(!get2Points(pt1, pt2, false))
     //   return;
    //AcGsView* pView = NULL;
    //int vportNum;
    //if(!getGsViewObj(pView, vportNum))
    //    return;

    AcGePoint3d  camaraPt = pView->position();
    AcGeVector3d upVector = pView->upVector();

	camaraPt[0] += 50;
	camaraPt[1] += 50;

    double fieldWd = pView->fieldWidth();
    double fieldHt = pView->fieldHeight();

    double xShift = 0; //pt1[X] - pt2[X]; 
    double yShift = 0; //pt1[Y] - pt2[Y]; 

    AcGePoint3d targetOrinPt = pView->target();
    AcGePoint3d targetPt(targetOrinPt.x + xShift, 
        targetOrinPt.y + yShift, targetOrinPt.z);
    AcGsView::Projection projType = pView->isPerspective() ?	 
        AcGsView::Projection::kPerspective :
        AcGsView::Projection::kParallel;
    pView->setView(camaraPt, targetPt, upVector, fieldWd, fieldHt, projType);
    pView->update();
}
*/


/*
void DialogCompDwg::OnBtnTest14() 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください

	AcApDocument *pDoc = acDocManager->mdiActiveDocument();
	m_bFocus = false;
	acDocManager->activateDocument(pDoc);
	acDocManager->lockDocument(pDoc);
	acDocManager->sendStringToExecute(pDoc, "1sa\nzoom\na\n", true, true, false);
	//m_bFocus = true;
}
*/

// ハイライトの終了処理　コマンドリアクタから呼ばれる。
void DialogCompDwg::HighlightEnd()
{
	//if (!ms_bUserZoom)
	//	return;
	
	// 選択機能を実行した図面でないときは終了処理をしない。
	//if (ms_pDocUserZoom != acDocManager->mdiActiveDocument())
	//	return;

	ACDocManager acDocMng;
	// 選択した図形をハイライトする。
	//acDocMng.HighlightEntities(ms_idmapHighlight, false);	
	
	// アクティブな図面をロックする。
	//acDocManager->unlockDocument(acDocManager->mdiActiveDocument());

	// フォーカスをウィンドウが保持する
	m_bFocus = true;
	// ウィンドウを再表示する。
	//if (ms_pthis != NULL)
	//	ms_pthis->SetWindowPos(NULL, 0, 0, 100, 100, SWP_SHOWWINDOW |SWP_NOMOVE | SWP_NOSIZE);
	//m_lstGrid.Invalidate();		
	//ms_bUserZoom = false;
}

/*
void DialogCompDwg::OnBtnSel3() 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
		
	//AcApDocument *pDoc = acDocManager->mdiActiveDocument();
	AcDbDatabase *pDb  = acdbHostApplicationServices()->workingDatabase() ;
	AcDbBlockTable *pBlkTbl;
	AcDbBlockTableIterator *pBlkItr;
	Acad::ErrorStatus es;
	bool bChanged = false;

	es = pDb->getBlockTable(pBlkTbl, AcDb::kForRead); 
	if (es != Acad::eOk)
		return;

	es = pBlkTbl->newIterator(pBlkItr);
	pBlkTbl->close();

	if (es != Acad::eOk)
		return;
	
	acDocManager->lockDocument(acDocManager->document(pDb));
	for (pBlkItr->start(); !pBlkItr->done() && !bChanged; pBlkItr->step()) {	
		AcDbBlockTableRecord *pBlkRec;
		if ((es = pBlkItr->getRecord(pBlkRec, AcDb::kForRead)) == Acad::eOk) {					
			AcApLayoutManager *pLayoutMng = (AcApLayoutManager *)acdbHostApplicationServices()->layoutManager();				
			AcDbLayout   *pLayout;			
			AcDbObjectId idLayout;
			Acad::ErrorStatus es;
			idLayout = pBlkRec->getLayoutId();			
			bool bIsPaperOk = false;

			if (acdbOpenObject(pLayout, idLayout, AcDb::kForRead) == Acad::eOk) {
				char *pcPSetName;			
				es = pLayout->getPlotSettingsName(pcPSetName);
				acutDelString(pcPSetName);

				//if (pLayout->getTabSelected() == Adesk::kTrue) 					
				//	bIsSelected = true;
				//else
				//	bIsSelected = false;
						
				pLayout->close();
			}
			
			if (pLayoutMng->showPageSetup() == Adesk::kTrue)
				bIsPaperOk = true;									

			char *pcName;
			pBlkRec->getName(pcName);
			
			if (_stricmp(pcName, "*Model_Space") != 0) {
				if (!idLayout.isNull() && bIsPaperOk) {					
					pLayoutMng->setCurrentLayoutId(idLayout);					
					bChanged = true;
				}
			}
			
			acutDelString(pcName);

			pBlkRec->close();						
		}				
	}

	delete pBlkItr;
	acDocManager->unlockDocument(acDocManager->document(pDb));

}
*/

void DialogCompDwg::TestMakeMap(CMap<int, int, int, int> &imapRet) 
{	
	int i;

	imapRet.InitHashTable(10000);				

	for (i = 0; i < 9999; i++) 
		imapRet[i] = i;	
}

void DialogCompDwg::ShowAlert(LPCTSTR lpszMsg) 
{
	CString strCaption;

	this->GetWindowText(strCaption);
	MessageBox(lpszMsg, strCaption, MB_OK | MB_ICONWARNING); 	
}

void DialogCompDwg::ShowError(LPCTSTR lpszMsg) 
{
	CString strCaption;

	this->GetWindowText(strCaption);
	MessageBox(lpszMsg, strCaption, MB_OK | MB_ICONERROR); //| MB_ICONHAND); 	
}




void DialogCompDwg::OnSize(UINT nType, int cx, int cy) 
{
	// TODO: この位置にメッセージ ハンドラ用のコードを追加してください

	RECT rec;
	const int MARGIN_X          = 14;
	const int MARGIN_TOP        = 14;
	const int MARGIN_BOTTOM     = 14;
	const int WIDTH_BUTTON_L    = 100;
	const int WIDTH_BUTTON_S    = 56;
	const int WIDTH_COMBO       = 150;
	const int WIDTH_LABEL       = 34;
	const int WIDTH_CHK         = 100;
	const int HEIGHT_BUTTON     = 22;
	const int HEIGHT_COMBO      = 28;
	const int HEIGHT_MENU       = 32;
	const int HEIGHT_DROP_LIST  = 100;	
	const int HEIGHT_FRAME_TEXT = 14;	
	const int HEIGHT_CHK        = 18;		
	const int PITCH_X           = 12;
	const int PITCH_Y           = 6;
	const int REV_FRAME_Y       = 4;	
	
	int iWidthCombo;


	//if (cx <= 4 * WIDTH_BUTTON_L + 2 * MARGIN_X + 3 * PITCH_X) {
	//this->MoveWindow(rec.left, rec.top, m_iPreWidth, m_iPreHeitht); 
	//	return;	
	//}
	
	CDialog::OnSize(nType, cx, cy);

	this->GetClientRect(&rec);	
	iWidthCombo = (rec.right - rec.left - 2 * MARGIN_X - 2 * WIDTH_BUTTON_S - 7 * PITCH_X) / 2;		

	m_lstGrid.MoveWindow(
		rec.left + MARGIN_X, 
		rec.top + HEIGHT_FRAME_TEXT + HEIGHT_COMBO + 3 * PITCH_Y, 
		rec.right - rec.left - 2 * MARGIN_X, 
		rec.bottom - rec.top - HEIGHT_COMBO - HEIGHT_COMBO - MARGIN_BOTTOM - HEIGHT_BUTTON - 2 * PITCH_Y 
		  - 3 * PITCH_Y - HEIGHT_CHK- HEIGHT_FRAME_TEXT / 2);				
	
	m_btnCancel.MoveWindow(
		rec.right - WIDTH_BUTTON_L - MARGIN_X, 
		rec.bottom - MARGIN_BOTTOM - HEIGHT_CHK - 2 * PITCH_Y - HEIGHT_BUTTON,
		WIDTH_BUTTON_L,  	
		HEIGHT_BUTTON);

	m_btnComp.MoveWindow(
		rec.left + MARGIN_X + PITCH_X, 
		rec.bottom - MARGIN_BOTTOM - 2 * PITCH_Y - HEIGHT_CHK - HEIGHT_BUTTON,
		WIDTH_BUTTON_L,  	
		HEIGHT_BUTTON);

	m_btnSel1.MoveWindow(
		rec.left + WIDTH_BUTTON_L + MARGIN_X + PITCH_X + 2 * PITCH_X, 
		rec.bottom - MARGIN_BOTTOM - HEIGHT_CHK - 2 * PITCH_Y - HEIGHT_BUTTON,
		WIDTH_BUTTON_L,  	
		HEIGHT_BUTTON);

	m_btnSel2.MoveWindow(
		rec.left + 2 * WIDTH_BUTTON_L + MARGIN_X + 2 * PITCH_X + 2 * PITCH_X,
		rec.bottom - MARGIN_BOTTOM - HEIGHT_CHK - 2 * PITCH_Y - HEIGHT_BUTTON,
		WIDTH_BUTTON_L,  	
		HEIGHT_BUTTON);	
	
	// ADD
	m_statComp.MoveWindow(
		rec.left + MARGIN_X, 
		rec.bottom - MARGIN_BOTTOM - HEIGHT_CHK - HEIGHT_BUTTON - 3 * PITCH_Y - HEIGHT_FRAME_TEXT,
		WIDTH_BUTTON_L + 2 * PITCH_X,  	
		HEIGHT_BUTTON + HEIGHT_CHK + 3 * PITCH_Y + HEIGHT_FRAME_TEXT + REV_FRAME_Y);
	
	m_statCsv.MoveWindow(
		WIDTH_BUTTON_L + 6 * PITCH_X + 2 * WIDTH_BUTTON_L, 
		rec.bottom - MARGIN_BOTTOM - HEIGHT_CHK - HEIGHT_BUTTON - 3 * PITCH_Y - HEIGHT_FRAME_TEXT,
		WIDTH_BUTTON_L + 2 * PITCH_X,  	
		HEIGHT_BUTTON + HEIGHT_CHK + 3 * PITCH_Y + HEIGHT_FRAME_TEXT + REV_FRAME_Y);

	m_chkResDwg.MoveWindow(
		rec.left + MARGIN_X + PITCH_X, 
		rec.bottom - MARGIN_BOTTOM - PITCH_Y - HEIGHT_CHK,
		WIDTH_CHK,  	
		HEIGHT_CHK);

	m_chkExcel.MoveWindow(
		WIDTH_BUTTON_L + 7 * PITCH_X + 2 * WIDTH_BUTTON_L, 
		rec.bottom - MARGIN_BOTTOM - PITCH_Y - HEIGHT_CHK,
		WIDTH_CHK,  	
		HEIGHT_CHK);

	m_btnCsv.MoveWindow(
		WIDTH_BUTTON_L + 7 * PITCH_X + 2 * WIDTH_BUTTON_L, 
		rec.bottom - MARGIN_BOTTOM - HEIGHT_CHK - 2 * PITCH_Y - HEIGHT_BUTTON,
		WIDTH_BUTTON_L,  	
		HEIGHT_BUTTON);

	/////////


	m_btnRef1.MoveWindow(
		rec.left + MARGIN_X + iWidthCombo + 2 * PITCH_X, 
		rec.top + HEIGHT_FRAME_TEXT + PITCH_Y,
		WIDTH_BUTTON_S,  	
		HEIGHT_BUTTON);

	m_btnRef2.MoveWindow(
		rec.right - WIDTH_BUTTON_S - MARGIN_X - 2 * PITCH_Y, 
		rec.top + HEIGHT_FRAME_TEXT + PITCH_Y,
		WIDTH_BUTTON_S,  	
		HEIGHT_BUTTON);		
	
	m_stat1.MoveWindow(
		rec.left + MARGIN_X, 
		rec.top,
		3 * PITCH_X + iWidthCombo + WIDTH_BUTTON_S,  	
		HEIGHT_COMBO + 2 * PITCH_Y + HEIGHT_FRAME_TEXT);

	m_stat2.MoveWindow(
		rec.right - MARGIN_X - WIDTH_BUTTON_S - iWidthCombo - 3 * PITCH_X, 
		rec.top,
		3 * PITCH_X + iWidthCombo + WIDTH_BUTTON_S,  	
		HEIGHT_COMBO + 2 * PITCH_Y + HEIGHT_FRAME_TEXT);		

	m_cboList1.MoveWindow(
		rec.left + MARGIN_X + PITCH_X, 
		rec.top + HEIGHT_FRAME_TEXT + PITCH_Y,
		iWidthCombo,  	
		HEIGHT_COMBO + HEIGHT_DROP_LIST);

	m_cboList2.MoveWindow(
		rec.right - MARGIN_X - WIDTH_BUTTON_S - iWidthCombo - 2 * PITCH_X, 
		rec.top + HEIGHT_FRAME_TEXT + PITCH_Y,
		iWidthCombo,  	
		HEIGHT_COMBO + HEIGHT_DROP_LIST);

	//m_lbl1.MoveWindow(
	//	rec.left + MARGIN_X, 
	//	rec.top + PITCH_Y + REV_LABEL_Y,
	//	WIDTH_LABEL,  	
	//	HEIGHT_BUTTON);

	//m_lbl2.MoveWindow(
	//	rec.right - WIDTH_LABEL - iWidthCombo - WIDTH_BUTTON_S - MARGIN_X - PITCH_X, 
	//	rec.top + PITCH_Y + REV_LABEL_Y,
	//	WIDTH_LABEL,  	
	//	HEIGHT_BUTTON);
		
		
	m_btnCancel.RedrawWindow();

	m_statCsv.RedrawWindow();

	m_btnComp.RedrawWindow();
	m_btnSel1.RedrawWindow();
	m_btnSel2.RedrawWindow();
	m_btnRef1.RedrawWindow();	
	m_btnRef2.RedrawWindow();
	m_stat1.RedrawWindow();
	m_stat2.RedrawWindow();
	m_cboList1.RedrawWindow();
	m_cboList2.RedrawWindow();
		
	m_statComp.RedrawWindow();	
	
	m_chkResDwg.RedrawWindow();
	m_chkExcel.RedrawWindow();
	m_btnCsv.RedrawWindow();

	m_lstGrid.RedrawWindow();

	this->RedrawWindow();			
}

// ユーザーに保存先を指定させ、比較結果のCSVを出力する。
// @T: CSVが既に存在している場合; 存在し、Excelに開かれている場合はどうなるか？
// @T: 比較結果がないときに警告MSGが表示されるか？
// @T: ダイアログでキャンセルされたとき、ウェイトカーソルが元に戻ること。
void DialogCompDwg::OnBtnCsv() 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	ACProfileManager proMng;
	CString strRetPath, strDefDir;	
	
	try {
		this->BeginWaitCursor();
		
		// 比較結果が存在するかどうかのチェック
		if (m_lstGrid.GetItemCount() == 0)
			throw (new ACErrorInfo(ACErrorInfo::ALERT, "比較結果がありません。"));

		// プロファイルからオープンディレクトリパスを得る。
		// そのパスが有効でないときは、空文字をセットする。
		strDefDir = proMng.GetUserSaveCSVPath();
		if (_access(strDefDir, 0) == -1)
			strDefDir = "";
		
		// 図面ファイル選択ダイアログを表示する。
		if (!SaveFileDialog("名前を付けて保存", strDefDir, "csv", strRetPath)) 
			throw (new ACErrorInfo(ACErrorInfo::NONE, ""));
		
		// ユーザーが指定したファイルに比較結果を書き込む。	
		WriteCSV(strRetPath);

		// 選択パスをプロファイルにセットする。
		strDefDir = ACString::GetSegmentR(strRetPath, '\\', false, false);
		strDefDir = strDefDir + '\\';
		proMng.SetUserSaveCSVPath(strDefDir);							
		
		// チェックがされているときのみExcelを起動する。
		if (m_chkExcel.GetCheck() == 1) {
			CString strBootPath = "\"" + strRetPath + "\"";
			ShellExecute(this->m_hWnd, "open", "EXCEL", strBootPath, NULL, SW_SHOW);
		}

		throw (new ACErrorInfo(ACErrorInfo::NONE, ""));		
	}
	catch (ACErrorInfo *pEI) {
		CString strCaption;		
		
		this->EndWaitCursor();					
		this->GetWindowText(strCaption);
		pEI->ShowMsgDlg(this->m_hWnd, strCaption);
		
		// ダイアログ表示後にアクティブな図面をコマンド終了状態にするため、無意味なコマンドを送る。
		AcApDocument *pDocBefore = acDocManager->mdiActiveDocument();
		acDocManager->sendStringToExecute(pDocBefore, DCD_DUMMY_COMMAND, false, true, false);
		this->SetFocus();

		delete pEI;		
	}
	catch (CException *pExc)
	{
		char cBuff[256];
		
		this->EndWaitCursor();	

		pExc->GetErrorMessage(cBuff, 256);
		ShowError(cBuff);		

		// ダイアログ表示後にアクティブな図面をコマンド終了状態にするため、無意味なコマンドを送る。
		AcApDocument *pDocBefore = acDocManager->mdiActiveDocument();
		acDocManager->sendStringToExecute(pDocBefore, DCD_DUMMY_COMMAND, false, true, false);
		this->SetFocus();

		pExc->Delete();
	}
}



void DialogCompDwg::WriteCSV(LPCTSTR strCSVPath)
{
	CStdioFile cFile;
	CFileException cfExp;	
	int iItemIdx = -1;
	int iFlags   = LVNI_ALL;	
	
	if (!cFile.Open(strCSVPath, CFile::modeWrite | CFile::modeCreate, &cfExp)) {
		CString strErrMsg;
		strErrMsg.Format("ファイルオープンエラー: %d", cfExp.m_cause);
		throw (new ACErrorInfo(ACErrorInfo::ERR, strErrMsg));
	}
	
	// タイトル行の出力
	CString strTitle;
	for (int i = 0; i < (int)ListGrid::KEY; i++) {   // ハイパーリンクまで出力される。キーは出力されない。
		if (i > 0)
		strTitle = strTitle + ",";
		strTitle = strTitle + "\"" + m_lstGrid.GetColumnName(i) + "\"";
	}
	strTitle = strTitle + "\n"; 
	cFile.WriteString(strTitle);

	// 比較結果の出力
	while ((iItemIdx = m_lstGrid.GetNextItem(iItemIdx, iFlags)) != -1) {
		CString strLineOutput;	
		for (int j = 0; j < (int)ListGrid::KEY; j++) {
			LVITEM lvItem;
			char cBuff[DCD_MAX_OUTPUT];

			lvItem.mask = LVIF_TEXT;
			lvItem.iItem = iItemIdx;		
			lvItem.pszText = cBuff;
			lvItem.cchTextMax = sizeof(cBuff);			
			lvItem.iSubItem = j;
			m_lstGrid.GetItem(&lvItem);
			
			if (j > 0)
				strLineOutput = strLineOutput + ",";

			// 数値のとき
			if (m_lstGrid.GetColType(j) == 0)
				strLineOutput = strLineOutput + cBuff;
			// 文字列のとき
			else
				strLineOutput = strLineOutput + "\"" + cBuff + "\"";			
			//i++;			
		}		
		strLineOutput += "\n";
		cFile.WriteString(strLineOutput);
	}	
	cFile.Close();
}

void DialogCompDwg::OnBtnTest1() 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください

	// コンボボックスで選択している項目のインデックスを得る。
	int iCurIdx1, iCurIdx2;		

	if ((iCurIdx1 = m_cboList1.GetCurSel()) == CB_ERR)
		throw (new ACErrorInfo(ACErrorInfo::ALERT, "図面1を選択してください。"));

	if ((iCurIdx2 = m_cboList2.GetCurSel()) == CB_ERR)
		throw (new ACErrorInfo(ACErrorInfo::ALERT, "図面2を選択してください。"));

	// 現在選択している図面のBlockTableのIDを得る。
	AcDbObjectId idBlkTbl1, idBlkTbl2;

	idBlkTbl1 = m_idaryBlkTbl1[m_cboList1.GetItemData(iCurIdx1)];
	idBlkTbl2 = m_idaryBlkTbl2[m_cboList2.GetItemData(iCurIdx2)];				
	
	
	// ウィンドウを最小化する。
	m_bFocus = false;		
	CWnd *pWndAcad = AcUiMainWindow();	
	// ウィンドウを非表示にする。
	this->SetWindowPos(pWndAcad, 
		0, 0, 0, 0, SWP_HIDEWINDOW | SWP_NOACTIVATE | SWP_NOMOVE | SWP_NOSIZE);	

	// doc1をアクティブにし、2点ポイントを選択する。
	AcApDocument *pDoc;
	pDoc = acDocManager->document(idBlkTbl1.database());
	
	try {
		acDocManager->setCurDocument(pDoc, AcAp::kNone, true);	

		ads_point aptSel;
		
		if (acedGetPoint(NULL, "\n図面1の比較範囲を指定：1点目：", aptSel) != RTNORM) {
			throw (new ACErrorInfo(ACErrorInfo::ALERT, 
				"\n選択に失敗しました。"));				
		}		

		if (acedGetPoint(NULL, "\n図面1の比較範囲を指定：2点目：", aptSel) != RTNORM) {
			throw (new ACErrorInfo(ACErrorInfo::ALERT, 
				"\n選択に失敗しました。"));				
		}			

		// doc2をアクティブにし、1点ポイントを選択する。	
		pDoc = acDocManager->document(idBlkTbl2.database());
			
		acDocManager->setCurDocument(pDoc, AcAp::kNone, true);	
		if (acedGetPoint(NULL, "\n\図面2の比較基点を指定：", aptSel) != RTNORM) {
			throw (new ACErrorInfo(ACErrorInfo::ALERT, 
				"\n選択に失敗しました。"));			
		}			

		// ウィンドウを再表示する。
		this->SetWindowPos(NULL, 0, 0, 100, 100, SWP_SHOWWINDOW |SWP_NOMOVE | SWP_NOSIZE);		
	}	
	catch (ACErrorInfo *pErrInfo) {
		m_bFocus = true;
		// ウィンドウを再表示する。
		this->SetWindowPos(NULL, 0, 0, 100, 100, SWP_SHOWWINDOW |SWP_NOMOVE | SWP_NOSIZE);
		ShowAlert(pErrInfo->m_strMsg);
		delete pErrInfo;
	}
}
