#include"Parser.h"

using namespace std;
using namespace NativeParser;

void ParserOBD::RetrieveRealTimeParameters() {
	// np. 41 0D 00
	RetrieveResponse();

	try {
		pair<int, string> CommandAndValue = RetrieveCommandAndValue();
		InsertIntoRealTimeParametersMap(CommandAndValue.first, CommandAndValue.second);
	}
	catch (exception& exc) {
		throw;
	}
}