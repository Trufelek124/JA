#pragma once

#include "PictureManager.h"
#include <msclr\marshal_cppstd.h>
#include <string.h>

using namespace System;
namespace JAImageBrightening {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for Form1
	/// </summary>
	public ref class Form1 : public System::Windows::Forms::Form
	{
	public:
		Form1(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~Form1()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::TextBox^  inputDir;
	protected:
	private: System::Windows::Forms::Label^  inputDirLabel;
	private: System::Windows::Forms::Label^  outputDirLabel;
	private: System::Windows::Forms::TextBox^  outputDir;
	private: System::Windows::Forms::RadioButton^  radioASM;
	private: System::Windows::Forms::RadioButton^  radioCPP;
	private: System::Windows::Forms::Label^  label3;
	private: System::Windows::Forms::Label^  label4;
	private: System::Windows::Forms::TextBox^  multiplier;
	private: System::Windows::Forms::Button^  runButton;
	private: System::Windows::Forms::NumericUpDown^  threadCount;
	private: System::Windows::Forms::Label^  threadCountLabel;
	private: System::Windows::Forms::Label^  timeLabel;
	private: System::Windows::Forms::TextBox^  timeTextBox;

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->inputDir = (gcnew System::Windows::Forms::TextBox());
			this->inputDirLabel = (gcnew System::Windows::Forms::Label());
			this->outputDirLabel = (gcnew System::Windows::Forms::Label());
			this->outputDir = (gcnew System::Windows::Forms::TextBox());
			this->radioASM = (gcnew System::Windows::Forms::RadioButton());
			this->radioCPP = (gcnew System::Windows::Forms::RadioButton());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->multiplier = (gcnew System::Windows::Forms::TextBox());
			this->runButton = (gcnew System::Windows::Forms::Button());
			this->threadCount = (gcnew System::Windows::Forms::NumericUpDown());
			this->threadCountLabel = (gcnew System::Windows::Forms::Label());
			this->timeLabel = (gcnew System::Windows::Forms::Label());
			this->timeTextBox = (gcnew System::Windows::Forms::TextBox());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->threadCount))->BeginInit();
			this->SuspendLayout();
			// 
			// inputDir
			// 
			this->inputDir->Location = System::Drawing::Point(91, 23);
			this->inputDir->Name = L"inputDir";
			this->inputDir->Size = System::Drawing::Size(318, 20);
			this->inputDir->TabIndex = 0;
			this->inputDir->Text = L"C:\\\\Users\\\\User\\\\Documents\\\\studia\\\\ja\\\\jpeg-build\\\\jpeg-6b\\\\testoutt.jpg";
			// 
			// inputDirLabel
			// 
			this->inputDirLabel->AutoSize = true;
			this->inputDirLabel->Location = System::Drawing::Point(3, 26);
			this->inputDirLabel->Name = L"inputDirLabel";
			this->inputDirLabel->Size = System::Drawing::Size(74, 13);
			this->inputDirLabel->TabIndex = 1;
			this->inputDirLabel->Text = L"Input directory";
			this->inputDirLabel->Click += gcnew System::EventHandler(this, &Form1::inputDirLabel_Click);
			// 
			// outputDirLabel
			// 
			this->outputDirLabel->AutoSize = true;
			this->outputDirLabel->Location = System::Drawing::Point(3, 62);
			this->outputDirLabel->Name = L"outputDirLabel";
			this->outputDirLabel->Size = System::Drawing::Size(82, 13);
			this->outputDirLabel->TabIndex = 3;
			this->outputDirLabel->Text = L"Output directory";
			this->outputDirLabel->Click += gcnew System::EventHandler(this, &Form1::outputDirLabel_Click);
			// 
			// outputDir
			// 
			this->outputDir->Location = System::Drawing::Point(91, 59);
			this->outputDir->Name = L"outputDir";
			this->outputDir->Size = System::Drawing::Size(318, 20);
			this->outputDir->TabIndex = 2;
			this->outputDir->Text = L"C:\\\\Users\\\\User\\\\Documents\\\\studia\\\\ja\\\\jpeg-build\\\\jpeg-6b\\\\testout.jpg";
			this->outputDir->TextChanged += gcnew System::EventHandler(this, &Form1::outputDir_TextChanged);
			// 
			// radioASM
			// 
			this->radioASM->AutoSize = true;
			this->radioASM->Location = System::Drawing::Point(29, 196);
			this->radioASM->Name = L"radioASM";
			this->radioASM->Size = System::Drawing::Size(48, 17);
			this->radioASM->TabIndex = 4;
			this->radioASM->TabStop = true;
			this->radioASM->Text = L"ASM";
			this->radioASM->UseVisualStyleBackColor = true;
			this->radioASM->CheckedChanged += gcnew System::EventHandler(this, &Form1::radioASM_CheckedChanged);
			// 
			// radioCPP
			// 
			this->radioCPP->AutoSize = true;
			this->radioCPP->Location = System::Drawing::Point(29, 220);
			this->radioCPP->Name = L"radioCPP";
			this->radioCPP->Size = System::Drawing::Size(44, 17);
			this->radioCPP->TabIndex = 5;
			this->radioCPP->TabStop = true;
			this->radioCPP->Text = L"C++";
			this->radioCPP->UseVisualStyleBackColor = true;
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(3, 166);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(50, 13);
			this->label3->TabIndex = 6;
			this->label3->Text = L"DLL type";
			this->label3->Click += gcnew System::EventHandler(this, &Form1::label3_Click);
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Location = System::Drawing::Point(3, 99);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(48, 13);
			this->label4->TabIndex = 7;
			this->label4->Text = L"Multiplier";
			this->label4->Click += gcnew System::EventHandler(this, &Form1::label4_Click);
			// 
			// multiplier
			// 
			this->multiplier->Location = System::Drawing::Point(91, 96);
			this->multiplier->Name = L"multiplier";
			this->multiplier->Size = System::Drawing::Size(97, 20);
			this->multiplier->TabIndex = 8;
			// 
			// runButton
			// 
			this->runButton->Location = System::Drawing::Point(29, 272);
			this->runButton->Name = L"runButton";
			this->runButton->Size = System::Drawing::Size(358, 79);
			this->runButton->TabIndex = 9;
			this->runButton->Text = L"RUN";
			this->runButton->UseVisualStyleBackColor = true;
			this->runButton->Click += gcnew System::EventHandler(this, &Form1::runButton_Click);
			// 
			// threadCount
			// 
			this->threadCount->Location = System::Drawing::Point(317, 97);
			this->threadCount->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 64, 0, 0, 0 });
			this->threadCount->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
			this->threadCount->Name = L"threadCount";
			this->threadCount->Size = System::Drawing::Size(92, 20);
			this->threadCount->TabIndex = 10;
			this->threadCount->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
			// 
			// threadCountLabel
			// 
			this->threadCountLabel->AutoSize = true;
			this->threadCountLabel->Location = System::Drawing::Point(219, 99);
			this->threadCountLabel->Name = L"threadCountLabel";
			this->threadCountLabel->Size = System::Drawing::Size(71, 13);
			this->threadCountLabel->TabIndex = 11;
			this->threadCountLabel->Text = L"Thread count";
			this->threadCountLabel->Click += gcnew System::EventHandler(this, &Form1::threadCountLabel_Click);
			// 
			// timeLabel
			// 
			this->timeLabel->AutoSize = true;
			this->timeLabel->Location = System::Drawing::Point(3, 132);
			this->timeLabel->Name = L"timeLabel";
			this->timeLabel->Size = System::Drawing::Size(30, 13);
			this->timeLabel->TabIndex = 12;
			this->timeLabel->Text = L"Time";
			this->timeLabel->Click += gcnew System::EventHandler(this, &Form1::timeLabel_Click);
			// 
			// timeTextBox
			// 
			this->timeTextBox->Location = System::Drawing::Point(91, 129);
			this->timeTextBox->Name = L"timeTextBox";
			this->timeTextBox->ReadOnly = true;
			this->timeTextBox->Size = System::Drawing::Size(318, 20);
			this->timeTextBox->TabIndex = 13;
			this->timeTextBox->Text = L"0";
			this->timeTextBox->TextChanged += gcnew System::EventHandler(this, &Form1::timeTextBox_TextChanged);
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(421, 379);
			this->Controls->Add(this->timeTextBox);
			this->Controls->Add(this->timeLabel);
			this->Controls->Add(this->threadCountLabel);
			this->Controls->Add(this->threadCount);
			this->Controls->Add(this->runButton);
			this->Controls->Add(this->multiplier);
			this->Controls->Add(this->label4);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->radioCPP);
			this->Controls->Add(this->radioASM);
			this->Controls->Add(this->outputDirLabel);
			this->Controls->Add(this->outputDir);
			this->Controls->Add(this->inputDirLabel);
			this->Controls->Add(this->inputDir);
			this->Name = L"Form1";
			this->Text = L"JAImageBrightening";
			this->Load += gcnew System::EventHandler(this, &Form1::Form1_Load);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->threadCount))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void Form1_Load(System::Object^  sender, System::EventArgs^  e) {
	}
	private: System::Void inputDirLabel_Click(System::Object^  sender, System::EventArgs^  e) {
	}
	private: System::Void outputDirLabel_Click(System::Object^  sender, System::EventArgs^  e) {
	}
	private: System::Void outputDir_TextChanged(System::Object^  sender, System::EventArgs^  e) {
	}
	private: System::Void radioASM_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
	}
	private: System::Void label3_Click(System::Object^  sender, System::EventArgs^  e) {
	}
	private: System::Void label4_Click(System::Object^  sender, System::EventArgs^  e) {
	}
	private: System::Void threadCountLabel_Click(System::Object^  sender, System::EventArgs^  e) {
	}
	private: System::Void timeLabel_Click(System::Object^  sender, System::EventArgs^  e) {
	}
private: System::Void timeTextBox_TextChanged(System::Object^  sender, System::EventArgs^  e) {
}
	private: System::Void runButton_Click(System::Object^  sender, System::EventArgs^  e) {
		//tutaj program
		std::string num = msclr::interop::marshal_as<std::string>(multiplier->Text);
		std::string mulS = replaceChar(num, ',', '.');
		double mul = (double)std::stof(mulS);

		std::string imputD = msclr::interop::marshal_as<std::string>(inputDir->Text);
		char *inputDUC = new char[imputD.length() + 1];
		strcpy((char *)inputDUC, imputD.c_str());

		std::string outputD = msclr::interop::marshal_as<std::string>(outputDir->Text);
		char *outputDUC = new char[outputD.length() + 1];
		strcpy((char *)outputDUC, outputD.c_str());

		PictureManager* pManager = new PictureManager(inputDUC, outputDUC, radioASM->Checked, mul, (int)threadCount->Value);

		runButton->Text = L"Working...";
		bool setup = pManager->setup();
		if (setup){
			bool opening = pManager->openPictureAndGetRGBVector();
			if (opening){
				bool brightening = pManager->brightenImageFun();
				if (brightening){
					bool saving = pManager->savePicture();

					if (!saving){
						runButton->Text = L"Error saving!";
					}
					else {
						runButton->Text = L"Done!";
					}
				}
				else {
					runButton->Text = L"Error saving!";
				}
			}
			else {
				runButton->Text = L"Error opening!";
			}
		}
		else {
			runButton->Text = L"Error setup!";
		}
	}

	private: std::string replaceChar(std::string str, char ch1, char ch2) {
	  for (int i = 0; i < str.length(); ++i) {
		if (str[i] == ch1)
		  str[i] = ch2;
	  }

	  return str;
	}
};
}


