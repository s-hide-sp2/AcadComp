//////////////////////////////////////////////////////////////////////////////
// AcEditorReactor reactors, created by  [2004/02/27], , 

#if !defined(ARX__REDITORREACTOR_H__20040227_095120)
#define ARX__REDITORREACTOR_H__20040227_095120

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "dbidmap.h"
#include "aced.h"


class DAACustomEditorReactor : public AcEditorReactor
{
public:

	// Constructor / Destructor
	DAACustomEditorReactor(const bool autoInitAndRelease = true);
	virtual ~DAACustomEditorReactor();

	//{{AFX_ARX_METHODS(DAACustomEditorReactor)
	//}}AFX_ARX_METHODS

private:
	// Auto initialization and release flag.
	bool m_autoInitAndRelease;
};



#endif // !defined(ARX__REDITORREACTOR_H__20040227_095120)