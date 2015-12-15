// ACConvertName.cpp: ACConvertName クラスのインプリメンテーション
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "resource.h"
#include "ACConvertName.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// 構築/消滅
//////////////////////////////////////////////////////////////////////

ACConvertName::ACConvertName()
{

}

ACConvertName::~ACConvertName()
{

}

CString ACConvertName::GetColorStr(int iColIdx)
{
	//2006.07.20
	CString strColor[7] = {
		_T("Red"), 
		_T("Yellow"), 
		_T("Green"),
		_T("Cyan"),
		_T("Blue"),
		_T("Magenta"),
		_T("White")};

	if (0 < iColIdx && iColIdx <= 7)
		return strColor[iColIdx - 1];
	else if (iColIdx == 256) {
		return CString(_T("ByLayer"));
	}
	else {
		CString strTmp;
		strTmp.Format(_T("%d"), iColIdx);
		return strTmp;			
	}			
	
	/*
	switch (iColIdx) {		
		case 1:
			return "Red";			
		case 2:
			return "Yellow";
		case 3:
			return "Green";
		case 4:
			return "Cyan";
		case 5:
			return "Blue";	
		case 6:
			return "Magenta";
		case 7:
			return "White";  // or Black
		default:
			strTmp.Format("%d", iColIdx);
			return strTmp;			
	}
	*/
}

CString ACConvertName::GetLineWeightStr(AcDb::LineWeight lw)
{	
	CString strTmp;
	
	//2006.07.20
	strTmp.Format(_T("%d"), lw);
	return strTmp;
}

// 図形タイプの一般名を得る。
CString ACConvertName::GetEntityTypeStr(AcDbEntity *pEnt)
{
	// AcDbCurveから派生した図形
	if (pEnt->isKindOf(AcDbCurve::desc()))	{
		// ラインの比較
		if      (pEnt->isA()->isEqualTo(AcDbLine::desc()) == Adesk::kTrue)
			return CString(_T("線分"));
		// 2dポリラインの比較
		else if (pEnt->isA()->isEqualTo(AcDb2dPolyline::desc()) == Adesk::kTrue)			
			return CString(_T("2D ﾎﾟﾘﾗｲﾝ"));
		// 3dポリラインの比較
		else if (pEnt->isA()->isEqualTo(AcDb3dPolyline::desc()) == Adesk::kTrue)
			return CString(_T("3D ﾎﾟﾘﾗｲﾝ"));
		// 円弧の比較
		else if (pEnt->isA()->isEqualTo(AcDbArc::desc()) == Adesk::kTrue)
			return CString(_T("円弧"));
		// 円の比較
		else if (pEnt->isA()->isEqualTo(AcDbCircle::desc()) == Adesk::kTrue)
			return CString(_T("円"));
		// 楕円の比較
		else if (pEnt->isA()->isEqualTo(AcDbEllipse::desc()) == Adesk::kTrue)
			return CString(_T("楕円"));
		// 引出し線の比較
		else if (pEnt->isA()->isEqualTo(AcDbLeader::desc()) == Adesk::kTrue)
			return CString(_T("引出線"));
		// ポリラインの比較
		else if (pEnt->isA()->isEqualTo(AcDbPolyline::desc()) == Adesk::kTrue)
			return CString(_T("ﾎﾟﾘﾗｲﾝ"));
		// Rayの比較
		else if (pEnt->isA()->isEqualTo(AcDbRay::desc()) == Adesk::kTrue)
			return CString(_T("放射線"));
		// Splineの比較
		else if (pEnt->isA()->isEqualTo(AcDbSpline::desc()) == Adesk::kTrue)
			return CString(_T("ｽﾌﾟﾗｲﾝ"));
		// Xlineの比較
		else if (pEnt->isA()->isEqualTo(AcDbXline::desc()) == Adesk::kTrue)
			return CString(_T("構築線"));
		// それ以外　カスタムオブジェクト
		//else
		//	return CString(true);
	}
	// 寸法線派生クラス	
	else if (pEnt->isKindOf(AcDbDimension::desc())) {
		//return CString(CompareDimensionGeoms(pEnt, pEnt2)); //####
		//return CString(false); //###
		// 2LineAngularDimension
		if (pEnt->isA()->isEqualTo(AcDb2LineAngularDimension::desc()) == Adesk::kTrue)
			return CString(_T("角度寸法"));
		// 3PointAngularDimension
		else if (pEnt->isA()->isEqualTo(AcDb3PointAngularDimension::desc()) == Adesk::kTrue)
			return CString(_T("3点角度寸法"));
		// AlignedDimension
		else if (pEnt->isA()->isEqualTo(AcDbAlignedDimension::desc()) == Adesk::kTrue)
			return CString(_T("平行寸法"));	
		// DiametricDimension
		else if (pEnt->isA()->isEqualTo(AcDbDiametricDimension::desc()) == Adesk::kTrue)
			return CString(_T("直径寸法"));
		// OrdinateDimension
		else if (pEnt->isA()->isEqualTo(AcDbOrdinateDimension::desc()) == Adesk::kTrue)
			return CString(_T("座標寸法"));
		// RadialDimension
		else if (pEnt->isA()->isEqualTo(AcDbRadialDimension::desc()) == Adesk::kTrue)
			return CString(_T("半径寸法"));
		// RotatedDimension
		else if (pEnt->isA()->isEqualTo(AcDbRotatedDimension::desc()) == Adesk::kTrue)		
			return CString(_T("長さ寸法"));
		// その他 寸法線派生クラス？
		//else
		//	return CString(true);
	}
	// ブロック参照	
	else if (pEnt->isKindOf(AcDbBlockReference::desc())) {
		// ブロック参照	
		if (pEnt->isA()->isEqualTo(AcDbBlockReference::desc()) == Adesk::kTrue)
			return CString(_T("ﾌﾞﾛｯｸ参照"));
		// MInsertBlock?
		else if (pEnt->isA()->isEqualTo(AcDbMInsertBlock::desc()) == Adesk::kTrue)
			return CString(pEnt->isA()->name()); //CompareMInsertBlockGeoms(pEnt, pEnt2);
		// その他ブロック参照派生クラス？
		//else
		//	return CString(true);
	}
	// Face // 3dはサポートしない。
	else if (pEnt->isA()->isEqualTo(AcDbFace::desc()) == Adesk::kTrue) {
		return CString(_T("3D 面"));
	}
	// FaceRecord  // 3dはサポートしない。
	else if (pEnt->isA()->isEqualTo(AcDbFaceRecord::desc()) == Adesk::kTrue) {
		return CString(pEnt->isA()->name());
	}
	// Fcf: 幾何公差
	else if (pEnt->isA()->isEqualTo(AcDbFcf::desc()) == Adesk::kTrue) {
		return CString(_T("幾何公差"));
	}
	// Frame派生クラス // // サポートしない。
	else if (pEnt->isKindOf(AcDbFrame::desc())) {
		// ??? Frameは抽象クラスか? → 抽象クラス
		//if (pEnt->isA()->isEqualTo(AcDbFrame::desc()) == Adesk::kTrue) 
		//	return CString(CompareFrameGeoms(pEnt, pEnt2));		
		
		// OleFrame
		if (pEnt->isA()->isEqualTo(AcDbOleFrame::desc()) == Adesk::kTrue) 
			return CString(pEnt->isA()->name());
		// Ole2Frame
		else if (pEnt->isA()->isEqualTo(AcDbOle2Frame::desc()) == Adesk::kTrue) 
			return CString(_T("OLE"));
		// その他 Frame派生クラス?
		//else
		//	return CString(false);
		
	}
	// ハッチング
	else if (pEnt->isA()->isEqualTo(AcDbHatch::desc()) == Adesk::kTrue) {
		return CString(_T("ﾊｯﾁﾝｸﾞ"));
	}
	// Image派生クラス
	else if (pEnt->isKindOf(AcDbImage::desc())) {
		// ??? Frameは抽象クラスか? → 抽象クラス
		//if (pEnt->isA()->isEqualTo(AcDbImage::desc()) == Adesk::kTrue) 
		//	return CString(CompareImageGeoms(pEnt, pEnt2));

		// RasterImage
		if (pEnt->isA()->isEqualTo(AcDbRasterImage::desc()) == Adesk::kTrue) 
			return CString(_T("ﾗｽﾀｰ ｲﾒｰｼﾞ"));
		// その他 Image派生クラス?
		//else
		//	return CString(false);
	}
	// Mline
	else if (pEnt->isA()->isEqualTo(AcDbMline::desc()) == Adesk::kTrue) {
		return CString(_T("ﾏﾙﾁﾗｲﾝ"));
	}	
	// MText
	else if (pEnt->isA()->isEqualTo(AcDbMText::desc()) == Adesk::kTrue) {
		return CString(_T("ﾏﾙﾁ ﾃｷｽﾄ"));
	}
	// Point
	else if (pEnt->isA()->isEqualTo(AcDbPoint::desc()) == Adesk::kTrue) {
		return CString(_T("点"));
	}
	// PolyFaceMesh // 3dはサポートしない。
	else if (pEnt->isA()->isEqualTo(AcDbPolyFaceMesh::desc()) == Adesk::kTrue) {		
		return CString(pEnt->isA()->name());
	}
	// PolygonMesh
	else if (pEnt->isA()->isEqualTo(AcDbPolygonMesh::desc()) == Adesk::kTrue) {
		return CString(_T("ﾎﾟﾘｺﾞﾝ ﾒｯｼｭ"));
	}
	// ProxyEntity
	else if (pEnt->isA()->isEqualTo(AcDbProxyEntity::desc()) == Adesk::kTrue) {
		return CString(pEnt->isA()->name());
	}
	// Shape
	else if (pEnt->isA()->isEqualTo(AcDbShape::desc()) == Adesk::kTrue) {
		return CString(_T("ｼｪｲﾌﾟ"));
	}
	// Solid
	else if (pEnt->isA()->isEqualTo(AcDbSolid::desc()) == Adesk::kTrue) {
		return CString(_T("ｿﾘｯﾄﾞ"));
	}
	// Text派生クラス
	else if (pEnt->isKindOf(AcDbText::desc())) {
		// テキスト
		if (pEnt->isA()->isEqualTo(AcDbText::desc()) == Adesk::kTrue) 
			return CString(_T("ﾃｷｽﾄ"));
		// 属性
		else if (pEnt->isA()->isEqualTo(AcDbAttribute::desc()) == Adesk::kTrue) 
			return CString(_T("属性"));
		// 属性定義
		else if (pEnt->isA()->isEqualTo(AcDbAttributeDefinition::desc()) == Adesk::kTrue) 
			return CString(_T("属性(定義)"));
		// その他 Text派生クラス?
		//else
		//	return CString(false);
	}
	// Trace
	else if (pEnt->isA()->isEqualTo(AcDbTrace::desc()) == Adesk::kTrue) {
		return CString(_T("太線"));
	}
	// Viewport
	else if (pEnt->isA()->isEqualTo(AcDbViewport::desc()) == Adesk::kTrue) {
		return CString(_T("ﾋﾞｭｰﾎﾟｰﾄ"));
	}
	// 3dSolid  // 3dはサポートしない
	else if (pEnt->isA()->isEqualTo(AcDb3dSolid::desc()) == Adesk::kTrue) {
		return CString(_T("3D ｿﾘｯﾄﾞ"));
	}
	// Body // 3dはサポートしない
	else if (pEnt->isA()->isEqualTo(AcDbBody::desc()) == Adesk::kTrue) {
		return CString(pEnt->isA()->name());
	}
	// Region
	else if (pEnt->isA()->isEqualTo(AcDbRegion::desc()) == Adesk::kTrue) {
		return CString(_T("ﾘｰｼﾞｮﾝ"));
	}
	// AcDbVertex 派生クラス
	else if (pEnt->isKindOf(AcDbVertex::desc())) {
		// AcDbVertex
		if (pEnt->isA()->isEqualTo(AcDbVertex::desc()) == Adesk::kTrue) 
			return CString(pEnt->isA()->name());
		// AcDb2dVertex
		else if (pEnt->isA()->isEqualTo(AcDb2dVertex::desc()) == Adesk::kTrue) 
			return CString(pEnt->isA()->name());
		// AcDb3dPolylineVertex
		else if (pEnt->isA()->isEqualTo(AcDb3dPolylineVertex::desc()) == Adesk::kTrue) 
			return CString(pEnt->isA()->name());
		// AcDbPolyFaceMeshVertex
		else if (pEnt->isA()->isEqualTo(AcDbPolyFaceMeshVertex::desc()) == Adesk::kTrue) 
			return CString(pEnt->isA()->name());
		// AcDbPolygonMeshVertex
		else if (pEnt->isA()->isEqualTo(AcDbPolygonMeshVertex::desc()) == Adesk::kTrue) 
			return CString(pEnt->isA()->name());
		//else 
		//	return CString(true);
	}
	// その他図形　カスタムオブジェクト
	//else {
	//	return CString(true);
	//}
	
	return CString(pEnt->isA()->name());

}
