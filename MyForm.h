#ifndef MYFORM_H
#define MYFORM_H

#include <pjlib.h>
#include <pjlib-util.h>
#include <pjsip.h>
#include <pjsip_ua.h>
#include <pjsip_simple.h>
#include <pjsua-lib/pjsua.h>
#include <pjmedia.h>
#include <pjmedia-codec.h>

namespace SIPclient {
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	public ref class MyForm : public System::Windows::Forms::Form
	{
	private: pj_status_t status;
			 char* myAddress = "192.168.0.107";
			 void start_sip_stack();
			 void stop_sip_stack();
	public:
		MyForm(void) {
			start_sip_stack();
			InitializeComponent();}
	protected:
		~MyForm() {
			stop_sip_stack();
			if (components) delete components;}
#pragma region Forms
		private: System::Windows::Forms::Button^ CallBtn;
		private: System::Windows::Forms::Button^ DeclineBtn;
		private: System::Windows::Forms::TextBox^ userTxt;
		private: System::Windows::Forms::TextBox^ serverIPTxt;
		private: System::Windows::Forms::TextBox^ portTxt;
		private: System::Windows::Forms::Label^ label1;
		private: System::Windows::Forms::Label^ label2;
		private: System::Windows::Forms::Label^ label3;
		private: System::Windows::Forms::TextBox^ clientTxt;
		private: System::Windows::Forms::Label^ label6;
		private: System::Windows::Forms::Button^ RegisterBtn;
		private: System::Windows::Forms::TextBox^ pswdTxt;
		private: System::Windows::Forms::Label^ label5;
		private: System::Windows::Forms::Panel^ panel1;
		private: System::Windows::Forms::Label^ label4;
		private: System::ComponentModel::Container^ components;
#pragma endregion
#pragma region Windows Form Designer generated code
	private: void InitializeComponent(void)
		   {
		this->CallBtn = (gcnew System::Windows::Forms::Button());
		this->DeclineBtn = (gcnew System::Windows::Forms::Button());
		this->userTxt = (gcnew System::Windows::Forms::TextBox());
		this->serverIPTxt = (gcnew System::Windows::Forms::TextBox());
		this->portTxt = (gcnew System::Windows::Forms::TextBox());
		this->label1 = (gcnew System::Windows::Forms::Label());
		this->label2 = (gcnew System::Windows::Forms::Label());
		this->label3 = (gcnew System::Windows::Forms::Label());
		this->panel1 = (gcnew System::Windows::Forms::Panel());
		this->label4 = (gcnew System::Windows::Forms::Label());
		this->RegisterBtn = (gcnew System::Windows::Forms::Button());
		this->pswdTxt = (gcnew System::Windows::Forms::TextBox());
		this->label5 = (gcnew System::Windows::Forms::Label());
		this->clientTxt = (gcnew System::Windows::Forms::TextBox());
		this->label6 = (gcnew System::Windows::Forms::Label());
		this->panel1->SuspendLayout();
		this->SuspendLayout();
		// 
		// CallBtn
		// 
		this->CallBtn->Anchor = System::Windows::Forms::AnchorStyles::None;
		this->CallBtn->Location = System::Drawing::Point(231, 210);
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
		this->DeclineBtn->Location = System::Drawing::Point(306, 210);
		this->DeclineBtn->Name = L"DeclineBtn";
		this->DeclineBtn->Size = System::Drawing::Size(75, 25);
		this->DeclineBtn->TabIndex = 2;
		this->DeclineBtn->Text = L"Decline";
		this->DeclineBtn->UseVisualStyleBackColor = true;
		this->DeclineBtn->Click += gcnew System::EventHandler(this, &MyForm::DeclineBtn_Click);
		// 
		// userTxt
		// 
		this->userTxt->Anchor = System::Windows::Forms::AnchorStyles::None;
		this->userTxt->Location = System::Drawing::Point(231, 17);
		this->userTxt->Name = L"userTxt";
		this->userTxt->Size = System::Drawing::Size(150, 20);
		this->userTxt->TabIndex = 3;
		this->userTxt->Text = L"3460210";
		this->userTxt->TextChanged += gcnew System::EventHandler(this, &MyForm::userTxt_TextChanged);
		// 
		// serverIPTxt
		// 
		this->serverIPTxt->Anchor = System::Windows::Forms::AnchorStyles::None;
		this->serverIPTxt->Location = System::Drawing::Point(231, 69);
		this->serverIPTxt->Name = L"serverIPTxt";
		this->serverIPTxt->Size = System::Drawing::Size(150, 20);
		this->serverIPTxt->TabIndex = 3;
		this->serverIPTxt->Text = L"192.168.39.18";
		this->serverIPTxt->TextChanged += gcnew System::EventHandler(this, &MyForm::ServerIPTxt_TextChanged);
		// 
		// portTxt
		// 
		this->portTxt->Anchor = System::Windows::Forms::AnchorStyles::None;
		this->portTxt->Location = System::Drawing::Point(231, 95);
		this->portTxt->Name = L"portTxt";
		this->portTxt->Size = System::Drawing::Size(150, 20);
		this->portTxt->TabIndex = 3;
		this->portTxt->Text = L"5060";
		this->portTxt->TextChanged += gcnew System::EventHandler(this, &MyForm::PortTxt_TextChanged);
		// 
		// label1
		// 
		this->label1->Anchor = System::Windows::Forms::AnchorStyles::None;
		this->label1->AutoSize = true;
		this->label1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 11.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
			static_cast<System::Byte>(204)));
		this->label1->Location = System::Drawing::Point(387, 19);
		this->label1->Name = L"label1";
		this->label1->Size = System::Drawing::Size(77, 18);
		this->label1->TabIndex = 5;
		this->label1->Text = L"Username";
		// 
		// label2
		// 
		this->label2->Anchor = System::Windows::Forms::AnchorStyles::None;
		this->label2->AutoSize = true;
		this->label2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 11.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
			static_cast<System::Byte>(204)));
		this->label2->Location = System::Drawing::Point(387, 71);
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
		this->label3->Location = System::Drawing::Point(387, 97);
		this->label3->Name = L"label3";
		this->label3->Size = System::Drawing::Size(36, 18);
		this->label3->TabIndex = 5;
		this->label3->Text = L"Port";
		// 
		// panel1
		// 
		this->panel1->AutoScroll = true;
		this->panel1->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
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
		// RegisterBtn
		// 
		this->RegisterBtn->Anchor = System::Windows::Forms::AnchorStyles::None;
		this->RegisterBtn->Location = System::Drawing::Point(231, 121);
		this->RegisterBtn->Name = L"RegisterBtn";
		this->RegisterBtn->Size = System::Drawing::Size(75, 25);
		this->RegisterBtn->TabIndex = 9;
		this->RegisterBtn->Text = L"Register";
		this->RegisterBtn->UseVisualStyleBackColor = true;
		this->RegisterBtn->Click += gcnew System::EventHandler(this, &MyForm::RegisterBtn_Click);
		// 
		// pswdTxt
		// 
		this->pswdTxt->Anchor = System::Windows::Forms::AnchorStyles::None;
		this->pswdTxt->Location = System::Drawing::Point(231, 43);
		this->pswdTxt->Name = L"pswdTxt";
		this->pswdTxt->Size = System::Drawing::Size(150, 20);
		this->pswdTxt->TabIndex = 10;
		this->pswdTxt->TextChanged += gcnew System::EventHandler(this, &MyForm::pswdTxt_TextChanged);
		// 
		// label5
		// 
		this->label5->Anchor = System::Windows::Forms::AnchorStyles::None;
		this->label5->AutoSize = true;
		this->label5->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 11.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
			static_cast<System::Byte>(204)));
		this->label5->Location = System::Drawing::Point(387, 42);
		this->label5->Name = L"label5";
		this->label5->Size = System::Drawing::Size(75, 18);
		this->label5->TabIndex = 11;
		this->label5->Text = L"Password";
		// 
		// clientTxt
		// 
		this->clientTxt->Anchor = System::Windows::Forms::AnchorStyles::None;
		this->clientTxt->Location = System::Drawing::Point(231, 184);
		this->clientTxt->Name = L"clientTxt";
		this->clientTxt->Size = System::Drawing::Size(150, 20);
		this->clientTxt->TabIndex = 14;
		this->clientTxt->Text = L"3460210";
		this->clientTxt->TextChanged += gcnew System::EventHandler(this, &MyForm::clientTxt_TextChanged);
		// 
		// label6
		// 
		this->label6->Anchor = System::Windows::Forms::AnchorStyles::None;
		this->label6->AutoSize = true;
		this->label6->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 11.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
			static_cast<System::Byte>(204)));
		this->label6->Location = System::Drawing::Point(387, 183);
		this->label6->Name = L"label6";
		this->label6->Size = System::Drawing::Size(45, 18);
		this->label6->TabIndex = 15;
		this->label6->Text = L"Client";
		// 
		// MyForm
		// 
		this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
		this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
		this->ClientSize = System::Drawing::Size(484, 291);
		this->Controls->Add(this->label6);
		this->Controls->Add(this->clientTxt);
		this->Controls->Add(this->label5);
		this->Controls->Add(this->pswdTxt);
		this->Controls->Add(this->RegisterBtn);
		this->Controls->Add(this->panel1);
		this->Controls->Add(this->label3);
		this->Controls->Add(this->label2);
		this->Controls->Add(this->label1);
		this->Controls->Add(this->portTxt);
		this->Controls->Add(this->serverIPTxt);
		this->Controls->Add(this->userTxt);
		this->Controls->Add(this->DeclineBtn);
		this->Controls->Add(this->CallBtn);
		this->MaximumSize = System::Drawing::Size(500, 330);
		this->MinimumSize = System::Drawing::Size(500, 330);
		this->Name = L"MyForm";
		this->Text = L"SIP Client";
		this->panel1->ResumeLayout(false);
		this->panel1->PerformLayout();
		this->ResumeLayout(false);
		this->PerformLayout();

	}
#pragma endregion
	private: System::Void CallBtn_Click(System::Object^ sender, System::EventArgs^ e);
	private: System::Void DeclineBtn_Click(System::Object^ sender, System::EventArgs^ e);
	private: System::Void ServerIPTxt_TextChanged(System::Object^ sender, System::EventArgs^ e);
	private: System::Void PortTxt_TextChanged(System::Object^ sender, System::EventArgs^ e);
	private: System::Void userTxt_TextChanged(System::Object^ sender, System::EventArgs^ e);
	private: System::Void pswdTxt_TextChanged(System::Object^ sender, System::EventArgs^ e);
	private: System::Void RegisterBtn_Click(System::Object^ sender, System::EventArgs^ e);
	private: System::Void clientTxt_TextChanged(System::Object^ sender, System::EventArgs^ e);
};
}
#endif