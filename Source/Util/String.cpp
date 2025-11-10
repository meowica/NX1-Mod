namespace Util
{
	namespace String
	{
#define VA_BUFFER_COUNT 4
#define VA_BUFFER_SIZE 32768

		const char* VA(const char* fmt, ...)
		{
			static char buffers[VA_BUFFER_COUNT][VA_BUFFER_SIZE];
			static int currentBuffer = 0;

			char* dest = buffers[currentBuffer];
			currentBuffer = (currentBuffer + 1) % VA_BUFFER_COUNT;

			va_list args;
			va_start(args, fmt);
			int len = vsnprintf(dest, VA_BUFFER_SIZE, fmt, args);
			va_end(args);

			dest[VA_BUFFER_SIZE - 1] = '\0'; // ensure null-termination

			if (len < 0 || len >= VA_BUFFER_SIZE)
			{
				printf("Attempted to overrun string in call to va()\n");
			}
			return dest;
		}

		const char* GetCurrentTime()
		{
			static char buf[16];

			time_t now = time(NULL);
			now += 8 * 3600; // adjust to UTC+8 if needed

			struct tm* timeinfo = localtime(&now);

			strftime(buf, sizeof(buf), "%I:%M:%S %p", timeinfo);
			return buf;
		}
	}
}
