#include <print>
#include <iostream>
#include <Zut/ZxArg.h>
#include <Zut/ZxMem.h>
#include <ReVN/RxPJADV/Core/Bin_TextData.h>

namespace RxPJADV { using namespace ZQF::ReVN::RxPJADV; }


auto main(void) -> int
{
	try
	{
		ZxArg::Parser arg;
		arg.AddOption("-bin", "textdata file path");
		arg.AddOption("-save", "textdata save path");
		arg.AddExample("-bin textdata.bin -save textdata.bin.dec");
		if (arg.Parse() == false) { return 0; }

		ZxMem text_data_mem{ arg["-bin"].GetStrView() };
		RxPJADV::Script::TextDataDat::XorBytes(text_data_mem.Span(), 0xC5);
		text_data_mem.Save(arg["-save"].GetStrView());

		std::println("cryptor done!");
	}
	catch (const std::exception& err)
	{
		std::println(std::cerr, "std::exception: {}", err.what());
	}
}
