//#pragma comment(lib, "D:\\studia\\Informatyka\\programowanie komputerów\\sem IV\\projekt PK4 diagnostyka DPF\\Projekt PK4\\Debug\\BTH_ILBridge.lib")
#pragma comment(lib, "../Debug/BTH_ILBridge.lib")

#include<iostream>
#include<string>
#include"../BTH_ILBridge/BTH_ELMNative.h"
#include"Parser.h"
#include"ParserOBD_CAN.h"
#include"ParserOBD.h"
#include"ChiefController.h"

using namespace std;

BTHSemaphores MemoryControl;

/*int main() {
	/*
	ELMCommandManager Szef("OBDII", "1234");

	Szef.StartThread();
	

	string Resp = Szef.ExecuteCommand("ATZ\r", false);
	cout << Resp << endl;

	Resp = Szef.ExecuteCommand("AT SP A5\r", false);
	cout << Resp << endl;

	Resp = Szef.ExecuteCommand("01 00\r", false);
	cout << Resp << endl;

	Resp = Szef.ExecuteCommand("AT DP\r", false);
	cout << Resp << endl;

	Resp = Szef.ExecuteCommand("01 0D\r", false);
	cout << Resp << endl;

	Resp = Szef.ExecuteCommand("09 02\r", false);
	cout << Resp << endl;

	Resp = Szef.ExecuteCommand("AT H1\r", false);
	cout << Resp << endl;

	Resp = Szef.ExecuteCommand("01 00\r", false);
	cout << Resp << endl;

	Resp = Szef.ExecuteCommand("01 0D\r", false);
	cout << Resp << endl;

	Resp = Szef.ExecuteCommand("09 02\r", true);
	cout << Resp << endl;
	
	Szef.JoinThread();//*/

	/*ParserOBD_CAN Parsowanie;
	//ParserOBD Parsowanie;

	Parsowanie.SetResponseOrError("AT DP\r\nAUTO, ISO 15765-4 (CAN 11/500)\r\n\r\n>");

	Parsowanie.RetrieveVehicleInformation();

	////////Parsowanie.SetResponseOrError(Szef.ExecuteCommand("01 0D\r", false));
	//Parsowanie.SetResponseOrError("01 0D\r\n41 0D 00\r\n\r\n>");

	//Parsowanie.RetrieveRealTimeParameters();

	////////Parsowanie.SetResponseOrError(Szef.ExecuteCommand("01 0C\r", false));
	//Parsowanie.SetResponseOrError("01 0C\r\n41 0C 0F A0\r\n\r\n>");

	//Parsowanie.RetrieveRealTimeParameters();

	Parsowanie.SetResponseOrError("01 0B 04 0C 05\r\n00A\r\n0: 41 0B 21 04 3F 0C \r\n1: 17 B8 05 44 00 00 00 \r\n\r\n>");

	Parsowanie.RetrieveRealTimeParameters();// tu ma byæ koniec komentarza z gwiazdk¹

	ChiefController NewController;
	NewController.GetRealTimeData();

	system("pause");
	return 0;
}//*/