#pragma once

namespace ILoadedSound
{
	struct XMA2DataAligned
	{
		unsigned char* p_audioData;
		unsigned int audioBytes;
	};

	struct tWAVEFORMATEX
	{
		unsigned short wFormatTag;
		unsigned short nChannels;
		unsigned int nSamplesPerSec;
		unsigned int nAvgBytesPerSec;
		unsigned short nBlockAlign;
		unsigned short wBitsPerSample;
		unsigned short cbSize;
	};

	struct XMA2WAVEFORMATEX
	{
		tWAVEFORMATEX wfx;
		unsigned short NumStreams;
		unsigned int ChannelMask;
		unsigned int SamplesEncoded;
		unsigned int BytesPerBlock;
		unsigned int PlayBegin;
		unsigned int PlayLength;
		unsigned int LoopBegin;
		unsigned int LoopLength;
		unsigned char LoopCount;
		unsigned char EncoderVersion;
		unsigned short BlockCount;
	};

	struct XA2SeekTable
	{
		unsigned int* p_seekData;
		unsigned int seekBytes;
	};

	struct PlatSound
	{
		XMA2DataAligned data;
		XMA2WAVEFORMATEX format;
		XA2SeekTable seekTable;
	};

	struct PrimedInfo
	{
		unsigned int crc;
		unsigned int dataSizeLoaded;
		unsigned int dataSizeStreamed;
		unsigned char format;
	};

	struct StreamFileNameRaw
	{
		const char* p_dir;
		const char* p_name;
	};

	struct StreamFileNamePacked
	{
		unsigned int offset;
		unsigned int length;
	};

	union StreamFileInfo
	{
		StreamFileNameRaw raw;
		StreamFileNamePacked packed;
	};

	struct StreamFileName
	{
		unsigned int fileIndex;
		StreamFileInfo info;
	};

	struct LoadedSound
	{
		const char* p_name;
		PlatSound sound;
		PrimedInfo info;
		StreamFileName streamFilename;
	};

#ifdef IS_MP
	namespace MP
	{
		void Load();
		void Unload();
	}
#elif IS_SP
	namespace SP
	{
		void Load();
		void Unload();
	}
#endif
}
