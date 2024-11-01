#include <print>
#include <iostream>
#include <Zut/ZxArg.h>
#include <ReVN/RxGSD/Core/BMZ.h>

namespace RxGSD { using namespace ZQF::ReVN::RxGSD; }


auto main(void) -> int
{
	try
	{
		ZxArg::Parser arg;
		arg.AddOption("-bmz", "bmz file path");
		arg.AddOption("-bmp", "bmp file path");
		arg.AddOption("-new", "new bmz file path");
		arg.AddOption("-mode", "mode: bmz2bmp | bmp2bmz");
		arg.AddExample("-mode bmz2bmp -bmz im106.bmz -bmp im106.bmp");
		arg.AddExample("-mode bmp2bmz -bmz im106.bmz -bmp im106.bmp -new im106.bmz.new");
		if (arg.Parse() == false) { return 0; }

		const auto mode{ arg["-mode"].GetStrView() };

		if (mode == "bmz2bmp")
		{
			RxGSD::BMZ::Export(arg["-bmz"].GetStrView(), arg["-bmp"].GetStrView());
			std::println("bmz2bmp done!");
		}
		else if (mode == "bmp2bmz")
		{
			RxGSD::BMZ::Import(arg["-bmz"].GetStrView(), arg["-bmp"].GetStrView(), arg["-new"].GetStrView());
			std::println("bmp2bmz done!");
		}
		else
		{
			std::println("unknown command!");
		}
	}
	catch (const std::exception& err)
	{
		std::println(std::cerr, "std::exception: {}", err.what());
	}
}
