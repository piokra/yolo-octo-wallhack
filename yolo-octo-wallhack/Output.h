#pragma once
#include <vector>
#include <string>
namespace yolo_octo_wallhack {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for Output
	/// </summary>
	public ref class Output : public System::Windows::Forms::Form
	{
	public:
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
	public:
		void pushLine(String^ line)
		{
			if (textBox1->Text != "")
				textBox1->Text += Environment::NewLine;
			textBox1->Text += line;
			
		}
		void flushText()
		{
			textBox1->Text = L"";
		}

		Output(const std::vector<std::string>& strs)
		{
			InitializeComponent();
			flushText();
			for (int i = 0; i < strs.size(); i++)
				pushLine(gcnew String(strs[i].c_str()));
		}

		Output(const std::string& str)
		{
			InitializeComponent(); 
			flushText();
			pushLine(gcnew String(str.c_str()));
		}

		/*
		*	Custom code goes above
		*/
		Output(void)
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
		~Output()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::TextBox^  textBox1;
	protected:







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
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->SuspendLayout();
			// 
			// textBox1
			// 
			this->textBox1->AcceptsReturn = true;
			this->textBox1->AcceptsTab = true;
			this->textBox1->AllowDrop = true;
			this->textBox1->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->textBox1->Font = (gcnew System::Drawing::Font(L"Comic Sans MS", 10.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->textBox1->Location = System::Drawing::Point(0, 4);
			this->textBox1->Multiline = true;
			this->textBox1->Name = L"textBox1";
			this->textBox1->ReadOnly = true;
			this->textBox1->Size = System::Drawing::Size(282, 249);
			this->textBox1->TabIndex = 2;
			// 
			// Output
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(282, 255);
			this->Controls->Add(this->textBox1);
			this->Name = L"Output";
			this->Text = L"Output";
			this->SizeChanged += gcnew System::EventHandler(this, &Output::Output_SizeChanged);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void Output_SizeChanged(System::Object^  sender, System::EventArgs^  e) {
		resizeUI();
	}
	private: System::Void clearToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
		textBox1->Text = L"";
		
	}
};
}
