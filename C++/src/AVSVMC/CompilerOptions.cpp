
#include "CompilerOptions.h"
#include <iostream>
#include <string>

using namespace std;
using namespace AVSVM_Compiler;

CompilerOptions gopts[ ] =
{
	//ָ������ļ�
	{ L"-o", CompilerOptionType_OutputFileName },
	{ L"-out", CompilerOptionType_OutputFileName },
	{ L"-output", CompilerOptionType_OutputFileName },

	//����
	{ L"-h" , CompilerOptionType_Help },
	{ L"-help", CompilerOptionType_Help },

	//�汾
	{ L"-v" , CompilerOptionType_Version },
	{ L"-ver" , CompilerOptionType_Version },
	{ L"-version", CompilerOptionType_Version },
	
};

/*
�õ�ѡ������
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
