#include <String>
namespace TEG
{
	enum LogType
	{
		None,
		Warning,
		Error,
		Debug
	};
	struct Log
	{
		LogType type;
		std::string content;
	};
}