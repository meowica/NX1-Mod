// We could use an external lib for this, but i think this is better... for now atleast
// We're also pretty limited as this is in C++03-11
//
// Credits:
// - Lil Poop - idea + inital work
// - Wemino - for https://github.com/Wemino/EchoPatch, I used a few things from this patch

namespace IniHelper
{
	static void StripComments(std::string& str)
	{
		for (size_t i = 0; i < str.size(); ++i)
		{
			if (str[i] == '\r')
			{
				str.erase(i, 1); --i;
			}
		}

		size_t commentPos = std::string::npos;
		for (size_t i = 0; i < str.size(); ++i)
		{
			if (str[i] == ';')
			{
				if (i == 0 || isspace(static_cast<unsigned char>(str[i - 1])))
				{
					commentPos = i;
					break;
				}
			}
		}

		if (commentPos != std::string::npos)
		{
			str.erase(commentPos);
		}

		size_t start = 0;
		while (start < str.size() && (str[start] == ' ' || str[start] == '\t'))
		{
			++start;
		}

		size_t end = str.size();
		while (end > start && (str[end - 1] == ' ' || str[end - 1] == '\t'))
		{
			--end;
		}

		if (start > 0 || end < str.size())
		{
			str = str.substr(start, end - start);
		}
	}

	static void SanitizeIniValue(std::string& s)
	{
		std::string out;
		out.reserve(s.size());

		for (size_t i = 0; i < s.size(); ++i)
		{
			unsigned char ch = (unsigned char)s[i];
			if (ch == '\r' || ch == '\n')
			{
				break;
			}

			if (ch < 32 && ch != '\t' && ch != ' ')
			{
				continue;
			}

			out.push_back((char)ch);
		}

		while (!out.empty() && (out.back() == ' ' || out.back() == '\t'))
		{
			out.pop_back();
		}

		size_t start = 0;
		while (start < out.size() && (out[start] == ' ' || out[start] == '\t'))
		{
			++start;
		}

		if (start > 0)
		{
			out = out.substr(start);
		}

		if (out.size() > 256)
		{
			out.resize(256);
		}

		s.swap(out);
	}
}

namespace IniConfig
{
	// =============================
	// Ini Variables
	// =============================

	// Intro
	static bool ShowIntroMovie = true;

	// Drawing
	static bool ShowWatermark = true;
	static bool ShowFPSCounter = false;

	static void ReadConfig()
	{
		const char* g_configPath = Util::String::VA("game:\\" BASE_FOLDER "\\NX1-Mod.ini");

		HANDLE hFile = CreateFileA(g_configPath, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
		if (hFile == INVALID_HANDLE_VALUE)
		{
			return;
		}

		DWORD fileSize = GetFileSize(hFile, NULL);
		if (fileSize == INVALID_FILE_SIZE || fileSize == 0)
		{
			CloseHandle(hFile);
			return;
		}

		std::string content;
		content.resize(fileSize);

		DWORD bytesRead = 0;
		BOOL ok = ReadFile(hFile, &content[0], fileSize, &bytesRead, NULL);

		CloseHandle(hFile);

		if (!ok || bytesRead == 0)
		{
			return;
		}

		if (bytesRead < content.size())
		{
			content.resize(bytesRead);
		}

		std::string normalized;
		normalized.reserve(content.size());
		for (size_t i = 0; i < content.size(); ++i)
		{
			char ch = content[i];
			if (ch == '\r')
			{
				continue;
			}

			normalized.push_back(ch);
		}

		// Remove BOM if present
		if (normalized.size() >= 3 && (unsigned char)normalized[0] == 0xEF && (unsigned char)normalized[1] == 0xBB && (unsigned char)normalized[2] == 0xBF)
		{
			normalized.erase(0, 3);
		}

		size_t start = 0;
		while (start <= normalized.size())
		{
			size_t end = normalized.find('\n', start);
			std::string line = (end == std::string::npos) ? normalized.substr(start) : normalized.substr(start, end - start);
			start = (end == std::string::npos) ? normalized.size() + 1 : end + 1;

			IniHelper::StripComments(line);
			if (line.empty())
			{
				continue;
			}

			if (line[0] == ';')
			{
				continue;
			}

			if (line[0] == '[')
			{
				continue;
			}

			size_t equalPos = line.find('=');
			if (equalPos == std::string::npos)
			{
				continue;
			}

			std::string key = line.substr(0, equalPos);
			std::string value = line.substr(equalPos + 1);

			IniHelper::StripComments(key);
			IniHelper::StripComments(value);
			IniHelper::SanitizeIniValue(key);
			IniHelper::SanitizeIniValue(value);

			if (key == "ShowIntroMovie")
			{
				ShowIntroMovie = (value == "true" || value == "1");
			}
			else if (key == "ShowWatermark")
			{
				ShowWatermark = (value == "true" || value == "1");
			}
			else if (key == "ShowFPSCounter")
			{
				ShowFPSCounter = (value == "true" || value == "1");
			}
		}
	}

	bool ShouldShowIntroMovie()
	{
		return ShowIntroMovie;
	}

	bool ShouldShowWatermark()
	{
		return ShowWatermark;
	}

	bool ShouldShowFPSCounter()
	{
		return ShowFPSCounter;
	}

#ifdef IS_MULTIPLAYER
	namespace Multiplayer
	{
		void Load()
		{
			ReadConfig();
		}

		void Unload()
		{
			// nothing
		}
	}
#elif IS_SINGLEPLAYER
	namespace Singleplayer
	{
		void Load()
		{
			ReadConfig();
		}

		void Unload()
		{
			// nothing
		}
	}
#endif
}