// ACCompEntitiesGeom.cpp: ACCompEntitiesGeom クラスのインプリメンテーション
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "resource.h"
#include "ACCompEntitiesGeom.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//double ACCompEntitiesGeom::m_dTol = 0.0001;     // 図形比較時の許容誤差
//////////////////////////////////////////////////////////////////////
// 構築/消滅
//////////////////////////////////////////////////////////////////////

ACCompEntitiesGeom::ACCompEntitiesGeom()
{

}

ACCompEntitiesGeom::~ACCompEntitiesGeom()
{

}

// 指定されたエンティティのジオメトリの違いを調べる。
// 図形タイプ別のプロパティで比較する。
// 派生クラス等は比較をせずにtrueを返す。
bool ACCompEntitiesGeom::CompareEntityGeoms(AcDbEntity *pEnt1, AcDbEntity *pEnt2)
{	
	// 図形タイプが同じであるかどうか調べる。
	if (pEnt1->isA()->isEqualTo(pEnt2->isA()) != Adesk::kTrue)	
		return false;

	// AcDbCurveから派生した図形
	if (pEnt1->isKindOf(AcDbCurve::desc()))	{
		// ラインの比較
		if      (pEnt1->isA()->isEqualTo(AcDbLine::desc()) == Adesk::kTrue)
			return CompareLineGeoms(pEnt1, pEnt2);
		// 2dポリラインの比較
		else if (pEnt1->isA()->isEqualTo(AcDb2dPolyline::desc()) == Adesk::kTrue)			
			return Compare2dPolylineGeoms(pEnt1, pEnt2);
		// 3dポリラインの比較  ※3dはサポートしない。図面に存在した場合は、違いが検出されない。
		else if (pEnt1->isA()->isEqualTo(AcDb3dPolyline::desc()) == Adesk::kTrue)
			return Compare3dPolylineGeoms(pEnt1, pEnt2);
		// 円弧の比較
		else if (pEnt1->isA()->isEqualTo(AcDbArc::desc()) == Adesk::kTrue)
			return CompareArcGeoms(pEnt1, pEnt2);
		// 円の比較
		else if (pEnt1->isA()->isEqualTo(AcDbCircle::desc()) == Adesk::kTrue)
			return CompareCircleGeoms(pEnt1, pEnt2);
		// 楕円の比較
		else if (pEnt1->isA()->isEqualTo(AcDbEllipse::desc()) == Adesk::kTrue)
			return CompareEllipseGeoms(pEnt1, pEnt2);
		// 引出し線の比較
		else if (pEnt1->isA()->isEqualTo(AcDbLeader::desc()) == Adesk::kTrue)
			return CompareLeaderGeoms(pEnt1, pEnt2);
		// ポリラインの比較
		else if (pEnt1->isA()->isEqualTo(AcDbPolyline::desc()) == Adesk::kTrue)
			return ComparePolylineGeoms(pEnt1, pEnt2);
		// Rayの比較
		else if (pEnt1->isA()->isEqualTo(AcDbRay::desc()) == Adesk::kTrue)
			return CompareRayGeoms(pEnt1, pEnt2);
		// Splineの比較
		else if (pEnt1->isA()->isEqualTo(AcDbSpline::desc()) == Adesk::kTrue)
			return CompareSplineGeoms(pEnt1, pEnt2);
		// Xlineの比較
		else if (pEnt1->isA()->isEqualTo(AcDbXline::desc()) == Adesk::kTrue)
			return CompareXlineGeoms(pEnt1, pEnt2);		
		// それ以外　カスタムオブジェクト
		else
			return true;
	}
	// 寸法線派生クラス	
	else if (pEnt1->isKindOf(AcDbDimension::desc())) {		
		// 2LineAngularDimension
		if (pEnt1->isA()->isEqualTo(AcDb2LineAngularDimension::desc()) == Adesk::kTrue)
			return Compare2LineAngularDimensionGeoms(pEnt1, pEnt2);
		// 3PointAngularDimension
		else if (pEnt1->isA()->isEqualTo(AcDb3PointAngularDimension::desc()) == Adesk::kTrue)
			return Compare3PointAngularDimensionGeoms(pEnt1, pEnt2);
		// AlignedDimension
		else if (pEnt1->isA()->isEqualTo(AcDbAlignedDimension::desc()) == Adesk::kTrue)
			return CompareAlignedDimensionGeoms(pEnt1, pEnt2);	
		// DiametricDimension
		else if (pEnt1->isA()->isEqualTo(AcDbDiametricDimension::desc()) == Adesk::kTrue)
			return CompareDiametricDimensionGeoms(pEnt1, pEnt2);
		// OrdinateDimension
		else if (pEnt1->isA()->isEqualTo(AcDbOrdinateDimension::desc()) == Adesk::kTrue)
			return CompareOrdinateDimensionGeoms(pEnt1, pEnt2);
		// RadialDimension
		else if (pEnt1->isA()->isEqualTo(AcDbRadialDimension::desc()) == Adesk::kTrue)
			return CompareRadialDimensionGeoms(pEnt1, pEnt2);
		// RotatedDimension
		else if (pEnt1->isA()->isEqualTo(AcDbRotatedDimension::desc()) == Adesk::kTrue)		
			return CompareRotatedDimensionGeoms(pEnt1, pEnt2);
		// その他 寸法線派生クラス？
		else
			return true;
	}
	// ブロック参照	
	else if (pEnt1->isKindOf(AcDbBlockReference::desc())) {
		// ブロック参照	
		if (pEnt1->isA()->isEqualTo(AcDbBlockReference::desc()) == Adesk::kTrue)
			return CompareBlockReferenceGeoms(pEnt1, pEnt2);
		// MInsertBlock?
		else if (pEnt1->isA()->isEqualTo(AcDbMInsertBlock::desc()) == Adesk::kTrue)
			return CompareMInsertBlockGeoms(pEnt1, pEnt2);
		// その他ブロック参照派生クラス？
		else
			return true;
	}
	// Face // 3dはサポートしない。
	else if (pEnt1->isA()->isEqualTo(AcDbFace::desc()) == Adesk::kTrue) {
		return CompareFaceGeoms(pEnt1, pEnt2);		
	}
	// FaceRecord  // 3dはサポートしない。
	else if (pEnt1->isA()->isEqualTo(AcDbFaceRecord::desc()) == Adesk::kTrue) {
		return CompareFaceRecordGeoms(pEnt1, pEnt2);		
	}
	// Fcf: 幾何公差
	else if (pEnt1->isA()->isEqualTo(AcDbFcf::desc()) == Adesk::kTrue) {
		return CompareFcfGeoms(pEnt1, pEnt2);
	}
	// Frame派生クラス // // サポートしない。
	else if (pEnt1->isKindOf(AcDbFrame::desc())) {
		// ??? Frameは抽象クラスか? → 抽象クラス
		//if (pEnt1->isA()->isEqualTo(AcDbFrame::desc()) == Adesk::kTrue) 
		//	return CompareFrameGeoms(pEnt1, pEnt2);		
		
		// OleFrame
		if (pEnt1->isA()->isEqualTo(AcDbOleFrame::desc()) == Adesk::kTrue) 
			return CompareOleFrameGeoms(pEnt1, pEnt2);
		// Ole2Frame
		else if (pEnt1->isA()->isEqualTo(AcDbOle2Frame::desc()) == Adesk::kTrue) 
			return CompareOle2FrameGeoms(pEnt1, pEnt2);
		// その他 Frame派生クラス?
		else
			return false;
		
	}
	// ハッチング
	else if (pEnt1->isA()->isEqualTo(AcDbHatch::desc()) == Adesk::kTrue) {
		return CompareHatchGeoms(pEnt1, pEnt2);
	}
	// Image派生クラス
	else if (pEnt1->isKindOf(AcDbImage::desc())) {
		// ??? Frameは抽象クラスか? → 抽象クラス
		//if (pEnt1->isA()->isEqualTo(AcDbImage::desc()) == Adesk::kTrue) 
		//	return CompareImageGeoms(pEnt1, pEnt2);

		// RasterImage
		if (pEnt1->isA()->isEqualTo(AcDbRasterImage::desc()) == Adesk::kTrue) 
			return CompareRasterImageGeoms(pEnt1, pEnt2);
		// その他 Image派生クラス?
		else
			return false;
	}
	// Mline
	else if (pEnt1->isA()->isEqualTo(AcDbMline::desc()) == Adesk::kTrue) {
		return CompareMlineGeoms(pEnt1, pEnt2);
	}	
	// MText
	else if (pEnt1->isA()->isEqualTo(AcDbMText::desc()) == Adesk::kTrue) {
		return CompareMTextGeoms(pEnt1, pEnt2);
	}
	// Point
	else if (pEnt1->isA()->isEqualTo(AcDbPoint::desc()) == Adesk::kTrue) {
		return ComparePointGeoms(pEnt1, pEnt2);
	}
	// PolyFaceMesh // 3dはサポートしない。
	else if (pEnt1->isA()->isEqualTo(AcDbPolyFaceMesh::desc()) == Adesk::kTrue) {		
		return ComparePolyFaceMeshGeoms(pEnt1, pEnt2);
	}
	// PolygonMesh
	else if (pEnt1->isA()->isEqualTo(AcDbPolygonMesh::desc()) == Adesk::kTrue) {
		return ComparePolygonMeshGeoms(pEnt1, pEnt2);
	}
	// ProxyEntity
	else if (pEnt1->isA()->isEqualTo(AcDbProxyEntity::desc()) == Adesk::kTrue) {
		return CompareProxyEntityGeoms(pEnt1, pEnt2);
	}
	// Shape
	else if (pEnt1->isA()->isEqualTo(AcDbShape::desc()) == Adesk::kTrue) {
		return CompareShapeGeoms(pEnt1, pEnt2);
	}
	// Solid
	else if (pEnt1->isA()->isEqualTo(AcDbSolid::desc()) == Adesk::kTrue) {
		return CompareSolidGeoms(pEnt1, pEnt2);
	}
	// Text派生クラス
	else if (pEnt1->isKindOf(AcDbText::desc())) {
		// テキスト
		if (pEnt1->isA()->isEqualTo(AcDbText::desc()) == Adesk::kTrue) 
			return CompareTextGeoms(pEnt1, pEnt2);
		// 属性
		else if (pEnt1->isA()->isEqualTo(AcDbAttribute::desc()) == Adesk::kTrue) 
			return CompareAttributeGeoms(pEnt1, pEnt2);
		// 属性定義
		else if (pEnt1->isA()->isEqualTo(AcDbAttributeDefinition::desc()) == Adesk::kTrue) 
			return CompareAttributeDefinitionGeoms(pEnt1, pEnt2);
		// その他 Text派生クラス?
		else
			return false;
	}
	// Trace
	else if (pEnt1->isA()->isEqualTo(AcDbTrace::desc()) == Adesk::kTrue) {
		return CompareTraceGeoms(pEnt1, pEnt2);
	}
	// Viewport
	else if (pEnt1->isA()->isEqualTo(AcDbViewport::desc()) == Adesk::kTrue) {
		return CompareViewportGeoms(pEnt1, pEnt2);
	}
	// 3dSolid  // 3dはサポートしない
	else if (pEnt1->isA()->isEqualTo(AcDb3dSolid::desc()) == Adesk::kTrue) {
		return Compare3dSolidGeoms(pEnt1, pEnt2);
	}
	// Body // 3dはサポートしない
	else if (pEnt1->isA()->isEqualTo(AcDbBody::desc()) == Adesk::kTrue) {
		return CompareBodyGeoms(pEnt1, pEnt2);
	}
	// Region
	else if (pEnt1->isA()->isEqualTo(AcDbRegion::desc()) == Adesk::kTrue) {
		return CompareRegionGeoms(pEnt1, pEnt2);
	}
	// AcDbVertex 派生クラス
	else if (pEnt1->isKindOf(AcDbVertex::desc())) {
		// AcDbVertex
		if (pEnt1->isA()->isEqualTo(AcDbVertex::desc()) == Adesk::kTrue) 
			return CompareVertexGeoms(pEnt1, pEnt2);
		// AcDb2dVertex
		else if (pEnt1->isA()->isEqualTo(AcDb2dVertex::desc()) == Adesk::kTrue) 
			return Compare2dVertexGeoms(pEnt1, pEnt2);
		// AcDb3dPolylineVertex
		else if (pEnt1->isA()->isEqualTo(AcDb3dPolylineVertex::desc()) == Adesk::kTrue) 
			return Compare3dPolylineVertexGeoms(pEnt1, pEnt2);
		// AcDbPolyFaceMeshVertex
		else if (pEnt1->isA()->isEqualTo(AcDbPolyFaceMeshVertex::desc()) == Adesk::kTrue) 
			return ComparePolyFaceMeshVertexGeoms(pEnt1, pEnt2);
		// AcDbPolygonMeshVertex
		else if (pEnt1->isA()->isEqualTo(AcDbPolygonMeshVertex::desc()) == Adesk::kTrue) 
			return ComparePolygonMeshVertexGeoms(pEnt1, pEnt2);
		else 
			return true;
	}
	// その他図形　カスタムオブジェクト
	else {
		return true;
	}		
}



// 指定した2つの図形の一般属性が等しいかどうか調べる。
// pEnt1, pEnt2: 開かれているエンティティ
bool ACCompEntitiesGeom::IsEqualGeneralAttrs(AcDbEntity *pEnt1, AcDbEntity *pEnt2)
{
	//return true; //###

	CString strAttr1, strAttr2;
	int     iAttr1, iAttr2;
	double  dAttr1, dAttr2;

	// 図形タイプの比較
	if (pEnt1->isA()->isEqualTo(pEnt2->isA()) != Adesk::kTrue)		
		return false;

	//strAttr1 = pEnt1->isA()->name();
	//strAttr2 = pEnt2->isA()->name();	
	//if (strAttr1.CompareNoCase(strAttr2) != 0)
	//	return false;		
	
	// 色の比較
	iAttr1 = pEnt1->colorIndex();
	iAttr2 = pEnt2->colorIndex();
	if (iAttr1 != iAttr2)
		return false;	

	// レイヤーの比較	
	TCHAR *pcLayer1 = NULL, *pcLayer2 = NULL; //2006.07.20
	bool bEqualLayer;

	pcLayer1 = pEnt1->layer();
	pcLayer2 = pEnt2->layer();
	bEqualLayer = IsEqualStr(pcLayer1, pcLayer2);
	acutDelString(pcLayer1);
	acutDelString(pcLayer2);

	if (!bEqualLayer)
		return false;
	
	// *charの戻り値を持つ関数は、以下のように他の関数の引数に指定するだけでメモリリークが発生する。
	//if (!IsEqual(pEnt1->layer(), pEnt2->layer())) //###
	//	return false;

	// 線種の比較
	TCHAR *pcLinetype1 = NULL, *pcLinetype2 = NULL;//2006.07.20
	bool bEqualLinetype;

	pcLinetype1 = pEnt1->linetype();
	pcLinetype2 = pEnt2->linetype();
	bEqualLinetype = IsEqualStr(pcLinetype1, pcLinetype2);
	acutDelString(pcLinetype1);
	acutDelString(pcLinetype2);
	if (!bEqualLinetype)
		return false;	

	// 印刷スタイルの比較	
	TCHAR *pcPlot1 = NULL, *pcPlot2 = NULL;
	bool bEqualPlot;

	pcPlot1 = pEnt1->plotStyleName();
	pcPlot2 = pEnt2->plotStyleName();	
	bEqualPlot = IsEqualStr(pcPlot1, pcPlot2);
	acutDelString(pcPlot1);
	acutDelString(pcPlot2);
	if (!bEqualPlot)
		return false;

	// 線の太さの比較
	iAttr1 = pEnt1->lineWeight();
	iAttr2 = pEnt2->lineWeight();
	if (iAttr1 != iAttr2)	
		return false;

	// 線種尺度の比較
	dAttr1 = pEnt1->linetypeScale();
	dAttr2 = pEnt2->linetypeScale();	
	//if (dAttr1 != dAttr2)
	if (!IsEqual(dAttr1, dAttr2))
		return false;
	
	// ハイパーリンクの比較	
	//// ハイパーリンクが同じであるときと、両方とも拡張データがないときにtrueを返す。	
	if (!CompareHyperLink(pEnt1, pEnt2))
		return false;	

	return true;
}

// 2dポリラインの比較	
bool ACCompEntitiesGeom::Compare2dPolylineGeoms(AcDbEntity *pEnt1, AcDbEntity *pEnt2)
{
	AcDb2dPolyline *p2dPLine1 = AcDb2dPolyline::cast(pEnt1);
	AcDb2dPolyline *p2dPLine2 = AcDb2dPolyline::cast(pEnt2);
	AcDbObjectIterator *pItr1, *pItr2;	
	Acad::ErrorStatus es1, es2;
	bool bEqualQuery = false;	
	bool bEqualVerts = false;
	
	// 2dポリラインにキャストできない場合は終了
	if (p2dPLine1 == NULL || p2dPLine2 == NULL)
		return false;
	
	// 厚さ、頂点(XY、開始セグメント幅、終了セグメント幅)、高度、面積、
	// フィット/スムーズ、グローバル幅、閉じている、線種生成モード		

	
	// 「グローバル幅」は全てのセグメントの幅を同じにするために使用する。(?)
	// グローバル幅を設定しても、頂点の、開始・終了セグメント幅を違う値に設定すれば
	// グローバル幅は空欄になる。

	// 属性を比較する。 
	bEqualQuery = (		 
		 IsEqual(p2dPLine1->elevation(),		        p2dPLine2->elevation())		 &&	// 高度	 		
		 IsEqual(p2dPLine1->thickness(),		        p2dPLine2->thickness())		 &&    // 厚さ	
			    (p2dPLine1->isLinetypeGenerationOn() == p2dPLine2->isLinetypeGenerationOn()) &&  // 線種生成モード
			    (p2dPLine1->polyType()				 == p2dPLine2->polyType()) &&  // フィット/スムーズ
				(p2dPLine1->isClosed()               == p2dPLine2->isClosed()));   // 閉じている

	if (!bEqualQuery)
		return false;	

	//double dS = p2dPLine1->defaultStartWidth();
	//double dE = p2dPLine1->defaultEndWidth();

	// 面積の比較
	double dArea1, dArea2;
	bool   bEqualArea;

	es1 = p2dPLine1->getArea(dArea1);
	es2 = p2dPLine2->getArea(dArea2);

	if (es1 == Acad::eOk && es2 == Acad::eOk) 
		bEqualArea = IsEqual(dArea1, dArea2);			
	else
		bEqualArea = false;

	if (!bEqualArea)
		return false;

	// 頂点を比べる。頂点(XY、開始セグメント幅、終了セグメント幅)
	// 閉じている、かどうかも分かる
	pItr1 = p2dPLine1->vertexIterator();
	pItr2 = p2dPLine2->vertexIterator();
	
	pItr1->start(); 
	pItr2->start(); 

	while (1) {			
		AcDbObjectId idVert1, idVert2;
		AcDb2dVertex *p2dVert1, *p2dVert2;
		bool bEnd1 = false, bEnd2 = false, bRes = false; 
		
		// done() = falseが継続条件?
		bEnd1 = pItr1->done();
		bEnd2 = pItr2->done();

		if (bEnd1 != bEnd2)
			break;
		else if (bEnd1) {
			bEqualVerts = true;	
			break;
		}		
		
		idVert1 = pItr1->objectId();
		idVert2 = pItr2->objectId();
		
		// 頂点オブジェクトが開けない場合は終了
		es1 = p2dPLine1->openVertex(p2dVert1, idVert1, AcDb::kForRead);					
		es2 = p2dPLine2->openVertex(p2dVert2, idVert2, AcDb::kForRead);			
		
		// 頂点を比較する。違った場合は終了
		if (es1 == Acad::eOk && es2 == Acad::eOk) 
			bRes = Compare2dVertexGeoms(p2dVert1, p2dVert2);
		else
			bRes = false;

		if (es1 == Acad::eOk)					
			p2dVert1->close();

		if (es2 == Acad::eOk)
			p2dVert2->close();

		// 開けない、または結果が違っていた場合は終了
		if (!bRes)
			break;

		pItr1->step();
		pItr2->step();
	}
	delete pItr1;
	delete pItr2;
	
	return bEqualVerts;
	
}	

// 3dポリラインの比較		
bool ACCompEntitiesGeom::Compare3dPolylineGeoms(AcDbEntity *pEnt1, AcDbEntity *pEnt2)
{
	return true;

	/*
	AcDb3dPolyline *p3dPLine1 = AcDb3dPolyline::cast(pEnt1);
	AcDb3dPolyline *p3dPLine2 = AcDb3dPolyline::cast(pEnt2);
	AcDbObjectIterator *pItr1, *pItr2;	
	Acad::ErrorStatus es1, es2;
	bool bEqualQuery = false;	
	bool bEqualVerts = false;
	

	if (p3dPLine1 == NULL || p3dPLine2 == NULL)
		return false;		

	// 属性を比較する。
	bEqualQuery = (
		(p3dPLine1->polyType() == p3dPLine2->polyType()) &&  // フィット/スムーズ
		(p3dPLine1->isClosed() == p3dPLine2->isClosed()));   // 閉じている
	if (!bEqualQuery)
		return false;
		
	// 頂点を比べる。
	pItr1 = p3dPLine1->vertexIterator();
	pItr2 = p3dPLine2->vertexIterator();
	
	pItr1->start(); 
	pItr2->start(); 

	while (1) {
		AcDbObjectId idVert1, idVert2;
		AcDb3dPolylineVertex *p3dVert1, *p3dVert2;
		bool bEnd1 = false, bEnd2 = false, bRes = false; 
		
		// done() = falseが継続条件?
		bEnd1 = pItr1->done();
		bEnd2 = pItr2->done();
				
		if (bEnd1 != bEnd2)
			break;
		else if (bEnd1) {
			bEqualVerts = true;	
			break;
		}

		idVert1 = pItr1->objectId();
		idVert2 = pItr2->objectId();
		
		// 頂点オブジェクトを開く
		es1 = p3dPLine1->openVertex(p3dVert1, idVert1, AcDb::kForRead);					
		es2 = p3dPLine2->openVertex(p3dVert2, idVert2, AcDb::kForRead);			
		
		// 頂点を比較する。違った場合は終了
		if (es1 == Acad::eOk && es2 == Acad::eOk)
			bRes = Compare3dPolylineVertexGeoms(p3dVert1, p3dVert2);			
		else
			bRes = false;

		if (es1 == Acad::eOk)
			p3dVert1->close();		

		if (es2 == Acad::eOk)
			p3dVert2->close();		
		
		// 開けない、または結果が違っていた場合は終了
		if (!bRes)
			break;

		pItr1->step();
		pItr2->step();
	}
	delete pItr1;
	delete pItr2;
	
	return bEqualVerts;
	*/
	
}	

// 円弧の比較	
bool ACCompEntitiesGeom::CompareArcGeoms(AcDbEntity *pEnt1, AcDbEntity *pEnt2)
{
	AcDbArc *pArc1 = AcDbArc::cast(pEnt1);
	AcDbArc *pArc2 = AcDbArc::cast(pEnt2);
	
	if (pArc1 == NULL || pArc2 == NULL)
		return false;
	
	// 厚さ、始点XYZ、中心XYZ、終点XYZ、半径、開始角度、終了角度、
	// 全角度、円弧の長さ、面積、法線XYZ
	
	// 全角度(disable)?、円弧の長さ(disable)?
	bool bEqualQuery = (
		IsEqual(pArc1->center(),	 pArc2->center()) &&   // 中心
		IsEqual(pArc1->endAngle(),   pArc2->endAngle()) &&  // 終了角度  
		IsEqual(pArc1->normal(),	 pArc2->normal()) &&  // 法線XYZ
		IsEqual(pArc1->radius(),	 pArc2->radius()) &&  // 半径
		IsEqual(pArc1->startAngle(), pArc2->startAngle()) &&  // 開始角度
		IsEqual(pArc1->thickness(),  pArc2->thickness()));  // 厚さ

	if (!bEqualQuery)
		return false;

	// 面積
	Acad::ErrorStatus es1, es2;
	double dArea1, dArea2;	
	bool   bEqualArea = true;

	es1 = pArc1->getArea(dArea1);
	es2 = pArc2->getArea(dArea2);

	if (es1 == Acad::eOk && es2 == Acad::eOk) 
		bEqualArea = IsEqual(dArea1, dArea2);
	else // if (es1 != es2)
        bEqualArea = false;

	if (!bEqualArea)
		return false;

	// 始点XYZ(disable)
	AcGePoint3d pt3Start1, pt3Start2;
	bool bEqualSPt = true;

	es1 = pArc1->getStartPoint(pt3Start1);
	es2 = pArc2->getStartPoint(pt3Start2);

	if (es1 == Acad::eOk && es2 == Acad::eOk) 
		bEqualSPt = IsEqual(pt3Start1, pt3Start2);
	else // if (es1 != es2)
        bEqualSPt = false;

	if (!bEqualSPt)
		return false;

		
	// 終点XYZ(disable)
	AcGePoint3d pt3End1, pt3End2;
	bool bEqualEPt = true;

	es1 = pArc1->getEndPoint(pt3End1);
	es2 = pArc2->getEndPoint(pt3End2);

	if (es1 == Acad::eOk && es2 == Acad::eOk) 
		bEqualEPt = IsEqual(pt3End1, pt3End2);
	else // if (es1 != es2)
        bEqualEPt = false;

	return bEqualEPt;			
}	

// 円の比較		
bool ACCompEntitiesGeom::CompareCircleGeoms(AcDbEntity *pEnt1, AcDbEntity *pEnt2)
{
	AcDbCircle *pCircle1 = AcDbCircle::cast(pEnt1);
	AcDbCircle *pCircle2 = AcDbCircle::cast(pEnt2);
	
	if (pCircle1 == NULL || pCircle2 == NULL)
		return false;
	
	// 属性の比較
	bool bEqualQuery = (
		IsEqual(pCircle1->center(),    pCircle2->center()) &&   // 中心XYZ 
		IsEqual(pCircle1->normal(),	   pCircle2->normal()) &&   // 法線XYZ
		IsEqual(pCircle1->radius(),    pCircle2->radius()) &&   // 半径、(直径)
		IsEqual(pCircle1->thickness(), pCircle2->thickness()));  // 厚さ

	return bEqualQuery;		

	// 円周、面積→半径から求められる
	//getArea
}	

// 楕円の比較	
bool ACCompEntitiesGeom::CompareEllipseGeoms(AcDbEntity *pEnt1, AcDbEntity *pEnt2)
{
	AcDbEllipse *pEllipse1 = AcDbEllipse::cast(pEnt1);
	AcDbEllipse *pEllipse2 = AcDbEllipse::cast(pEnt2);
	
	if (pEllipse1 == NULL || pEllipse2 == NULL)
		return false;	
	
	// 始点XYZ、中心XYZ、終点XYZ、長径、短径
	// 半径比、開始角度、終了角度、主軸ベクトルXYZ、補助軸ベクトルXYZ、面積

	// 始点XYZ(disable)、終点XYZ(disable)	
	// 面積(disable)

	// 属性の比較
	bool bEqualQuery = (	
		IsEqual(pEllipse1->center(),       pEllipse2->center()) &&      // 中心XYZ
		IsEqual(pEllipse1->endAngle(),     pEllipse2->endAngle()) &&    // 終了角度				
		IsEqual(pEllipse1->majorAxis(),    pEllipse2->majorAxis()) &&   // 主軸ベクトルXYZ
		IsEqual(pEllipse1->minorAxis(),    pEllipse2->minorAxis()) &&   // 補助軸ベクトルXYZ		
		IsEqual(pEllipse1->radiusRatio(),  pEllipse2->radiusRatio()) && // 半径比
		IsEqual(pEllipse1->startAngle(),   pEllipse2->startAngle()));   // 開始角度

	if (!bEqualQuery)
		return false;

	// 長径、短径(主軸ベクトルと半径比から求められる)の比較
	double dMajLen1, dMajLen2, dMinoLen1, dMinoLen2;
	
	dMajLen1 = 
		sqrt(pEllipse1->majorAxis()[0] * pEllipse1->majorAxis()[0] +
		     pEllipse1->majorAxis()[1] * pEllipse1->majorAxis()[1] +
		     pEllipse1->majorAxis()[2] * pEllipse1->majorAxis()[2]);

	dMajLen2 = 
		sqrt(pEllipse2->majorAxis()[0] * pEllipse2->majorAxis()[0] +
		     pEllipse2->majorAxis()[1] * pEllipse2->majorAxis()[1] +
		     pEllipse2->majorAxis()[2] * pEllipse2->majorAxis()[2]);
	
	dMinoLen1 = dMajLen1 * pEllipse1->radiusRatio();
	dMinoLen2 = dMajLen2 * pEllipse2->radiusRatio();

	return (
		IsEqual(dMajLen1,  dMajLen2) &&
		IsEqual(dMinoLen1, dMinoLen2));
}	

// 引出し線の比較	
bool ACCompEntitiesGeom::CompareLeaderGeoms(AcDbEntity *pEnt1, AcDbEntity *pEnt2)
{
	AcDbLeader *pLeader1 = AcDbLeader::cast(pEnt1);
	AcDbLeader *pLeader2 = AcDbLeader::cast(pEnt2);	

	if (pLeader1 == NULL || pLeader2 == NULL)
		return false;
	
	//dimtxsty  // 引き出し線に文字部分は含まれないので必要ない？
	//dimtxt    // 引き出し線に文字部分は含まれないので必要ない？
	
	// 自動調整、ハイパーリンク
	// 頂点XYZ x n、寸法スタイル、タイプ、全体の寸法尺度
	// 矢印、矢印サイズ、寸法線の太さ、寸法線の色、文字オフセット、垂直方向の寸法値位置

	// 自動調整(disable)、ハイパーリンクは？

	// 属性の比較
	bool bEqualQuery = (	
		IsEqual(pLeader1->dimasz(),		  pLeader2->dimasz())       && // 矢印サイズ
		IsEqual(pLeader1->dimclrd(),	  pLeader2->dimclrd())      && // 寸法線の色
		IsEqual(pLeader1->dimgap(),		  pLeader2->dimgap())       && // 文字オフセット
		IsEqual(pLeader1->dimlwd(),		  pLeader2->dimlwd())       && // 寸法線の太さ
		IsEqual(pLeader1->dimscale(),	  pLeader2->dimscale())     && // 全体の寸法尺度
		IsEqual(pLeader1->dimtad(),		  pLeader2->dimtad())       && // 垂直方向の寸法値位置	
		IsEqual(pLeader1->hasArrowHead(), pLeader2->hasArrowHead()) && // タイプ(1)  要テスト
		IsEqual(pLeader1->hasHookLine(),  pLeader2->hasHookLine())  && // タイプ(?)
		IsEqual(pLeader1->isSplined(),    pLeader2->isSplined()));     // タイプ(2)  要テスト

	if (!bEqualQuery)
		return false;
	
	// 矢印の比較
	bool bRetOpenOk;
	if (!CompareBlockTableRecord(pLeader1->dimldrblk(), pLeader2->dimldrblk(), bRetOpenOk))
		return false;
		  		 
	// 寸法スタイルの比較
	if (!CompareDimStyle(pLeader1->dimensionStyle(), pLeader2->dimensionStyle()))
		return false;		

	// 頂点の比較
	if (pLeader1->numVertices() != pLeader2->numVertices()) 
		return false;

	for (int i = 0; i < pLeader1->numVertices(); i++) {
		if (!IsEqual(pLeader1->vertexAt(i), pLeader2->vertexAt(i)))  
			return false;			
	}			
	
	return true;		
}	

// 指定された2本のラインが図形的に等しいかどうか調べる。
bool ACCompEntitiesGeom::CompareLineGeoms(AcDbEntity *pEnt1, AcDbEntity *pEnt2)
{
	AcDbLine *pLine1 = AcDbLine::cast(pEnt1);
	AcDbLine *pLine2 = AcDbLine::cast(pEnt2);
	
	if (pLine1 == NULL || pLine2 == NULL)
		return false;


	// 厚さ、始点XYZ、終点XYZ、デルタXYZ、長さ、角度

	// 、デルタXYZ(disable)、長さ(disable)、角度(disable)

	// 属性の比較結果を返す。
	return (IsEqual(pLine1->startPoint(), pLine2->startPoint()) &&  // 始点XYZ
			IsEqual(pLine1->endPoint(),   pLine2->endPoint())   &&  // 終点XYZ		    
			IsEqual(pLine1->thickness(),  pLine2->thickness()));    // 厚さ
}

// ポリラインの比較	
bool ACCompEntitiesGeom::ComparePolylineGeoms(AcDbEntity *pEnt1, AcDbEntity *pEnt2)
{
	AcDbPolyline *pPLine1 = AcDbPolyline::cast(pEnt1);
	AcDbPolyline *pPLine2 = AcDbPolyline::cast(pEnt2);
	bool bEqualQuery;
	
	if (pPLine1 == NULL || pPLine2 == NULL)
		return false;
	
	// 厚さ、頂点(XYZ、開始・終了セグメント幅)、グローバル幅、高度、面積(disable)
	// 閉じている、線種生成モード

	// グローバル幅→設定のみ？	
	// 面積(disable)

	// 属性の比較
	bEqualQuery = (
		IsEqual(pPLine1->elevation(),   pPLine2->elevation()) &&  // 高度
		IsEqual(pPLine1->isClosed(),    pPLine2->isClosed())  &&  // 閉じている						
		IsEqual(pPLine1->thickness(),   pPLine2->thickness()) &&  // 厚さ  	
		IsEqual(pPLine1->hasPlinegen(), pPLine2->hasPlinegen())); // 線種生成モード
	
	// 属性が等しくない場合は、頂点の比較をせずに終了
	if (!bEqualQuery)
		return false;	
	
	// 各頂点の比較  // 頂点(XYZ、開始・終了セグメント幅)
	if (pPLine1->numVerts() != pPLine2->numVerts()) 
		return false;

	for (int i = 0; i < (int)(pPLine1->numVerts()); i++) {
		AcGePoint3d pt3_1, pt3_2;
		Acad::ErrorStatus es1, es2;
		//double dBulge1, dBulge2; 
		double dStartWidth1, dStartWidth2, dEndWidth1, dEndWidth2;
		bool bEqualPt, bEqualWidth;

		//if ((es = pPLine1->getBulgeAt(i, dBulge1)) != pPLine2->getBulgeAt(i, dBulge2))
		//	break;

		//if (es == Acad::eOk) {
		//	if (!IsEqual(dBulge1, dBulge2))
		//		break;
		//}
			
		es1 = pPLine1->getPointAt(i, pt3_1);
		es2 = pPLine2->getPointAt(i, pt3_2);

		if (es1 == Acad::eOk && es2 == Acad::eOk) 
			bEqualPt = IsEqual(pt3_1, pt3_2);				
		else 
			bEqualPt = false;

		if (!bEqualPt)
			return false;
		
		es1 = pPLine1->getWidthsAt(i, dStartWidth1, dEndWidth1);
		es2 = pPLine2->getWidthsAt(i, dStartWidth2, dEndWidth2);

		if (es1 == Acad::eOk && es1 == Acad::eOk) 
			bEqualWidth = (
				IsEqual(dStartWidth1, dStartWidth2) && 
				IsEqual(dEndWidth1,   dEndWidth2));
		else
			bEqualWidth = false;

		if (!bEqualWidth)
			return false;

		//if (pPLine1->segType(i) != pPLine2->segType(i))
		//	break;
	}		

	//if (i == pPLine1->numVerts())
	//	bEqualVert = true;

	return true;
}	

// Rayの比較		
bool ACCompEntitiesGeom::CompareRayGeoms(AcDbEntity *pEnt1, AcDbEntity *pEnt2)
{
	AcDbRay *pRay1 = AcDbRay::cast(pEnt1);
	AcDbRay *pRay2 = AcDbRay::cast(pEnt2);
	
	if (pRay1 == NULL || pRay2 == NULL)
		return false;
	
	// 基点XYZ、2点目XYZ、方向ベクトルXYZ

	// 2点目XYZ = 基点XYZ + 方向ベクトルXYZ
	return (
		IsEqual(pRay1->basePoint(), pRay2->basePoint()) && // 基点XYZ
		IsEqual(pRay1->unitDir(),   pRay2->unitDir()));    // 方向ベクトルXYZ(disable)
}
	

// Splineの比較	
bool ACCompEntitiesGeom::CompareSplineGeoms(AcDbEntity *pEnt1, AcDbEntity *pEnt2)
{
	AcDbSpline *pSpline1 = AcDbSpline::cast(pEnt1);
	AcDbSpline *pSpline2 = AcDbSpline::cast(pEnt2);
	Acad::ErrorStatus es1, es2;
	bool bEqualQuery = false, bEqualFitPts = false, bEqualNurbs = false;
	int i;

	if (pSpline1 == NULL || pSpline2 == NULL)
		return false;

	// 制御点数(disable)、制御点(XYZ、重み)、フィット点の数、フィット点(XYZ)
	// 度(disable)、閉じている(disable)、平面状(disable)、
	// 開始接線ベクトルXYZ(disable)、終了接線ベクトルXYZ(disable)
	// フィット許容差、面積(disable)

	// 属性の比較
	bEqualQuery = (	
		IsEqual(pSpline1->fitTolerance(), pSpline2->fitTolerance()) &&   // フィット許容差  				 			   
			   (pSpline1->degree() == pSpline2->degree()));  // 度(disable)			   
	
	if (!bEqualQuery)
		return false;



	// 、閉じている(disable)、平面状(disable)、
	// 開始接線ベクトルXYZ(disable)、終了接線ベクトルXYZ(disable)
	// 、面積(disable)

	
	// フィット点の比較
	if (pSpline1->numFitPoints() != pSpline2->numFitPoints()) // フィット点の数   
		return false;

	for (i = 0; i < pSpline1->numFitPoints(); i++) {
		AcGePoint3d pt3Fit1, pt3Fit2; 

		es1 = pSpline1->getFitPointAt(i, pt3Fit1);
		es2 = pSpline2->getFitPointAt(i, pt3Fit2);

		if (es1 == Acad::eOk && es2 == Acad::eOk) 
			if (!IsEqual(pt3Fit1, pt3Fit2))
				return false;
	}
		
	// 制御点数と制御点の比較(XYZ、重み) 重みはrationalスプラインのときのみ比較する。
	Adesk::Boolean abRational;

	if ((abRational = pSpline1->isRational()) != 
		             pSpline2->isRational())
		return false;

	if (pSpline1->numControlPoints() != pSpline2->numControlPoints())	
		return false;

	for (i = 0; i < pSpline1->numControlPoints(); i++) {
		AcGePoint3d pt3Ctrl1, pt3Ctrl2;		

		es1 = pSpline1->getControlPointAt(i, pt3Ctrl1);
		es2 = pSpline2->getControlPointAt(i, pt3Ctrl2);

		if (es1 == Acad::eOk && es2 == Acad::eOk) {
			if (!IsEqual(pt3Ctrl1, pt3Ctrl2))
				return false;
		}
		else
			return false;

		if (abRational == Adesk::kTrue) {
			double dWeight1, dWeight2;

			dWeight1 = pSpline1->weightAt(i);
			dWeight2 = pSpline2->weightAt(i);

			if (!IsEqual(dWeight1, dWeight2))
				return false;
		}		
	}

	return true;
}	

// Xlineの比較		
bool ACCompEntitiesGeom::CompareXlineGeoms(AcDbEntity *pEnt1, AcDbEntity *pEnt2)
{
	AcDbXline *pXline1 = AcDbXline::cast(pEnt1);
	AcDbXline *pXline2 = AcDbXline::cast(pEnt2);
	
	if (pXline1 == NULL || pXline2 == NULL)
		return false;
	
	// 2点目XYZ (= 基点XYZ + 方向ベクトルXYZ)

	return (
		IsEqual(pXline1->basePoint(), pXline2->basePoint()) && // 基点XYZ
		IsEqual(pXline1->unitDir(),   pXline2->unitDir()));    // 方向ベクトルXYZ
}	

// 2d頂点を比較する。
bool ACCompEntitiesGeom::Compare2dVertexGeoms(AcDb2dVertex *p2dVtx1, AcDb2dVertex *p2dVtx2)
{
	return (
		IsEqual(p2dVtx1->bulge(),	   	  p2dVtx2->bulge())			&&   
		IsEqual(p2dVtx1->endWidth(),	  p2dVtx2->endWidth())		&&
		//IsEqual(p2dVtx1->isTangentUsed(), p2dVtx2->isTangentUsed()) &&  
		IsEqual(p2dVtx1->position(),	  p2dVtx2->position())		&&
		IsEqual(p2dVtx1->startWidth(),	  p2dVtx2->startWidth())); //	&&
		//IsEqual(p2dVtx1->tangent(),		  p2dVtx2->tangent())		&&
		//IsEqual(p2dVtx1->vertexType(),	  p2dVtx2->vertexType()));

}

// 3d頂点を比較する。
bool ACCompEntitiesGeom::Compare3dPolylineVertexGeoms(AcDb3dPolylineVertex *p3dVtx1, AcDb3dPolylineVertex *p3dVtx2)
{
	return (
		IsEqual(p3dVtx1->position(), p3dVtx2->position()) && 
			   (p3dVtx1->vertexType() == p3dVtx2->vertexType()));
}


//---- 寸法線派生クラスの比較 ----//
// Dimension 基底クラスの属性の比較を行う。
bool ACCompEntitiesGeom::CompareDimensionGeoms(AcDbEntity *pEnt1, AcDbEntity *pEnt2)
{
	AcDbDimension *pDim1 = AcDbDimension::cast(pEnt1); 
	AcDbDimension *pDim2 = AcDbDimension::cast(pEnt2); 
//	Acad::ErrorStatus es1, es2;	

	if (pDim1 == NULL || pDim2 == NULL)
		return false;

	//isPlanar  (in getPlane)	  	
	bool bResQuery = (			   
			   (pDim1->textAttachment() ==			   pDim2->textAttachment()) &&
		IsEqual(pDim1->textLineSpacingFactor(),		   pDim2->textLineSpacingFactor()) &&  
			   (pDim1->textLineSpacingStyle() ==	   pDim2->textLineSpacingStyle()) && 
		IsEqualNoGap(pDim1->dimBlockPosition(),			   pDim2->dimBlockPosition()) &&	
		//IsEqual(pDim1->elevation(),					   pDim2->elevation()) &&  	
		IsEqual(pDim1->horizontalRotation(),		   pDim2->horizontalRotation()) &&  	
		//	   (pDim1->isUsingDefaultTextPosition() == pDim2->isUsingDefaultTextPosition()) &&
		//IsEqual(pDim1->normal(),					   pDim2->normal()) &&
		IsEqual(pDim1->textPosition(),			   pDim2->textPosition()) &&  // 寸法値位置XY
		IsEqual(pDim1->textRotation(),				   pDim2->textRotation()));   // 寸法値角度
			
	if (!bResQuery)
		return false;
	
	// 自動調整寸法であるかどうかの比較		
	if (IsAssociatedDimension(pDim1) != IsAssociatedDimension(pDim2))
		return false;


/* 実測値のみを外部から変更する手段はないので比較対照から削除
// 2006/03/08 hashimoto
	// 計測値の比較
	double dMeasure1, dMeasure2;
	bool   bEqualMeasure = true;

	es1 = pDim1->measurement(dMeasure1);	//計測値	
	es2 = pDim2->measurement(dMeasure2);	
	
	if (es1 == Acad::eOk && es2 == Acad::eOk) 			
		bEqualMeasure = IsEqual(dMeasure1, dMeasure2);		
	else if (es1 != es2) {
		bEqualMeasure = false;
	}

	if (!bEqualMeasure)
		return false;
*/

	// dimensionTextの比較 // 寸法値上書き	
	TCHAR *pcDimText1 = NULL, *pcDimText2 = NULL;//2006.07.20	
	bool bEqualText = true;
	
	pcDimText1 = pDim1->dimensionText();
	pcDimText2 = pDim2->dimensionText();		

	//// 内容が異なるときはfalse, どちらか一方がNULLの場合もfalse
	//// 両方NULLのときはtrue
	bEqualText = IsEqualStr(pcDimText1, pcDimText2);
	
	acutDelString(pcDimText1);
	acutDelString(pcDimText2);
		
	if (!bEqualText)
		return false;


	// 文字スタイルの比較 (DIMTXSTY)
	if (!CompareTextStyle(pDim1->dimtxsty(), pDim2->dimtxsty()))
		return false;

	// 寸法スタイルの比較 ()
	if (!CompareDimStyle(pDim1->dimensionStyle(), pDim2->dimensionStyle()))
		return false;

	// // 矢印1の比較 名前のみ比較する。dimblk1()    
	bool bRetOpenOk;
	if (!CompareBlockTableRecord(pDim1->dimblk1(), pDim2->dimblk1(), bRetOpenOk))
		return false;

	// // 矢印2の比較 名前のみ比較する。dimblk2()    	
	if (!CompareBlockTableRecord(pDim1->dimblk2(), pDim2->dimblk2(), bRetOpenOk))
		return false;
	
	// // 矢印?の比較 名前のみ比較する。dimblk()    	
	if (!CompareBlockTableRecord(pDim1->dimblk(), pDim2->dimblk(), bRetOpenOk))
		return false;
	
	// // 矢印?の比較 名前のみ比較する。dimldrblk()    	
	if (!CompareBlockTableRecord(pDim1->dimldrblk(), pDim2->dimldrblk(), bRetOpenOk))
		return false;	
	
	// 寸法システム変数の比較
	//(pDim1->dimfit() ==   pDim2->dimfit()) &&   //// XXXX 廃止された
	//(pDim1->dimunit() ==  pDim2->dimunit()) &&  //// XXXX 廃止された

	bool bSysVar = ( 
			   (pDim1->dimadec()  == pDim2->dimadec())   &&
			   (pDim1->dimalt()   == pDim2->dimalt())    &&    // 変換単位を使用
			   (pDim1->dimaltd()  == pDim2->dimaltd())   &&   // 変換単位の許容差の精度		
		IsEqual(pDim1->dimaltf(),	 pDim2->dimaltf())   &&   // 変換単位の尺度
		IsEqual(pDim1->dimaltrnd(),  pDim2->dimaltrnd()) &&  // 変換単位の丸め 
			   (pDim1->dimalttd() == pDim2->dimalttd())  &&   // 変換単位の精度	
			   (pDim1->dimalttz() == pDim2->dimalttz())  &&   // 変換単位の許容差の接頭の0を省略, 変換単位の許容差の末尾の0を省略, 変換単位の許容差の0フィートを省略, 変換単位の許容差の0インチを省略
			   (pDim1->dimaltu()  == pDim2->dimaltu())   &&   // 変換単位の形式
			   (pDim1->dimaltz()  == pDim2->dimaltz())  &&   // 変換単位の接頭の0を省略, 変換単位の末尾の0を省略, 変換単位の0フィートを省略, 変換単位の0インチを省略 		
	 IsEqualStr(pDim1->dimapost(),   pDim2->dimapost()) &&  // 変換単位の接頭表記, 変換単位の末尾表記		
		IsEqual(pDim1->dimasz(),	 pDim2->dimasz())   &&     // 矢印サイズ	
			   (pDim1->dimatfit() == pDim2->dimatfit()) &&   // フィット		
			   (pDim1->dimaunit() == pDim2->dimaunit()) &&
			   (pDim1->dimazin()  == pDim2->dimazin()) &&	 
		IsEqual(pDim1->dimcen(),	 pDim2->dimcen())  &&  			
			   (pDim1->dimclrd()  == pDim2->dimclrd()) && // 寸法線の色
			   (pDim1->dimclre()  == pDim2->dimclre()) && // 寸法補助線の色
			   (pDim1->dimclrt()  == pDim2->dimclrt()) && // 文字の色
			   (pDim1->dimdec()   == pDim2->dimdec()) &&   // 精度 (int)
	    IsEqual(pDim1->dimdle(),	 pDim2->dimdle()) &&   // 寸法線延長長さ
		IsEqual(pDim1->dimdli(),	 pDim2->dimdli()) &&   	
  			   (pDim1->dimdsep()  == pDim2->dimdsep())   &&  // 十進数の区切り
		IsEqual(pDim1->dimexe(),	 pDim2->dimexe()) &&   // 寸法補助線延長長さ
		IsEqual(pDim1->dimexo(),	 pDim2->dimexo()) &&   // 寸法補助線のオフセット			   
			   (pDim1->dimfrac()  == pDim2->dimfrac()) &&  // 分数の形式
		IsEqual(pDim1->dimgap(),	 pDim2->dimgap()) &&   // 文字オフセット   
			   (pDim1->dimjust()  == pDim2->dimjust()) &&  // 水平方向の寸法値位置
		IsEqual(pDim1->dimlfac(),    pDim2->dimlfac()) &&  // 長さの寸法尺度 
			   (pDim1->dimlim()   == pDim2->dimlim())  &&  	
			   (pDim1->dimlunit() == pDim2->dimlunit()) &&  // 寸法の単位
			   (pDim1->dimlwd()   == pDim2->dimlwd()) &&     // 寸法線の太さ
			   (pDim1->dimlwe()   == pDim2->dimlwe()) &&  	 // 寸法補助線の太さ
	 IsEqualStr(pDim1->dimpost(),    pDim2->dimpost()) &&  // 寸法値の接頭表記, 寸法値の末尾表記
		IsEqual(pDim1->dimrnd(),	 pDim2->dimrnd()) &&     // 寸法値の丸め
			   (pDim1->dimsah()   == pDim2->dimsah()) &&   
		IsEqual(pDim1->dimscale(),   pDim2->dimscale()) &&  // 全体の寸法尺度
			   (pDim1->dimsd1()   == pDim2->dimsd1()) &&     // 寸法線1
			   (pDim1->dimsd2()   == pDim2->dimsd2()) &&	 // 寸法線2
			   (pDim1->dimse1()   == pDim2->dimse1()) &&	 // 寸法補助線1
			   (pDim1->dimse2()   == pDim2->dimse2()) &&     // 寸法補助線2
			   (pDim1->dimsoxd()  == pDim2->dimsoxd()) &&  // 寸法線内側
			   (pDim1->dimtad()   == pDim2->dimtad()) &&   // 垂直方向の寸法値位置
			   (pDim1->dimtdec()  == pDim2->dimtdec()) &&  // 許容差の精度
		IsEqual(pDim1->dimtfac(),	 pDim2->dimtfac()) &&  // 許容差の文字高さ(DIMTXT高さに対する)
			   (pDim1->dimtih()   == pDim2->dimtih())  &&  		
			   (pDim1->dimtix()   == pDim2->dimtix()) &&  // 寸法内側位置合わせ, 寸法値内側記入
		IsEqual(pDim1->dimtm(),		 pDim2->dimtm()) &&   // 許容差のマイナス値, 許容差のプラス値: DIMTOL or DIMLIMがオンのとき有効 
			   (pDim1->dimtmove() == pDim2->dimtmove()) &&  // 寸法値の移動
			   (pDim1->dimtofl()  == pDim2->dimtofl()) &&  // 寸法線強制記入
			   (pDim1->dimtoh()   == pDim2->dimtoh()) &&    // 寸法値外側位置合わせ
			   (pDim1->dimtol()   == pDim2->dimtol()) &&    // 許容差表示
			   (pDim1->dimtolj()  == pDim2->dimtolj()) &&  // 許容差の垂直方向の位置
		IsEqual(pDim1->dimtp(),		 pDim2->dimtp()) &&  
		IsEqual(pDim1->dimtsz(),	 pDim2->dimtsz()) &&  
		IsEqual(pDim1->dimtvp(),	 pDim2->dimtvp()) &&  	
		IsEqual(pDim1->dimtxt(),	 pDim2->dimtxt()) &&  // 文字高さ
			   (pDim1->dimtzin()  == pDim2->dimtzin()) &&  // 許容差の接頭の0を省略, 許容差の末尾の0を省略, 許容差の0フィートを省略, 許容差の0インチを省略			   
			   (pDim1->dimupt()   == pDim2->dimupt())  &&  
			   (pDim1->dimzin()   == pDim2->dimzin()));  // 接頭の0を省略, 末尾の0を省略, 0フィートを省略, 0インチを省略

	
	return bSysVar;
	
}	

// 2LineAngularDimension
bool ACCompEntitiesGeom::Compare2LineAngularDimensionGeoms(AcDbEntity *pEnt1, AcDbEntity *pEnt2)
{	
	if (!CompareDimensionGeoms(pEnt1, pEnt2))
		return false;

	AcDb2LineAngularDimension *p2LADim1 = AcDb2LineAngularDimension::cast(pEnt1);
	AcDb2LineAngularDimension *p2LADim2 = AcDb2LineAngularDimension::cast(pEnt2);
	
	if (p2LADim1 == NULL || p2LADim2 == NULL)
		return false;
	
	return (
	  IsEqual(p2LADim1->arcPoint(),    p2LADim2->arcPoint()) &&  
	  IsEqual(p2LADim1->xLine1End(),   p2LADim2->xLine1End()) &&   
	  IsEqual(p2LADim1->xLine1Start(), p2LADim2->xLine1Start()) &&   
	  IsEqual(p2LADim1->xLine2End(),   p2LADim2->xLine2End()) &&   
	  IsEqual(p2LADim1->xLine2Start(), p2LADim2->xLine2Start()));  
}	

// 3PointAngularDimension
bool ACCompEntitiesGeom::Compare3PointAngularDimensionGeoms(AcDbEntity *pEnt1, AcDbEntity *pEnt2)
{
	if (!CompareDimensionGeoms(pEnt1, pEnt2))
		return false;

	AcDb3PointAngularDimension *p3LADim1 = AcDb3PointAngularDimension::cast(pEnt1);
	AcDb3PointAngularDimension *p3LADim2 = AcDb3PointAngularDimension::cast(pEnt2);
	
	if (p3LADim1 == NULL || p3LADim2 == NULL)
		return false;

	return (  
		IsEqual(p3LADim1->arcPoint(),    p3LADim2->arcPoint()) &&  
		IsEqual(p3LADim1->centerPoint(), p3LADim2->centerPoint()) &&   
		IsEqual(p3LADim1->xLine1Point(), p3LADim2->xLine1Point()) &&    
		IsEqual(p3LADim1->xLine2Point(), p3LADim2->xLine2Point()));  
}	

// AlignedDimension
bool ACCompEntitiesGeom::CompareAlignedDimensionGeoms(AcDbEntity *pEnt1, AcDbEntity *pEnt2)
{
	if (!CompareDimensionGeoms(pEnt1, pEnt2))
		return false;

	AcDbAlignedDimension *pAliDim1 = AcDbAlignedDimension::cast(pEnt1);
	AcDbAlignedDimension *pAliDim2 = AcDbAlignedDimension::cast(pEnt2);
	
	if (pAliDim1 == NULL || pAliDim2 == NULL)
		return false;

	//return (

	bool bRet = (
		IsEqual(pAliDim1->dimLinePoint(), pAliDim2->dimLinePoint()) &&  	
		IsEqual(pAliDim1->oblique(),	  pAliDim2->oblique())      &&  	
		IsEqual(pAliDim1->xLine1Point(),  pAliDim2->xLine1Point())  &&	
		IsEqual(pAliDim1->xLine2Point(),  pAliDim2->xLine2Point()));
	
	return bRet;
}	

// DiametricDimension
bool ACCompEntitiesGeom::CompareDiametricDimensionGeoms(AcDbEntity *pEnt1, AcDbEntity *pEnt2)
{
	if (!CompareDimensionGeoms(pEnt1, pEnt2))
		return false;

	AcDbDiametricDimension *pDiaDim1 = AcDbDiametricDimension::cast(pEnt1);
	AcDbDiametricDimension *pDiaDim2 = AcDbDiametricDimension::cast(pEnt2);
	
	if (pDiaDim1 == NULL || pDiaDim2 == NULL)
		return false;

	return (
		IsEqual(pDiaDim1->chordPoint(),	   pDiaDim2->chordPoint())    &&   
		IsEqual(pDiaDim1->farChordPoint(), pDiaDim2->farChordPoint())   &&   
		IsEqual(pDiaDim1->leaderLength(),  pDiaDim2->leaderLength()));  
}	

// OrdinateDimension
bool ACCompEntitiesGeom::CompareOrdinateDimensionGeoms(AcDbEntity *pEnt1, AcDbEntity *pEnt2)
{
	if (!CompareDimensionGeoms(pEnt1, pEnt2))
		return false;
	
	AcDbOrdinateDimension *pOrdDim1 = AcDbOrdinateDimension::cast(pEnt1);
	AcDbOrdinateDimension *pOrdDim2 = AcDbOrdinateDimension::cast(pEnt2);
	
	if (pOrdDim1 == NULL || pOrdDim2 == NULL)
		return false;

	return (
		IsEqual(pOrdDim1->definingPoint(),  pOrdDim2->definingPoint()) &&    
			   (pOrdDim1->isUsingXAxis() == pOrdDim2->isUsingXAxis()) &&   
			   (pOrdDim1->isUsingYAxis() == pOrdDim2->isUsingYAxis()) &&  
		IsEqual(pOrdDim1->leaderEndPoint(), pOrdDim2->leaderEndPoint()) &&  
		IsEqual(pOrdDim1->origin(),			pOrdDim2->origin()));  
}	

// RadialDimension
bool ACCompEntitiesGeom::CompareRadialDimensionGeoms(AcDbEntity *pEnt1, AcDbEntity *pEnt2)
{
	if (!CompareDimensionGeoms(pEnt1, pEnt2))
		return false;

	AcDbRadialDimension *pRadDim1 = AcDbRadialDimension::cast(pEnt1);
	AcDbRadialDimension *pRadDim2 = AcDbRadialDimension::cast(pEnt2);
	
	if (pRadDim1 == NULL || pRadDim2 == NULL)
		return false;

	return (
		IsEqual(pRadDim1->center(),		  pRadDim2->center()) &&   
		IsEqual(pRadDim1->chordPoint(),   pRadDim2->chordPoint()) &&   
		IsEqual(pRadDim1->leaderLength(), pRadDim2->leaderLength()));  
}	

// RotatedDimension
bool ACCompEntitiesGeom::CompareRotatedDimensionGeoms(AcDbEntity *pEnt1, AcDbEntity *pEnt2)
{
	if (!CompareDimensionGeoms(pEnt1, pEnt2))
		return false;

	AcDbRotatedDimension *pRotDim1 = AcDbRotatedDimension::cast(pEnt1);
	AcDbRotatedDimension *pRotDim2 = AcDbRotatedDimension::cast(pEnt2);
	
	if (pRotDim1 == NULL || pRotDim2 == NULL)
		return false;

	return (
		IsEqual(pRotDim1->dimLinePoint(), pRotDim2->dimLinePoint()) &&   
		IsEqual(pRotDim1->oblique(),	  pRotDim2->oblique()) &&  
		IsEqual(pRotDim1->rotation(),	  pRotDim2->rotation()) &&  
		IsEqual(pRotDim1->xLine1Point(),  pRotDim2->xLine1Point()) &&  
		IsEqual(pRotDim1->xLine2Point(),  pRotDim2->xLine2Point()));  
}	


// ---- その他AcDbEntity派生クラスの比較 ---- //
// ブロック参照			
bool ACCompEntitiesGeom::CompareBlockReferenceGeoms(AcDbEntity *pEnt1, AcDbEntity *pEnt2)
{
	AcDbBlockReference *pBlkRef1 = AcDbBlockReference::cast(pEnt1);
	AcDbBlockReference *pBlkRef2 = AcDbBlockReference::cast(pEnt2);
	
	if (pBlkRef1 == NULL || pBlkRef2 == NULL)
		return false;
	
	// 属性の比較
	bool bEqualQuery = (
		IsEqual(pBlkRef1->position(),	  pBlkRef2->position()) &&   // 挿入点XYZ
		IsEqual(pBlkRef1->rotation(),     pBlkRef2->rotation()) &&   // 回転 
		IsEqual(pBlkRef1->scaleFactors(), pBlkRef2->scaleFactors())); // 尺度XYZ 		
	
	if (!bEqualQuery)
		return false;

	// 名前、パスの比較 + 構成要素の比較
	// 外部参照の場合のみパスを比較する。	
	AcDbBlockTableRecord *pBlkRec1, *pBlkRec2;
	AcDbObjectId	      idBlkRec1, idBlkRec2;
	Acad::ErrorStatus     es1, es2;
	bool bEqualRec = true;
	
	idBlkRec1 = pBlkRef1->blockTableRecord();
	idBlkRec2 = pBlkRef2->blockTableRecord();

	es1 = acdbOpenObject(pBlkRec1, idBlkRec1, AcDb::kForRead);
	es2 = acdbOpenObject(pBlkRec2, idBlkRec2, AcDb::kForRead);

	if (es1 == Acad::eOk && es2 == Acad::eOk) {			 
		TCHAR *pcName1  = NULL, *pcName2  = NULL;//2006.07.20		
		bool bIsXRef1, bIsXRef2; 

		// 名前の比較
		pBlkRec1->getName(pcName1);
		pBlkRec2->getName(pcName2);

		bEqualRec = IsEqualStr(pcName1, pcName2);
			
		acutDelString(pcName1);
		acutDelString(pcName2);				
	
		// 外部参照である場合はパスの比較
		bIsXRef1 = (pBlkRec1->xrefDatabase() != NULL);
		bIsXRef2 = (pBlkRec2->xrefDatabase() != NULL);
		
		if (bIsXRef1 && bIsXRef2) {
			TCHAR *pcPath1 = NULL, *pcPath2 = NULL;//2006.07.20
			pBlkRec1->pathName(pcPath1);
			pBlkRec2->pathName(pcPath2);

			bEqualRec = bEqualRec && IsEqualStr(pcPath1, pcPath2);
				
			acutDelString(pcPath1);
			acutDelString(pcPath2);	
		}
		else if (bIsXRef1 != bIsXRef2) {
			bEqualRec = false;
		}

		if (!CompareBlockRecSubEntityGeoms(pBlkRec1, pBlkRec2))
			bEqualRec = false;

		
	}
	else {
		bEqualRec = false;
	}
	
	if (es1 == Acad::eOk)
		pBlkRec1->close();

	if (es2 == Acad::eOk)
		pBlkRec2->close();
	
	if (!bEqualRec)
		return false;
	


	return true;
}

// MInsertBlock?		
bool ACCompEntitiesGeom::CompareMInsertBlockGeoms(AcDbEntity *pEnt1, AcDbEntity *pEnt2)
{
	return true;

	AcDbMInsertBlock *pMInsBlk1 = AcDbMInsertBlock::cast(pEnt1);
	AcDbMInsertBlock *pMInsBlk2 = AcDbMInsertBlock::cast(pEnt2);
	
	if (pMInsBlk1 == NULL || pMInsBlk2 == NULL)
		return false;

	return true;
}
		
// Face	比較対象外
bool ACCompEntitiesGeom::CompareFaceGeoms(AcDbEntity *pEnt1, AcDbEntity *pEnt2)
{

	/*
	AcDbFace *pFace1 = AcDbFace::cast(pEnt1);
	AcDbFace *pFace2 = AcDbFace::cast(pEnt2);
	Acad::ErrorStatus es1, es2;

	if (pFace1 == NULL || pFace2 == NULL)
		return false;

	for (int i = 0; i < 4; i++) {
		AcGePoint3d    pt3_1, pt3_2;
		Adesk::Boolean abVisible1, abVisible2;

		es1 = pFace1->getVertexAt(i, pt3_1);
		es2 = pFace2->getVertexAt(i, pt3_2);
		
		if ( es1 != es2 ) 
			return false;

		if ( es1 == Acad::eOk && !IsEqual(pt3_1, pt3_2) )
				return false;

		es1 = pFace1->isEdgeVisibleAt(i, abVisible1);
		es2 = pFace2->isEdgeVisibleAt(i, abVisible2);

		if ( es1 != es2 )
			return false;

		if ( es1 == Acad::eOk && abVisible1 != abVisible2 )
				return false;
	}
	*/

	return true;
}

// FaceRecord 比較対象外	
bool ACCompEntitiesGeom::CompareFaceRecordGeoms(AcDbEntity *pEnt1, AcDbEntity *pEnt2)
{
	/*
	AcDb2LineAngularDimension *p2LADim1 = AcDb2LineAngularDimension::cast(pEnt1);
	AcDb2LineAngularDimension *p2LADim2 = AcDb2LineAngularDimension::cast(pEnt2);
	
	if (p2LADim1 == NULL || p2LADim2 == NULL)
		return false;
	*/

	return true;
}

// Fcf: 幾何公差	
bool ACCompEntitiesGeom::CompareFcfGeoms(AcDbEntity *pEnt1, AcDbEntity *pEnt2)
{
	AcDbFcf *pFcf1 = AcDbFcf::cast(pEnt1);
	AcDbFcf *pFcf2 = AcDbFcf::cast(pEnt2);
	
	if (pFcf1 == NULL || pFcf2 == NULL)
		return false;

	//direction  
	//getBoundingPline  
	//getBoundingPoints  
	//getDimstyleData  
	//normal  

	// 寸法線の色、位置XYZ、寸法スタイル、全体の寸法尺度、
	// 文字の色、文字高さ、文字スタイル、寸法値上書き

	// 属性の比較
	bool bEqualQuery = (
		IsEqual(pFcf1->dimclrd(),   pFcf2->dimclrd())  &&  // 寸法線の色
		IsEqual(pFcf1->dimclrt(),   pFcf2->dimclrt())  &&  // 文字の色
		IsEqual(pFcf1->dimscale(),  pFcf2->dimscale()) &&  // 全体の寸法尺度	
		IsEqual(pFcf1->dimtxt(),    pFcf2->dimtxt())   &&  // 文字高さ		
		IsEqual(pFcf1->location(),  pFcf2->location()));   // 位置XYZ	
	
	if (!bEqualQuery)
		return false;


	// 寸法値上書きの比較
	TCHAR *pcText1 = NULL, *pcText2 = NULL; //2006.07.20
	bool bEqualText;

	pcText1 = pFcf1->text();    // 寸法値上書き?
	pcText2 = pFcf2->text();

	bEqualText = IsEqualStr(pcText1, pcText2);
	
	acutDelString(pcText1);
	acutDelString(pcText2);
	
	if (!bEqualText)
		return false;


	// 文字スタイル名の比較
	AcDbSymbolTableRecord *pSymRec1, *pSymRec2;
	AcDbObjectId idTxtStl1, idTxtStl2; 
	Acad::ErrorStatus es1, es2;
	bool bEqualTxtStl = true;

	idTxtStl1 = pFcf1->dimtxsty();  // 文字スタイル
	idTxtStl2 = pFcf2->dimtxsty();
	
	// textStyle or dimensionStyle ? 
	es1 = acdbOpenObject(pSymRec1, idTxtStl1, AcDb::kForRead);
	es2 = acdbOpenObject(pSymRec2, idTxtStl2, AcDb::kForRead);

	if (es1 == Acad::eOk && es2 == Acad::eOk) {
		TCHAR *pcTxtStl1 = NULL, *pcTxtStl2 = NULL;//2006.07.20
		
		pSymRec1->getName(pcTxtStl1);
		pSymRec2->getName(pcTxtStl2);
		
		bEqualTxtStl = IsEqualStr(pcTxtStl1, pcTxtStl2);

		acutDelString(pcTxtStl1);
		acutDelString(pcTxtStl2);
	}
	else {
		bEqualTxtStl = false;
	}

	if (es1 == Acad::eOk)
		pSymRec1->close();

	if (es2 == Acad::eOk)
		pSymRec2->close();
		
	if (!bEqualTxtStl)		
		return false;


	// 寸法スタイル名の比較
	if (!CompareDimStyle(pFcf1->dimensionStyle(), pFcf2->dimensionStyle()))
		return false;

	return true;
}

// ??? Frameは抽象クラスか?	
//bool ACCompEntitiesGeom::CompareFrameGeoms(AcDbEntity *pEnt1, AcDbEntity *pEnt2)
//{	
//	return true;
//}

// OleFrame 比較対象外
bool ACCompEntitiesGeom::CompareOleFrameGeoms(AcDbEntity *pEnt1, AcDbEntity *pEnt2)
{
	/*
	AcDb2LineAngularDimension *p2LADim1 = AcDb2LineAngularDimension::cast(pEnt1);
	AcDb2LineAngularDimension *p2LADim2 = AcDb2LineAngularDimension::cast(pEnt2);
	
	if (p2LADim1 == NULL || p2LADim2 == NULL)
		return false;
	*/
	return true;
}

// Ole2Frame 比較対象外
bool ACCompEntitiesGeom::CompareOle2FrameGeoms(AcDbEntity *pEnt1, AcDbEntity *pEnt2)
{
	/*
	AcDb2LineAngularDimension *p2LADim1 = AcDb2LineAngularDimension::cast(pEnt1);
	AcDb2LineAngularDimension *p2LADim2 = AcDb2LineAngularDimension::cast(pEnt2);
	
	if (p2LADim1 == NULL || p2LADim2 == NULL)
		return false;
	*/

	return true;
}

// ハッチング	
bool ACCompEntitiesGeom::CompareHatchGeoms(AcDbEntity *pEnt1, AcDbEntity *pEnt2)
{
	AcDbHatch *pHatch1 = AcDbHatch::cast(pEnt1);
	AcDbHatch *pHatch2 = AcDbHatch::cast(pEnt2);
	
	if (pHatch1 == NULL || pHatch2 == NULL)
		return false;

	//タイプ、パターン名、角度、尺度、間隔、ISOペン幅、ダブル、高度、自動調整、島の検出スタイル		

	//ISOペン幅(disable)→おそらくハッチングパターンに依存する。
	bool bEqualQuery = (
		IsEqual(pHatch1->patternAngle(),    pHatch2->patternAngle())  && // 角度 
			   (pHatch1->patternDouble() == pHatch2->patternDouble()) && // ダブル 
	 IsEqualStr(pHatch1->patternName(),		pHatch2->patternName())   && // パターン名
		IsEqual(pHatch1->patternScale(),	pHatch2->patternScale())  && // 尺度
		IsEqual(pHatch1->patternSpace(),	pHatch2->patternSpace())  && // 間隔
			   (pHatch1->patternType()	 ==	pHatch2->patternType())   && // タイプ	
		IsEqual(pHatch1->elevation(),	    pHatch2->elevation())     && // 高度		
			   (pHatch1->hatchStyle()    == pHatch2->hatchStyle()));     // 島の検出スタイル 				   

	if (!bEqualQuery)
		return false;

	// 自動調整
	//bool bAssoc;
	if (pHatch1->associative() != pHatch2->associative())
		return false;    


	// 境界線の比較		
	int iNumLoops;

	if ((iNumLoops = pHatch1->numLoops()) != pHatch2->numLoops())
		return false;
	
	for (int k = 0; k < iNumLoops; k++) { 	
		Adesk::Int32 iLoopType1, iLoopType2;
		bool bRes;

		iLoopType1 = pHatch1->loopTypeAt(k);
		iLoopType2 = pHatch2->loopTypeAt(k);

		if (iLoopType1 != iLoopType2)
			return false;

		if ((iLoopType1 & AcDbHatch::kPolyline) == AcDbHatch::kPolyline)		
			bRes = CompareHatchBoundary_Type_Polyline(k, pHatch1, pHatch2);
		else {
			bRes = CompareHatchBoundary(k, pHatch1, pHatch2);
		}

		if (!bRes)
			return false;

				
	}		

	return true;
}
		
// Imageは抽象クラス		
//bool ACCompEntitiesGeom::CompareImageGeoms(AcDbEntity *pEnt1, AcDbEntity *pEnt2)
//{	
//	return true;
//}

// RasterImage		
bool ACCompEntitiesGeom::CompareRasterImageGeoms(AcDbEntity *pEnt1, AcDbEntity *pEnt2)
{
	AcDbRasterImage *pRImg1 = AcDbRasterImage::cast(pEnt1);
	AcDbRasterImage *pRImg2 = AcDbRasterImage::cast(pEnt2);
	
	if (pRImg1 == NULL || pRImg2 == NULL)
		return false;
	
	// 明るさ, コントラスト, フェード, 位置XYZ、回転、幅、高さ、尺度
	// 名前、パス、イメージ表示、クリップされたものを表示、透過性
	// 、、

	// 、回転?、、	
	
	//isClipped 

	bool bEqualQuery = (
			   (pRImg1->brightness() == pRImg2->brightness()) &&  // 明るさ
			   (pRImg1->contrast()   == pRImg2->contrast()) &&    // コントラスト
			   (pRImg1->fade()       == pRImg2->fade()) &&		// フェード 
			   (pRImg1->isSetDisplayOpt(AcDbRasterImage::kShow) == 
				pRImg2->isSetDisplayOpt(AcDbRasterImage::kShow)) &&   // イメージ表示
			   (pRImg1->isSetDisplayOpt(AcDbRasterImage::kShowUnAligned) == 
				pRImg2->isSetDisplayOpt(AcDbRasterImage::kShowUnAligned)) &&
			   (pRImg1->isSetDisplayOpt(AcDbRasterImage::kClip) ==    
				pRImg2->isSetDisplayOpt(AcDbRasterImage::kClip)) &&   // クリップされたものを表示
  			   (pRImg1->isSetDisplayOpt(AcDbRasterImage::kTransparent) == 
				pRImg2->isSetDisplayOpt(AcDbRasterImage::kTransparent))); // &&  // 透過性

	bEqualQuery = bEqualQuery && (
		IsEqual(pRImg1->imageSize(),    pRImg2->imageSize()) &&  // 幅、高さ
		IsEqual(pRImg1->scale()[0],		pRImg2->scale()[0]) &&  	   // 尺度
		IsEqual(pRImg1->scale(),		pRImg2->scale())); 	   // 尺度

	if (!bEqualQuery)
		return false;

	// 位置の比較
	// 位置XYZ, 「回転」の情報も含まれる？ 要テスト
	AcGePoint3d pt3Org1, pt3Org2;
	AcGeVector3d vec3U1, vec3U2, vec3V1, vec3V2; 
	bool bEqualPos;

	pRImg1->getOrientation(pt3Org1, vec3U1, vec3V1);
	pRImg2->getOrientation(pt3Org2, vec3U2, vec3V2);
	
	bEqualPos = (
		IsEqual(pt3Org1, pt3Org2) &&
		IsEqual(vec3U1,  vec3U2)  &&
		IsEqual(vec3V1,  vec3V2));

	if (!bEqualPos)
		return false;		
	
	// イメージ定義の比較
	// 名前、パス
	AcDbRasterImageDef *pImgDef1, *pImgDef2;
	AcDbObjectId	    idDef1, idDef2;
	Acad::ErrorStatus   es1, es2;
	bool bEqualDef = true;

	idDef1 = pRImg1->imageDefId(); 
	idDef2 = pRImg2->imageDefId(); 

	es1 = acdbOpenObject(pImgDef1, idDef1, AcDb::kForRead);
	es2 = acdbOpenObject(pImgDef2, idDef2, AcDb::kForRead);
	
	if (es1 == Acad::eOk && es2 == Acad::eOk) {
		CString strName1,    strName2;
		CString strSrcPath1, strSrcPath2;
		
		strName1 = pImgDef1->activeFileName();
		strName2 = pImgDef2->activeFileName();
		
		if (strName1.CompareNoCase(strName2) != 0)
			bEqualDef = false;

		strSrcPath1 = pImgDef1->sourceFileName();
		strSrcPath2 = pImgDef2->sourceFileName();
		
		if (strSrcPath1.CompareNoCase(strSrcPath2) != 0)		
			bEqualDef = false;		
	}
	else {
		bEqualDef = false;
	}

	if (es1 == Acad::eOk)
		pImgDef1->close();

	if (es2 == Acad::eOk)
		pImgDef2->close();

	return bEqualDef;
}

// Mline	
bool ACCompEntitiesGeom::CompareMlineGeoms(AcDbEntity *pEnt1, AcDbEntity *pEnt2)
{
	AcDbMline *pMline1 = AcDbMline::cast(pEnt1);
	AcDbMline *pMline2 = AcDbMline::cast(pEnt2);
	bool bEqualQuery;

	if (pMline1 == NULL || pMline2 == NULL)
		return false;

	// マルチラインスタイルのみ？
	
	//getPlane  	
	//justification  
	//normal  
	// 属性の比較
	bEqualQuery = (
			   (pMline1->closedMline()      == pMline2->closedMline()) &&
		IsEqual(pMline1->scale(),			   pMline2->scale()) &&
			   (pMline1->supressStartCaps() == pMline2->supressStartCaps()) && 		
			   (pMline1->supressEndCaps()   == pMline2->supressEndCaps()));
	
	if (!bEqualQuery)
		return false;

	// マルチラインスタイルの比較 スタイルの比較は名前のみで行う。			
	AcDbObjectId    idStyle1, idStyle2;
	AcDbMlineStyle *pmlStl1, *pmlStl2; 
	Acad::ErrorStatus es1, es2;
	bool bResStyle = true;

	idStyle1 = pMline1->style();
	idStyle2 = pMline2->style();
	
	es1 = acdbOpenObject(pmlStl1, idStyle1, AcDb::kForRead);
	es2 = acdbOpenObject(pmlStl2, idStyle2, AcDb::kForRead);
	
	if (es1 == Acad::eOk && es2 == Acad::eOk) {			
		CString strStlName1, strStlName2;

		strStlName1 = pmlStl1->name();
		strStlName2 = pmlStl2->name();

		if (strStlName1.CompareNoCase(strStlName2) != 0)
			bResStyle = false;
	}
	else {
		bResStyle = false;
	}

	if (es1 == Acad::eOk)
		pmlStl1->close();

	if (es2 == Acad::eOk)
		pmlStl2->close();

	if (!bResStyle)
		return false;


	// 頂点の比較
	if (pMline1->numVertices() != pMline2->numVertices())  
		return false;

	for (int i = 0; i < pMline1->numVertices(); i++) {
		if (!IsEqual(pMline1->vertexAt(i), pMline2->vertexAt(i)))   	
			return false;	
	}

	return true;
}
	
// MText	
bool ACCompEntitiesGeom::CompareMTextGeoms(AcDbEntity *pEnt1, AcDbEntity *pEnt2)
{
	AcDbMText *pMText1 = AcDbMText::cast(pEnt1);
	AcDbMText *pMText2 = AcDbMText::cast(pEnt2);
	
	if (pMText1 == NULL || pMText2 == NULL)
		return false;
	
	// 内容、スタイル、位置合わせ、方向（スタイルに準拠）、幅、高さ、回転、行間隔の尺度、行間隔のスタイル
	// ［ｼﾞｵﾒﾄﾘ］位置XYZ	

	bool bEqualQuery = (
			   (pMText1->attachment() == pMText2->attachment()) &&   // 位置合わせ		
		//IsEqual(pMText1->alignmentPoint(),	  pMText2->alignmentPoint()) &&   // 位置合わせ	
		IsEqual(pMText1->flowDirection(),	  pMText2->flowDirection()) &&     // 方向（スタイルに準拠） 
		IsEqual(pMText1->lineSpacingFactor(), pMText2->lineSpacingFactor()) &&   // 行間隔の尺度
		IsEqual(pMText1->lineSpacingStyle(),  pMText2->lineSpacingStyle()) &&   // 行間隔のスタイル
		IsEqual(pMText1->location(),		  pMText2->location()) &&    // 位置XYZ
		IsEqual(pMText1->rotation(),		  pMText2->rotation()) &&	// 回転 
		IsEqual(pMText1->textHeight(),		  pMText2->textHeight()) &&  // 高さ		
		IsEqual(pMText1->width(),			  pMText2->width()));   // 幅

	if (!bEqualQuery)
		return false;
	

	// テキストスタイルの比較
	if (!CompareTextStyle(pMText1->textStyle(), pMText2->textStyle()))
		return false;
	

	// 内容の比較
	TCHAR *pcContents1 = NULL, *pcContents2 = NULL;//2006.07.20
	bool bEqualContents;
	
	pcContents1 = pMText1->contents();		// 内容
	pcContents2 = pMText2->contents();

	bEqualContents = IsEqualStr(pcContents1, pcContents2);

	acutDelString(pcContents1);
	acutDelString(pcContents2);

	return bEqualContents;

	/*
	alignChange  
	blockBegin  
	blockEnd  
	colorChange  
	fontChange  
	heightChange  
	nonBreakSpace  
	obliqueChange  
	overlineOff  
	overlineOn  
	paragraphBreak  
	stackStart  
	trackChange  
	underlineOff  
	underlineOn  
	widthChange  
	lineBreak
	actualHeight  
	actualWidth  	
	attachment  	
	direction     	
	getBoundingPoints  
	getEcs  
	horizontalMode  
	isDefaultAlignment  
	isMirroredInX  
	isMirroredInY  
	isR12StyleText  
	normal  
	oblique  
	thickness  
	verticalMode  	
	*/	
}

// Point	
bool ACCompEntitiesGeom::ComparePointGeoms(AcDbEntity *pEnt1, AcDbEntity *pEnt2)
{
	AcDbPoint *pPnt1 = AcDbPoint::cast(pEnt1);
	AcDbPoint *pPnt2 = AcDbPoint::cast(pEnt2);
	
	if (pPnt1 == NULL || pPnt2 == NULL)
		return false;

	// 位置XYZ, 厚さ
	return (
		IsEqual(pPnt1->position(),  pPnt2->position()) &&  // 位置XYZ
		IsEqual(pPnt1->thickness(), pPnt2->thickness()));  // 厚さ	 	
}

// PolyFaceMesh	比較対象外
bool ACCompEntitiesGeom::ComparePolyFaceMeshGeoms(AcDbEntity *pEnt1, AcDbEntity *pEnt2)
{
	/*
	AcDb2LineAngularDimension *p2LADim1 = AcDb2LineAngularDimension::cast(pEnt1);
	AcDb2LineAngularDimension *p2LADim2 = AcDb2LineAngularDimension::cast(pEnt2);
	
	if (p2LADim1 == NULL || p2LADim2 == NULL)
		return false;
	*/

	return true;
}

// PolygonMesh 比較対象外	
bool ACCompEntitiesGeom::ComparePolygonMeshGeoms(AcDbEntity *pEnt1, AcDbEntity *pEnt2)
{
	/*
	AcDbPolygonMesh *pPolyMesh1 = AcDbPolygonMesh::cast(pEnt1);
	AcDbPolygonMesh *pPolyMesh2 = AcDbPolygonMesh::cast(pEnt2);
	
	if (pPolyMesh1 == NULL || pPolyMesh2 == NULL)
		return false;
	
	// 頂点数、(各)頂点XYZ、
	// M方向に閉じている、N方向に閉じている、M方向の密度、N方向の密度、M方向の頂点数、N方向の頂点数、
	// フィット/スムーズ

	bool bEqualQuery = (
		(pPolyMesh1->isMClosed()	   == pPolyMesh2->isMClosed()) &&  // M方向に閉じている
		(pPolyMesh1->isNClosed()	   == pPolyMesh2->isNClosed()) &&  // N方向に閉じている
		(pPolyMesh1->mSize()		   == pPolyMesh2->mSize()) &&   // M方向の頂点数	
		(pPolyMesh1->mSurfaceDensity() == pPolyMesh2->mSurfaceDensity()) && // M方向の密度
		(pPolyMesh1->nSize()		   == pPolyMesh2->nSize()) &&			 // N方向の頂点数
		(pPolyMesh1->nSurfaceDensity() == pPolyMesh2->nSurfaceDensity()) &&  // N方向の密度
		(pPolyMesh1->polyMeshType()    == pPolyMesh2->polyMeshType()));  // フィット/スムーズ

	if (!bEqualQuery)
		return false;

	//AcDbObjectIterator *vertexIterator() const;

	//Acad::ErrorStatus openVertex(AcDbPolygonMeshVertex*& , AcDbObjectId, AcDb::OpenMode)

	*/

	return true;
}

// ProxyEntity 比較対象外	
bool ACCompEntitiesGeom::CompareProxyEntityGeoms(AcDbEntity *pEnt1, AcDbEntity *pEnt2)
{
	/*
	AcDb2LineAngularDimension *p2LADim1 = AcDb2LineAngularDimension::cast(pEnt1);
	AcDb2LineAngularDimension *p2LADim2 = AcDb2LineAngularDimension::cast(pEnt2);
	
	if (p2LADim1 == NULL || p2LADim2 == NULL)
		return false;
	*/

	return true;
}

// Shape	
bool ACCompEntitiesGeom::CompareShapeGeoms(AcDbEntity *pEnt1, AcDbEntity *pEnt2)
{
	AcDbShape *pShape1 = AcDbShape::cast(pEnt1);
	AcDbShape *pShape2 = AcDbShape::cast(pEnt2);
	
	if (pShape1 == NULL || pShape2 == NULL)
		return false;

	// シェイプファイル必要 比較項目が不明

	bool bEqualQuery = (
		//IsEqual(pShape1->normal(),		pShape2->normal())	    && 
		IsEqual(pShape1->oblique(),		pShape2->oblique())		&&  // 傾斜
		IsEqual(pShape1->position(),	pShape2->position())	&&  // 位置XYZ
		IsEqual(pShape1->rotation(),	pShape2->rotation())	&&  // 回転		
		//IsEqual(pShape1->shapeNumber(), pShape2->shapeNumber()) &&   
		IsEqual(pShape1->size(),		pShape2->size())		&&  // サイズ
		IsEqual(pShape1->thickness(),	pShape2->thickness())   &&  // 厚さ
		IsEqual(pShape1->widthFactor(), pShape2->widthFactor()));   // 縦横比

	if (!bEqualQuery)
		return false;

	// SHX フォントシンボルテーブルレコードのID
	//pShape1->shapeIndex  
	//Adesk::Int16 pShape1->shapeNumber() const;

	// 名前
	TCHAR *pcName1 = NULL, *pcName2 = NULL;//2006.07.20
	bool bEqualName;
	
	// 正しいnameを得るため、図面を交互にアクティブにする。
	acDocManager->activateDocument(acDocManager->document(pShape1->database()));	
	pcName1 = pShape1->name();
	
	acDocManager->activateDocument(acDocManager->document(pShape2->database()));
	pcName2 = pShape2->name();	

	bEqualName = IsEqualStr(pcName1, pcName2);
	
	acutDelString(pcName1);
	acutDelString(pcName2);

	if (!bEqualName)
		return false;

	return true;
}

// Solid	
bool ACCompEntitiesGeom::CompareSolidGeoms(AcDbEntity *pEnt1, AcDbEntity *pEnt2)
{
	AcDbSolid *pSolid1 = AcDbSolid::cast(pEnt1);
	AcDbSolid *pSolid2 = AcDbSolid::cast(pEnt2);
	
	if (pSolid1 == NULL || pSolid2 == NULL)
		return false;

	// 頂点XY、頂点高度、厚さ
	// normal  
	if (!IsEqual(pSolid1->thickness(), pSolid2->thickness()))  // 厚さ
		return false;	

	// 頂点XY、高度
	for (int i = 0; i < 4; i++) {
		AcGePoint3d pt3_1, pt3_2;
		Acad::ErrorStatus es1, es2;

		es1 = pSolid1->getPointAt(i, pt3_1);
		es2 = pSolid2->getPointAt(i, pt3_2);		

		if (es1 != es2)
			return false;
		
		if (es1 == Acad::eOk && !IsEqual(pt3_1, pt3_2))
			return false;			
	}

	return true;	
}
	
// テキスト	
// bApplyGap: alignmentPointの比較で比較基点のずれを考慮するか否か
//   　
bool ACCompEntitiesGeom::CompareTextGeoms(AcDbEntity *pEnt1, AcDbEntity *pEnt2)
{
	AcDbText *pText1 = AcDbText::cast(pEnt1);
	AcDbText *pText2 = AcDbText::cast(pEnt2);
	bool bEqualQuery;

	if (pText1 == NULL || pText2 == NULL)
		return false;		

	//// , 高さ, 位置合わせ(1), 位置合わせ(2), 上下を逆, 前後を逆, 傾斜, 位置XYZ, 回転, 縦横比  
	//// 内容, 文字スタイル
	
	// 属性の比較
	bEqualQuery = (		
		IsEqual(pText1->height(),			pText2->height()) && // 高さ
		       (pText1->horizontalMode() == pText2->horizontalMode()) &&  // 位置合わせ(1)
			   (pText1->isMirroredInX()  ==	pText2->isMirroredInX()) && // 上下を逆
			   (pText1->isMirroredInY()  ==	pText2->isMirroredInY()) &&  // 前後を逆  
		IsEqual(pText1->oblique(),			pText2->oblique()) &&  // 傾斜
		IsEqual(pText1->position(),			pText2->position()) &&   // 位置XYZ
		IsEqual(pText1->rotation(),			pText2->rotation()) &&    // 回転		
		IsEqual(pText1->thickness(),		pText2->thickness()) &&   
			   (pText1->verticalMode()   ==	pText2->verticalMode()) && // 位置合わせ(2)
		IsEqual(pText1->widthFactor(),		pText2->widthFactor()));  // 縦横比
	
	if (!bEqualQuery)
		return false;


	// 位置合わせの比較：左寄せである場合のみ、比較基点のずれを考慮しない。
	bool bEqualAlignment;
	if (pText1->horizontalMode() == AcDb::kTextLeft && pText1->verticalMode() == AcDb::kTextBase) 
		bEqualAlignment = IsEqualNoGap(pText1->alignmentPoint(), pText2->alignmentPoint());   // 文字位置合わせXYZ
	else
		bEqualAlignment = IsEqual(pText1->alignmentPoint(), pText2->alignmentPoint());   // 文字位置合わせXYZ

	if (!bEqualAlignment)
		return false;	


	// 内容の比較
	TCHAR *pcContents1 = NULL, *pcContents2 = NULL;
	bool bEqualContents = true;	

	pcContents1 = pText1->textString();
	pcContents2 = pText2->textString();
	
	//// 内容が同じである場合と、両方NULLである場合はtrue
	bEqualContents = IsEqualStr(pcContents1, pcContents2);
	
	acutDelString(pcContents1);	
	acutDelString(pcContents2);

	if (!bEqualContents)
		return false;


	// 文字スタイルの比較 スタイル名のみ比較する。
	AcDbTextStyleTableRecord  *ptxtStlRec1, *ptxtStlRec2;
	AcDbObjectId idTxtStl1, idTxtStl2;
	Acad::ErrorStatus es1, es2;
	bool bEqualStyle = true;

	idTxtStl1 = pText1->textStyle();
	idTxtStl2 = pText2->textStyle();

	es1 = acdbOpenObject(ptxtStlRec1, idTxtStl1, AcDb::kForRead);
	es2 = acdbOpenObject(ptxtStlRec2, idTxtStl2, AcDb::kForRead);		
		
	if (es1 == Acad::eOk && es2 == Acad::eOk) {
		TCHAR *pcStlName1 = NULL, *pcStlName2 = NULL;//2006.07.20

		ptxtStlRec1->getName(pcStlName1);
		ptxtStlRec2->getName(pcStlName2);

		bEqualStyle = IsEqualStr(pcStlName1, pcStlName2);
		
		acutDelString(pcStlName1);
		acutDelString(pcStlName2);
	}
	else {
		bEqualStyle = false;
	}	

	if (es1 == Acad::eOk)
		ptxtStlRec1->close();

	if (es2 == Acad::eOk)
		ptxtStlRec2->close();

	return bEqualStyle;	
}

// 属性	
bool ACCompEntitiesGeom::CompareAttributeGeoms(AcDbEntity *pEnt1, AcDbEntity *pEnt2)
{
	// テキストの属性の比較をする。
	if (!CompareTextGeoms(pEnt1, pEnt2))
		return false;

	// 以下、Attribute独自の属性の比較をする。
	AcDbAttribute *pAttr1 = AcDbAttribute::cast(pEnt1);
	AcDbAttribute *pAttr2 = AcDbAttribute::cast(pEnt2);
	

	if (pAttr1 == NULL || pAttr2 == NULL)
		return false;

	// 名称、値、スタイル、位置合わせ、高さ、回転、縦横比、傾斜、
	// 文字位置合わせXYZ、位置XYZ、上下を逆、前後を逆、非表示、一定、確認、プリセット
	
	// ↑の内、attributeのみの属性は、
	// 名称、値 → (文字)
	// 、非表示、一定、確認、プリセット
	
	//fieldLength  
	bool bEqualQuery = (
		(pAttr1->isConstant()   == pAttr2->isConstant()) &&
		(pAttr1->isInvisible()  == pAttr2->isInvisible()) && 
		(pAttr1->isPreset()     == pAttr2->isPreset()) && 
		(pAttr1->isVerifiable() == pAttr2->isVerifiable()));   

	if (!bEqualQuery)
		return false;

	// タグの比較
	TCHAR *pcTag1 = NULL, *pcTag2 = NULL;//2006.07.20
	bool bEqualTag = true;	

	pcTag1 = pAttr1->tag();
	pcTag2 = pAttr2->tag();
	
	//// 内容が同じである場合と、両方NULLである場合はtrue
	bEqualTag = IsEqualStr(pcTag1, pcTag2);
	
	acutDelString(pcTag1);
	acutDelString(pcTag2);

	if (!bEqualTag)
		return false;

	return true;
}

// 属性定義	
bool ACCompEntitiesGeom::CompareAttributeDefinitionGeoms(AcDbEntity *pEnt1, AcDbEntity *pEnt2)
{
	// テキストの属性の比較をする。
	if (!CompareTextGeoms(pEnt1, pEnt2))
		return false;

	// 以下、Attribute独自の属性の比較をする。
	AcDbAttributeDefinition *pAttrDef1 = AcDbAttributeDefinition::cast(pEnt1);
	AcDbAttributeDefinition *pAttrDef2 = AcDbAttributeDefinition::cast(pEnt2);
	
	if (pAttrDef1 == NULL || pAttrDef2 == NULL)
		return false;

	//// 名称、プロンプト、値、スタイル、位置合わせ、高さ、回転、縦横比、傾斜、
	//// 文字位置合わせXYZ、位置XYZ、上下を逆、前後を逆、非表示、一定、確認、プリセット	
	
	//// ↑の内、attributedefのみの属性は、
	//// 名称、値 → (文字) 、非表示、一定、確認、プリセット
		
	//fieldLength  
	bool bEqualQuery = (
		(pAttrDef1->isConstant()   == pAttrDef2->isConstant()) &&
		(pAttrDef1->isInvisible()  == pAttrDef2->isInvisible()) && 
		(pAttrDef1->isPreset()     == pAttrDef2->isPreset()) && 
		(pAttrDef1->isVerifiable() == pAttrDef2->isVerifiable()));   

	if (!bEqualQuery)
		return false;


	// タグの比較
	TCHAR *pcTag1 = NULL, *pcTag2 = NULL;//2006.07.20
	bool bEqualTag;	

	pcTag1 = pAttrDef1->tag();
	pcTag2 = pAttrDef2->tag();
	
	//// 内容が同じである場合と、両方NULLである場合はtrue
	bEqualTag = IsEqualStr(pcTag1, pcTag2);
		
	acutDelString(pcTag1);	
	acutDelString(pcTag2);

	if (!bEqualTag)
		return false;	


	// プロンプトの比較
	TCHAR *pcProm1 = NULL, *pcProm2 = NULL;//2006.07.20
	bool bEqualPrompt;	

	pcProm1 = pAttrDef1->prompt();
	pcProm2 = pAttrDef2->prompt();
	
	//// 内容が同じである場合と、両方NULLである場合はtrue
	bEqualPrompt = IsEqualStr(pcProm1, pcProm2);
		
	acutDelString(pcProm1);
	acutDelString(pcProm2);

	return bEqualPrompt;	
}

// Trace	
bool ACCompEntitiesGeom::CompareTraceGeoms(AcDbEntity *pEnt1, AcDbEntity *pEnt2)
{
	AcDbTrace *pTrace1 = AcDbTrace::cast(pEnt1);
	AcDbTrace *pTrace2 = AcDbTrace::cast(pEnt2);
	
	if (pTrace1 == NULL || pTrace2 == NULL)
		return false;

	// 頂点数、(各)頂点XY、高度、厚さ
	// 頂点数は4で固定	
	
	// 厚さの比較
	if (!IsEqual(pTrace1->thickness(), pTrace2->thickness()))  
		return false;	

	// 各頂点の比較 XY、高度
	for (int i = 0; i < 4; i++) {
		AcGePoint3d pt3_1, pt3_2;
		Acad::ErrorStatus es1, es2;
		bool bEqualVtx = true;

		es1 = pTrace1->getPointAt(i, pt3_1);
		es2 = pTrace2->getPointAt(i, pt3_2);
	
		if (es1 == Acad::eOk && es2 == Acad::eOk) 
			bEqualVtx = IsEqual(pt3_1, pt3_2);			
		else if (es1 != es2)
			bEqualVtx = false;

		if (!bEqualVtx)
			return false;					
	}
	
	return true;	
}

// Viewport	
bool ACCompEntitiesGeom::CompareViewportGeoms(AcDbEntity *pEnt1, AcDbEntity *pEnt2)
{
	AcDbViewport *pVp1 = AcDbViewport::cast(pEnt1);
	AcDbViewport *pVp2 = AcDbViewport::cast(pEnt2);
	
	if (pVp1 == NULL || pVp2 == NULL)
		return false;
	
	/*
	// TEST S
	Adesk::Int16 iNum;
	bool bTrans;

	iNum = pVp1->number();
	bTrans = pVp1->isTransparent();
	// TEST E 
	*/
	
	/*
	// TEST // S
	AcDbObjectId idVp;
	AcDbLayout *pLayout;
	idVp = pVp1->objectId();
	pVp1->close();
	if (acdbOpenObject(pLayout, idVp, AcDb::kForRead) == Acad::eOk) {		
		pLayout->close();
	}

	if (acdbOpenObject(pVp1, idVp, AcDb::kForRead) != Acad::eOk)
		return false;
	// TEST // E
	*/





	// ↓ペーパー空間でプロパティを表示すると違うのでは？
	// 中央XYZ、高さ、幅
	// ［その他］オブジェクトを表示、クリップされている、ビューをロック、標準尺度、カスタム尺度、
	//          ビューごとのUCS、隠線印刷

	//double dcsVp1 = pVp1->customScale();
	//double dcsVp2 = pVp2->customScale();

	bool bEqualQuery = (	
		IsEqual(pVp1->customScale(),			pVp2->customScale()) &&     // カスタム尺度	
		IsEqual(pVp1->hiddenLinesRemoved(),		pVp2->hiddenLinesRemoved()) &&   // 隠線印刷	
		IsEqual(pVp1->isLocked(),				pVp2->isLocked()) &&         // ビューをロック
		IsEqual(pVp1->isOn(),					pVp2->isOn()) &&			// オブジェクトを表示		
		IsEqual(pVp1->standardScale(),			pVp2->standardScale()) && // 標準尺度			
		IsEqual(pVp1->isUcsSavedWithViewport(), pVp2->isUcsSavedWithViewport()) &&  // ビューごとのUCS
		IsEqual(pVp1->width(),					pVp2->width()) &&         // 幅
		IsEqual(pVp1->centerPoint(),			pVp2->centerPoint()) &&     // 中央XYZ
		IsEqual(pVp1->height(),				    pVp2->height())); // &&   // 高さ			

	bEqualQuery = bEqualQuery && (	
		IsEqual(pVp1->isBackClipOn(),  	        pVp2->isBackClipOn()) &&     // クリップされている?
		IsEqual(pVp1->isFrontClipOn(),		    pVp2->isFrontClipOn()) &&     // クリップされている?	
		IsEqual(pVp1->isFrontClipAtEyeOn(),     pVp2->isFrontClipAtEyeOn())); // クリップされている?	

	/*
	viewCenter
	viewHeight
	isTransparent  	
	renderMode  	  
	subObjModified  	
	backClipDistance  	
	circleSides  	
	effectivePlotStyleSheet  
	elevation  
	frontClipDistance  
	getFrozenLayerList  
	getUcs  
	gridIncrement  	
	isFastZoomOn  
	isFrontClipAtEyeOn  	
	isGridOn  
	isLayerFrozenInViewport  	
	isNonRectClipOn  	
	isPerspectiveOn  
	isSnapIsometric  
	isSnapOn  
	isUcsFollowModeOn  
	isUcsIconAtOrigin  
	isUcsIconVisible  
	isUcsOrthographic  	
	isViewOrthographic  
	lensLength  
	nonRectClipEntityId  
	number  
	plotStyleSheet  
	snapAngle  
	snapBasePoint  
	snapIncrement  
	snapIsoPair  	
	twistAngle  
	ucsName  	
	viewDirection  	
	viewTarget  	
	*/

  

	return bEqualQuery;
}

// 3dSolid 比較対象外	
bool ACCompEntitiesGeom::Compare3dSolidGeoms(AcDbEntity *pEnt1, AcDbEntity *pEnt2)
{
	/*
	AcDb2LineAngularDimension *p2LADim1 = AcDb2LineAngularDimension::cast(pEnt1);
	AcDb2LineAngularDimension *p2LADim2 = AcDb2LineAngularDimension::cast(pEnt2);
	
	if (p2LADim1 == NULL || p2LADim2 == NULL)
		return false;
	*/

	return true;
}

// Body	比較対象外
bool ACCompEntitiesGeom::CompareBodyGeoms(AcDbEntity *pEnt1, AcDbEntity *pEnt2)
{
	/*
	AcDb2LineAngularDimension *p2LADim1 = AcDb2LineAngularDimension::cast(pEnt1);
	AcDb2LineAngularDimension *p2LADim2 = AcDb2LineAngularDimension::cast(pEnt2);
	
	if (p2LADim1 == NULL || p2LADim2 == NULL)
		return false;
	*/

	return true;
}

// Region	
bool ACCompEntitiesGeom::CompareRegionGeoms(AcDbEntity *pEnt1, AcDbEntity *pEnt2)
{
	AcDbRegion *pRgn1 = AcDbRegion::cast(pEnt1);
	AcDbRegion *pRgn2 = AcDbRegion::cast(pEnt2);
	//bool bEqual;

	if (pRgn1 == NULL || pRgn2 == NULL)
		return false;
		
	//####TEST_S 	
	/*
	AcGe::EntityId

	AcDbFullSubentPath* pfsubPath;	
	int iNumPaths;
	
	pfsubPath = new AcDbFullSubentPath();
	pRgn1->getSubentPathsAtGsMarker(AcDb::kFaceSubentType, 1, AcGePoint3d(0,0,0), AcGeMatrix3d(), iNumPaths, pfsubPath);		
	
	AcBrFace face;
	face.setSubentPath(*pfsubPath);

	AcBrFaceLoopTraverser flt;
	AcBrLoopEdgeTraverser let;
	AcBrLoop loop;
	AcBrEdge edge;
	AcGeCurve3d *pCurv3;
	double dist = -1.0;
	AcGePoint3d pt_near, NearestPoint;
	//AcGePointOnCurve3d oncurve;

	flt.setFace(face);
	for( ; !flt.done(); flt.next() ) {
		let.setLoop(flt);
		let.getOrientedCurve(pCurv3);
		for( ; !let.done(); let.next() ) {
			let.getEdge(edge);
			edge.getCurve(pCurv3);
			edge.getCurveType(pCurv3);			
		}
	}
	*/
	//####TEST_E
	
	// リージョンの構成要素を比較する。
	//if (!CompareRegionComponent(pRgn1, pRgn2))
	//	return false;


	
	// 面積を比較する。注：このメソッドはメモリリークする？
	Acad::ErrorStatus es1, es2;
	double dArea1, dArea2, dPermeter1, dPermeter2;		 

	es1 = pRgn1->getArea(dArea1);
	es2 = pRgn2->getArea(dArea2);

	if (es1 != es2)		
		return false;

	if (es1 == Acad::eOk)		
		if (!IsEqual(dArea1, dArea2))
			return false;
	
	// 円周を比較する。注：このメソッドはメモリリークする？
	es1 = pRgn1->getPerimeter(dPermeter1);
	es2 = pRgn2->getPerimeter(dPermeter2);   
	
	if (es1 != es2)
		return false;

	if (es1 == Acad::eOk)		
		if (!IsEqual(dPermeter1, dPermeter2))
			return false;
	

	return true;
}

// AcDbBlockTableRecordのサブエンティティを比較する。
// pBlkRec1, pBlkRec2 はAcad::kForReadの状態で開かれていること。
bool ACCompEntitiesGeom::CompareBlockRecSubEntityGeoms(
AcDbBlockTableRecord *pBlkRec1, AcDbBlockTableRecord *pBlkRec2) 
{	
	AcDbBlockTableRecordIterator *pItrBlkRec1, *pItrBlkRec2;
	Acad::ErrorStatus es1, es2;
	bool bRes = true;

	es1 =  pBlkRec1->newIterator(pItrBlkRec1);
	es2 =  pBlkRec2->newIterator(pItrBlkRec2);

	if (es1 == Acad::eOk && es2 == Acad::eOk) {
		pItrBlkRec1->start();
		pItrBlkRec2->start();

		while (1) {
			AcDbEntity *pEntElm1, *pEntElm2;
			Acad::ErrorStatus esElm1, esElm2; 	
			bool bEnd1, bEnd2;
		
			// イテレイタの両端に達した場合はtrueが返る。
			bEnd1 = pItrBlkRec1->done();
			bEnd2 = pItrBlkRec2->done();	
			
			// イテレイタの要素数が異なる場合はfalseを返し終了
			if (bEnd1 != bEnd2) {
				bRes = false;
				break;
			}
			// イテレイタの要素数が同じで、終点に達した場合はtrueを返し終了
			else if (bEnd1)
				break;
			
			// 要素を開く
			esElm1 = pItrBlkRec1->getEntity(pEntElm1, AcDb::kForRead);
			esElm2 = pItrBlkRec2->getEntity(pEntElm2, AcDb::kForRead);
			
			if (esElm1 == Acad::eOk && esElm2 == Acad::eOk) {
				if (!IsEqualGeneralAttrs(pEntElm1, pEntElm2))
					bRes = false;
				
				if (bRes) {
					// bApplyGap = false：範囲比較モードでも、ブロックの構成要素は比較範囲の
					//   基点のずれを考慮しないで比較を行う。
					// 構成要素は、ブロック空間に属するため、モデル空間上の座標とは関係がない。
					if (!CompareEntityGeoms(pEntElm1, pEntElm2, false))
						bRes = false;					
				}
			}
			else
				bRes = false;
			
			if (esElm1 == Acad::eOk)
				pEntElm1->close();

			if (esElm2 == Acad::eOk)
				pEntElm2->close();
			
			if (!bRes) {					
				break;
			}
			
			pItrBlkRec1->step();
			pItrBlkRec2->step();				
		}			
	}
	// eOk以外は、イテレータ取得時のメモリ不足
	else {
		bRes = false;
	}

	if (pItrBlkRec1 != NULL)
		delete pItrBlkRec1;

	if (pItrBlkRec2 != NULL)
		delete pItrBlkRec2;	

	return bRes;
}

// AcDbVertex派生クラス
// AcDbVertex	
bool ACCompEntitiesGeom::CompareVertexGeoms(AcDbEntity *pEnt1, AcDbEntity *pEnt2)
{
	return true;
}

// AcDb2dVertex	
bool ACCompEntitiesGeom::Compare2dVertexGeoms(AcDbEntity *pEnt1, AcDbEntity *pEnt2)
{
	AcDb2dVertex *p2dVtx1 = AcDb2dVertex::cast(pEnt1);
	AcDb2dVertex *p2dVtx2 = AcDb2dVertex::cast(pEnt2);

	if (p2dVtx1 == NULL || p2dVtx2 == NULL)
		return false;
	
	return Compare2dVertexGeoms(p2dVtx1, p2dVtx2);
}

// AcDb3dPolylineVertex	
bool ACCompEntitiesGeom::Compare3dPolylineVertexGeoms(AcDbEntity *pEnt1, AcDbEntity *pEnt2)
{
	AcDb3dPolylineVertex *p3dPolyVtx1 = AcDb3dPolylineVertex::cast(pEnt1);
	AcDb3dPolylineVertex *p3dPolyVtx2 = AcDb3dPolylineVertex::cast(pEnt2);
	
	if (p3dPolyVtx1 == NULL || p3dPolyVtx2 == NULL)
		return false;
	
	return Compare3dPolylineVertexGeoms(p3dPolyVtx1, p3dPolyVtx2);	
}

// AcDbPolyFaceMeshVertex サポート対象外	
bool ACCompEntitiesGeom::ComparePolyFaceMeshVertexGeoms(AcDbEntity *pEnt1, AcDbEntity *pEnt2)
{	
	return true;
}

// AcDbPolygonMeshVertex サポート対象外	
bool ACCompEntitiesGeom::ComparePolygonMeshVertexGeoms(AcDbEntity *pEnt1, AcDbEntity *pEnt2)
{
	return true;
}

// 指定されたIDでBlockTableRecordを開き、その名前を比較する。
// 開いたときの結果がeOkで、名前が同じ場合はbRetOpenOk=trueで、trueを返す。
// 開いたときの結果がeOk以外のときは、bRetOpenOk=falseで、結果が同じかどうかを戻り値で返す。
bool ACCompEntitiesGeom::CompareBlockTableRecord(const AcDbObjectId &idRec1, const AcDbObjectId &idRec2, bool &bRetOpenOk)
{
	AcDbBlockTableRecord *pBlkRec1, *pBlkRec2;
	Acad::ErrorStatus    es1, es2;
	bool bRet = true;		

	es1 = acdbOpenObject(pBlkRec1, idRec1, AcDb::kForRead);	
	es2 = acdbOpenObject(pBlkRec2, idRec2, AcDb::kForRead);	

	if (es1 == Acad::eOk && es2 == Acad::eOk) {
		TCHAR *pcName1 = NULL, *pcName2 = NULL;//2006.07.20
		
		bRetOpenOk = true;

		pBlkRec1->getName(pcName1);				
		pBlkRec2->getName(pcName2);				
		bRet = IsEqualStr(pcName1, pcName2);
		acutDelString(pcName1);
		acutDelString(pcName2);		
	}
	else if (es1 != es2) {
		bRet = false;
	}

	if (es1 == Acad::eOk) 
		pBlkRec1->close();

	if (es2 == Acad::eOk) 
		pBlkRec2->close();

	return bRet;
}

// 寸法スタイルの比較
// 寸法スタイルが存在し、その名前が異なる場合はfalseを返す。
bool ACCompEntitiesGeom::CompareDimStyle(const AcDbObjectId &idDimStl1, const AcDbObjectId &idDimStl2)
{
	AcDbDimStyleTableRecord *pDimStlRec1, *pDimStlRec2;	
	Acad::ErrorStatus es1, es2;		
	bool bRet = true;

	es1 = acdbOpenObject(pDimStlRec1, idDimStl1, AcDb::kForRead);   	
	es2 = acdbOpenObject(pDimStlRec2, idDimStl2, AcDb::kForRead);   	

	if (es1 == Acad::eOk && es2 == Acad::eOk) {
		Acad::ErrorStatus esN1, esN2;
		TCHAR *pcName1 = NULL, *pcName2 = NULL; 	//2006.07.20	
		
		esN1 = pDimStlRec1->getName(pcName1);
		esN2 = pDimStlRec2->getName(pcName2);		
		
		if (esN1 == Acad::eOk && esN2 == Acad::eOk)  
			bRet = IsEqualStr(pcName1, pcName2);			
		else			
			bRet = false;

		acutDelString(pcName1);
		acutDelString(pcName2);					
	}
	else {
		bRet = false;
	}
	
	if (es1 == Acad::eOk) 
		pDimStlRec1->close();		

	if (es2 == Acad::eOk) 
		pDimStlRec2->close();

	return bRet;		
}

// テキストスタイルの比較
// テキストスタイルが存在し、その名前が異なる場合はfalseを返す。
bool ACCompEntitiesGeom::CompareTextStyle(const AcDbObjectId &idTxtStl1, const AcDbObjectId &idTxtStl2)
{
	AcDbTextStyleTableRecord *pTxtStlRec1, *pTxtStlRec2;	
	Acad::ErrorStatus es1, es2;		
	bool bRet = true;

	es1 = acdbOpenObject(pTxtStlRec1, idTxtStl1, AcDb::kForRead);   	
	es2 = acdbOpenObject(pTxtStlRec2, idTxtStl2, AcDb::kForRead);   	

	if (es1 == Acad::eOk && es2 == Acad::eOk) {
		Acad::ErrorStatus esN1, esN2;
		TCHAR *pcName1 = NULL, *pcName2 = NULL; 	//2006.07.20	
		
		esN1 = pTxtStlRec1->getName(pcName1);
		esN2 = pTxtStlRec2->getName(pcName2);		
		
		if (esN1 == Acad::eOk && esN2 == Acad::eOk)  
			bRet = IsEqualStr(pcName1, pcName2);			
		else			
			bRet = false;

		acutDelString(pcName1);
		acutDelString(pcName2);					
	}
	else {
		bRet = false;
	}
	
	if (es1 == Acad::eOk) 
		pTxtStlRec1->close();		

	if (es2 == Acad::eOk) 
		pTxtStlRec2->close();

	return bRet;		
}

// ハイパーリンクの比較	
//// ハイパーリンクが同じであるときと、両方とも拡張データがないときにtrueを返す。
bool ACCompEntitiesGeom::CompareHyperLink(AcDbEntity *pEnt1, AcDbEntity *pEnt2)
{		
	CString strHPL1, strHPL2;

	strHPL1 = ACEntityInfo::GetHyperLink(pEnt1);
	strHPL2 = ACEntityInfo::GetHyperLink(pEnt2);

	return IsEqualStr(strHPL1, strHPL2);
}

// 指定した寸法線が自動調整寸法であるか調べる。
bool ACCompEntitiesGeom::IsAssociatedDimension(AcDbDimension *pDim) {
	AcDbVoidPtrArray  *pReactors;		
	AcDbObjectId      idPersReac;	
	int				  iLenReac;
	bool			  bRes = false;
	void			  *pSomething;
						
	pReactors = pDim->reactors();							
	if (pReactors == NULL) 
		return bRes;
			
	iLenReac = pReactors->logicalLength();
	for (int l = 0; l < iLenReac; l++) {			
		pSomething = (void *)pReactors->at(l);	
		if (acdbIsPersistentReactor(pSomething)) {
			idPersReac = acdbPersistentReactorObjectId(pSomething);												
			AcDbObject *pObjAssoc;
			
			// 寸法線のリアクタのIDがAcDbDimAssocを指すときは、自動調整寸法と判断する。
			if (acdbOpenObject(pObjAssoc, idPersReac, AcDb::kForRead) == Acad::eOk) {
				CString strName;					
				strName = pObjAssoc->isA()->name();

				if (strName.CompareNoCase(_T("AcDbDimAssoc")) == 0)//2006.07.20
					bRes = true;

				//if (pObjAssoc->isA()->isEqualTo(AcDbDimAssoc::desc()) == Adesk::kTrue)
				//	bRes = true;

				pObjAssoc->close();
			}
		}
	}
	
	return bRes;
}

// シンボルテーブルのレコードを名前で比較する。
bool ACCompEntitiesGeom::CompareSymbolTableRecord(const AcDbObjectId &idRec1, const AcDbObjectId &idRec2)
{
	AcDbSymbolTableRecord *pSymRec1, *pSymRec2;	
	Acad::ErrorStatus es1, es2;		
	bool bRet = true;

	es1 = acdbOpenObject(pSymRec1, idRec1, AcDb::kForRead);   	
	es2 = acdbOpenObject(pSymRec2, idRec2, AcDb::kForRead);   	

	if (es1 == Acad::eOk && es2 == Acad::eOk) {
		Acad::ErrorStatus esN1, esN2;
		TCHAR *pcName1 = NULL, *pcName2 = NULL; //2006.07.20		
		
		esN1 = pSymRec1->getName(pcName1);
		esN2 = pSymRec1->getName(pcName2);		
		
		if (esN1 == Acad::eOk && esN2 == Acad::eOk)  
			bRet = IsEqualStr(pcName1, pcName2);			
		else			
			bRet = false;

		acutDelString(pcName1);
		acutDelString(pcName2);					
	}
	else {
		bRet = false;
	}
	
	if (es1 == Acad::eOk) 
		pSymRec1->close();		

	if (es2 == Acad::eOk) 
		pSymRec1->close();

	return bRet;		

}


//AcGeCircArc2d の比較
bool ACCompEntitiesGeom::CompareCircArc2dGeom(AcGeCircArc2d *pCArc1, AcGeCircArc2d *pCArc2) 
{
	return (
		IsEqual(pCArc1->center(),	   pCArc2->center()) &&   
		IsEqual(pCArc1->endAng(),	   pCArc2->endAng()) &&
		IsEqual(pCArc1->endPoint(),    pCArc2->endPoint()) &&   
		IsEqual(pCArc1->isClockWise(), pCArc2->isClockWise()) &&   
		IsEqual(pCArc1->radius(),	   pCArc2->radius()) &&   
		IsEqual(pCArc1->refVec(),	   pCArc2->refVec()) &&   
		IsEqual(pCArc1->startAng(),    pCArc2->startAng()) &&   
		IsEqual(pCArc1->startPoint(),  pCArc2->startPoint()));   
}

//AcGeEllipArc2d の比較
bool ACCompEntitiesGeom::CompareEllipArc2dGeom(AcGeEllipArc2d *pEArc1, AcGeEllipArc2d *pEArc2) 
{
	return (
		IsEqual(pEArc1->center(),	   pEArc2->center())	  &&   
		IsEqual(pEArc1->endAng(),	   pEArc2->endAng())	  &&    
		IsEqual(pEArc1->endPoint(),	   pEArc2->endPoint())	  &&   
		IsEqual(pEArc1->isCircular(),  pEArc2->isCircular())  &&  
		IsEqual(pEArc1->isClockWise(), pEArc2->isClockWise()) &&   
		IsEqual(pEArc1->majorAxis(),   pEArc2->majorAxis())   &&  
		IsEqual(pEArc1->majorRadius(), pEArc2->majorRadius()) &&  
		IsEqual(pEArc1->minorAxis(),   pEArc2->minorAxis())   &&  
		IsEqual(pEArc1->minorRadius(), pEArc2->minorRadius()) &&   
		IsEqual(pEArc1->startAng(),    pEArc2->startAng())    &&   
		IsEqual(pEArc1->startPoint(),  pEArc2->startPoint())); 
}

//AcGeLineSeg2d の比較
bool ACCompEntitiesGeom::CompareLineSeg2dGeom(AcGeLineSeg2d *pLineSeg1, AcGeLineSeg2d *pLineSeg2) 
{
	
	//length  
	return (
		IsEqual(pLineSeg1->endPoint(),   pLineSeg2->endPoint()) &&   
		IsEqual(pLineSeg1->midPoint(),   pLineSeg2->midPoint()) &&   
		IsEqual(pLineSeg1->startPoint(), pLineSeg2->startPoint()));  



}

//AcGeNurbCurve2d の比較
bool ACCompEntitiesGeom::CompareNurbCurve2dGeom(AcGeNurbCurve2d *pNCurve1, AcGeNurbCurve2d *pNCurve2) 
{
	//continuityAtKnot  
	//knotAt  
	//knots  
	//numKnots  
	//startParam  
	//startPoint  
	//endParam  
	//endPoint  
	//order  

	// 制御点の比較
	int iNumCtrlPts;

	if ((iNumCtrlPts = pNCurve1->numControlPoints()) != pNCurve2->numControlPoints())
		return false;

	for (int l = 0; l < iNumCtrlPts; l++) {
		if (!IsEqual(pNCurve1->controlPointAt(l), pNCurve2->controlPointAt(l)))
			return false;
	}

	
	bool bEqualQuery = (	
		IsEqual(pNCurve1->degree(),		pNCurve2->degree())     &&   	
		IsEqual(pNCurve1->hasFitData(), pNCurve2->hasFitData()) && 
		IsEqual(pNCurve1->isRational(), pNCurve2->isRational()));    	
	
	


	//evalMode  
	//getDefinitionData  // 制御点データ
	//getFitData  // フィット点データ 
	//getParamsOfC1Discontinuity ?  
	//getParamsOfG1Discontinuity ?  
	
		




	int iNumFitPt;

	if ((iNumFitPt = pNCurve1->numFitPoints()) != pNCurve2->numFitPoints())
		return false;

	for (int i = 0; i < iNumFitPt; i++) {
		AcGePoint2d pt2Fit1, pt2Fit2;

		pNCurve1->getFitPointAt(i, pt2Fit1);
		pNCurve2->getFitPointAt(i, pt2Fit2);
		
		if (!IsEqual(pt2Fit1, pt2Fit2))
			return false;
	}

	// FitTangentsの比較
	Adesk::Boolean abRes1, abRes2;	
	AcGeVector2d startTan1, startTan2, endTan1, endTan2;	
	
	abRes1 = pNCurve1->getFitTangents(startTan1, endTan1);	
	abRes2 = pNCurve2->getFitTangents(startTan2, endTan2);	
	
	if (abRes1 != abRes2)
		return false;

	if (abRes1 == Adesk::kTrue) {
		if (!IsEqual(startTan1, startTan2))
			return false;

		if (!IsEqual(endTan1, endTan2))
			return false;				
	}
	
	// FitToleranceの比較
	AcGeTol tol1, tol2;
	abRes1 = pNCurve1->getFitTolerance(tol1);
	abRes2 = pNCurve2->getFitTolerance(tol2);
	
	if (abRes1 != abRes2)
		return false;
	
	if (abRes1 == Adesk::kTrue) {
		if (!IsEqual(tol1, tol2))
			return false;
	}

	
	// weightの比較
	int iNumWeight;
		
	if ((iNumWeight = pNCurve1->numWeights()) != pNCurve2->numWeights())
		return false;

	for (int j = 0; j < iNumWeight; j++) {
		if (!IsEqual(pNCurve1->weightAt(j), pNCurve2->weightAt(j)))
			return false;
	}
	
	return true;
}


// ハッチング境界線 ポリラインタイプの比較
bool ACCompEntitiesGeom::CompareHatchBoundary_Type_Polyline(int iIdx, AcDbHatch *pHatch1, AcDbHatch *pHatch2) 
{
	Adesk::Int32 lpType1, lpType2;
	AcGePoint2dArray pt2aryVert1, pt2aryVert2;
	AcGeDoubleArray  daryBulg1,   daryBulg2;	
	Acad::ErrorStatus es1, es2;	
	int iLenVert, iLenBulg;

	es1 = pHatch1->getLoopAt(iIdx, lpType1, pt2aryVert1, daryBulg1);
	es2 = pHatch2->getLoopAt(iIdx, lpType2, pt2aryVert2, daryBulg2);
	
	if (!(es1 == Acad::eOk && es1 == Acad::eOk))
		return false;						

	//iLenVert = pt2aryVert2.logicalLength();
	if ((iLenVert = pt2aryVert1.logicalLength()) != pt2aryVert2.logicalLength()) 
		return false;

	for (int i = 0; i < iLenVert; i++) {
		if (!IsEqual(pt2aryVert1[i], pt2aryVert2[i]))
			return false;		
	}	

	if ((iLenBulg = daryBulg1.logicalLength()) != daryBulg2.logicalLength()) 
		return false;

	for (int j = 0; j < iLenBulg; j++) {		
		if (!IsEqual(daryBulg1[j], daryBulg2[j]))
			return false;
	}	

	return true;
}

// ハッチング境界線 ポリラインタイプ以外 の比較
bool ACCompEntitiesGeom::CompareHatchBoundary(int iIdx, AcDbHatch *pHatch1, AcDbHatch *pHatch2) 
{
	Adesk::Int32 lpType1, lpType2;
	AcGeVoidPointerArray vparyEdge1, vparyEdge2;  
	AcGeIntArray iaryEdgeType1, iaryEdgeType2;
	Acad::ErrorStatus es1, es2;	
	int iLen;

	es1 = pHatch1->getLoopAt(iIdx, lpType1, vparyEdge1, iaryEdgeType1);
	es2 = pHatch2->getLoopAt(iIdx, lpType2, vparyEdge2, iaryEdgeType2);
	
	if (!(es1 == Acad::eOk && es1 == Acad::eOk))
		return false;						

	if ((iLen = vparyEdge1.logicalLength()) != vparyEdge2.logicalLength()) 
		return false;

	for (int i = 0; i < iLen; i++) {
		if (iaryEdgeType1[i] != iaryEdgeType2[i])
			return false;

		switch (iaryEdgeType1[i]) {
			case AcDbHatch::kLine:
				if (!CompareLineSeg2dGeom((AcGeLineSeg2d *)vparyEdge1[i], (AcGeLineSeg2d *)vparyEdge2[i]))
					return false;
				break;
			case AcDbHatch::kCirArc:
				if (!CompareCircArc2dGeom((AcGeCircArc2d *)vparyEdge1[i], (AcGeCircArc2d *)vparyEdge2[i]))
					return false;
				break;
			case AcDbHatch::kEllArc:
				if (!CompareEllipArc2dGeom((AcGeEllipArc2d *)vparyEdge1[i], (AcGeEllipArc2d *)vparyEdge2[i]))
					return false;
				break;
			case AcDbHatch::kSpline:
				if (!CompareNurbCurve2dGeom((AcGeNurbCurve2d *)vparyEdge1[i], (AcGeNurbCurve2d *)vparyEdge2[i]))
					return false;
				break;				
		}
	}

	return true;
}

// リージョンの構成要素を比較する。
// fullSubentPath→AcBr→境界線の個々の図形比較の方法は、それぞれのAcGeクラスの比較を
// 作成するのが大変なため、リージョンを分解し、それぞれのAcDbを比較する方法にした。
bool ACCompEntitiesGeom::CompareRegionComponent(AcDbRegion *pRgn1, AcDbRegion *pRgn2) 
{
	AcDbVoidPtrArray vpAry1, vpAry2;
	Acad::ErrorStatus es1, es2;
	bool bRet = false;

	es1 = pRgn1->explode(vpAry1);				
	es2 = pRgn2->explode(vpAry2);				
	
	
	if (es1 == Acad::eOk && es2 == Acad::eOk && 
		vpAry1.logicalLength()  == vpAry2.logicalLength() &&
		vpAry1.logicalLength()  != 0) {		
		bRet = true;
		for (int i = 0; i < vpAry1.logicalLength(); i++) {
			// 範囲比較モードのときは、リージョンの比較は比較範囲の基点のずれを考慮する。
			// リージョンの構成要素はモデル空間上に属するため。
			if (!CompareEntityGeoms((AcDbEntity *)vpAry1[i], (AcDbEntity *)vpAry2[i]), true) {
				bRet = false;
				break;
			}
		}									
	}	
	
	if (es1 == Acad::eOk) {
		for (int j = 0; j < vpAry1.logicalLength(); j++) {
			AcDbEntity *pEnt1 = (AcDbEntity *)vpAry1[j];
					
			acutPrintf(_T("\ntypename: %s"), pEnt1->isA()->name());			//2006.07.20
			
			//delete (AcDbEntity::cast(vpAry1));
			
			if      (pEnt1->isA()->isEqualTo(AcDbLine::desc()) == Adesk::kTrue) {
				AcDbLine *pLine1 = AcDbLine::cast(pEnt1);	
				delete pLine1;			
			}
			else if (pEnt1->isA()->isEqualTo(AcDbArc::desc()) == Adesk::kTrue) {
				AcDbArc *pArc1 = AcDbArc::cast(pEnt1);
				delete pArc1;
			}
			else if (pEnt1->isA()->isEqualTo(AcDbCircle::desc()) == Adesk::kTrue) {
				AcDbCircle *pCir1 = AcDbCircle::cast(pEnt1);
				delete pCir1;
			}
			else if (pEnt1->isA()->isEqualTo(AcDbSpline::desc()) == Adesk::kTrue) {
				AcDbSpline *pSpl1 = AcDbSpline::cast(pEnt1);
				delete pSpl1;
			}
			else
				acutPrintf(_T("\ntype    : else"));//2006.07.20			
		}			
	}

	if (es2 == Acad::eOk) {
		for (int k = 0; k < vpAry2.logicalLength(); k++) {
			AcDbEntity *pEnt2 = (AcDbEntity *)vpAry2[k];

			acutPrintf(_T("\ntypename: %s"), pEnt2->isA()->name());			//2006.07.20

			if      (pEnt2->isA()->isEqualTo(AcDbLine::desc()) == Adesk::kTrue) {
				AcDbLine *pLine2 = AcDbLine::cast(pEnt2);	
				delete pLine2;			
			}
			else if (pEnt2->isA()->isEqualTo(AcDbArc::desc()) == Adesk::kTrue) {
				AcDbArc *pArc2 = AcDbArc::cast(pEnt2);
				delete pArc2;				
			}
			else if (pEnt2->isA()->isEqualTo(AcDbCircle::desc()) == Adesk::kTrue) {
				AcDbCircle *pCir2 = AcDbCircle::cast(pEnt2);
				delete pCir2;
			}
			else if (pEnt2->isA()->isEqualTo(AcDbSpline::desc()) == Adesk::kTrue) {
				AcDbSpline *pSpl2 = AcDbSpline::cast(pEnt2);
				delete pSpl2;
			}
			else
				acutPrintf(_T("\ntype    : else"));//2006.07.20			
		}		
	}					
	
	return bRet;
}

// CompareEntityGeoms関数のカバー関数
// AcGePoint3d型の比較時に使用するメンバ変数m_vec3BasePointGapApplyの制御を行う。
// ブロックとリージョンの比較を行うときに、再帰呼び出しを行う場合があるので、
// m_vec3BasePointGapApplyの制御を行うためにこのようにした。
bool ACCompEntitiesGeom::CompareEntityGeoms(AcDbEntity *pEnt1, AcDbEntity *pEnt2, bool bApplyGap)
{
	AcGeVector3d vec3Prev = m_vec3BasePointGapApply;
	bool bRes;

	// 2つの図面の比較基点のずれを考慮する指定の場合：
	// (A)範囲比較モード ： 比較範囲のずれを考慮して比較する。
	// (B)全図面比較モード: m_vec3BasePointGapが、(0,0,0)なので、比較範囲のずれは考慮せずに比較を行う。
	if (bApplyGap) 
		m_vec3BasePointGapApply = m_vec3BasePointGap;
	// 2つの図面の比較基点のずれを考慮しない指定の場合：
	//   (0,0,0)に設定されるので、比較範囲のずれは考慮せずに比較を行う。
	else
		m_vec3BasePointGapApply.set(0.0, 0.0, 0.0);

	// 比較を実行する。
	bRes = CompareEntityGeoms(pEnt1, pEnt2);

	// 比較基点のずれを元に戻す。
	m_vec3BasePointGapApply = vec3Prev;
	return bRes;
}
