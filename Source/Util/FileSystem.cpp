namespace Util
{
	namespace FileSystem
	{
		bool FileExists(const std::string& filePath)
		{
			std::ifstream fs(filePath.c_str());
			return fs.good();
		}

		std::string ReadFileIntoString(const std::string& filePath)
		{
			std::ifstream f(filePath, std::ios::binary);
			if (!f)
				return "";
			std::string content((std::istreambuf_iterator<char>(f)), std::istreambuf_iterator<char>());
			f.close();
			return content;
		}

		void CreateNestedDirectories(const std::string& path)
		{
			if (path.empty())
				return;

			std::string temp(path);

			std::size_t pos = 0;
			if (temp.size() >= 3 &&
				std::isalpha(temp[0]) &&
				temp[1] == ':' &&
				(temp[2] == '\\' || temp[2] == '/'))
			{
				pos = 3;
			}
			else if (temp.rfind("game:\\", 0) == 0)
			{
				pos = 6;
			}

			for (; pos < temp.size(); ++pos)
			{
				if (temp[pos] == '\\' || temp[pos] == '/')
				{
					std::string sub = temp.substr(0, pos);

					if (!sub.empty())
						mkdir(sub.c_str());
				}
			}

			mkdir(temp.c_str());
		}

		bool WriteFile(const char* filePath, const char* data, std::size_t dataSize)
		{
			std::string path(filePath);

			std::size_t pos = path.find_last_of("\\/");
			if (pos != std::string::npos)
				CreateNestedDirectories(path.substr(0, pos));

			std::ofstream file(path, std::ios::binary);
			if (!file)
				return false;

			file.write(data, dataSize);
			return file.good();
		}
	}
}
