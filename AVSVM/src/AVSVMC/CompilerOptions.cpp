#include "stdafx.h"
#include "CompilerOptions.h"

using namespace AVSVM_Compiler;

CompilerOptions gopts[ ] =
{
	//指定输出文件
	{ _T( "-o" ), CompilerOptionType_Help },
	{ _T( "-out" ), CompilerOptionType_Help },
	{ _T( "-output" ), CompilerOptionType_Help },

	//帮助
	{ _T( "-h" ), CompilerOptionType_Help },
	{ _T( "-help" ), CompilerOptionType_Help }
};

/*
得到选项类型
*/
CompilerOptionType GetOptionType( const TCHAR * const pstr )
{

	return CompilerOptionType_Unknown;
}