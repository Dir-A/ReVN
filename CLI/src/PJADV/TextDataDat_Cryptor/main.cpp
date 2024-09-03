#include <print>
#include <iostream>
#include <ZxArg/Parser.h>
#include <ZxMem/ZxMem.h>
#include <RxPJADV/Core/Bin_TextData.h>


auto main(void) -> int
{
	try
	{
		ZQF::ZxArg::Parser arg;
		arg.AddCmd("-bin", "textdata file path");
		arg.AddCmd("-save", "textdata save path");
		arg.AddExample("-bin textdata.bin -save textdata.bin.dec");
		if (arg.Parse() == false) { return 0; }

		ZQF::ZxMem text_data_mem{ arg["-bin"].Get<std::string_view>() };
		ZQF::RxPJADV::Script::TextDataDat::XorBytes(text_data_mem.Span(), 0xC5);
		text_data_mem.Save(arg["-save"].Get<std::string_view>());

		std::println("cryptor done!");
	}
	catch (const std::exception& err)
	{
		std::println(std::cerr, "std::exception: {}", err.what());
	}
}