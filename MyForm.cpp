#include "MyForm.h"

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
    char* sip_domain = "192.168.39.18";
    char* sip_realm = "*";
    char* sip_user = "3460210";
    char* sip_password = "2";
    char* sip_port = "5060";
    char* phone_number;
    int repetition_limit = 3;
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
static void error_exit(const char* title, pj_status_t status)
{
    if (play_id != -1) pjsua_player_destroy(play_id);
    if (rec_id != -1) pjsua_recorder_destroy(rec_id);
    pjsua_perror("MyForm", title, status);
    pjsua_call_hangup_all();
    pjsua_destroy();
    exit(1);
}
// handler for call-media-state-change-events
static void on_call_media_state(pjsua_call_id call_id)
{	// get call infos
	pjsua_call_info ci;
	pjsua_call_get_info(call_id, &ci);
	pj_status_t status;
    for (unsigned i = 0; i < ci.media_cnt; ++i) {
        if (ci.media[i].type == PJMEDIA_TYPE_AUDIO) {
            switch (ci.media[i].status) {
            case PJSUA_CALL_MEDIA_ACTIVE:
                pjsua_conf_connect(ci.media[i].stream.aud.conf_slot, 0);
                pjsua_conf_connect(0, ci.media[i].stream.aud.conf_slot);
                break;
            default:
                break;
            }
        }
    }
}
// handler for call-state-change-events
static void on_call_state(pjsua_call_id call_id, pjsip_event* e)
{	// get call infos
	pjsua_call_info ci;
	pjsua_call_get_info(call_id, &ci);
	// prevent warning about unused argument e
	PJ_UNUSED_ARG(e);
	// check call state
	if (ci.state == PJSIP_INV_STATE_DISCONNECTED)
	{	// exit app if call is finished/disconnected
		app_exit();
	}
}
    // incoming call notice
static void on_incoming_call(pjsua_acc_id acc_id, pjsua_call_id call_id, pjsip_rx_data* rdata) {
    PJ_UNUSED_ARG(acc_id);
    PJ_UNUSED_ARG(rdata);
    pj_status_t status;
    pjsua_call_info ci;
    char info[80];
    pjsua_call_get_info(call_id, &ci);
    status = pjsua_call_answer(call_id, 200, NULL, NULL);
    snprintf(info, sizeof(info), "Incoming call from %.*s", (int)ci.remote_info.slen, ci.remote_info.ptr);
}
void SIPclient::MyForm::CallBtn_Click(System::Object^ sender, System::EventArgs^ e) {
    label4->Text += "Starting call ... ";
    // build target sip-url
    char sip_target_url[40];
    sprintf(sip_target_url, "sip:%s@%s;transport=tcp", app_cfg.phone_number, app_cfg.sip_domain);//;transport=tcp
    // start call with sip-url
    pj_str_t uri = pj_str(sip_target_url);
    status = pjsua_call_make_call(acc_id, &uri, 0, NULL, NULL, NULL);
    system("pause");
    if (status != PJ_SUCCESS) error_exit("Error making call", status);
}
void SIPclient::MyForm::DeclineBtn_Click(System::Object^ sender, System::EventArgs^ e) {
    pjsua_call_hangup_all();
}
void SIPclient::MyForm::ServerIPTxt_TextChanged(System::Object^ sender, System::EventArgs^ e) {
    app_cfg.sip_domain = (char*)(System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(serverIPTxt->Text)).ToPointer();
}
void SIPclient::MyForm::PortTxt_TextChanged(System::Object^ sender, System::EventArgs^ e) {
    app_cfg.sip_port = (char*)(System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(portTxt->Text)).ToPointer();
}
void SIPclient::MyForm::userTxt_TextChanged(System::Object^ sender, System::EventArgs^ e) {
    app_cfg.sip_user = (char*)(System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(userTxt->Text)).ToPointer();
}
void SIPclient::MyForm::pswdTxt_TextChanged(System::Object^ sender, System::EventArgs^ e) {
    app_cfg.sip_password = (char*)(System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(pswdTxt->Text)).ToPointer();
}
void SIPclient::MyForm::clientTxt_TextChanged(System::Object^ sender, System::EventArgs^ e) {
    app_cfg.phone_number = (char*)(System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(clientTxt->Text)).ToPointer();;
}
void SIPclient::MyForm::RegisterBtn_Click(System::Object^ sender, System::EventArgs^ e) {
    label4->Text += "Registering account ... ";
    // prepare account configuration
    pjsua_acc_config cfg;
    pjsua_acc_config_default(&cfg);
    // build sip-user-url
    char sip_user_url[40];
    sprintf(sip_user_url, "sip:%s@%s", app_cfg.sip_user, app_cfg.sip_domain);
    // build sip-provder-url
    char sip_provider_url[40];
    sprintf(sip_provider_url, "sip:%s;transport=tcp", app_cfg.sip_domain);//;transport=tcp
    // create and define account
    cfg.id = pj_str(sip_user_url);
    cfg.reg_uri = pj_str(sip_provider_url);
    cfg.cred_count = 2;
    cfg.cred_info[0].realm = pj_str(app_cfg.sip_realm);
    cfg.cred_info[0].scheme = pj_str("digest");
    cfg.cred_info[0].username = pj_str(app_cfg.sip_user);
    cfg.cred_info[0].data_type = PJSIP_CRED_DATA_PLAIN_PASSWD;
    cfg.cred_info[0].data = pj_str(app_cfg.sip_password);
    // add account
    status = pjsua_acc_add(&cfg, PJ_TRUE, &acc_id);
    if (status != PJ_SUCCESS) error_exit("Error adding account", status);
    if (status == PJ_SUCCESS) label4->Text += "Done.\n";
}
void SIPclient::MyForm::start_sip_stack()
{
    status = pjsua_create();
    if (status != PJ_SUCCESS)
        error_exit("Error in pjsua_create()", status);
    pjsua_config cfg;
    pjsua_config_default(&cfg);
    // enable just 1 simultaneous call 
    cfg.max_calls = 1;
    // callback configuration		
    //fg.cb.on_incoming_call = &on_incoming_call;
    cfg.cb.on_call_media_state = &on_call_media_state;
    cfg.cb.on_call_state = &on_call_state;
    // initialize pjsua 
    status = pjsua_init(&cfg, NULL, NULL);
    if (status != PJ_SUCCESS) error_exit("Error in pjsua_init()", status);
    // add TCP transport
    pjsua_transport_config tcfg;
    pjsua_transport_config_default(&tcfg);
    tcfg.port = 5060;
    status = pjsua_transport_create(PJSIP_TRANSPORT_TCP, &tcfg, NULL);
    if (status != PJ_SUCCESS) error_exit("Error creating transport", status);
    status = pjsua_start();
    if (status != PJ_SUCCESS) error_exit("Error starting pjsua", status);

}
void SIPclient::MyForm::stop_sip_stack() { app_exit(); }