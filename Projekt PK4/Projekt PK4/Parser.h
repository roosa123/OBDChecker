#pragma once

#include<string>
#include<map>

#ifdef CPPCLINET_EXPORTS
#define _DECLSPEC __declspec(dllexport)
#else
#define _DECLSPEC	__declspec(dllimport)
#endif

using namespace std;

enum MULTIPLE_READ_DATA {
	VEHICLE_SPEED = 0x0D,													// 1 bajt				// tylko zamiana na dec; km/h
	ENGINE_LOAD = 0x04,														// 1 bajt				// %
	ENGINE_COOLANT_TEMPERATURE = 0x05,										// 1 bajt				// deg. C
	ENGINE_OIL_TEMPERATURE = 0x5C,											// 1 bajt				// deg. C
	FUEL_PRESSURE = 0x0A,													// 1 bajt				// 3 * tylko zamiana na dec; kPa
	INTAKE_MANIFOLD_ABSOLUTE_PRESSURE = 0x0B,								// 1 bajt				// tylko zamiana na dec; kPa
	INTAKE_AIR_TEMPERAUTRE = 0x0F,											// 1 bajt				// deg. C
	THROTTLE_POSITION = 0x11,												// 1 bajt				// %
	RELATIVE_ACCELERATOR_PEDAL_POSITION = 0x5A,								// 1 bajt				// %
};

enum SINGLE_READ_DATA {
	PROTOCOL,				// AT command
	OBD_STANDARD = 0x1C,	// mode 01										// 1 bajt
	FUEL_TYPE = 0x51,		// mode 01										// 1 bajt
};

namespace NativeParser {
	class _DECLSPEC Parser {
		map<MULTIPLE_READ_DATA, double> RealTimeParameters;
		map<SINGLE_READ_DATA, string> VehicleInformation;
		map<int, string> OBDStandards;
		map<int, string> FuelType;

		const char SeparatorSpace;
		const char CarriageReturn;
		const char EndOfLine;

		void FillOBDStandardsOrFuelTypeMap(bool);

		int HexToDec(string);									// ogolnego uzytku, ale glownie na uzytek switcha

		double CalculatePercents(string);						// na uzytek switcha
		double CalculateSeconds(string);						// na uzytek switcha
		double CalculateDegreeCelsius(string);					// na uzytek switcha
		double CalculateRPM(string);							// na uzytek switcha
		double CalculateVolts(string);							// na uzytek switcha

		void InsertIntoVehicleInformationMap(int);				// na uzytek RetrieveVehicleInformation

		void RetrieveProtocol();								// ogolnego uzytku, glownie w RetrieveRealTimeParameters()
		string RetrieveOBDStandardOrFuelType(bool);				// na uzytek switcha

	protected:
		string ResponseOrError;
		string MessageOnly;

		static bool CompareTokens(char, char);					// na uzytek jedngo bodajze wystapienia adjacent_find

		pair<int, string> RetrieveCommandAndValue();			// do wywolania switcha - 2in1
		void InsertIntoRealTimeParametersMap(int, string);		// na uzytek RetrieveRealTimeParameters
		void RetrieveResponse();								// ogolnego uzytku, glownie w RetrieveRealTimeParameters()

	public:
		Parser();
		virtual void RetrieveRealTimeParameters() = 0;
		void RetrieveVehicleInformation();						// mniej wiecej wazna, a nawet bardzo

		void SetResponseOrError(string);						// bardzo ogolnego uzytku
		string GetResponseOrError() const;

		map<MULTIPLE_READ_DATA, double>* GetInterpretedRealTimeParameters();
		map<SINGLE_READ_DATA, string>* GetInterpretedRVehicleInformation();

		void SetInterpretedRealTimeParameters(map<MULTIPLE_READ_DATA, double>*);

		virtual ~Parser();
	};

	class _DECLSPEC ParserOBD_CAN :public Parser {
		string ResponseOrError_CAN;
		string SentCommands;
		string FullMessage;
	public:
		void SetResponseOrError(string);						// bardzo ogolnego uzytku
		void RetrieveRealTimeParameters();
		void RetrieveSentCommands();

		~ParserOBD_CAN() {}
	};

	class _DECLSPEC ParserOBD :public Parser {
		string ResponseOrError_OBD;
	public:
		void SetResponseOrError(string);						// bardzo ogolnego uzytku
		void RetrieveRealTimeParameters();

		~ParserOBD() {}
	};
}