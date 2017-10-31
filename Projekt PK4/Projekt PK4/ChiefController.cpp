#include"ChiefController.h"
#include"ParserOBD.h"
#include"ParserOBD_CAN.h"

#include<fstream>

ChiefController::ChiefController() {
	CommandExecuter = new ELMCommandManager;
	FillAvailableCommandsMap();
}

ELMCommandManager* ChiefController::GetCommandManager() const {
	return CommandExecuter;
}

void ChiefController::FillAvailableCommandsMap() {
	string FileName = "Commands.bin";
	fstream File;

	File.open(FileName, ios::out | ios::binary);

	int Counter = 0;
	string Buffer;

	while(getline(File, Buffer)) {
		switch (Counter) {
		case ATZ:
			AvailableCommands[INITIALIZATION].insert_or_assign(ATZ, Buffer);
			break;
			
		case AT_SP:
			AvailableCommands[INITIALIZATION].insert_or_assign(AT_SP, Buffer);
			break;

		case AT_DP:
			AvailableCommands[INITIALIZATION].insert_or_assign(AT_DP, Buffer);
			break;

		case AT_H0:
			AvailableCommands[INITIALIZATION].insert_or_assign(AT_H0, Buffer);
			break;

		case CHECK_PIDS_00:
			AvailableCommands[CHECKING_PIDS].insert_or_assign(CHECK_PIDS_00, Buffer);
			break;

		case CHECK_PIDS_20:
			AvailableCommands[CHECKING_PIDS].insert_or_assign(CHECK_PIDS_20, Buffer);
			break;

		case CHECK_PIDS_40:
			AvailableCommands[CHECKING_PIDS].insert_or_assign(CHECK_PIDS_40, Buffer);
			break;

		case SPEED:
			AvailableCommands[RETRIEVING_REAL_TIME_DATA].insert_or_assign(SPEED, Buffer);
			break;

		case RPM:
			AvailableCommands[RETRIEVING_REAL_TIME_DATA].insert_or_assign(RPM, Buffer);
			break;

		case LOAD:
			AvailableCommands[RETRIEVING_REAL_TIME_DATA].insert_or_assign(LOAD, Buffer);
			break;

		case COOL_TEMP:
			AvailableCommands[RETRIEVING_REAL_TIME_DATA].insert_or_assign(COOL_TEMP, Buffer);
			break;

		case OIL_TEMP:
			AvailableCommands[RETRIEVING_REAL_TIME_DATA].insert_or_assign(OIL_TEMP, Buffer);
			break;

		case F_PRESSURE:
			AvailableCommands[RETRIEVING_REAL_TIME_DATA].insert_or_assign(F_PRESSURE, Buffer);
			break;

		case INT_MAN_ABS_PRES:
			AvailableCommands[RETRIEVING_REAL_TIME_DATA].insert_or_assign(INT_MAN_ABS_PRES, Buffer);
			break;

		case INT_AIR_TEMP:
			AvailableCommands[RETRIEVING_REAL_TIME_DATA].insert_or_assign(INT_AIR_TEMP, Buffer);
			break;

		case THROTTLE:
			AvailableCommands[RETRIEVING_REAL_TIME_DATA].insert_or_assign(THROTTLE, Buffer);
			break;
		
		case RELAT_ACC:
			AvailableCommands[RETRIEVING_REAL_TIME_DATA].insert_or_assign(RELAT_ACC, Buffer);
			break;

		case CONTROL_MOD_VOLT:
			AvailableCommands[RETRIEVING_REAL_TIME_DATA].insert_or_assign(CONTROL_MOD_VOLT, Buffer);
			break;

		case F_TANK_LEVEL:
			AvailableCommands[RETRIEVING_REAL_TIME_DATA].insert_or_assign(F_TANK_LEVEL, Buffer);
			break;

		case STANDARD:
			AvailableCommands[RETRIEVING_VEHICLE_INFORMATION].insert_or_assign(STANDARD, Buffer);
			break;

		case F_TYPE:
			AvailableCommands[RETRIEVING_VEHICLE_INFORMATION].insert_or_assign(F_TYPE, Buffer);
			break;
			
		default:
			break;
		}

		//AvailableCommands[INITIALIZATION].push_back(Buffer);
		//++Counter;
	}

	File.close();
}

map<MULTIPLE_READ_DATA, double>* ChiefController::GetRealTimeData() {
	return RetrievedRealTimeData;
}

map<SINGLE_READ_DATA, string>* ChiefController::GetVehicleInformation() {
	return RetrievedVehicleInformation;
}

void ChiefController::InitializeELM() {
	COMMAND_GROUP Group = INITIALIZATION;
	const int Size = AvailableCommands.at(Group).size();

	for (int i = 0; i < Size; ++i) {
		ResponseFromELM = CommandExecuter->ExecuteCommand(AvailableCommands.at(Group).at(static_cast<COMMAND>(i)), false);

		if (i == ATZ)
			if (ResponseFromELM.find("ELM327") == string::npos)
				throw exception("To nie ELM");

		if (i == AT_SP)
			CommandExecuter->ExecuteCommand(AvailableCommands.at(CHECKING_PIDS).at(CHECK_PIDS_00), false);
		
		if (i == AT_DP) {
			if (ResponseFromELM.find("CAN") != string::npos)
				ResponseInterperter = new ParserOBD_CAN;
			else
				ResponseInterperter = new ParserOBD;

			ResponseInterperter->SetResponseOrError(ResponseFromELM);
			ResponseInterperter->RetrieveVehicleInformation();
		}
	}
}

void ChiefController::RequestRealTimeData() {
	const string Mode = "01 ";
	int LoopRepeats = AvailableCommands.at(RETRIEVING_REAL_TIME_DATA).size();
	int CANCommandComposition;
	int Step;
	bool IfCAN = false;

	if (typeid(*ResponseInterperter) == typeid(ParserOBD)) {		// no tego to sie nie spodziewalam :P
		CANCommandComposition = 0;
		Step = 1;
	}
	else if (typeid(*ResponseInterperter) == typeid(ParserOBD_CAN)) {
		CANCommandComposition = AvailableCommands.at(RETRIEVING_REAL_TIME_DATA).size() / 2;
		Step = CANCommandComposition;
		IfCAN = true;
	}

	string CAN_Command = Mode;
	const char SeparatorSpace = ' ';	//nie wiem, czy to w ogole potrzebne - czy ELM w ogole zwraca uwage na spacje

	for (int i = 0; i < LoopRepeats; i += Step) {
		for (int j = 0; j < CANCommandComposition; ++j)
			CAN_Command += AvailableCommands.at(RETRIEVING_REAL_TIME_DATA).at(static_cast<COMMAND>(j)) + SeparatorSpace;

		if (IfCAN)
			ResponseFromELM = CommandExecuter->ExecuteCommand(CAN_Command, false);
		else
			ResponseFromELM = CommandExecuter->ExecuteCommand(AvailableCommands.at(RETRIEVING_REAL_TIME_DATA).at(static_cast<COMMAND>(i)), false);

		ResponseInterperter->SetResponseOrError(ResponseFromELM);
		ResponseInterperter->RetrieveRealTimeParameters();
	}
	RetrievedRealTimeData = ResponseInterperter->GetInterpretedRealTimeParameters();
}

void ChiefController::RequestVehicleInformation() {
	const string Mode = "01 ";

	for (int i = 0; i < AvailableCommands.at(RETRIEVING_VEHICLE_INFORMATION).size(); ++i) {
		ResponseFromELM = CommandExecuter->ExecuteCommand(AvailableCommands.at(RETRIEVING_VEHICLE_INFORMATION).at(static_cast<COMMAND>(i)), false);

		ResponseInterperter->SetResponseOrError(ResponseFromELM);
		ResponseInterperter->RetrieveVehicleInformation();
	}
	RetrievedVehicleInformation = ResponseInterperter->GetInterpretedRVehicleInformation();
}

ChiefController::~ChiefController() {
	CommandExecuter->ExecuteCommand(AvailableCommands.at(INITIALIZATION).at(ATZ), true);
	CommandExecuter->JoinThread();

	delete CommandExecuter;
	delete ResponseInterperter;

	RetrievedRealTimeData->clear();
	RetrievedVehicleInformation->clear();

	for (int i = 0; i < AvailableCommands.size(); ++i)
		AvailableCommands.at(static_cast<COMMAND_GROUP>(i)).clear();
	
	AvailableCommands.clear();
}