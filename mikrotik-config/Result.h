#pragma once

using namespace System;

ref class CResult
{

private:
	String ^clientComment;
	String ^clientIp;
	String ^ipPublic;


public:

	String ^ SetClientComment(String ^ comment);
	String ^ SetIpPublic(String ^ ip);
	String ^ SetClientIp(String ^ ip);

	String ^ GetClient();
	String ^ GetIpPublic();
	String ^ GetIpClient();


	CResult(void);

};
