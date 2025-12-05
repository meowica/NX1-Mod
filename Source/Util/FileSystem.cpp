namespace Util
{
	namespace FileSystem
	{
		bool FileExists(const std::string& filePath)
		{
			std::ifstream fs(filePath.c_str());
			return fs.is_open();
		}

		std::string ReadFileIntoString(const std::string& filePath)
		{
			std::ifstream f(filePath.c_str(), std::ios::binary);
			if (!f)
				return std::string();

			std::string content;

			f.seekg(0, std::ios::end);
			content.reserve(static_cast<size_t>(f.tellg()));
			f.seekg(0, std::ios::beg);

			content.assign(std::istreambuf_iterator<char>(f), std::istreambuf_iterator<char>());
			return content;
		}

		void CreateNestedDirectories(const std::string& filePath)
		{
			if (filePath.empty())
				return;

			std::string temp(filePath);

			std::size_t pos = 0;

			if (temp.size() >= 3 && std::isalpha(temp[0]) && temp[1] == ':' && (temp[2] == '\\' || temp[2] == '/'))
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

			std::ofstream file(path.c_str(), std::ios::binary | std::ios::trunc);
			if (!file)
				return false;

			file.write(data, dataSize);
			return file.good();
		}
	}
}
