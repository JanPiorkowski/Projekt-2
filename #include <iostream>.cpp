#include <iostream>
#include <cstdlib>
#include <time.h>
#include <queue>
#include <stack>
#include <thread>

struct zmienne;
char losuj();
void cele(char A[][5]);
void nowy_rzad(char A[][5],int tor);
void wypiszkolej(std::queue <char> wagony);
void sprawdz(char A[][5],int tor,char wagon,int B[],int &pkt, std::stack<char>(&Tory)[]);
void jedzie(int r2,int r3,int r4,int r5,int &ntor,char A[][5], int &pkt, int B[], std::queue <char>& wagony,std::stack<char>(&Tory)[]);
void rysuj (int r2,int r3,int r4,int r5, int pkt, char A[][5], std::queue<char>wagony,std::stack<char>Tory[]);
void start(int B[], char A[][5], std::queue < char >&wagony);
void gra();

main()
{   
        gra();

    return 0;
}

struct zmienne
{
    int r2=0,r3=0,r4=0,r5=0,tor,B[5],pkt=0;;
    char A[5][5];
    std::queue < char > wagony;
    std::stack<char>Tory[5];
};

char losuj(){
    int liczba;

    liczba= rand()%4;
    switch (liczba){
    case(0):
        return 'A';
    break;
    case(1):
        return 'B';
    break;
    case(2):
        return 'C';
    break;
    case(3):
        return 'D';
    break;
    }
    return 'A';
}

void cele(char A[][5])
{
    int k;
    for (int j=0;j<5;j++)
    {
        k=rand()%2+3;
        for (int i=0;i<k;i++)
            A[j][i]=losuj();
        if (k<4)
            A[j][3]='w';
    }
    for (int j=0;j<5;j++)
    {
      A[j][4]='w';
    }
}

void nowy_rzad(char A[][5],int tor)
{
        int k;
                k=rand()%2+3;
                for (int i=0;i<k;i++)
                    A[tor][i]=losuj();
                if (k<4)
                    A[tor][3]='w';
}

void wypiszkolej(std::queue <char> wagony)
{
    char pomoc;
    std::cout<<std::endl;
    while(!wagony.empty())
    {
        for(int i=0; i<wagony.size()-1; i++)
        {
        pomoc=wagony.front();
        wagony.pop();
        wagony.push(pomoc);
        }
        std::cout<<wagony.front();
        wagony.pop();
    }
}

void sprawdz(zmienne &Z, char wagon)
    {
        if (Z.A[Z.tor][Z.B[Z.tor]]==wagon)
            {std::cout<<"Dobrze"<<std::endl;
            
            if(Z.A[Z.tor][Z.B[Z.tor]+1]=='w')
            {
                Z.pkt++;
                nowy_rzad(Z.A,Z.tor);
                while(!Z.Tory[Z.tor].empty())
                {
                    Z.Tory[Z.tor].pop();
                }
                Z.B[Z.tor]=0;
            }
            else
              Z.B[Z.tor]++;
            }

        else
            {std::cout<<"Zle"<<std::endl;
            nowy_rzad(Z.A,Z.tor);
            while(!Z.Tory[Z.tor].empty())
                {
                    Z.Tory[Z.tor].pop();
                }
            Z.B[Z.tor]=0;
            Z.pkt--;
            }
    }


void jedzie(zmienne &Z)
{

    if(Z.r2==0){
        Z.tor=0;
        }
     else if (Z.r3==0){
        Z.tor=1;
        }
     else if (Z.r4==0){
        Z.tor=2;
        }
     else if (Z.r5==0){
        Z.tor=3;
        }
     else{
        Z.tor=4;
        }
    Z.Tory[Z.tor].push(Z.wagony.front());
    Z.wagony.pop();
    Z.wagony.push(losuj());
    sprawdz(Z,Z.Tory[Z.tor].top());
}

void rysuj (zmienne Z)
{
    int r=1,h=0;
    wypiszkolej(Z.wagony);
    std::cout<<" ";

    for (int i = 0; i <38-(Z.Tory[0].size()); i++)
        std::cout<<"=";
    for(int i=4;i>=0;i--)
        if(Z.A[r-1][i]!='w'&&h<Z.Tory[0].size()&&i<Z.Tory[0].size()){
            std::cout<<Z.A[r-1][i];
            h++;
        }
    h=0;
    std::cout<<" Tor "<<r<<": [";
    for(int i=4;i>=0;i--)
        if(Z.A[r-1][i]!='w')
            std::cout<<Z.A[r-1][i];
        std::cout<<"]\n";

    for (int i = 0; i < 20; i++)
        std::cout<<" ";
    if(Z.r2==1)
        std::cout<<"\\\\ (2)\n";
    else
        std::cout<<"   (2)\n";    
    for (int i = 0; i < 21; i++)
        std::cout<<" ";


    std::cout<<"\\\\";
    for (int i = 0; i < 23-(Z.Tory[1].size()); i++)
        std::cout<<"=";
    r++;
    for(int i=4;i>=0;i--)
        if(Z.A[r-1][i]!='w'&&h<Z.Tory[1].size()&&i<Z.Tory[1].size()){
            std::cout<<Z.A[r-1][i];
            h++;
        }
    h=0;
    std::cout<<" Tor "<<r<<": [";
    for(int i=4;i>=0;i--)
        if(Z.A[r-1][i]!='w')
            std::cout<<Z.A[r-1][i];
        std::cout<<"]\n";
    for (int i = 0; i < 22; i++)
        std::cout<<" ";
    if(Z.r3==1)
        std::cout<<"\\\\ (3)\n";
    else
        std::cout<<"   (3)\n";    
    for (int i = 0; i < 23; i++)
        std::cout<<" ";
    std::cout<<"\\\\";
    for (int i = 0; i < 21-(Z.Tory[2].size()); i++)
        std::cout<<"=";
    r++;
    for(int i=4;i>=0;i--)
        if(Z.A[r-1][i]!='w'&&h<Z.Tory[2].size()&&i<Z.Tory[2].size()){
            std::cout<<Z.A[r-1][i];
            h++;
        }
    h=0;
    std::cout<<" Tor "<<r<<": [";
    for(int i=4;i>=0;i--)
        if(Z.A[r-1][i]!='w')
            std::cout<<Z.A[r-1][i];
        std::cout<<"]\n";

    for (int i = 0; i < 24; i++)
        std::cout<<" ";
    if(Z.r4==1)
        std::cout<<"\\\\ (4)\n";
    else
        std::cout<<"   (4)\n";    
    for (int i = 0; i < 25; i++)
        std::cout<<" ";
    std::cout<<"\\\\";
    for (int i = 0; i < 19-(Z.Tory[3].size()); i++)
        std::cout<<"=";
    r++;
    for(int i=4;i>=0;i--)
        if(Z.A[r-1][i]!='w'&&h<Z.Tory[3].size()&&i<Z.Tory[3].size()){
            std::cout<<Z.A[r-1][i];
            h++;
        }
    h=0;
    std::cout<<" Tor "<<r<<": [";
    for(int i=4;i>=0;i--)
        if(Z.A[r-1][i]!='w')
            std::cout<<Z.A[r-1][i];
        std::cout<<"]\n";

    for (int i = 0; i < 26; i++)
        std::cout<<" ";
    if(Z.r5==1)
        std::cout<<"\\\\ (5)\n";
    else
        std::cout<<"   (5)\n";    
    for (int i = 0; i < 27; i++)
        std::cout<<" ";
    std::cout<<"\\\\";
    for (int i = 0; i < 17-(Z.Tory[4].size()); i++)
        std::cout<<"=";
    r++;
    for(int i=4;i>=0;i--)
        if(Z.A[r-1][i]!='w'&&h<Z.Tory[4].size()&&i<Z.Tory[4].size()){
            std::cout<<Z.A[r-1][i];
            h++;
        }
    h=0;
    std::cout<<" Tor "<<r<<": [";
    for(int i=4;i>=0;i--)
        if(Z.A[r-1][i]!='w')
            std::cout<<Z.A[r-1][i];
        std::cout<<"]\n\n\n";
        std::cout<<"Liczba punktow: "<<10*Z.pkt<<std::endl;

}
void start(int B[], char A[][5], std::queue < char >&wagony)
{
    for(int i=0;i<5;i++)
    {
        B[i]=0;
    }
    srand(time(NULL));
    cele(A);
    for (int i = 0; i < 7; i++)
    {
        wagony.push(losuj());
    }
}

void gra()
{   
    char z;
    zmienne Z;
    std::thread s1(start, Z.B, Z.A, std::ref(Z.wagony));

    s1.join();

    while (z!='0')
    {
        
        rysuj(Z);
        std::cin>>z;
        switch (z)
        {
        case('2'):
            if (Z.r2==0)
                Z.r2=1;
            else
                Z.r2=0;
        break;
        case('3'):
            if (Z.r3==0)
                Z.r3=1;
            else
                Z.r3=0;
        break;
        case('4'):
            if (Z.r4==0)
                Z.r4=1;
            else
                Z.r4=0;
        break;
        case('5'):
            if (Z.r5==0)
                Z.r5=1;
            else
                Z.r5=0;
            break;
        case('w'):
            jedzie(Z);
        break;
        default:
            std::cout<<"Nieprawidlowa komenda\n";
        break;
        }

        if (Z.pkt<0)
        {
            std::cout<<"PRZEGRALES"<<std::endl;
            rysuj(Z);
            //system("Pause");
             Z.pkt=0;
            cele(Z.A);
        } 
        if (Z.pkt>=5)
        {
            std::cout<<"WYGRALES"<<std::endl;
            rysuj(Z);
            //system("Pause");
            Z.pkt=0;
            cele(Z.A);
        }
    }
}