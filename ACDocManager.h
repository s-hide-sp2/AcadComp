// ACDocManager.h: ACDocManager クラスのインターフェイス
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ACDOCMANAGER_H__7641E627_F0E1_4B31_B44E_CF2702644CB8__INCLUDED_)
#define AFX_ACDOCMANAGER_H__7641E627_F0E1_4B31_B44E_CF2702644CB8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// [ADD]
#define ACDM_EXTENTS_MIN  0.5
#define ACDM_EXTENTS_RATE 3
#define ACDM_INFINITE_ENT_ZOOM_RATE 400
#define ACDM_COLOR_EQUAL      8 
#define ACDM_COLOR_NOT_EQUAL 20
#define ACDM_COLOR_DELETE   142
#define ACDM_COLOR_NEW        3
#define ACDM_COLOR_LAYER      7 
#define ACDM_COLOR_BYBLOCK    0
#define ACDM_FILE_NAME_BIGFONT _T("BIGFONT.SHX") //2006.07.20
#define	ACDM_RESULTAPPNAME	_T("ACADCOMP_RESULTAPP")
#define	ACDM_RESULTXDATA	_T("ACADCOMP_RESULTDRAWING")

// 変更前文字列レイヤー
#define ACDM_PREVMODIFY_COLOR	26
#define ACDM_PREVMODIFY_LAYER	_T("ZZ_変更前文字列")

#include "InfoDwgEntity.h"
#include "ResultCompEntity.h"
//#include "AcConvertColor.h"
#include "ACConvertName.h"
#include "ACCompEntitiesGeom.h"
#include "ACCMap.h"
#include "ACSort.h"
#include "ACEntityInfo.h"
#include "ACRetType.h"
#include "ACResultLayers.h"
#include "ACCompRect.h"


class ACDocManager  
{
public:
	ACDocManager();
	virtual ~ACDocManager();		

	// 現在開いている全図面のパスの配列を得る。
	void GetDocPaths(CStringArray &saryRet, AcDbObjectIdArray &idaryBlkTbl);

	// パスを指定して、図面オブジェクトを得る。該当する図面がないときはfalseを返す。
	bool GetDoc(LPCTSTR lpctDwgPath, AcApDocument *pDoc);
	
	// 指定した図面を比較し、結果を得る。
	bool CompDwgs(
		CMap<int, int, AcDbObjectId, AcDbObjectId> &idmap1, 
		CMap<int, int, AcDbObjectId, AcDbObjectId> &idmap2,
		ResultCompEntity &rce);

	// 指定した図面の全ての図形要素のIDを得る。
	bool GetDwgAllEntityIds(AcApDocument *pDoc1, CMap<int, int, AcDbObjectId, AcDbObjectId> &idmapRet);
	
	// 指定したパスの図面の全ての図形要素のIDを得る。
	bool GetDwgAllEntityIds(const AcDbObjectId &idBlkTbl, CMap<int, int, AcDbObjectId, AcDbObjectId> &idmapRet);

	// 指定したIDの図形をハイライトする。指定された図形がない場合も考慮する。
	// 対象は一つの図面のみ？ 空間が違うときは無効
	bool HighlightEntities(const CMap<int, int, AcDbObjectId, AcDbObjectId> &idmapEnt, bool bOn);
	
	// 指定したIDの図形の範囲を得る。
	bool GetEntityExtents(const CMap<int, int, AcDbObjectId, AcDbObjectId> &idmapEnt, AcGePoint2d &pt2LB, AcGePoint2d &pt2RT);	

	// 指定した範囲を拡張する。
	void Extents(AcGePoint2d &pt2LB, AcGePoint2d &pt2RT);

	// 指定されたオブジェクトIDの配列をオブジェクトハンドル順にソートする。
	void SortEntities(CMap<int, int, AcDbObjectId, AcDbObjectId> &idmapSort);

	// オートメーションを使ってズームを実行する。
	bool AutomationZoom(const AcGePoint2d &pt2LB, const AcGePoint2d &pt2RT);	

	// アクティブな図面に対し、オートメーションでコマンドを送る。
	bool AutomationCommand(LPCTSTR strCmd);	

	// 指定したIDのブロックテーブルを持つドキュメント(データベース)がコマンド使用中であるかどうか調べる。
	ACRetType::ACRETTYPE CheckDwg(const AcDbObjectId &idBlkTbl);

	// カレント図面を保持する。
	void SetCurDoc();

	// 元のカレント図面をアクティブにする。
	void ReturnCurDoc();
	
	// 新しい図面を作成し、アクティブにする。
	bool CreateNewDwg();

	// 現在アクティブな図面に比較結果を色で表現した図形を描く。		
	// idNewDwgBlockTable: 新図面のブロックテーブルのID
	// idOldDwgBlockTable: 旧図面のブロックテーブルのID
	// idMapNew: 
	bool DrawResultDwg(AcDbObjectId idNewDwgBlockTable, AcDbObjectId idOldDwgBlockTable, 
		ResultCompEntity &rce, CMap<int, int, AcDbObjectId, AcDbObjectId> &idMapNew);

	// SetCurDocで保持した図面をロック解除する。
	void UnlockCurDoc();
	
	// 指定したDBで、レイアウトになっていないブロックテーブルレコードをレイアウト化する。
	bool CreateLayout(AcDbDatabase *pDb);
	
private:
	// 読み込みでオープン状態のエンティティを比較し、結果を返す。
	// どちらかのエンティティがない場合は片方をNULLにして書き込む。
	void CompEntities(AcDbEntity *pEnt1, AcDbEntity *pEnt2, int &iIdx, ResultCompEntity &rce);
	
	// 指定されたエンティティのジオメトリの違いを調べる。
	//bool CompareEntitiesGeom(AcDbEntity *pEnt1, AcDbEntity *pEnt2);	

	// オブジェクトIDの配列より、オブジェクトハンドルの配列を得る。
	void GetEntityHandles(
		CMap<int, int, AcDbObjectId, AcDbObjectId> &idmapSort,
		CMap<int, int, CString, CString> &strmapRet);	

	// 結果情報クラスに情報を書き込む
	void RCESetValue1(int iIdx, ResultCompEntity &rce, AcDbEntity *pEnt);

	// 結果情報クラスに情報を書き込む
	void RCESetValue2(int iIdx, ResultCompEntity &rce, AcDbEntity *pEnt);

	// ビューオブジェクトを得る。
	bool GetGsView(AcGsView*& pView, int& iVportNum);
	
	// CMapのIDで、idOwnerがオーナーであるものをidaryRetにセットする。
	void IdFilterByOwner(CMap<int, int, AcDbObjectId, AcDbObjectId> &idMap, 
		const AcDbObjectId &idOwner, AcDbObjectIdArray &idaryRet);
	
	// pDbのブロックテーブルレコードのIDの配列を得る。
	bool GetBlockTableRecordIdArray(AcDbDatabase *pDb, AcDbObjectIdArray &idaryBlkRec);

	// 指定されたIDマップのクローンされた方の図形の色を白にする。
	bool ClonedColorWhite(const AcDbIdMapping &idMap);

	// 指定されたIDマップ内で、idSearchと一致するKEYを探し、そのペアのObjectIdを返す。
	bool SearchClonedPairId(const AcDbIdMapping &idMap, const AcDbObjectId &idSearch, AcDbObjectId &idRet);

	// 指定したDBの全てのレイヤーの色を白にする。
	bool AllLayerDisable(AcDbDatabase *pDb, bool bUnLock, bool bNoFreeze, bool bAllVisible);

	// 指定されたIDの図形の色を指定された色に変更する。ブロック図形の場合は、構成要素の色も同じにする。
	bool SetEntityColor(AcDbObjectId idEnt, Adesk::UInt16 uiColIdx);

	// 指定されたDBのレイアウト空間のID列を得る。
	void GetLayoutBlkRecObjectIdArray(AcDbDatabase *pDb, AcDbObjectIdArray &idaryRetLayout);

	// アクティブな図面に、先の操作で得たレイアウト列のうち、ハンドルが存在しないものを作成する。
	// レイアウトID列と、新規図面のIDのマップを作成する。		
	//bool CreateLayout(AcDbDatabase *pDb, const AcDbObjectIdArray &idaryRefLayout, 
	//	CArray<LayoutBlkRecMap3, LayoutBlkRecMap3> &idaryRetMapLayout);
		
	bool SetMlineStyle(AcDbDatabase *pDb, UINT uiColIdx);

	bool SetDimStyle(AcDbDatabase *pDb, UINT uiColIdx);

	// 寸法スタイルの色を設定する。
	bool SetAllTextStyle(AcDbDatabase *pDb);
	
	// コピーした外部参照をバインドする。
	void BindXRef(const AcDbIdMapping &idMap);
	
	// 変更無し、追加、修正、削除の結果を色で表現するレイヤーを作成する。
	bool CreateResultLayers(AcDbDatabase *pDb, ACResultLayers &resLayers);

	// 変更前文字列レイヤーを作成する。
	bool CreateBeforeModifyLayers(AcDbDatabase *pDb);

	// 指定した名前を付けたレイヤーを返す。レイヤーが既に存在する場合は指定した名前の後に番号を付ける。
	//bool CreateNameLayer(const AcDbDatabase *pDb, const ACCreateLayerInfo &lyrInfo, AcDbObjectId &idRetLayer);

	// 指定されたオブジェクトIDが引き出し線のものであるか調べる。
	bool IsAcDbLeaderId(AcDbObjectId idEnt);

public:	
	// ブロックテーブルのIDがidBlkTblである図面の、extRangeの範囲にあるエンティティを取得し、オブジェクトIDのMAPを得る。
	bool GetRangeEntityIds(const AcDbObjectId &idCompRect, CMap<int, int, AcDbObjectId, AcDbObjectId> &idmapRet);
	// idBlkTblで指定した図面より、COMPRECTコマンドで作成した比較範囲の矩形のIDを得る。戻り値で比較範囲の矩形の個数を得る。
	long GetCompRectId(const AcDbObjectId &idBlkTbl, AcDbObjectId &idRetCompRect);
	// 渡された図形ID列の内、同じ空間にある図形のID列を返す。
	bool GetSameSpaceEntities(
		const CMap<int, int, AcDbObjectId, AcDbObjectId> &idmapEnt,
		CMap<int, int, AcDbObjectId, AcDbObjectId> &idmapRetEnt);

	// 指定したID列の最初のエンティティのある空間へ切り替える。その図面をアクティブにする。
	// 有効な図形がなかった場合と、図面をアクティブにするのに失敗した場合と、切り替えられなかった場合はfalse
	bool ChangeToFirstEntitySpace(const CMap<int, int, AcDbObjectId, AcDbObjectId> &idmapEnt);

private:
	// 外部参照を図面間でコピーする。	
	bool CopyXRefBlock(AcDbDatabase *pDbSrc, AcDbDatabase *pDbDst);

	// 外部参照を図面間でコピーする。
	bool ACDocManager::CopyXRefBlock(AcDbDatabase *pDbSrc, AcDbIdMapping &idMap, AcDbDatabase *pDbDst);

	// 指定したエンティティが属する空間のIDを返す。
	// オーナーが空間でないときは、そのオーナーを辿っていく。
	// 失敗した場合はfalseを返す。
	bool GetSpaceId(const AcDbEntity *pEnt, AcDbObjectId &idRetSpace);

public:	
	void SetRangeCompMode(const AcGeVector3d &vec3Gap);
	// IDで指定したエンティティの範囲を得る。
	// XlineとRayはそれぞれの位置と方向より得る。
	bool GetGeomExtents(AcDbObjectId idEnt, AcDbExtents &extRet);

	// 指定したデータベースを、モデル空間へ切り替える。
	bool ChangeToModelSpace(AcDbDatabase *pDb);

private:
	// Wcs座標からUcs座標へ変換する。
	bool WcsToUcs2d(const AcGePoint2d &pt2Wcs, AcGePoint2d &pt2RetUcs);

	

	// 指定したエンティティが属する空間へ切り替える。	
	bool ChangeToEntitySpace(const AcDbObjectId &idEnt);	

	// 指定したデータベースを、指定した空間へ切り替える。
	bool ChangeToSpace(AcDbDatabase *pDb, const AcDbObjectId &idSpace);

	// 指定したデータベースのモデル空間ブロックのIDを得る。
	bool GetModelSpaceId(AcDbDatabase *pDb, AcDbObjectId &idRet); 

	// 指定したデータベースで現在コマンドが使用中であるかどうかを調べる。
	bool IsCommandRunning(AcDbDatabase *pDb); 
	
	// 指定したDBのペーパー空間タブを全て削除する。
	bool DeleteAllTabs(AcDbDatabase *pDb);

	// カレント図面を保持する。
	AcApDocument *m_pDocCur;	

	// 範囲比較モードのときは、旧図面の図形を、比較範囲の基点のずれの分だけ移動する。
	bool MoveGap(AcDbIdMapping &idMap);

	// 範囲比較モード
	bool m_bRangeCompMode; 
	// 図面1の比較基点から図面2の比較範囲へのベクトル。範囲比較モード時のみ指定する。
	AcGeVector3d m_vec3Gap; 
public:
	bool SetResultXData(AcDbObjectId idModel);
};

#endif // !defined(AFX_ACDOCMANAGER_H__7641E627_F0E1_4B31_B44E_CF2702644CB8__INCLUDED_)
