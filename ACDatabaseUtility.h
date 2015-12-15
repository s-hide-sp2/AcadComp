// ACDatabaseUtility.h: ACDatabaseUtility クラスのインターフェイス
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ACDATABASEUTILITY_H__9CD1EDA1_59E1_41E1_AA33_0757890A577C__INCLUDED_)
#define AFX_ACDATABASEUTILITY_H__9CD1EDA1_59E1_41E1_AA33_0757890A577C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class ACDatabaseUtility  
{
public:
	// アクティブなデータベースにエンティティを加える。	
	bool AppendEntity(AcDbEntity* pEntity, AcDbObjectId& outputId);
	ACDatabaseUtility();
	virtual ~ACDatabaseUtility();

};

#endif // !defined(AFX_ACDATABASEUTILITY_H__9CD1EDA1_59E1_41E1_AA33_0757890A577C__INCLUDED_)
