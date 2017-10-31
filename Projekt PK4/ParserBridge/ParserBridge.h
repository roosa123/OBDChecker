// ParserBridge.h
#pragma managed
#pragma once

#include"../Projekt PK4/Parser.h"
#include<vcclr.h>

using namespace System;
using namespace System::Collections::Generic;

namespace ParserBridge {

	public enum class MultipleReadData {
		VehicleSpeed = 0x0D,													// 1 bajt				// km/h
		EngineLoad = 0x04,														// 1 bajt				// %
		EngineCoolantTemperature = 0x05,										// 1 bajt				// deg. C
		EngineOilTemperature = 0x5C,											// 1 bajt				// deg. C
		FuelPressure = 0x0A,													// 1 bajt				// 3 * tylko zamiana na dec; kPa
		IntakeManifoldAbsolutePressure = 0x0B,									// 1 bajt				// tylko zamiana na dec; kPa
		IntakeAirTemperature = 0x0F,											// 1 bajt				// deg. C
		ThrottlePosition = 0x11,												// 1 bajt				// %
		RelativeAcceleratorPedalPosition = 0x5A,								// 1 bajt				// %
	};

	public enum class SingleReadData {
		Protocol,				// AT command
		OBDStandard = 0x1C,	// mode 01										// 1 bajt
		FuelType = 0x51,		// mode 01										// 1 bajt
	};

	class Marshaling {
	public:
		static string MarshalString(String^);
	};

	class ParserProxy;

	public ref class ParserManaged abstract
	{
		ParserProxy* ParserNative;
	public:
		ParserManaged();

		virtual void RetrieveRealTimeParameters() abstract;
		void RetrieveVehicleInformation();

		void SetResponseOrError(String^);
		string GetReponseOrError();

		virtual Dictionary<MultipleReadData, double>^ GetInterpretedRealTimeParameters();
		Dictionary<SingleReadData, String^>^ GetInterpretedVehicleInformation();
		void SetInterpretedRealTimeInformation(map<MULTIPLE_READ_DATA, double>*);

		virtual ~ParserManaged();
	};

	public ref class ParserOBD_Managed :public ParserManaged {
		NativeParser::ParserOBD* ParserNative;
	public:
		ParserOBD_Managed();

		 void RetrieveRealTimeParameters() override;
		 Dictionary<MultipleReadData, double>^ GetInterpretedRealTimeParameters() override;

		 ~ParserOBD_Managed();
	};

	public ref class ParserOBD_CAN_Managed :public ParserManaged {
		NativeParser::ParserOBD_CAN* ParserNative;
	public:
		ParserOBD_CAN_Managed();

		void RetrieveRealTimeParameters() override;
		Dictionary<MultipleReadData, double>^ GetInterpretedRealTimeParameters() override;
		void RetrieveSentCommands();

		~ParserOBD_CAN_Managed();
	};

	class ParserProxy :public NativeParser::Parser {
		gcroot<ParserManaged^> Target;
	public:
		ParserProxy(ParserBridge::ParserManaged^);

		virtual void RetrieveRealTimeParameters();
	};
}
