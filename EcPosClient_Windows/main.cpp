/******************************************************************************
*  Source File: main.cpp
*  Description: Main entry point of the server program
*
*  Copyright (c) EcSoft, 2015
*
*  This unpublished material is proprietary to EcSoft.All rights reserved.
*  The methods and techniques described herein are considered trade secrets
*  and/or confidential. Reproduction or distribution, in whole or in part, is
*  forbidden except by express written permission of EcSoft.
*
*******************************************************************************/

#include <string>
#include <stdio.h>
#include <share.h>
#include "cpprest/json.h"
#include "cpprest/details/basic_types.h"
#include "cpprest/base_uri.h"
#include "cpprest/http_client.h"
#include "cpprest/http_msg.h"
#include "pplx/pplxtasks.h"

using namespace std;
using namespace web;
using namespace utility;
using namespace http;
using namespace web::http;
using namespace std;
void main()
{
	utility::string_t port = U("34568");
	utility::string_t address = U("http://localhost:");
	address.append(port);
	http::uri uri = http::uri(address);
	client::http_client aClient(http::uri_builder(uri).append_path(U("EcPos")).to_uri());

	std::vector<json::value> itemList;
	for (int i = 0; i < 10; i++)
	{
		auto item = json::value::object();
		item[L"name"] = json::value::string(L"coffee");
		item[L"guid"] = json::value::string(L"d1f2ca8c-a537-41a9-8c25-ef156a82d90f");
		itemList.push_back(item);
	}

	auto menu = json::value::array(itemList);

	ucout << aClient.request(methods::PUT, L"order/new?name=andy", menu).get().to_string() << endl;
}
