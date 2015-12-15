// LayoutInfo.h: LayoutInfo クラスのインターフェイス
// レイアウトと関連付いたブロックテーブルレコードの情報を保持する。
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LAYOUTINFO_H__A30FA471_E9B2_4C80_85AB_441776D5AC49__INCLUDED_)
#define AFX_LAYOUTINFO_H__A30FA471_E9B2_4C80_85AB_441776D5AC49__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class LayoutInfo  
{
public:
	LayoutInfo();
	virtual ~LayoutInfo();
	
	void SetInfo(LPCTSTR strName, AcDbObjectId idBlkRec);

	LPCTSTR GetLayoutName();
	AcDbObjectId &GetBlockTableRecordId();

private:
	AcDb m_strLayoutName;
	AcDbObjectId m_idBlkRec;
};

#endif // !defined(AFX_LAYOUTINFO_H__A30FA471_E9B2_4C80_85AB_441776D5AC49__INCLUDED_)
