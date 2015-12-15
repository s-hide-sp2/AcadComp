// LayoutBlkRecMap3.h: LayoutBlkRecMap3 クラスのインターフェイス
// 図面1、図面2、新図面のそれぞれのブロックレコードID（レイアウト空間のみ）の対応関係を保持する。
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LAYOUTBLKRECMAP3_H__C21D5316_76CF_45C6_B933_2F399E507DA4__INCLUDED_)
#define AFX_LAYOUTBLKRECMAP3_H__C21D5316_76CF_45C6_B933_2F399E507DA4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class LayoutBlkRecMap3  
{
public:
	LayoutBlkRecMap3();
	LayoutBlkRecMap3(AcDbObjectId idDwg1LayoutBlkRec, AcDbObjectId idDwg2LayoutBlkRec, AcDbObjectId idNewDwgLayoutBlkRec);
	virtual ~LayoutBlkRecMap3();

	void SetDwg1LayoutBlkRecObjectId(AcDbObjectId idBlkRecObject);
	void SetDwg2LayoutBlkRecObjectId(AcDbObjectId idBlkRecObject);
	void SetNewDwgLayoutBlkRecObjectId(AcDbObjectId idBlkRecObject);

	AcDbObjectId &GetDwg1LayoutBlkRecObjectId();
	AcDbObjectId &GetDwg2LayoutBlkRecObjectId();
	AcDbObjectId &GetNewDwgLayoutBlkRecObjectId();

private:
	AcDbObjectId m_idDwg1LayoutBlkRec;
	AcDbObjectId m_idDwg2LayoutBlkRec;
	AcDbObjectId m_idNewDwgLayoutBlkRec;


};

#endif // !defined(AFX_LAYOUTBLKRECMAP3_H__C21D5316_76CF_45C6_B933_2F399E507DA4__INCLUDED_)
