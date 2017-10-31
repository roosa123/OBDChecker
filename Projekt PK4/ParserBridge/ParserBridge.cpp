// This is the main DLL file.

#include "stdafx.h"

#include "ParserBridge.h"

string ParserBridge::Marshaling::MarshalString(String^ StringToConvert) {
	using namespace System::Runtime::InteropServices;

	return string((char*)(Marshal::StringToHGlobalAnsi(StringToConvert)).ToPointer());
}

ParserBridge::ParserManaged::ParserManaged() {
	ParserNative = new ParserProxy(this);

	if (!ParserNative)
		throw gcnew OutOfMemoryException("Nie dalo sie zaalokowac pamieci");
}

void ParserBridge::ParserManaged::RetrieveVehicleInformation() {
	try {
		ParserNative->RetrieveVehicleInformation();
	}
	catch (exception& exc) {
		throw gcnew Exception(gcnew String(exc.what()));
	}
}

void ParserBridge::ParserManaged::SetResponseOrError(String^ ResponseFromELM) {
	ParserNative->SetResponseOrError(Marshaling::MarshalString(ResponseFromELM));
}

string ParserBridge::ParserManaged::GetReponseOrError() {
	return ParserNative->GetResponseOrError();
}

Dictionary<ParserBridge::MultipleReadData, double>^ ParserBridge::ParserManaged::GetInterpretedRealTimeParameters() {
	Dictionary<MultipleReadData, double>^ ConvertedInformation = gcnew Dictionary<MultipleReadData, double>();
	map<MULTIPLE_READ_DATA, double>* NativeValues = ParserNative->GetInterpretedRealTimeParameters();

	for (map<MULTIPLE_READ_DATA, double>::iterator it = NativeValues->begin(); it != NativeValues->end(); ++it) {
		MultipleReadData ManagedKey = static_cast<MultipleReadData>(it->first);
		ConvertedInformation->Add(ManagedKey, it->second);
	}

	NativeValues->clear();

	return ConvertedInformation;
}

Dictionary<ParserBridge::SingleReadData, String^>^ ParserBridge::ParserManaged::GetInterpretedVehicleInformation() {
	Dictionary<SingleReadData, String^>^ ConvertedInformation = gcnew Dictionary<SingleReadData, String^>();
	map<SINGLE_READ_DATA, string>* NativeParameters = ParserNative->GetInterpretedRVehicleInformation();

	for (map<SINGLE_READ_DATA, string>::iterator it = NativeParameters->begin(); it != NativeParameters->end(); ++it) {
		SingleReadData ManagedKey = static_cast<SingleReadData>(it->first);
		String^ ManagedValue = gcnew String(it->second.c_str());
		ConvertedInformation->Add(ManagedKey, ManagedValue);
	}

	NativeParameters->clear();
	
	return ConvertedInformation;
}

void ParserBridge::ParserManaged::SetInterpretedRealTimeInformation(map<MULTIPLE_READ_DATA, double>* NewParameters) {
	ParserNative->SetInterpretedRealTimeParameters(NewParameters);
}

ParserBridge::ParserManaged::~ParserManaged() {
	delete ParserNative;
}

ParserBridge::ParserOBD_Managed::ParserOBD_Managed() {
	ParserNative = new NativeParser::ParserOBD;
	if (!ParserNative)
		throw gcnew OutOfMemoryException("Nie dalo sie zaalokowac pamieci");
}

void ParserBridge::ParserOBD_Managed::RetrieveRealTimeParameters() {
	ParserNative->SetResponseOrError(ParserManaged::GetReponseOrError());
	ParserNative->RetrieveRealTimeParameters();
}

Dictionary<ParserBridge::MultipleReadData, double>^ ParserBridge::ParserOBD_Managed::GetInterpretedRealTimeParameters() {
	ParserManaged::SetInterpretedRealTimeInformation(ParserNative->GetInterpretedRealTimeParameters());
	return ParserManaged::GetInterpretedRealTimeParameters();
}

ParserBridge::ParserOBD_Managed::~ParserOBD_Managed() {
	delete ParserNative;
}

ParserBridge::ParserOBD_CAN_Managed::ParserOBD_CAN_Managed() {
	ParserNative = new NativeParser::ParserOBD_CAN;

	if (!ParserNative)
		throw gcnew OutOfMemoryException("Nie dalo sie zaalokowac pamieci");
}

void ParserBridge::ParserOBD_CAN_Managed::RetrieveRealTimeParameters() {
	ParserNative->SetResponseOrError(ParserManaged::GetReponseOrError());
	ParserNative->RetrieveRealTimeParameters();
}

Dictionary<ParserBridge::MultipleReadData, double>^ ParserBridge::ParserOBD_CAN_Managed::GetInterpretedRealTimeParameters() {
	ParserManaged::SetInterpretedRealTimeInformation(ParserNative->GetInterpretedRealTimeParameters());
	return ParserManaged::GetInterpretedRealTimeParameters();
}

void ParserBridge::ParserOBD_CAN_Managed::RetrieveSentCommands() {
	try {
		ParserNative->RetrieveSentCommands();
	}
	catch (exception& exc) {
		throw gcnew Exception(gcnew String(exc.what()));
	}
}

ParserBridge::ParserOBD_CAN_Managed::~ParserOBD_CAN_Managed() {
	delete ParserNative;
}

ParserBridge::ParserProxy::ParserProxy(ParserBridge::ParserManaged^ Target) :Target(Target) {}

void ParserBridge::ParserProxy::RetrieveRealTimeParameters() {
	Target->RetrieveRealTimeParameters();
 }