/*******************************************************************************
ģ����		: AVSVM������
�ļ���		: calc.c
�ļ�ʵ�ֹ���	: ��ʾ����
����			: �±�ˮ
��ϵ��ʽ		:hbs@bistu.edu.cn
�汾			: 1.0

--------------------------------------------------------------------------------
�޸ļ�¼ :
�� ��        �汾     �޸���              �޸�����
2014.11.20   1.0     hbs               �����ļ�

*******************************************************************************/

#include "stdafx.h"

#include "Parser.h"
using namespace AVSVM_Compiler;


/*
�������÷���
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


