﻿#include <print>
#include <iostream>
#include <ZxFS/Core.h>
#include <ZxFS/Walker.h>
#include <ZxArg/Parser.h>
#include <RxValkyria/Core/SDT_TextParser.h>


static auto Export(const std::string_view msSdtPath, const std::string_view msSavePath, const std::size_t nCodePage) -> void
{
	ZQF::RxValkyria::SDT::TextParserJsonManager text_parser{ msSdtPath };
	if (text_parser.Parse())
	{
		text_parser.Export(msSavePath, nCodePage);
		std::println("export -> {} | sav -> {}", msSdtPath, msSavePath);
	}
	else
	{
		std::println("export -> {} | not find text", msSdtPath);
	}
}

static auto Import(const std::string_view msSdtPath, const std::string_view msJsonPath, const std::string_view msNewSdtPath, const std::size_t nCodePage) -> void
{
	ZQF::RxValkyria::SDT::TextParserJsonManager text_parser{ msSdtPath };
	if (text_parser.Parse())
	{
		text_parser.Import(msNewSdtPath, msJsonPath, nCodePage);
		std::println("import -> {} | json -> {} | sav -> {}", msSdtPath, msJsonPath, msNewSdtPath);
	}
	else
	{
		std::println("import -> {} | json -> {} | not find text", msSdtPath, msJsonPath);
	}
}


auto main(void) -> int
{
	try
	{
		ZQF::ZxArg::Parser arg;
		arg.AddCmd("-sdt", "sdt org path");
		arg.AddCmd("-sav", "sdt sav path");
		arg.AddCmd("-json", "json path");
		arg.AddCmd("-mode", "mode: single | batch");
		arg.AddCmd("-way", "way: export | import");
		arg.AddCmd("-code", "code page");
		arg.AddExample("-mode batch -way export -sdt sdt/ -json sdt_json/ -code 932");
		arg.AddExample("-mode batch -way import -sdt sdt/ -json sdt_json/ -sav sdt_new/ -code 936");
		arg.AddExample("-mode single -way export -sdt seen1100.sdt -json seen1100.json -code 932");
		arg.AddExample("-mode single -way import -sdt seen1100.sdt -json seen1100.json -sav seen1100.sdt.new -code 936");
		if (arg.Parse() == false) { return 0; }

		const auto mode = arg["-mode"].Get<std::string_view>();
		const auto way = arg["-way"].Get<std::string_view>();
		const auto code_page = arg["-code"].Get<std::size_t>();

		if (mode == "batch")
		{
			const auto sdt_json_dir{ arg["-json"].Get<std::string_view>() };
			const auto sdt_org_dir{ arg["-sdt"].Get<std::string_view>() };

			if (way == "export")
			{
				ZQF::ZxFS::DirMake(sdt_json_dir, true);
				for (ZQF::ZxFS::Walker walker{ sdt_org_dir }; walker.NextFile(); )
				{
					const std::string_view org_path{ walker.GetPath() };
					const std::string sav_path{ std::string{ sdt_json_dir }.append(ZQF::ZxFS::FileNameStem(walker.GetName())).append(".json") };
					::Export(org_path, sav_path, code_page);
					
				}
			}
			else if (way == "import")
			{
				const auto sdt_sav_dir{ arg["-sav"].Get<std::string_view>() };

				ZQF::ZxFS::DirMake(sdt_sav_dir, true);
				for (ZQF::ZxFS::Walker walker{ sdt_json_dir }; walker.NextFile(); )
				{
					const std::string_view json_path{ walker.GetPath() };
					const std::string org_path{ std::string{ sdt_org_dir }.append(ZQF::ZxFS::FileNameStem(walker.GetName())).append(".sdt") };
					const std::string sav_path{ std::string{ sdt_sav_dir }.append(ZQF::ZxFS::FileNameStem(walker.GetName())).append(".sdt") };
					::Import(org_path, json_path, sav_path, code_page);
				}
			}
		}
		else if (mode == "single")
		{
			const auto sdt_org_path{ arg["-sdt"].Get<std::string_view>() };
			const auto save_path{ arg["-sav"].Get<std::string_view>() };

			if (way == "export")
			{
				::Export(sdt_org_path, save_path, code_page);
			}
			else if (way == "import")
			{
				const auto json_path{ arg["-json"].Get<std::string_view>() };
				::Import(sdt_org_path, json_path, save_path, code_page);
			}
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