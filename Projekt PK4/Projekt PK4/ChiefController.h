#pragma once

#include"Parser.h"
#include"../BTH_ILBridge/BTH_ELMNative.h"

#include<map>
#include<vector>
#include<iterator>

enum COMMAND_GROUP {
	INITIALIZATION,
	CHECKING_PIDS,
	RETRIEVING_REAL_TIME_DATA,
	RETRIEVING_VEHICLE_INFORMATION
};

enum COMMAND {
	ATZ,
	AT_SP,
	AT_H0,
	AT_DP,
	CHECK_PIDS_00,
	CHECK_PIDS_20,
	CHECK_PIDS_40,
	LOAD,
	COOL_TEMP,
	F_PRESSURE,
	INT_MAN_ABS_PRES,
	RPM,
	SPEED,
	INT_AIR_TEMP,
	THROTTLE,
	F_TANK_LEVEL,
	CONTROL_MOD_VOLT,
	RELAT_ACC,
	OIL_TEMP,
	STANDARD,
	F_TYPE
};

class ChiefController {
	Parser* ResponseInterperter;
	ELMCommandManager* CommandExecuter;

	string ResponseFromELM;

	map<MULTIPLE_READ_DATA, double>* RetrievedRealTimeData;
	map<SINGLE_READ_DATA, string>* RetrievedVehicleInformation;
	map<COMMAND_GROUP, map<COMMAND, string>> AvailableCommands;

public:
	ChiefController();

	ELMCommandManager* GetCommandManager() const;
	void FillAvailableCommandsMap();
	map<MULTIPLE_READ_DATA, double>* GetRealTimeData();
	map<SINGLE_READ_DATA, string>* GetVehicleInformation();

	void InitializeELM();
	void RequestRealTimeData();
	void RequestVehicleInformation();

	~ChiefController();
};