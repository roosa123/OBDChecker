#pragma once

#include"Parser.h"

#ifdef CPPCLINET_EXPORTS
#define _DECLSPEC __declspec(dllexport)
#else
#define _DECLSPEC	__declspec(dllimport)
#endif

class _DECLSPEC ParserOBD_CAN :public Parser {
	string SentCommands;
	string FullMessage;
public:
	void RetrieveRealTimeParameters();
	void RetrieveSentCommands();

	~ParserOBD_CAN() {}
};