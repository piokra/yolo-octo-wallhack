// WindowsFormApplication1.cpp : main project file.

#include "Input.h"
#include "Output.h"
#include "Graph.h"
#include "piotr\utill\type.h"
#include "piotr\math\interpreter.h"
#include "piotr\math\math_function.h"
#include "piotr\math\sumoffunctions.h"
#include "piotr\math\constant.h"
#include "piotr\math\variable.h"
#include "piotr\math\multiplictionoffunctions.h"
using namespace yolo_octo_wallhack;



[STAThreadAttribute]
int main(array<System::String ^> ^args)
{
	

	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false); 

	Application::Run(gcnew Input());

	return 0;
}
