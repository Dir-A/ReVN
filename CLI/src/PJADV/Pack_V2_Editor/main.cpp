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

		if (arg["-mode"].GetStrView() == "unpack")
		{
			RxPJADV::PackV2::Export(arg["-dat"].GetStrView(), arg["-dir"].GetStrView());
			std::println("unpack done!");
		}
		else if (arg["-mode"].GetStrView() == "repack")
		{
			RxPJADV::PackV2::Import(arg["-dir"].GetStrView(), arg["-dat"].GetStrView());
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
