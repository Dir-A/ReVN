#include <print>
#include <iostream>
#include <ZxArg/Parser.h>
#include <RxGSD/Core/GSP.h>


auto main(void) -> int
{
	try
	{
		ZQF::ZxArg::Parser arg;
		arg.AddCmd("-gsp", "gsp file path");
		arg.AddCmd("-dir", "files dir path");
		arg.AddCmd("-mode", "mode: unpack | repack");
		arg.AddExample("-mode unpack -gsp data.gsp -dir data/");
		arg.AddExample("-mode repack -dir data/ -gsp data.gsp.new");
		if (arg.Parse() == false) { return 0; }

		const auto mode{ arg["-mode"].Get<std::string_view>() };

		if (mode == "unpack")
		{
			ZQF::RxGSD::GSP::Export(arg["-gsp"].Get<std::string_view>(), arg["-dir"].Get<std::string_view>());
			std::println("unpack done!");
		}
		else if (mode == "repack")
		{
			ZQF::RxGSD::GSP::Import(arg["-dir"].Get<std::string_view>(), arg["-gsp"].Get<std::string_view>());
			std::println("repack done!");
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