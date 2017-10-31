#pragma once

#include"Parser.h"

#ifdef CPPCLINET_EXPORTS
#define _DECLSPEC __declspec(dllexport)
#else
#define _DECLSPEC	__declspec(dllimport)
#endif

class _DECLSPEC ParserOBD :public Parser {
public:
	void RetrieveRealTimeParameters();

	~ParserOBD() {}
};