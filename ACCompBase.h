// ACCompBase.h: ACCompBase クラスのインターフェイス
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ACCOMPBASE_H__BF30EC2F_9D90_40B6_9A68_8685BFF57FE0__INCLUDED_)
#define AFX_ACCOMPBASE_H__BF30EC2F_9D90_40B6_9A68_8685BFF57FE0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "StdAfx.h"

class ACCompBase  
{
public:
	ACCompBase();
	virtual ~ACCompBase();
	
	// 図形比較時の許容誤差をセットする。
	static void SetTol(double dTol);

	// 図形比較時の許容誤差を得る。
	//static void GetTol(double dTol);

public: //protected:
	// 指定した2つの値が許容誤差の範囲内で等しいかどうかを返す。
	bool IsEqual(const double &dVal1, const double &dVal2);
	
	// 指定した2つの2dポイントが許容誤差の範囲内で等しいかどうかを返す。
	bool IsEqual(const AcGePoint2d &pt2_1, const AcGePoint2d &pt2_2); 

	// 指定した2つの3dポイントが許容誤差の範囲内で等しいかどうかを返す。
	// 比較範囲の基点のずれを考慮しないタイプ
	bool IsEqualNoGap(const AcGePoint3d &pt3_1, const AcGePoint3d &pt3_2);

	// 指定した2つの3dポイントが許容誤差の範囲内で等しいかどうかを返す。
	bool IsEqual(const AcGePoint3d &pt3_1, const AcGePoint3d &pt3_2); 
	
	// 指定した2つの2dベクトルが許容誤差の範囲内で等しいかどうかを返す。
	bool IsEqual(const AcGeVector3d &vec3_1, const AcGeVector3d &vec3_2); 

	// 指定した2つの3dポイント配列が許容誤差の範囲内で等しいかどうかを返す。
	// 配列数が異なる場合はfalseを返す。
	bool IsEqual(const AcGePoint3dArray &pt3ary1, const AcGePoint3dArray &pt3ary2); 
	
	// 指定した2つのdouble配列が許容誤差の範囲で等しいかどうかを返す。
	// 配列数が異なる場合はfalseを返す。
	bool IsEqual(const AcGeDoubleArray &dary1, const AcGeDoubleArray &dary2); 

	// 指定した2つの平面が許容誤差の範囲で等しいかどうかを返す。	
	bool IsEqual(const AcGePlane &dpln1, const AcGePlane &dpln2); 

	// 指定した2つの2dベクトルが許容誤差の範囲で等しいかどうかを返す。
	bool IsEqual(const AcGeVector2d &vec2_1, const AcGeVector2d &vec2_2); 
	
	// 指定した2つの3dスケールが許容誤差の範囲で等しいかどうかを返す。
	bool IsEqual(const AcGeScale3d &scl3_1, const AcGeScale3d &scl3_2);

	// AcGeクラスの比較
	//AcGeCircArc2d の比較
	//bool IsEqual(const AcGeCircArc2d &cArc1, const AcGeCircArc2d &cArc2);

	//AcGeEllipArc2d の比較
	//bool IsEqual(const AcGeEllipArc2d &eArc1, const AcGeEllipArc2d &eArc2);	 

	//AcGeLineSeg2d の比較
	//bool IsEqual(const AcGeLineSeg2d &lineSeg1, const AcGeLineSeg2d &lineSeg2);
	 
	//AcGeNurbCurve2d の比較
	//bool IsEqual(const AcGeNurbCurve2d &nCurve1, const AcGeNurbCurve2d &nCurve2);


	


	// ---- 以下は許容誤差を考慮しない比較 ----

	//bool IsEqual(const bool ab1, const bool ab2);

	// Adesk::Boolean型の比較
	//bool IsEqual(const Adesk::Boolean ab1, const Adesk::Boolean ab2);

	// AcCmColor型の比較
	bool IsEqual(const AcCmColor &clr1, const AcCmColor &clr2);

	// int型の比較
	bool IsEqual(const int &i1, const int &i2); 

	// AcDb::LineWeight型の比較
	bool IsEqual(const AcDb::LineWeight lw1, const AcDb::LineWeight lw2); 
	
	// AcDb::Vertex2dType型の比較
	bool IsEqual(const AcDb::Vertex2dType &vtx2Type1, const AcDb::Vertex2dType &vtx2Type2);
	
	// FlowDirection型の比較
	bool IsEqual(const AcDbMText::FlowDirection &fDir1, const AcDbMText::FlowDirection &fDir2);
	
	// AcDb::LineSpacingStyle型の比較
	bool IsEqual(const AcDb::LineSpacingStyle &lineSpcStl1, const AcDb::LineSpacingStyle &lineSpcStl2);

	// bool型の比較
	bool IsEqual(const bool &b1, const bool &b2);
	
	// StandardScaleType型の比較
	bool IsEqual(const AcDbViewport::StandardScaleType &ssclType1, const AcDbViewport::StandardScaleType &ssclType2);
	
	// Adesk::Int16型の比較
	bool IsEqual(const Adesk::Int16 &aint1, const Adesk::Int16 &aint2);

	//AcGeTol の比較
	bool IsEqual(const AcGeTol &tol1, const AcGeTol &tol2);

public:
	void SetBasePointGap(const AcGeVector3d &vec3BasePointGap);
	// 文字列の比較をする。
	bool IsEqualStr(const TCHAR *pcStr1, const TCHAR *pcStr2); 

private:
	// 図形比較時の許容誤差
	static double  m_dTol; 
	static AcGeTol m_geTol; 

protected:
	// 図面1の比較基点座標から図面2の比較基点座標へのベクトル。範囲比較モード時のみ設定する。
	AcGeVector3d m_vec3BasePointGap;      // 範囲比較モードで設定されたギャップ
	AcGeVector3d m_vec3BasePointGapApply; // 実際に比較時に適用するギャップ
};

#endif // !defined(AFX_ACCOMPBASE_H__BF30EC2F_9D90_40B6_9A68_8685BFF57FE0__INCLUDED_)
