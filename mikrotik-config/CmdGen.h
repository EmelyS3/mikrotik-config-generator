#pragma once

#include "result.h"

using namespace System;
using namespace Text::RegularExpressions;
using namespace IO;

ref class CCmdGen
{

private:

	 String ^ operation;
	 String ^ action;
	 String ^ chain;
	 String ^ comment;
	 String ^ ip;
	 String ^ srcAddress;
	 String ^ toAdress;
	 int linesClient;
	 int linesIpPublic;

public:

	array <CResult ^> ^arrayResult;

	CCmdGen(void);
	int GetPublicIpLines();
	String ^ ReadInputs(String ^ clientsList, String ^ ipList);
	array<String ^ > ^ ParseClients(String ^ input);
	String ^ ParseIpPublics(String ^ input);

	int SetOperation(String ^ value);
	int SetChain(String ^ value);
	int SetAction(String ^ value);
	int SetComment(String ^ value);
	int SetSrcAddress(String ^ value);
	int SetToAddress(String ^ value);
	int GetClientLines();
	array<CResult ^>  ^ Results();

	String ^ FwNat(bool pair);	

};
