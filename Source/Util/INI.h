#pragma once

namespace Util
{
	class INI
	{
	public:
		bool Load(const std::string& filePath)
		{
			std::ifstream f(filePath.c_str());
			if (!f.is_open())
				return false;

			std::string line;
			std::string currentSection;

			while (std::getline(f, line))
			{
				Trim(line);

				if (line.empty())
					continue;
				if (line[0] == ';') // comment
					continue;

				if (line[0] == '[')
				{
					const std::string::size_type end = line.find(']');
					if (end != std::string::npos)
						currentSection = line.substr(1, end - 1);
					continue;
				}

				const std::string::size_type eq = line.find('=');
				if (eq == std::string::npos)
					continue;

				std::string key = line.substr(0, eq);
				std::string value = line.substr(eq + 1);

				Trim(key);
				Trim(value);

				data_[currentSection][key] = value;
			}
			return true;
		}

		bool Unload()
		{
			data_.clear();
			return true;
		}

		std::string GetString(
			const std::string& section,
			const std::string& key,
			const std::string& def = "") const
		{
			SectionMap::const_iterator itS = data_.find(section);
			if (itS == data_.end())
				return def;

			KeyMap::const_iterator itK = itS->second.find(key);
			if (itK == itS->second.end())
				return def;
			return itK->second;
		}

		bool GetBoolean(
			const std::string& section,
			const std::string& key,
			bool def = false) const
		{
			const std::string value = GetString(section, key);
			if (value.empty())
				return def;

			std::string string = value;
			for (size_t i = 0; i < string.size(); ++i)
				string[i] = static_cast<char>(std::tolower(static_cast<unsigned char>(string[i])));
			return (string == "1" || string == "true");
		}

	private:
		typedef std::map<std::string, std::string>	KeyMap;
		typedef std::map<std::string, KeyMap>		SectionMap;

		SectionMap data_;

		static void Trim(std::string& string)
		{
			while (!string.empty() && (string[0] == ' ' || string[0] == '\t'))
				string.erase(0, 1);

			while (!string.empty() && (string[string.size() - 1] == ' ' || string[string.size() - 1] == '\t'))
				string.erase(string.size() - 1, 1);
		}
	};
}
