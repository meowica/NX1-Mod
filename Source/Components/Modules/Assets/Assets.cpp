namespace Assets
{
#ifdef MP_MOD	
	namespace MP
	{
#ifdef INCLUDE_ASSET_DUMPERS
		Util::Hook::Detour Load_PhysPresetPtr_Hook;
		void Load_PhysPresetPtr(bool atStreamStart)
		{
			auto Invoke = Load_PhysPresetPtr_Hook.Invoke<void(*)(bool)>();
			Invoke(atStreamStart);

			PhysPreset** varPhysPresetPtr = *(PhysPreset***)0x82CE6DE0;
			if (varPhysPresetPtr && *varPhysPresetPtr)
			{
				Dump_PhysPreset(*varPhysPresetPtr);
			}
		}
#endif

		void Hooks()
		{
#ifdef INCLUDE_ASSET_DUMPERS
			Load_PhysPresetPtr_Hook.Create(0x82306FD8, Load_PhysPresetPtr);
#endif
		}

		void ClearHooks()
		{

		}

		void Load()
		{
			Hooks();
		}

		void Unload()
		{
			ClearHooks();
		}
	}
#endif

#ifdef SP_MOD
	namespace SP
	{
		void Hooks()
		{

		}

		void ClearHooks()
		{

		}

		void Load()
		{
			Hooks();
		}

		void Unload()
		{
			ClearHooks();
		}
	}
#endif
}