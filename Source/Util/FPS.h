#pragma once

namespace Util
{
	class FPS
	{
	public:
		FPS()
		{
			Reset();
		}

		void Reset()
		{
			for (int i = 0; i < SAMPLE_COUNT; ++i)
				frameTimes[i] = 16.6f;

			index = 0;
			lastTick = GetTickCount();
		}

		void Update()
		{
			DWORD now = GetTickCount();
			DWORD delta = now - lastTick;
			lastTick = now;

			frameTimes[index] = static_cast<float>(delta);
			index = (index + 1) % SAMPLE_COUNT;
		}

		float GetAverageFrameTime() const
		{
			float sum = 0.0f;
			for (int i = 0; i < SAMPLE_COUNT; ++i)
				sum += frameTimes[i];
			return sum / SAMPLE_COUNT;
		}

		float GetFPS() const
		{
			float avg = GetAverageFrameTime();
			if (avg <= 0.0f)
				return 0.0f;
			return 1000.0f / avg;
		}

		static FPS& GetInstance()
		{
			static FPS instance;
			return instance;
		}

	private:
		static const int SAMPLE_COUNT = 32;
		float frameTimes[SAMPLE_COUNT];

		int index;
		DWORD lastTick;
	};
}
