
#include "Parser.h"


using namespace AVSVM_Compiler;

Parser::Parser()
{
}


Parser::~Parser()
{
}

bool Parser::IsTokenEnd()
{
	return m_nToken == Token_Eof;
}

void Parser::Skip(int nToken)
{
	if (m_nToken == nToken)
		m_nToken = m_lex.GetNextToken();
}


/*
基本表达式
primary_expression
	: IDENTIFIER
	| constant
	| string
	| '(' expression ')'
*/
Node* Parser::Primary_Expression(NodeValue &result)
{
	Node *pNodeResult = NULL;
	Node *pNodeLeft = NULL;
	Node *pNodeRight = NULL;

	switch (m_nToken)
	{
	case Token_ID:		
		break;
	case Token_Num:		
	case Token_String:		
	case Token_Char:
		result.Set( m_lex.m_tokenvalue );
		m_nToken = m_lex.GetNextToken( );
		break;
	case '(':
		break;
	case ')':
		break;
	case '[':
		break;
	case ']':
		break;
	case '{':
		break;
	case '}':
		break;
	case '+'://一元加
		break;
	case '-'://一元减
		break;

	case Token_type_int:
		break;
	case Token_type_float:
		break;
	case Token_type_char:
		break;
	case Token_type_string:
		break;

	
	case Token_default:
		break;
	case Token_continue:
		break;
	case Token_break:
		break;
	case Token_while:
		break;
	case Token_for:
		break;
	case Token_foreach:
		break;

	default:
		break;
	}
	return pNodeResult;
}


/*后缀
postfix_expression
: primary_expression
| postfix_expression '[' expression ']'
| postfix_expression '(' ')'
| postfix_expression '(' argument_expression_list ')'
| postfix_expression '.' IDENTIFIER
| postfix_expression PTR_OP IDENTIFIER
| postfix_expression INC_OP
| postfix_expression DEC_OP
| '(' type_name ')' '{' initializer_list '}'
| '(' type_name ')' '{' initializer_list ',' '}'
；
*/
Node* Parser::Postfix_Expression(NodeValue &result)
{
	Node *pNodeResult = NULL;
	Node *pNodeLeft = NULL;
	Node *pNodeRight = NULL;

	if (IsTokenEnd())
		return nullptr;



	pNodeLeft = Primary_Expression(result);




	/*
	U++
	U--
	*/
	while (m_nToken == Token_Op_Inc
		|| m_nToken == Token_Op_Deinc
		)
	{
		switch (m_nToken)
		{
		case Token_Op_Inc:

			break;
		case Token_Op_Deinc:

			break;


		}
		//	Skip(m_nToken);
		m_nToken = m_lex.GetNextToken();
	}

	return pNodeResult;
}

/*
unary_expression
: postfix_expression
| INC_OP unary_expression
| DEC_OP unary_expression
| unary_operator cast_expression
| SIZEOF unary_expression
| SIZEOF '(' type_name ')'
| ALIGNOF '(' type_name ')'
*/
Node* Parser::Unary_Expression(NodeValue &result)
{
	Node *pNodeResult = NULL;
	Node *pNodeLeft = NULL;
	Node *pNodeRight = NULL;

	if (IsTokenEnd())
		return nullptr;

	


	/*
	++U
	--U
	*/
	while (m_nToken == Token_Op_Inc
		|| m_nToken == Token_Op_Deinc
		)
	{
		switch (m_nToken)
		{
		case Token_Op_Inc:

			break;
		case Token_Op_Deinc:

			break;


		}
		//	Skip(m_nToken);
		m_nToken = m_lex.GetNextToken();
	}



	return pNodeResult;
}


/*
multiplicative_expression
: cast_expression
| multiplicative_expression '*' cast_expression
| multiplicative_expression '/' cast_expression
| multiplicative_expression '%' cast_expression
；
*/
Node* Parser::Multiplicative_Expression(NodeValue &result)
{
	Node *pNodeResult = NULL;
	Node *pNodeLeft = NULL;
	Node *pNodeRight = NULL;

	if (IsTokenEnd())
		return nullptr;

	NodeValue vLeft;
	NodeValue vRight;
	pNodeResult = pNodeLeft = Unary_Expression(vLeft);

	


	while (m_nToken == '*' || m_nToken == '/' || m_nToken == '%')
	{
		pNodeRight = Unary_Expression(vRight);
		Token t = m_nToken;
		NodeOP op;
		switch (t)
		{
		case '*':
			op = NodeOP_Mul;
			break;

		case '/':
			op = NodeOP_Div;
			break;

		case '%':
			op = NodeOP_Mod;
			break;


		}



		m_nToken = m_lex.GetNextToken();
		if ( pNodeLeft || pNodeRight )
		{
			if ( NULL == pNodeLeft )
				pNodeLeft = new Node( vLeft );

			if ( NULL == pNodeRight )
				pNodeRight = new Node( vRight );

			pNodeResult = new Node( op, pNodeLeft, pNodeRight );
		}
		else
		{

			switch ( t )
			{
			case '*':
				vLeft = vLeft * vRight;
				break;
			case '/':
				vLeft = vLeft / vRight;
			case '%':
				vLeft = vLeft % vRight;
				break;
			}
		}

	}
	result = vLeft;

	return pNodeResult;
}


/*
additive_expression
: multiplicative_expression
| additive_expression '+' multiplicative_expression
| additive_expression '-' multiplicative_expression
;
*/
Node* Parser::Additive_Expression(NodeValue &result)
{
	Node *pNodeResult = NULL;
	Node *pNodeLeft = NULL;
	Node *pNodeRight = NULL;

	if (IsTokenEnd())
		return nullptr;

	NodeValue vLeft;
	NodeValue vRight;
	pNodeResult = pNodeLeft = Multiplicative_Expression(vLeft);

	while (m_nToken == '+' || m_nToken == '-')
	{
		
		pNodeRight = Multiplicative_Expression(vRight);
		Token t = m_nToken;
		NodeOP op;
		switch (t)
		{
		case '+':
			op = NodeOP_Plus;
			break;
		case '-':
			op = NodeOP_Sub;
			break;
		}
		m_nToken = m_lex.GetNextToken();

		if ( pNodeLeft || pNodeRight )
		{
			if ( NULL == pNodeLeft )
				pNodeLeft = new Node( vLeft );

			if ( NULL == pNodeRight )
				pNodeRight = new Node( vRight );

			pNodeResult = new Node( op, pNodeLeft, pNodeRight );
		}
		else
		{

			switch ( t )
			{
			case '+':
				vLeft = vLeft + vRight;
				break;
			case '-':
				vLeft = vLeft - vRight;

				break;
			}
		}

	}
	result = vLeft;

	return pNodeResult;
}


/*
relational_expression
: Additive_Expression
| relational_expression '<' Additive_Expression
| relational_expression '>' Additive_Expression
| relational_expression LE_OP Additive_Expression
| relational_expression GE_OP Additive_Expression
;

*/
Node* Parser::Relational_Expression(NodeValue &result)
{
	Node *pNodeResult = NULL;
	Node *pNodeLeft = NULL;
	Node *pNodeRight = NULL;

	if (IsTokenEnd())
		return nullptr;

	bool r = false;

	pNodeResult = Additive_Expression(result);

	while (m_nToken == '>'
		|| m_nToken == '<'
		|| m_nToken == Token_Op_LessOrEqual	//<=
		|| m_nToken == Token_Op_GreatOrEqual)	//>=
	{



		switch (m_nToken)
		{
		case '>':

			break;
		case '<':

			break;
		}


		m_nToken = m_lex.GetNextToken();

	}


	return pNodeResult;
}


/*
equality_expression
: relational_expression
| equality_expression EQ_OP relational_expression
| equality_expression NE_OP relational_expression
;

*/
Node* Parser::Equality_Expression(NodeValue &result)
{
	Node *pNodeResult = NULL;
	Node *pNodeLeft = NULL;
	Node *pNodeRight = NULL;

	if (IsTokenEnd())
		return nullptr;

	

	pNodeResult = Relational_Expression(result);



	while (m_nToken == Token_Op_Equal   /*相等关系*/
		|| m_nToken == Token_Op_NotEqual)/*不相等关系*/
	{
		switch (m_nToken)
		{
		case Token_Op_Equal:

			break;
		case Token_Op_NotEqual:

			break;
		}

		m_nToken = m_lex.GetNextToken();

	}


	return pNodeResult;
}


/*
and_expression
: equality_expression
| and_expression '&' equality_expression
;

*/
Node* Parser::Logical_And_Expression(NodeValue &result)
{
	Node *pNodeResult = NULL;
	Node *pNodeLeft = NULL;
	Node *pNodeRight = NULL;

	if (IsTokenEnd())
		return nullptr;



	pNodeResult = Equality_Expression(result);



	while (m_nToken == Token_Op_And) /* && */
	{


		m_nToken = m_lex.GetNextToken();


	}


	return pNodeResult;
}


/*
logical_or_expression
: logical_and_expression
| logical_or_expression OR_OP logical_and_expression
;

*/
Node* Parser::Logical_Or_Expression(NodeValue &result)
{
	Node *pNodeResult = NULL;
	Node *pNodeLeft = NULL;
	Node *pNodeRight = NULL;

	if (IsTokenEnd())
		return nullptr;

	

	pNodeResult = Logical_And_Expression(result);



	while (m_nToken == Token_Op_Or) /* || */
	{







		m_nToken = m_lex.GetNextToken();


	}


	return pNodeResult;
}


/*
conditional_expression
: logical_or_expression
| logical_or_expression '?' expression ':' conditional_expression
;

*/
Node* Parser::Condition_Expression(NodeValue &result)
{
	Node *pNodeResult = NULL;
	Node *pNodeLeft = NULL;
	Node *pNodeRight = NULL;

	if (IsTokenEnd())
		return nullptr;

	

	pNodeResult = Logical_Or_Expression(result);

	while (m_nToken == '?')
	{
		pNodeResult = Logical_Or_Expression(result);

		//冒号
		Skip(':');

		pNodeResult = Logical_Or_Expression(result);



	}


	return pNodeResult;
}


/*
assignment_expression
: conditional_expression
| unary_expression assignment_operator assignment_expression
;

*/
Node* Parser::Assignment_Expression(NodeValue &result)
{
	Node *pNodeResult = NULL;
	Node *pNodeLeft = NULL;
	Node *pNodeRight = NULL;

	if (IsTokenEnd())
		return nullptr;

	
	pNodeResult = Condition_Expression(result);





	while (m_nToken == '='
		|| m_nToken == Token_Op_AddAssignment
		|| m_nToken == Token_Op_SubAssignment
		|| m_nToken == Token_Op_MulAssignment
		|| m_nToken == Token_Op_DivAssignment
		|| m_nToken == Token_Op_ModAssignment)
	{
		//左侧不是变量等，左值
		//	if ( pNodeLeft && !pNodeLeft->isVar() )
		//	{
		//		Error(Exp_E_ID_LEFT_INVALID_ID);
		//	}

		//	int t = m_nToken;




		pNodeResult = Assignment_Expression(result);

	}


	return pNodeResult;
}


/*
expression
: assignment_expression
| expression ',' assignment_expression
;
*/
Node* Parser::Expression( NodeValue &result )
{
	Node *pNodeResult = NULL;
	Node *pNodeLeft = NULL;
	Node *pNodeRight = NULL;

	if (IsTokenEnd())
		return nullptr;


	int nCount = 0;
	

	for (;;)
	{
		if (nCount == 1)
		{
			//	SkipToken(states, ';', result);

			//	r=body(lstTokensResult, result);
		}

		pNodeResult = Assignment_Expression(result);

		nCount++;

		if (IsTokenEnd())
			break;

	}



	return pNodeResult;
}
/*
selection_statement
	: IF '(' expression ')' statement ELSE statement
	| IF '(' expression ')' statement
	| SWITCH '(' expression ')' statement
	;
	*/
Node* Parser::Selection_Statement(NodeValue &result)
{
	Node *pNodeResult = NULL;
	Node *pNodeLeft = NULL;
	Node *pNodeRight = NULL;

	switch (m_nToken)
	{
	case Token_if:
		break;
	case Token_else:
		break;
	case Token_switch:
		break;
	case Token_case:
		break;
	}
	

	return pNodeResult;
}

/*
iteration_statement
	: WHILE '(' expression ')' statement
	| DO statement WHILE '(' expression ')' ';'
	| FOR '(' expression_statement expression_statement ')' statement
	| FOR '(' expression_statement expression_statement expression ')' statement
	| FOR '(' declaration expression_statement ')' statement
	| FOR '(' declaration expression_statement expression ')' statement
	;
	*/
Node* Parser::Iteration_Statement(NodeValue &result)
{
	Node *pNodeResult = NULL;
	Node *pNodeLeft = NULL;
	Node *pNodeRight = NULL;
	switch (m_nToken)
	{
	case Token_while:
		break;
	case Token_for:
		break;
	case Token_foreach:
		break;	
	}
	return pNodeResult;
}

/*
jump_statement
	:  CONTINUE ';'
	| BREAK ';'
	| RETURN ';'
	| RETURN expression ';'
	;
	*/
Node* Parser::Jump_Statement(NodeValue &result)
{
	Node *pNodeResult = NULL;
	Node *pNodeLeft = NULL;
	Node *pNodeRight = NULL;

	return pNodeResult;
}


/*语句
statement:
labeled_statement
| compound_statement
| expression_statement
| selection_statement
| iteration_statement
| jump_statement
;
*/
Node* Parser::Statement(NodeValue &result)
{
	Node *pNodeResult = NULL;
	Node *pNodeLeft = NULL;
	Node *pNodeRight = NULL;

	return pNodeResult;
}

/*
复合语句
*/
Node* Parser::CompoundStatement( NodeValue &result )
{
	Node *pNodeResult = NULL;
	Node *pNodeLeft = NULL;
	Node *pNodeRight = NULL;

	if (IsTokenEnd())
		return NULL;


	bool bIsCollection = false;
	if (m_nToken == '{')
	{
		Skip('{');
		bIsCollection = true;
	}

	Expression(result);

	if (bIsCollection)
	{
		Skip('}');
	}

	return pNodeResult;
}






/*函数定义
function_definition
	: declaration_specifiers declarator declaration_list compound_statement
	| declaration_specifiers declarator compound_statement
	;
*/
Node* Parser::FunctionDefinition( NodeValue &result )
{
	Node *pNodeResult = NULL;
	Node *pNodeLeft = NULL;
	Node *pNodeRight = NULL;

	m_nToken = m_lex.GetNextToken();
	while (!IsTokenEnd())
	{
		m_nToken = m_lex.GetNextToken();
	}

	return pNodeResult;
}


/*声明语句
declaration
	: declaration_specifiers ';'
	| declaration_specifiers init_declarator_list ';'
*/
Node* Parser::Declaration( NodeValue &result )
{
	Node *pNodeResult = NULL;
	Node *pNodeLeft = NULL;
	Node *pNodeRight = NULL;

	m_nToken = m_lex.GetNextToken();
	while (!IsTokenEnd())
	{
		m_nToken = m_lex.GetNextToken();
	}

	return pNodeResult;
}


/*
外部声明：由声明或函数定义组成

external_declaration
: function_definition
| declaration
;
*/

Node* Parser::ExternalDeclaration(NodeValue &result)
{
	Node *pNodeResult = NULL;
	Node *pNodeLeft = NULL;
	Node *pNodeRight = NULL;

	m_nToken = m_lex.GetNextToken();
	while (!IsTokenEnd())
	{
		pNodeLeft = FunctionDefinition(result);
		m_nToken = m_lex.GetNextToken();
	}

	return pNodeResult;
}

/*
编译单元：由外部声明组成
	
translation_unit
	: external_declaration
	| translation_unit external_declaration
	;

*/
Node* Parser::TranslationUnit( NodeValue &result )
{
	Node *pNodeResult = NULL;
	Node *pNodeLeft = NULL;
	Node *pNodeRight = NULL;

	m_nToken = m_lex.GetNextToken();
	while (!IsTokenEnd())
	{
		pNodeLeft=ExternalDeclaration(result);
		m_nToken = m_lex.GetNextToken();
	}

	return pNodeResult;
		
}



/*
编译程序
strSrcFileName：源文件名
strDestFileName：目标文件名
*/
bool Parser::Parse(const wstring strSrcFileName,
	const wstring strDestFileName)
{
	if (strSrcFileName.empty() || strDestFileName.empty())
		return false;

	m_lex.SetProgram(strSrcFileName.c_str());

	NodeValue result;
	return TranslationUnit(result)!=NULL;
}