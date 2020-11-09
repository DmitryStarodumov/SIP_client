#include "MyForm.h"

#define BIG_DATA_LEN 1024
static char senddata[BIG_DATA_LEN];
static char recvdata[BIG_DATA_LEN];

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
	pj_init();
    Application::Run(% form);
}
//global vars for pjsua
pjsua_player_id play_id = PJSUA_INVALID_ID;
pjmedia_port* play_port;
pjsua_recorder_id rec_id = PJSUA_INVALID_ID;
pjsua_acc_id acc_id;

// struct for app configuration settings
struct app_config {
    char* sip_domain = "192.168.0.107";
    char* sip_realm = "*";
    char* sip_user = "3460210";
    char* sip_password = "2";
    char* sip_port = "5060";
} app_cfg;
static void app_exit()
{   // check if player/recorder is active and stop them
    if (play_id != -1) pjsua_player_destroy(play_id);
    if (rec_id != -1) pjsua_recorder_destroy(rec_id);
    // hangup open calls and stop pjsua
    pjsua_call_hangup_all();
    pjsua_destroy();
    exit(0);
}
/* Callback called by the library upon receiving incoming call */
static void on_incoming_call(pjsua_acc_id acc_id, pjsua_call_id call_id, pjsip_rx_data* rdata)
{
    pjsua_call_info ci;
    pjsua_call_get_info(call_id, &ci);
    /* Automatically answer incoming calls with 200/OK */
    pjsua_call_answer(call_id, 200, NULL, NULL);
}
/* Callback called by the library when call's media state has changed */
static void on_call_media_state(pjsua_call_id call_id)
{
    pjsua_call_info ci;
    pjsua_call_get_info(call_id, &ci);

    if (ci.media_status == PJSUA_CALL_MEDIA_ACTIVE)
    {
        pjsua_conf_connect(ci.conf_slot, 0);
        pjsua_conf_connect(0, ci.conf_slot);
    }
}
// handler for call-state-change-events
static void on_call_state(pjsua_call_id call_id, pjsip_event* e)
{    // get call infos
    pjsua_call_info ci;
    pjsua_call_get_info(call_id, &ci);
    // prevent warning about unused argument e
    PJ_UNUSED_ARG(e);
    // check call state
    if (ci.state == PJSIP_INV_STATE_CONFIRMED)
    {    // ensure that message is played from start
        if (play_id != PJSUA_INVALID_ID)
        {
            pjmedia_wav_player_port_set_pos(play_port, 0);
        }
    }
    if (ci.state == PJSIP_INV_STATE_DISCONNECTED)
    {   // exit app if call is finished/disconnected
        app_exit();
    }
}
/* Display error and exit application */
static void error_exit(const char* title, pj_status_t status)
{
    if (play_id != -1) pjsua_player_destroy(play_id);
    if (rec_id != -1) pjsua_recorder_destroy(rec_id);
    pjsua_perror("MyForm", title, status);
    pjsua_call_hangup_all();
    pjsua_destroy();
    system("pause");
    exit(0);
}
/*
void SIPclient::MyForm::StartClientBtn_Click(System::Object^ sender, System::EventArgs^ e) {
	label4->Text += "Client starting...\n";
	pj_str_t s_ipv4 = pj_str(myAddress);
    pj_str_t s_port = pj_str(app_cfg.sip_port);
	pj_str_t s;
	pj_sock_t sock;
	pj_ssize_t size = BIG_DATA_LEN;
	pj_sock_t ss;
	senddata[size - 1] = '\0';
    recvdata[size - 1] = '\0';

    if ((status = pj_sock_socket(pj_AF_INET(), pj_SOCK_STREAM(), 0, &sock)) != 0)
	{
		label4->Text += "Can't create socket\n";
		pj_sock_close(sock);
		return;
	}
	// Fill in a hint structure

	pj_sockaddr_in hint; //endpoint
    pj_sockaddr_in tmp_addr;
    pj_sockaddr_in_init(&hint, NULL, 0);
	hint.sin_family = pj_AF_INET();
	hint.sin_port = pj_htons(port);
	//hint.sin_addr = pj_inet_addr(pj_cstr(&s, myAddress));
	pj_inet_pton(pj_AF_INET(), &s_ipv4, &hint.sin_addr);

	// Connect to server
	status = pj_sock_connect(sock, &hint, sizeof(hint));
	if (status != 0)
	{
		label4->Text += "Can't connect to server\n";
		pj_sock_close(sock);
		return;
	}
	label4->Text += "Done.\n";
    
	if (senddata > 0) { //Send the text
		int sendResult = pj_sock_send(sock, senddata, &size, 0);
		if (sendResult != PJ_SUCCESS || size != BIG_DATA_LEN) {
			label4->Text += "error sending message\n";
		}
	}
    int bytesReceived = pj_sock_recv(ss, recvdata, &size, 0);//problem here
    if (bytesReceived != PJ_SUCCESS || size != BIG_DATA_LEN) {
        label4->Text += "error recieving message\n";
    }
    else label4->Text += "send/recv ok\n";
       // pj_sock_close(sock);
}
void SIPclient::MyForm::StopClientBtn_Click(System::Object^ sender, System::EventArgs^ e) {
	if (!status) {
		pj_sock_shutdown(sock, how);
		pj_sock_close(sock);
		label4->Text += "Client stopped.\n";
		status = 1;
	}
	else {label4->Text += "Not found any started client\n";}
}
*/
void SIPclient::MyForm::CallBtn_Click(System::Object^ sender, System::EventArgs^ e) {
    label4->Text += "Starting call ... ";
    // build target sip-url
    //sprintf(sip_target_url, "sip:%s@%s", app_cfg.phone_number, app_cfg.sip_domain);
    //sprintf(sip_target_url, "sip:%s@192.168.172.1", app_cfg.phone_number, app_cfg.sip_domain);
    char sip_reg_uri[40];
    sprintf(sip_reg_uri, "sip:%s:%s;transport=tcp", app_cfg.sip_domain, app_cfg.sip_port);
    // start call with sip-url
    pj_str_t uri = pj_str(sip_reg_uri);
    status = pjsua_call_make_call(acc_id, &uri, 0, NULL, NULL, NULL);
    if (status != PJ_SUCCESS) error_exit("Error making call", status);
    if (status == PJ_SUCCESS) label4->Text += "Done.\n";
}
void SIPclient::MyForm::DeclineBtn_Click(System::Object^ sender, System::EventArgs^ e) {
    //pjsua_call_hangup(acc_id, 0, NULL, NULL);
    pjsua_call_hangup_all();
    if (acc_id != -1) {pjsua_acc_del(acc_id);}
    pjsua_destroy();
    system("pause");
}
void SIPclient::MyForm::ServerIPTxt_TextChanged(System::Object^ sender, System::EventArgs^ e) {
    app_cfg.sip_domain = (char*)(System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(serverIPTxt->Text)).ToPointer();
}
void SIPclient::MyForm::PortTxt_TextChanged(System::Object^ sender, System::EventArgs^ e) {
	port = System::Convert::ToInt32(portTxt->Text);
    app_cfg.sip_port = (char*)(System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(portTxt->Text)).ToPointer();
}
void SIPclient::MyForm::userTxt_TextChanged(System::Object^ sender, System::EventArgs^ e) {
    app_cfg.sip_user = (char*)(System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(userTxt->Text)).ToPointer();
}
void SIPclient::MyForm::pswdTxt_TextChanged(System::Object^ sender, System::EventArgs^ e) {
    app_cfg.sip_password = (char*)(System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(pswdTxt->Text)).ToPointer();
}
void SIPclient::MyForm::RegisterBtn_Click(System::Object^ sender, System::EventArgs^ e) {
    label4->Text += "Registering account ... ";
    // prepare account configuration
    pjsua_acc_config cfg;
    pjsua_acc_config_default(&cfg);
    // build sip-user-url
    char sip_user_url[40];
    sprintf(sip_user_url, "sip:%s@%s:%s", app_cfg.sip_user, app_cfg.sip_domain, app_cfg.sip_port);
    //sprintf(sip_user_url, "sip:3460210@192.168.39.18:5060");
   
    // build sip-provder-url
    char sip_provider_url[40];
    sprintf(sip_provider_url, "sip:%s:%s;transport=tcp", app_cfg.sip_domain, app_cfg.sip_port);
    //sprintf(sip_provider_url, "sip:192.168.39.18:5060;transport=tcp");
    // create and define account
    cfg.id = pj_str(sip_user_url);
    cfg.reg_uri = pj_str(sip_provider_url);
    cfg.cred_count = 1;
    cfg.cred_info[0].realm = pj_str(app_cfg.sip_realm);
    cfg.cred_info[0].scheme = pj_str("digest");
    cfg.cred_info[0].username = pj_str(app_cfg.sip_user);
    cfg.cred_info[0].data_type = PJSIP_CRED_DATA_PLAIN_PASSWD;
    cfg.cred_info[0].data = pj_str(app_cfg.sip_password);
    // add account
    status = pjsua_acc_add(&cfg, PJ_TRUE, &acc_id);
    if (status != PJ_SUCCESS) error_exit("Error adding account", status);
    status = pjsua_start();
    if (status != PJ_SUCCESS) error_exit("Error starting pjsua", status);
    if (status == PJ_SUCCESS) label4->Text += "Done.\n";
}
void SIPclient::MyForm::start_sip_stack()
{
    pjsua_transport_id tcp_tp_id;
    status = pjsua_create();
    if (status != PJ_SUCCESS)
        error_exit("Error in pjsua_create()", status);
    pjsua_config cfg;
    pjsua_config_default(&cfg);
    // enable just 1 simultaneous call 
    cfg.max_calls = 1;
    // callback configuration		
    cfg.cb.on_incoming_call = &on_incoming_call;
    cfg.cb.on_call_media_state = &on_call_media_state;
    cfg.cb.on_call_state = &on_call_state;
    // initialize pjsua 
    status = pjsua_init(&cfg, NULL, NULL);
    if (status != PJ_SUCCESS) error_exit("Error in pjsua_init()", status);
    // add TCP transport
    pjsua_transport_config tcfg;
    pjsua_transport_config_default(&tcfg);
    tcfg.port = port;
    status = pjsua_transport_create(PJSIP_TRANSPORT_TCP, &tcfg, &tcp_tp_id);
    if (status != PJ_SUCCESS) error_exit("Error creating transport", status);
}
void SIPclient::MyForm::stop_sip_stack() { app_exit(); }

/*
void SIPclient::MyForm::AdjustTranVolume(pjsua_call_id call_id, float level)
{
    pjsua_call_info ci;
    pjsua_call_get_info(call_id, &ci);
#ifdef DEBUG
    unsigned tx_level = 0;
    unsigned rx_level = 0;
    status = pjsua_conf_get_signal_level(ci.conf_slot, &tx_level, &rx_level);
    if (status != PJ_SUCCESS)
        error_exit("Error get signal level", status);
#endif
    status = pjsua_conf_adjust_tx_level(ci.conf_slot, level);
    if (status != PJ_SUCCESS)
        error_exit("Error adjust tx level", status);
}

void SIPclient::MyForm::AdjustRecvVolume(pjsua_call_id call_id, float level)
{
    pjsua_call_info ci;
    pjsua_call_get_info(call_id, &ci);

#ifdef DEBUG
    unsigned tx_level = 0;
    unsigned rx_level = 0;
    status = pjsua_conf_get_signal_level(ci.conf_slot, &tx_level, &rx_level);
    if (status != PJ_SUCCESS)
        error_exit("Error get signal level", status);
#endif
    status = pjsua_conf_adjust_rx_level(ci.conf_slot, level);
    if (status != PJ_SUCCESS)
        error_exit("Error adjust rx level", status);
}
*/
