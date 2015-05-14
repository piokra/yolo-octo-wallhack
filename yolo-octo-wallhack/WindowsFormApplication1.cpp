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
			Form^ form = gcnew Output(si.removeSpaces("Hello my name is yoloswag13."));
			form->Show();
			form = gcnew Output(si.seperateWords("Hello my name      is yoloswag13."));
			form->Show();
			si.compileLine("");
			si.compileLine("YOLO SWAG 13");
			si.compileLine("Real yoloswag13");
			si.compileLine("DisplayReal yoloswag13");
			si.showResult();
			si.showLog();
			
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

	Application::Run(gcnew Input());
	return 0;
}
