#ifndef PIOTR_TEMPLATE_FUNCTION_TEMPLATE_H
#define PIOTR_TEMPLATE_FUNCTION_TEMPLATE_H

namespace Piotr
{
	namespace Template
	{
		template<typename R, typename...Args>
		class FunctionalObject;

		template<typename R, typename...Args>
		class FunctionalObject < R(Args...) >
		{
		public:
			virtual R operator()(Args...args) = 0;
		};
	}
}

#endif