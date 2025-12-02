#include "ISndVfCurve.h"

namespace ISndVfCurve
{
#ifdef IS_MP
	namespace MP
	{
		void Dump_SndVfCurve(const SndVfCurve* sndVfCurve)
		{
			if (!sndVfCurve)
				return;

			std::string assetName = sndVfCurve->p_filename;
			std::replace(assetName.begin(), assetName.end(), '/', '\\');

			std::string outPath = "game:\\" BASE_FOLDER "\\dump\\snd_vf_curve\\" + assetName + ".json";

			std::ostringstream oss;
			oss << "{\n";
			oss << "  \"filename\": \"" << assetName << "\",\n";
			oss << "  \"knotCount\": " << sndVfCurve->sndCurve.knotCount << ",\n";
			oss << "  \"knots\": [\n";

			unsigned short count = std::min<unsigned short>(sndVfCurve->sndCurve.knotCount, 16);

			for (unsigned short i = 0; i < count; ++i)
			{
				float x = sndVfCurve->sndCurve.knots[i][0];
				float y = sndVfCurve->sndCurve.knots[i][1];

				oss << "    { \"x\": " << x << ", \"y\": " << y << " }";
				if (i + 1 < count)
					oss << ",";
				oss << "\n";
			}

			oss << "  ]\n";
			oss << "}\n";

			std::string outStr = oss.str();
			Util::FileSystem::WriteFile(outPath.c_str(), outStr.c_str(), outStr.size());
		}

		Util::Hook::Detour Load_SndVfCurvePtr_Hook;
		void Load_SndVfCurvePtr(bool atStreamStart)
		{
			auto varSndVfCurvePtr = *reinterpret_cast<SndVfCurve***>(0x82CE6A20);

			Load_SndVfCurvePtr_Hook.Invoke<void>(atStreamStart);

			if (varSndVfCurvePtr && *varSndVfCurvePtr)
			{
				if (IniConfig::EnableSndVfCurveDumper)
					Dump_SndVfCurve(*varSndVfCurvePtr);
				//if (IniConfig::EnableSndVfCurveLoader)
				//	Load_SndVfCurve(*varSndVfCurvePtr);
			}
		}

		void Load()
		{
			Load_SndVfCurvePtr_Hook.Create(0x822F8688, Load_SndVfCurvePtr);
		}

		void Unload()
		{
			Load_SndVfCurvePtr_Hook.Clear();
		}
	}
#elif IS_SP
	namespace SP
	{
		void Dump_SndVfCurve(const SndVfCurve* sndVfCurve)
		{
			if (!sndVfCurve)
				return;

			std::string assetName = sndVfCurve->p_filename;
			std::replace(assetName.begin(), assetName.end(), '/', '\\');

			std::string outPath = "game:\\" BASE_FOLDER "\\dump\\snd_vf_curve\\" + assetName + ".json";

			std::ostringstream oss;
			oss << "{\n";
			oss << "  \"filename\": \"" << assetName << "\",\n";
			oss << "  \"knotCount\": " << sndVfCurve->sndCurve.knotCount << ",\n";
			oss << "  \"knots\": [\n";

			unsigned short count = std::min<unsigned short>(sndVfCurve->sndCurve.knotCount, 16);

			for (unsigned short i = 0; i < count; ++i)
			{
				float x = sndVfCurve->sndCurve.knots[i][0];
				float y = sndVfCurve->sndCurve.knots[i][1];

				oss << "    { \"x\": " << x << ", \"y\": " << y << " }";
				if (i + 1 < count)
					oss << ",";
				oss << "\n";
			}

			oss << "  ]\n";
			oss << "}\n";

			std::string outStr = oss.str();
			Util::FileSystem::WriteFile(outPath.c_str(), outStr.c_str(), outStr.size());
		}

		Util::Hook::Detour Load_SndVfCurvePtr_Hook;
		void Load_SndVfCurvePtr(bool atStreamStart)
		{
			auto varSndVfCurvePtr = *reinterpret_cast<SndVfCurve***>(0x82C6E420);

			Load_SndVfCurvePtr_Hook.Invoke<void>(atStreamStart);

			if (varSndVfCurvePtr && *varSndVfCurvePtr)
			{
				if (IniConfig::EnableSndVfCurveDumper)
					Dump_SndVfCurve(*varSndVfCurvePtr);
				//if (IniConfig::EnableSndVfCurveLoader)
				//	Load_SndVfCurve(*varSndVfCurvePtr);
			}
		}

		void Load()
		{
			Load_SndVfCurvePtr_Hook.Create(0x822422B0, Load_SndVfCurvePtr);
		}

		void Unload()
		{
			Load_SndVfCurvePtr_Hook.Clear();
		}
	}
#endif
}
