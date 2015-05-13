#pragma once


#include "piotr/math/real.h"
#include "piotr/math/argument_collection.h"
#include "piotr/math/constant.h"
#include "piotr/math/variable.h"
#include "Output.h"

namespace yolo_octo_wallhack {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace Piotr;
	using namespace Math;

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
			this->exitToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->runToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->compileAndRunToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->menuStrip1->SuspendLayout();
			this->SuspendLayout();
			// 
			// menuStrip1
			// 
			this->menuStrip1->ImageScalingSize = System::Drawing::Size(20, 20);
			this->menuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
				this->toolStripMenuItem1,
					this->runToolStripMenuItem
			});
			this->menuStrip1->Location = System::Drawing::Point(0, 0);
			this->menuStrip1->Name = L"menuStrip1";
			this->menuStrip1->Size = System::Drawing::Size(282, 28);
			this->menuStrip1->TabIndex = 0;
			this->menuStrip1->Text = L"menuStrip1";
			// 
			// toolStripMenuItem1
			// 
			this->toolStripMenuItem1->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) { this->exitToolStripMenuItem });
			this->toolStripMenuItem1->Name = L"toolStripMenuItem1";
			this->toolStripMenuItem1->Size = System::Drawing::Size(154, 24);
			this->toolStripMenuItem1->Text = L"toolStripMenuItem1";
			// 
			// exitToolStripMenuItem
			// 
			this->exitToolStripMenuItem->Name = L"exitToolStripMenuItem";
			this->exitToolStripMenuItem->Size = System::Drawing::Size(102, 24);
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
			this->compileAndRunToolStripMenuItem->Size = System::Drawing::Size(188, 24);
			this->compileAndRunToolStripMenuItem->Text = L"Compile and run";
			this->compileAndRunToolStripMenuItem->Click += gcnew System::EventHandler(this, &Input::compileAndRunToolStripMenuItem_Click);
			// 
			// textBox1
			// 
			this->textBox1->AcceptsReturn = true;
			this->textBox1->AcceptsTab = true;
			this->textBox1->AllowDrop = true;
			this->textBox1->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->textBox1->Font = (gcnew System::Drawing::Font(L"Comic Sans MS", 10.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->textBox1->Location = System::Drawing::Point(0, 31);
			this->textBox1->Multiline = true;
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(282, 223);
			this->textBox1->TabIndex = 1;
			this->textBox1->Text = L"a";
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
	Output^ form = gcnew Output();
	form->Show();
	form->flushText();
	ArgumentCollection t2(3);
	ArgumentCollection t(0);
	Variable<Real> variable(3,1);
	t2.set(0, new Real(1));
	t2.set(1, new Real(2));
	t2.set(2, new Real(5));
	Constant<Real> constant(3);
	constant.set(0, new Real(1));
	constant.set(1, new Real(1));
	constant.set(2, new Real(2));

	t = constant(t);
	form->pushLine(t.toString());
	t.recycle();

	t = variable(t2);
	form->pushLine(t.toString());
	/*for (int i = 0; i < textBox1->Lines->Length; i++)
	{
		array<String^>^ ta = textBox1->Lines;
		String^ t = ta[i];
		form->pushLine(t);
	}*/
	
}
};



	


}
