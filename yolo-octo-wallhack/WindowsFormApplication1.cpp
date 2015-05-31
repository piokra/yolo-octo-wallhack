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

namespace Piotr
{
	namespace Math
	{
		/*
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

		}*/
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
		class THC
		{
		public:
			ManagedArgument m;
			GenericMathFunction* get()
			{
				return (GenericMathFunction*)m.get();
			}
			Variable* v()
			{
				return (Variable*)m.get();
			}
			Constant* c()
			{
				return (Constant*)m.get();
			}
			GenericMathFunction* operator->()
			{
				return get();
			}
		};
		void FunctionTestFunction()
		{
			ManagedArgument mc(new Constant(1));
			THC tmc{ mc };
			std::string str;
			tmc.c()->set(ManagedArgument(new Real(7)));
			THC tmc2;
			tmc2.m = tmc->operator+(tmc.m);
			tmc.get()->operator()(ManagedArgument())->toString(str);
			Output^ out = gcnew Output(str);
			out->Show();
			str = "";
			tmc2.get()->operator()(ManagedArgument())->toString(str);
			out = gcnew Output(str);
			out->Show();
			THC tmc3 = { ManagedArgument(new Variable(0, 0)) };
			tmc2.m = tmc->operator*(tmc3.m);
			str = "";
			tmc2.get()->operator()(ManagedArgument(new Real(7)))->toString(str);
			out = gcnew Output(str);
			out->Show();

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
	//FunctionTestFunction();
	//SITestFunction();
	// Create the main window and run it
	//SITestFunction();
	ManagedArgument ma = ManagedArgument(new Variable(1, 0));
	Graph^ graph = gcnew Graph(ma, 0, 1, 0.1);
	graph->Show();
	Application::Run(gcnew Input());

	return 0;
}
