#include "stdafx.h"
#include "CompilerOptions.h"

using namespace AVSVM_Compiler;

CompilerOptions gopts[ ] =
{
	//ָ������ļ�
	{ _T( "-o" ), CompilerOptionType_Help },
	{ _T( "-out" ), CompilerOptionType_Help },
	{ _T( "-output" ), CompilerOptionType_Help },

	//����
	{ _T( "-h" ), CompilerOptionType_Help },
	{ _T( "-help" ), CompilerOptionType_Help }
};

/*
�õ�ѡ������
*/
CompilerOptionType GetOptionType( const TCHAR * const pstr )
{

	return CompilerOptionType_Unknown;
}