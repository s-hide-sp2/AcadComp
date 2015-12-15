// ACCompEntitiesGeom.h: ACCompEntitiesGeom クラスのインターフェイス
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ACCOMPENTITIESGEOM_H__25291CD7_5C15_498A_BE88_757CCAB26930__INCLUDED_)
#define AFX_ACCOMPENTITIESGEOM_H__25291CD7_5C15_498A_BE88_757CCAB26930__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "StdAfx.h"
#include "ACCompBase.h"
#include "ACEntityInfo.h"

class ACCompEntitiesGeom : public ACCompBase
{
public:
	bool CompareEntityGeoms(AcDbEntity *pEnt1, AcDbEntity *pEnt2, bool bApplyGap);
	// 比較結果のタイプ
	enum CE_TYPE_RET {
		INVALID,
		EQUAL,
		NOTEQUAL,
		ONLY1,
		ONLY2,
		UNKNOWN
	};


	ACCompEntitiesGeom();
	virtual ~ACCompEntitiesGeom();

	

	// 図形比較時の許容誤差をセットする。
	//void SetTol(double dTol);

	// 指定した2つの図形の一般属性が等しいかどうか調べる。
	bool IsEqualGeneralAttrs(AcDbEntity *pEnt1, AcDbEntity *pEnt2);

private:	 
	// 指定されたエンティティのジオメトリの違いを調べる。
	// pEnt1, pEnt2 はAcad::kForReadで開かれていること
	// ユーザー派生クラス等は比較をせずにtrueを返す。
	// bApplyGap: 比較基点のずれを考慮して比較するかどうかを指定する。
	// 比較範囲モードでも、ブロック参照や、リージョンの構成要素の比較の場合は比較基点のずれを考慮する必要がないため。
	bool CompareEntityGeoms(AcDbEntity *pEnt1, AcDbEntity *pEnt2);


	// ---- カーブ派生クラスの比較 ---- //
	// 指定された2本のラインが図形的に等しいかどうか調べる。
	bool CompareLineGeoms(AcDbEntity *pEnt1, AcDbEntity *pEnt2);	

	// 2dポリラインの比較	
	bool Compare2dPolylineGeoms(AcDbEntity *pEnt1, AcDbEntity *pEnt2);	

	// 3dポリラインの比較		
	bool Compare3dPolylineGeoms(AcDbEntity *pEnt1, AcDbEntity *pEnt2);	

	// 円弧の比較	
	bool CompareArcGeoms(AcDbEntity *pEnt1, AcDbEntity *pEnt2);	

	// 円の比較		
	bool CompareCircleGeoms(AcDbEntity *pEnt1, AcDbEntity *pEnt2);	

	// 楕円の比較	
	bool CompareEllipseGeoms(AcDbEntity *pEnt1, AcDbEntity *pEnt2);	

	// 引出し線の比較	
	bool CompareLeaderGeoms(AcDbEntity *pEnt1, AcDbEntity *pEnt2);	

	// ポリラインの比較	
	bool ComparePolylineGeoms(AcDbEntity *pEnt1, AcDbEntity *pEnt2);	

	// Rayの比較		
	bool CompareRayGeoms(AcDbEntity *pEnt1, AcDbEntity *pEnt2);	

	// Splineの比較	
	bool CompareSplineGeoms(AcDbEntity *pEnt1, AcDbEntity *pEnt2);	

	// Xlineの比較		
	bool CompareXlineGeoms(AcDbEntity *pEnt1, AcDbEntity *pEnt2);	

	// Vettex
	// 2d頂点を比較する。
	bool Compare2dVertexGeoms(AcDb2dVertex *p2dVtx1, AcDb2dVertex *p2dVtx2);

	// 3d頂点を比較する。
	bool Compare3dPolylineVertexGeoms(AcDb3dPolylineVertex *p3dVtx1, AcDb3dPolylineVertex *p3dVtx2);


	//---- 寸法線派生クラスの比較 ----//
	// Dimension 基底クラスの属性の比較を行う。
	bool CompareDimensionGeoms(AcDbEntity *pEnt1, AcDbEntity *pEnt2);	

	// 2LineAngularDimension
	bool Compare2LineAngularDimensionGeoms(AcDbEntity *pEnt1, AcDbEntity *pEnt2);	

	// 3PointAngularDimension
	bool Compare3PointAngularDimensionGeoms(AcDbEntity *pEnt1, AcDbEntity *pEnt2);	

	// AlignedDimension
	bool CompareAlignedDimensionGeoms(AcDbEntity *pEnt1, AcDbEntity *pEnt2);	

	// DiametricDimension
	bool CompareDiametricDimensionGeoms(AcDbEntity *pEnt1, AcDbEntity *pEnt2);	

	// OrdinateDimension
	bool CompareOrdinateDimensionGeoms(AcDbEntity *pEnt1, AcDbEntity *pEnt2);	

	// RadialDimension
	bool CompareRadialDimensionGeoms(AcDbEntity *pEnt1, AcDbEntity *pEnt2);	

	// RotatedDimension
	bool CompareRotatedDimensionGeoms(AcDbEntity *pEnt1, AcDbEntity *pEnt2);	


	// ---- その他AcDbEntity派生クラスの比較 ---- //
	// ブロック参照			
	bool CompareBlockReferenceGeoms(AcDbEntity *pEnt1, AcDbEntity *pEnt2);

	// MInsertBlock?		
	bool CompareMInsertBlockGeoms(AcDbEntity *pEnt1, AcDbEntity *pEnt2);
			
	// Face	比較対象外
	bool CompareFaceGeoms(AcDbEntity *pEnt1, AcDbEntity *pEnt2);
	
	// FaceRecord 比較対象外
	bool CompareFaceRecordGeoms(AcDbEntity *pEnt1, AcDbEntity *pEnt2);
	
	// Fcf?	
	bool CompareFcfGeoms(AcDbEntity *pEnt1, AcDbEntity *pEnt2);
	
	// ??? Frameは抽象クラスか? → 抽象クラス	
	//bool CompareFrameGeoms(AcDbEntity *pEnt1, AcDbEntity *pEnt2);

	// OleFrame 比較対象外
	bool CompareOleFrameGeoms(AcDbEntity *pEnt1, AcDbEntity *pEnt2);

	// Ole2Frame 比較対象外	
	bool CompareOle2FrameGeoms(AcDbEntity *pEnt1, AcDbEntity *pEnt2);
	
	// ハッチング	
	bool CompareHatchGeoms(AcDbEntity *pEnt1, AcDbEntity *pEnt2);
			
	// ??? Imageは抽象クラスか? → 抽象クラス
	//bool CompareImageGeoms(AcDbEntity *pEnt1, AcDbEntity *pEnt2);

	// RasterImage		
	bool CompareRasterImageGeoms(AcDbEntity *pEnt1, AcDbEntity *pEnt2);

	// Mline	
	bool CompareMlineGeoms(AcDbEntity *pEnt1, AcDbEntity *pEnt2);
		
	// MText	
	bool CompareMTextGeoms(AcDbEntity *pEnt1, AcDbEntity *pEnt2);
	
	// Point	
	bool ComparePointGeoms(AcDbEntity *pEnt1, AcDbEntity *pEnt2);
	
	// PolyFaceMesh	比較対象外
	bool ComparePolyFaceMeshGeoms(AcDbEntity *pEnt1, AcDbEntity *pEnt2);
	
	// PolygonMesh 比較対象外
	bool ComparePolygonMeshGeoms(AcDbEntity *pEnt1, AcDbEntity *pEnt2);
	
	// ProxyEntity 比較対象外
	bool CompareProxyEntityGeoms(AcDbEntity *pEnt1, AcDbEntity *pEnt2);
	
	// Shape	
	bool CompareShapeGeoms(AcDbEntity *pEnt1, AcDbEntity *pEnt2);
	
	// Solid	
	bool CompareSolidGeoms(AcDbEntity *pEnt1, AcDbEntity *pEnt2);
		
	// テキスト	
	bool CompareTextGeoms(AcDbEntity *pEnt1, AcDbEntity *pEnt2);

	// 属性	
	bool CompareAttributeGeoms(AcDbEntity *pEnt1, AcDbEntity *pEnt2);

	// 属性定義	
	bool CompareAttributeDefinitionGeoms(AcDbEntity *pEnt1, AcDbEntity *pEnt2);
	
	// Trace	
	bool CompareTraceGeoms(AcDbEntity *pEnt1, AcDbEntity *pEnt2);
	
	// Viewport	
	bool CompareViewportGeoms(AcDbEntity *pEnt1, AcDbEntity *pEnt2);
	
	// 3dSolid 比較対象外
	bool Compare3dSolidGeoms(AcDbEntity *pEnt1, AcDbEntity *pEnt2);
	
	// Body	比較対象外 
	bool CompareBodyGeoms(AcDbEntity *pEnt1, AcDbEntity *pEnt2);
	
	// Region	
	bool CompareRegionGeoms(AcDbEntity *pEnt1, AcDbEntity *pEnt2);


	// AcDbVertex派生クラス
	// AcDbVertex	
	bool CompareVertexGeoms(AcDbEntity *pEnt1, AcDbEntity *pEnt2);
	// AcDb2dVertex	
	bool Compare2dVertexGeoms(AcDbEntity *pEnt1, AcDbEntity *pEnt2);
	// AcDb3dPolylineVertex	
	bool Compare3dPolylineVertexGeoms(AcDbEntity *pEnt1, AcDbEntity *pEnt2);
	// AcDbPolyFaceMeshVertex	
	bool ComparePolyFaceMeshVertexGeoms(AcDbEntity *pEnt1, AcDbEntity *pEnt2);
	// AcDbPolygonMeshVertex	
	bool ComparePolygonMeshVertexGeoms(AcDbEntity *pEnt1, AcDbEntity *pEnt2);
	
	// AcDbBlockTableRecordのサブエンティティを比較する。
	// pBlkRec1, pBlkRec2 はAcad::kForReadの状態で開かれていること。
	bool CompareBlockRecSubEntityGeoms(
		AcDbBlockTableRecord *pBlkRec1, 
		AcDbBlockTableRecord *pBlkRec2); 	
	
	// 指定されたIDでBlockTableRecordを開き、その名前を比較する。
	// 開いたときの結果がeOkで、名前が同じ場合はbRetOpenOk=trueで、trueを返す。
	// 開いたときの結果がeOk以外のときは、bRetOpenOk=falseで、結果が同じかどうかを戻り値で返す。
	bool CompareBlockTableRecord(const AcDbObjectId &idRec1, const AcDbObjectId &idRec2, bool &bRetOpenOk);

	// 寸法スタイルの比較
	// 寸法スタイルが存在し、その名前が異なる場合はfalseを返す。
	bool CompareDimStyle(const AcDbObjectId &idDimStl1, const AcDbObjectId &idDimStl2);

	// テキストスタイルの比較
	// テキストスタイルが存在し、その名前が異なる場合はfalseを返す。
	bool CompareTextStyle(const AcDbObjectId &idTxtStl1, const AcDbObjectId &idTxtStl2);


	// ハイパーリンクの比較	
	//// ハイパーリンクが同じであるときと、両方とも拡張データがないときにtrueを返す。
	bool CompareHyperLink(AcDbEntity *pEnt1, AcDbEntity *pEnt2);	

	// 指定した寸法線が自動調整寸法であるか調べる。
	bool IsAssociatedDimension(AcDbDimension *pDim);

	// シンボルテーブルのレコードを名前で比較する。
	bool CompareSymbolTableRecord(const AcDbObjectId &idRec1, const AcDbObjectId &idRec2);


	//// AcGeCurve派生クラス ////	
	//AcGeCircArc2d の比較
	bool CompareCircArc2dGeom(AcGeCircArc2d *pCArc1, AcGeCircArc2d *pCArc2); 

	//AcGeEllipArc2d の比較
	bool CompareEllipArc2dGeom(AcGeEllipArc2d *pEArc1, AcGeEllipArc2d *pEArc2); 

	//AcGeLineSeg2d の比較
	bool CompareLineSeg2dGeom(AcGeLineSeg2d *pLineSeg1, AcGeLineSeg2d *pLineSeg2); 

	//AcGeNurbCurve2d の比較
	bool CompareNurbCurve2dGeom(AcGeNurbCurve2d *pNCurve1, AcGeNurbCurve2d *pNCurve2); 	

	

	// ハッチング境界線 ポリラインタイプの比較
	bool CompareHatchBoundary_Type_Polyline(int iIdx, AcDbHatch *pHatch1, AcDbHatch *pHatch2); 

	// ハッチング境界線 ポリラインタイプ以外の比較
	bool CompareHatchBoundary(int iIdx, AcDbHatch *pHatch1, AcDbHatch *pHatch2); 

	// リージョンの構成要素を比較する。
	// fullSubentPath→AcBr→境界線の個々の図形比較の方法は、それぞれのAcGeクラスの比較を
	// 作成するのが大変なため、リージョンを分解し、それぞれのAcDbを比較する方法にした。
	bool CompareRegionComponent(AcDbRegion *pRgn1, AcDbRegion *pRgn2); 
};

#endif // !defined(AFX_ACCOMPENTITIESGEOM_H__25291CD7_5C15_498A_BE88_757CCAB26930__INCLUDED_)
