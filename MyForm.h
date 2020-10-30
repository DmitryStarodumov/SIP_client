#pragma once
#ifndef MYFORM_H
#define MYFORM_H

#include <pjlib.h>
#include <pjlib-util.h>
#include <pjnath.h>
#include <pjsip.h>
#include <pjsip_ua.h>
#include <pjsip_simple.h>
#include <pjsua-lib/pjsua.h>
#include <pjmedia.h>
#include <pjmedia-codec.h>
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

namespace SIPclient {

	using namespace std;
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void) {InitializeComponent();}
	protected:
		~MyForm() {if (components) delete components;}

	private: System::Windows::Forms::Button^ CallBtn;
	private: System::Windows::Forms::Button^ DeclineBtn;
	private: System::Windows::Forms::TextBox^ textBox2;
	private: System::Windows::Forms::TextBox^ textBox1;
	private: System::Windows::Forms::TextBox^ textBox3;
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::Label^ label3;
	private: System::Windows::Forms::Button^ StartClientBtn;
	private: System::Windows::Forms::Button^ StopClientBtn;
	private: System::Windows::Forms::TextBox^ SendMsgBox;
	private: System::Windows::Forms::Button^ SendMsgBtn;
	private: System::Windows::Forms::Panel^ panel1;
	private: System::Windows::Forms::Label^ label4;
	private: System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code
		   /// <summary>
		   /// ��������� ����� ��� ��������� ������������ � �� ��������� 
		   /// ���������� ����� ������ � ������� ��������� ����.
		   /// </summary>
		   void InitializeComponent(void)
		   {
			   this->CallBtn = (gcnew System::Windows::Forms::Button());
			   this->DeclineBtn = (gcnew System::Windows::Forms::Button());
			   this->textBox2 = (gcnew System::Windows::Forms::TextBox());
			   this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			   this->textBox3 = (gcnew System::Windows::Forms::TextBox());
			   this->label1 = (gcnew System::Windows::Forms::Label());
			   this->label2 = (gcnew System::Windows::Forms::Label());
			   this->label3 = (gcnew System::Windows::Forms::Label());
			   this->StartClientBtn = (gcnew System::Windows::Forms::Button());
			   this->StopClientBtn = (gcnew System::Windows::Forms::Button());
			   this->SendMsgBox = (gcnew System::Windows::Forms::TextBox());
			   this->SendMsgBtn = (gcnew System::Windows::Forms::Button());
			   this->panel1 = (gcnew System::Windows::Forms::Panel());
			   this->label4 = (gcnew System::Windows::Forms::Label());
			   this->panel1->SuspendLayout();
			   this->SuspendLayout();
			   // 
			   // CallBtn
			   // 
			   this->CallBtn->Anchor = System::Windows::Forms::AnchorStyles::None;
			   this->CallBtn->Location = System::Drawing::Point(231, 87);
			   this->CallBtn->Name = L"CallBtn";
			   this->CallBtn->Size = System::Drawing::Size(75, 25);
			   this->CallBtn->TabIndex = 1;
			   this->CallBtn->Text = L"Call";
			   this->CallBtn->UseVisualStyleBackColor = true;
			   this->CallBtn->Click += gcnew System::EventHandler(this, &MyForm::CallBtn_Click);
			   // 
			   // DeclineBtn
			   // 
			   this->DeclineBtn->Anchor = System::Windows::Forms::AnchorStyles::None;
			   this->DeclineBtn->Location = System::Drawing::Point(306, 87);
			   this->DeclineBtn->Name = L"DeclineBtn";
			   this->DeclineBtn->Size = System::Drawing::Size(75, 25);
			   this->DeclineBtn->TabIndex = 2;
			   this->DeclineBtn->Text = L"Decline";
			   this->DeclineBtn->UseVisualStyleBackColor = true;
			   this->DeclineBtn->Click += gcnew System::EventHandler(this, &MyForm::DeclineBtn_Click);
			   // 
			   // textBox2
			   // 
			   this->textBox2->Anchor = System::Windows::Forms::AnchorStyles::None;
			   this->textBox2->Location = System::Drawing::Point(231, 10);
			   this->textBox2->Name = L"textBox2";
			   this->textBox2->Size = System::Drawing::Size(150, 20);
			   this->textBox2->TabIndex = 3;
			   // 
			   // textBox1
			   // 
			   this->textBox1->Anchor = System::Windows::Forms::AnchorStyles::None;
			   this->textBox1->Location = System::Drawing::Point(231, 35);
			   this->textBox1->Name = L"textBox1";
			   this->textBox1->Size = System::Drawing::Size(150, 20);
			   this->textBox1->TabIndex = 3;
			   // 
			   // textBox3
			   // 
			   this->textBox3->Anchor = System::Windows::Forms::AnchorStyles::None;
			   this->textBox3->Location = System::Drawing::Point(231, 61);
			   this->textBox3->Name = L"textBox3";
			   this->textBox3->Size = System::Drawing::Size(150, 20);
			   this->textBox3->TabIndex = 3;
			   // 
			   // label1
			   // 
			   this->label1->Anchor = System::Windows::Forms::AnchorStyles::None;
			   this->label1->AutoSize = true;
			   this->label1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 11.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				   static_cast<System::Byte>(204)));
			   this->label1->Location = System::Drawing::Point(387, 12);
			   this->label1->Name = L"label1";
			   this->label1->Size = System::Drawing::Size(48, 18);
			   this->label1->TabIndex = 5;
			   this->label1->Text = L"Name";
			   // 
			   // label2
			   // 
			   this->label2->Anchor = System::Windows::Forms::AnchorStyles::None;
			   this->label2->AutoSize = true;
			   this->label2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 11.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				   static_cast<System::Byte>(204)));
			   this->label2->Location = System::Drawing::Point(387, 37);
			   this->label2->Name = L"label2";
			   this->label2->Size = System::Drawing::Size(79, 18);
			   this->label2->TabIndex = 5;
			   this->label2->Text = L"IP Address";
			   // 
			   // label3
			   // 
			   this->label3->Anchor = System::Windows::Forms::AnchorStyles::None;
			   this->label3->AutoSize = true;
			   this->label3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 11.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				   static_cast<System::Byte>(204)));
			   this->label3->Location = System::Drawing::Point(387, 63);
			   this->label3->Name = L"label3";
			   this->label3->Size = System::Drawing::Size(36, 18);
			   this->label3->TabIndex = 5;
			   this->label3->Text = L"Port";
			   // 
			   // StartClientBtn
			   // 
			   this->StartClientBtn->Anchor = System::Windows::Forms::AnchorStyles::None;
			   this->StartClientBtn->Location = System::Drawing::Point(57, 306);
			   this->StartClientBtn->Name = L"StartClientBtn";
			   this->StartClientBtn->Size = System::Drawing::Size(75, 25);
			   this->StartClientBtn->TabIndex = 1;
			   this->StartClientBtn->Text = L"Start Client";
			   this->StartClientBtn->UseVisualStyleBackColor = true;
			   this->StartClientBtn->Click += gcnew System::EventHandler(this, &MyForm::StartClientBtn_Click);
			   // 
			   // StopClientBtn
			   // 
			   this->StopClientBtn->Anchor = System::Windows::Forms::AnchorStyles::None;
			   this->StopClientBtn->Location = System::Drawing::Point(132, 306);
			   this->StopClientBtn->Name = L"StopClientBtn";
			   this->StopClientBtn->Size = System::Drawing::Size(75, 25);
			   this->StopClientBtn->TabIndex = 6;
			   this->StopClientBtn->Text = L"Stop Client";
			   this->StopClientBtn->UseVisualStyleBackColor = true;
			   this->StopClientBtn->Click += gcnew System::EventHandler(this, &MyForm::StopClientBtn_Click);
			   // 
			   // SendMsgBox
			   // 
			   this->SendMsgBox->AccessibleDescription = L"";
			   this->SendMsgBox->Anchor = System::Windows::Forms::AnchorStyles::None;
			   this->SendMsgBox->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				   static_cast<System::Byte>(204)));
			   this->SendMsgBox->Location = System::Drawing::Point(57, 241);
			   this->SendMsgBox->Name = L"SendMsgBox";
			   this->SendMsgBox->Size = System::Drawing::Size(150, 22);
			   this->SendMsgBox->TabIndex = 3;
			   this->SendMsgBox->Tag = L"";
			   // 
			   // SendMsgBtn
			   // 
			   this->SendMsgBtn->Anchor = System::Windows::Forms::AnchorStyles::None;
			   this->SendMsgBtn->Location = System::Drawing::Point(213, 240);
			   this->SendMsgBtn->Name = L"SendMsgBtn";
			   this->SendMsgBtn->Size = System::Drawing::Size(93, 25);
			   this->SendMsgBtn->TabIndex = 1;
			   this->SendMsgBtn->Text = L"Send Message";
			   this->SendMsgBtn->UseVisualStyleBackColor = true;
			   this->SendMsgBtn->Click += gcnew System::EventHandler(this, &MyForm::SendMsgBtn_Click);
			   // 
			   // panel1
			   // 
			   this->panel1->AutoScroll = true;
			   this->panel1->Controls->Add(this->label4);
			   this->panel1->Location = System::Drawing::Point(57, 12);
			   this->panel1->Name = L"panel1";
			   this->panel1->Size = System::Drawing::Size(150, 223);
			   this->panel1->TabIndex = 8;
			   // 
			   // label4
			   // 
			   this->label4->AutoSize = true;
			   this->label4->Location = System::Drawing::Point(4, 4);
			   this->label4->Name = L"label4";
			   this->label4->Size = System::Drawing::Size(0, 13);
			   this->label4->TabIndex = 0;
			   // 
			   // MyForm
			   // 
			   this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			   this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			   this->ClientSize = System::Drawing::Size(484, 341);
			   this->Controls->Add(this->panel1);
			   this->Controls->Add(this->StopClientBtn);
			   this->Controls->Add(this->label3);
			   this->Controls->Add(this->label2);
			   this->Controls->Add(this->label1);
			   this->Controls->Add(this->SendMsgBox);
			   this->Controls->Add(this->textBox3);
			   this->Controls->Add(this->textBox1);
			   this->Controls->Add(this->textBox2);
			   this->Controls->Add(this->DeclineBtn);
			   this->Controls->Add(this->StartClientBtn);
			   this->Controls->Add(this->SendMsgBtn);
			   this->Controls->Add(this->CallBtn);
			   this->MaximumSize = System::Drawing::Size(500, 380);
			   this->MinimumSize = System::Drawing::Size(500, 380);
			   this->Name = L"MyForm";
			   this->Text = L"MyForm";
			   this->panel1->ResumeLayout(false);
			   this->panel1->PerformLayout();
			   this->ResumeLayout(false);
			   this->PerformLayout();

		   }
#pragma endregion
	private: System::Void StartClientBtn_Click(System::Object^ sender, System::EventArgs^ e) {
		label4->Text += "Server starting...\n";
		pj_str_t s_ipv4 = pj_str(ADDRESS);
		pj_str_t s;
		pj_thread_desc a_thread_desc; 
		pj_thread_t* a_thread;
		// Create socket
		pj_sock_t sock = pj_sock_socket(PJ_AF_INET, PJ_SOCK_STREAM, 0, 0);
		if (sock != 0)
		{
			label4->Text += "Can't create socket\n";
			pj_sock_close(sock);
			return;
		}
		if (!pj_thread_is_registered()) {
			pj_thread_register(NULL, a_thread_desc, &a_thread);
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
			label4->Text += "Can't connect to server\n";
			pj_sock_close(sock);
			return;
		}
		//Do-while loop to send and receive data
		pj_ssize_t size = BIG_DATA_LEN;
		do
		{ //Prompt the user for some text
			cin.get(bigdata, BIG_DATA_LEN);// getdata not works
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
						label4->Text += "SERVER> %s", string(bigdata, 0, bytesReceived);
					}
				}
			}
		} while (bigdata > 0);
	}
	private: System::Void StopClientBtn_Click(System::Object^ sender, System::EventArgs^ e) {}
	private: System::Void SendMsgBtn_Click(System::Object^ sender, System::EventArgs^ e) {
			label4->Text += SendMsgBox->Text;
			label4->Text += "\n";
	}
	private: System::Void CallBtn_Click(System::Object^ sender, System::EventArgs^ e) {}
	private: System::Void DeclineBtn_Click(System::Object^ sender, System::EventArgs^ e) {}






	};
}
#endif