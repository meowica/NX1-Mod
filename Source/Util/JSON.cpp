namespace Util
{
	namespace JSON
	{
		std::string JsonEscape(const char* string)
		{
			if (!string)
				return "";

			std::string input = string;
			std::string out;
			out.reserve(input.size() + 8);

			for (std::size_t i = 0; i < input.size(); i++)
			{
				char c = input[i];
				switch (c)
				{
				case '\\':
					out += "\\\\";
					break;
				case '"':
					out += "\\\"";
					break;
				case '\n':
					out += "\\n";
					break;
				case '\r':
					out += "\\r";
					break;
				case '\t':
					out += "\\t";
					break;
				default:
					if ((unsigned char)c < 0x20)
					{
						char buf[8];
						snprintf(buf, sizeof(buf), "\\u%04x", c);
						out += buf;
					}
					else
						out += c;
				}
			}
			return out;
		}
	}
}
