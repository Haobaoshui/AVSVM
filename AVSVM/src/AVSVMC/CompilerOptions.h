#pragma once

namespace AVSVM_Compiler
{
	//编译器选项
	enum CompilerOptionType
	{
		CompilerOptionType_OutputFileName,	//输出文件
		CompilerOptionType_Help,			//帮助
		CompilerOptionType_Unknown			//未知类型
	};
	struct CompilerOptions
	{
		TCHAR *pstrOption;
		CompilerOptionType nType;
	};

	
	CompilerOptionType GetOptionType( const TCHAR * const pstr );
}


