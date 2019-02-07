#include "StdAfx.h"
#include "CmdGen.h"


CCmdGen::CCmdGen(void)
{
}


int CCmdGen::GetPublicIpLines()
{
	return linesIpPublic;
}


int CCmdGen::GetClientLines()
{
	return linesClient;
}


int CCmdGen::SetOperation(String ^ value)
{

	operation = value;

	return 0;
}



String ^ CCmdGen::ParseIpPublics(String ^ input)
{

	return input;

}



int CCmdGen::SetAction(String ^ value)
{

	action = value;

	return 0;
}



int CCmdGen::SetComment(String ^ value)
{

	comment = value;

	return 0;
}


int CCmdGen::SetSrcAddress(String ^ value)
{
	srcAddress = value;

	return 0;
}


int CCmdGen::SetToAddress(String ^ value)
{

	toAdress = value;

	return 0;
}


int CCmdGen::SetChain(String ^ value)
{
	chain = value;

	return 0;
}


array<CResult ^>  ^ CCmdGen::Results()
{

	array<CResult ^>  ^ retResult;

	return retResult;
}


String ^ CCmdGen::ReadInputs(String ^ clientsList, String ^ ipList)
{

	TextReader ^clientRdr = gcnew StringReader(clientsList);
	TextReader ^ipRdr = gcnew StringReader(ipList);
	String ^lineClient;
	String ^lineIp;
	String ^ip;
	String ^cmdResult;
	array <String ^> ^arrayClients;
	arrayResult = gcnew array <CResult ^>(5000);
	int indexResult = 0;


	//Read line by line clientRdr ...
    while (lineClient = clientRdr->ReadLine())
    {

		//Read line by line ipRdr ...
	    lineIp = ipRdr->ReadLine();

		linesClient++;

		if(lineIp == nullptr)
			break;

			else
			{
				linesIpPublic++;
			}			


		if(lineIp->Length > 0 && lineClient->Length > 0)
		{

			arrayClients = ParseClients(lineClient);

			if(arrayClients[0]->Length > 0 && arrayClients[1]->Length > 0)
			{

				ip = ParseIpPublics(lineIp);

				SetOperation("add");
				SetAction("netmap");
				SetChain("srcnat");				
				SetComment(arrayClients[0]);				
				SetSrcAddress(arrayClients[1]);
				SetToAddress(ip);

				arrayResult[indexResult] = gcnew CResult();
				arrayResult[indexResult]->SetIpPublic(ip);
				arrayResult[indexResult]->SetClientComment(arrayClients[0]);
				arrayResult[indexResult]->SetClientIp(arrayClients[1]);				
				indexResult++;


				if(cmdResult != nullptr)
					cmdResult = cmdResult + "\r\n\r\n" + FwNat(true);

				else
					cmdResult = cmdResult + FwNat(true);

			}
		}
	}

	Array::Resize(arrayResult, indexResult);
	return cmdResult;

}



array<String ^ > ^ CCmdGen::ParseClients(String ^ input)
{


	//Split IP
	String ^ pattern = "(\\d{1,3}(\\.\\d{1,3}){3})";
	TextReader ^ txtReader = gcnew StringReader(input);
	String ^ line;
	Match ^ rExpr;
	Group ^ groupComment;
	int indexComment;
	array<String^>^ arrayReturn = gcnew array<String^> {"comment",  "ipPrivate"};


	//Read line by line ...
    while ((line = txtReader->ReadLine()))
    {

		// Evaluate regular expression
		rExpr = Regex::Match(line, pattern);

		groupComment = rExpr->Groups[0];
		indexComment = groupComment->Index;
		arrayReturn[0] = line->Substring(0, indexComment);
		arrayReturn[1] = rExpr->Value;


		Console::WriteLine(line);


    }


	return arrayReturn;
}



String ^ CCmdGen::FwNat(bool pair)
{	

	String ^ strResult;


    strResult = "/ip firewall nat " + operation +
				" action=" + action + " chain=" + chain +
                " comment=\"" + comment + "\"" +
                " src-address=" + srcAddress +
                " to-address=" + toAdress;

	strResult =  strResult + "\r\n";



	if(pair == true)
	{

		strResult = strResult + "/ip firewall nat " + operation +
					" action=" + action + " chain=dstnat" +
					" comment=\'" + comment + "\'" +
					" dst-address=\'" + toAdress + "\'" +
					" to-address=" + srcAddress;
	}


	return strResult;

}


