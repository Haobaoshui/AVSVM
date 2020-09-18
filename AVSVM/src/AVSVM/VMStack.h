#pragma once

namespace AVSVM_VM
{
	const unsigned char VMStack_Type_Int = 0;
	const unsigned char VMStack_Type_Float = 1;
	const unsigned char VMStack_Type_Object = 2;

	typedef unsigned char VMStackType;

	class VMStack
	{
		VMStackType type;
		union data
		{
			int n;
			float f;
		};
	};
}

