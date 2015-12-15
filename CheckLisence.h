// CheckLisence.h: CCheckLisence クラスのインターフェイス
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CHECKLISENCE_H__5B075BAB_7D56_4E68_AB8B_F8567546CF5B__INCLUDED_)
#define AFX_CHECKLISENCE_H__5B075BAB_7D56_4E68_AB8B_F8567546CF5B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


//AutoCADバージョン定義
#define CAD_CURRENTAPP			_T("AutoCAD.Application")
#define CAD_CURVER				_T("AutoCAD.Application\\CurVer")
#define CAD_CLSID				_T("AutoCAD.Application\\CLSID")
#define CAD_CLSIDPART			_T("\\CLSID")
#define CAD_14VERSION			_T("AutoCAD.Application.14")
#define CAD_2000VERSION			_T("AutoCAD.Application.15")
#define CAD_2000iVERSION		_T("AutoCAD.Application.15")
#define CAD_2002VERSION			_T("AutoCAD.Application.15")
#define CAD_2004VERSION			_T("AutoCAD.Application.16")
#define CAD_2005VERSION			_T("AutoCAD.Application.16.1")
#define CAD_2006VERSION			_T("AutoCAD.Application.16.2")
#define CAD_2007VERSION			_T("AutoCAD.Application.17")	//2006.07.02
#define CAD_2008VERSION			_T("AutoCAD.Application.17.1")	//2007.05.08
#define CAD_2009VERSION			_T("AutoCAD.Application.17.2")	//2008.04.14
#define CAD_14REG				_T("Software\\Autodesk\\AutoCAD\\R14.0")
#define CAD_2000REG				_T("Software\\Autodesk\\AutoCAD\\R15.0")
#define CAD_2000iREG			_T("Software\\Autodesk\\AutoCAD\\R15.0")
#define CAD_2002REG				_T("Software\\Autodesk\\AutoCAD\\R15.0")
#define CAD_2004REG				_T("Software\\Autodesk\\AutoCAD\\R16.0")
#define CAD_2005REG				_T("Software\\Autodesk\\AutoCAD\\R16.1")
#define CAD_2006REG				_T("Software\\Autodesk\\AutoCAD\\R16.2")
#define CAD_2007REG				_T("Software\\Autodesk\\AutoCAD\\R17.0")	//2006.07.02
#define CAD_2008REG				_T("Software\\Autodesk\\AutoCAD\\R17.1")	//2007.05.08
#define CAD_2009REG				_T("Software\\Autodesk\\AutoCAD\\R17.2")	//2008.04.14
#define CAD_2006CUI				_T(".CUI")					//2006.03.29
#define CAD_SUPPORT				_T("Support")				//2006.09.28
#define REG_FIXEDPROFILE		_T("FixedProfile")			//2006.09.28

#define VER_14					_T("R14.0")
#define VER_2000				_T("R15.0")
#define	VER_2004				_T("R16.0")
#define	VER_2005				_T("R16.1")
#define VER_2006				_T("R16.2")
#define	VER_2007				_T("R17.0")
#define	VER_2008				_T("R17.1")					//2007.05.08
#define	VER_2009				_T("R17.2")					//2008.04.14

#define	ITM_VERSION			"VERSION"
#define	ITM_OVERRIDE		"OVERRIDE"
#define	ITM_INSTALLFOLDER	"INSTALLFOLDER"
#define	ITM_DEFAULTFOLDER	"DEFAULTFOLDER"
#define	ITM_INSTALLDATE		"INSTALLDATE"		//2006.09.28
#define	ITM_LASTACCESS		"LASTACCESS"		//2006.09.28
#define	ITM_CHECKPRG		"CHECKPRG"			//2006.09.28
#define	ITM_REVISION		"REVISION"			//2006.09.28
#define	ITM_REVISIONSUB		"REVISIONSUB"		//2006.09.28
#define ITM_USABLETERM		"USABLETERM"

#define BUF_MAX 2048


class CCheckLisence  
{
public:
	CCheckLisence();
	virtual ~CCheckLisence();
public:
	static	BOOL CCheckLisence::CheckUsableTerm(CString strAppName, CString strAcadVer);
	static  BOOL CCheckLisence::GetRegBase(CString strCadVer, CString & strRegPath);
	static  long CCheckLisence::RegQueryValueAcad(HKEY hKey, CString strItem, CString &strStr);
	static  BOOL CCheckLisence::GetCRCVal(CString strBuf, unsigned short & crc);
	static  BOOL CCheckLisence::GetCRCValFile(CString strInpFile, unsigned short & crc);
	static void CCheckLisence::GetDayString( 
							TCHAR * lpszString,	//(o)日付文字列
							const CTime& time	//(i)時間
			);
	static long CCheckLisence::RegSetValueAcad(HKEY hKey, CString strItem,  CString strStr);

};

#endif // !defined(AFX_CHECKLISENCE_H__5B075BAB_7D56_4E68_AB8B_F8567546CF5B__INCLUDED_)
