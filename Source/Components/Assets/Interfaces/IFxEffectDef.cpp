#include "IFxEffectDef.h"

namespace IFxEffectDef
{
	static void JsonEscape(const char* s, std::ostringstream& o)
	{
		o << "\"";
		while (*s)
		{
			unsigned char c = *s++;
			switch (c)
			{
			case '\"': o << "\\\""; break;
			case '\\': o << "\\\\"; break;
			case '\b': o << "\\b"; break;
			case '\f': o << "\\f"; break;
			case '\n': o << "\\n"; break;
			case '\r': o << "\\r"; break;
			case '\t': o << "\\t"; break;
			default:
				if (c < 0x20)
					o << "\\u" << std::hex << std::setw(4) << std::setfill('0') << (int)c << std::dec;
				else
					o << c;
			}
		}
		o << "\"";
	}

	static void Indent(std::ostringstream& oss, int level)
	{
		for (int i = 0; i < level; i++)
			oss << "  ";
	}

	void Dump_FxFloatRange(const FxFloatRange& v, const char* name, std::ostringstream& oss, int level)
	{
		Indent(oss, level);
		oss << "\"" << name << "\": {\n";

		Indent(oss, level + 1);
		oss << "\"base\": " << v.base << ",\n";

		Indent(oss, level + 1);
		oss << "\"amplitude\": " << v.amplitude << "\n";

		Indent(oss, level);
		oss << "}";
	}

	void Dump_FxIntRange(const FxIntRange& v, const char* name, std::ostringstream& oss, int level)
	{
		Indent(oss, level);
		oss << "\"" << name << "\": {\n";

		Indent(oss, level + 1);
		oss << "\"base\": " << v.base << ",\n";

		Indent(oss, level + 1);
		oss << "\"amplitude\": " << v.amplitude << "\n";

		Indent(oss, level);
		oss << "}";
	}

	void Dump_FxSpawnDef(const FxSpawnDef& spawn, int flags, std::ostringstream& oss, int level)
	{
		bool isLooping = (flags & 1) != 0; // TODO: real determination

		Indent(oss, level);
		oss << "\"spawn\": {\n";

		if (isLooping)
		{
			Indent(oss, level + 1);
			oss << "\"intervalMsec\": " << spawn.looping.intervalMsec << ",\n";

			Indent(oss, level + 1);
			oss << "\"count\": " << spawn.looping.count << "\n";
		}
		else
		{
			Dump_FxIntRange(spawn.oneShot.count, "count", oss, level + 1);
			oss << "\n";
		}

		Indent(oss, level);
		oss << "}";
	}

	void Dump_FxElemDef(const FxElemDef& elem, std::ostringstream& oss, int level)
	{
		Indent(oss, level);
		oss << "{\n";

		Indent(oss, level + 1);
		oss << "\"flags\": " << elem.flags << ",\n";

		Dump_FxSpawnDef(elem.spawn, elem.flags, oss, level + 1);
		oss << ",\n";

		Dump_FxFloatRange(elem.spawnRange, "spawnRange", oss, level + 1);
		oss << ",\n";

		Dump_FxFloatRange(elem.fadeInRange, "fadeInRange", oss, level + 1);
		oss << ",\n";

		Dump_FxFloatRange(elem.fadeOutRange, "fadeOutRange", oss, level + 1);
		oss << ",\n";

		Indent(oss, level + 1);
		oss << "\"spawnFrustumCullRadius\": " << elem.spawnFrustumCullRadius << ",\n";

		Dump_FxIntRange(elem.spawnDelayMsec, "spawnDelayMsec", oss, level + 1);
		oss << ",\n";

		Dump_FxIntRange(elem.lifeSpanMsec, "lifeSpanMsec", oss, level + 1);
		oss << "\n";

		Indent(oss, level);
		oss << "}";
	}

#ifdef IS_MP
	namespace MP
	{
		void Dump_FxEffectDef(const FxEffectDef* fx)
		{
			if (!fx)
				return;

			std::string assetName = fx->name;
			std::replace(assetName.begin(), assetName.end(), '/', '\\');

			std::string outPath = "game:\\" BASE_FOLDER "\\dump\\fx\\" + assetName + ".json";

			std::ostringstream oss;
			oss << "{\n";

			Indent(oss, 1);
			oss << "\"name\": ";
			JsonEscape(fx->name, oss);
			oss << ",\n";

			Indent(oss, 1);
			oss << "\"flags\": " << fx->flags << ",\n";

			Indent(oss, 1);
			oss << "\"totalSize\": " << fx->totalSize << ",\n";

			Indent(oss, 1);
			oss << "\"msecLoopingLife\": " << fx->msecLoopingLife << ",\n";

			Indent(oss, 1);
			oss << "\"elemDefs\": [\n";

			int total = fx->elemDefCountLooping + fx->elemDefCountOneShot + fx->elemDefCountEmission;

			for (int i = 0; i < total; i++)
			{
				Dump_FxElemDef(fx->elemDefs[i], oss, 2);
				if (i + 1 < total)
					oss << ",";
				oss << "\n";
			}

			Indent(oss, 1);
			oss << "]\n";
			oss << "}\n";

			std::string outStr = oss.str();
			Util::FileSystem::WriteFile(outPath.c_str(), outStr.c_str(), outStr.size());
		}

		Util::Hook::Detour Load_FxEffectDefHandle_Hook;
		void Load_FxEffectDefHandle(bool atStreamStart)
		{
			auto varFxEffectDefHandle = *reinterpret_cast<FxEffectDef***>(0x82CE6648);

			Load_FxEffectDefHandle_Hook.Invoke<void>(atStreamStart);

			if (varFxEffectDefHandle && *varFxEffectDefHandle)
			{
				if (IniConfig::EnableFxEffectDefDumper)
					Dump_FxEffectDef(*varFxEffectDefHandle);
				//if (IniConfig::EnableFxEffectDefLoader)
				//	Load_FxEffectDef(*varFxEffectDefHandle);
			}
		}

		void Load()
		{
			Load_FxEffectDefHandle_Hook.Create(0x823264C0, Load_FxEffectDefHandle);
		}

		void Unload()
		{
			Load_FxEffectDefHandle_Hook.Clear();
		}
	}
#elif IS_SP
	namespace SP
	{
		void Dump_FxEffectDef(const FxEffectDef* fx)
		{
			if (!fx)
				return;

			std::string assetName = fx->name;
			std::replace(assetName.begin(), assetName.end(), '/', '\\');

			std::string outPath = "game:\\" BASE_FOLDER "\\dump\\fx\\" + assetName + ".json";

			std::ostringstream oss;
			oss << "{\n";

			Indent(oss, 1);
			oss << "\"name\": ";
			JsonEscape(fx->name, oss);
			oss << ",\n";

			Indent(oss, 1);
			oss << "\"flags\": " << fx->flags << ",\n";

			Indent(oss, 1);
			oss << "\"totalSize\": " << fx->totalSize << ",\n";

			Indent(oss, 1);
			oss << "\"msecLoopingLife\": " << fx->msecLoopingLife << ",\n";

			Indent(oss, 1);
			oss << "\"elemDefs\": [\n";

			int total = fx->elemDefCountLooping + fx->elemDefCountOneShot + fx->elemDefCountEmission;

			for (int i = 0; i < total; i++)
			{
				Dump_FxElemDef(fx->elemDefs[i], oss, 2);
				if (i + 1 < total)
					oss << ",";
				oss << "\n";
			}

			Indent(oss, 1);
			oss << "]\n";
			oss << "}\n";

			std::string outStr = oss.str();
			Util::FileSystem::WriteFile(outPath.c_str(), outStr.c_str(), outStr.size());
		}

		Util::Hook::Detour Load_FxEffectDefHandle_Hook;
		void Load_FxEffectDefHandle(bool atStreamStart)
		{
			auto varFxEffectDefHandle = *reinterpret_cast<FxEffectDef***>(0x82C6E048);

			Load_FxEffectDefHandle_Hook.Invoke<void>(atStreamStart);

			if (varFxEffectDefHandle && *varFxEffectDefHandle)
			{
				if (IniConfig::EnableFxEffectDefDumper)
					Dump_FxEffectDef(*varFxEffectDefHandle);
				//if (IniConfig::EnableFxEffectDefLoader)
				//	Load_FxEffectDef(*varFxEffectDefHandle);
			}
		}

		void Load()
		{
			Load_FxEffectDefHandle_Hook.Create(0x82270130, Load_FxEffectDefHandle);
		}

		void Unload()
		{
			Load_FxEffectDefHandle_Hook.Clear();
		}
	}
#endif
}
