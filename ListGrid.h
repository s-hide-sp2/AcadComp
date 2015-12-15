#if !defined(AFX_LISTGRID_H__F5BCA644_A498_40E1_B161_575D9D9DD87D__INCLUDED_)
#define AFX_LISTGRID_H__F5BCA644_A498_40E1_B161_575D9D9DD87D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ListGrid.h : ヘッダー ファイル
//

#include <afxcview.h>

// [ADD] 
#include "ResultCompEntity.h"

/////////////////////////////////////////////////////////////////////////////
// ListGrid ビュー

#define LG_NUM_FIELD 19


// エンティティ比較に特化したグリッドクラス
class ListGrid : public CListCtrl
{
protected:
public:
	ListGrid();           // 動的生成に使用されるプロテクト コンストラクタ
	DECLARE_DYNCREATE(ListGrid)

// アトリビュート
public:
	
// オペレーション
public:	

// オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。

	//{{AFX_VIRTUAL(ListGrid)
	protected:
	virtual void OnDraw(CDC* pDC);      // このビューを描画するためにオーバーライドしました。
	//}}AFX_VIRTUAL
	
	virtual void DrawItem( LPDRAWITEMSTRUCT lpDrawItemStruct );
	

// インプリメンテーション
protected:
public:
	virtual ~ListGrid();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// 生成されたメッセージ マップ関数
protected:
	//{{AFX_MSG(ListGrid)
	
	virtual BOOL OnNotify( WPARAM wParam, LPARAM lParam, LRESULT* pResult );

	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	//void GetClientRect( LPRECT lpRect ) const;

	int GetColCount();
	CString GetColumnName(int iIdx);
	enum LG_FIELD_IDX {
		RESULTALL,
		RESULTGEOM,
		TYPE1,
		TYPE2,
		COLOR1,
		COLOR2,
		LAYER1,
		LAYER2,
		LINETYPE1,
		LINETYPE2,
		LINETYPESCALE1,
		LINETYPESCALE2,
		PLOTSTYLE1,
		PLOTSTYLE2,
		LINEWEIGHT1,
		LINEWEIGHT2,
		HYPERLINK1,
		HYPERLINK2,
		KEY
	};		
	
	// 列の項目を設定する。
	void InitGridCompEntity();

	// 結果を表示する。
	void ShowResultCompEntity(ResultCompEntity &rce);
	
	// lParamを再セットする。
	void SetlParam();

	enum EHighlight {HIGHLIGHT_NORMAL, HIGHLIGHT_ALLCOLUMNS, HIGHLIGHT_ROW};

	// 各列の昇順、降順を保持する。true: 昇順、false: 降順
	bool m_bOrderAsc[LG_NUM_FIELD];

	int GetColType(int iIdx);
protected:
	int  m_nHighlight;		// Indicate type of selection highlighting

private:
	// 指定した列の(見えている範囲の)全行の内容を表示するのに必要な幅を取得する。
	int GetMaxViewColumnWidth(int iCol) const; 
	int m_iColType[LG_NUM_FIELD];
	int m_iColSize[LG_NUM_FIELD];
	CString m_strColName[LG_NUM_FIELD];
	
	CImageList m_imglstIcon;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_LISTGRID_H__F5BCA644_A498_40E1_B161_575D9D9DD87D__INCLUDED_)
