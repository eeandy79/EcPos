/******************************************************************************
*  Source File: Server.cpp
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

#include "Server.h"

PosServer::PosServer(utility::string_t url) : m_listener(url)
{
	m_listener.support(methods::GET, std::bind(&PosServer::handle_get, this, std::placeholders::_1));
	m_listener.support(methods::PUT, std::bind(&PosServer::handle_put, this, std::placeholders::_1));
	m_listener.support(methods::POST, std::bind(&PosServer::handle_post, this, std::placeholders::_1));
	m_listener.support(methods::DEL, std::bind(&PosServer::handle_delete, this, std::placeholders::_1));
}

void PosServer::handle_get(http_request message)
{
	printf("handle_get\n");
	ucout << message.to_string() << endl;
	message.reply(status_codes::Forbidden, U("Unrecognized request"));
};

void PosServer::handle_post(http_request message)
{
	printf("handle_post\n");
	ucout << message.to_string() << endl;
	message.reply(status_codes::Forbidden, U("Unrecognized request"));
};

void PosServer::handle_delete(http_request message)
{
	printf("handle_delete\n");
	ucout << message.to_string() << endl;
	message.reply(status_codes::Forbidden, U("Unrecognized request"));
};


void PosServer::handle_put(http_request message)
{
	printf("handle_put\n");
	ucout << message.to_string() << endl;

	auto paths = uri::split_path(uri::decode(message.relative_uri().path()));
	auto query = uri::split_query(uri::decode(message.relative_uri().query()));

	auto json = message.extract_json().get();

	if (json.is_array()) {
		auto items = json.as_array();
		for (int i = 0; i < items.size(); i++) {
			ucout << items.at(i).as_object()[L"guid"] << " " << items.at(i).as_object()[L"name"] << endl;
		}
	}

	message.reply(status_codes::Forbidden, U("Unrecognized request"));
};