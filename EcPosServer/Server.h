/******************************************************************************
*  Header File: Server.h
*  Description: HTTP servier to handle JSON message
*
*  Copyright (c) EcSoft, 2015
*
*  This unpublished material is proprietary to EcSoft.All rights reserved. 
*  The methods and techniques described herein are considered trade secrets 
*  and/or confidential. Reproduction or distribution, in whole or in part, is 
*  forbidden except by express written permission of EcSoft.
*
*******************************************************************************/

#ifndef __SERVER_H__
#define __SERVER_H__

#include "cpprest/details/basic_types.h"
#include "cpprest/http_listener.h"
#include "cpprest/http_msg.h"
#include "pplx/pplxtasks.h"

using namespace std;
using namespace web;
using namespace utility;
using namespace http;
using namespace web::http::experimental::listener;
	
class PosServer
{
public:
	PosServer() { }
	PosServer(utility::string_t url);

	pplx::task<void> open() { return m_listener.open(); }
	pplx::task<void> close() { return m_listener.close(); }

private:

	void handle_get(http_request message);
	void handle_put(http_request message);
	void handle_post(http_request message);
	void handle_delete(http_request message);

	http_listener m_listener;
};


#endif