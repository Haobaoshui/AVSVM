
#include "CompilerOptions.h"
#include <iostream>
#include <string>

using namespace std;
using namespace AVSVM_Compiler;

CompilerOptions gopts[ ] =
{
	//指定输出文件
	{ L"-o", CompilerOptionType_OutputFileName },
	{ L"-out", CompilerOptionType_OutputFileName },
	{ L"-output", CompilerOptionType_OutputFileName },

	//帮助
	{ L"-h" , CompilerOptionType_Help },
	{ L"-help", CompilerOptionType_Help },

	//版本
	{ L"-v" , CompilerOptionType_Version },
	{ L"-ver" , CompilerOptionType_Version },
	{ L"-version", CompilerOptionType_Version },
	
};

/*
得到选项类型
*/
CompilerOptionType AVSVM_Compiler::GetOptionType(const wchar_t* const pstr)
{
	wstring str = pstr;
	for (CompilerOptions c : gopts) {
		if (str.compare(c.pstrOption) == 0)
			return c.nType;
	}
	return CompilerOptionType_Unknown;
}
