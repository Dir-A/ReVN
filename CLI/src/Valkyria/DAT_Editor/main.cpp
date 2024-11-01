#include <print>
#include <iostream>
#include <Zut/ZxArg.h>
#include <ReVN/RxValkyria/Core/Pack.h>

namespace RxValkyria { using namespace ZQF::ReVN::RxValkyria; }


auto main(void) -> int
{
	try
	{
		ZxArg::Parser arg;
		arg.AddOption("-dat", "dat path");
		arg.AddOption("-dir", "files dir");
		arg.AddOption("-mode", "mode: unpack | repack");
		arg.AddExample("-mode unpack -dat data06-00.dat -dir data06/");
		arg.AddExample("-mode repack -dir data06/ -dat data06-01.dat");
		if (arg.Parse() == false) { return 0; }

		const auto mode{ arg["-mode"].GetStrView() };
		const auto dat_path{ arg["-dat"].GetStrView() };
		const auto dir_path{ arg["-dir"].GetStrView() };

		if (mode == "unpack")
		{
			const auto status = RxValkyria::Pack::Export(dat_path, dir_path);
			status ? std::println("success! -> {}", dat_path) : std::println("error! -> {}", dat_path);
		}
		else if (mode == "repack")
		{
			const auto status = RxValkyria::Pack::Import(dir_path, dat_path);
			status ? std::println("success! -> {}", dir_path) : std::println("error! -> {}", dir_path);
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
