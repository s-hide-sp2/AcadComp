// LVSortInfo.cpp: LVSortInfo クラスのインプリメンテーション
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "resource.h"
#include "LVSortInfo.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// 構築/消滅
//////////////////////////////////////////////////////////////////////

LVSortInfo::LVSortInfo()
{
	m_bAsc = false;
	m_iIdx = -1;
}

LVSortInfo::~LVSortInfo()
{

}
