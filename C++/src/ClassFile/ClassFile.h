#pragma once

#include <string>
using namespace std;

namespace AVSVM_ClassFile
{

	//Ä§Êý
	uint32_t magicNum;

	

	class ClassFile
	{
	public:
		ClassFile();

	public:
		int Save();
		int Load();
		

	};

}