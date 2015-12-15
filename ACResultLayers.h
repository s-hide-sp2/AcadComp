// ACResultLayers.h: ACResultLayers クラスのインターフェイス
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ACRESULTLAYERS_H__6754B687_7594_40CB_811B_54B2B206440E__INCLUDED_)
#define AFX_ACRESULTLAYERS_H__6754B687_7594_40CB_811B_54B2B206440E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class ACResultLayers  
{
public:
	ACResultLayers();
	virtual ~ACResultLayers();
	
	// 修正が無い、修正あり、追加、削除の図形のレイヤーのオブジェクトID
	AcDbObjectId m_idNotModify;
	AcDbObjectId m_idModify;
	AcDbObjectId m_idAdd;
	AcDbObjectId m_idDelete;

};

#endif // !defined(AFX_ACRESULTLAYERS_H__6754B687_7594_40CB_811B_54B2B206440E__INCLUDED_)
