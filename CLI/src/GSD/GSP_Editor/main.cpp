#include <print>
#include <iostream>
#include <Zut/ZxArg.h>
#include <ReVN/RxGSD/Core/GSP.h>

namespace RxGSD { using namespace ZQF::ReVN::RxGSD; }


auto main(void) -> int
{
	try
	{
		ZxArg::Parser arg;
		arg.AddOption("-gsp", "gsp file path");
		arg.AddOption("-dir", "files dir path");
		arg.AddOption("-mode", "mode: unpack | repack");
		arg.AddExample("-mode unpack -gsp data.gsp -dir data/");
		arg.AddExample("-mode repack -dir data/ -gsp data.gsp.new");
		if (arg.Parse() == false) { return 0; }

		const auto mode{ arg["-mode"].Get<std::string_view>() };

		if (mode == "unpack")
		{
			RxGSD::GSP::Export(arg["-gsp"].Get<std::string_view>(), arg["-dir"].Get<std::string_view>());
			std::println("unpack done!");
		}
		else if (mode == "repack")
		{
			RxGSD::GSP::Import(arg["-dir"].Get<std::string_view>(), arg["-gsp"].Get<std::string_view>());
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
