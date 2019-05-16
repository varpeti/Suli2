#ifndef _ENV_
#define _ENV_

#include "math.h"

struct Skoord
{   
    double x;
    double y;
    double z;

    Skoord()
    {
        x=0;
        y=0;
        z=0;
    }

    Skoord(double _x,double _y,double _z = 0)
    {
        x=_x;
        y=_y;
        z=_z;
    }

    Skoord operator+(Skoord);
    Skoord operator-(Skoord);
    Skoord operator/(double);
    double operator|(Skoord);

    Skoord forgat(double alpha, double beta, double gamma);
    Skoord lekepzes(double kx,double ky,double kz);
};

Skoord Skoord::operator+(Skoord b)
{
    Skoord c;
    c.x = x+b.x;
    c.y = y+b.y;
    c.z = z+b.z;
    return(c);
}

Skoord Skoord::operator-(Skoord b)
{
    Skoord c;
    c.x = x-b.x;
    c.y = y-b.y;
    c.z = z-b.z;
    return(c);
}

Skoord Skoord::operator/(double b)
{
    Skoord c;
    c.x = x/b;
    c.y = y/b;
    c.z = z/b;
    return(c);
}

double Skoord::operator|(Skoord b)
{
    return sqrt( (x-b.x)*(x-b.x)+(y-b.y)*(y-b.y)+(z-b.z)*(z-b.z) );
}

Skoord Skoord::forgat(double alpha, double beta, double gamma)
{
    double se;
    Skoord f=*this;

    //y tengely körüli forgatás
    se= f.x*cos(alpha)+f.z*sin(alpha);
    f.z= -f.x*sin(alpha)+f.z*cos(alpha);
    f.x= se;

    //x tengely körüli forgatás
    se= f.y*cos(beta)-f.z*sin(beta);
    f.z= f.y*sin(beta)+f.z*cos(beta);
    f.y= se;

    //z tengely körüli forgatás
    se= f.x*cos(gamma)-f.y*sin(gamma);
    f.y= f.x*sin(gamma)+f.y*cos(gamma);
    f.x= se;
    return f;
}

Skoord Skoord::lekepzes(double kx,double ky,double kz) // kx ky kz - a világ nagysága
{
    double mz = (kz/2 + z)/(kz/2) *12; if (mz<3) mz=3; // Mekkora legyen ; minumum 3
    return Skoord(x + z/2 + kx/2,y + z/2 + ky/2,mz); // a Z koordináta a nagyságát adja meg
}

struct Sszin
{
    unsigned char rr;
    unsigned char gg;
    unsigned char bb;
    Sszin()
    {
        rr=255;
        gg=255;
        bb=255;
    }
    Sszin(unsigned char _rr, unsigned char _gg, unsigned char _bb)
    {
        rr=_rr;
        gg=_gg;
        bb=_bb;
    }
};

struct Svonal
{
    Skoord a;
    Skoord b;
    unsigned int meret;
    Sszin szin;
    Svonal()
    {
        a=Skoord();
        b=Skoord();
        meret=1;
        szin=Sszin();
    }
    Svonal(Skoord _a, Skoord _b, unsigned int _meret, Sszin _szin)
    {
        a=_a;
        b=_b;
        meret=_meret;
        szin=_szin;
    }

    Skoord* getAp()
    {
        return &a;
    }

    Skoord* getBp()
    {
        return &b;
    }
};

#endif