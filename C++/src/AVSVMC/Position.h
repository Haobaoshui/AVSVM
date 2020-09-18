#pragma once

namespace AVSVM_Compiler
{

	//TokenŒª÷√
	struct TokenPosition
	{
		TokenPosition( )
		{
			nBeginRow = nBeginCol = nEndRow = nEndCol = -1;
		}
		int nBeginRow;
		int nBeginCol;

		int nEndRow;
		int nEndCol;

	};
}
