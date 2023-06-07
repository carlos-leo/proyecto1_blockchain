#ifndef __UTILES_H
#define __UTILES_H


#include<ctime>
#include<string>
std::string ObtieneFechaActual()
{
	std::tm bt{};
	std::time_t t = std::time(nullptr);
#if defined(__unix__)
	localtime_r(&timer, &bt);
#else defined(_MSC_VER)
	localtime_s(&bt, &t);
#endif

	char buffer[17];
	strftime(buffer, sizeof(buffer), "%Y/%m/%d %H:%M", &bt);

	return buffer;
}

#endif // !__UTILES_H