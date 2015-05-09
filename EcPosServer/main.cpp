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
#include "Server.h"

using namespace std;

std::unique_ptr<PosServer> g_PosServer;

void on_initialize(const string_t& address)
{
	uri_builder uri(address);
	uri.append_path(U("EcPos"));

	auto addr = uri.to_uri().to_string();
	g_PosServer = std::unique_ptr<PosServer>(new PosServer(addr));
	g_PosServer->open().wait();

	ucout << utility::string_t(U("Listening for requests at: ")) << addr << std::endl;

	return;
}

void on_shutdown()
{
	g_PosServer->close().wait();
	return;
}

int main(int argc, char *argv[])
{
	auto server = std::make_shared<PosServer>();

	utility::string_t port = U("34568");
	utility::string_t address = U("http://localhost:");
	address.append(port);

	on_initialize(address);
	std::cout << "Press ENTER to exit." << std::endl;

	std::string line;
	std::getline(std::cin, line);

	on_shutdown();
	return 0;
}