#include "db_table.hpp"
#define db_table DB_TABLE

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#include <string>
#include <iostream>
#include <set>
#include <cstdlib>
#include <ctime>

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

int main(int argc, char *argv[]) {
    int test_no = 0;
    int counter = 0;
    int total = 0;
    srand(time(nullptr));
    if (argc == 2) {
        test_no = std::atoi(argv[1]);
    }

    using namespace std;

    TEST("create an empty table", 5) {
        db_table t;
    }

    TEST("add good columns", 10) {
        db_table t;
        set<string> cn {"asd", "AsDf"};
        t.add_column("asd");
        t.add_column("AsDf");
        auto vec = t.column_names();
        set<string> st(vec.begin(), vec.end());
        CHECK_EQ(cn, st);
    }

    TEST("add bad columns", 5) {
        db_table t;
        CHECK_EXC(invalid_column_name, t.add_column("i'm invalid"));
        CHECK_EXC(invalid_column_name, t.add_column("=lllll"));
        CHECK_EXC(invalid_column_name, t.add_column(",kkkk"));
        CHECK_EXC(invalid_column_name, t.add_column(""));
        t.add_column("a");
        CHECK_EXC(invalid_column_name, t.add_column("a"));
    }

    TEST("add rows", 5) {
        db_table t;
        t.add_row();
        t.add_row();
        CHECK_EQ(2, t.row_count());
        t.add_column("aaa");
        t.add_row();
        CHECK_EQ(3, t.row_count());
    }

    TEST("set/get values with good index", 10) {
        db_table t;
        t.add_column("col1");
        t.add_column("col2");
        t.add_row();
        t.add_row();
        t.set("col1", 0, "a");
        t.set("col2", 1, "a+b");
        CHECK_EQ("", t.get("col2", 0));
        CHECK_EQ("", t.get("col1", 1));
        CHECK_EQ("a", t.get("col1", 0));
        CHECK_EQ("a+b", t.get("col2", 1));
        t.set("col1", 0, "x");
        CHECK_EQ("x", t.get("col1", 0));
        t.add_column("col3");
        CHECK_EQ("", t.get("col3", 0));
        CHECK_EQ("", t.get("col3", 1));
    }

    TEST("set/get values with bad index", 5) {
        db_table t;
        t.add_column("col1");
        t.add_row();
        t.add_row();
        CHECK_EXC(invalid_index, t.set("col2", 0, "e"));
        CHECK_EXC(invalid_index, t.get("col2", 0));
        CHECK_EXC(invalid_index, t.set("col1", 10, "e"));
        CHECK_EXC(invalid_index, t.get("col1", 10));
        CHECK_EXC(invalid_index, t.set("col+", 0, "e"));
        CHECK_EXC(invalid_index, t.get("col+", 0));
    }

    TEST("set bad value", 5) {
        db_table t;
        t.add_column("col1");
        t.add_row();
        std::string str = "asd";
        str.push_back('\0');
        str += "asd";
        CHECK_EXC(invalid_value, t.set("col1", 0, str));
    }

    TEST("simple join", 15) {
        db_table t1;
        t1.add_column("1col1");
        t1.add_column("1col2");
        t1.add_row();
        t1.add_row();
        t1.set("1col1", 0, "a");
        t1.set("1col2", 0, "b");
        t1.set("1col1", 1, "c");
        t1.set("1col2", 1, "d");
        db_table t2;
        t2.add_column("2col1");
        t2.add_column("2col2");
        t2.add_row();
        t2.add_row();
        t2.set("2col1", 0, "b");
        t2.set("2col2", 0, "b");
        t2.set("2col1", 1, "y");
        t2.set("2col2", 1, "z");

        db_table t3 = t1.join(t2, "1col2=2col2");
        CHECK_EQ(4, t3.column_names().size());
        CHECK_EQ(1, t3.row_count());
        CHECK_EQ("a", t3.get("1col1", 0));
        CHECK_EQ("b", t3.get("1col2", 0));
        CHECK_EQ("b", t3.get("2col1", 0));
        CHECK_EQ("b", t3.get("2col2", 0));

        db_table t4 = t1.join(t2, "1col2=2col2,1col2=2col1");
        CHECK_EQ(4, t4.column_names().size());
        CHECK_EQ(1, t4.row_count());
        CHECK_EQ("a", t4.get("1col1", 0));
        CHECK_EQ("b", t4.get("1col2", 0));
        CHECK_EQ("b", t4.get("2col1", 0));
        CHECK_EQ("b", t4.get("2col2", 0));

        db_table t5 = t1.join(t2, "1col1=2col2,1col2=2col2,1col1=2col1");
        CHECK_EQ(4, t5.column_names().size());
        CHECK_EQ(0, t5.row_count());
    }

    TEST("more complex join", 20) {
        db_table a, b;
        a.add_column("a1");
        a.add_column("a2");
        a.add_column("a3");
        b.add_column("b1");
        b.add_column("b2");
        b.add_column("b3");
        a.add_row();
        a.add_row();
        a.add_row();
        a.add_row();
        b.add_row();
        b.add_row();
        b.add_row();
        b.add_row();
        a.set("a1", 0, "pata");
        a.set("a2", 0, "kapa");
        a.set("a3", 0, "papa");
        a.set("a1", 1, "pata");
        a.set("a2", 1, "pete");
        a.set("a3", 1, "teve");
        a.set("a1", 2, "teve");
        a.set("a2", 2, "tele");
        a.set("a3", 2, "fele");
        a.set("a1", 3, "tere");
        a.set("a2", 3, "fere");
        a.set("a3", 3, "fele");
        b.set("b1", 0, "pata");
        b.set("b2", 0, "totĂł");
        b.set("b3", 0, "kapa");
        b.set("b1", 1, "pata");
        b.set("b2", 1, "mohĂł");
        b.set("b3", 1, "kapa");
        b.set("b1", 2, "tere");
        b.set("b2", 2, "jojĂł");
        b.set("b3", 2, "fere");
        b.set("b1", 3, "hohĂł");
        b.set("b2", 3, "hihi");
        b.set("b3", 3, "hehe");

        db_table c = a.join(b, "a1=b1,a2=b3");
        CHECK_EQ(6, c.column_names().size());
        CHECK_EQ(3, c.row_count());
        bool ok1 = false, ok2 = false, ok3 = false;
        std::cout << "looking for row 1... ";
        for (size_t i = 0; i<3; ++i) {
            bool match = true;
            match &= "pata" == c.get("a1", i);
            match &= "kapa" == c.get("a2", i);
            match &= "papa" == c.get("a3", i);
            match &= "pata" == c.get("b1", i);
            match &= "totĂł" == c.get("b2", i);
            match &= "kapa" == c.get("b3", i);
            ok1 |= match;
        }
        CHECK_EQ(true, ok1);
        std::cout << "ok" << std::endl;
        std::cout << "looking for row 2... ";
        for (size_t i = 0; i<3; ++i) {
            bool match = true;
            match &= "pata" == c.get("a1", i);
            match &= "kapa" == c.get("a2", i);
            match &= "papa" == c.get("a3", i);
            match &= "pata" == c.get("b1", i);
            match &= "mohĂł" == c.get("b2", i);
            match &= "kapa" == c.get("b3", i);
            ok2 |= match;
        }
        CHECK_EQ(true, ok2);
        std::cout << "ok" << std::endl;
        std::cout << "looking for row 3... ";
        for (size_t i = 0; i<3; ++i) {
            bool match = true;
            match &= "tere" == c.get("a1", i);
            match &= "fere" == c.get("a2", i);
            match &= "fele" == c.get("a3", i);
            match &= "tere" == c.get("b1", i);
            match &= "jojĂł" == c.get("b2", i);
            match &= "fere" == c.get("b3", i);
            ok3 |= match;
        }
        CHECK_EQ(true, ok3);
        std::cout << "ok" << std::endl;
    }

    TEST("simple yet tricky join", 10) {
        db_table t1, t2;
        t1.add_column("a");
        t1.add_column("b");
        t1.add_row();
        t2.add_column("c");
        t2.add_column("d");
        t2.add_row();
        t1.set("a", 0, "q");
        t1.set("b", 0, "qq");
        t2.set("c", 0, "qq");
        t2.set("d", 0, "q");
        db_table t3 = t1.join(t2, "a=c,b=d");
        CHECK_EQ(0, t3.row_count());
    }

    TEST("bad join conditions", 10) {
        db_table t1, t2, t3;
        t1.add_column("a");
        t1.add_column("b");
        t2.add_column("c");
        t3.add_column("a");
        t3.add_column("d");
        CHECK_EXC(invalid_condition, t1.join(t2, "a=b,"));
        CHECK_EXC(invalid_condition, t1.join(t2, "a=d"));
        CHECK_EXC(invalid_condition, t1.join(t2, "c=a"));
        CHECK_EXC(invalid_condition, t1.join(t2, "a=c,b"));
        CHECK_EXC(invalid_condition, t1.join(t2, "a=c,,b=c"));
        CHECK_EXC(invalid_condition, t1.join(t2, "a==c"));
        CHECK_EXC(invalid_condition, t1.join(t2, "a,a=c"));
        CHECK_EXC(invalid_condition, t1.join(t3, "a=d,b=a"));
    }

    std::cout << ">>> TOTAL POINTS: " << total << std::endl;
    return 0;
}