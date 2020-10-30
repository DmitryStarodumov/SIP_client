#include "MyForm.h"
#include <iostream>

#define TCP_PORT (3487)

#define ADDRESS "127.0.0.1"
#define BIG_DATA_LEN 8192

static char bigdata[BIG_DATA_LEN];
static char bigbuffer[BIG_DATA_LEN];

#if defined(PJ_SOCKADDR_HAS_LEN) && PJ_SOCKADDR_HAS_LEN!=0
# define CHECK_SA_ZERO_LEN(addr, ret) \
if (((pj_addr_hdr*)(addr))->sa_zero_len != 0) \
return ret
#else
# define CHECK_SA_ZERO_LEN(addr, ret)
#endif

using namespace std;
using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;

[STAThread]
void main() {
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	SIPclient::MyForm form;
	Application::Run(% form);
}


System::Void StartClientBtn_Click(System::Object^ sender, System::EventArgs^ e) {
	pj_str_t s_ipv4 = pj_str(ADDRESS);
	pj_str_t s;
	// Create socket
	pj_sock_t sock = pj_sock_socket(PJ_AF_INET, PJ_SOCK_STREAM, 0, 0);
	if (sock != 0)
	{
		cerr << "Can't create socket" << endl;
		pj_sock_close(sock);
		return;
	}
	// Fill in a hint structure
	pj_sockaddr_in hint;
	hint.sin_family = PJ_AF_INET;
	hint.sin_port = pj_htons(TCP_PORT);
	hint.sin_addr = pj_inet_addr(pj_cstr(&s, ADDRESS));
	/*if ((sock = pj_sock_bind(sock, &hint, sizeof(hint))) != 0) {
		cerr << "...bind error" << endl;
	}*///for server part

	pj_inet_pton(pj_AF_INET(), &s_ipv4, &hint.sin_addr);
	// Connect to server
	int conResult = pj_sock_connect(sock, &hint, sizeof(hint));
	if (conResult != 0)
	{
		cerr << "Can't connect to server" << endl;
		pj_sock_close(sock);
		return;
	}
	//Do-while loop to send and receive data
	pj_ssize_t size = BIG_DATA_LEN;
	do
	{ //Prompt the user for some text
		cout << "> ";
		cin.get(bigdata, BIG_DATA_LEN);
		if (bigdata > 0)		// Make sure the user has typed in something
		{ //Send the text
			int sendResult = pj_sock_send(sock, bigdata, &size, 0);
			if (sendResult != PJ_INVALID_SOCKET)
			{ //Wait for response
				pj_bzero(bigdata, sizeof(BIG_DATA_LEN));
				size = 100;
				int bytesReceived = pj_sock_recv(sock, bigdata, &size, 0);
				if (bytesReceived > 0)
				{ //Echo response to console
					cout << "SERVER> " << string(bigdata, 0, bytesReceived) << endl;
				}
			}
		}
	} while (bigdata > 0);
}

System::Void StopClientBtn_Click(System::Object^ sender, System::EventArgs^ e) {
	// Gracefully close down everything

}

System::Void SendMsgBtn_Click(System::Object^ sender, System::EventArgs^ e) {

}

System::Void CallBtn_Click(System::Object^ sender, System::EventArgs^ e) {

}

System::Void DeclineBtn_Click(System::Object^ sender, System::EventArgs^ e) {

}