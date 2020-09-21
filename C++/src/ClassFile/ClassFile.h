#pragma once

#include <string>
using namespace std;

namespace AVSVM_ClassFile
{

	//Ä§Êý
	const uint32_t magicNum=0;

	

	class ClassFile
	{
	public:
		ClassFile();

	public:
		int Save();
		int Load();
		

	};

}