/*
Copyright (C) - Jean-Sébastien Fauteux 2017
This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 3.0 Unported License.
To view a copy of this license, visit http://creativecommons.org/licenses/by-nc-sa/3.0/ or send a letter to
Creative Commons, 444 Castro Street, Suite 900, Mountain View, California, 94041, USA.
*/

#include "application.hpp"

#include <rsm/logger.hpp>
#include <rsm/unused.hpp>

int main(int argc, char* argv[]) {
	RSM_UNUSED(argc);
	RSM_UNUSED(argv);
#if defined(NDEBUG)
	rsm::Logger::setMinLoggingLevel(rsm::Logger::LoggingLevel::Warn);
#endif

	Application app;
	app.run();
}
