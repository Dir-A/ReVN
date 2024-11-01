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

		const auto mode{ arg["-mode"].GetStrView() };

		if (mode == "unpack")
		{
			RxGSD::GSP::Export(arg["-gsp"].GetStrView(), arg["-dir"].GetStrView());
			std::println("unpack done!");
		}
		else if (mode == "repack")
		{
			RxGSD::GSP::Import(arg["-dir"].GetStrView(), arg["-gsp"].GetStrView());
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
