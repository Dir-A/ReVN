#include <print>
#include <iostream>
#include <ZxArg/Parser.h>
#include <RxPJADV/Core/TextManager.h>


auto main(void) -> int
{
	try
	{
		ZQF::ZxArg::Parser cmd;
		cmd.AddCmd("-text", "textdata path");
		cmd.AddCmd("-scen", "scenario path");
		cmd.AddCmd("-jmsg", "msg json path");
		cmd.AddCmd("-jseq", "seq json path");
		cmd.AddCmd("-code", "codepage");
		cmd.AddCmd("-mode", "mode: export | import");
		cmd.AddExample("-mode export -text textdata.bin -scen scenario.dat -jmsg scenario_msg.json -jseq scenario_seq.json -code 932");
		cmd.AddExample("-mode import -text textdata.bin -scen scenario.dat -jmsg scenario_msg.json -jseq scenario_seq.json -code 932");
		if (cmd.Parse() == false) { return 0; }

		if (cmd["-mode"].Get<std::string_view>() == "export")
		{
			ZQF::RxPJADV::Script::TextManager::Export(cmd["-text"].Get<std::string_view>(), cmd["-scen"].Get<std::string_view>(), cmd["-jmsg"].Get<std::string_view>(), cmd["-jseq"].Get<std::string_view>(), cmd["-code"].Get<std::size_t>());
			std::println("export done!");
		}
		else if (cmd["-mode"].Get<std::string_view>() == "import")
		{
			ZQF::RxPJADV::Script::TextManager::Import(cmd["-text"].Get<std::string_view>(), cmd["-scen"].Get<std::string_view>(), cmd["-jmsg"].Get<std::string_view>(), cmd["-jseq"].Get<std::string_view>(), cmd["-code"].Get<std::size_t>());
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