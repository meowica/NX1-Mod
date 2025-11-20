#define VA_BUFFER_COUNT 4
#define VA_BUFFER_SIZE 32768

namespace Util
{
	namespace String
	{
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
				printf("Attempted to overrun string in call to VA()\n");
			return dest;
		}

		PWCHAR VAW(const char* fmt, ...)
		{
			static wchar_t buffers[VA_BUFFER_COUNT][VA_BUFFER_SIZE];
			static int currentBuffer = 0;

			wchar_t* dest = buffers[currentBuffer];
			currentBuffer = (currentBuffer + 1) % VA_BUFFER_COUNT;

			char tempDest[VA_BUFFER_SIZE];

			va_list args;
			va_start(args, fmt);
			int len = vsnprintf(tempDest, VA_BUFFER_SIZE, fmt, args);
			va_end(args);

			tempDest[VA_BUFFER_SIZE - 1] = '\0'; // ensure null-termination

			if (len < 0 || len >= VA_BUFFER_SIZE)
				printf("Attempted to overrun string in call to VAW()\n");

			mbstowcs(dest, tempDest, VA_BUFFER_SIZE);
			dest[VA_BUFFER_SIZE - 1] = L'\0';
			return dest;
		}
	}
}
