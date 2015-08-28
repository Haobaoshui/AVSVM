#pragma once
namespace AVSVM_ISA
{
	typedef unsigned char INSTRUCTIONS;

	//指令
	const INSTRUCTIONS LOCALLOAD = 0;		//局部变量
	const INSTRUCTIONS LOCALLOAD0 = 1;		//
	const INSTRUCTIONS LOCALLOAD1 = 2;		//

	const INSTRUCTIONS LOCALSTORE = 3;		//局部变量
	const INSTRUCTIONS LOCALSTORE0 = 4;		//
	const INSTRUCTIONS LOCALSTORE1 = 5;		//

	const INSTRUCTIONS GLOBALLOAD = 6;		//全局/静态变量
	const INSTRUCTIONS GLOBALSTORE = 7;	//全局静态变量

	//栈操作
	const INSTRUCTIONS PUSH = 8;			//
	const INSTRUCTIONS POP = 9;			//
	const INSTRUCTIONS DUP = 10;			//
	const INSTRUCTIONS SWAP = 11;			//

	const INSTRUCTIONS INTADD = 12;			//加
	const INSTRUCTIONS INTSUB = 13;			//减
	const INSTRUCTIONS INTMUL = 14;			//乘
	const INSTRUCTIONS INTDIV = 15;			//除
	const INSTRUCTIONS INTMOD = 16;			//模

	const INSTRUCTIONS FLOATADD = 17;			//
	const INSTRUCTIONS FLOATSUB = 18;			//
	const INSTRUCTIONS FLOATMUL = 19;			//
	const INSTRUCTIONS FLOATDIV = 20;			//

	//条件分支指令
	const INSTRUCTIONS IFEQ = 21;			//如果相等
	const INSTRUCTIONS IFNE = 22;			//如果不等


	const INSTRUCTIONS NEW = 23;			//

	const INSTRUCTIONS RETURN = 24;			//
	const INSTRUCTIONS CALL = 25;			//

	/*
	系统函数调用，例如sin,cos,...
	形式：
	Parameter
	SYSCALL nType(4bytes)
	注意：函数参数在SYSCALL指令前面
	*/
	const INSTRUCTIONS SYS_CALL = 26;

	const INSTRUCTIONS NOP = 27;			//无操作
	const INSTRUCTIONS HALT = 28;			//停机


	//系统调用
	typedef enum tagVM_SYSFUNC
	{
		SYSFUNC_abs,		//(double x)			返回整型参数i的绝对值
		SYSFUNC_exp,		//(double x)			返回指数函数ex的值
		SYSFUNC_frexp,	//(double value,int *eptr)	返回value=x*2n中x的值,n存贮在eptr中
		SYSFUNC_ldexp,	//(double value,int exp)	返回value*2exp的值
		SYSFUNC_log,		//(double x)				返回logex的值
		SYSFUNC_log10,	//(double x)				返回log10x的值
		SYSFUNC_pow,		//(double x,double y)		返回xy的值
		SYSFUNC_pow10,	//(int p)					返回10p的值
		SYSFUNC_sqrt,		//(double x)			返回+√x的值
		SYSFUNC_acos,		//(double x)			返回x的反余弦cos-1(x)值,x为弧度
		SYSFUNC_asin,		//(double x)			返回x的反正弦sin-1(x)值,x为弧度
		SYSFUNC_atan,		//(double x)			返回x的反正切tan-1(x)值,x为弧度
		SYSFUNC_atan2,	//(double y,double x)	返回y/x的反正切tan-1(x)值,y的x为弧度
		SYSFUNC_cos,		//(double x)			返回x的余弦cos(x)值,x为弧度
		SYSFUNC_sin,		//(double x)			返回x的正弦sin(x)值,x为弧度
		SYSFUNC_tan,		//(double x)			返回x的正切tan(x)值,x为弧度
		SYSFUNC_cosh,		//(double x)			返回x的双曲余弦cosh(x)值,x为弧度
		SYSFUNC_sinh,		//(double x)			返回x的双曲正弦sinh(x)值,x为弧度
		SYSFUNC_tanh,		//(double x)			返回x的双曲正切tanh(x)值,x为弧度
		SYSFUNC_hypot,	//(double x,double y)	返回直角三角形斜边的长度(z),x和y为直角边的长度,z2=x2+y2
		SYSFUNC_ceil,		//(double x)			返回不小于x的最小整数
		SYSFUNC_floor,	//(double x)			返回不大于x的最大整数
		SYSFUNC_rand,		//()					产生一个随机数并返回这个数
		SYSFUNC_fmod,		//(double x,double y)	返回x/y的余数
		SYSFUNC_UNKNOWN

	} VM_SYSFUNC;


}

