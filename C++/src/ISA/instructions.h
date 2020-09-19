#pragma once
namespace AVSVM_ISA
{
	typedef unsigned char INSTRUCTIONS;
	typedef uint32_t INSTRUCTIONS_SYSTEM_CALL;
	
	const uint32_t PARAMETER_SIZE = 4;				//参数为4个字节

	const INSTRUCTIONS NOP = 0;				//无操作

	//加载整数类型的局部变量到栈顶
	const INSTRUCTIONS LOCAL_INT_LOAD		= 1;	//加载局部变量至栈顶,后跟局部变量索引
	const INSTRUCTIONS LOCAL_INT_LOAD_0		= 2;	//加载局部变量0至栈顶
	const INSTRUCTIONS LOCAL_INT_LOAD_1		= 3;	//加载局部变量1至栈顶

	//加载浮点数类型的局部变量到栈顶
	const INSTRUCTIONS LOCAL_FLOAT_LOAD		= 4;	//加载局部变量至栈顶
	const INSTRUCTIONS LOCAL_FLOAT_LOAD_0	= 5;	//加载局部变量0至栈顶
	const INSTRUCTIONS LOCAL_FLOAT_LOAD_1	= 6;	//加载局部变量1至栈顶

	//将整数类型的栈顶值保存到局部变量
	const INSTRUCTIONS LOCAL_INT_STORE		= 7;	//保存到局部变量,后跟局部变量索引
	const INSTRUCTIONS LOCAL_INT_STORE_0	= 8;	//保存到局部变量0至栈顶
	const INSTRUCTIONS LOCAL_INT_STORE_1	= 9;	//保存到局部变量1至栈顶

	//将浮点数类型的栈顶值保存到局部变量
	const INSTRUCTIONS LOCAL_FLOAT_STORE	= 10;	//保存到局部变量,后跟局部变量索引
	const INSTRUCTIONS LOCAL_FLOAT_STORE_0	= 11;	//将栈顶值保存到局部变量0
	const INSTRUCTIONS LOCAL_FLOAT_STORE_1	= 12;	//将栈顶值保存到局部变量1

	//将整数类型的全局变量加载到栈顶或相反
	const INSTRUCTIONS LOAD_INT				= 13;	//全局/静态变量
	const INSTRUCTIONS STORE_INT			= 14;	//将栈顶值保存到全局静态变量

	//将浮点数类型的全局变量加载到栈顶或相反
	const INSTRUCTIONS LOAD_FLOAT			= 15;	//全局/静态变量
	const INSTRUCTIONS STORE_FLOAT			= 16;	//将栈顶值保存到全局静态变量

	//栈操作
	const INSTRUCTIONS PUSH_INT				= 17;	//将整数压栈，后跟4字节整数参数
	const INSTRUCTIONS POP_INT				= 18;	//将栈顶的整数值弹栈
	const INSTRUCTIONS PUSH_FLOAT			= 19;	//将浮点压栈，后跟4字节整数参数
	const INSTRUCTIONS POP_FLOAT			= 20;	//将栈顶的浮点值弹栈

	const INSTRUCTIONS DUP					= 21;	//复制栈顶
	const INSTRUCTIONS SWAP					= 22;	//交换栈顶和次栈顶

	const INSTRUCTIONS INT_ADD				= 23;	//整数加
	const INSTRUCTIONS INT_SUB				= 24;	//整数减
	const INSTRUCTIONS INT_MUL				= 25;	//整数乘
	const INSTRUCTIONS INT_DIV				= 26;	//整数除
	const INSTRUCTIONS INT_MOD				= 27;	//整数模

	const INSTRUCTIONS FLOAT_ADD			= 28;	//浮点数加
	const INSTRUCTIONS FLOAT_SUB			= 29;	//浮点数减
	const INSTRUCTIONS FLOAT_MUL			= 30;	//浮点数乘
	const INSTRUCTIONS FLOAT_DIV			= 31;	//浮点数除

	const INSTRUCTIONS FLOAT_DIV			= 32;	//浮点数除


	const INSTRUCTIONS INT_2_FLOAT			= 33;	//将栈顶整数类型转换为浮点数类型
	const INSTRUCTIONS FLOAT_2_INT			= 34;	//将栈顶浮点数类型转换为整数类型


		

	//条件分支指令
	const INSTRUCTIONS IFEQ					= 35;	//如果相等
	const INSTRUCTIONS IFNE					= 36;	//如果不等


	//对象
	const INSTRUCTIONS NEW					= 37;	//新建对象

	//函数调用
	const INSTRUCTIONS RETURN				= 38;	//函数返回
	const INSTRUCTIONS CALL					= 39;	//函数调用

	/*
	系统函数调用，例如sin,cos,...
	形式：
	Parameter
	SYSCALL nType(4bytes)
	注意：函数参数在SYSCALL指令前面
	*/
	const INSTRUCTIONS SYS_CALL				= 40;	//系统调用

	
	const INSTRUCTIONS HALT					= 41;	//停机


	//系统函数类型	
	const INSTRUCTIONS_SYSTEM_CALL	SYSFUNC_abs = 0;		//(double x)				返回整型参数i的绝对值
	const INSTRUCTIONS_SYSTEM_CALL	SYSFUNC_exp = 1;		//(double x)				返回指数函数ex的值
	const INSTRUCTIONS_SYSTEM_CALL	SYSFUNC_frexp = 2;		//(double value,int *eptr)	返回value=x*2n中x的值,n存贮在eptr中
	const INSTRUCTIONS_SYSTEM_CALL	SYSFUNC_ldexp = 3;		//(double value,int exp)	返回value*2exp的值
	const INSTRUCTIONS_SYSTEM_CALL	SYSFUNC_log = 4;		//(double x)				返回logex的值
	const INSTRUCTIONS_SYSTEM_CALL	SYSFUNC_log10 = 5;		//(double x)				返回log10x的值
	const INSTRUCTIONS_SYSTEM_CALL	SYSFUNC_pow = 6;		//(double x,double y)		返回xy的值
	const INSTRUCTIONS_SYSTEM_CALL	SYSFUNC_pow10 = 7;		//(int p)					返回10p的值
	const INSTRUCTIONS_SYSTEM_CALL	SYSFUNC_sqrt = 8;		//(double x)				返回+√x的值
	const INSTRUCTIONS_SYSTEM_CALL	SYSFUNC_acos = 9;		//(double x)				返回x的反余弦cos-1(x)值,x为弧度
	const INSTRUCTIONS_SYSTEM_CALL	SYSFUNC_asin = 10;		//(double x)				返回x的反正弦sin-1(x)值,x为弧度
	const INSTRUCTIONS_SYSTEM_CALL	SYSFUNC_atan = 11;		//(double x)				返回x的反正切tan-1(x)值,x为弧度
	const INSTRUCTIONS_SYSTEM_CALL	SYSFUNC_atan2 = 12;		//(double y,double x)		返回y/x的反正切tan-1(x)值,y的x为弧度
	const INSTRUCTIONS_SYSTEM_CALL	SYSFUNC_cos = 13;		//(double x)				返回x的余弦cos(x)值,x为弧度
	const INSTRUCTIONS_SYSTEM_CALL	SYSFUNC_sin = 14;		//(double x)				返回x的正弦sin(x)值,x为弧度
	const INSTRUCTIONS_SYSTEM_CALL	SYSFUNC_tan = 15;		//(double x)				返回x的正切tan(x)值,x为弧度
	const INSTRUCTIONS_SYSTEM_CALL	SYSFUNC_cosh = 16;		//(double x)				返回x的双曲余弦cosh(x)值,x为弧度
	const INSTRUCTIONS_SYSTEM_CALL	SYSFUNC_sinh = 17;		//(double x)				返回x的双曲正弦sinh(x)值,x为弧度
	const INSTRUCTIONS_SYSTEM_CALL	SYSFUNC_tanh = 18;		//(double x)				返回x的双曲正切tanh(x)值,x为弧度
	const INSTRUCTIONS_SYSTEM_CALL	SYSFUNC_hypot = 19;		//(double x,double y)		返回直角三角形斜边的长度(z),x和y为直角边的长度,z2=x2+y2
	const INSTRUCTIONS_SYSTEM_CALL	SYSFUNC_ceil = 20;		//(double x)				返回不小于x的最小整数
	const INSTRUCTIONS_SYSTEM_CALL	SYSFUNC_floor = 21;		//(double x)				返回不大于x的最大整数
	const INSTRUCTIONS_SYSTEM_CALL	SYSFUNC_rand = 22;		//()						产生一个随机数并返回这个数
	const INSTRUCTIONS_SYSTEM_CALL	SYSFUNC_fmod = 23;		//(double x,double y)		返回x/y的余数
	const INSTRUCTIONS_SYSTEM_CALL	SYSFUNC_UNKNOWN = 24;




}

