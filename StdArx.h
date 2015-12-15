//
// StdArx.h : include file for ObjectARX/DBX include files
// this file is only included once by your stdafx.h

#if !defined(AFX_STDARX_H__191161DA_7ADE_4750_B0B6_6C0B0C8597DE__INCLUDED_)
#define AFX_STDARX_H__191161DA_7ADE_4750_B0B6_6C0B0C8597DE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


//{{AFX_ARX_INC_SELECTED
//}}AFX_ARX_INC_SELECTED

//{{AFX_ARX_INC_OTHERS
#include "rEditorReactor.h"
//}}AFX_ARX_INC_OTHERS
#include "AdskDMgr.h"         // Utility class for document data
#include "docdata.h"          // Your document specific data

// Declare it as an extern here so that it
// becomes available in all modules
extern AsdkDataManager<CDocData> DocVars;
//{{AFX_ARX_FUNC
void DAACMPCompDwg();
void DAACMPCOMPRECT();
void DAACMPDELCOMPRECT();
void DAACMPTEST01();
void DAACMPTEST02();
void DAACMPTOGGLEDISPADD();
void DAACMPTOGGLEDISPDELETE();
void DAACMPTOGGLEDISPMODIFY();
void DAACMPTOGGLEDISPSAME();
//}}AFX_ARX_FUNC

// TODO: Here you can add your own includes / declarations
#endif 
