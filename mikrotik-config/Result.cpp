#include "StdAfx.h"
#include "Result.h"

CResult::CResult(void)
{
}


String ^ CResult::GetClient()
{
	return clientComment;
}


String ^ CResult::SetClientComment(String ^ comment)
{
	clientComment = comment;
	return clientComment;
}


String ^ CResult::SetIpPublic(String ^ ip)
{
	ipPublic = ip;
	return ipPublic;
}


String ^ CResult::GetIpPublic()
{
	return ipPublic;
}

String ^ CResult::GetIpClient()
{
	return clientIp;
}


String ^ CResult::SetClientIp(String ^ ip)
{

	clientIp = ip;
	return clientIp;
}
