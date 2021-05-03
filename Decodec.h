#pragma once
//#include
/**
* ��򵥵Ļ���FFmpeg�Ľ�����
* Simplest FFmpeg Decoder
* ������ʵ������Ƶ�ļ��Ľ���(֧��HEVC��H.264��MPEG2��)��
* ����򵥵�FFmpeg��Ƶ���뷽��Ľ̡̳�
* ͨ��ѧϰ�����ӿ����˽�FFmpeg�Ľ������̡�
* This software is a simplest video decoder based on FFmpeg.
* Suitable for beginner of FFmpeg.
*
*/
#include <stdio.h>
#include "iostream"

#define __STDC_CONSTANT_MACROS
extern "C"
{
#include "libavcodec/avcodec.h"
#include "libavformat/avformat.h"
#include "libswscale/swscale.h"
};

class FfmpegDecodec
{
public:
	FfmpegDecodec();
	~FfmpegDecodec();
	static FfmpegDecodec* getInstance();
	
	//���װ
	int format2stream(AVFormatContext *pFormatCtx, char filepath[],int &videoIndex);
	//����������
	int stream2frame(AVFormatContext *pFormatCtx, AVCodecContext *pCodecCtx);
    //д264�ļ�
	int packet2H264(AVFormatContext *pFormatCtx, FILE *file, int vedioIndex);
	//����packetд��YUV�ļ�
	int frame2YUV(AVFormatContext *pFormatCtx, AVCodecContext *pCodecCtx
		, FILE *file, int videoIndex);
	
protected:
private:
	static FfmpegDecodec* instance;
	//�������ͷŵ�������ֹ�ڴ�й©
	class delInstance {
	public:
		~delInstance() {
			if (nullptr != instance)
			{
				delete instance;
				instance = nullptr;
			}
		}
	};
	static delInstance gc;
};