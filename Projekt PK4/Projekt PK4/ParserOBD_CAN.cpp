#include"Parser.h"

#include<algorithm>

using namespace NativeParser;

void ParserOBD_CAN::RetrieveRealTimeParameters() {
	// np. 41 0B 21 04 3F 0C 17 B8 05 44 00 00 00

	RetrieveResponse();

	FullMessage = MessageOnly;

	try {
		RetrieveSentCommands();
	}
	catch (exception& exc) {
		throw;
	}

	size_t NextCommand = 0;
	size_t CommandFound;

	pair<int, string> CommandAndValue;

	for(int i = 0; i < FullMessage.length(); i += 6) {
		
		CommandFound = NextCommand;

		MessageOnly.assign(next(FullMessage.begin(), CommandFound), next(FullMessage.begin(), NextCommand += 6));

		try {
		CommandAndValue = RetrieveCommandAndValue();
		}
		catch (exception& exc) {
			throw;
		}

		InsertIntoRealTimeParametersMap(CommandAndValue.first, CommandAndValue.second);
	}
}

void ParserOBD_CAN::RetrieveSentCommands() {
	string::iterator RestOfMessageOffset = adjacent_find(ResponseOrError.begin(), ResponseOrError.end(), CompareTokens);

	if (RestOfMessageOffset != ResponseOrError.end()) {
		SentCommands.assign(ResponseOrError.begin() + 3, RestOfMessageOffset);
	}
	else
		throw exception("Nie mozna wyodrebnic komend");
}