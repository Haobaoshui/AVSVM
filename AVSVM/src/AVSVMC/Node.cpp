
#include "Node.h"

using namespace AVSVM_Compiler;

Node::Node( )
{
	m_pLeft = NULL;
	m_pRight = NULL;	
}

Node::Node( NodeValue v )
{
	m_pLeft = NULL;
	m_pRight = NULL;
	m_value.Set( v );
}
Node::Node( int n )
{
	m_pLeft = NULL;
	m_pRight = NULL;
	m_value.Set( n );
}

Node::Node( double d )
{
	m_pLeft = NULL;
	m_pRight = NULL;
	m_value.Set( d);
}

Node::Node( wstring str )
{
	m_pLeft = NULL;
	m_pRight = NULL;
	m_value.Set( str );
}




Node::Node( NodeOP op, Node *pLeft, Node *pRight )
{
	
	m_pLeft = pLeft;
	m_pRight = pRight;
	m_value.Set( op );
}

Node::Node( NodeOP op, Node *pLeft )
{
	m_pLeft = pLeft;
	m_pRight = NULL;
	m_value.Set( op );
}

Node::Node( const Node &r )
{
	m_pLeft = r.m_pLeft;
	m_pRight = r.m_pRight;
	m_value = r.m_value;
}

Node::~Node( )
{
	
	Clean( );
}



void Node::Clean( )
{
	if ( m_pLeft )
		delete m_pLeft;

	if ( m_pRight )
		delete m_pRight;	
}