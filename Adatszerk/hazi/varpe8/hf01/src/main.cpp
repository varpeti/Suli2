#include "skiplist.hpp"

struct skiplist
{
    SKIPLIST<int,int> slist;
    void insert(int value) {slist.insert(value,value);}
    void erase(int value) {slist.erase(value);}
    bool contains(int value) {return slist.contains(value);}
    int size(){return slist.size();}
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#include <string>
#include <iostream>
#include <set>
#include <cstdlib>
#include <ctime>
#include <functional>
#include <chrono>

struct test_controller {
    bool enabled;
    std::string label;
    int points;
    bool ok;
    bool run;
    int &out;
    test_controller(bool enabled, std::string&& label, int points, int &out)
        : enabled(enabled)
        , label(std::move(label))
        , points(points)
        , ok(true)
        , run(true)
        , out(out)
    {    
        if (enabled) {
            std::cout << ">>> Test: " << this->label << " (" << points << ")" << std::endl;
        }
    }
    ~test_controller() {
        if (enabled) {
            out += ok ? points : 0;
            std::cout << ">>> Result: " << (ok ? "PASS" : "FAIL") << std::endl;
        }
    }
};

struct measurement_controller {
    std::string name;
    std::chrono::nanoseconds &out;
    std::chrono::time_point<std::chrono::high_resolution_clock> start;
    bool run;
    measurement_controller(std::string &&name, std::chrono::nanoseconds &out)
        : name(std::move(name))
        , out(out)
        , start(std::chrono::high_resolution_clock::now())
        , run(true) {}
    ~measurement_controller() {
        auto stop = std::chrono::high_resolution_clock::now();
        out = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start);
        std::cout << name << ": " << out.count() << "ns" << std::endl;
    }
};
        

#define TEST(label, points) \
    for (test_controller cntr(++counter == test_no || test_no == 0, label, points, total); \
        cntr.run; cntr.run = false)

#define CHECK(code) \
    if (cntr.ok) { \
        try { \
            code; \
        } catch (...) { \
            cntr.ok = false; \
            std::cout << ">>> unexpected exception" << std::endl; \
        } \
        if (!cntr.ok) { \
            std::cout << ">>> " << #code << " failed at " << __LINE__ << std::endl; \
        } \
    }

#define CHECK_EQ(val, expr) \
    if (cntr.ok) { \
        try { \
            cntr.ok = (val) == (expr); \
        } catch (...) { \
            cntr.ok = false; \
            std::cout << ">>> unexpected exception" << std::endl; \
        } \
        if (!cntr.ok) { \
            std::cout << ">>> " << #val << " == " << #expr << " failed at " << __LINE__ << std::endl; \
        } \
    }

#define CHECK_EXC(exc, code) \
    if (cntr.ok) { \
        try { \
            code; \
            cntr.ok = false; \
            std::cout << ">>> expected exception" << std::endl; \
        } catch (exc) { \
        } catch (...) { \
            std::cout << ">>> unexpected exception" << std::endl; \
            cntr.ok = false; \
        } \
        if (!cntr.ok) { \
            std::cout << #code << " failed at" << __LINE__ << std::endl; \
        } \
    }

#define MEASURE(label, var) \
    std::chrono::nanoseconds var; \
    for (measurement_controller mcntr(label, var); mcntr.run; mcntr.run = false)

int main(int argc, char *argv[]) {
    int test_no = 0;
    int counter = 0;
    int total = 0;
    time_t rng_seed = time(nullptr);
    std::cout << "Random seed: " << rng_seed << std::endl;
    srand(rng_seed);
    if (argc == 2) {
        test_no = std::atoi(argv[1]);
    }

    TEST("Create an empty list. Size should be 0.", 5) {
        skiplist sl;
        CHECK_EQ(0, sl.size());
    }

    TEST("Add a few elements. Size should grow.", 10) {
        skiplist sl;
        CHECK_EQ(0, sl.size());
        sl.insert(3);
        CHECK_EQ(1, sl.size());
        sl.insert(42);
        CHECK_EQ(2, sl.size());
        sl.insert(0);
        CHECK_EQ(3, sl.size());
        sl.insert(-100);
        CHECK_EQ(4, sl.size());
        sl.insert(6);
        CHECK_EQ(5, sl.size());
    }

    TEST("Add a few elements. Elements should be in the list.", 10) {
        skiplist sl;
        sl.insert(3);
        sl.insert(-23123);
        sl.insert(2222);
        CHECK_EQ(true, sl.contains(3));
        CHECK_EQ(true, sl.contains(-23123));
        CHECK_EQ(true, sl.contains(2222));
        CHECK_EQ(false, sl.contains(0));
        CHECK_EQ(false, sl.contains(1));
        CHECK_EQ(false, sl.contains(5765));
    }

    TEST("Try to add duplicate elements. Size should not grow.", 10) {
        skiplist sl;
        sl.insert(9);
        sl.insert(7);
        sl.insert(21);
        sl.insert(9);
        sl.insert(9);
        sl.insert(24);
        sl.insert(7);
        CHECK_EQ(4, sl.size());
        CHECK_EQ(true, sl.contains(9));
        CHECK_EQ(true, sl.contains(7));
        CHECK_EQ(true, sl.contains(21));
        CHECK_EQ(true, sl.contains(24));
    }

    TEST("Delete a few elements. Size should shrink.", 10) {
        skiplist sl;
        sl.insert(12);
        sl.insert(89);
        sl.insert(100);
        sl.insert(56);
        sl.insert(86);
        sl.insert(5);
        CHECK_EQ(6, sl.size());
        sl.erase(12);
        CHECK_EQ(5, sl.size());
        sl.erase(5);
        CHECK_EQ(4, sl.size());
        sl.erase(100);
        CHECK_EQ(3, sl.size());
        sl.erase(89);
        CHECK_EQ(2, sl.size());
    }

    TEST("Delete a few elements. They should disappear.", 10) {
        skiplist sl;
        sl.insert(12);
        sl.insert(89);
        sl.insert(100);
        sl.insert(56);
        sl.insert(86);
        sl.insert(5);
        sl.erase(12);
        sl.erase(5);
        sl.erase(100);
        sl.erase(89);
        CHECK_EQ(false, sl.contains(12));
        CHECK_EQ(false, sl.contains(5));
        CHECK_EQ(false, sl.contains(100));
        CHECK_EQ(false, sl.contains(89));
        CHECK_EQ(true, sl.contains(86));
        CHECK_EQ(true, sl.contains(56));
    }

    TEST("Delete non-existent elements. Size should stay the same.", 10) {
        skiplist sl;
        sl.insert(3);
        sl.insert(4);
        sl.insert(5);
        sl.insert(9);
        CHECK_EQ(4, sl.size());
        sl.erase(0);
        sl.erase(7);
        CHECK_EQ(4, sl.size());
        CHECK_EQ(true, sl.contains(3));
        CHECK_EQ(true, sl.contains(4));
        CHECK_EQ(true, sl.contains(5));
        CHECK_EQ(true, sl.contains(9));
    }

    TEST("Do a lot of random operations. Skiplist should behave the same as a std::set", 20) {
        std::set<int> ref;
        skiplist sl;
        for (size_t i = 0; i<10000; ++i) {
            const int rnd = rand()%200 - 100;
            switch (rand() % 3) {
                case 0:
                    ref.insert(rnd);
                    sl.insert(rnd);
                    break;
                case 1:
                    CHECK_EQ(ref.count(rnd) > 0, sl.contains(rnd));
                    break;
                case 2:
                    ref.erase(rnd);
                    sl.erase(rnd);
                    break;
            }
            CHECK_EQ(ref.size(), sl.size());
        }
    }

    TEST("Build a 2^5 and a 2^10-large set. Operation times on the two should be within a factor of ~2", 15) {
        skiplist small, big;

        while (small.size() < 32) {
            small.insert(rand());
        }
        while (big.size() < 1024) {
            big.insert(rand());
        }
        MEASURE("Insert into small set", small_insert) {
            for (size_t i = 0; i<10; ++i) {
                small.insert(rand());
            }
        }
        MEASURE("Erase from small set", small_erase) {
            for (size_t i = 0; i<10; ++i) {
                small.erase(rand());
            }
        }
        MEASURE("Query small set", small_contains) {
            for (size_t i = 0; i<10; ++i) {
                small.contains(rand());
            }
        }
        MEASURE("Insert into big set", big_insert) {
            for (size_t i = 0; i<10; ++i) {
                big.insert(rand());
            }
        }
        MEASURE("Erase from big set", big_erase) {
            for (size_t i = 0; i<10; ++i) {
                big.erase(rand());
            }
        }
        MEASURE("Query big set", big_contains) {
            for (size_t i = 0; i<10; ++i) {
                big.contains(rand());
            }
        }
        CHECK_EQ(true, small_insert*2.3 >= big_insert);
        CHECK_EQ(true, small_erase*2.3 >= big_erase);
        CHECK_EQ(true, small_contains*2.3 >= big_contains);
    }

    std::cout << ">>> TOTAL POINTS: " << total << std::endl;
    return 0;
}
//*/

