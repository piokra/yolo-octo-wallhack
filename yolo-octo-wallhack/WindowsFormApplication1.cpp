// WindowsFormApplication1.cpp : main project file.

#include "Input.h"
#include "Output.h"
#include "piotr\utill\type.h"
#include "piotr\math\interpreter.h"

using namespace yolo_octo_wallhack;

namespace Piotr
{
	namespace Math
	{
		void SITestFunction()
		{
			StringInterpreter si;
			si.pushLine("Real a");
			si.pushLine("Real t");
			si.pushLine("Real b");
			si.pushLine("Real c");
			si.pushLine("Real d");
			si.run();
			Output^ op = gcnew Output(si.seperateWords("f(2+3*4*55+swag13)"," ","()*+-/^"));
			op->Show();
			op = gcnew Output(si.seperateWords(("(2+3)*5"), " ", "()+-*^,"));
			op->Show();
			op = gcnew Output(si.seperateWords(("((a+t)*((b+(a+c))^(c+d)))"), " ", "()+-*^/,"));
			op->Show();
			op = gcnew Output(si.toRPN("((a+t)*((b+(a+c))^(c+d)))"));
			op->Show();

		}
		void SITestFunction2()
		{
			/*
			StringInterpreter si;
			Form^ form = gcnew Output(si.removeSpaces("Hello my name is yoloswag13."));
			form->Show();
			form = gcnew Output(si.seperateWords("Hello my name      is yoloswag13.", " ", ""));
			form->Show();
			si.compileLine("");
			si.compileLine("YOLO SWAG 13");
			si.compileLine("Real yoloswag13");
			si.compileLine("DisplayReal yoloswag13");
			si.showResult();
			si.showLog();
			*/
		}
	}
}


[STAThreadAttribute]
int main(array<System::String ^> ^args)
{
	StringInterpreter si;
	// Enabling Windows XP visual effects before any controls are created
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false); 
	//SITestFunction();
	// Create the main window and run it
	//SITestFunction();
	Application::Run(gcnew Input());
	return 0;
}
