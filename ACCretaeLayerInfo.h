// ACCretaeLayerInfo.h: ACCretaeLayerInfo クラスのインターフェイス
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ACCRETAELAYERINFO_H__5BDE4C4F_2166_4070_AC51_4A200AB7792E__INCLUDED_)
#define AFX_ACCRETAELAYERINFO_H__5BDE4C4F_2166_4070_AC51_4A200AB7792E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class ACCretaeLayerInfo  
{
public:
	ACCretaeLayerInfo();
	virtual ~ACCretaeLayerInfo();
	
	CString   strName;
	AcCmColor col;

};

#endif // !defined(AFX_ACCRETAELAYERINFO_H__5BDE4C4F_2166_4070_AC51_4A200AB7792E__INCLUDED_)
