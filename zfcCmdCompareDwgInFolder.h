#pragma once
#include "zfccommand.h"

class zfcCmdCompareDwgInFolder : public zfcCommand
{
public:
	zfcCmdCompareDwgInFolder(void);
	virtual ~zfcCmdCompareDwgInFolder(void);

	//	�}�ʔ�r�����s����
	virtual bool execute();

	/////////////////////////////////////////////////
	//
	//	Get/Set

	void setFolderOldDwg(const CString& value );
	const CString& folderOldDwg() const;

	void setFolderNewDwg( const CString& value );
	const CString& folderNewDwg() const;

	void setfolderOutput(const CString& value);
	const CString& folderOutput() const;

protected:
	//	�t�H���_���̐}�ʃt�@�C�����擾
	void getDwgInFoder( zfc::pathContainer& conPath, const CString& strFolder ) const;

	//	�t�@�C���p�X�����o
	bool findPath( zfc::pathContainer::const_iterator itPath, const CString& strFind, const zfc::pathContainer& conPath ) const;

	//	�}�ʂ��r����
	void compare( zfc::pathContainer::const_reference pairNew, const zfc::pathContainer& conPathOld ) const;

	//	�����ςݐ}�ʂ�ǉ�
	void addProcessed( const CString& strTitle, const CString& strPath );
	
	//	�������}�ʂ�ǉ�
	void addUnProcessed( const CString& strTitle, const CString& strPath );

	// ���}�ʃt�H���_�ɂ����Ȃ��t�@�C���������O�o��
	void writeLogOnlyExistInOldDwgFolder(zfc::pathContainer& conPathOld) const;

	// �V�}�ʃt�H���_�ɂ����Ȃ��t�@�C���������O�o��
	void writeLogOnlyExistInNewDwgFolder() const;

private:
	//	���}�ʊi�[�t�H���_
	CString m_strFolderOldDwg;

	//	�V�}�ʊi�[�t�H���_
	CString m_strFolderNewDwg;

	//	�o�̓t�H���_
	CString m_strFolderOutput;

	//	�����σt�@�C��
	zfc::pathContainer m_conProcessed;

	//	�������t�@�C��
	zfc::pathContainer m_conUnProcessed;
};

inline void zfcCmdCompareDwgInFolder::setFolderOldDwg(const CString& value )
{
	m_strFolderOldDwg = value;
}

inline const CString& zfcCmdCompareDwgInFolder::folderOldDwg() const
{
	return m_strFolderOldDwg;
}

inline void zfcCmdCompareDwgInFolder::setFolderNewDwg( const CString& value )
{
	m_strFolderNewDwg = value;
}

inline const CString& zfcCmdCompareDwgInFolder::folderNewDwg() const
{
	return m_strFolderNewDwg;
}

inline void zfcCmdCompareDwgInFolder::setfolderOutput(const CString& value)
{
	m_strFolderOutput = value;
}

inline const CString& zfcCmdCompareDwgInFolder::folderOutput() const
{
	return m_strFolderOutput;
}

inline void zfcCmdCompareDwgInFolder::addProcessed( const CString& strTitle, const CString& strPath )
{
	auto itp = m_conProcessed.insert( zfc::pathContainer::value_type( strTitle, strPath ) );
	assert( itp.second );
}

inline void zfcCmdCompareDwgInFolder::addUnProcessed( const CString& strTitle, const CString& strPath )
{
	auto itp = m_conUnProcessed.insert( zfc::pathContainer::value_type( strTitle, strPath ) );
	assert( itp.second );
}