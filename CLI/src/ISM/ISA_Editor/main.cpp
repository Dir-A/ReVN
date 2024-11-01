#include <print>
#include <iostream>
#include <Zut/ZxArg.h>
#include <ReVN/RxISM/Core/ISA.h>

namespace RxISM { using namespace ZQF::ReVN::RxISM; }


auto main(void) -> int
{
	try
	{
		ZxArg::Parser arg;
        arg.SetAbout("ISM Engine: .isa editor");
        arg.SetAuthor("github.com/Dir-A");
		arg.AddOption("-isa", "isa path");
        arg.AddOption("-dir", "files dir");
        arg.AddOption("-sig", "sig -> [\"ISM ENGLISH \" | \"ISM ARCHIVED\"]", "ISM ARCHIVED");
		arg.AddOption("-mode", "mode -> [unpack | repack]");
		arg.AddExample("-mode unpack -isa script.isa -dir script/");
        arg.AddExample("-mode repack -dir script/ -sig \"ISM ENGLISH \" -isa script.isa.new");
        arg.AddExample("-mode repack -dir script/ -sig \"ISM ARCHIVED\" -isa script.isa.new");
		if (arg.Parse() == false) { return 0; }

		const auto mode{ arg["-mode"].GetStrView() };

		if (mode == "unpack")
		{
			RxISM::ISA::Export(arg["-isa"].GetStrView(), arg["-dir"].GetStrView());
			std::println("isa unpack done!");
		}
		else if (mode == "repack")
		{
            RxISM::ISA::Import(arg["-dir"].GetStrView(), arg["-isa"].GetStrView(), arg["-sig"].GetStrView());
			std::println("isa repack done!");
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
