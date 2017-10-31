#include<iostream>
#include<exception>
#include"OBDService.h"

using namespace std;

OBDService::OBDService() :InitCommandsCount(4), CarriageReturn('\r') {
	Client = new ELMClient;
	MemoryControl = new BTHSemaphores;
	Hollow = new ELMCommandBuffer;
	InitCommands = new string[InitCommandsCount];

	InitCommands[ATZ] = "ATZ";
	InitCommands[AT_TP_0] = "AT TP 0";
	InitCommands[PID_CHECK] = "01 00";
	InitCommands[AT_DP] = "AT DP";
}

void OBDService::OBDInit() {	// to jest jeszcze baaaaardzo brzydkie i zdaje sobie z tego sprawe...
	for (int i = -1; i < InitCommandsCount - 1; ++i) {
		MemoryControl->ResponseWait();
		MemoryControl->MemoryLockWait();

		string Resp = Hollow->GetResponse();

		if (i == ATZ || i == AT_TP_0)
			if (Resp.find("OK") != string::npos)
				throw exception("Inicjalizacja nie powiodla sie");

		if (i == AT_DP)
			Protocol = Resp;

		cout << "Response from ELM: " << Resp.c_str() << endl;

		Hollow->SetCommand(InitCommands[i + 1] + CarriageReturn);

		MemoryControl->MemoryLockRelease();
		MemoryControl->CommandRelease();
	}
}

void OBDService::GetData() {

}

OBDService::~OBDService() {
	delete Client;
	delete MemoryControl;
	delete Hollow;
	delete[] InitCommands;
}