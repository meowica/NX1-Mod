#include "IStructuredDataDefSet.h"

namespace IStructuredDataDefSet
{
	static const char* StructuredDataTypeCategoryToString(StructuredDataTypeCategory type)
	{
		switch (type)
		{
		case DATA_INT:
			return "int";
		case DATA_BYTE:
			return "byte";
		case DATA_BOOL:
			return "bool";
		case DATA_STRING:
			return "string";
		case DATA_ENUM:
			return "enum";
		case DATA_STRUCT:
			return "struct";
		case DATA_INDEXED_ARRAY:
			return "indexed_array";
		case DATA_ENUM_ARRAY:
			return "enum_array";
		case DATA_FLOAT:
			return "float";
		case DATA_SHORT:
			return "short";
		default:
			return "unknown";
		}
	}

	void Dump_StructuredDataType(std::ostringstream& oss, const StructuredDataType& type)
	{
		oss << "type = " << StructuredDataTypeCategoryToString(type.type) << "\n";

		switch (type.type)
		{
		case DATA_STRING:
			oss << "stringLength = " << type.u.stringDataLength << "\n";
			break;
		case DATA_ENUM:
			oss << "enumIndex = " << type.u.enumIndex << "\n";
			break;
		case DATA_STRUCT:
			oss << "structIndex = " << type.u.structIndex << "\n";
			break;
		case DATA_INDEXED_ARRAY:
			oss << "indexedArrayIndex = " << type.u.indexedArrayIndex << "\n";
			break;
		case DATA_ENUM_ARRAY:
			oss << "enumArrayIndex = " << type.u.enumedArrayIndex << "\n";
			break;
		default:
			break;
		}
	}

#ifdef IS_MP
	namespace MP
	{
		void Dump_StructuredDataDefSet(const StructuredDataDefSet* structuredDataDefSet)
		{
			if (!structuredDataDefSet)
				return;

			std::string assetName = structuredDataDefSet->name;
			std::replace(assetName.begin(), assetName.end(), '/', '\\');

			std::string outPath = "game:\\" BASE_FOLDER "\\dump\\" + assetName;

			std::ostringstream oss;
			oss << "STRUCTURED_DATA_DEF_SET " << structuredDataDefSet->name << "\n{\n";

			for (unsigned int d = 0; d < structuredDataDefSet->defCount; ++d)
			{
				const StructuredDataDef& def = structuredDataDefSet->defs[d];
				oss << "    DEF " << d << "\n    {\n";
				oss << "        version = " << def.version << "\n";
				oss << "        checksum = 0x" << std::hex << def.formatChecksum << std::dec << "\n";
				oss << "        ENUMS " << def.enumCount << "\n        {\n";
				for (int i = 0; i < def.enumCount; ++i)
				{
					const StructuredDataEnum& e = def.enums[i];
					oss << "            ENUM " << i << "\n            {\n";
					oss << "                entryCount = " << e.entryCount << "\n";
					oss << "                reservedCount = " << e.reservedEntryCount << "\n";
					oss << "                entries:\n";
					for (int j = 0; j < e.entryCount; ++j)
					{
						const StructuredDataEnumEntry& entry = e.entries[j];
						oss << "                    " << entry.index << " = \"" << entry.string << "\"\n";
					}
					oss << "            }\n";
				}
				oss << "        }\n";
				oss << "        STRUCTS " << def.structCount << "\n        {\n";
				for (int i = 0; i < def.structCount; ++i)
				{
					const StructuredDataStruct& s = def.structs[i];
					oss << "            STRUCT " << i << " size=" << s.size
						<< " bitOffset=" << s.bitOffset << "\n            {\n";
					for (int p = 0; p < s.propertyCount; ++p)
					{
						const StructuredDataStructProperty& prop = s.properties[p];
						oss << "                PROPERTY " << p << "\n                {\n";
						oss << "                    name = \"" << prop.name << "\"\n";
						oss << "                    offset = " << prop.offset << "\n";
						Dump_StructuredDataType(oss, prop.type);
						oss << "                }\n";
					}
					oss << "            }\n";
				}
				oss << "        }\n";
				oss << "        INDEXED_ARRAYS " << def.indexedArrayCount << "\n        {\n";
				for (int i = 0; i < def.indexedArrayCount; ++i)
				{
					const StructuredDataIndexedArray& a = def.indexedArrays[i];
					oss << "            INDEXED_ARRAY " << i << "\n            {\n";
					oss << "                size = " << a.arraySize << "\n";
					Dump_StructuredDataType(oss, a.elementType);
					oss << "                elementSize = " << a.elementSize << "\n";
					oss << "            }\n";
				}
				oss << "        }\n";
				oss << "        ENUMED_ARRAYS " << def.enumedArrayCount << "\n        {\n";
				for (int i = 0; i < def.enumedArrayCount; ++i)
				{
					const StructuredDataEnumedArray& a = def.enumedArrays[i];
					oss << "            ENUMED_ARRAY " << i << "\n            {\n";
					oss << "                enumIndex = " << a.enumIndex << "\n";
					Dump_StructuredDataType(oss, a.elementType);
					oss << "                elementSize = " << a.elementSize << "\n";
					oss << "            }\n";
				}
				oss << "        }\n";
				oss << "        ROOT_TYPE\n        {\n";
				Dump_StructuredDataType(oss, def.rootType);
				oss << "        }\n";
				oss << "        SIZE = " << def.size << "\n";
				oss << "    }\n";
			}
			oss << "}\n";

			const std::string data = oss.str();
			Util::FileSystem::WriteFile(outPath.c_str(), data.c_str(), data.size());
		}

		Util::Hook::Detour Load_StructuredDataDefSetPtr_Hook;
		void Load_StructuredDataDefSetPtr(bool atStreamStart)
		{
			auto varStructuredDataDefSetPtr = *reinterpret_cast<StructuredDataDefSet***>(0x82CE6D88);

			Load_StructuredDataDefSetPtr_Hook.Invoke<void>(atStreamStart);

			if (varStructuredDataDefSetPtr && *varStructuredDataDefSetPtr)
			{
				//if (IniConfig::EnableStructuredDataDefSetDumper)
					Dump_StructuredDataDefSet(*varStructuredDataDefSetPtr);
				//if (IniConfig::EnableStructuredDataDefSetLoader)
				//	Load_StructuredDataDefSet(*varStructuredDataDefSetPtr);
			}
		}

		void Load()
		{
			Load_StructuredDataDefSetPtr_Hook.Create(0x8231B088, Load_StructuredDataDefSetPtr);
		}

		void Unload()
		{
			Load_StructuredDataDefSetPtr_Hook.Clear();
		}
	}
#elif IS_SP
	namespace SP
	{
		void Dump_StructuredDataDefSet(const StructuredDataDefSet* structuredDataDefSet)
		{
			if (!structuredDataDefSet)
				return;

			std::string assetName = structuredDataDefSet->name;
			std::replace(assetName.begin(), assetName.end(), '/', '\\');

			std::string outPath = "game:\\" BASE_FOLDER "\\dump\\" + assetName;

			std::ostringstream oss;
			oss << "STRUCTURED_DATA_DEF_SET " << structuredDataDefSet->name << "\n{\n";

			for (unsigned int d = 0; d < structuredDataDefSet->defCount; ++d)
			{
				const StructuredDataDef& def = structuredDataDefSet->defs[d];
				oss << "    DEF " << d << "\n    {\n";
				oss << "        version = " << def.version << "\n";
				oss << "        checksum = 0x" << std::hex << def.formatChecksum << std::dec << "\n";
				oss << "        ENUMS " << def.enumCount << "\n        {\n";
				for (int i = 0; i < def.enumCount; ++i)
				{
					const StructuredDataEnum& e = def.enums[i];
					oss << "            ENUM " << i << "\n            {\n";
					oss << "                entryCount = " << e.entryCount << "\n";
					oss << "                reservedCount = " << e.reservedEntryCount << "\n";
					oss << "                entries:\n";
					for (int j = 0; j < e.entryCount; ++j)
					{
						const StructuredDataEnumEntry& entry = e.entries[j];
						oss << "                    " << entry.index << " = \"" << entry.string << "\"\n";
					}
					oss << "            }\n";
				}
				oss << "        }\n";
				oss << "        STRUCTS " << def.structCount << "\n        {\n";
				for (int i = 0; i < def.structCount; ++i)
				{
					const StructuredDataStruct& s = def.structs[i];
					oss << "            STRUCT " << i << " size=" << s.size
						<< " bitOffset=" << s.bitOffset << "\n            {\n";
					for (int p = 0; p < s.propertyCount; ++p)
					{
						const StructuredDataStructProperty& prop = s.properties[p];
						oss << "                PROPERTY " << p << "\n                {\n";
						oss << "                    name = \"" << prop.name << "\"\n";
						oss << "                    offset = " << prop.offset << "\n";
						Dump_StructuredDataType(oss, prop.type);
						oss << "                }\n";
					}
					oss << "            }\n";
				}
				oss << "        }\n";
				oss << "        INDEXED_ARRAYS " << def.indexedArrayCount << "\n        {\n";
				for (int i = 0; i < def.indexedArrayCount; ++i)
				{
					const StructuredDataIndexedArray& a = def.indexedArrays[i];
					oss << "            INDEXED_ARRAY " << i << "\n            {\n";
					oss << "                size = " << a.arraySize << "\n";
					Dump_StructuredDataType(oss, a.elementType);
					oss << "                elementSize = " << a.elementSize << "\n";
					oss << "            }\n";
				}
				oss << "        }\n";
				oss << "        ENUMED_ARRAYS " << def.enumedArrayCount << "\n        {\n";
				for (int i = 0; i < def.enumedArrayCount; ++i)
				{
					const StructuredDataEnumedArray& a = def.enumedArrays[i];
					oss << "            ENUMED_ARRAY " << i << "\n            {\n";
					oss << "                enumIndex = " << a.enumIndex << "\n";
					Dump_StructuredDataType(oss, a.elementType);
					oss << "                elementSize = " << a.elementSize << "\n";
					oss << "            }\n";
				}
				oss << "        }\n";
				oss << "        ROOT_TYPE\n        {\n";
				Dump_StructuredDataType(oss, def.rootType);
				oss << "        }\n";
				oss << "        SIZE = " << def.size << "\n";
				oss << "    }\n";
			}
			oss << "}\n";

			const std::string data = oss.str();
			Util::FileSystem::WriteFile(outPath.c_str(), data.c_str(), data.size());
		}

		Util::Hook::Detour Load_StructuredDataDefSetPtr_Hook;
		void Load_StructuredDataDefSetPtr(bool atStreamStart)
		{
			auto varStructuredDataDefSetPtr = *reinterpret_cast<StructuredDataDefSet***>(0x82C6E788);

			Load_StructuredDataDefSetPtr_Hook.Invoke<void>(atStreamStart);

			if (varStructuredDataDefSetPtr && *varStructuredDataDefSetPtr)
			{
				//if (IniConfig::EnableStructuredDataDefSetDumper)
					Dump_StructuredDataDefSet(*varStructuredDataDefSetPtr);
				//if (IniConfig::EnableStructuredDataDefSetLoader)
				//	Load_StructuredDataDefSet(*varStructuredDataDefSetPtr);
			}
		}

		void Load()
		{
			Load_StructuredDataDefSetPtr_Hook.Create(0x82264CB0, Load_StructuredDataDefSetPtr);
		}

		void Unload()
		{
			Load_StructuredDataDefSetPtr_Hook.Clear();
		}
	}
#endif
}
