#include <print>
#include <iostream>
#include <ZxArg/Parser.h>
#include <RxValkyria/Core/Pack.h>


auto main(void) -> int
{
	try
	{
		ZQF::ZxArg::Parser arg;
		arg.AddCmd("-dat", "dat path");
		arg.AddCmd("-dir", "files dir");
		arg.AddCmd("-mode", "mode: unpack | repack");
		arg.AddExample("-mode unpack -dat data06-00.dat -dir data06/");
		arg.AddExample("-mode repack -dir data06/ -dat data06-01.dat");
		if (arg.Parse() == false) { return 0; }

		const auto mode{ arg["-mode"].Get<std::string_view>() };
		const auto dat_path{ arg["-dat"].Get<std::string_view>() };
		const auto dir_path{ arg["-dir"].Get<std::string_view>() };

		if (mode == "unpack")
		{
			const auto status = ZQF::RxValkyria::Pack::Export(dat_path, dir_path);
			status ? std::println("success! -> {}", dat_path) : std::println("error! -> {}", dat_path);
		}
		else if (mode == "repack")
		{
			const auto status = ZQF::RxValkyria::Pack::Import(dir_path, dat_path);
			status ? std::println("success! -> {}", dir_path) : std::println("error! -> {}", dir_path);
		}
	}
	catch (const std::exception& err)
	{
		std::println(std::cerr, "std::exception: {}", err.what());
	}
}