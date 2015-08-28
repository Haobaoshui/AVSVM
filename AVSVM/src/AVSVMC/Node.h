#pragma once
#include "NodeValue.h"



namespace AVSVM_Compiler
{
	

	

	

	class Node
	{
	public:
		Node( );
		Node( NodeValue v );
		Node( int n );
		Node( double d );
		Node( wstring str );
		Node( NodeOP op, Node *pLeft, Node *pRight );
		Node( NodeOP op, Node *pLeft );
		Node(const Node &r );
		~Node( );

	public:
		void Clean( );

	protected:
		Node *m_pLeft;
		Node *m_pRight;
		NodeValue m_value;		
	};


}

