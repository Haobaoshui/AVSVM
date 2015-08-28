#pragma once

#include "Lex.h"
#include "Node.h"


namespace AVSVM_Compiler
{
	#include "Node.h"

	
	

	class Parser
	{
	public:
		Parser( );
		~Parser( );

	public:
		bool Parse(const wstring strSrcFileName, const wstring strDestFileNam);

	protected:
		Node* Primary_Expression(NodeValue &result);
		Node* Postfix_Expression(NodeValue &result);
		Node* Unary_Expression(NodeValue &result);
		Node* Multiplicative_Expression(NodeValue &result);
		Node* Additive_Expression(NodeValue &result);
		Node* Relational_Expression(NodeValue &result);
		Node* Equality_Expression(NodeValue &result);
		Node* Logical_And_Expression(NodeValue &result);
		Node* Logical_Or_Expression(NodeValue &result);
		Node* Condition_Expression(NodeValue &result);
		Node* Assignment_Expression(NodeValue &result);
		Node* Expression( NodeValue &result );
		Node* Selection_Statement(NodeValue &result);
		Node* Iteration_Statement(NodeValue &result);
		Node* Jump_Statement(NodeValue &result);
		Node* Statement(NodeValue &result);
		Node* CompoundStatement( NodeValue &result );		
		Node* FunctionDefinition( NodeValue &result );
		Node* Declaration( NodeValue &result );
		Node* ExternalDeclaration(NodeValue &result);
		Node* TranslationUnit( NodeValue &result );

	protected:
		bool IsTokenEnd();
		void Skip(Token nToken);

	protected:
		Lex m_lex;
		Token m_nToken;
	};
}
