namespace IRawFile
{
	struct RawFile
	{
		const char* name;
		int compressedLen;
		int len;
		const char* buffer;
	};

#ifdef IS_MP
	namespace MP
	{
		void Dump_RawFile(const RawFile* rawFile)
		{
			if (!rawFile)
				return;

			std::string assetName = rawFile->name;
			std::replace(assetName.begin(), assetName.end(), '/', '\\');

			std::string outPath = "game:\\" BASE_FOLDER "\\dump\\" + assetName;

			const int srcLen = (rawFile->compressedLen > 0) ? rawFile->compressedLen : rawFile->len;
			const bool isCompressed = (rawFile->compressedLen > 0 && rawFile->compressedLen < rawFile->len);

			std::vector<char> decompressed;

			const char* finalData = nullptr;
			size_t finalLen = 0;

			if (isCompressed)
			{
				decompressed.resize(rawFile->len);

				uLongf destLen = rawFile->len;
				int zResult = uncompress(reinterpret_cast<Bytef*>(decompressed.data()), &destLen, reinterpret_cast<const Bytef*>(rawFile->buffer), rawFile->compressedLen);

				if (zResult == Z_OK)
				{
					finalData = decompressed.data();
					finalLen = destLen;
				}
				else
				{
					// fallback if decompression failed

					finalData = rawFile->buffer;
					finalLen = rawFile->len;
				}
			}
			else
			{
				finalData = rawFile->buffer;
				finalLen = rawFile->len;
			}

			Util::FileSystem::WriteFileToDisk(outPath.c_str(), finalData, finalLen);
		}

		bool Load_RawFile(RawFile* rawFile)
		{
			if (!rawFile)
				return false;

			std::string assetName = rawFile->name;
			std::replace(assetName.begin(), assetName.end(), '/', '\\');

			std::string inPath = "game:\\" BASE_FOLDER "\\raw\\" + assetName;

			std::ifstream f(inPath, std::ios::binary | std::ios::ate);
			if (!f.is_open())
				return false;

			std::streamsize size = f.tellg();
			if (size < 0)
				return false; // file error

			f.seekg(0, std::ios::beg);

			std::vector<char> fileData(static_cast<size_t>(size));
			if (!f.read(fileData.data(), size))
				return false;

			bool shouldCompress = (rawFile->compressedLen > 0 && rawFile->compressedLen < rawFile->len);

			if (shouldCompress)
			{
				std::vector<char> compressed(static_cast<size_t>(rawFile->len));
				uLongf destLen = static_cast<uLongf>(rawFile->len);

				int status = compress(
					reinterpret_cast<Bytef*>(compressed.data()),
					&destLen,
					reinterpret_cast<const Bytef*>(fileData.data()),
					static_cast<uLongf>(size));
				if (status == Z_OK)
				{
					rawFile->buffer = new char[static_cast<size_t>(destLen)];
					memcpy((void*)rawFile->buffer, compressed.data(), static_cast<size_t>(destLen));

					rawFile->compressedLen = static_cast<int>(destLen);
					rawFile->len = static_cast<int>(size);
				}
				else
				{
					rawFile->buffer = new char[static_cast<size_t>(size)];
					memcpy((void*)rawFile->buffer, fileData.data(), static_cast<size_t>(size));

					rawFile->len = static_cast<int>(size);
					rawFile->compressedLen = 0;
				}
			}
			else
			{
				rawFile->buffer = new char[static_cast<size_t>(size)];
				memcpy((void*)rawFile->buffer, fileData.data(), static_cast<size_t>(size));

				rawFile->len = static_cast<int>(size);
				rawFile->compressedLen = 0;
			}

			return true;
		}

		Util::Hook::Detour Load_RawFilePtr_Hook;
		void Load_RawFilePtr(bool atStreamStart)
		{
			auto varRawFilePtr = *reinterpret_cast<RawFile***>(0x82CE5FCC);

			Load_RawFilePtr_Hook.Invoke<void>(atStreamStart);

			if (varRawFilePtr && *varRawFilePtr)
			{
				if (IniConfig::EnableRawFileDumper)
				{
					Dump_RawFile(*varRawFilePtr);
				}
				
				if (IniConfig::EnableRawFileLoader)
				{
					Load_RawFile(*varRawFilePtr);
				}
			}
		}

		void Load()
		{
			Load_RawFilePtr_Hook.Create(0x823190A0, Load_RawFilePtr);
		}

		void Unload()
		{
			Load_RawFilePtr_Hook.Clear();
		}
	}
#elif IS_SP
	namespace SP
	{
		void Dump_RawFile(const RawFile* rawFile)
		{
			if (!rawFile)
				return;

			std::string assetName = rawFile->name;
			std::replace(assetName.begin(), assetName.end(), '/', '\\');

			std::string outPath = "game:\\" BASE_FOLDER "\\dump\\" + assetName;

			const int srcLen = (rawFile->compressedLen > 0) ? rawFile->compressedLen : rawFile->len;
			const bool isCompressed = (rawFile->compressedLen > 0 && rawFile->compressedLen < rawFile->len);

			std::vector<char> decompressed;

			const char* finalData = nullptr;
			size_t finalLen = 0;

			if (isCompressed)
			{
				decompressed.resize(rawFile->len);

				uLongf destLen = rawFile->len;
				int zResult = uncompress(reinterpret_cast<Bytef*>(decompressed.data()), &destLen, reinterpret_cast<const Bytef*>(rawFile->buffer), rawFile->compressedLen);

				if (zResult == Z_OK)
				{
					finalData = decompressed.data();
					finalLen = destLen;
				}
				else
				{
					// fallback if decompression failed

					finalData = rawFile->buffer;
					finalLen = rawFile->len;
				}
			}
			else
			{
				finalData = rawFile->buffer;
				finalLen = rawFile->len;
			}

			Util::FileSystem::WriteFileToDisk(outPath.c_str(), finalData, finalLen);
		}

		bool Load_RawFile(RawFile* rawFile)
		{
			if (!rawFile)
				return false;

			std::string assetName = rawFile->name;
			std::replace(assetName.begin(), assetName.end(), '/', '\\');

			std::string inPath = "game:\\" BASE_FOLDER "\\raw\\" + assetName;

			std::ifstream f(inPath, std::ios::binary | std::ios::ate);
			if (!f.is_open())
				return false;

			std::streamsize size = f.tellg();
			if (size < 0)
				return false; // file error

			f.seekg(0, std::ios::beg);

			std::vector<char> fileData(static_cast<size_t>(size));
			if (!f.read(fileData.data(), size))
				return false;

			bool shouldCompress = (rawFile->compressedLen > 0 && rawFile->compressedLen < rawFile->len);

			if (shouldCompress)
			{
				std::vector<char> compressed(static_cast<size_t>(rawFile->len));
				uLongf destLen = static_cast<uLongf>(rawFile->len);

				int status = compress(
					reinterpret_cast<Bytef*>(compressed.data()),
					&destLen,
					reinterpret_cast<const Bytef*>(fileData.data()),
					static_cast<uLongf>(size));
				if (status == Z_OK)
				{
					rawFile->buffer = new char[static_cast<size_t>(destLen)];
					memcpy((void*)rawFile->buffer, compressed.data(), static_cast<size_t>(destLen));

					rawFile->compressedLen = static_cast<int>(destLen);
					rawFile->len = static_cast<int>(size);
				}
				else
				{
					rawFile->buffer = new char[static_cast<size_t>(size)];
					memcpy((void*)rawFile->buffer, fileData.data(), static_cast<size_t>(size));

					rawFile->len = static_cast<int>(size);
					rawFile->compressedLen = 0;
				}
			}
			else
			{
				rawFile->buffer = new char[static_cast<size_t>(size)];
				memcpy((void*)rawFile->buffer, fileData.data(), static_cast<size_t>(size));

				rawFile->len = static_cast<int>(size);
				rawFile->compressedLen = 0;
			}

			return true;
		}

		Util::Hook::Detour Load_RawFilePtr_Hook;
		void Load_RawFilePtr(bool atStreamStart)
		{
			auto varRawFilePtr = *reinterpret_cast<RawFile***>(0x82C6D9CC);

			Load_RawFilePtr_Hook.Invoke<void>(atStreamStart);

			if (varRawFilePtr && *varRawFilePtr)
			{
				if (IniConfig::EnableRawFileDumper)
					Dump_RawFile(*varRawFilePtr);

				if (IniConfig::EnableRawFileLoader)
					Load_RawFile(*varRawFilePtr);
			}
		}

		void Load()
		{
			Load_RawFilePtr_Hook.Create(0x82262CC8, Load_RawFilePtr);
		}

		void Unload()
		{
			Load_RawFilePtr_Hook.Clear();
		}
	}
#endif
}
