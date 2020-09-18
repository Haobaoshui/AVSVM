/*
* 符号表管理
*/
#pragma once
#include <vector>
using namespace std;

namespace AVSVM_Compiler
{

	class SymbolItem
	{
	public:
		SymbolItem( );
		~SymbolItem( );

	public:
		int m_nNextIndex;


	};

	class BlockItem
	{
	public:
		BlockItem( );
		~BlockItem( );
	public:
		int m_nSymbolIndex;
	};


	const size_t SYMTAB_HASH_BUCKET_SIZE = 100;

	class SymbolTableManager
	{
	public:
		SymbolTableManager( );
		~SymbolTableManager( );

		//块
	public:
		int Push_Block( );
		int Pop_Block( );
		int front_block( );

		//符号
		int push_SymbolItem( );
		int find_SymbolItem( );


	protected:
		unsigned int GetHash( );
	protected:
		vector<BlockItem> m_lstBlocks;//块栈
		vector<SymbolItem> m_lstSymbolItems;//符号表项栈
		vector<unsigned int> m_hashBucket;//散列值

		
	};
}

