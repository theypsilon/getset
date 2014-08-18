#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "../getset.hpp"

#include <string>

using namespace accessor;
using namespace std;


TEST_CASE( "GETSET_DATA_BRACEINIT/INT", "Getset int type, basic operations" ) {
	struct Data {
	    getset<int> a;
		getset<int> b;
		getset<int> c;
	} x{1,2,3};
	CHECK( x.a() == 1 );
	CHECK( x.b() == 2 );
	CHECK( x.c() == 3 );
}

TEST_CASE( "GETSET_DATA_BRACEINIT/STRING", "Getset int type, basic operations" ) {
	struct Data {
	    getset<std::string> a;
		getset<std::string> b;
		getset<std::string> c;
	} x{"1","2","3"};
	CHECK( x.a() == "1" );
	CHECK( x.b() == "2" );
	CHECK( x.c() == "3" );
}

TEST_CASE( "GETSET/INT", "Getset int type, basic operations" ) {
    getset<int> a{1};
	CHECK( a() == 1 );
	a(2);
	CHECK( a() == 2 );
	getset<int> b{a};
	getset<int> c{std::move(a)};
	CHECK( b() == 2 );
	CHECK( c() == 2 );
	getset<int> d;
	d(3);
	CHECK( d() == 3 );
	getset<int> e = 4;
	CHECK( e() == 4 );
}

TEST_CASE( "GETSET/STRING", "Getset std::string type, basic operations" ) {
    getset<std::string> a{"1"};
	CHECK( a() == "1" );
	a("2");
	CHECK( a() == "2" );
	getset<std::string> b{a};
	getset<std::string> c{std::move(a)};
	CHECK( b() == "2" );
	CHECK( c() == "2" );
	getset<std::string> d;
	CHECK( d() == "" );
	d("3");
	CHECK( d() == "3" );
	getset<std::string> e = "4";
	CHECK( e() == "4" );
}

TEST_CASE( "GETTER/INT", "Getter int type, basic operations" ) {
    getter<int> a{1};
	CHECK( a() == 1 );
	getter<int> b{a};
	getter<int> c{std::move(a)};
	CHECK( b() == 1 );
	CHECK( c() == 1 );
	getter<int> d = 3;
	CHECK( d() == 3 );
}

TEST_CASE( "GETTER_DATA/INT", "Getter int type, basic operations" ) {
	struct Data {
	    getter<int, Data> a;
		getter<int, Data> b;
		getter<int, Data> c;

		void set(int n) {
			a(n);
		}
	} x{1,2,3};
    CHECK( x.a() == 1 );
    x.set(2);
    CHECK( x.a() == 2 );
}

TEST_CASE( "GETTER/STRING", "Getter std::string type, basic operations" ) {
    getter<std::string> a{"1"};
	CHECK( a() == "1" );
	getter<std::string> b{a};
	getter<std::string> c{std::move(a)};
	CHECK( b() == "1" );
	CHECK( c() == "1" );
	getter<std::string> d;
	CHECK( d() == "" );
	getter<std::string> e = "2";
	CHECK( e() == "2" );
}

TEST_CASE( "SETTER_DATA_DEFAULT/INT", "Setter int type, basic operations" ) {
	struct Data {
	    setter<int, Data> a;
		setter<int, Data> b;
		setter<int, Data> c;

		Data() : a{1}, b{a}, c{std::move(a)} {
			CHECK( a() == 1 );
			CHECK( b() == 1 );
			CHECK( c() == 1 );
		}

		void check(int n) {
			CHECK( a() == n );
		}
	} x;
    x.a(3);
    x.check(3);
}

TEST_CASE( "SETTER_DATA_BRACEINIT/INT", "Setter int type, basic operations" ) {
	struct Data {
	    setter<int, Data> a;
		setter<int, Data> b;
		setter<int, Data> c;

		void check(int n) {
			CHECK( a() == n );
		}
	} x{1,2,3};
    x.check(1);
    x.a(3);
    x.check(3);
}

TEST_CASE( "SETTER_DATA_BRACEINIT/STRING", "Setter int type, basic operations" ) {
	struct Data {
	    setter<std::string, Data> a;
		setter<std::string, Data> b;
		setter<std::string, Data> c;

		void check(std::string n) {
			CHECK( a() == n );
		}
	} x{"1","2","3"};
    x.check("1");
    x.a("3");
    x.check("3");
}
