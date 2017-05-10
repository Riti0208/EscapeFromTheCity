#include <string>
#include <list>
#include"split.h"
std::list<std::string> split(std::string str, std::string delim){
	std::list<std::string> result;
	int cutAt;
	while ((cutAt = str.find_first_of(delim)) != str.npos)
	{
		if (cutAt > 0)
		{
			result.push_back(str.substr(0, cutAt));
		}
		str = str.substr(cutAt + 1);
	}
	if (str.length() > 0)
	{
		result.push_back(str);
	}
	return result;
}