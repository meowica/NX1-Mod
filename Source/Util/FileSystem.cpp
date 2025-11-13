namespace Util
{
	namespace FileSystem
	{
		bool FileExists(const std::string& filePath)
		{
			std::ifstream f(filePath.c_str());
			return f.good();
		}

		std::string ReadFileIntoString(const std::string& filePath)
		{
			std::ifstream f(filePath, std::ios::binary);
			if (!f)
			{
				printf("ReadFileIntoToString: Failed to open file: %s\n", filePath.c_str());
				return "";
			}

			std::string content((std::istreambuf_iterator<char>(f)), std::istreambuf_iterator<char>());
			f.close();
			return content;
		}
	}
}
