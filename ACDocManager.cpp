// ACDocManager.cpp: ACDocManager クラスのインプリメンテーション
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "resource.h"
#include "ACDocManager.h"
#include "ACProfileManager.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

#define ACADTLB

//////////////////////////////////////////////////////////////////////
// 構築/消滅
//////////////////////////////////////////////////////////////////////

ACDocManager::ACDocManager()
{
	m_pDocCur = NULL;
	m_bRangeCompMode = false;
	m_vec3Gap.set(0, 0, 0);
}

ACDocManager::~ACDocManager()
{

}

// 現在開いている全図面のパスの配列を得る。
void ACDocManager::GetDocPaths(CStringArray &saryRet, AcDbObjectIdArray &idaryBlkTbl)
{	
	AcApDocManager *pDocMng = acDocManager;
	AcApDocumentIterator *pDocItr = pDocMng->newAcApDocumentIterator(); 	
	int iDocCount = pDocMng->documentCount();
	int i = 0;

	saryRet.SetSize(iDocCount);
	
	if (!idaryBlkTbl.isEmpty())
		idaryBlkTbl.removeSubArray(0, idaryBlkTbl.logicalLength());
	idaryBlkTbl.setLogicalLength(iDocCount);	
	
	// 現在開かれているドキュメントを走査する。
	for (; !pDocItr->done(); pDocItr->step()) {
		AcApDocument *pDoc = pDocItr->document();
		
		saryRet[i] = pDoc->docTitle();
		//saryRet[i] = pDoc->fileName();
		
		idaryBlkTbl[i] = pDoc->database()->blockTableId();

		i++;
	}
	delete pDocItr;
}


// パスを指定して、図面オブジェクトを得る。
bool ACDocManager::GetDoc(LPCTSTR lpctDwgPath, AcApDocument *pDocRet)
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	AcApDocManager *pDocMng = acDocManager;
	AcApDocumentIterator *pDocItr = pDocMng->newAcApDocumentIterator(); 		
	bool bRes = false;

	// 現在開かれているドキュメントを走査する。
	for (; !pDocItr->done(); pDocItr->step()) {
		AcApDocument *pDoc = pDocItr->document();
		CString strDwgPath = pDoc->fileName();

		//acutPrintf("\ndoc: %s", pDoc->fileName());

		if (strDwgPath.CompareNoCase(lpctDwgPath) == 0) {
			pDocRet = (AcApDocument *)pDoc->contextPtr();
			bRes = true;
			break;
		}
	}
	delete pDocItr;	
	return bRes;
}

// 指定した図面を比較し、結果を得る。
bool ACDocManager::CompDwgs(
	CMap<int, int, AcDbObjectId, AcDbObjectId> &idmap1, 
	CMap<int, int, AcDbObjectId, AcDbObjectId> &idmap2,
	ResultCompEntity &rce)
{
	Acad::ErrorStatus es;
	int i = 0, j = 0, iIdx = 0;
	int iMax1 = idmap1.GetCount(), iMax2 = idmap2.GetCount();
	
	while (1) {
		AcDbObjectId idEnt1, idEnt2;	
		AcDbEntity *pEnt1 = NULL, *pEnt2 = NULL;
		
		if (i < iMax1) {
			idmap1.Lookup(i, idEnt1);
			es = acdbOpenObject(pEnt1, idEnt1, AcDb::kForRead);
//			es = acdbOpenObject(pEnt1, idEnt1, AcDb::kForWrite);
			if (es != Acad::eOk) {
				i++;
				continue;
			}
		}
		
		if (j < iMax2) {
			idmap2.Lookup(j, idEnt2);
			es = acdbOpenObject(pEnt2, idEnt2, AcDb::kForRead);
//			es = acdbOpenObject(pEnt2, idEnt2, AcDb::kForWrite);
			if (es != Acad::eOk) {
				if (pEnt1 != NULL)
					pEnt1->close();
				j++;
				continue;
			}
		}				

		// 読み込みでオープン状態のエンティティを比較する。
		if (pEnt1 == NULL) {				
			CompEntities(NULL, pEnt2, iIdx, rce);
			//iIdx++;
			j++;
		}
		else if (pEnt2 == NULL) {
			CompEntities(pEnt1, NULL, iIdx, rce);
			//iIdx++;
			i++;
		}
		else {
			AcDbHandle hdlEnt1, hdlEnt2;
						
			pEnt1->getAcDbHandle(hdlEnt1);
			pEnt2->getAcDbHandle(hdlEnt2);

			TCHAR cBuff1[AC_LEN_HANDLE], cBuff2[AC_LEN_HANDLE];	//2006.07.20						
			pEnt1->getAcDbHandle(hdlEnt1);
			hdlEnt1.getIntoAsciiBuffer(cBuff1);
			
			pEnt2->getAcDbHandle(hdlEnt2);
			hdlEnt2.getIntoAsciiBuffer(cBuff2);
			
			CString strHdl1(cBuff1), strHdl2(cBuff2);
			int iRes;

			iRes = strHdl1.CompareNoCase(strHdl2); 
			if (iRes == 0) {
				CompEntities(pEnt1, pEnt2, iIdx, rce);
				//iIdx++;
				i++;
				j++;
			}
			else if (iRes < 0) {
				CompEntities(pEnt1, NULL, iIdx, rce);										
				//iIdx++;
				i++;
			}
			else {
				CompEntities(NULL, pEnt2, iIdx, rce);										
				//iIdx++;
				j++;
			}			
		}

		if (pEnt1 != NULL)
			pEnt1->close();

		if (pEnt2 != NULL)
			pEnt2->close();			

		if (i >= iMax1 && j >= iMax2)
			break;
	}

	return true;
}

// 読み込みでオープン状態のエンティティを比較し、結果を返す。
// どちらかのエンティティがない場合はNULLを指定する。
void ACDocManager::CompEntities(AcDbEntity *pEnt1, AcDbEntity *pEnt2, int &iIdx, ResultCompEntity &rce)
{
	if (pEnt1 != NULL && pEnt2 == NULL) {		
		RCESetValue1(iIdx, rce, pEnt1);
		RCESetValue2(iIdx, rce, pEnt2);
		rce.SetResult(iIdx, ResultCompEntity::ONLY1, ResultCompEntity::ONLY1);
		iIdx++;
	}
	else if (pEnt1 == NULL && pEnt2 != NULL) {
		RCESetValue1(iIdx, rce, pEnt1);
		RCESetValue2(iIdx, rce, pEnt2);		
		rce.SetResult(iIdx, ResultCompEntity::ONLY2, ResultCompEntity::ONLY2);
		iIdx++;
	}		
	else if (pEnt1 != NULL && pEnt2 != NULL) {		
		ACCompEntitiesGeom compEntGeom;
		ResultCompEntity::RCE_TYPE_RESULT rceResGeom, rceResAll;
		CString strVal1, strVal2;

		// [ADD:2005/06/14] 範囲比較モードのときは、比較基点のずれをセットする。
		if (m_bRangeCompMode) {
			compEntGeom.SetBasePointGap(m_vec3Gap);
		}

		bool bEqualGeom = compEntGeom.CompareEntityGeoms(pEnt1, pEnt2, m_bRangeCompMode);		
		bool bEqualGeneralAttr = compEntGeom.IsEqualGeneralAttrs(pEnt1, pEnt2);		
		
		// 結果が同じであった場合は書き込まない。
		if (bEqualGeom)
			rceResGeom = ResultCompEntity::EQUAL;
		else
			rceResGeom = ResultCompEntity::NOTEQUAL;

		if (!bEqualGeneralAttr || !bEqualGeom) {
			rceResAll = ResultCompEntity::NOTEQUAL;

			RCESetValue1(iIdx, rce, pEnt1);
			RCESetValue2(iIdx, rce, pEnt2);
			rce.SetResult(iIdx, rceResAll, rceResGeom);
			iIdx++;
		}
		

	}	
	
}

// ###よく確認
// 指定したパスの図面の全ての図形要素のIDを得る。
bool ACDocManager::GetDwgAllEntityIds(const AcDbObjectId &idBlkTbl, CMap<int, int, AcDbObjectId, AcDbObjectId> &idmapRet)
{
	AcApDocManager *pDocMng = acDocManager;	
	Acad::ErrorStatus es;	
	int iIdx = -1;
	bool bRes = false;
	//AcDbDatabase *pDb = NULL; 

	AcApDocumentIterator *pDocItr = pDocMng->newAcApDocumentIterator(); 			

	// 現在開かれているドキュメントを走査する。
	for (; !pDocItr->done() && !bRes; pDocItr->step()) {
		AcApDocument *pDoc = pDocItr->document();
		//CString strDwgPath = pDoc->fileName();				
		AcDbDatabase *pDb = NULL; 

		pDb = pDoc->database();
		if (pDb == NULL)
			break; 
				
		if (pDb->blockTableId() == idBlkTbl) {
		//if (strDwgPath.CompareNoCase(lpctDwgPath) == 0) {							
			
			AcDbBlockTable *pBlkTable;
			es = pDb->getBlockTable(pBlkTable, AcDb::kForRead);
			if (es != Acad::eOk) 
				break;
			
			// コマンド使用中である場合は終了する。
			if (IsCommandRunning(pDb))
				break;
					
			// モデル空間に切り替えられなかったときは終了する。
			if (!ChangeToModelSpace(pDb))
				break;

			bRes = true;

			AcDbBlockTableIterator *pBlkItr;					
			
			pBlkTable->newIterator(pBlkItr); 
			for (pBlkItr->start(); !pBlkItr->done(); pBlkItr->step()) {
				AcDbBlockTableRecord *pBlkRec;				

				es = pBlkItr->getRecord(pBlkRec, AcDb::kForRead);						
				if (es != Acad::eOk)
					continue;

				if (pBlkRec->isLayout()) {			
					AcDbBlockTableRecordIterator *pBlkRecItr;
					bool bFirstVp = true;

					pBlkRec->newIterator(pBlkRecItr);
					for (pBlkRecItr->start(); !pBlkRecItr->done(); pBlkRecItr->step()) {												
						AcDbEntity *pEnt;

						es = pBlkRecItr->getEntity(pEnt, AcDb::kForRead);
						if (es == Acad::eOk) {														
							
							// ペーパー空間の最初のビューポートは除く???
							if (pEnt->isA()->isEqualTo(AcDbViewport::desc()) == Adesk::kTrue && bFirstVp) {
								bFirstVp = false;
							}
							else {	
								iIdx++;	
								idmapRet[iIdx] = pEnt->objectId();								
							}
							
							// ブロック参照の場合は、サブエンティティ(Attribute)も調べる。
							AcDbBlockReference *pBlockRef = AcDbBlockReference::cast(pEnt);														
							if (pBlockRef != NULL) {
								AcDbObjectIterator *pItrAttr = pBlockRef->attributeIterator();
								AcDbObjectId idAttr;

								for (pItrAttr->start(); !pItrAttr->done(); pItrAttr->step()) {
									AcDbObjectId idAttr;

									idAttr = pItrAttr->objectId();
									if (idAttr != AcDbObjectId::kNull) {
										iIdx++;	
										idmapRet[iIdx] = idAttr;	
									}
								}							
								delete pItrAttr;
							}

							pEnt->close();
						}						
					}
					delete pBlkRecItr;							
				}
				pBlkRec->close();
			}				

			delete pBlkItr;			
			pBlkTable->close();		
			//return true;
		}
	}
	delete pDocItr;
	
	return bRes;
}


// 指定した図面の全ての図形要素のIDを得る。
bool ACDocManager::GetDwgAllEntityIds(AcApDocument *pDoc, CMap<int, int, AcDbObjectId, AcDbObjectId> &idmapRet)
{
	AcApDocManager *pDocMng = acDocManager;	
	Acad::ErrorStatus es;	
	int iIdx = -1;

	// 指定されたドキュメントを探す。					
	AcDbDatabase *pDb = NULL;
	pDb = pDoc->database();
	if (pDb == NULL)
		return false;

	AcDbBlockTable *pBlkTable;
	es = pDb->getBlockTable(pBlkTable, AcDb::kForRead);
	if (es != Acad::eOk) 
		return false;

	AcDbBlockTableIterator *pBlkItr;					
	
	pBlkTable->newIterator(pBlkItr); 
	for (pBlkItr->start(); !pBlkItr->done(); pBlkItr->step()) {
		AcDbBlockTableRecord *pBlkRec;				

		es = pBlkItr->getRecord(pBlkRec, AcDb::kForRead);						
		if (es != Acad::eOk)
			continue;

		if (pBlkRec->isLayout()) {			
			AcDbBlockTableRecordIterator *pBlkRecItr;

			pBlkRec->newIterator(pBlkRecItr);
			for (pBlkRecItr->start(); !pBlkRecItr->done(); pBlkRecItr->step()) {												
				AcDbObjectId idEnt;
										
				es = pBlkRecItr->getEntityId(idEnt);
				if (es == Acad::eOk) {
					iIdx++;	
					idmapRet[iIdx] = idEnt;							
				}													
			}
			delete pBlkRecItr;							
		}
		pBlkRec->close();
	}				

	delete pBlkItr;			
	pBlkTable->close();										

	return true;
}

// 指定したIDの図形をハイライトする。指定された図形がない場合も考慮する。
// 対象は一つの図面のみ？ 空間が違うときは無効
bool ACDocManager::HighlightEntities(const CMap<int, int, AcDbObjectId, AcDbObjectId> &idmapEnt, bool bOn)
{
	Acad::ErrorStatus es;
	int iCount  = idmapEnt.GetCount();
	bool bExistValidEnt = false;
	bool bChangeSpace   = false;	

	for (int i = 0; i < iCount; i++) {
		AcDbObjectId idEnt;
		AcDbEntity   *pEnt;

		idmapEnt.Lookup(i, idEnt);

		es = acdbOpenObject(pEnt, idEnt, AcDb::kForRead);
		if (es == Acad::eOk) {			
			//// 最初の図形の図面をアクティブにする。	
			//if (!bExistValidEnt) {				
			bExistValidEnt = true;			
			//	AcApDocument *pDoc = acDocManager->document(pEnt->database());				
			//	acDocManager->lockDocument(pDoc);
			//	acDocManager->activateDocument(pDoc);
			//	acDocManager->unlockDocument(pDoc);
			//}
			
			//if (!bChangeSpace) {
			//	bChangeSpace = true;
			//	// エンティティが属する空間へ切り替える。
			//	ChangeSpace(pEnt);
			//}
			
			if (bOn) {	 
				//pEnt->draw();
				pEnt->highlight(); //kNullSubent, true);
			}
			else
				pEnt->unhighlight();
			
			pEnt->close();
		}					
	}

	return bExistValidEnt;
}

// 指定されたオブジェクトIDの配列をオブジェクトハンドル順にソートする。
void ACDocManager::GetEntityHandles(
CMap<int, int, AcDbObjectId, AcDbObjectId> &idmapSort,
CMap<int, int, CString, CString> &strmapRet)
{
	Acad::ErrorStatus es;	
	int iAdd = 0;

	strmapRet.InitHashTable(idmapSort.GetCount());
	
	for (int i = 0; i < idmapSort.GetCount(); i++) {
		AcDbEntity *pEnt;		
		AcDbObjectId idEnt;

		idmapSort.Lookup(i, idEnt);
		es = acdbOpenObject(pEnt, idEnt, AcDb::kForRead);
		if (es == Acad::eOk) {
			AcDbHandle hdlEnt;
			TCHAR cBuff[AC_LEN_HANDLE];	//2006.07.20					

			pEnt->getAcDbHandle(hdlEnt);
			hdlEnt.getIntoAsciiBuffer(cBuff);

			CString strHdl(cBuff);

			strmapRet[iAdd] = strHdl;
			iAdd++;
			
			pEnt->close();
		}
	}
}


// 指定されたオブジェクトIDの配列をオブジェクトハンドル順にソートする。
void ACDocManager::SortEntities(CMap<int, int, AcDbObjectId, AcDbObjectId> &idmapSort)
{
	CMap<int, int, AcDbObjectId, AcDbObjectId> idmapTmp;
	CMap<int, int, CString, CString> strmapHdl;
	CMap<int, int, int, int>		 imapIdx;	
	int i;

	idmapTmp.InitHashTable(idmapSort.GetCount());
	
	// オブジェクトIDの配列の内容をコピーする。
	for (i = 0; i < idmapSort.GetCount(); i++) {
		AcDbObjectId idEnt = AcDbObjectId::kNull;

		idmapSort.Lookup(i, idEnt);
		idmapTmp[i] = idEnt;
	}

	// オブジェクトIDの列より、オブジェクトハンドルの列を得る。
	GetEntityHandles(idmapTmp, strmapHdl);
	
	// ハンドルの配列をソートし、ソート後のインデックス列を得る。
	ACSort sort;
	sort.QSort(strmapHdl, imapIdx);
	
	for (i = 0; i < imapIdx.GetCount(); i++) {
		AcDbObjectId idTmp;

		idmapTmp.Lookup(ACCMap::GetKeyVal(imapIdx, i), idTmp);
		idmapSort[i] = idTmp;			
	}
}

void ACDocManager::RCESetValue1(int iIdx, ResultCompEntity &rce, AcDbEntity *pEnt) {		
	if (pEnt != NULL) {
		TCHAR *pcLayer = NULL;//2006.07.20
		TCHAR *pcLinetype = NULL;//2006.07.20
		TCHAR *pcPlotStyleName = NULL;//2006.07.20

		pcLayer		    = pEnt->layer(),
		pcLinetype      = pEnt->linetype(),
		pcPlotStyleName = pEnt->plotStyleName(),
				
		rce.SetValue1(
			iIdx, pEnt->objectId(), 
			ACConvertName::GetEntityTypeStr(pEnt), // pEnt->isA()->name(), 
			ACConvertName::GetColorStr(pEnt->colorIndex()), 
			pcLayer,
			pcLinetype,
			pcPlotStyleName,
			ACConvertName::GetLineWeightStr(pEnt->lineWeight()),			
			ACEntityInfo::GetHyperLink(pEnt), 
			pEnt->linetypeScale());		

		acutDelString(pcLayer);
		acutDelString(pcLinetype);
		acutDelString(pcPlotStyleName);
	}
	else {
		rce.SetValue1(
			iIdx, AcDbObjectId::kNull, 
			_T(""), 
			_T(""), 
			_T(""),
			_T(""),
			_T(""),
			_T(""),
			_T(""),
			-1);
	}
}

void ACDocManager::RCESetValue2(int iIdx, ResultCompEntity &rce, AcDbEntity *pEnt) {

	if (pEnt != NULL) {		
		TCHAR *pcLayer = NULL;//2006.07.20
		TCHAR *pcLinetype = NULL;//2006.07.20
		TCHAR *pcPlotStyleName = NULL;//2006.07.20

		pcLayer		    = pEnt->layer(),
		pcLinetype      = pEnt->linetype(),
		pcPlotStyleName = pEnt->plotStyleName(),
			
		rce.SetValue2(
			iIdx, pEnt->objectId(), 
			ACConvertName::GetEntityTypeStr(pEnt), //pEnt->isA()->name(), 
			ACConvertName::GetColorStr(pEnt->colorIndex()), 
			pcLayer,
			pcLinetype,
			pcPlotStyleName,
			ACConvertName::GetLineWeightStr(pEnt->lineWeight()),
			ACEntityInfo::GetHyperLink(pEnt), 
			pEnt->linetypeScale());

		acutDelString(pcLayer);
		acutDelString(pcLinetype);
		acutDelString(pcPlotStyleName);
	}
	else {
		rce.SetValue2(
			iIdx, AcDbObjectId::kNull, 
			"", 
			"", 
			"",
			"",
			"",
			"",
			"",
			-1);
	}
}

// 指定したIDの図形の範囲を得る。
bool ACDocManager::GetEntityExtents(const CMap<int, int, AcDbObjectId, AcDbObjectId> &idmapEnt, 
AcGePoint2d &pt2RetLB, AcGePoint2d &pt2RetRT)
{
	//Acad::ErrorStatus es;
	AcGePoint3d pt3Min, pt3Max;
	int iCount   = idmapEnt.GetCount();		
	bool bGetExt = false;

	for (int i = 0; i < iCount; i++) {
		AcDbObjectId idEnt;
		//AcDbEntity  *pEnt;
		AcDbExtents  extEnt;

		idmapEnt.Lookup(i, idEnt);
		

		if (!GetGeomExtents(idEnt, extEnt))
			continue;
		
		if (!bGetExt) {
			bGetExt = true;				
			pt3Min = extEnt.minPoint();
			pt3Max = extEnt.maxPoint();										
		}
		else {										
			for (int j = 0; j < 3; j++) {
				if (extEnt.minPoint()[j] < pt3Min[j])
					pt3Min[j] = extEnt.minPoint()[j];

				if (extEnt.maxPoint()[j] > pt3Max[j])
					pt3Max[j] = extEnt.maxPoint()[j];
			}										
		}		
		
		/*
		es = acdbOpenObject(pEnt, idEnt, AcDb::kForRead);
		if (es == Acad::eOk) {
			AcDbExtents extEnt;
			
			es = pEnt->getGeomExtents(extEnt);
			if (es == Acad::eOk) {
				if (!bGetExt) {
					bGetExt = true;				
					pt3Min = extEnt.minPoint();
					pt3Max = extEnt.maxPoint();										
				}
				else {										
					for (int j = 0; j < 3; j++) {
						if (extEnt.minPoint()[j] < pt3Min[j])
							pt3Min[j] = extEnt.minPoint()[j];

						if (extEnt.maxPoint()[j] > pt3Max[j])
							pt3Max[j] = extEnt.maxPoint()[j];
					}										
				}												
			}			
			pEnt->close();
		}					
		*/
	}

	//extRet.set(pt3Min, pt3Max);
	pt2RetLB.set(pt3Min[0], pt3Min[1]);
	pt2RetRT.set(pt3Max[0], pt3Max[1]);

	return bGetExt;		
}	


bool ACDocManager::GetGsView(AcGsView*& pView, int& iVportNum)
{
	/*
    struct resbuf rb;
    int rt = acedGetVar(_T("CVPORT"), &rb);
    if(rt != RTNORM)
    {
        //acutPrintf(_T("\nError acquiring sysvar \"CVPORT\" value."));
        return false;
    }	
    iVportNum = rb.resval.rint;
	*/

    pView = acgsGetGsView(iVportNum, true);
    if(!pView)
    {
        //acutPrintf("\nError obtaining AcGsView object.");
        return false;
    }
    return true;
}

// 指定した範囲を拡張する。
// LBとRTの値が逆転している場合は修正する。
void ACDocManager::Extents(AcGePoint2d &pt2LB, AcGePoint2d &pt2RT)
{
	double dTmp;
	double dExtent;

	// Left BottomとRight Topが逆転しているときは終了する。
	if (pt2RT[0] - pt2LB[0] < 0) {
		dTmp = pt2LB[0];
		pt2LB[0] = pt2RT[0];
		pt2RT[0] = dTmp;
	}

	if (pt2RT[1] - pt2LB[1] < 0) {
		dTmp = pt2LB[1];
		pt2LB[1] = pt2RT[1];
		pt2RT[1] = dTmp;
	}

	// 範囲を拡張する。X
	dTmp = pt2RT[0] - pt2LB[0];

	// LBとRTがほとんど同じ点の場合は最小範囲を設定する
	//if (pt2RT[0] - pt2LB[0] < ACDM_EXTENTS_MIN) 
	//	dExtent = ACDM_EXTENTS_MIN;
	//else
	dExtent = dTmp * 0.5 * ACDM_EXTENTS_RATE;
	if (dExtent == 0)
		dExtent = ACDM_EXTENTS_MIN;


	pt2RT[0] = pt2LB[0] + dTmp / 2 + dExtent;
	pt2LB[0] = pt2LB[0] + dTmp / 2 - dExtent;
	


	// 範囲を拡張する。Y
	dTmp = pt2RT[1] - pt2LB[1];

	// LBとRTがほとんど同じ点の場合は最小範囲を設定する
	//if (pt2RT[1] - pt2LB[1] < ACDM_EXTENTS_MIN) 
	//	dExtent = ACDM_EXTENTS_MIN;
	//else
	dExtent = dTmp * 0.5 * ACDM_EXTENTS_RATE;
	if (dExtent == 0)
		dExtent = ACDM_EXTENTS_MIN;

	pt2RT[1] = pt2LB[1] + dTmp / 2 + dExtent;
	pt2LB[1] = pt2LB[1] + dTmp / 2 - dExtent;

}

// 渡された図形ID列の内、同じ空間にある図形のID列を返す。
bool ACDocManager::GetSameSpaceEntities(const CMap<int, int, AcDbObjectId, AcDbObjectId> &idmapEnt,
CMap<int, int, AcDbObjectId, AcDbObjectId> &idmapRetEnt)
{
	AcDbObjectId idSpaceCommon = AcDbObjectId::kNull;
	Acad::ErrorStatus es;
	int iCount = idmapEnt.GetCount(), iAddCount = 0;;
	bool bExistValidEnt = false;	
	
	idmapRetEnt.InitHashTable(iCount);

	for (int i = 0; i < iCount; i++) {
		AcDbObjectId idEnt;
		AcDbEntity   *pEnt;

		idmapEnt.Lookup(i, idEnt);
		
		// IDが示す図形のデータベースが利用できるかどうかを調べる。
		if (!idEnt.isValid())
			continue;

		es = acdbOpenObject(pEnt, idEnt, AcDb::kForRead);
		if (es == Acad::eOk) {				
			// 最初の図形と同じ空間に属する図形IDのみ追加する。	
			AcDbObjectId idSpace;
			bool bAdd = false;

			if (GetSpaceId(pEnt, idSpace)) {
				if (idSpaceCommon == AcDbObjectId::kNull) {
					bExistValidEnt = true;
					idSpaceCommon = idSpace;					
					bAdd = true;
				}					
				else if (idSpaceCommon == idSpace) {
					bAdd = true;
				}

				if (bAdd) {
					idmapRetEnt[iAddCount]	= idEnt; 
					iAddCount++;
				}
			}						
			
			pEnt->close();
		}		
	}
		
	if (idSpaceCommon != AcDbObjectId::kNull)
		return true;
	else
		return false;	
}

// 指定したエンティティが属する空間のIDを返す。
// オーナーが空間でないときは、そのオーナーを辿っていく。
// 失敗した場合はfalseを返す。
bool ACDocManager::GetSpaceId(const AcDbEntity *pEnt, AcDbObjectId &idRetSpace)
{
	AcDbObjectId idTmp; 
	bool bLayout = false;

	idTmp = pEnt->blockId();
	do {
		AcDbBlockTableRecord *pBlkTbl;		
		if (acdbOpenObject(pBlkTbl, idTmp, AcDb::kForRead) == Acad::eOk) {
			bLayout = pBlkTbl->isLayout();			
			pBlkTbl->close();
		}		
		else
			return false;

		if (!bLayout) {
			AcDbEntity *pEnt;
			if (acdbOpenObject(pEnt, idTmp, AcDb::kForRead) == Acad::eOk) {
				idTmp = pEnt->blockId();
				pEnt->close();
			}
			else
				return false;		
		}
	}
	while(!bLayout); 
		
	idRetSpace = idTmp;

	return true;
}

// 指定したデータベースを、指定した空間へ切り替える。
bool ACDocManager::ChangeToSpace(AcDbDatabase *pDb, const AcDbObjectId &idSpace)
{
	//AcDbDatabase *pDb;
	//AcDbObjectId idSpace;		
	//AcDbEntity   *pEnt = NULL;	
	//bool bGetSpaceId;				
	
	// コマンド実行中の場合は終了する。
	if (!acDocManager->document(pDb)->isQuiescent())
		return false;			
	
	// 対象のDBをカレントにしないと、以下の、pDb->currentSpaceId()、
	// pLayoutMng->setCurrentLayoutId(idLayout); が正しく動かない。
	acDocManager->setCurDocument(acDocManager->document(pDb), AcAp::kNone, true);

	// エンティティの属する空間が、現在の空間であるときは終了する。
	if (idSpace == pDb->currentSpaceId())
		return true;	
	
	AcDbBlockTableRecord *pBlkRec;

	if (acdbOpenObject(pBlkRec, idSpace, AcDb::kForRead) != Acad::eOk)
		return false;

	// 図形が属する空間へ切り替える。
	AcDbObjectId idLayout = pBlkRec->getLayoutId();		
	Acad::ErrorStatus es;

	pBlkRec->close();
	
	AcApLayoutManager *pLayoutMng = (AcApLayoutManager *)acdbHostApplicationServices()->layoutManager();					
	AcApDocument *pDoc = acDocManager->document(pDb); //pEnt->database());

	acDocManager->lockDocument(pDoc);
	es = pLayoutMng->setCurrentLayoutId(idLayout);							
	acDocManager->unlockDocument(pDoc);

	if (es == Acad::eOk)
		return true;
	else
		return false;
}

/*
// 指定したエンティティが属する空間へ切り替える。
bool ACDocManager::ChangeSpace(const AcDbObjectId &idEnt)
{
	AcDbDatabase *pDb;
	AcDbEntity   *pEnt = NULL;
	AcDbObjectId idSpace;		
	bool bGetSpaceId;
	
	if (acdbOpenObject(pEnt, idEnt, AcDb::kForRead) != Acad::eOk)
		return false;

	pDb = pEnt->database();	
	bGetSpaceId = GetSpaceId(pEnt, idSpace);
	pEnt->close();
	
	if (!bGetSpaceId)
		return false;

	// コマンド実行中の場合は終了する。
	if (!acDocManager->document(pDb)->isQuiescent())
		return false;			

	// エンティティの属する空間が、現在の空間であるときは終了する。
	if (idSpace == pDb->currentSpaceId())
		return true;	
	
	AcDbBlockTableRecord *pBlkRec;

	if (acdbOpenObject(pBlkRec, idSpace, AcDb::kForRead) != Acad::eOk)
		return false;

	// 図形が属する空間へ切り替える。
	AcDbObjectId idLayout = pBlkRec->getLayoutId();		
	Acad::ErrorStatus es;

	pBlkRec->close();
	
	AcApLayoutManager *pLayoutMng = (AcApLayoutManager *)acdbHostApplicationServices()->layoutManager();					
	AcApDocument *pDoc = acDocManager->document(pDb); //pEnt->database());

	acDocManager->lockDocument(pDoc);
	es = pLayoutMng->setCurrentLayoutId(idLayout);							
	acDocManager->unlockDocument(pDoc);

	if (es == Acad::eOk)
		return true;
	else
		return false;
}


*/


// 指定したID列の最初のエンティティのある空間へ切り替える。その図面をアクティブにする。
// 有効な切り替えられなかった場合と、
bool ACDocManager::ChangeToFirstEntitySpace(const CMap<int, int, AcDbObjectId, AcDbObjectId> &idmapEnt)
{
	Acad::ErrorStatus es;
	int iCount  = idmapEnt.GetCount();
	bool bActivatedDoc = false;
	bool bChangedSpace = false;	

	for (int i = 0; i < iCount && (!(bActivatedDoc && bChangedSpace)); i++) {
		AcDbObjectId idEnt;
		AcDbEntity   *pEnt;

		idmapEnt.Lookup(i, idEnt);

		es = acdbOpenObject(pEnt, idEnt, AcDb::kForRead);
		if (es == Acad::eOk) {
			// 最初の図形の図面をアクティブにする。	
			if (!bActivatedDoc) {												
				AcApDocument *pDoc = acDocManager->document(pEnt->database());				
				//if (acDocManager->setCurDocument(pDoc, AcAp::kNone, true) == Acad::eOk)							     
				acDocManager->setCurDocument(pDoc, AcAp::kNone, true);
				bActivatedDoc = true;
				
				//AcApDocument *pDoc = acDocManager->document(pEnt->database());				
				//acDocManager->lockDocument(pDoc);
				//if (acDocManager->activateDocument(pDoc) == Acad::eOk)
				//	bActivatedDoc = true;
				//acDocManager->unlockDocument(pDoc);
			}

			pEnt->close();						
		}		

		if (!bChangedSpace) {				
			// エンティティが属する空間へ切り替える。
			bChangedSpace = ChangeToEntitySpace(idEnt);
		}			
	}

	return (bActivatedDoc && bChangedSpace);
}

// IDで指定したエンティティの範囲を得る。
// XlineとRayはそれぞれの位置と方向より得る。
bool ACDocManager::GetGeomExtents(AcDbObjectId idEnt, AcDbExtents &extRet) {
	AcDbExtents extEnt;
	AcDbEntity *pEnt;
	Acad::ErrorStatus es = Acad::eInvalidInput;		
	
	if (acdbOpenObject(pEnt, idEnt, AcDb::kForRead) != Acad::eOk)
		return false;
	
	if (pEnt->isA()->isEqualTo(AcDbXline::desc()) == Adesk::kTrue) {
		AcDbXline *pXline = AcDbXline::cast(pEnt);	
		
		if (pXline != NULL) {
			extEnt.set(pXline->basePoint() - pXline->unitDir() * ACDM_INFINITE_ENT_ZOOM_RATE, 
					   pXline->basePoint() + pXline->unitDir() * ACDM_INFINITE_ENT_ZOOM_RATE); 
			es = Acad::eOk;
		}
		
	}
	else if (pEnt->isA()->isEqualTo(AcDbRay::desc()) == Adesk::kTrue) {
		AcDbRay *pRay = AcDbRay::cast(pEnt);	
		
		if (pRay != NULL) {
			extEnt.set(pRay->basePoint() - pRay->unitDir() * ACDM_INFINITE_ENT_ZOOM_RATE, 
					   pRay->basePoint() + pRay->unitDir() * ACDM_INFINITE_ENT_ZOOM_RATE); 
			es = Acad::eOk;
		}
	}
	else {	
		es = pEnt->getGeomExtents(extEnt);
	}

	pEnt->close();

	if (es == Acad::eOk) {
		extRet = extEnt;	
		return true;
	}
	else
		return false;
		
	
}

// オートメーションを使ってズームを実行する。
bool ACDocManager::AutomationCommand(LPCTSTR strCmd)	
{
#ifdef ACADTLB
	try
    {
		IDispatch* pDisp = acedGetAcadWinApp()->GetIDispatch(FALSE);
        AutoCAD::IAcadApplicationPtr pApp;
		_com_util::CheckError(pDisp->QueryInterface(__uuidof(AutoCAD::IAcadApplication),(void**)&pApp));
        AutoCAD::IAcadDocumentPtr pDoc;
        _com_util::CheckError(pApp->get_ActiveDocument(&pDoc));

		//CString strCmd;

		//strCmd.Format("zoom %.4f,%.4f %.4f,%.4f ", pt2LBUcs[0], pt2LBUcs[1], pt2RTUcs[0], pt2RTUcs[1]);
		// オートメーションにコマンドを送る。
		_com_util::CheckError(pDoc->SendCommand(_bstr_t(strCmd)));		
		return true;
    }
    catch(const _com_error e)
    {
        if (e.ErrorMessage()!=NULL)
#ifdef UNICODE
            wprintf(_T("Error: %s"),e.ErrorMessage());
#else
            printf("Error: %s",e.ErrorMessage());
#endif
		return false;
    }
#else
	return true;
#endif		
}


// オートメーションを使ってズームを実行する。
bool ACDocManager::AutomationZoom(const AcGePoint2d &pt2LB, const AcGePoint2d &pt2RT)	
{
#ifdef ACADTLB
	AcGePoint2d pt2LBUcs, pt2RTUcs;

	WcsToUcs2d(pt2LB, pt2LBUcs);
	WcsToUcs2d(pt2RT, pt2RTUcs);


	try
    {
		IDispatch* pDisp = acedGetAcadWinApp()->GetIDispatch(FALSE);
        AutoCAD::IAcadApplicationPtr pApp;
		_com_util::CheckError(pDisp->QueryInterface(__uuidof(AutoCAD::IAcadApplication),(void**)&pApp));
        AutoCAD::IAcadDocumentPtr pDoc;
        _com_util::CheckError(pApp->get_ActiveDocument(&pDoc));

		CString strCmd;

		strCmd.Format(_T("zoom %.4f,%.4f %.4f,%.4f "), pt2LBUcs[0], pt2LBUcs[1], pt2RTUcs[0], pt2RTUcs[1]);
		// Zoom範囲
		_com_util::CheckError(pDoc->SendCommand(_bstr_t((LPCTSTR)strCmd)));		
		
		//ms_bUserZoom = true;

		// リアルタイムZoom
		//_com_util::CheckError(pDoc->SendCommand(_bstr_t("zoom  ")));

		return true;
    }
    catch(const _com_error e)
    {
        if (e.ErrorMessage()!=NULL)
#ifdef UNICODE
            wprintf(_T("Error: %s"),e.ErrorMessage());
#else
            printf("Error: %s",e.ErrorMessage());
#endif
		return false;
    }
#else
	return true;
#endif
}

bool ACDocManager::WcsToUcs2d(const AcGePoint2d &pt2Wcs, AcGePoint2d &pt2RetUcs)
{
	ads_point aptWcs, aptUcs;
	bool      bRes;

	aptWcs[0] = pt2Wcs[0];
	aptWcs[1] = pt2Wcs[1];
	bRes = acdbWcs2Ucs(aptWcs, aptUcs, false);
	
	pt2RetUcs.set(aptUcs[0], aptUcs[1]);

	return bRes;
}

// 指定したデータベースを、指定したエンティティの属する空間へ切り替える。
bool ACDocManager::ChangeToEntitySpace(const AcDbObjectId &idEnt) 
{
	AcDbDatabase *pDb;
	AcDbEntity   *pEnt = NULL;
	AcDbObjectId idSpace;		
	bool bGetSpaceId;
	
	if (acdbOpenObject(pEnt, idEnt, AcDb::kForRead) != Acad::eOk)
		return false;

	pDb = pEnt->database();	
	bGetSpaceId = GetSpaceId(pEnt, idSpace);
	pEnt->close();			
	
	return ChangeToSpace(pDb, idSpace);
}

// 指定したデータベースを、モデル空間へ切り替える。
bool ACDocManager::ChangeToModelSpace(AcDbDatabase *pDb)
{
	AcDbObjectId idModelSpace;

	// コマンド実行中の場合は終了する。
	//if (!acDocManager->document(pDb)->isQuiescent())
	//	return false;			

	// モデル空間のIDを得る。
	if (!GetModelSpaceId(pDb, idModelSpace))
		return false;	
	
	return ChangeToSpace(pDb, idModelSpace);	
}

// 指定したデータベースのモデル空間ブロックのIDを得る。
bool ACDocManager::GetModelSpaceId(AcDbDatabase *pDb, AcDbObjectId &idRet) 
{
	AcDbBlockTable       *pBlkTbl;
    //AcDbBlockTableRecord *pBlkRec;
	bool bRes = true;	

    if (pDb->getSymbolTable(pBlkTbl, AcDb::kForRead) != Acad::eOk)
		return false;

    if (pBlkTbl->getAt(ACDB_MODEL_SPACE, idRet, AcDb::kForRead) != Acad::eOk)
		bRes = false;
    pBlkTbl->close();
	
	if (!bRes)
		return false;

	//idRet = pBlkRec->objectId();
	//pBlkRec->close();

	return true;
}


// 指定したデータベースで現在コマンドが使用中であるかどうかを調べる。
bool ACDocManager::IsCommandRunning(AcDbDatabase *pDb) 
{	
	return (!acDocManager->document(pDb)->isQuiescent());
}

// 指定したIDのブロックテーブルを持つドキュメント(データベース)がコマンド使用中であるかどうか調べる。
ACRetType::ACRETTYPE ACDocManager::CheckDwg(const AcDbObjectId &idBlkTbl)
{		
	AcApDocumentIterator *pDocItr = acDocManager->newAcApDocumentIterator(); 	
	ACRetType::ACRETTYPE acRet = ACRetType::rInvalidDwg;
	int iDocCount = acDocManager->documentCount();
	int i = 0;
	
	// 図面が閉じられている場合は、ブロックテーブルIDが無効になる。
	if (!idBlkTbl.isValid())
		return ACRetType::rInvalidDwg;		
	
	// 現在開かれているドキュメントを走査する。
	for (; !pDocItr->done(); pDocItr->step()) {
		AcApDocument *pDoc = pDocItr->document();

		if (pDoc->database()->blockTableId() != idBlkTbl)
			continue;
				
		//CString strTestName = pDoc->docTitle();		
		//acutPrintf("\ntype: %s", strTestName);

		// これが存在すると、呼び出し元でメッセージボックスor throwを使う場合に落ちるらしい。
		//MessageBox(NULL, strTestName, "test", MB_OK);

		acRet = ACRetType::rOk;

		// コマンドが使用中であるかどうか調べる。
		if (!pDoc->isQuiescent()) 
			acRet = ACRetType::rCommandRunning;
			
		break;
	}
	delete pDocItr;

	return acRet;
}

// カレント図面を保持する。
void ACDocManager::SetCurDoc()
{
	m_pDocCur = acDocManager->mdiActiveDocument();

	//CString strDocName = m_pDocCur->fileName(); //### 
}

// 元のカレント図面をアクティブにする。
void ACDocManager::ReturnCurDoc()
{
	//CString strDocName1 = m_pDocCur->fileName(); //### 
	if (m_pDocCur != NULL)
		acDocManager->activateDocument(m_pDocCur);

	//CString strDocName = m_pDocCur->fileName(); //### 
	m_pDocCur = NULL;
}

// 新しい図面を作成し、アクティブにする。
bool ACDocManager::CreateNewDwg()
{	
	AcApDocument *pDocNew;	
	AcApDocumentIterator *pDocItr;

	// 新しい図面を開く
	acDocManager->appContextNewDocument(_T(""));	//2006.07.20		

	// ロックを掛ける。
	pDocItr = acDocManager->newAcApDocumentIterator();
	for (; !pDocItr->done(); pDocItr->step()) {				
		pDocNew = pDocItr->document();
	}
	delete pDocItr;

	//pDocNew = acDocManager->mdiActiveDocument();	
	acDocManager->lockDocument(pDocNew);
	acDocManager->activateDocument(pDocNew);

	return true;
}

// CreateNewDwg時に行った図面のロックを解除する。
void ACDocManager::UnlockCurDoc()
{
	acDocManager->unlockDocument(m_pDocCur);
}


// 現在アクティブな図面に比較結果を色で表現した図形を描く。
bool ACDocManager::DrawResultDwg(AcDbObjectId idNewDwgBlockTable, AcDbObjectId idOldDwgBlockTable, 
	ResultCompEntity &rce, CMap<int, int, AcDbObjectId, AcDbObjectId> &idMapNew)
{							
	//return false; //####

	// アクティブな図面を得る。
	AcApDocument *pDocAct = acDocManager->mdiActiveDocument(); 	
	
	// 新図面のモデル空間のIDを得る。
	AcDbObjectId idModelNew;

	//[DEL: 2005.06.15]
	//CMap<int, int, AcDbObjectId, AcDbObjectId> idMapNew; #####
	
	GetModelSpaceId(idNewDwgBlockTable.database(), idModelNew); 			
	
	//[DEL: 2005.06.15]
	// 図面の全ての図形のIDを得る。
	//GetDwgAllEntityIds(idNewDwgBlockTable, idMapNew);	##### 

	acDocManager->activateDocument(pDocAct);
	
	//SetMlineStyle(pDocAct->database());	

	// 取得した図形IDのうち、モデル空間に存在するものを配列にする。
	AcDbObjectIdArray idaryModelNew;
	int iAddIdx = -1;		
		
	IdFilterByOwner(idMapNew, idModelNew, idaryModelNew);
	
	AcDbObjectId   idModelAct;	
	GetModelSpaceId(pDocAct->database(), idModelAct); 		

	// 合成図面の目印用XDATAをモデルスペースへ設定する
	if( !SetResultXData( idModelAct ) ) {
		return false;
	}

	// 現在アクティブな図面に新図面の全図形を挿入する。
	// ブロックの属性を変更されたケースで、旧図面を元にすると、属性の変更が表現できないという問題があるので、
	// 新図面を元にすることにした。
	AcDbIdMapping idMapModelNew;	

	if (pDocAct->database()->wblockCloneObjects(
		idaryModelNew, idModelAct, idMapModelNew, AcDb::kDrcIgnore) != Acad::eOk)
		return false;					
	
	// コピーした外部参照をバインドする。
	BindXRef(idMapModelNew);


	// 結果セットから、削除、変更、追加されたものだけを取り出す。
	CMap<int, int, AcDbObjectId, AcDbObjectId> idmap1;
	CMap<int, int, AcDbObjectId, AcDbObjectId> idmap2;
	CMap<int, int, ResultCompEntity::RCE_TYPE_RESULT, ResultCompEntity::RCE_TYPE_RESULT> resmap;
	int iAddMapIdx = -1;
	idmap1.InitHashTable(rce.GetCount());
	idmap2.InitHashTable(rce.GetCount());
	resmap.InitHashTable(rce.GetCount());
	for (int j =0 ; j < rce.GetCount(); j++) {
		ResultCompEntity::RCE_TYPE_RESULT rceres;

		rce.GetResultMap(ResultCompEntity::COMPALL).Lookup(j, rceres);
		if (rceres != ResultCompEntity::EQUAL && rceres != ResultCompEntity::INVALID) {
			AcDbObjectId id1, id2;
			
			rce.GetObjectIdMap(ResultCompEntity::FIRST).Lookup(j, id1);
			rce.GetObjectIdMap(ResultCompEntity::SECOND).Lookup(j, id2);
			
			iAddMapIdx++;
			idmap1.SetAt(iAddMapIdx, id1);
			idmap2.SetAt(iAddMapIdx, id2);
			resmap.SetAt(iAddMapIdx, rceres);			
		}
	}

	//return true; //####


	// 旧図面のモデル空間のIDを得る。
	AcDbObjectId idModelOld;
	GetModelSpaceId(idOldDwgBlockTable.database(), idModelOld); 

	// 旧図面で変更された図形の内、モデル空間に属するものだけをアクティブな図面にコピーする。
	AcDbObjectIdArray idaryModelOld;
	IdFilterByOwner(idmap1, idModelOld, idaryModelOld);
	
	AcDbIdMapping idMapModelOld;
	if (pDocAct->database()->wblockCloneObjects(
		idaryModelOld, idModelAct, idMapModelOld, AcDb::kDrcIgnore) != Acad::eOk)
		return false;
	
	


	// [ADD:2005.06.14] 範囲比較モードのときは、旧図面の図形を、比較範囲の基点のずれの分だけ移動する。
	if (m_bRangeCompMode) 
		MoveGap(idMapModelOld);	


	

	// コピーした外部参照をバインドする。
	BindXRef(idMapModelOld);

	// 全てのレイヤーの色を白にする。
	AllLayerDisable(pDocAct->database(), true, true, false);
	
	// 2005.03.15 新規、修正、削除図形用のレイヤーを作成する。
	//ACResultLayers resLayers;
	//CreateResultLayers(pDocAct->database(), resLayers);	
	


	// クローンした図形を全て白くする。	
	ClonedColorWhite(idMapModelNew);
	ClonedColorWhite(idMapModelOld);		

	// 全ての寸法スタイルの色をBYBLOCKにする。
	SetDimStyle(pDocAct->database(), ACDM_COLOR_BYBLOCK);
	// 全てのテキストスタイルのビッグフォントファイルを設定する。
	SetAllTextStyle(pDocAct->database());		

	ACProfileManager	profile;
	double dArrowMinLen =  profile.GetUserModTextArrowMinLength();

	// コピーしたIDのペアを一つづつ調べる。
	//   変更がない図形: 白:1,2
	//   削除された図形: 暗い青:1
	//   変更前の図形  : 削除する。:1
	//   変更後の図形  : 赤:2
	//   追加された図形: 緑:2
	for (int k = 0; k < idmap1.GetCount(); k++)	{
		ResultCompEntity::RCE_TYPE_RESULT rceTmp;
		AcDbObjectId idEnt1, idEnt2;

		resmap.Lookup(k, rceTmp);

		// 比較結果が変更の場合、旧図面の図形に対応するクローンを削除し、新図面の図形に対応するクローンの色を赤にする。
		if (rceTmp == ResultCompEntity::NOTEQUAL) {
			BOOL	bIsText = FALSE;
			AcDbObjectId idRet1;

			AcGePoint3d	pntBeforeModText;

			idmap1.Lookup(k, idEnt1);

			if (idEnt1.isValid() && SearchClonedPairId(idMapModelOld, idEnt1, idRet1)) {
				AcDbEntity *pEnt;	
				if (acdbOpenObject(pEnt, idRet1, AcDb::kForWrite) == Acad::eOk) {
					// ハッチングは関連付けを切ってから削除する。（このようにしないと、図面作成後に落ちることがある）
					if (pEnt->isA()->isEqualTo(AcDbHatch::desc()) == Adesk::kTrue) {
						AcDbHatch *pHatch;
						pHatch = AcDbHatch::cast(pEnt);
						pHatch->setAssociative(false);						
					}

					// テキストの場合はレイヤーを変える
					// テキスト以外は削除する
					if( pEnt->isA()->isEqualTo(AcDbText::desc()) == Adesk::kTrue ||
						pEnt->isA()->isEqualTo(AcDbMText::desc()) == Adesk::kTrue ) {
						CreateBeforeModifyLayers(pDocAct->database());
						pEnt->setLayer(ACDM_PREVMODIFY_LAYER);
						pEnt->setColorIndex( ACDM_PREVMODIFY_COLOR );

						if( pEnt->isA()->isEqualTo(AcDbText::desc()) == Adesk::kTrue ) {
							pntBeforeModText = AcDbText::cast(pEnt)->position();
						} else {
							pntBeforeModText = AcDbMText::cast(pEnt)->location();
						}

						bIsText = TRUE;
					} else {
						pEnt->erase();	
					}

					pEnt->close();
				}			
			}

			AcDbObjectId idRet2;

			idmap2.Lookup(k, idEnt2);

			if (idEnt2.isValid() && SearchClonedPairId(idMapModelNew, idEnt2, idRet2)) {
				SetEntityColor(idRet2, ACDM_COLOR_NOT_EQUAL);							
			}

			// テキストの場合、元から先へ線を引く
			if( bIsText ) {
				AcDbBlockTableRecordPointer	pTbl( pDocAct->database()->currentSpaceId(), AcDb::kForWrite );
				AcDbEntityPointer	pEnt( idEnt2, AcDb::kForRead );
				AcGePoint3d	pntAfterModText;
				double	dHeight;

				if( pEnt->isA()->isEqualTo(AcDbText::desc()) == Adesk::kTrue ) {
					pntAfterModText = AcDbText::cast(pEnt)->position();
					dHeight = AcDbText::cast(pEnt)->height();
				} else {
					pntAfterModText = AcDbMText::cast(pEnt)->location();
					dHeight = AcDbMText::cast(pEnt)->height();
				}

				if( (dHeight * dArrowMinLen) <= pntBeforeModText.distanceTo(pntAfterModText) ) {
					AcDbObjectPointer<AcDbLeader>	pLeader;
					pLeader.create();
					pLeader->setDatabaseDefaults( pDocAct->database() );
					pLeader->appendVertex( pntAfterModText );
					pLeader->appendVertex( pntBeforeModText );
					pLeader->setColorIndex( ACDM_PREVMODIFY_COLOR );
					pLeader->setLayer( ACDM_PREVMODIFY_LAYER );
					pTbl->appendAcDbEntity( pLeader );
				}
			}
		}
		// 旧図面にしか存在しない図形は青色にする。
		else if (rceTmp == ResultCompEntity::ONLY1) {
			AcDbObjectId idRet;

			idmap1.Lookup(k, idEnt1);

			if (idEnt1.isValid() && SearchClonedPairId(idMapModelOld, idEnt1, idRet)) 
				SetEntityColor(idRet, ACDM_COLOR_DELETE);						
		}
		// 新図面にしか存在しない図形は緑色にする。
		else if (rceTmp == ResultCompEntity::ONLY2) {
			AcDbObjectId idRet;

			idmap2.Lookup(k, idEnt2);

			if (idEnt2.isValid() && SearchClonedPairId(idMapModelNew, idEnt2, idRet)) 
				SetEntityColor(idRet, ACDM_COLOR_NEW);
		}

	}

	//acDocManager->activateDocument(pDocAct); //####
	return true;
}


/*
// 現在アクティブな図面に比較結果を色で表現した図形を描く。
bool ACDocManager::DrawResultDwg(AcDbObjectId idNewDwgBlockTable, AcDbObjectId idOldDwgBlockTable, 
	ResultCompEntity &rce)
{	
	// 新旧図面のレイアウトIDの配列を得る。
	// それぞれの配列を比較し、両方のレイアウトのハンドルを足し合わせたIDの配列を作成する。
	AcDbObjectIdArray idaryOldLayout, idaryNewLayout, idaryAppend;

	GetLayoutBlkRecObjectIdArray(idOldDwgBlockTable.database(), idaryOldLayout);
	GetLayoutBlkRecObjectIdArray(idNewDwgBlockTable.database(), idaryNewLayout);
	
	for (int i = 0; i < idaryOldLayout.logicalLength(); i++) {
		bool bHandleExist = false;
		for (int j = 0; j < idaryNewLayout.logicalLength(); j++) {
			if (idaryOldLayout[i].handle() == idaryNewLayout[j].handle()) {
				bHandleExist = true;
				break;
			}						
		}
		if (!bHandleExist)
			idaryAppend.append(idaryOldLayout[i]);
	}

	idaryNewLayout.append(idaryAppend);
	

	// アクティブな図面を得る。
	AcApDocument *pDocAct = acDocManager->mdiActiveDocument(); 	

	// アクティブな図面に、先の操作で得たレイアウト列のうち、ハンドルが存在しないものを作成する。
	// レイアウトID列と、新規図面のIDのマップを作成する。
	CArray<AcDbIdPair, AcDbIdPair> idparyLayout;
	CreateLayout(pDocAct->database(), idaryNewLayout, idparyLayout);
		

	return false; //####	








	
	
	// 新図面のモデル空間のIDを得る。
	AcDbObjectId idModelNew;
	CMap<int, int, AcDbObjectId, AcDbObjectId> idMapNew;
	
	GetModelSpaceId(idNewDwgBlockTable.database(), idModelNew); 			
	
	// 図面の全ての図形のIDを得る。
	GetDwgAllEntityIds(idNewDwgBlockTable, idMapNew);	

	acDocManager->activateDocument(pDocAct);

	// 取得した図形IDを、モデル空間とペーパー空間に分け、それぞれ配列にする。
	AcDbObjectIdArray idaryModelNew;
	int iAddIdx = -1;		
		
	IdFilterByOwner(idMapNew, idModelNew, idaryModelNew);
	
	AcDbObjectId   idModelAct;	
	GetModelSpaceId(pDocAct->database(), idModelAct); 		

	// 現在アクティブな図面に新図面の全図形を挿入する。
	// ブロックの属性を変更されたケースで、旧図面を元にすると、属性の変更が表現できないという問題があるので、
	// 新図面を元にすることにした。
	AcDbIdMapping idMapModelNew;	

	if (pDocAct->database()->wblockCloneObjects(
		idaryModelNew, idModelAct, idMapModelNew, AcDb::kDrcIgnore) != Acad::eOk)
		return false;					
	
	// 結果セットから、削除、変更、追加されたものだけを取り出す。
	CMap<int, int, AcDbObjectId, AcDbObjectId> idmap1;
	CMap<int, int, AcDbObjectId, AcDbObjectId> idmap2;
	CMap<int, int, ResultCompEntity::RCE_TYPE_RESULT, ResultCompEntity::RCE_TYPE_RESULT> resmap;
	int iAddMapIdx = -1;
	idmap1.InitHashTable(rce.GetCount());
	idmap2.InitHashTable(rce.GetCount());
	resmap.InitHashTable(rce.GetCount());
	for (int j =0 ; j < rce.GetCount(); j++) {
		ResultCompEntity::RCE_TYPE_RESULT rceres;

		rce.GetResultMap(ResultCompEntity::COMPALL).Lookup(j, rceres);
		if (rceres != ResultCompEntity::EQUAL && rceres != ResultCompEntity::INVALID) {
			AcDbObjectId id1, id2;
			
			rce.GetObjectIdMap(ResultCompEntity::FIRST).Lookup(j, id1);
			rce.GetObjectIdMap(ResultCompEntity::SECOND).Lookup(j, id2);
			
			iAddMapIdx++;
			idmap1.SetAt(iAddMapIdx, id1);
			idmap2.SetAt(iAddMapIdx, id2);
			resmap.SetAt(iAddMapIdx, rceres);			
		}
	}

	// 旧図面のモデル空間のIDを得る。
	AcDbObjectId idModelOld;
	GetModelSpaceId(idOldDwgBlockTable.database(), idModelOld); 

	AcDbObjectIdArray idaryModelOld;
	IdFilterByOwner(idmap1, idModelOld, idaryModelOld);
	
	AcDbIdMapping idMapModelOld;
	if (pDocAct->database()->wblockCloneObjects(
		idaryModelOld, idModelAct, idMapModelOld, AcDb::kDrcIgnore) != Acad::eOk)
		return false;	
	
	// 全てのレイヤーの色を白にする。
	AllLayerDisable(pDocAct->database(), true, true, false);
			
	// コピーしたIDのペアを一つづつ調べる。
	//   変更がない図形: 白:1,2
	//   削除された図形: 暗い青:1
	//   変更前の図形  : 削除する。:1
	//   変更後の図形  : 赤:2
	//   追加された図形: 緑:2
	ClonedColorWhite(idMapModelNew);
	ClonedColorWhite(idMapModelOld);	
	
	for (int k = 0; k < idmap1.GetCount(); k++)	{
		ResultCompEntity::RCE_TYPE_RESULT rceTmp;
		AcDbObjectId idEnt1, idEnt2;

		resmap.Lookup(k, rceTmp);

		// 比較結果が変更の場合、旧図面の図形に対応するクローンを削除し、新図面の図形に対応するクローンの色を赤にする。
		if (rceTmp == ResultCompEntity::NOTEQUAL) {
			AcDbObjectId idRet1;

			idmap1.Lookup(k, idEnt1);			

			if (idEnt1.isValid() && SearchClonedPairId(idMapModelOld, idEnt1, idRet1)) {
				AcDbEntity *pEnt;	
				if (acdbOpenObject(pEnt, idRet1, AcDb::kForWrite) == Acad::eOk) {
					pEnt->erase();	
					pEnt->close();
				}			
			}

			AcDbObjectId idRet2;

			idmap2.Lookup(k, idEnt2);

			if (idEnt2.isValid() && SearchClonedPairId(idMapModelNew, idEnt2, idRet2)) 
				SetEntityColor(idRet2, ACDM_COLOR_NOT_EQUAL);							
		}
		else if (rceTmp == ResultCompEntity::ONLY1) {
			AcDbObjectId idRet;

			idmap1.Lookup(k, idEnt1);

			if (idEnt1.isValid() && SearchClonedPairId(idMapModelOld, idEnt1, idRet)) 
				SetEntityColor(idRet, ACDM_COLOR_DELETE);						
		}
		else if (rceTmp == ResultCompEntity::ONLY2) {
			AcDbObjectId idRet;

			idmap2.Lookup(k, idEnt2);

			if (idEnt2.isValid() && SearchClonedPairId(idMapModelNew, idEnt2, idRet)) 
				SetEntityColor(idRet, ACDM_COLOR_NEW);
		}

	}
	return true;
}
*/

// pDbのブロックテーブルレコードのIDの配列を得る。
bool ACDocManager::GetBlockTableRecordIdArray(AcDbDatabase *pDb, AcDbObjectIdArray &idaryBlkRec)
{
	AcDbBlockTable *pBlkTbl;
	
	if (pDb->getSymbolTable(pBlkTbl, AcDb::kForRead) != Acad::eOk) 
		return false;
	
	AcDbBlockTableIterator *pBlkItr;		

	pBlkTbl->newIterator(pBlkItr);
	pBlkTbl->close();
	
	int iBlkRecCount = 0, i = -1;	

	for (pBlkItr->start(); !pBlkItr->done(); pBlkItr->step()) {
		iBlkRecCount++;
	}
	
	idaryBlkRec.setLogicalLength(iBlkRecCount);
	for (pBlkItr->start(); !pBlkItr->done(); pBlkItr->step()) {
		AcDbBlockTableRecord *pBlkRec;	
		if (pBlkItr->getRecord(pBlkRec, AcDb::kForRead) == Acad::eOk) {
			i++;
			idaryBlkRec.setAt(i, pBlkRec->objectId());	
			//const char *pcName;
			//pBlkRec->getName(pcName);	
			//OutputDebugString(pcName);
			//OutputDebugString("\n");
			pBlkRec->close();
		}		
	}
	delete pBlkItr;			

	return true;
}

// idMapの図形のうち、オーナーがidOwnerに等しいもののみを配列（idaryRet）にして返す。
void ACDocManager::IdFilterByOwner(CMap<int, int, AcDbObjectId, AcDbObjectId> &idMap, 
const AcDbObjectId &idOwner, AcDbObjectIdArray &idaryRet)
{	
	int iAddIdx = -1;	

	idaryRet.setLogicalLength(idMap.GetCount());
	for (int i = 0; i < idMap.GetCount(); i++) {			
		AcDbEntity   *pEnt;	
		AcDbObjectId idObj;		

		idMap.Lookup(i, idObj);
		
		if (!idObj.isValid()) 
			continue;
		
		if (acdbOpenObject(pEnt, idObj, AcDb::kForRead) == Acad::eOk) {
			///////////S
			//AcDbBlockTableRecord *pBlkRec;
			//bool bOwnerIsLayout = false;
			//if (acdbOpenObject(pBlkRec, pEnt->ownerId(), AcDb::kForRead) == Acad::eOk) {
			//	if (pBlkRec->isLayout())
			//		bOwnerIsLayout = true;
			//	pBlkRec->close();
			//}			
			///////////E

			if (pEnt->ownerId() == idOwner) {   // || bOwnerIsLayout /**/
				iAddIdx++;
				idaryRet.setAt(iAddIdx, idObj);
			}

			pEnt->close();
		}
	}
	idaryRet.setLogicalLength(iAddIdx + 1);		
}

// 指定したDBのペーパー空間タブを全て削除する。XXXXXXXX
bool ACDocManager::DeleteAllTabs(AcDbDatabase *pDb)
{
	AcDbBlockTable *pBlkTbl;

	if (pDb->getSymbolTable(pBlkTbl, AcDb::kForRead) != Acad::eOk) 
		return false;
	
	AcDbBlockTableIterator *pBlkItr;		

	pBlkTbl->newIterator(pBlkItr);
	pBlkTbl->close();
	
	AcDbLayoutManager *pLayoutMng = acdbHostApplicationServices()->layoutManager();							

	// ブロックテーブルの全レコードを調べ、関連付けられたレイアウトを削除する。
	for (pBlkItr->start(); !pBlkItr->done(); pBlkItr->step()) {
		AcDbBlockTableRecord *pBlkRec;

		if (pBlkItr->getRecord(pBlkRec, AcDb::kForRead) != Acad::eOk) 
			continue;
		
		AcDbObjectId idLayout;		
		AcDbLayout   *pLayout;

		idLayout = pBlkRec->getLayoutId();
		pBlkRec->close();

		if (acdbOpenObject(pLayout, idLayout, AcDb::kForRead) != Acad::eOk)	
			continue;
		
		const TCHAR *pcName;//2006.07.20

		pLayout->getLayoutName(pcName);
		pLayoutMng->deleteLayout(pcName);
		pLayout->close();		
	}	
	delete pBlkItr;	
		
	return true;
}

bool ACDocManager::CreateLayout(AcDbDatabase *pDb)
{
	AcDbBlockTable *pBlkTbl;

	if (pDb->getSymbolTable(pBlkTbl, AcDb::kForRead) != Acad::eOk) 
		return false;
	
	AcDbBlockTableIterator *pBlkItr;		

	pBlkTbl->newIterator(pBlkItr);
	pBlkTbl->close();
	
	AcDbLayoutManager *pLayoutMng = acdbHostApplicationServices()->layoutManager();							

	// ブロックテーブルの全レコードを調べ、関連付けられたレイアウトを削除する。
	for (pBlkItr->start(); !pBlkItr->done(); pBlkItr->step()) {
		AcDbBlockTableRecord *pBlkRec;

		if (pBlkItr->getRecord(pBlkRec, AcDb::kForRead) != Acad::eOk) 
			continue;
		
		AcDbObjectId idLayout, idBlkRec;				

		idLayout = pBlkRec->getLayoutId();
		idBlkRec = pBlkRec->objectId();
		pBlkRec->close();

		if (idLayout.isValid())
			continue;
		
		AcDbLayout   *pLayout = new AcDbLayout();
		
		pLayout->setBlockTableRecordId(idBlkRec);

		pLayoutMng->cloneLayout(pLayout, _T(""));
		
			
		
		//const char *pcName;
		//pLayout->getLayoutName(pcName);
		//pLayoutMng->deleteLayout(pcName);
		//pLayout->close();		
	}	
	delete pBlkItr;	
		
	return true;
}

bool ACDocManager::ClonedColorWhite(const AcDbIdMapping &idMap)
{
	AcDbIdMappingIter idmapItr(idMap);
	for (idmapItr.start(); !idmapItr.done(); idmapItr.next()) {
		AcDbIdPair idPair;

		idmapItr.getMap(idPair);
		if (!idPair.isCloned())
			continue;
	
		SetEntityColor(idPair.value(), ACDM_COLOR_EQUAL);
		
		/*
		AcDbEntity *pEnt;
		if (acdbOpenObject(pEnt, idPair.value(), AcDb::kForWrite) != Acad::eOk)
			continue;

		pEnt->setColorIndex(ACDM_COLOR_EQUAL, false);
		pEnt->close();	
		*/
	}		

	return true;
}

bool ACDocManager::SearchClonedPairId(const AcDbIdMapping &idMap, const AcDbObjectId &idSearch, AcDbObjectId &idRet)
{
	AcDbIdMappingIter idmapItr(idMap);	

	for (idmapItr.start(); !idmapItr.done(); idmapItr.next()) {
		AcDbIdPair idPair;
		
		idmapItr.getMap(idPair);
		if (!idPair.isCloned())
			continue;

		if (idPair.key() == idSearch) {
			idRet = idPair.value();
			return true;
		}
	}
	return false;
}

// 指定したDBの全てのレイヤーの色を白にする。
bool ACDocManager::AllLayerDisable(AcDbDatabase *pDb, bool bAllUnLock, bool bAllNoFreeze, bool bAllVisible)
{
	AcDbLayerTable *pLayerTbl;

	if (pDb->getLayerTable(pLayerTbl, AcDb::kForRead) != Acad::eOk)
		return false;

	AcDbLayerTableIterator *pLayerItr;

	pLayerTbl->newIterator(pLayerItr);	
	pLayerTbl->close();

	// 全てのレイヤーレコードに対し、色、レイヤーのロック解除、フリーズ解除、可視を設定する。
	for (pLayerItr->start(); !pLayerItr->done(); pLayerItr->step()) {
		AcDbLayerTableRecord *pLayerRec;

		if (pLayerItr->getRecord(pLayerRec, AcDb::kForWrite) != Acad::eOk)
			continue;
		
		if (bAllUnLock)
			pLayerRec->setIsLocked(false);

		if (bAllNoFreeze)
			pLayerRec->setIsFrozen(false);
		
		if (bAllVisible)
			pLayerRec->setIsOff(false);

		AcCmColor col;		
		col.setColorIndex(ACDM_COLOR_LAYER);
		pLayerRec->setColor(col);

		pLayerRec->close();		
	}
	delete pLayerItr;

	return true;
}


// 指定されたIDの図形の色を指定された色に変更する。ブロック図形、寸法の場合は、構成要素の色も同じにする。
bool ACDocManager::SetEntityColor(AcDbObjectId idEnt, Adesk::UInt16 uiColIdx)
{	
	AcDbEntity *pEnt;	


	if (acdbOpenObject(pEnt, idEnt, AcDb::kForWrite) != Acad::eOk) 
		return false;
	
	pEnt->setColorIndex(uiColIdx, false);	
	
	//CString strName = pEnt->isA()->name();  //####	

	AcDbObjectId idBlkRec = AcDbObjectId::kNull;
	// ブロック参照の場合は構成要素の色も変更する。	
	if (pEnt->isKindOf(AcDbBlockReference::desc())) {					
		AcDbBlockReference *pBlkRef = AcDbBlockReference::cast(pEnt);		
		idBlkRec = pBlkRef->blockTableRecord();		
	}
	// 寸法の場合は構成要素の色も変更する。
	else if (pEnt->isKindOf(AcDbDimension::desc())) {
		AcDbDimension *pDim = AcDbDimension::cast(pEnt);		
		idBlkRec = pDim->dimBlockId();		
	}
	// 寸法の場合は構成要素の色も変更する。
	else if (pEnt->isKindOf(AcDbLeader::desc())) {
		AcDbLeader *pLeader = AcDbLeader::cast(pEnt);
//		pLeader->setDimstyleData( pLeader->dimensionStyle() );
		AcDbDimStyleTableRecord	*pRecord = new AcDbDimStyleTableRecord();
		if( pLeader->getDimstyleData( pRecord ) == Acad::eOk ) {
			pLeader->setDimstyleData( pRecord );
			pRecord->erase();
			pRecord->close();
			delete pRecord;
		}

		AcCmColor col;		
		col.setColorIndex(uiColIdx);
		pLeader->setDimclrd( col );
	}
	//else if (pEnt->isA()->isEqualTo(AcDbMline::desc()) == Adesk::kTrue) {
	//	AcDbMline *pMline = AcDbMline::cast(pEnt);
	//	idBlkRec = pMline->blockId();
	//}

	//idBlkRec = AcDbObjectId::kNull; //####

	if (idBlkRec != AcDbObjectId::kNull) {		
		AcDbBlockTableRecord *pBlkRec;	

		if (acdbOpenObject(pBlkRec, idBlkRec, AcDb::kForRead) == Acad::eOk) {
			AcDbBlockTableRecordIterator *pBlkItr;	

			pBlkRec->newIterator(pBlkItr);
			pBlkRec->close();

			for (pBlkItr->start(); !pBlkItr->done(); pBlkItr->step()) {
				AcDbObjectId idEntElm;

				pBlkItr->getEntityId(idEntElm);
				SetEntityColor(idEntElm, ACDM_COLOR_BYBLOCK);
			}			
			delete pBlkItr;
		}
	}
			
	pEnt->close();
	return true;
}

// 指定したDBのレイアウトのブロックテーブルレコードのID列を得る。
void ACDocManager::GetLayoutBlkRecObjectIdArray(AcDbDatabase *pDb, AcDbObjectIdArray &idaryRetLayout)
{
	AcDbBlockTable *pBlkTbl;

	if (pDb->getSymbolTable(pBlkTbl, AcDb::kForRead) != Acad::eOk) 
		return;
	
	AcDbBlockTableIterator *pBlkItr;		
	int iLayerCount = 0, iAddIdx = -1;

	pBlkTbl->newIterator(pBlkItr);
	pBlkTbl->close();
	
	AcDbLayoutManager *pLayoutMng = acdbHostApplicationServices()->layoutManager();							

	// ブロックテーブルの全レコードを調べ、レイアウトのカウントを得る。
	for (pBlkItr->start(); !pBlkItr->done(); pBlkItr->step()) {
		AcDbBlockTableRecord *pBlkRec;

		if (pBlkItr->getRecord(pBlkRec, AcDb::kForRead) != Acad::eOk) 
			continue;
		
		if (pBlkRec->isLayout())
			iLayerCount++;
		
		pBlkRec->close();	
	}	
	
	idaryRetLayout.setLogicalLength(iLayerCount);
	// ブロックテーブルの全レコードを調べ、関連付けられたレイアウトを削除する。
	for (pBlkItr->start(); !pBlkItr->done(); pBlkItr->step()) {
		AcDbBlockTableRecord *pBlkRec;

		if (pBlkItr->getRecord(pBlkRec, AcDb::kForRead) != Acad::eOk) 
			continue;
		
		if (pBlkRec->isLayout()) {
			iAddIdx++;
			//idaryRetLayout.setAt(iAddIdx, pBlkRec->getLayoutId());
			idaryRetLayout.setAt(iAddIdx, pBlkRec->objectId());
		}
					
		pBlkRec->close();	
	}	

	delete pBlkItr;	
		
	//return true;
}

/*
bool ACDocManager::CreateLayoutMap(
	const AcDbObjectIdArray &idaryLayoutBlkRecOldDwg,
	const AcDbObjectIdArray &idaryLayoutBlkRecOldDwg,								   
	CArray<LayoutBlkRecMap3, LayoutBlkRecMap3> &lomaparyRetMap)
{
	/////
	return true;
}
*/

/*
bool ACDocManager::CreateLayout(AcDbDatabase *pDb, const AcDbObjectIdArray &idaryRefLayoutBlkRec, 
	CArray<LayoutBlkRecMap3, LayoutBlkRecMap3> &lomaparyRetMap)
{
	AcDbObjectIdArray idaryLayoutBlkRec;
	
	GetLayoutBlkRecObjectIdArray(pDb, idaryLayoutBlkRec);
	
	///////////////////////////
	
	CStringArray straryRefName;
	
	// 参考のレイアウトに対応するブロックレコード名の列を得る。
	straryRefName.SetSize(idaryRefLayoutBlkRec.logicalLength());
	for (int i = 0; i < idaryRefLayoutBlkRec.logicalLength(); i++) {
		AcDbBlockTableRecord *pBlkRec;	
		if (acdbOpenObject(pBlkRec, idaryLayoutBlkRec[i], AcDb::kForRead) == Acad::eOk) {	
			CString    strName;
			const char *pcName;

			pBlkRec->getName(pcName);
			strName = pcName;
			straryRefName.SetAt(i, strName);
			pBlkRec->close();
		}
		else {
			straryRefName.SetAt(i, "");
		}
	}

	// レイアウト空間のブロックレコードIDのペアの配列を初期化する。
	lomaparyRetMap.SetSize(idaryRefLayoutBlkRec.logicalLength());
	for (int l = 0; l < idaryRefLayoutBlkRec.logicalLength(); l++) {
		AcDbIdPair idPair(idaryRefLayoutBlkRec[i], AcDbObjectId::kNull, false); 

		lomaparyRetMap.SetAt(l, idPair);
	}

	for (int j = 0; j < idaryLayoutBlkRec.logicalLength(); j++) {
		AcDbBlockTableRecord *pBlkRec;	
		CString strName = "";
		if (acdbOpenObject(pBlkRec, idaryLayoutBlkRec[j], AcDb::kForRead) == Acad::eOk) {
			const char *pcName;		
			pBlkRec->getName(pcName);
			strName = pcName;
			pBlkRec->close();
		}
		
		if (strName != "") {
			for (int k = 0; k < straryRefName.GetSize(); k++) {
				if (straryRefName[k].CollateNoCase(strName) == 0) {
					//AcDbIdPair idPair(idaryRefLayoutBlkRec[k], 
					break;
				}
			}
		}
	}



	
	idaryRetMapLayout.setLogicalLength(idaryRefLayout.logicalLength);
	for (int i = 0; i < idaryRefLayout.logicalLength(); i++) {
		bool bExist = false;
		for (int j = 0; j < idaryLayout.logicalLength(); j++) {
			// 参照レイアウト列のハンドルが指定DBにも存在した場合には、その関係を記録する。
			if (idaryRefLayout[i].handle() == idaryActLayout[j].hendle()) {
				AcDbIdPair idPair(idaryRefLayout[i], idaryActLayout[i], false);
				
				idaryRetMapLayout.setAt(i, idPair);
				bExist = true;
				break;
			}
		}

		
	}
	

	return false;
}
*/

bool ACDocManager::SetMlineStyle(AcDbDatabase *pDb, UINT uiColIdx)
{
	AcDbMlineStyle *pmlStl;

	if (acdbOpenObject(pmlStl, pDb->mLStyleDictionaryId(), AcDb::kForWrite) != Acad::eOk) 
		return false;
	
		
	//pmlStl->

	pmlStl->close();
	

	return true;	
}

// 寸法スタイルの色を設定する。
bool ACDocManager::SetDimStyle(AcDbDatabase *pDb, UINT uiColIdx)
{
	AcDbDimStyleTable *pDimStlTbl;
	
	if (pDb->getDimStyleTable(pDimStlTbl, AcDb::kForRead) != Acad::eOk)
		return false;
	
	AcDbDimStyleTableIterator *pDimStlItr;
	pDimStlTbl->newIterator(pDimStlItr);
	pDimStlTbl->close();
	
	for (pDimStlItr->start(); !pDimStlItr->done(); pDimStlItr->step()) {
		AcDbDimStyleTableRecord *pDimStlRec;

		if (pDimStlItr->getRecord(pDimStlRec, AcDb::kForWrite) == Acad::eOk) {
			AcCmColor col;

			col.setColorIndex(uiColIdx);
	
			pDimStlRec->setDimclrd(col);
			pDimStlRec->setDimclre(col);
			pDimStlRec->setDimclrt(col);
			
			pDimStlRec->close();
		}
	}
	delete pDimStlItr;

	return true;
}

// 寸法スタイルの色を設定する。
bool ACDocManager::SetAllTextStyle(AcDbDatabase *pDb)
{
	AcDbTextStyleTable *pTxtStlTbl;
	
	if (pDb->getTextStyleTable(pTxtStlTbl, AcDb::kForRead) != Acad::eOk)
		return false;
	
	AcDbTextStyleTableIterator *pTxtStlItr;
	pTxtStlTbl->newIterator(pTxtStlItr);
	pTxtStlTbl->close();
	
	for (pTxtStlItr->start(); !pTxtStlItr->done(); pTxtStlItr->step()) {
		AcDbTextStyleTableRecord *pTxtStlRec;

		if (pTxtStlItr->getRecord(pTxtStlRec, AcDb::kForWrite) == Acad::eOk) {
			pTxtStlRec->setBigFontFileName(ACDM_FILE_NAME_BIGFONT);			
			
			pTxtStlRec->close();
		}
	}
	delete pTxtStlItr;

	return true;
}

// 外部参照を図面間でコピーする。
bool ACDocManager::CopyXRefBlock(AcDbDatabase *pDbSrc, AcDbDatabase *pDbDst)
{
	AcDbBlockTable *pBlkTbl;
	AcDbBlockTableIterator *pBlkTblItr;
	bool bRes = true;

	if (pDbSrc->getBlockTable(pBlkTbl, AcDb::kForRead) != Acad::eOk)
		return false;

	pBlkTbl->newIterator(pBlkTblItr);
	pBlkTbl->close();
	
	for (pBlkTblItr->start(); !pBlkTblItr->done(); pBlkTblItr->step()) {	
		AcDbBlockTableRecord *pBlkRec;

		

		if (pBlkTblItr->getRecord(pBlkRec, AcDb::kForRead) == Acad::eOk) {
			AcDbObjectIdArray idaryEnt;	
			AcDbIdMapping	  idMapDst;	
			long lCount = 0;
			long lIdx   = 0;


			// 外部参照ブロックのとき	
			if (pBlkRec->xrefDatabase(true) != NULL) {
				AcDbBlockTableRecordIterator *pBlkRecItr;
				

				TCHAR *pcName;//2006.07.20
				pBlkRec->xrefDatabase(true)->getFilename((const ACHAR *&)pcName);
				acutPrintf(_T("\nXRef: %s"), pcName);
				

				pBlkRec->newIterator(pBlkRecItr); 
				
				// カウントをとる。
				for (pBlkRecItr->start(); !pBlkRecItr->done(); pBlkRecItr->step()) {
					AcDbEntity *pEnt;
					
					if (pBlkRecItr->getEntity(pEnt, AcDb::kForRead) == Acad::eOk) {

						pEnt->database()->getFilename((const ACHAR *&)pcName);
						acutPrintf(_T("\nElm : %s"), pcName);

						lCount++;					
						pEnt->close();
					}
				}
				
				idaryEnt.setLogicalLength(lCount);

				// 要素のオブジェクトIDを配列にする。
				for (pBlkRecItr->start(); !pBlkRecItr->done(); pBlkRecItr->step()) {					
					AcDbEntity *pEnt;
					
					if (pBlkRecItr->getEntity(pEnt, AcDb::kForRead) == Acad::eOk) {
						idaryEnt.setAt(lIdx, pEnt->objectId());						
						lIdx++;
						pEnt->close();
					}		
					
				}
				
				//Acad::ErrorStatus es;
				
				// コピーの実行
				//if ((es = pDbDst->wblockCloneObjects(
				//	idaryEnt, pBlkRec->objectId(), idMapDst, AcDb::kDrcIgnore)) != Acad::eOk) {
			//		bRes = false;					
			//	}

				delete pBlkRecItr;				
			}			
			pBlkRec->close();


			Acad::ErrorStatus es;
			// コピーの実行
			if (lCount > 0) {
				if ((es = pDbDst->wblockCloneObjects(
					idaryEnt, pBlkRec->objectId(), idMapDst, AcDb::kDrcIgnore)) != Acad::eOk) {
					bRes = false;					
					break;
				}
			}

			//if (!bRes)
			//	break;
		}		
	}
	
	delete pBlkTblItr;
	return bRes;
}

// 外部参照を図面間でコピーする。
bool ACDocManager::CopyXRefBlock(AcDbDatabase *pDbSrc, AcDbIdMapping &idMap, AcDbDatabase *pDbDst)
{
	AcDbIdMappingIter idMapItr(idMap);
	bool bRes = true;


	for (idMapItr.start(); !idMapItr.done(); idMapItr.next()) {
		AcDbIdPair idPair;

		idMapItr.getMap(idPair);
		if (!idPair.isCloned())
			continue;
	
		//idPair
		
		AcDbBlockTableRecord *pBlkRec;

		if (acdbOpenObject(pBlkRec, idPair.key(), AcDb::kForRead) == Acad::eOk) {
			AcDbObjectIdArray idaryEnt;	
		   	AcDbIdMapping   idMapDst;
			long lCount = 0;

			// 外部参照ブロックのとき	
			if (pBlkRec->xrefDatabase(true) != NULL) {
				AcDbBlockTableRecordIterator *pBlkRecItr;
				long lIdx = 0;

				//char *pcName;
				//pBlkRec->xrefDatabase(true)->getFilename(pcName);
				//acutPrintf("\nXRef: %s", pcName);
				
				pBlkRec->newIterator(pBlkRecItr); 
				
				// カウントをとる。
				for (pBlkRecItr->start(); !pBlkRecItr->done(); pBlkRecItr->step()) {
					AcDbEntity *pEnt;
					
					if (pBlkRecItr->getEntity(pEnt, AcDb::kForRead) == Acad::eOk) {

						//pEnt->database()->getFilename(pcName);
						//acutPrintf("\nElm : %s", pcName);

						lCount++;					
						pEnt->close();
					}
				}
				
				idaryEnt.setLogicalLength(lCount);

				// 要素のオブジェクトIDを配列にする。
				for (pBlkRecItr->start(); !pBlkRecItr->done(); pBlkRecItr->step()) {					
					AcDbEntity *pEnt;
					
					if (pBlkRecItr->getEntity(pEnt, AcDb::kForRead) == Acad::eOk) {
						idaryEnt.setAt(lIdx++, pEnt->objectId());						
						//lIdx++;
						pEnt->close();
					}		
					
				}
				
				//Acad::ErrorStatus es;
				
				// コピーの実行
				//if ((es = pDbDst->wblockCloneObjects(
				//	idaryEnt, pBlkRec->objectId(), idMapDst, AcDb::kDrcIgnore)) != Acad::eOk) {
			//		bRes = false;					
			//	}

				delete pBlkRecItr;				
			}			

			//pBlkRec->setIsUnloaded(false);
			pBlkRec->close();
			
			// コピー先の外部参照レコードを開き、アンロードされているかどうか調べる。
			if (acdbOpenObject(pBlkRec, idPair.value(), AcDb::kForWrite) == Acad::eOk) {
				pBlkRec->setIsUnloaded(false);
				pBlkRec->setPathName(NULL);
				pBlkRec->close();
			}

			Acad::ErrorStatus es;
			// コピーの実行
			if (lCount > 0) {
				if ((es = pDbDst->wblockCloneObjects(
					idaryEnt, idPair.value(), idMapDst, AcDb::kDrcIgnore)) != Acad::eOk) {
					bRes = false;					
					break;
				}
			}

			pBlkRec->close();
		}
	
	}		
	

	return true;
}

// コピーした外部参照をバインドする。
void ACDocManager::BindXRef(const AcDbIdMapping &idMap)
{
	AcDbIdMappingIter idMapItr(idMap);	

	for (idMapItr.start(); !idMapItr.done(); idMapItr.next()) {
		AcDbIdPair idPair;

		idMapItr.getMap(idPair);
		if (!idPair.isCloned())
			continue;
		
		AcDbBlockTableRecord *pBlkRec;	
		
		
		if (acdbOpenObject(pBlkRec, idPair.key(), AcDb::kForRead) == Acad::eOk) {			
			if (pBlkRec->xrefDatabase() != NULL) {
				Acad::ErrorStatus es;	
				TCHAR *pcName;//2006.07.20
				
				// 最初にリロードをし、成功すればバインドする。リロードに失敗した場合（ファイルが無い場合など）
				// は、デタッチし、警告を表示する。
				// 外部参照の名前は元の図面より取得する。
				//acedXrefReloadはアクティブな図面(合成図面)に対して適用される。
				pBlkRec->getName(pcName);
				if ((es = acedXrefReload(pcName)) == Acad::eOk) {
					es = acedXrefBind(pcName);
				}
				else {
					es = acedXrefDetach(pcName);
					acutPrintf(_T("\n次の外部参照は見つかりません。: %s"), pcName);//2006.07.20
				}
				
				acutDelString(pcName);
			}
			
			pBlkRec->close();
		}
	}
}

// 変更無し、追加、修正、削除の結果を色で表現するレイヤーを作成する。
bool ACDocManager::CreateResultLayers(AcDbDatabase *pDb, ACResultLayers &resLayers)
{
	AcDbLayerTable       *pLayerTbl;
	AcDbLayerTableRecord *pLayerRec; 	
	AcCmColor		  col;
	CString			  strName;	
	
	if (pDb->getLayerTable(pLayerTbl, AcDb::kForWrite) != Acad::eOk)
		return false;

	strName.Format(_T("変更無し")); 
	col.setColorIndex(ACDM_COLOR_EQUAL);
	pLayerRec = new AcDbLayerTableRecord();
	pLayerRec->setName(strName);
	pLayerRec->setIsFrozen(0);
	pLayerRec->setIsOff(0);
	pLayerRec->setVPDFLT(0);
	pLayerRec->setIsLocked(0);	
	pLayerRec->setColor(col);
	pLayerTbl->add(resLayers.m_idNotModify, pLayerRec);
	pLayerRec->close();

	
	strName.Format(_T("変更有り"));//2006.07.20 
	col.setColorIndex(ACDM_COLOR_NOT_EQUAL);
	pLayerRec = new AcDbLayerTableRecord();
	pLayerRec->setName(strName);
	pLayerRec->setIsFrozen(0);
	pLayerRec->setIsOff(0);
	pLayerRec->setVPDFLT(0);
	pLayerRec->setIsLocked(0);	
	pLayerRec->setColor(col);
	pLayerTbl->add(resLayers.m_idModify, pLayerRec);
	pLayerRec->close();

	strName.Format(_T("追加"));//2006.07.20 
	col.setColorIndex(ACDM_COLOR_NEW);
	pLayerRec = new AcDbLayerTableRecord();
	pLayerRec->setName(strName);
	pLayerRec->setIsFrozen(0);
	pLayerRec->setIsOff(0);
	pLayerRec->setVPDFLT(0);
	pLayerRec->setIsLocked(0);	
	pLayerRec->setColor(col);
	pLayerTbl->add(resLayers.m_idAdd, pLayerRec);
	pLayerRec->close();

	strName.Format(_T("削除"));//2006.07.20 
	col.setColorIndex(ACDM_COLOR_DELETE);
	pLayerRec = new AcDbLayerTableRecord();
	pLayerRec->setName(strName);
	pLayerRec->setIsFrozen(0);
	pLayerRec->setIsOff(0);
	pLayerRec->setVPDFLT(0);
	pLayerRec->setIsLocked(0);	
	pLayerRec->setColor(col);
	pLayerTbl->add(resLayers.m_idDelete, pLayerRec);
	pLayerRec->close();
	

	pLayerTbl->close();
	
	return true;
}

// 変更前文字列レイヤーを作成する。
bool ACDocManager::CreateBeforeModifyLayers(AcDbDatabase *pDb)
{
	AcDbSymbolTablePointer<AcDbLayerTable>	pLayerTbl( pDb->layerTableId(), AcDb::kForWrite );
	if( pLayerTbl.openStatus() != Acad::eOk ) {
		return false;
	}

	if( pLayerTbl->has( ACDM_PREVMODIFY_LAYER ) ) {
		return true;
	}

	AcDbSymbolTableRecordPointer<AcDbLayerTableRecord>	pLayerRec;

	pLayerRec.create();
	AcCmColor	col;
	col.setColorIndex( ACDM_PREVMODIFY_COLOR );
	pLayerRec->setName(ACDM_PREVMODIFY_LAYER);
	pLayerRec->setColor( col );
	pLayerTbl->add(pLayerRec);
	pLayerRec->close();

	return true;
}

/*
// 指定した名前を付けたレイヤーを返す。レイヤーが既に存在する場合は名前の後ろに番号をつける。
bool ACDocManager::CreateNameLayer(const AcDbDatabase *pDb, const ACCreateLayerInfo &lyrInfo, AcDbObjectId &idRetLayer)
{
	AcDbLayerTable       *pLayerTbl;
	AcDbLayerTableRecord *pLayerRec;
	Acad::ErrorStatus    es;
	CString			     strName;
	long				 lNumber = 1;

	if (pDb->getLayerTable(pLayerTbl, AcDb::kForWrite) != Acad::eOk)
		return false;

	pLayerRec = new AcDbLayerTableRecord();
	strName.Format("0"); 
	es = pLayerRec->setName(strName);
	es = pLayerTbl->add(pLayerRec);

	return true;
}
*/

long ACDocManager::GetCompRectId(const AcDbObjectId &idBlkTbl, AcDbObjectId &idRetCompRect)
{
	// ブロックテーブルのIDがidBlkTblである図面をアクティブにする。
	AcApDocument *pDoc;
	
	pDoc = acDocManager->document(idBlkTbl.database());
	acDocManager->setCurDocument(pDoc, AcAp::kNone, true);

	// アクティブな図面から比較範囲の矩形の個数と先頭のオブジェクトID得る。
	ACCompRect acRect;
	return acRect.GetCompRectId(idRetCompRect);
}

bool ACDocManager::GetRangeEntityIds(const AcDbObjectId &idCompRect, CMap<int, int, AcDbObjectId, AcDbObjectId> &idmapRet)
{
	// ブロックテーブルのIDがidBlkTblである図面をアクティブにする。
	AcApDocument *pDoc;

	pDoc = acDocManager->document(idCompRect.database());
	acDocManager->setCurDocument(pDoc, AcAp::kNone, true);
	
	acDocManager->lockDocument(pDoc);

	// 比較範囲の矩形を取得する。
	AcDbExtents extRange;

	GetGeomExtents(idCompRect, extRange);

	// 指定した範囲でズームする。
	double dZoomExtX, dZoomExtY;  // ズームのための拡大
	
	dZoomExtX = (extRange.maxPoint()[X] - extRange.minPoint()[X]) / 1000;
	dZoomExtY = (extRange.maxPoint()[Y] - extRange.minPoint()[Y]) / 1000;

	AcGePoint2d ptLB(extRange.minPoint()[X] - dZoomExtX, extRange.minPoint()[Y] - dZoomExtY);
	AcGePoint2d ptRT(extRange.maxPoint()[X] + dZoomExtX, extRange.maxPoint()[Y] + dZoomExtY);

	AutomationZoom(ptLB, ptRT); 
	//AutomationCommand("REGEN "); 

	// 選択範囲の図形を取得する。
	ads_point aptLB, aptRT;
	ads_name  sset;

	aptLB[X] = extRange.minPoint()[X];
	aptLB[Y] = extRange.minPoint()[Y];
	aptRT[X] = extRange.maxPoint()[X];
	aptRT[Y] = extRange.maxPoint()[Y];

	//acedSSGet("B", aptLB, aptRT, NULL, sset);
	acedSSGet(_T("W"), aptLB, aptRT, NULL, sset);//2006.07.20
	
	long l, lLen = 0, lMapKey = 0;		
	acedSSLength(sset, &lLen);
	
	

	// 範囲にある図形のカウントを取る。ブロック参照の場合は、属性のカウントも加える。
	for (l = 0; l < lLen; l++) {
		ads_name nameEnt;
		AcDbObjectId idEnt;

		acedSSName(sset, l, nameEnt);
		acdbGetObjectId(idEnt, nameEnt);
		
		// 比較範囲の矩形のオブジェクトID以外のときは、マップに追加する。
		if (idEnt != idCompRect) 
			lMapKey++;

		AcDbEntity *pEnt;

		if (acdbOpenObject(pEnt, idEnt, AcDb::kForRead) == Acad::eOk) {
			// ブロック参照の場合は、属性のカウントも取る。
			AcDbBlockReference *pBlockRef = AcDbBlockReference::cast(pEnt);
			if (pBlockRef != NULL) {
				AcDbObjectIterator *pItrAttr = pBlockRef->attributeIterator();
				AcDbObjectId idAttr;

				for (pItrAttr->start(); !pItrAttr->done(); pItrAttr->step()) {
					AcDbObjectId idAttr;

					idAttr = pItrAttr->objectId();
					if (idAttr != AcDbObjectId::kNull) 						
						lMapKey++;
				}							
				delete pItrAttr;
			}
			pEnt->close();
		}
	}

	idmapRet.InitHashTable(lMapKey);
	lMapKey = 0;

	// 範囲にある図形のIDをマップに加える。ブロック参照の場合は、属性のIDも加える。
	for (l = 0; l < lLen; l++) {
		ads_name nameEnt;
		AcDbObjectId idEnt;

		acedSSName(sset, l, nameEnt);
		acdbGetObjectId(idEnt, nameEnt);
		
		// 比較範囲の矩形のオブジェクトID以外のときは、マップに追加する。
		if (idEnt != idCompRect) 
			idmapRet[lMapKey++] = idEnt;

		AcDbEntity *pEnt;

		if (acdbOpenObject(pEnt, idEnt, AcDb::kForRead) == Acad::eOk) {
			// ブロック参照の場合は、属性のIDも加える。
			AcDbBlockReference *pBlockRef = AcDbBlockReference::cast(pEnt);
			if (pBlockRef != NULL) {
				AcDbObjectIterator *pItrAttr = pBlockRef->attributeIterator();
				AcDbObjectId idAttr;

				for (pItrAttr->start(); !pItrAttr->done(); pItrAttr->step()) {
					AcDbObjectId idAttr;

					idAttr = pItrAttr->objectId();
					if (idAttr != AcDbObjectId::kNull) {						
						idmapRet[lMapKey++] = idAttr;	
					}
				}							
				delete pItrAttr;
			}
			pEnt->close();
		}
	}



	acedSSFree(sset);
	
	AutomationCommand(_T("zoom p "));//2006.07.20

	acDocManager->unlockDocument(pDoc);
	return true;
}

void ACDocManager::SetRangeCompMode(const AcGeVector3d &vec3Gap)
{
	m_bRangeCompMode = true;
	m_vec3Gap.set(vec3Gap.x, vec3Gap.y, vec3Gap.z);
}


// 範囲比較モードのときは、旧図面の図形を、比較範囲の基点のずれの分だけ移動する。
bool ACDocManager::MoveGap(AcDbIdMapping &idMap)
{
	// アクティブな図面のモデル空間のブロックテーブルIDを得る。
	AcDbBlockTable *pBlkTbl;
	
	acdbHostApplicationServices()->workingDatabase()->
		getSymbolTable(pBlkTbl, AcDb::kForRead);

	AcDbObjectId idModelSpace;
	pBlkTbl->getAt(ACDB_MODEL_SPACE, idModelSpace);
	pBlkTbl->close();

	// ディープクローンした図形のオブジェクトIDのマップを得る。
	AcDbIdMappingIter idMapItr(idMap);	

	// 移動のマトリックスを得る。
	AcGeMatrix3d matMove; 

	matMove = AcGeMatrix3d::translation(m_vec3Gap);
	
	for (idMapItr.start(); !idMapItr.done(); idMapItr.next()) {
		AcDbIdPair idPair;

		idMapItr.getMap(idPair);
		if (!idPair.isCloned())
			continue;
		
		AcDbEntity *pEnt;	
		Acad::ErrorStatus es;

		if ((es = acdbOpenObject(pEnt, idPair.value(), AcDb::kForWrite)) == Acad::eOk) {			
			// グループ化図形の場合は、リアクターにより、次の移動とスケールの変換が
			// 二重にかかってしまうことがあるので、リアクタを除く。
			// 引き出し線の場合は、注釈オブジェクトにリアクタがセットされているが、
			// 移動や、スケールをかけるようなリアクタではないのでリアクタを除かない。
			AcDbVoidPtrArray  *pReactors;	
			void			  *pSomething;
			AcDbObjectId      idPersReac;
			Acad::ErrorStatus es;
			int				  iLenReac;						
			
			pReactors = pEnt->reactors();							
			if (pReactors != NULL) {
				int iIdxReac = 0;
				iLenReac = pReactors->logicalLength();
				for (int l = 0; l < iLenReac; l++) {					
					pSomething = (void *)pReactors->at(iIdxReac);	
					if (acdbIsPersistentReactor(pSomething)) {
						idPersReac = acdbPersistentReactorObjectId(pSomething);

						es = Acad::eInvalidInput;
						// 注釈オブジェクトのリアクタのIDは、引出し線を表す。
						if (!IsAcDbLeaderId(idPersReac))
							es = pEnt->removePersistentReactor(idPersReac);
						
						// リアクタの取り除きに失敗したときや、引き出し線のリアクタであった場合は、
						// 次のリアクタに移動する。
						if (es != Acad::eOk)
							iIdxReac++;						
					}
					// 永続リアクタでない場合は次のリアクタに移動する。
					else
						iIdxReac++;			
				}
			}
			

			// オーナーがモデル空間である場合のみ移動を実行する。
			if (pEnt->ownerId() == idModelSpace)
				pEnt->transformBy(matMove);	
			pEnt->close();
		}
	}	
	
	return true;
}

// 指定されたオブジェクトIDが引き出し線のものであるか調べる。
bool ACDocManager::IsAcDbLeaderId(AcDbObjectId idEnt)
{
	AcDbEntity *pEnt;
	bool bRes = false;

	if (acdbOpenObject(pEnt, idEnt, AcDb::kForRead) == Acad::eOk) {
		if (pEnt->isA()->isEqualTo(AcDbLeader::desc()) == Adesk::kTrue)	
			bRes = true;
		pEnt->close();
	}
	
	return bRes;	
}

bool ACDocManager::SetResultXData(AcDbObjectId idModel)
{
	// モデル空間のオブジェクトを開く
	AcDbObject* pObj;
	Acad::ErrorStatus retStat;
	if ((retStat = acdbOpenObject(pObj, idModel, AcDb::kForWrite)) != Acad::eOk) {
		ads_printf(_T("\nacdbOpenEntity failed: retStat:%d"), retStat);
		return false;
	}

	struct resbuf *pRb, *pTemp;
	pRb = pObj->xData(ACDM_RESULTAPPNAME);
	pTemp = pRb;

	/* 拡張データの種類が異なると困るので、既にある拡張データは解放する。	*/
    if (pRb != NULL) {
		ads_relrb(pRb);
		pRb = NULL;
	}

	/* アプリケーション名の登録とセット */
	ads_regapp(ACDM_RESULTAPPNAME);
	pRb = ads_newrb(AcDb::kDxfRegAppName);
	if (pRb == NULL) {
		pObj->close();
		return false;
	}
	pTemp = pRb;
//	pTemp->resval.rstring = (TCHAR*)malloc(_tcslen(ACDM_RESULTAPPNAME) + 1);
	pTemp->resval.rstring = new TCHAR[_tcslen(ACDM_RESULTAPPNAME) + 1];
	_tcscpy(pTemp->resval.rstring, ACDM_RESULTAPPNAME);

	// 合成図面XDATAを設定
	pTemp->rbnext = ads_newrb(AcDb::kDxfXdAsciiString);
	if (pTemp->rbnext == NULL) {
		pObj->close();
		ads_relrb(pRb);
		return false;
	}
	pTemp = pTemp->rbnext;
//	pTemp->resval.rstring = (TCHAR*)malloc(_tcslen(ACDM_RESULTXDATA) + 1);
	pTemp->resval.rstring = new TCHAR[_tcslen(ACDM_RESULTXDATA) + 1];
	if (pTemp->resval.rstring == NULL) {
		pObj->close();
		ads_relrb(pRb);
		return false;
	}
	_tcscpy(pTemp->resval.rstring, ACDM_RESULTXDATA);

	pTemp->rbnext = NULL;

	if (Acad::eOk != pObj->setXData(pRb)) {
		ads_printf(_T("\n setXData ERR"));
	}
	pObj->close();
	ads_relrb(pRb);

	return true;
}
