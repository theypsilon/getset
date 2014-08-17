#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "../getset.hpp"

using namespace accessor;
using namespace std;


TEST_CASE( "Basic types, identity", "basic_id" ) {
    getset<int> a{1};
	CHECK( a() == 1 );
}
