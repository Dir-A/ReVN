#include <print>
#include <iostream>
#include <ZxArg/Parser.h>
#include <RxGSD/Core/BMZ.h>


auto main(void) -> int
{
	try
	{
		ZQF::ZxArg::Parser arg;
		arg.AddCmd("-bmz", "bmz file path");
		arg.AddCmd("-bmp", "bmp file path");
		arg.AddCmd("-new", "new bmz file path");
		arg.AddCmd("-mode", "mode: bmz2bmp | bmp2bmz");
		arg.AddExample("-mode bmz2bmp -bmz im106.bmz -bmp im106.bmp");
		arg.AddExample("-mode bmp2bmz -bmz im106.bmz -bmp im106.bmp -new im106.bmz.new");
		if (arg.Parse() == false) { return 0; }

		const auto mode{ arg["-mode"].Get<std::string_view>() };

		if (mode == "bmz2bmp")
		{
			ZQF::RxGSD::BMZ::Export(arg["-bmz"].Get<std::string_view>(), arg["-bmp"].Get<std::string_view>());
			std::println("bmz2bmp done!");
		}
		else if (mode == "bmp2bmz")
		{
			ZQF::RxGSD::BMZ::Import(arg["-bmz"].Get<std::string_view>(), arg["-bmp"].Get<std::string_view>(), arg["-new"].Get<std::string_view>());
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