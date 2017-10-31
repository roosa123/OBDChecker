#include"Parser.h"

#include<algorithm>
#include<fstream>

using namespace NativeParser;

Parser::Parser() :SeparatorSpace(' '), CarriageReturn('\r'), EndOfLine('\n') {
	FillOBDStandardsOrFuelTypeMap(true);
	FillOBDStandardsOrFuelTypeMap(false);
}

void Parser::FillOBDStandardsOrFuelTypeMap(bool IfOBDStandardsMap) {
	string FileName;

	if (IfOBDStandardsMap)
		FileName = "OBDStandards.bin";
	else
		FileName = "FuelType.bin";

	fstream File;
	File.open(FileName, ios::in | ios::binary);

	string Buffer;
	int Index;
	string IndexTmp;
	string Description;

	while (getline(File, Buffer)) {
		string::iterator TabulatorOffset = find(Buffer.begin(), Buffer.end(), '\t');
		
		Index = stoi(IndexTmp.assign(Buffer.begin(), TabulatorOffset));
		Description.assign(TabulatorOffset + 1, Buffer.end());
		if (IfOBDStandardsMap)
			OBDStandards.insert_or_assign(Index, Description);
		else
			FuelType.insert_or_assign(Index, Description);
	}

	File.close();
}

bool Parser::CompareTokens(char TokenA, char TokenB) {
	const char CarriageReturn = '\r';
	const char EndOfLine = '\n';

	if (TokenA == CarriageReturn && TokenB == EndOfLine)
		return true;
	else
		return false;
}

void Parser::SetResponseOrError(string Resp) {
	ResponseOrError = Resp;
}

string Parser::GetResponseOrError() const {
	return ResponseOrError;
}

void ParserOBD::SetResponseOrError(string Resp) {
	ResponseOrError = Resp;
	ResponseOrError_OBD = Resp;
}

void ParserOBD_CAN::SetResponseOrError(string Resp) {
	ResponseOrError = Resp;
	ResponseOrError_CAN = Resp;
}

int Parser::HexToDec(string ReceivedValues) {
	ReceivedValues.erase(remove(ReceivedValues.begin(), ReceivedValues.end(), SeparatorSpace), ReceivedValues.end());
	return stoi(ReceivedValues, nullptr, 16);
}

double Parser::CalculatePercents(string Value) {
	return static_cast<double>(static_cast<int>(((100.0 / 255.0) * HexToDec(Value)) * 100)) / 100.0;
}

double Parser::CalculateSeconds(string Value) {
	return double(HexToDec(Value));
}

double Parser::CalculateDegreeCelsius(string Value) {
	return double(HexToDec(Value) - 40.0);
}

double Parser::CalculateRPM(string Value) {
	return static_cast<double>(static_cast<int>((HexToDec(Value) / 4.0) * 100)) / 100.0;
}

double Parser::CalculateVolts(string Value) {
	return static_cast<double>(static_cast<int>((HexToDec(Value) / 1000.0) * 100)) / 100.0;
}

void Parser::InsertIntoRealTimeParametersMap(int CommandCode, string Value) {
	switch (CommandCode) {
	case VEHICLE_SPEED:
		RealTimeParameters.insert_or_assign(VEHICLE_SPEED, HexToDec(Value));
		break;

	case ENGINE_LOAD:
		RealTimeParameters.insert_or_assign(ENGINE_LOAD, CalculatePercents(Value));
		break;

	case ENGINE_COOLANT_TEMPERATURE:
		RealTimeParameters.insert_or_assign(ENGINE_COOLANT_TEMPERATURE, CalculateDegreeCelsius(Value));
		break;

	case ENGINE_OIL_TEMPERATURE:
		RealTimeParameters.insert_or_assign(ENGINE_OIL_TEMPERATURE, CalculateDegreeCelsius(Value));
		break;

	case FUEL_PRESSURE:
		RealTimeParameters.insert_or_assign(FUEL_PRESSURE, 3 * HexToDec(Value));
		break;

	case INTAKE_MANIFOLD_ABSOLUTE_PRESSURE:
		RealTimeParameters.insert_or_assign(INTAKE_MANIFOLD_ABSOLUTE_PRESSURE, HexToDec(Value));
		break;

	case INTAKE_AIR_TEMPERAUTRE:
		RealTimeParameters.insert_or_assign(INTAKE_AIR_TEMPERAUTRE, CalculateDegreeCelsius(Value));
		break;

	case THROTTLE_POSITION:
		RealTimeParameters.insert_or_assign(THROTTLE_POSITION, CalculatePercents(Value));
		break;

	case RELATIVE_ACCELERATOR_PEDAL_POSITION:
		RealTimeParameters.insert_or_assign(RELATIVE_ACCELERATOR_PEDAL_POSITION, CalculatePercents(Value));
		break;

	default:
		throw exception("Nie mozna przypisac do mapy RealTimeParameters");
		break;
	}
}

void Parser::InsertIntoVehicleInformationMap(int CommandCode) {
	switch (CommandCode) {
	case OBD_STANDARD:
		VehicleInformation.insert_or_assign(OBD_STANDARD, RetrieveOBDStandardOrFuelType(true));
		break;

	case FUEL_TYPE:
		VehicleInformation.insert_or_assign(FUEL_TYPE, RetrieveOBDStandardOrFuelType(false));
		break;

	default:
		throw exception("Nie mozna przypisac do mapy VehicleInformation");
		break;
	}
}

void Parser::RetrieveResponse() {			// uniwersalna tez dla AT Commands (odcina tylko naglowek i koncowke od ELM-a)
	string::iterator RespondedValuesOffset = adjacent_find(ResponseOrError.begin(), ResponseOrError.end(), CompareTokens);

	const char Colon = ':';		// z tego tytulu dla CAN-a dziala tylko dla wylaczonych naglowkow - we wlaczonych naglowkach nie ma dwukropka

	if (RespondedValuesOffset != ResponseOrError.end()) {
		string::iterator FindColon = find(ResponseOrError.begin(), ResponseOrError.end(), Colon);

		if (FindColon != ResponseOrError.end()) {
			string BytesReturned;

			BytesReturned.assign(RespondedValuesOffset + 2, RespondedValuesOffset + 5);

			int TotalRespondedBytes = stoi(BytesReturned, nullptr, 16);
			TotalRespondedBytes *= 2;
			TotalRespondedBytes += 0.5 * TotalRespondedBytes;

			string::iterator FindNext = adjacent_find(FindColon, ResponseOrError.end(), CompareTokens);

			MessageOnly.assign(FindColon + 2, FindNext);
			string AnotherPart;

			while (TotalRespondedBytes > MessageOnly.length()) {
				FindColon = FindNext + 5;
				FindNext = adjacent_find(FindNext + 1, ResponseOrError.end(), CompareTokens);
				AnotherPart.assign(FindColon, FindNext);
				MessageOnly += AnotherPart;
			}
		}
		else {
			const string SeparatorAUTO = "AUTO";
			const string SearchingMessage = "SEARCHING";
			const string ErrorMessage = "NO DATA";
			const string ErrorMessage2 = "UNABLE TO CONNECT";

			if (MessageOnly.find(SeparatorAUTO) == string::npos)
				if (ResponseOrError.find(ErrorMessage) != string::npos || ResponseOrError.find(ErrorMessage2) != string::npos) {
					MessageOnly.assign(ResponseOrError.begin() + 2, ResponseOrError.begin() + 4);
					MessageOnly += " " + ErrorMessage;
				}
				else
					MessageOnly.assign(RespondedValuesOffset + 5, ResponseOrError.end() - 5);	// przypisanie samej wiadomosci (komenda + wartosc), bez trybu
			else if (MessageOnly.find(SearchingMessage) != string::npos) {
				size_t FirstSpace = ResponseOrError.find(SeparatorSpace);
				MessageOnly.assign(FirstSpace, FirstSpace + 5);
			}
			else
				MessageOnly.assign(RespondedValuesOffset + 2, ResponseOrError.end() - 5);
		}
	}
	else
		throw exception("Nie mozna wyodrebnic odpowiedzi");
}

void Parser::RetrieveProtocol() {
	const string SeparatorAUTO = "AUTO";

	string ProtocolTemp;

	size_t IfAUTO = MessageOnly.find(SeparatorAUTO);

	if (IfAUTO != string::npos)
		ProtocolTemp.assign(MessageOnly, MessageOnly.find(SeparatorSpace) + 1);
	else
		ProtocolTemp.assign(MessageOnly.begin() + 3, MessageOnly.end());

	VehicleInformation.insert_or_assign(PROTOCOL, ProtocolTemp);
}

pair<int, string> Parser::RetrieveCommandAndValue() {
	string::iterator FirstSpace = find(MessageOnly.begin(), MessageOnly.end(), SeparatorSpace);

	string FoundCommand;
	string FoundValue;
	
	if (FirstSpace != MessageOnly.end()) {
		FoundCommand.assign(MessageOnly.begin(), FirstSpace);
		FoundValue.assign(FirstSpace + 1, MessageOnly.end());
		return make_pair(stoi(FoundCommand, nullptr, 16), FoundValue);
	}
	else
		throw exception("Nie mozna wyodrebnic komendy");
}

string Parser::RetrieveOBDStandardOrFuelType(bool IfOBDStandard) {
	const string ERROR_MESSAGE = "NO DATA";

	if (MessageOnly.find(ERROR_MESSAGE) != string::npos)
		return ERROR_MESSAGE;

	string Value;

	Value.reserve(2 * sizeof(char));

	Value.assign(MessageOnly.end() - 2, MessageOnly.end());

	if (IfOBDStandard)
		return OBDStandards.at(stoi(Value, nullptr, 16));
	else
		return FuelType.at(stoi(Value, nullptr, 16));
}

void Parser::RetrieveVehicleInformation() {
	try {
		RetrieveResponse();
	}
	catch (exception& exc) {
		throw;
	}

	const string ISO = "ISO";
	const string SAE = "SAE";
	const string CAN = "CAN";

	size_t IfISO = MessageOnly.find(ISO);
	size_t IfSAE = MessageOnly.find(SAE);
	size_t IfCAN = MessageOnly.find(CAN);

	if (IfISO != string::npos || IfSAE != string::npos || IfCAN != string::npos)
		RetrieveProtocol();
	else {
		try {
			InsertIntoVehicleInformationMap(RetrieveCommandAndValue().first);
		}
		catch (exception& exc) {
			throw;
		}
	}
}

map<MULTIPLE_READ_DATA, double>* Parser::GetInterpretedRealTimeParameters() {
	return &RealTimeParameters;
}

map<SINGLE_READ_DATA, string>* Parser::GetInterpretedRVehicleInformation() {
	return &VehicleInformation;
}

void Parser::SetInterpretedRealTimeParameters(map<MULTIPLE_READ_DATA, double>* NewParameters) {
	RealTimeParameters = *NewParameters;
}

Parser::~Parser() {
	RealTimeParameters.clear();
	VehicleInformation.clear();
	OBDStandards.clear();
	FuelType.clear();
}