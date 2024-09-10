#include <print>
#include <iostream>
#include <Zut/ZxArg.h>
#include <ReVN/RxPJADV/Core/Pack_V2.h>

namespace RxPJADV { using namespace ZQF::ReVN::RxPJADV; }


auto main(void) -> int
{
	try
	{
		ZxArg::Parser arg;
		arg.AddOption("-dat", ".dat file path");
		arg.AddOption("-dir", "dir path");
		arg.AddOption("-mode", "mode: unpack | repack");
		arg.AddExample("-mode unpack -dat archive.dat -dir archive/ ");
		arg.AddExample("-mode repack -dir archive/ -dat archive.dat ");
		if (arg.Parse() == false) { return 0; }

		if (arg["-mode"].Get<std::string_view>() == "unpack")
		{
			RxPJADV::PackV2::Export(arg["-dat"].Get<std::string_view>(), arg["-dir"].Get<std::string_view>());
			std::println("unpack done!");
		}
		else if (arg["-mode"].Get<std::string_view>() == "repack")
		{
			RxPJADV::PackV2::Import(arg["-dir"].Get<std::string_view>(), arg["-dat"].Get<std::string_view>());
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
