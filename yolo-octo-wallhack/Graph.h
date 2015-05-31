#pragma once
#include "piotr\math\math_function.h"
#include "piotr\math\argument.h"
#include "piotr\math\real.h"
namespace yolo_octo_wallhack {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace Piotr;
	using namespace Piotr::Math;
	/// <summary>
	/// Summary for MyForm
	/// </summary>
	public ref class Graph : public System::Windows::Forms::Form
	{
	public:
		Graph(ManagedArgument func, double start, double end, double step)
		{
			InitializeComponent();
			mRight = end;
			mLeft = start;
			mStep = step;
			GenericMathFunction* gmf = (GenericMathFunction*)func.get();
			const int steps = ceil((end - start) / step);
			mValues = gcnew array<double>(steps);
			double min = INFINITY;
			double max = -INFINITY;
			for (int i = 0; i < steps; i++)
			{
				ManagedArgument t = ManagedArgument(new Real(start + i*step));
				ManagedArgument tt = gmf->operator()(t);
				Real* tr = (Real*)tt.get();
				mValues[i] = -tr->value;
				if (mValues[i] < mDown)
					mDown = mValues[i];
				if (mValues[i] > mUp)
					mUp = mValues[i];
					
			}
			ResizeRedraw = false;

			
			
			
			
		}
		void resizeUI()
		{
			
			double windowX = Size.Width;
			double windowY = Size.Height;
			double xScale = windowX/ (mRight - mLeft);
			double yScale = windowY / (System::Math::Abs(mUp - mDown));
			Graphics^ gc = CreateGraphics();
			gc->Clear(System::Drawing::Color::AliceBlue);
			Drawing::Pen^ pen = gcnew Pen(System::Drawing::Color::HotPink, 10);
			array<Point>^ points = gcnew array<Point>(mValues->Length);
			double x = 0;

			for (int i = 0; i < mValues->Length; i++)
			{
				double y = ((mValues[i] - mDown)*yScale);
				points[i] = Point((x)*xScale, y);
				x += mStep;
			}
			gc->DrawCurve(pen, points);
			
			
			
		}
	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~Graph()
		{
			if (components)
			{
				delete components;
			}
		}

	private:
		double mLeft;
		double mRight;
		double mUp;
		double mDown;
		double mStep;
	
		array<double>^ mValues;
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
			this->SuspendLayout();
			// 
			// Graph
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(282, 255);
			this->Name = L"Graph";
			this->Text = L"Graph";
			this->Activated += gcnew System::EventHandler(this, &Graph::Graph_Activated);
			this->ResizeEnd += gcnew System::EventHandler(this, &Graph::MyForm_ResizeEnd);
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void MyForm_ResizeEnd(System::Object^  sender, System::EventArgs^  e) {
		resizeUI();
	}
	private: System::Void Graph_Activated(System::Object^  sender, System::EventArgs^  e) {
		resizeUI();
	}
};
}
