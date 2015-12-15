//////////////////////////////////////////////////////////////////////////////
// AcEditorReactor reactors, created by  [2004/02/27], , 

#include "StdAfx.h"
#include "StdArx.h"


//-----------------------------------------------------------------------------
DAACustomEditorReactor::DAACustomEditorReactor(const bool autoInitAndRelease)
{
#ifdef OARXWIZDEBUG
	acutPrintf ("\nOARXWIZDEBUG - () called.");
#endif // OARXWIZDEBUG

	m_autoInitAndRelease = autoInitAndRelease;
	if (m_autoInitAndRelease)
		if (NULL != acedEditor)
			acedEditor->addReactor(this);
		else
			m_autoInitAndRelease = false;
}

//-----------------------------------------------------------------------------
DAACustomEditorReactor::~DAACustomEditorReactor()
{
#ifdef OARXWIZDEBUG
	acutPrintf ("\nOARXWIZDEBUG - DAACustomEditorReactor::~DAACustomEditorReactor() called.");
#endif // OARXWIZDEBUG

	if (m_autoInitAndRelease)
		if (NULL != acedEditor)
			acedEditor->removeReactor(this);
}

