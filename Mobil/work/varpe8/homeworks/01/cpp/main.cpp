#include <iostream>

class Weapon
{
    protected:    
        int weight;
    public:
        virtual std::string const name() = 0;
        virtual int attack() = 0;
};

class MeeleWeapon : public Weapon
{
    protected:    
        int sharpness;
    public:
        virtual std::string const name() = 0;
        virtual int attack() = 0;
};

class RangedWeapon : public Weapon
{
    protected:    
        int ammo;
    public:
        virtual std::string const name() = 0;
        virtual int attack() = 0;
};

class Sword : public MeeleWeapon
{
    protected:
        int length;
    public:
        virtual std::string const name() = 0;
        virtual int attack() = 0;
};

class Bayonett : public Sword
{
    public:
        Bayonett(){weight=13;sharpness=9;length=5;};
        virtual std::string const name() {return "Bayonett";};
        virtual int attack() {return length*sharpness-weight;};
};

class Bow : public RangedWeapon
{
    public:
        Bow(){weight=3;};
        virtual std::string const name() {return "Bow";};
        virtual int attack() {return 23-weight;};
}; 

class Gun : public RangedWeapon
{
    protected:
        int accuracity;
    public:
        virtual std::string const name() = 0;
        virtual int attack() = 0;
};

class Rifle : public Gun
{
    public:
        Rifle(){weight=7;accuracity=8;};
        virtual std::string const name() {return "Rifle";};
        virtual int attack() {return 50+accuracity*2-weight;};
}; 

class BayonettRifle : public Rifle, public Bayonett
{
    public:
        BayonettRifle(){Bayonett::weight=3;Rifle::weight=3;accuracity=6;sharpness=7;}
        virtual std::string const name() {return "BayonettRifle";};
};

class WarpedBayonettRifle : private BayonettRifle
{
    public:
        int shoot(){return Rifle::attack();};
        int swing(){return Bayonett::attack();};
    
};

int main(int argc, char const *argv[])
{
    BayonettRifle *a = new BayonettRifle();
    std::cout << a->name() << ":\n" << a->Bayonett::name() << ": " << a->Bayonett::attack() << " " << a->Rifle::name() << ": " << a->Rifle::attack() << "\n\n";

    WarpedBayonettRifle * MyWBR = new WarpedBayonettRifle();
    std::cout << "WBR:\n" << "shoot: " << MyWBR->shoot() << " swing: " << MyWBR->swing() << "\n";

    getchar(); //TODO: remove

    return 0;
}