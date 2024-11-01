#include <print>
#include <iostream>
#include <Zut/ZxFS.h>
#include <Zut/ZxArg.h>
#include <ReVN/RxValkyria/Core/SDT_TextParser.h>

namespace RxValkyria { using namespace ZQF::ReVN::RxValkyria; }


static auto Export(const std::string_view msSdtPath, const std::string_view msSavePath, const std::size_t nCodePage) -> bool
{
    RxValkyria::SDT::TextParserJsonManager text_parser{ msSdtPath };
    if (text_parser.Parse() == false)
    {
        std::println("export -> {} | not find text", msSdtPath);
        return false;
    }

    text_parser.Export(msSavePath, nCodePage);

    std::println("export -> {} | sav -> {}", msSdtPath, msSavePath);
    return true;
}

static auto Import(const std::string_view msSdtPath, const std::string_view msJsonPath, const std::string_view msNewSdtPath, const std::size_t nCodePage) -> bool
{
    RxValkyria::SDT::TextParserJsonManager text_parser{ msSdtPath };
    if (text_parser.Parse() == false)
    {
        std::println("import -> {} | not find text", msSdtPath);
        return false;
    }

    text_parser.Import(msNewSdtPath, msJsonPath, nCodePage);

    std::println("import -> {} | json -> {} | sav -> {}", msSdtPath, msJsonPath, msNewSdtPath);
    return true;
}


auto main(void) -> int
{
	try
	{
		ZxArg::Parser arg;
		arg.AddOption("-sdt", "sdt org path");
		arg.AddOption("-sav", "sdt sav path");
		arg.AddOption("-json", "json path");
		arg.AddOption("-mode", "mode: single | batch");
		arg.AddOption("-way", "way: export | import");
		arg.AddOption("-code", "code page");
		arg.AddExample("-mode batch -way export -sdt sdt/ -json sdt_json/ -code 932");
		arg.AddExample("-mode batch -way import -sdt sdt/ -json sdt_json/ -sav sdt_new/ -code 936");
		arg.AddExample("-mode single -way export -sdt seen1100.sdt -json seen1100.json -code 932");
		arg.AddExample("-mode single -way import -sdt seen1100.sdt -json seen1100.json -sav seen1100.sdt.new -code 936");
		if (arg.Parse() == false) { return 0; }

		const auto mode = arg["-mode"].GetStrView();
		const auto way = arg["-way"].GetStrView();
		const auto code_page = arg["-code"].GetNum();

		if (mode == "batch")
		{
			const auto sdt_json_dir{ arg["-json"].GetStrView() };
			const auto sdt_org_dir{ arg["-sdt"].GetStrView() };

			if (way == "export")
			{
				ZxFS::DirMakeRecursive(sdt_json_dir);
				for (ZxFS::Walker walker{ sdt_org_dir }; walker.NextFile(); )
				{
					const std::string_view org_path{ walker.GetPath() };
					const std::string sav_path{ std::string{ sdt_json_dir }.append(ZxFS::FileNameStem(walker.GetName())).append(".json") };
					::Export(org_path, sav_path, code_page);
				}
			}
			else if (way == "import")
			{
				const auto sdt_sav_dir{ arg["-sav"].GetStrView() };

				ZxFS::DirMakeRecursive(sdt_sav_dir);
				for (ZxFS::Walker walker{ sdt_json_dir }; walker.NextFile(); )
				{
					const std::string_view json_path{ walker.GetPath() };
					const std::string org_path{ std::string{ sdt_org_dir }.append(ZxFS::FileNameStem(walker.GetName())).append(".sdt") };
					const std::string sav_path{ std::string{ sdt_sav_dir }.append(ZxFS::FileNameStem(walker.GetName())).append(".sdt") };
					::Import(org_path, json_path, sav_path, code_page);
				}
			}

            std::println("batch command done!");
		}
		else if (mode == "single")
		{
			const auto sdt_org_path{ arg["-sdt"].GetStrView() };
			const auto save_path{ arg["-sav"].GetStrView() };

			if (way == "export")
			{
				::Export(sdt_org_path, save_path, code_page);
			}
			else if (way == "import")
			{
				const auto json_path{ arg["-json"].GetStrView() };
				::Import(sdt_org_path, json_path, save_path, code_page);
			}

            std::println("single command done!");
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
