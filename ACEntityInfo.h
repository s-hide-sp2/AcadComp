// ACEntityInfo.h: ACEntityInfo クラスのインターフェイス
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ACENTITYINFO_H__07D9B97F_8F82_45C2_9FF8_83AC34F68573__INCLUDED_)
#define AFX_ACENTITYINFO_H__07D9B97F_8F82_45C2_9FF8_83AC34F68573__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//#define ACE_DXF_HYPERLINK 1000  // ハイパーリンクが収められているDXFコード
#define ACE_DXF_HYPERLINK 1002  //kDxfXdControlString

class ACEntityInfo  
{
public:
	ACEntityInfo();
	virtual ~ACEntityInfo();
	
	// 指定したエンティティのハイパーリンクの値を得る。
	// ハイパーリンクが設定されていない場合はNULLを返す。
	static CString GetHyperLink(AcDbEntity *pEnt);
};

#endif // !defined(AFX_ACENTITYINFO_H__07D9B97F_8F82_45C2_9FF8_83AC34F68573__INCLUDED_)
