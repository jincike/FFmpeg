// JHplay.cpp : �������̨Ӧ�ó������ڵ㡣
//
#include "stdafx.h"
#include "iostream"
#include "Decodec.h"

#define __STDC_CONSTANT_MACROS
extern "C"
{
#include "libavcodec/avcodec.h"
#include "libavformat/avformat.h"
#include "libswscale/swscale.h"
};
#define RETSUCESS 0
class FfmpegDecodec;
int main()
{
	//��ʼ��
	AVFormatContext	*pFormatCtx;
	int				videoIndex;//��Ƶ����indexcode
	AVCodecContext	*pCodecCtx;
	
	av_register_all();
	avformat_network_init();
	pFormatCtx = avformat_alloc_context();
	//��ȡ����������
	FfmpegDecodec* instanceDecodec = FfmpegDecodec::getInstance();
	char filepath[] = "Titanic.ts";//�����ļ�·��

	//1��ȡ��װ������
	instanceDecodec->format2stream(pFormatCtx, filepath, videoIndex);

	//2���װ��H264
	FILE* fp_H264 = nullptr;
	int ret = fopen_s(&fp_H264,"test1.h264", "wb+");
	if (RETSUCESS == ret)
	{
		//AVFormatContext	*pFormatCtxTmp = new AVFormatContext;
		//memcpy(pFormatCtxTmp, pFormatCtx, sizeof(AVFormatContext));
		//pFormatCtxֻ��av_read_frameһ�Σ�����ſ�frame2YUV�Ͳ��ܽ���ͬһ��pFormatCtx
		instanceDecodec->packet2H264(pFormatCtx, fp_H264, videoIndex);
		//delete pFormatCtxTmp;
	}
	fclose(fp_H264);

	//3��ȡ����������
	pCodecCtx = pFormatCtx->streams[videoIndex]->codec;
	instanceDecodec->stream2frame(pFormatCtx, pCodecCtx);

	//4���뵽yuv�ļ�
	FILE* fp_yuv = nullptr;
	int retYuv = fopen_s(&fp_yuv,"test2.yuv", "wb+");
	if (RETSUCESS == retYuv)
	{
		instanceDecodec->frame2YUV(pFormatCtx, pCodecCtx, fp_yuv, videoIndex);
	}
	fclose(fp_yuv);

	avcodec_close(pCodecCtx);
	avformat_close_input(&pFormatCtx);//��ȡ��ַ����������
    return 0;
}

