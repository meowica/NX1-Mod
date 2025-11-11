#pragma once

namespace Util
{
	class Ini
	{
	public:
		bool Load(const std::string& path)
		{
			std::ifstream f(path.c_str());
			if (!f.is_open())
			{
				return false;
			}

			std::string line;
			std::string currentSection;

			while (std::getline(f, line))
			{
				Trim(line);

				// skip empty lines
				if (line.empty())
				{
					continue;
				}

				// skip comments
				if (line[0] == ';')
				{
					continue;
				}

				if (line[0] == '[')
				{
					const std::string::size_type end = line.find(']');
					if (end != std::string::npos)
					{
						currentSection = line.substr(1, end - 1);
					}
					continue;
				}

				const std::string::size_type eq = line.find('=');
				if (eq == std::string::npos)
				{
					continue;
				}

				std::string key = line.substr(0, eq);
				std::string value = line.substr(eq + 1);

				Trim(key);
				Trim(value);

				data_[currentSection][key] = value;
			}

			return true;
		}

		std::string GetString(const std::string& section, const std::string& key, const std::string& def = "") const
		{
			SectionMap::const_iterator itS = data_.find(section);
			if (itS == data_.end())
			{
				return def;
			}

			KeyMap::const_iterator itK = itS->second.find(key);
			if (itK == itS->second.end())
			{
				return def;
			}
			return itK->second;
		}

		int GetInt(const std::string& section, const std::string& key, int def = 0) const
		{
			const std::string v = GetString(section, key);
			if (v.empty())
			{
				return def;
			}
			return std::atoi(v.c_str());
		}

		bool GetBool(const std::string& section, const std::string& key, bool def = false) const
		{
			const std::string v = GetString(section, key);
			if (v.empty())
			{
				return def;
			}

			std::string s = v;
			for (size_t i = 0; i < s.size(); ++i)
			{
				s[i] = (char)std::tolower((unsigned char)s[i]);
			}
			return (s == "1" || s == "true");
		}

	private:
		typedef std::map<std::string, std::string> KeyMap;
		typedef std::map<std::string, KeyMap> SectionMap;

		SectionMap data_;

		static void Trim(std::string& s)
		{
			while (!s.empty() && (s[0] == ' ' || s[0] == '\t'))
			{
				s.erase(0, 1);
			}

			while (!s.empty() && (s[s.size() - 1] == ' ' || s[s.size() - 1] == '\t'))
			{
				s.erase(s.size() - 1, 1);
			}
		}
	};
}
