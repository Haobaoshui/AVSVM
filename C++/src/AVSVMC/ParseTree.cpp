
#include "ParseTree.h"

using namespace AVSVM_Compiler;

#include "..\ClassFile\ClassFile.h"
using namespace AVSVM_ClassFile;

ParseTree::ParseTree( )
{
	m_pRoot = NULL;
}


ParseTree::~ParseTree( )
{
}
bool ParseTree::Parse( const wstring strSrcFileName, const wstring strDestFileNam )
{
	return Parser::Parse( strSrcFileName, strDestFileNam );
}
	
bool ParseTree::GenByteCodes( )
{
	if ( NULL == m_pRoot )
		return false;

//	ClassFile cf;
	return true;
}