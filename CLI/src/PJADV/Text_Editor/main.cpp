#include <print>
#include <iostream>
#include <Zut/ZxArg.h>
#include <ReVN/RxPJADV/Core/TextManager.h>

namespace RxPJADV { using namespace ZQF::ReVN::RxPJADV; }


auto main(void) -> int
{
	try
	{
		ZxArg::Parser cmd;
		cmd.AddOption("-text", "textdata path");
		cmd.AddOption("-scen", "scenario path");
		cmd.AddOption("-jmsg", "msg json path");
		cmd.AddOption("-jseq", "seq json path");
		cmd.AddOption("-code", "codepage");
		cmd.AddOption("-mode", "mode: export | import");
		cmd.AddExample("-mode export -text textdata.bin -scen scenario.dat -jmsg scenario_msg.json -jseq scenario_seq.json -code 932");
		cmd.AddExample("-mode import -text textdata.bin -scen scenario.dat -jmsg scenario_msg.json -jseq scenario_seq.json -code 932");
		if (cmd.Parse() == false) { return 0; }

		if (cmd["-mode"].Get<std::string_view>() == "export")
		{
			RxPJADV::Script::TextManager::Export(cmd["-text"].Get<std::string_view>(), cmd["-scen"].Get<std::string_view>(), cmd["-jmsg"].Get<std::string_view>(), cmd["-jseq"].Get<std::string_view>(), cmd["-code"].Get<std::size_t>());
			std::println("export done!");
		}
		else if (cmd["-mode"].Get<std::string_view>() == "import")
		{
			RxPJADV::Script::TextManager::Import(cmd["-text"].Get<std::string_view>(), cmd["-scen"].Get<std::string_view>(), cmd["-jmsg"].Get<std::string_view>(), cmd["-jseq"].Get<std::string_view>(), cmd["-code"].Get<std::size_t>());
			std::println("import done!");
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
