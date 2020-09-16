
#include "SymbolTable.h"

using namespace AVSVM_Compiler;

//SymbolItem
SymbolItem::SymbolItem( )
{
}


SymbolItem::~SymbolItem( )
{
}

//BlockItem
BlockItem::BlockItem( )
{
}


BlockItem::~BlockItem( )
{
}



//SymbolTableManager
SymbolTableManager::SymbolTableManager( )
{
	m_hashBucket.resize( SYMTAB_HASH_BUCKET_SIZE );
}


SymbolTableManager::~SymbolTableManager( )
{
}



int SymbolTableManager::Push_Block( )
{
	BlockItem block;
	return 0;
}


int SymbolTableManager::Pop_Block( )
{
	if ( m_lstBlocks.empty( ) )
		return 0;

	BlockItem &currentblock = m_lstBlocks.back( );
	

	return 0;
}


int SymbolTableManager::front_block( )
{
	return 0;
}

unsigned int SymbolTableManager::GetHash( )
{
	unsigned int n=0;
	return n%SYMTAB_HASH_BUCKET_SIZE;
}