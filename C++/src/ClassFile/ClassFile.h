#pragma once

#include <string>
using namespace std;

namespace AVSVM_ClassFile
{

	//ħ��
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