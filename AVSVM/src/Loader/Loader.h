#pragma once
#include <string>
using namespace std;

namespace AVSVM_VM
{
	class VM;
	class Loader
	{
	public:
		Loader( );
		~Loader( );

	public:
		int LoadBytecodes(VM &vm, const  wstring strBytecodesFileName/*字节码文件名*/);
	};
}

