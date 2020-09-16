/*
* 词法分析
*/
#pragma once
#include <iostream>
#include <string>

using namespace std;

#include "TokenValue.h"

namespace AVSVM_Compiler
{
	typedef int Token;

	const Token	Token_Eof = -1;	//结束

	const Token TokenBegin = 1000;

	const Token	Token_ID = TokenBegin + 10;
	const Token	Token_Num = TokenBegin + 20;
	const Token	Token_String = TokenBegin + 30;
	const Token	Token_Char = TokenBegin + 40;




	//自增, 自减
	const Token	Token_Op_Inc = TokenBegin + 1000;			//自增
	const Token	Token_Op_Deinc = TokenBegin + 1010;		//自减


	//逻辑运算符
	const Token	Token_Op_And = TokenBegin + 2000;			//与
	const Token	Token_Op_Or = TokenBegin + 2010;			//或

	//复合赋值运算符
	const Token	Token_Op_AddAssignment = TokenBegin + 3000;		//-=
	const Token	Token_Op_SubAssignment = TokenBegin + 3010;		//+=
	const Token	Token_Op_MulAssignment = TokenBegin + 3020;		//*=
	const Token	Token_Op_DivAssignment = TokenBegin + 3030;		///=
	const Token	Token_Op_ModAssignment = TokenBegin + 3040;		//%=

	//关系运算符,包括等于(==)、不等于(!=)、小于(<)、小于等于(<=)、大于(>)、大于等于(>=)等几种
	const Token	Token_Op_Equal = TokenBegin + 4000;				//==
	const Token	Token_Op_NotEqual = TokenBegin + 4010;			//!=
	const Token	Token_Op_LessOrEqual = TokenBegin + 4020;		//<=
	const Token	Token_Op_GreatOrEqual = TokenBegin + 4030;		//>=


	//数据类型关键字
	const Token	Token_type_int = TokenBegin + 5000;				//int
	const Token	Token_type_float = TokenBegin + 5010;			//float
	const Token	Token_type_char = TokenBegin + 5020;				//char
	const Token	Token_type_string = TokenBegin + 5030;			//string

	//关键字
	const Token	Token_if = TokenBegin + 6000;					//if
	const Token	Token_else = TokenBegin + 6010;					//else
	const Token	Token_switch = TokenBegin + 6020;				//switch
	const Token	Token_case = TokenBegin + 6030;					//case
	const Token	Token_default = TokenBegin + 6040;				//default
	const Token	Token_continue = TokenBegin + 6050;				//continue
	const Token	Token_break = TokenBegin + 6060;					//break
	const Token	Token_while = TokenBegin + 6070;					//while
	const Token	Token_for = TokenBegin + 6080;					//for
	const Token	Token_foreach = TokenBegin + 6090;				//foreach

	const Token	Token_Unknown = TokenBegin + 10000;


	//关键字字符串
	const wchar_t* const cst_KeyWord_int = L"int";
	const wchar_t* const cst_KeyWord_float = L"float";
	const wchar_t* const cst_KeyWord_char = L"char";
	const wchar_t* const cst_KeyWord_string = L"string";

	const wchar_t* const cst_KeyWord_if = L"if";
	const wchar_t* const cst_KeyWord_else = L"else";
	const wchar_t* const cst_KeyWord_switch = L"switch";
	const wchar_t* const cst_KeyWord_case = L"case";
	const wchar_t* const cst_KeyWord_default = L"default";
	const wchar_t* const cst_KeyWord_continue = L"continue";
	const wchar_t* const cst_KeyWord_break = L"break";
	const wchar_t* const cst_KeyWord_while = L"while";
	const wchar_t* const cst_KeyWord_for = L"for";
	const wchar_t* const cst_KeyWord_foreach = L"foreach";


	const unsigned int MAX_ID_LENGTH = 1024;

	struct KeyWord
	{
		const wchar_t*pKeyWord;
		int nToken;
	};

	const KeyWord gKeyWords[] =
	{
		{ cst_KeyWord_int, Token_type_int },
		{ cst_KeyWord_float, Token_type_float },
		{ cst_KeyWord_float, Token_type_char },
		{ cst_KeyWord_string, Token_type_string },

		{ cst_KeyWord_if, Token_if },
		{ cst_KeyWord_else, Token_else },
		{ cst_KeyWord_switch, Token_switch },
		{ cst_KeyWord_case, Token_case },
		{ cst_KeyWord_default, Token_case },
		{ cst_KeyWord_continue, Token_continue },
		{ cst_KeyWord_break, Token_break },
		{ cst_KeyWord_while, Token_while },
		{ cst_KeyWord_for, Token_for },
		{ cst_KeyWord_foreach, Token_foreach }
	};

	

	


	class Lex
	{
	public:
		Lex();
		~Lex();

	public:
		inline bool SetProgram(const wchar_t*pstr);
	protected:
		const wchar_t*m_pstrProgram;

	public:
		Token GetNextToken();
		TokenValue m_tokenvalue;
	protected:
		void ResetTokenValue();
		
		Token m_nToken;

	protected:
		inline bool IsParseStringEnd();
		inline void MoveToNextChar();
		inline void SkipSpace();
		inline wchar_t GetChar();
		inline wchar_t GetNextChar();
		int ParserID();
		bool ParseString();
		bool ParseChar();
		bool EscapeCharacter(const wchar_t*p);
		bool ParseNumber();
		inline bool IsID(wchar_t c);
		inline bool IsNum(wchar_t c);
		int GetTokenByString(const wchar_t*p);

	protected:
		inline void IncCol();
		inline void IncRow();
		void SetPosBegin();
		void SetPosEnd();
	private:
		int m_nCurrentRow;
		int m_nCurrentCol;
	};

	bool Lex::SetProgram(const wchar_t*pstr)
	{
		m_pstrProgram = pstr;
		return NULL != pstr && NULL != *pstr;
	}

	void Lex::IncCol()
	{
		m_nCurrentCol++;
	}

	void Lex::IncRow()
	{
		m_nCurrentRow++;
		m_nCurrentCol = 0;
	}

	void Lex::MoveToNextChar()
	{
		if (m_pstrProgram && *m_pstrProgram)
		{
			IncCol();
			m_pstrProgram++;
		}
	}


	//得到当前字符
	wchar_t Lex::GetChar()
	{
		if (m_pstrProgram)
			return *m_pstrProgram;
		return 0;
	}

	//得到下一个字符
	inline wchar_t Lex::GetNextChar()
	{
		if (m_pstrProgram && *m_pstrProgram)
			return *(m_pstrProgram + 1);
		return 0;
	}

	bool Lex::IsID(wchar_t c)
	{
		return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_';
	}

	bool Lex::IsNum(wchar_t c)
	{
		return  c >= '0' && c <= '9';
	}


	/*
	是否到了解析字符串的末尾
	*/
	bool Lex::IsParseStringEnd()
	{
		if (NULL == m_pstrProgram || NULL == *m_pstrProgram)

			return true;
		return false;
	}

	/*
	* 跳过空格
	*/
	inline void Lex::SkipSpace()
	{
		while (m_pstrProgram && *m_pstrProgram == ' ')
		{
			IncCol();
			MoveToNextChar();
		}
	}
}