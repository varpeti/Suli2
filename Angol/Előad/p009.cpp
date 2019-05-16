#include <iostream>

int main(int argc, char const *argv[])
{
    int x = 1;
    int y = 9;
    printf("0. x:%i y:%i\n",x,y);

    //newbie
    int s;
    s = x;
    x = y;
    y = s;
    printf("1. x:%i y:%i\n",x,y);


    //hacker
    x=x+y;
    y=x-y;
    x=x-y;
    printf("2. x:%i y:%i\n",x,y);


    //pro hacker
    x^=y;
    y^=x;
    x^=y;
    printf("3. x:%i y:%i\n",x,y);

    return 0;
}