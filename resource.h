#pragma once

#define VERSION_MAJOR 2
#define VERSION_MINOR 0
#define VERSION_REVISION 0
#define VERSION_BUILD 20141207

#define MAKE_VERSION_NUMBER_STRING_EX(major,minor,revision,build) \
	#major "." #minor "." #revision "." #build
#define MAKE_VERSION_NUMBER_STRING(major,minor,revision,build) \
	MAKE_VERSION_NUMBER_STRING_EX(major,minor,revision,build)

#define VERSION_NUMBER \
	VERSION_MAJOR,\
	VERSION_MINOR,\
	VERSION_REVISION,\
	VERSION_BUILD
#define VERSION_NUMBER_STRING \
	MAKE_VERSION_NUMBER_STRING(\
		VERSION_MAJOR, \
		VERSION_MINOR, \
		VERSION_REVISION, \
		VERSION_BUILD)

