#include "../graphics.hpp"

using namespace genv;

int main()
{
    gout.open(200,200);
    gout << text("hello world") << refresh;
    event ev;
    while(gin >> ev) {
    }
    return 0;
}
