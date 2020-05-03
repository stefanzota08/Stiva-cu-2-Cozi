#include <iostream>
#include <vector>
using namespace std;

class Pereche
{
    int x;
    int y;
public:
    Pereche(int x = 0, int y = 0)
    {
        this->x = x;
        this->y = y;
    }
    ~Pereche()
    {

    }

    int getX()
    {
        return x;
    }

    int getY()
    {
        return this->y;
    }

    void afis()
    {
        cout<<x<<" "<<y<<endl;
    }

    friend ostream& operator<<(ostream& afisare, Pereche& pereche)
    {
        afisare<<pereche.x<<" "<<pereche.y;
    }



};

class Multime_Pereche
{
private:
    int n;
    int index;
protected:
    Pereche v[101];
public:
    Multime_Pereche()
    {
        n = 0;
    }
    ~Multime_Pereche()
    {

    }

    int getN()
    {
        return n;
    }

    void setN(int val)
    {
        n = val;
    }

    virtual void afisare()
    {
        if(!isEmpty())
        {
            for(int i = 0; i<n; i++)
                {
                    v[i].afis();
                }
        }
        else cout<<"Stiva este goala :)"<<endl;

    }

    virtual void push(int a, int b)
    {
        Pereche per(a,b);
        v[n] = per;
        n++;
    }

    virtual void pop(int k)
    {
        for(int i=k ; i<n ; i++)
        {
            v[i] = v[i+1];
        }
        n--;
    }

    bool isEmpty()
    {
        if(n == 0)
            return true;
        return false;
    }
    bool isFull()
    {
        if(n == 101)
            return true;
        return false;
    }

    friend ostream& operator<<(ostream& afisare, Multime_Pereche& pereche)
    {
            if(!pereche.isEmpty())
            {
                for(int i = 0; i<pereche.n; i++)
                    {
                        afisare<<pereche.v[i]<<endl;
                    }
            }
            else afisare<<"Stiva este goala :)";
        return afisare;
    }

};

class Stiva_Pereche : public Multime_Pereche
{
public:
    Stiva_Pereche()
    {

    }
    ~Stiva_Pereche()
    {

    }
    void push(int a, int b)
    {
        if(!isFull())
        {
            Pereche per(a,b);
            v[getN()] = per;
            setN(getN()+1);
        }
        else cout<<"Nu se poate efectua *push* --> Stiva este plina!";
    }
    void pop()
    {
        if(!isEmpty())
        {
            cout<<"Se afiseaza pop: ";
            v[getN()-1].afis();
            cout<<endl;
            v[getN()-1] = NULL;
            setN(getN()-1);
        }
        else cout<<"Nu se poate efectua *pop* --> Stiva este goala";

    }
    void showTop()
    {
        v[getN()-1].afis();
    }
    void afisare()
    {
        if(!isEmpty())
        {
            for(int i = getN()-1; i>=0; i--)
                {
                    v[i].afis();
                }
        }
        else cout<<"Stiva este goala :)"<<endl;
    }

    friend ostream& operator<<(ostream& afisare, Stiva_Pereche& stiva)
    {
        for(int i = stiva.getN()-1; i>=0; i--)
        {
            afisare<<stiva.v[i]<<endl;
        }
    }
};

class Coada_Pereche : public Multime_Pereche
{
  public:
    Coada_Pereche()
    {

    }
    ~Coada_Pereche()
    {

    }
    void push(int a, int b)
    {
        if(!isFull())
        {
            Pereche per(a,b);
            v[getN()] = per;
            setN(getN()+1);
        }
        else cout<<"Nu se poate efectua *push* --> Coada este plina!";
    }
    void pop()
    {
        if(!isEmpty())
        {
            cout<<"Se afiseaza pop: ";
            v[0].afis();
            cout<<endl;
            for(int i=0 ; i<getN() ; i++)
            {
                v[i] = v[i+1];
            }
            setN(getN()-1);
        }
        else cout<<"Nu se poate efectua *pop* --> Coada este goala";

    }
    void showRear()
    {
        v[getN()-1].afis();
    }
    void showFront()
    {
        v[1].afis();
    }
};



int main()
{
    Coada_Pereche coada;
    Stiva_Pereche stiva;
    stiva.push(1,2);
    coada.push(1,2);
    stiva.push(2,3);
    coada.push(2,3);
    stiva.push(3,4);
    coada.push(3,4);
    stiva.afisare();
    cout<<endl;
    coada.afisare();
    cout<<endl;
    stiva.pop();
    coada.pop();
    cout<<stiva;
    cout<<endl;
    cout<<coada;
    cout<<endl;
    Stiva_Pereche stivacopy(stiva);
    cout<<stivacopy;
    return 0;
}
