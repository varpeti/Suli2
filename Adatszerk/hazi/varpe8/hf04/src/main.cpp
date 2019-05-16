#include "networksort.hpp"

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
            cntr.ok = val == (expr); \
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

#define CHECK_ANY_EXC(code) \
    if (cntr.ok) { \
        try { \
            code; \
            cntr.ok = false; \
            std::cout << ">>> expected exception" << std::endl; \
        } catch (...) { \
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

    TEST("Rendezettet megtartja-e", 5) {
       int array[16] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16};
       rendezo_halozat(array,16);
       for (int i = 1; i < 16; ++i)
       {
            CHECK_EQ((array[i]>array[i-1]),true);
       }
    }

    TEST("Forditott", 5) {
       int array[16] = {8,7,6,5,4,3,2,1,0,-1,-2,-3,-4,-5,-6,-7};
       rendezo_halozat(array,16);
       for (int i = 1; i < 16; ++i)
       {
            CHECK_EQ((array[i]>array[i-1]),true);
       }
    }

    TEST("\"Random\"", 20) {
        int array[16] = {16,12,13,14,1,6,8,10,11,9,2,5,3,4,7,15};
        rendezo_halozat(array,16);
        for (int i = 1; i < 16; ++i)
        {
            CHECK_EQ((array[i]>array[i-1]),true);
        }
    }

    TEST("Float", 20) {
        float array[16] = {1.6,1.2,1.3,1.4,1.2,6.5,8.2,10.1,11.1,9.2,2.3,5.4,3.9,4.5,7.0,15.0};
        rendezo_halozat(array,16);
        for (int i = 1; i < 16; ++i)
        {
            CHECK_EQ((array[i]>=array[i-1]),true);
        }
    }

    TEST("Exception teszt", 20) {
        const int size = 13;
        int array[size];
        for (int i = 0; i < size; ++i) array[i]=rand() % size;

        CHECK_ANY_EXC(rendezo_halozat(array,size))
        
    }

    TEST("Nagy random", 30) {
        const int size = 32768;
        int array[size];
        for (int i = 0; i < size; ++i) array[i]=rand() % size;

        rendezo_halozat(array,size);
        for (int i = 1; i < size; ++i)
        {
            CHECK_EQ((array[i]>=array[i-1]),true);
        }
    }

    

    TEST("Ido teszt", 0) {
        const int kicsi_size = 1024;
        int kicsi_array[kicsi_size];
        for (int i = 0; i < kicsi_size; ++i) kicsi_array[i]=rand() % kicsi_size;

        const int nagy_size = 32768;
        int nagy_array[nagy_size];
        for (int i = 0; i < nagy_size; ++i) nagy_array[i]=rand() % nagy_size;
        
        MEASURE("Kicsi (1024)", kicsi) {
            rendezo_halozat(kicsi_array,kicsi_size);
        }
        MEASURE("Nagy (32768)", nagy) {
            rendezo_halozat(nagy_array,nagy_size);
        }
    }

    std::cout << ">>> TOTAL POINTS: " << total << std::endl;
    getchar();
    return 0;
}