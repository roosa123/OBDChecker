#pragma once

#include<string>
#include"../BTH_ILBridge/BTH_ELMNative.h"

using namespace std;

enum InitializationCommands {
	ATZ,
	AT_TP_0,
	PID_CHECK,
	AT_DP
};

class OBDService {
	ELMClient* Client;
	BTHSemaphores* MemoryControl;
	ELMCommandBuffer* Hollow;
	string* InitCommands;
	const int InitCommandsCount;
	char CarriageReturn;

	string Protocol;
	string Speed;
	string RPM;
	string ThrottlePos;


public:
	OBDService();

	void OBDInit();
	void GetData();
	void GetTroubleCodes();

	~OBDService();
};