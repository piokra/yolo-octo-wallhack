#pragma once


#include "piotr/math/real.h"
#include "piotr/math/argument_collection.h"
#include "piotr/math/constant.h"
#include "piotr/math/variable.h"
#include "piotr/math/interpreter.h"
#include "Output.h"
#include "conversion.h"


namespace yolo_octo_wallhack {
	
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace Piotr;
	using namespace Math;
	using namespace System::IO;

	inline std::string toStringFromManaged(System::String^ str)
	{
		std::string ret = "";

		for (int i = 0; i < str->Length; i++)
		{
			ret += str[i];
		}
		return ret;
	}
	/// <summary>
	/// Summary for Input
	/// </summary>
	public ref class Input : public System::Windows::Forms::Form
	{
		/*
		*	Custom code goes below
		*/

	protected:
		void resizeUI()
		{
			double windowX = Size.Width;
			double windowY = Size.Height;

			double xPos = textBox1->Location.X;
			double yPos = textBox1->Location.Y;

			textBox1->Size = Drawing::Size(windowX - xPos, windowY - yPos);
		}
	private:
		
		/*
		*	Custom code goes above 
		*/
	public:
		Input(void)
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
		~Input()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::MenuStrip^  menuStrip1;
	protected:
	private: System::Windows::Forms::ToolStripMenuItem^  toolStripMenuItem1;
	private: System::Windows::Forms::ToolStripMenuItem^  exitToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  runToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  compileAndRunToolStripMenuItem;
	private: System::Windows::Forms::TextBox^  textBox1;
	private: System::Windows::Forms::ToolStripMenuItem^  saveToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  loadToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  helpToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  aboutToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  helpToolStripMenuItem1;
	private: System::Windows::Forms::OpenFileDialog^  openFileDialog1;
	private: System::Windows::Forms::SaveFileDialog^  saveFileDialog1;

	protected:

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
			this->menuStrip1 = (gcnew System::Windows::Forms::MenuStrip());
			this->toolStripMenuItem1 = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->saveToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->loadToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->exitToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->runToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->compileAndRunToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->helpToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->aboutToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->helpToolStripMenuItem1 = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->openFileDialog1 = (gcnew System::Windows::Forms::OpenFileDialog());
			this->saveFileDialog1 = (gcnew System::Windows::Forms::SaveFileDialog());
			this->menuStrip1->SuspendLayout();
			this->SuspendLayout();
			// 
			// menuStrip1
			// 
			this->menuStrip1->ImageScalingSize = System::Drawing::Size(20, 20);
			this->menuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(3) {
				this->toolStripMenuItem1,
					this->runToolStripMenuItem, this->helpToolStripMenuItem
			});
			this->menuStrip1->Location = System::Drawing::Point(0, 0);
			this->menuStrip1->Name = L"menuStrip1";
			this->menuStrip1->Size = System::Drawing::Size(282, 28);
			this->menuStrip1->TabIndex = 0;
			this->menuStrip1->Text = L"menuStrip1";
			// 
			// toolStripMenuItem1
			// 
			this->toolStripMenuItem1->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(3) {
				this->saveToolStripMenuItem,
					this->loadToolStripMenuItem, this->exitToolStripMenuItem
			});
			this->toolStripMenuItem1->Name = L"toolStripMenuItem1";
			this->toolStripMenuItem1->Size = System::Drawing::Size(44, 24);
			this->toolStripMenuItem1->Text = L"File";
			// 
			// saveToolStripMenuItem
			// 
			this->saveToolStripMenuItem->Name = L"saveToolStripMenuItem";
			this->saveToolStripMenuItem->Size = System::Drawing::Size(114, 24);
			this->saveToolStripMenuItem->Text = L"Save";
			this->saveToolStripMenuItem->Click += gcnew System::EventHandler(this, &Input::saveToolStripMenuItem_Click);
			// 
			// loadToolStripMenuItem
			// 
			this->loadToolStripMenuItem->Name = L"loadToolStripMenuItem";
			this->loadToolStripMenuItem->Size = System::Drawing::Size(114, 24);
			this->loadToolStripMenuItem->Text = L"Open";
			this->loadToolStripMenuItem->Click += gcnew System::EventHandler(this, &Input::loadToolStripMenuItem_Click);
			// 
			// exitToolStripMenuItem
			// 
			this->exitToolStripMenuItem->Name = L"exitToolStripMenuItem";
			this->exitToolStripMenuItem->Size = System::Drawing::Size(114, 24);
			this->exitToolStripMenuItem->Text = L"Exit";
			this->exitToolStripMenuItem->Click += gcnew System::EventHandler(this, &Input::exitToolStripMenuItem_Click);
			// 
			// runToolStripMenuItem
			// 
			this->runToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) { this->compileAndRunToolStripMenuItem });
			this->runToolStripMenuItem->Name = L"runToolStripMenuItem";
			this->runToolStripMenuItem->Size = System::Drawing::Size(46, 24);
			this->runToolStripMenuItem->Text = L"Run";
			// 
			// compileAndRunToolStripMenuItem
			// 
			this->compileAndRunToolStripMenuItem->Name = L"compileAndRunToolStripMenuItem";
			this->compileAndRunToolStripMenuItem->Size = System::Drawing::Size(103, 24);
			this->compileAndRunToolStripMenuItem->Text = L"Run";
			this->compileAndRunToolStripMenuItem->Click += gcnew System::EventHandler(this, &Input::compileAndRunToolStripMenuItem_Click);
			// 
			// helpToolStripMenuItem
			// 
			this->helpToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
				this->aboutToolStripMenuItem,
					this->helpToolStripMenuItem1
			});
			this->helpToolStripMenuItem->Name = L"helpToolStripMenuItem";
			this->helpToolStripMenuItem->Size = System::Drawing::Size(53, 24);
			this->helpToolStripMenuItem->Text = L"Help";
			// 
			// aboutToolStripMenuItem
			// 
			this->aboutToolStripMenuItem->Name = L"aboutToolStripMenuItem";
			this->aboutToolStripMenuItem->Size = System::Drawing::Size(175, 24);
			this->aboutToolStripMenuItem->Text = L"About";
			this->aboutToolStripMenuItem->Click += gcnew System::EventHandler(this, &Input::aboutToolStripMenuItem_Click);
			// 
			// helpToolStripMenuItem1
			// 
			this->helpToolStripMenuItem1->Name = L"helpToolStripMenuItem1";
			this->helpToolStripMenuItem1->Size = System::Drawing::Size(175, 24);
			this->helpToolStripMenuItem1->Text = L"Help";
			this->helpToolStripMenuItem1->Click += gcnew System::EventHandler(this, &Input::helpToolStripMenuItem1_Click);
			// 
			// textBox1
			// 
			this->textBox1->AcceptsReturn = true;
			this->textBox1->AcceptsTab = true;
			this->textBox1->AllowDrop = true;
			this->textBox1->AutoCompleteCustomSource->AddRange(gcnew cli::array< System::String^  >(4) {
				L"Real", L"DisplayReal", L"Set",
					L"Alibababa"
			});
			this->textBox1->AutoCompleteMode = System::Windows::Forms::AutoCompleteMode::SuggestAppend;
			this->textBox1->AutoCompleteSource = System::Windows::Forms::AutoCompleteSource::AllSystemSources;
			this->textBox1->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->textBox1->Font = (gcnew System::Drawing::Font(L"Consolas", 16.2F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->textBox1->Location = System::Drawing::Point(0, 31);
			this->textBox1->Multiline = true;
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(282, 223);
			this->textBox1->TabIndex = 1;
			// 
			// openFileDialog1
			// 
			this->openFileDialog1->DefaultExt = L"ppp";
			this->openFileDialog1->FileName = L"openFileDialog1";
			this->openFileDialog1->FileOk += gcnew System::ComponentModel::CancelEventHandler(this, &Input::openFileDialog1_FileOk);
			// 
			// saveFileDialog1
			// 
			this->saveFileDialog1->DefaultExt = L"ppp";
			this->saveFileDialog1->FileOk += gcnew System::ComponentModel::CancelEventHandler(this, &Input::saveFileDialog1_FileOk);
			// 
			// Input
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(282, 255);
			this->Controls->Add(this->textBox1);
			this->Controls->Add(this->menuStrip1);
			this->MainMenuStrip = this->menuStrip1;
			this->Name = L"Input";
			this->Text = L"Input";
			this->SizeChanged += gcnew System::EventHandler(this, &Input::Input_SizeChanged);
			this->menuStrip1->ResumeLayout(false);
			this->menuStrip1->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void exitToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
		this->Close();
	}
	private: System::Void Input_SizeChanged(System::Object^  sender, System::EventArgs^  e) {
		resizeUI();
	}

private: System::Void compileAndRunToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {

	StringInterpreter stringInterpreter;

	for (int i = 0; i < textBox1->Lines->Length; i++)
	{
		
		stringInterpreter.pushLine(toStringFromManaged((String^)textBox1->Lines[i]));
		
		

	}
	stringInterpreter.run();
	stringInterpreter.showLog();
	stringInterpreter.showResult();
	
}
private: System::Void saveToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
	saveFileDialog1->ShowDialog();
	
	
}
private: System::Void loadToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
	openFileDialog1->ShowDialog();
}
private: System::Void openFileDialog1_FileOk(System::Object^  sender, System::ComponentModel::CancelEventArgs^  e) {
	auto stream = openFileDialog1->OpenFile();
	System::IO::StreamReader streamreader(stream);
	String^ t;
	String^ out;
	while ((t = streamreader.ReadLine()) != nullptr)
	{
		out += t;
		out += Environment::NewLine;
	}
	this->textBox1->Text = out;
}
private: System::Void saveFileDialog1_FileOk(System::Object^  sender, System::ComponentModel::CancelEventArgs^  e) {
	auto stream = saveFileDialog1->OpenFile();
	System::IO::StreamWriter streamwriter(stream);
	for (int i = 0; i < textBox1->Lines->Length; i++)
	{
		streamwriter.WriteLine(textBox1->Lines[i]);
	}
}
private: System::Void aboutToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
	Output^ about = gcnew Output("Sample Text");
	about->Show();
}
private: System::Void helpToolStripMenuItem1_Click(System::Object^  sender, System::EventArgs^  e) {
	Output^ help = gcnew Output("This is a premium feature.");
	help->Show();
}
};



	


}
