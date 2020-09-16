/*
* 编译器选项
*/
#pragma once

namespace AVSVM_Compiler
{

	enum CompilerOptionType
	{
		CompilerOptionType_OutputFileName,	//输出文件
		CompilerOptionType_Help,			//帮助
		CompilerOptionType_Version,			//版本
		CompilerOptionType_Unknown			//未知类型
	};
	struct CompilerOptions
	{
		const wchar_t *pstrOption;
		CompilerOptionType nType;
	};

	
	CompilerOptionType GetOptionType( const wchar_t* const pstr );
}


