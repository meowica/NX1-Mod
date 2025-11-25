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
			{
				printf("ReadFileIntoToString: Failed to open file: %s\n", filePath.c_str());
				return "";
			}

			std::string content((std::istreambuf_iterator<char>(f)), std::istreambuf_iterator<char>());
			f.close();
			return content;
		}


		void CreateNestedDirectories(const char* path)
		{
			if (!path || !path[0])
				return;

			char tempPath[256];
			size_t len = strlen(path);
			if (len >= sizeof(tempPath))
				return;

			strcpy(tempPath, path);

			char* p = tempPath;

			// skip drive letter or known prefix's like "game:\"
			if ((p[0] && p[1] == ':' && (p[2] == '\\' || p[2] == '/')))
			{
				p += 3;
			}
			else if (strncmp(p, "game:\\", 6) == 0)
			{
				p += 6;
			}

			for (; p[0]; ++p)
			{
				if (p[0] == '\\' || p[0] == '/')
				{
					char saved = p[0];
					p[0] = '\0';
					mkdir(tempPath);
					p[0] = saved;
				}
			}

			mkdir(tempPath); // final directory
		}

		bool WriteFile(const char* filePath, const char* data, size_t dataSize)
		{
			char dirPath[256];
			strncpy(dirPath, filePath, sizeof(dirPath) - 1);
			dirPath[sizeof(dirPath) - 1] = '\0';

			char* lastSlash = strrchr(dirPath, '\\');
			if (lastSlash)
			{
				lastSlash[0] = '\0';
				CreateNestedDirectories(dirPath);
			}

			FILE* file = fopen(filePath, "wb");
			if (file)
			{
				fwrite(data, 1, dataSize, file);
				fclose(file);
				return TRUE;
			}
			else
			{
				return FALSE;
			}
		}
	}
}
