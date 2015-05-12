// WindowsFormApplication1.cpp : main project file.

#include "stdafx.h"
#include "Input.h"
#include "Output.h"

using namespace yolo_octo_wallhack;

[STAThreadAttribute]
int main(array<System::String ^> ^args)
{
	// Enabling Windows XP visual effects before any controls are created
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false); 

	// Create the main window and run it

	Application::Run(gcnew Input());
	return 0;
}
