#include "../getset.hpp"
#include <string>

using namespace std;
using namespace accessor;

void run(...) {}

#define RUN()\
void run(int yes)

#ifdef TEST_SUCCESS_GETSET_INT
    struct Data {
        getset<int> a;
        getset<int> b;
    };
	RUN() {
        Data d1{2,3};
        Data d2;
        Data d3 = d1;
        getset<int> x = 1;
        getset<int> y{x};
        getset<int> z = x;
        d1.a(1);
        d1.a();
        x();
    }	
#endif

#ifdef TEST_SUCCESS_GETSET_STRING
    struct Data {
        getset<string> a;
        getset<string> b;
    };
	RUN() {
        Data d1{"2","3"};
        Data d2;
        Data d3 = d1;
        getset<string> x = "1";
        getset<string> y{x};
        getset<string> z = x;
        d1.a("1");
        d1.a();
        x();
        x("1");
    }	
#endif

#ifdef TEST_SUCCESS_GETSET_CONSTRUCTION
    struct Data {
        getset<int> a;
        getset<int> b;

        Data() : a{1}, b{2} {}
    };
	RUN() {
        Data d;
        Data{}.a();
        Data{}.a(3);
    }	
#endif

#ifdef TEST_SUCCESS_GETTER
    struct Data1 {
        getter<int> a;
        getter<int> b;
    };

    struct Data2 {
        getter<int> a;

        Data2() : a{2} {}
    };

    struct Data3 {
        getter<int, Data3> a;

        void set(int b) { a(b); }
    };

	RUN() {
        Data1 d{1,2};
        d.a();
        Data1{}.a();
        Data2{}.a();
        Data3 f;
        f.a();
        f.set(3);

        getter<int> x = 1;
        getter<int> y{x};
        getter<int> z = x;
    }
#endif

#ifdef TEST_SUCCESS_SETTER
    struct Data1 {
        setter<int, void> a;
        setter<int, void> b;
    };

    struct Data2 {
        setter<int, Data2> a;

        int get() { return a(); }
    };

	RUN() {
        Data1 d{1,2};
        d.a(5);
        Data1{}.a(2);
        Data2{}.a(3);
        Data2{}.get();
        Data2 f{1};
        f.get();

        setter<int, void> x = 1;
        setter<int, void> y{x};
        setter<int, void> z = x;
    }
#endif


#ifdef TEST_FAIL_GETSET_COPY_ASSIGN
	RUN() {
        getset<int> a;
        getset<int> b;
        a = b;
    }	
#endif

#ifdef TEST_FAIL_GETSET_MOVE_ASSIGN
	RUN() {
        getset<int> a;
        getset<int> b;
        a = std::move(b);
    }	
#endif

#ifdef TEST_FAIL_GETTER_COPY_ASSIGN
	RUN() {
        getter<int> a;
        getter<int> b;
        a = b;
    }	
#endif

#ifdef TEST_FAIL_GETTER_MOVE_ASSIGN
	RUN() {
        getter<int> a;
        getter<int> b;
        a = std::move(b);
    }	
#endif

#ifdef TEST_FAIL_SETTER_COPY_ASSIGN
	RUN() {
        setter<int> a;
        setter<int> b;
        a = b;
    }	
#endif

#ifdef TEST_FAIL_SETTER_MOVE_ASSIGN
	RUN() {
        setter<int> a;
        setter<int> b;
        a = std::move(b);
    }	
#endif

#ifdef TEST_FAIL_GETTER_SET
	RUN() {
        getter<int> a;
        a(3);
    }	
#endif

#ifdef TEST_FAIL_SETTER_GET
	RUN() {
        setter<int> a;
        a();
    }	
#endif

int main(int argc, char* argv[]) {
	run(0);
	return 0;
}
