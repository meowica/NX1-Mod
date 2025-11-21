namespace ILocalizeEntry
{
	struct LocalizeEntry
	{
		const char* value;
		const char* name;
	};

#ifdef IS_MP
	namespace MP
	{
		void Dump_LocalizeEntry(const LocalizeEntry* localizeEntry)
		{
			if (!localizeEntry)
				return;

			std::string name(localizeEntry->name);
			std::string value(localizeEntry->value);

			std::string prefix = "default";
			std::string key = name;

			size_t pos = name.find('_');
			if (pos != std::string::npos)
			{
				prefix = name.substr(0, pos);
				key = name.substr(pos + 1);
			}

			std::transform(prefix.begin(), prefix.end(), prefix.begin(), ::tolower);
			std::string outPath = "game:\\NX1-Mod\\dump\\english\\localizedstrings\\" + prefix + ".str";

			std::string fileData;

			{
				FILE* rf = fopen(outPath.c_str(), "rb");
				if (rf)
				{
					fseek(rf, 0, SEEK_END);
					long size = ftell(rf);
					fseek(rf, 0, SEEK_SET);
					fileData.resize(size);
					fread((void*)fileData.data(), 1, size, rf);
					fclose(rf);
				}
			}

			{
				std::string findStr = "REFERENCE           " + key;
				if (fileData.find(findStr) != std::string::npos)
					return; // dupe
			}

			std::string out = fileData;

			if (out.empty())
			{
				out +=
					"// Note to translators:\r\n"
					"// If a sentence is the same in your language then please change it to \"#same\"\r\n"
					"//\r\n"
					"// eg:\r\n"
					"// LANG_ENGLISH  \"HALT\"\r\n"
					"// LANG_GERMAN   \"#same\"\r\n"
					"//\r\n"
					"// (This is so we can tell which strings have been signed-off as ok to be the same words for QA\r\n"
					"//  and because we do not store duplicate strings, which will then get exported again next time\r\n"
					"//  as being untranslated.)\r\n"
					"//\r\n";

				out += "VERSION             \"1\"\r\n";
				out += "CONFIG              \"C:\\trees\\nx1\\bin\\StringEd.cfg\"\r\n";
				out += "FILENOTES           \"";
				out += "Dumped by NX1-Mod.";
				out += "\"\r\n\r\n";
			}

			std::string escaped = value;
			for (size_t pos = 0; (pos = escaped.find('"', pos)) != std::string::npos;)
			{
				escaped.insert(pos, "\"");
				pos += 2;
			}

			{
				const char* marker = "ENDMARKER";
				size_t mpos = out.find(marker);
				if (mpos != std::string::npos)
					out.erase(mpos);
			}

			out += "REFERENCE           " + key + "\r\n";
			out += "LANG_ENGLISH        \"" + escaped + "\"\r\n\r\n";
			out += "ENDMARKER\n\n";

			Util::FileSystem::WriteFile(outPath.c_str(), out.c_str(), out.size());
		}

		Util::Hook::Detour Load_LocalizeEntryPtr_Hook;
		void Load_LocalizeEntryPtr(bool atStreamStart)
		{
			auto varLocalizeEntryPtr = *reinterpret_cast<LocalizeEntry***>(0x82CE6F5C);

			Load_LocalizeEntryPtr_Hook.Invoke<void>(atStreamStart);

			if (varLocalizeEntryPtr && *varLocalizeEntryPtr)
			{
				if (IniConfig::EnableLocalizeEntryDumper)
					Dump_LocalizeEntry(*varLocalizeEntryPtr);
				//if (IniConfig::EnableLocalizeEntryLoader)
				//	Load_LocalizeEntry(*varLocalizeEntryPtr);
			}
		}

		void Load()
		{
			Load_LocalizeEntryPtr_Hook.Create(0x82316100, Load_LocalizeEntryPtr);
		}

		void Unload()
		{
			Load_LocalizeEntryPtr_Hook.Clear();
		}
	}
#elif IS_SP
	namespace SP
	{
		void Dump_LocalizeEntry(const LocalizeEntry* localizeEntry)
		{
			if (!localizeEntry)
				return;

			std::string name(localizeEntry->name);
			std::string value(localizeEntry->value);

			std::string prefix = "default";
			std::string key = name;

			size_t pos = name.find('_');
			if (pos != std::string::npos)
			{
				prefix = name.substr(0, pos);
				key = name.substr(pos + 1);
			}

			std::transform(prefix.begin(), prefix.end(), prefix.begin(), ::tolower);
			std::string outPath = "game:\\NX1-Mod\\dump\\english\\localizedstrings\\" + prefix + ".str";

			std::string fileData;

			{
				FILE* rf = fopen(outPath.c_str(), "rb");
				if (rf)
				{
					fseek(rf, 0, SEEK_END);
					long size = ftell(rf);
					fseek(rf, 0, SEEK_SET);
					fileData.resize(size);
					fread((void*)fileData.data(), 1, size, rf);
					fclose(rf);
				}
			}

			{
				std::string findStr = "REFERENCE           " + key;
				if (fileData.find(findStr) != std::string::npos)
					return; // dupe
			}

			std::string out = fileData;

			if (out.empty())
			{
				out +=
					"// Note to translators:\r\n"
					"// If a sentence is the same in your language then please change it to \"#same\"\r\n"
					"//\r\n"
					"// eg:\r\n"
					"// LANG_ENGLISH  \"HALT\"\r\n"
					"// LANG_GERMAN   \"#same\"\r\n"
					"//\r\n"
					"// (This is so we can tell which strings have been signed-off as ok to be the same words for QA\r\n"
					"//  and because we do not store duplicate strings, which will then get exported again next time\r\n"
					"//  as being untranslated.)\r\n"
					"//\r\n";

				out += "VERSION             \"1\"\r\n";
				out += "CONFIG              \"C:\\trees\\nx1\\bin\\StringEd.cfg\"\r\n";
				out += "FILENOTES           \"";
				out += "Dumped by NX1-Mod.";
				out += "\"\r\n\r\n";
			}

			std::string escaped = value;
			for (size_t pos = 0; (pos = escaped.find('"', pos)) != std::string::npos;)
			{
				escaped.insert(pos, "\"");
				pos += 2;
			}

			{
				const char* marker = "ENDMARKER";
				size_t mpos = out.find(marker);
				if (mpos != std::string::npos)
					out.erase(mpos);
			}

			out += "REFERENCE           " + key + "\r\n";
			out += "LANG_ENGLISH        \"" + escaped + "\"\r\n\r\n";
			out += "ENDMARKER\n\n";

			Util::FileSystem::WriteFile(outPath.c_str(), out.c_str(), out.size());
		}

		Util::Hook::Detour Load_LocalizeEntryPtr_Hook;
		void Load_LocalizeEntryPtr(bool atStreamStart)
		{
			auto varLocalizeEntryPtr = *reinterpret_cast<LocalizeEntry***>(0x82C6E95C);

			Load_LocalizeEntryPtr_Hook.Invoke<void>(atStreamStart);

			if (varLocalizeEntryPtr && *varLocalizeEntryPtr)
			{
				if (IniConfig::EnableLocalizeEntryDumper)
					Dump_LocalizeEntry(*varLocalizeEntryPtr);
				//if (IniConfig::EnableLocalizeEntryLoader)
				//	Load_LocalizeEntry(*varLocalizeEntryPtr);
			}
		}

		void Load()
		{
			Load_LocalizeEntryPtr_Hook.Create(0x8225FD28, Load_LocalizeEntryPtr);
		}

		void Unload()
		{
			Load_LocalizeEntryPtr_Hook.Clear();
		}
	}
#endif
}
