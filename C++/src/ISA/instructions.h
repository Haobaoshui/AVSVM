#pragma once
namespace AVSVM_ISA
{
	typedef unsigned char INSTRUCTIONS;
	typedef uint32_t INSTRUCTIONS_SYSTEM_CALL;
	
	const uint32_t PARAMETER_SIZE = 4;				//����Ϊ4���ֽ�

	const INSTRUCTIONS NOP = 0;				//�޲���

	//�����������͵ľֲ�������ջ��
	const INSTRUCTIONS LOCAL_INT_LOAD		= 1;	//���ؾֲ�������ջ��,����ֲ���������
	const INSTRUCTIONS LOCAL_INT_LOAD_0		= 2;	//���ؾֲ�����0��ջ��
	const INSTRUCTIONS LOCAL_INT_LOAD_1		= 3;	//���ؾֲ�����1��ջ��

	//���ظ��������͵ľֲ�������ջ��
	const INSTRUCTIONS LOCAL_FLOAT_LOAD		= 4;	//���ؾֲ�������ջ��
	const INSTRUCTIONS LOCAL_FLOAT_LOAD_0	= 5;	//���ؾֲ�����0��ջ��
	const INSTRUCTIONS LOCAL_FLOAT_LOAD_1	= 6;	//���ؾֲ�����1��ջ��

	//���������͵�ջ��ֵ���浽�ֲ�����
	const INSTRUCTIONS LOCAL_INT_STORE		= 7;	//���浽�ֲ�����,����ֲ���������
	const INSTRUCTIONS LOCAL_INT_STORE_0	= 8;	//���浽�ֲ�����0��ջ��
	const INSTRUCTIONS LOCAL_INT_STORE_1	= 9;	//���浽�ֲ�����1��ջ��

	//�����������͵�ջ��ֵ���浽�ֲ�����
	const INSTRUCTIONS LOCAL_FLOAT_STORE	= 10;	//���浽�ֲ�����,����ֲ���������
	const INSTRUCTIONS LOCAL_FLOAT_STORE_0	= 11;	//��ջ��ֵ���浽�ֲ�����0
	const INSTRUCTIONS LOCAL_FLOAT_STORE_1	= 12;	//��ջ��ֵ���浽�ֲ�����1

	//���������͵�ȫ�ֱ������ص�ջ�����෴
	const INSTRUCTIONS LOAD_INT				= 13;	//ȫ��/��̬����
	const INSTRUCTIONS STORE_INT			= 14;	//��ջ��ֵ���浽ȫ�־�̬����

	//�����������͵�ȫ�ֱ������ص�ջ�����෴
	const INSTRUCTIONS LOAD_FLOAT			= 15;	//ȫ��/��̬����
	const INSTRUCTIONS STORE_FLOAT			= 16;	//��ջ��ֵ���浽ȫ�־�̬����

	//ջ����
	const INSTRUCTIONS PUSH_INT				= 17;	//������ѹջ�����4�ֽ���������
	const INSTRUCTIONS POP_INT				= 18;	//��ջ��������ֵ��ջ
	const INSTRUCTIONS PUSH_FLOAT			= 19;	//������ѹջ�����4�ֽ���������
	const INSTRUCTIONS POP_FLOAT			= 20;	//��ջ���ĸ���ֵ��ջ

	const INSTRUCTIONS DUP					= 21;	//����ջ��
	const INSTRUCTIONS SWAP					= 22;	//����ջ���ʹ�ջ��

	const INSTRUCTIONS INT_ADD				= 23;	//������
	const INSTRUCTIONS INT_SUB				= 24;	//������
	const INSTRUCTIONS INT_MUL				= 25;	//������
	const INSTRUCTIONS INT_DIV				= 26;	//������
	const INSTRUCTIONS INT_MOD				= 27;	//����ģ

	const INSTRUCTIONS FLOAT_ADD			= 28;	//��������
	const INSTRUCTIONS FLOAT_SUB			= 29;	//��������
	const INSTRUCTIONS FLOAT_MUL			= 30;	//��������
	const INSTRUCTIONS FLOAT_DIV			= 31;	//��������

	const INSTRUCTIONS FLOAT_DIV			= 32;	//��������


	const INSTRUCTIONS INT_2_FLOAT			= 33;	//��ջ����������ת��Ϊ����������
	const INSTRUCTIONS FLOAT_2_INT			= 34;	//��ջ������������ת��Ϊ��������


		

	//������ָ֧��
	const INSTRUCTIONS IFEQ					= 35;	//������
	const INSTRUCTIONS IFNE					= 36;	//�������


	//����
	const INSTRUCTIONS NEW					= 37;	//�½�����

	//��������
	const INSTRUCTIONS RETURN				= 38;	//��������
	const INSTRUCTIONS CALL					= 39;	//��������

	/*
	ϵͳ�������ã�����sin,cos,...
	��ʽ��
	Parameter
	SYSCALL nType(4bytes)
	ע�⣺����������SYSCALLָ��ǰ��
	*/
	const INSTRUCTIONS SYS_CALL				= 40;	//ϵͳ����

	
	const INSTRUCTIONS HALT					= 41;	//ͣ��


	//ϵͳ��������	
	const INSTRUCTIONS_SYSTEM_CALL	SYSFUNC_abs = 0;		//(double x)				�������Ͳ���i�ľ���ֵ
	const INSTRUCTIONS_SYSTEM_CALL	SYSFUNC_exp = 1;		//(double x)				����ָ������ex��ֵ
	const INSTRUCTIONS_SYSTEM_CALL	SYSFUNC_frexp = 2;		//(double value,int *eptr)	����value=x*2n��x��ֵ,n������eptr��
	const INSTRUCTIONS_SYSTEM_CALL	SYSFUNC_ldexp = 3;		//(double value,int exp)	����value*2exp��ֵ
	const INSTRUCTIONS_SYSTEM_CALL	SYSFUNC_log = 4;		//(double x)				����logex��ֵ
	const INSTRUCTIONS_SYSTEM_CALL	SYSFUNC_log10 = 5;		//(double x)				����log10x��ֵ
	const INSTRUCTIONS_SYSTEM_CALL	SYSFUNC_pow = 6;		//(double x,double y)		����xy��ֵ
	const INSTRUCTIONS_SYSTEM_CALL	SYSFUNC_pow10 = 7;		//(int p)					����10p��ֵ
	const INSTRUCTIONS_SYSTEM_CALL	SYSFUNC_sqrt = 8;		//(double x)				����+��x��ֵ
	const INSTRUCTIONS_SYSTEM_CALL	SYSFUNC_acos = 9;		//(double x)				����x�ķ�����cos-1(x)ֵ,xΪ����
	const INSTRUCTIONS_SYSTEM_CALL	SYSFUNC_asin = 10;		//(double x)				����x�ķ�����sin-1(x)ֵ,xΪ����
	const INSTRUCTIONS_SYSTEM_CALL	SYSFUNC_atan = 11;		//(double x)				����x�ķ�����tan-1(x)ֵ,xΪ����
	const INSTRUCTIONS_SYSTEM_CALL	SYSFUNC_atan2 = 12;		//(double y,double x)		����y/x�ķ�����tan-1(x)ֵ,y��xΪ����
	const INSTRUCTIONS_SYSTEM_CALL	SYSFUNC_cos = 13;		//(double x)				����x������cos(x)ֵ,xΪ����
	const INSTRUCTIONS_SYSTEM_CALL	SYSFUNC_sin = 14;		//(double x)				����x������sin(x)ֵ,xΪ����
	const INSTRUCTIONS_SYSTEM_CALL	SYSFUNC_tan = 15;		//(double x)				����x������tan(x)ֵ,xΪ����
	const INSTRUCTIONS_SYSTEM_CALL	SYSFUNC_cosh = 16;		//(double x)				����x��˫������cosh(x)ֵ,xΪ����
	const INSTRUCTIONS_SYSTEM_CALL	SYSFUNC_sinh = 17;		//(double x)				����x��˫������sinh(x)ֵ,xΪ����
	const INSTRUCTIONS_SYSTEM_CALL	SYSFUNC_tanh = 18;		//(double x)				����x��˫������tanh(x)ֵ,xΪ����
	const INSTRUCTIONS_SYSTEM_CALL	SYSFUNC_hypot = 19;		//(double x,double y)		����ֱ��������б�ߵĳ���(z),x��yΪֱ�Ǳߵĳ���,z2=x2+y2
	const INSTRUCTIONS_SYSTEM_CALL	SYSFUNC_ceil = 20;		//(double x)				���ز�С��x����С����
	const INSTRUCTIONS_SYSTEM_CALL	SYSFUNC_floor = 21;		//(double x)				���ز�����x���������
	const INSTRUCTIONS_SYSTEM_CALL	SYSFUNC_rand = 22;		//()						����һ������������������
	const INSTRUCTIONS_SYSTEM_CALL	SYSFUNC_fmod = 23;		//(double x,double y)		����x/y������
	const INSTRUCTIONS_SYSTEM_CALL	SYSFUNC_UNKNOWN = 24;




}

