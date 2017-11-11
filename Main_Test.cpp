
//#include <ostream>
#define CATCH_CONFIG_RUNNER
#include "Catch.hpp"

int main(int argc, char* const argv[]) {
	int result = Catch::Session().run( argc, argv );
	return result;
}
