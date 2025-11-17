#pragma once

namespace Util
{
	namespace FileSystem
	{
		bool FileExists(const std::string& filePath);
		std::string ReadFileIntoString(const std::string& filePath);

		bool WriteFileToDisk(const char* filePath, const char* data, size_t dataSize);
	}
}
