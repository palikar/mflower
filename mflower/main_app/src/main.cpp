#include <iostream>
#include <vector>
#include <string>

#include "mflower-dev/main_app/main.hpp"

#include <fmt/format.h>

#include <spdlog/spdlog.h>
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>

int main()
{
	
	std::cout << fmt::format("This is {}\n", "working!");


	auto console = spdlog::stdout_color_mt("console");
	spdlog::get("console")->info("loggers can be retrieved from a global registry using the spdlog::get(logger_name)");


	return 0;
}
