# Microsoft Developer Studio Project File - Name="AcadComp" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** 編集しないでください **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=AcadComp - Win32 FullDebug
!MESSAGE これは有効なﾒｲｸﾌｧｲﾙではありません。 このﾌﾟﾛｼﾞｪｸﾄをﾋﾞﾙﾄﾞするためには NMAKE を使用してください。
!MESSAGE [ﾒｲｸﾌｧｲﾙのｴｸｽﾎﾟｰﾄ] ｺﾏﾝﾄﾞを使用して実行してください
!MESSAGE 
!MESSAGE NMAKE /f "AcadComp.mak".
!MESSAGE 
!MESSAGE NMAKE の実行時に構成を指定できます
!MESSAGE ｺﾏﾝﾄﾞ ﾗｲﾝ上でﾏｸﾛの設定を定義します。例:
!MESSAGE 
!MESSAGE NMAKE /f "AcadComp.mak" CFG="AcadComp - Win32 FullDebug"
!MESSAGE 
!MESSAGE 選択可能なﾋﾞﾙﾄﾞ ﾓｰﾄﾞ:
!MESSAGE 
!MESSAGE "AcadComp - Win32 Release" ("Win32 (x86) Dynamic-Link Library" 用)
!MESSAGE "AcadComp - Win32 Debug" ("Win32 (x86) Dynamic-Link Library" 用)
!MESSAGE "AcadComp - Win32 FullDebug" ("Win32 (x86) Dynamic-Link Library" 用)
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""$/AcadComp", IBJDAAAA"
# PROP Scc_LocalPath "."
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "AcadComp - Win32 Release"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_AFXEXT" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x411 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x411 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 rxapi.lib acrx15.lib acdb15.lib acutil15.lib acge15.lib acgiapi.lib achapi15.lib acISMobj15.lib acad.lib acedapi.lib acsiobj.lib adui15.lib acui15.lib /nologo /subsystem:windows /dll /machine:I386 /out:"Release/AcadComp.arx"
# SUBTRACT LINK32 /pdb:none
# Begin Special Build Tool
SOURCE="$(InputPath)"
PostBuild_Cmds=copy Release\AcadComp.arx "C:\Program Files\ACADCOMP2002\ACADCOMP.arx"
# End Special Build Tool

!ELSEIF  "$(CFG)" == "AcadComp - Win32 Debug"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MD /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_AFXEXT" /FR /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x411 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x411 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 rxapi.lib acrx15.lib acdb15.lib acutil15.lib acge15.lib acgiapi.lib achapi15.lib acISMobj15.lib acad.lib acedapi.lib acsiobj.lib adui15.lib acui15.lib /nologo /subsystem:windows /dll /debug /machine:I386 /out:"Debug/DAAAcadComp.arx" /pdbtype:sept
# SUBTRACT LINK32 /pdb:none
# Begin Special Build Tool
SOURCE="$(InputPath)"
PostBuild_Cmds=copy Debug\DAAAcadComp.arx "C:\Program Files\ACADCOMP2002\ACADCOMP.arx"
# End Special Build Tool

!ELSEIF  "$(CFG)" == "AcadComp - Win32 FullDebug"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "AcadComp___Win32_FullDebug"
# PROP BASE Intermediate_Dir "AcadComp___Win32_FullDebug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "AcadComp___Win32_FullDebug"
# PROP Intermediate_Dir "AcadComp___Win32_FullDebug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /YX /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_AFXEXT" /D "_FULLDEBUG_" /Fp"FullDebug/AcadComp.pch" /YX /Fo"FullDebug/" /Fd"FullDebug/" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x411 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x411 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /pdb:"FullDebug/DAAAcadComp.pdb" /debug /machine:I386 /out:"FullDebug/DAAAcadComp.arx" /implib:"FullDebug/DAAAcadComp.lib" /pdbtype:sept
# SUBTRACT BASE LINK32 /pdb:none
# ADD LINK32 rxapi.lib acrx15.lib acdb15.lib acutil15.lib acge15d.lib acgiapi.lib achapi15.lib acISMobj15.lib acad.lib acedapi.lib acsiobj.lib adui15.lib acui15.lib /nologo /subsystem:windows /dll /pdb:"FullDebug/DAAAcadComp.pdb" /debug /machine:I386 /out:"FullDebug/DAAAcadComp.arx" /implib:"FullDebug/DAAAcadComp.lib" /pdbtype:sept
# SUBTRACT LINK32 /pdb:none
# Begin Special Build Tool
SOURCE="$(InputPath)"
PostBuild_Cmds=copy 
# End Special Build Tool

!ENDIF 

# Begin Target

# Name "AcadComp - Win32 Release"
# Name "AcadComp - Win32 Debug"
# Name "AcadComp - Win32 FullDebug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\AcadComp.cpp
# End Source File
# Begin Source File

SOURCE=.\AcadComp.def
# End Source File
# Begin Source File

SOURCE=.\AcadComp.rc
# End Source File
# Begin Source File

SOURCE=.\AcadCompCommands.cpp
# End Source File
# Begin Source File

SOURCE=.\ACCMap.cpp
# End Source File
# Begin Source File

SOURCE=.\ACCommandReactor.cpp
# End Source File
# Begin Source File

SOURCE=.\ACCompBase.cpp
# End Source File
# Begin Source File

SOURCE=.\ACCompEntitiesGeom.cpp
# End Source File
# Begin Source File

SOURCE=.\ACCompRect.cpp
# End Source File
# Begin Source File

SOURCE=.\AcConvertColor.cpp
# End Source File
# Begin Source File

SOURCE=.\ACConvertName.cpp
# End Source File
# Begin Source File

SOURCE=.\ACCretaeLayerInfo.cpp
# End Source File
# Begin Source File

SOURCE=.\ACDatabaseUtility.cpp
# End Source File
# Begin Source File

SOURCE=.\ACDbSysVar.cpp
# End Source File
# Begin Source File

SOURCE=.\ACDocManager.cpp
# End Source File
# Begin Source File

SOURCE=.\ACEntityInfo.cpp
# End Source File
# Begin Source File

SOURCE=.\ACErrorInfo.cpp
# End Source File
# Begin Source File

SOURCE=.\ACFinally.cpp
# End Source File
# Begin Source File

SOURCE=.\ACProfileManager.cpp
# End Source File
# Begin Source File

SOURCE=.\ACResultLayers.cpp
# End Source File
# Begin Source File

SOURCE=.\ACRetType.cpp
# End Source File
# Begin Source File

SOURCE=.\ACSort.cpp
# End Source File
# Begin Source File

SOURCE=.\ACString.cpp
# End Source File
# Begin Source File

SOURCE=.\ACUIManager.cpp
# End Source File
# Begin Source File

SOURCE=.\DialogCompDwg.cpp
# End Source File
# Begin Source File

SOURCE=.\DialogSetting.cpp
# End Source File
# Begin Source File

SOURCE=.\DocData.cpp
# End Source File
# Begin Source File

SOURCE=.\InfoDwgEntity.cpp
# End Source File
# Begin Source File

SOURCE=.\LayoutBlkRecMap3.cpp
# End Source File
# Begin Source File

SOURCE=.\ListGrid.cpp
# End Source File
# Begin Source File

SOURCE=.\LVSortInfo.cpp
# End Source File
# Begin Source File

SOURCE=.\ResultCompEntity.cpp
# End Source File
# Begin Source File

SOURCE=.\rxdebug.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp

!IF  "$(CFG)" == "AcadComp - Win32 Release"

# ADD CPP /Yc"stdafx.h"

!ELSEIF  "$(CFG)" == "AcadComp - Win32 Debug"

# ADD CPP /Yc"stdafx.h"

!ELSEIF  "$(CFG)" == "AcadComp - Win32 FullDebug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\tcRegistry.cpp
# End Source File
# Begin Source File

SOURCE=.\tcUtility.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\ACCMap.h
# End Source File
# Begin Source File

SOURCE=.\ACCommandReactor.h
# End Source File
# Begin Source File

SOURCE=.\ACCompBase.h
# End Source File
# Begin Source File

SOURCE=.\ACCompEntitiesGeom.h
# End Source File
# Begin Source File

SOURCE=.\ACCompRect.h
# End Source File
# Begin Source File

SOURCE=.\AcConvertColor.h
# End Source File
# Begin Source File

SOURCE=.\ACConvertName.h
# End Source File
# Begin Source File

SOURCE=.\ACCretaeLayerInfo.h
# End Source File
# Begin Source File

SOURCE=.\ACDatabaseUtility.h
# End Source File
# Begin Source File

SOURCE=.\ACDbSysVar.h
# End Source File
# Begin Source File

SOURCE=.\ACDocManager.h
# End Source File
# Begin Source File

SOURCE=.\ACEntityInfo.h
# End Source File
# Begin Source File

SOURCE=.\ACErrorInfo.h
# End Source File
# Begin Source File

SOURCE=.\ACFinally.h
# End Source File
# Begin Source File

SOURCE=.\ACProfileManager.h
# End Source File
# Begin Source File

SOURCE=.\ACResultLayers.h
# End Source File
# Begin Source File

SOURCE=.\ACRetType.h
# End Source File
# Begin Source File

SOURCE=.\ACSort.h
# End Source File
# Begin Source File

SOURCE=.\ACString.h
# End Source File
# Begin Source File

SOURCE=.\ACUIManager.h
# End Source File
# Begin Source File

SOURCE=.\AdskDMgr.h
# End Source File
# Begin Source File

SOURCE=.\DialogCompDwg.h
# End Source File
# Begin Source File

SOURCE=.\DialogSetting.h
# End Source File
# Begin Source File

SOURCE=.\DocData.h
# End Source File
# Begin Source File

SOURCE=.\InfoDwgEntity.h
# End Source File
# Begin Source File

SOURCE=.\LayoutBlkRecMap3.h
# End Source File
# Begin Source File

SOURCE=.\ListGrid.h
# End Source File
# Begin Source File

SOURCE=.\LVSortInfo.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\ResultCompEntity.h
# End Source File
# Begin Source File

SOURCE=.\rxdebug.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\StdArx.h
# End Source File
# Begin Source File

SOURCE=.\tcRegistry.h
# End Source File
# Begin Source File

SOURCE=.\tcTypeDef.h
# End Source File
# Begin Source File

SOURCE=.\tcUtility.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\AcadComp.rc2
# End Source File
# Begin Source File

SOURCE=.\res_equal.ico
# End Source File
# Begin Source File

SOURCE=.\res_not_equal.ico
# End Source File
# Begin Source File

SOURCE=.\res_only1.ico
# End Source File
# Begin Source File

SOURCE=.\res_only2.ico
# End Source File
# End Group
# Begin Source File

SOURCE=.\ObjectARX.prj
# End Source File
# End Target
# End Project
