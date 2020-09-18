#pragma once
#include <vector>
using namespace std;

namespace AVSVM_Compiler
{
	class ErrorItem
	{
	public:
		ErrorItem( );
		~ErrorItem( );
	};

	class ErrorManager
	{
	public:
		ErrorManager( );
		~ErrorManager( );

	public:
		vector<ErrorItem> m_lstError;
	};
}
