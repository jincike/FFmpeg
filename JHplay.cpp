// JHplay.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "iostream"
#define __STDC_CONSTANT_MACROS  //c++Ҫ���
extern "C"
{
#include "libavcodec/avcodec.h"
}

int main()
{
	std::cout << avcodec_configuration();
    return 0;
}

