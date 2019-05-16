#include <iostream>
#include <vector>

#define printa(a) {std::cout << a << "\n";}
#define printab(a,b) {std::cout << a << b << "\n";}

#define MAGIC_NUMBER 5
#define MAGIC_ARRAY {4,4,0,2,2,2,0}

// The Heavy duty class :)
class Weapon_AK47
{
    public:
        Weapon_AK47()
        {
            printab("Létrejöttem: ", this);
        }
        ~Weapon_AK47()
        {
            printab("Megszüntem: ",this);
        }
        void shoot()
        {
            printab("Lövök: ",this);
        }
};


class Proxy_AK47
{
    private:
        Weapon_AK47 *weapon_ak47;

    public:
        Proxy_AK47()
        {
            weapon_ak47 = nullptr;
        }
        ~Proxy_AK47()
        {
            delete weapon_ak47;
        }
        void shoot()
        {
            // Csak akkor jön létre, ha legalább egyszer használjuk
            if (weapon_ak47==nullptr)
            {
                weapon_ak47 = new Weapon_AK47();
            }
            weapon_ak47->shoot();
        }
};

int main()
{   
    //*/// Proxy nélkül


    {
        printa("\nWeapon_AK47\n");

        std::vector<Weapon_AK47*> ak47s;

        for (int i = 0; i < MAGIC_NUMBER; ++i)
        {
            ak47s.push_back(new Weapon_AK47());
        }

        // Némelyiket használjuk, akár többször is, némelyiket nem
        int random[] = MAGIC_ARRAY;
        for (const int &i : random)
        {
            ak47s[i]->shoot();
        }
    
        for (int i = 0; i < ak47s.size(); ++i)
        {
            delete ak47s[i];
        }

        ak47s.clear();
    }
    

    //*/// Proxyval

    {
        printa("\nProxy_AK47\n");

        std::vector<Proxy_AK47*> ak47s;

        for (int i = 0; i < MAGIC_NUMBER; ++i)
        {
            ak47s.push_back(new Proxy_AK47());
        }

        // Némelyiket használjuk, akár többször is, némelyiket nem
        int random[] = MAGIC_ARRAY;
        for (const int &i : random)
        {
            ak47s[i]->shoot();
        }

        for (int i = 0; i < ak47s.size(); ++i)
        {
            delete ak47s[i];
        }

        ak47s.clear();
    }
    

    //*///

    //getchar(); // TODO remove me

}