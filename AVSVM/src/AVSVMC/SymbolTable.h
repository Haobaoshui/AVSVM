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

		//¿é
	public:
		int Push_Block( );
		int Pop_Block( );
		int front_block( );

		//·ûºÅ
		int push_SymbolItem( );
		int find_SymbolItem( );


	protected:
		unsigned int GetHash( );
	protected:
		vector<BlockItem> m_lstBlocks;//¿éÕ»
		vector<SymbolItem> m_lstSymbolItems;//·ûºÅ±íÏîÕ»
		vector<unsigned int> m_hashBucket;//É¢ÁÐÖµ

		
	};
}

