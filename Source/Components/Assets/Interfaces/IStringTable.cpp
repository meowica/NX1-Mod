namespace IStringTable
{
	struct StringTableCell
	{
		const char* string;
		int hash;
	};

	struct StringTable
	{
		const char* name;
		int columnCount;
		int rowCount;
		StringTableCell* values;
	};

#ifdef IS_MP
	namespace MP
	{
		void Dump_StringTable(const StringTable* stringTable)
		{
			if (!stringTable)
				return;

			std::string assetName = stringTable->name;
			std::replace(assetName.begin(), assetName.end(), '/', '\\');

			std::string outPath = "game:\\" BASE_FOLDER "\\dump\\" + assetName;

			std::string csvTable;
			csvTable.reserve(stringTable->rowCount * stringTable->columnCount * 32); // rough preallocation

			for (int row = 0; row < stringTable->rowCount; ++row)
			{
				for (int col = 0; col < stringTable->columnCount; ++col)
				{
					const char* str = stringTable->values[row * stringTable->columnCount + col].string;
					csvTable += str ? str : "";

					if (col < stringTable->columnCount - 1)
						csvTable += ',';
				}
				csvTable += '\n';
			}

			Util::FileSystem::WriteFile(outPath.c_str(), csvTable.c_str(), csvTable.size());
		}

		Util::Hook::Detour Load_StringTablePtr_Hook;
		void Load_StringTablePtr(bool atStreamStart)
		{
			auto varStringTablePtr = *reinterpret_cast<StringTable***>(0x82CE655C);

			Load_StringTablePtr_Hook.Invoke<void>(atStreamStart);

			if (varStringTablePtr && *varStringTablePtr)
			{
				if (IniConfig::EnableStringTableDumper)
					Dump_StringTable(*varStringTablePtr);
				//if (IniConfig::EnableStringTableLoader)
				//	Load_StringTable(*varStringTablePtr);
			}
		}

		void Load()
		{
			Load_StringTablePtr_Hook.Create(0x82319928, Load_StringTablePtr);
		}

		void Unload()
		{
			Load_StringTablePtr_Hook.Clear();
		}
	}
#elif IS_SP
	namespace SP
	{
		void Dump_StringTable(const StringTable* stringTable)
		{
			if (!stringTable)
				return;

			std::string assetName = stringTable->name;
			std::replace(assetName.begin(), assetName.end(), '/', '\\');

			std::string outPath = "game:\\" BASE_FOLDER "\\dump\\" + assetName;

			std::string csvTable;
			csvTable.reserve(stringTable->rowCount * stringTable->columnCount * 32);

			for (int row = 0; row < stringTable->rowCount; ++row)
			{
				for (int col = 0; col < stringTable->columnCount; ++col)
				{
					const char* str = stringTable->values[row * stringTable->columnCount + col].string;
					csvTable += str ? str : "";

					if (col < stringTable->columnCount - 1)
						csvTable += ',';
				}
				csvTable += '\n';
			}

			Util::FileSystem::WriteFile(outPath.c_str(), csvTable.c_str(), csvTable.size());
}

		Util::Hook::Detour Load_StringTablePtr_Hook;
		void Load_StringTablePtr(bool atStreamStart)
		{
			auto varStringTablePtr = *reinterpret_cast<StringTable***>(0x82C6DF5C);

			Load_StringTablePtr_Hook.Invoke<void>(atStreamStart);

			if (varStringTablePtr && *varStringTablePtr)
			{
				if (IniConfig::EnableStringTableDumper)
					Dump_StringTable(*varStringTablePtr);
				//if (IniConfig::EnableStringTableLoader)
				//	Load_StringTable(*varStringTablePtr);
			}
		}

		void Load()
		{
			Load_StringTablePtr_Hook.Create(0x82263550, Load_StringTablePtr);
		}

		void Unload()
		{
			Load_StringTablePtr_Hook.Clear();
		}
	}
#endif
}
