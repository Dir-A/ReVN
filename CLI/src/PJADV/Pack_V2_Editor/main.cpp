#include <print>
#include <iostream>
#include <ZxArg/Parser.h>
#include <RxPJADV/Core/Pack_V2.h>


auto main(void) -> int
{
	try
	{
		ZQF::ZxArg::Parser arg;
		arg.AddCmd("-dat", ".dat file path");
		arg.AddCmd("-dir", "dir path");
		arg.AddCmd("-mode", "mode: unpack | repack");
		arg.AddExample("-mode unpack -dat archive.dat -dir archive/ ");
		arg.AddExample("-mode repack -dir archive/ -dat archive.dat ");
		if (arg.Parse() == false) { return 0; }

		if (arg["-mode"].Get<std::string_view>() == "unpack")
		{
			ZQF::RxPJADV::PackV2::Export(arg["-dat"].Get<std::string_view>(), arg["-dir"].Get<std::string_view>());
			std::println("unpack done!");
		}
		else if (arg["-mode"].Get<std::string_view>() == "repack")
		{
			ZQF::RxPJADV::PackV2::Import(arg["-dir"].Get<std::string_view>(), arg["-dat"].Get<std::string_view>());
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