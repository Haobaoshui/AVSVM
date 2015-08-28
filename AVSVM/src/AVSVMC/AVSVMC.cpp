/*******************************************************************************
模块名		: AVSVM编译器
文件名		: calc.c
文件实现功能	: 演示函数
作者			: 郝保水
联系方式		:hbs@bistu.edu.cn
版本			: 1.0

--------------------------------------------------------------------------------
修改记录 :
日 期        版本     修改人              修改内容
2014.11.20   1.0     hbs               创建文件

*******************************************************************************/

#include "stdafx.h"

#include "Parser.h"
using namespace AVSVM_Compiler;


/*
编译器用法：
avsvmc options files
*/
int _tmain(int argc, _TCHAR* argv[])
{
	if ( argc < 2 )
		return 1;

	for (int i = 1; i < argc; i++)
	{
		Parser parser;
		wstring s = argv[i];
		wstring d = s;
		parser.Parse(s, d);

	}

	return 0;
}


