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

		//��
	public:
		int Push_Block( );
		int Pop_Block( );
		int front_block( );

		//����
		int push_SymbolItem( );
		int find_SymbolItem( );


	protected:
		unsigned int GetHash( );
	protected:
		vector<BlockItem> m_lstBlocks;//��ջ
		vector<SymbolItem> m_lstSymbolItems;//���ű���ջ
		vector<unsigned int> m_hashBucket;//ɢ��ֵ

		
	};
}

