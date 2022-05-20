#include <iostream>
#include <vector>
#include <string>
using namespace std;

class IOInterface
{
public:
    virtual istream& citire(istream& is) = 0;
    virtual ostream& afisare(ostream& os) const = 0;
};

class Comanda: public IOInterface
{
protected:
    static int idx;
    int id;
    string nume;
    string adresa;
    double pret;
    int timp;
    vector<string> produse;
    vector<int> cantitate;
public:
    const string &getNume() const;

    void setNume(const string &nume);

public:
    Comanda();
    Comanda(string nume, string adresa, double pret, int timp, vector<string>produse, vector<int>cantitate);
    Comanda(const Comanda& c);
    Comanda& operator= (const Comanda& c);

    friend istream& operator >> (istream&is, Comanda& c);
    friend ostream& operator << (ostream&os, const Comanda& c);


    virtual ostream& afisare(ostream& os) const
    {
        os << "Nume client: "<<this->nume<<endl;
        os << "Adresa client: "<<this->adresa<<endl;
        os << "Pret comanda: "<<this->pret<<endl;
        os << "Timp livrare: "<<this->timp<<endl;
        for(int i = 0; i < produse.size(); i++)
            os << "Produsul: "<<this->produse[i]<<", in cantitate de: "<<this->cantitate[i]<<endl;
        return os;
    }

    virtual istream& citire(istream& is)
    {
        cout << "Introduceti nume client: "<<endl;
        is>> this->nume;
        cout << "Introduceti adresa client: "<<endl;
        is >>this->adresa;
        cout << "Intrdocueti pretul comenzii: "<<endl;
        is >> this->pret;
        cout << "Introduceti timpul de livrare: "<<endl;
        is >> this->timp;
        cout << "Introduceti numarul de produse: "<<endl;
        int nr;
        is >> nr;
        for(int i = 0; i < nr; i++) {
            cout << "Introduceti produsul: "<<endl;
            string prod;
            int cant;
            is >> prod;
            produse.push_back(prod);
            cout << "Introduceti cantitatea: "<<endl;
            is >> cant;
            cantitate.push_back(cant);
        }

        return is;
    }

    double getPret() const;

    void setPret(double pret);

    const vector<string> &getProduse() const;

    void setProduse(const vector<string> &produse);

    const string &getAdresa() const;

    void setAdresa(const string &adresa);

    int getTimp() const;

    void setTimp(int timp);

    const vector<int> &getCantitate() const;

    void setCantitate(const vector<int> &cantitate);

    int getId() const;

    void setId(int id);
};

int Comanda::idx = 0;
Comanda::Comanda() {
    ++idx;
    this->id = idx;
    this->nume = this->adresa = "";
    this->pret = this->timp = 0;
    this->produse = {};
    this->cantitate = {};
}

Comanda::Comanda(string nume, string adresa, double pret, int timp, vector<string> produse, vector<int> cantitate) {
    this->adresa = adresa;
    this->nume = nume;
    this->pret = pret;
    this->timp = timp;
    this->produse = produse;
    this->cantitate = cantitate;
    ++idx;
    this->id = idx;
}

Comanda::Comanda(const Comanda &c) {
    this->nume = c.nume;
    this->adresa = c.adresa;
    this->pret = c.pret;
    this->timp = c.timp;
    this->produse = c.produse;
    this->cantitate = c.cantitate;
    this->id = c.id;
}

Comanda& Comanda::operator=(const Comanda &c) {
    if(this != &c)
    {
        this->nume = c.nume;
        this->adresa = c.adresa;
        this->pret = c.pret;
        this->timp = c.timp;
        this->produse = c.produse;
        this->cantitate = c.cantitate;
        this->id = c.id;
    }
    return *this;

}


istream& operator >> (istream&is, Comanda& c)
{
    return c.citire(is);
}
ostream& operator << (ostream&os, const Comanda& c)
{
    return c.afisare(os);
}

int Comanda::getId() const {
    return id;
}

void Comanda::setId(int id) {
    Comanda::id = id;
}

const vector<int> &Comanda::getCantitate() const {
    return cantitate;
}

void Comanda::setCantitate(const vector<int> &cantitate) {
    Comanda::cantitate = cantitate;
}

int Comanda::getTimp() const {
    return timp;
}

void Comanda::setTimp(int timp) {
    Comanda::timp = timp;
}

const string &Comanda::getAdresa() const {
    return adresa;
}

void Comanda::setAdresa(const string &adresa) {
    Comanda::adresa = adresa;
}

const vector<string> &Comanda::getProduse() const {
    return produse;
}

void Comanda::setProduse(const vector<string> &produse) {
    Comanda::produse = produse;
}

double Comanda::getPret() const {
    return pret;
}

void Comanda::setPret(double pret) {
    Comanda::pret = pret;
}

const string &Comanda::getNume() const {
    return nume;
}

void Comanda::setNume(const string &nume) {
    Comanda::nume = nume;
}


class ComandaMancare: virtual public Comanda
{
protected:
    string numeLocal;
public:
    ComandaMancare();
    ComandaMancare(string nume, string adresa, double pret, int timp, vector<string>produse, vector<int>cantitate, string local);
    ComandaMancare(const ComandaMancare& c);
    ComandaMancare& operator= (const ComandaMancare& c);

    virtual ostream& afisare(ostream& os) const
    {
        Comanda::afisare(os);
        os << "Nume local: "<<this->numeLocal<<endl;
        return os;
    }

    const string &getNumeLocal() const;

    void setNumeLocal(const string &numeLocal);

    virtual istream& citire(istream& is)
    {
        Comanda::citire(is);
        cout << "Introduceti numele localului: "<<endl;
        is>> this->numeLocal;

        return is;
    }
};

ComandaMancare::ComandaMancare():Comanda() {
    this->numeLocal = "";
}

ComandaMancare::ComandaMancare(string nume, string adresa, double pret, int timp, vector<string> produse,
                               vector<int> cantitate, string local):Comanda(nume, adresa, pret, timp, produse, cantitate) {
    this->numeLocal = local;
}

ComandaMancare::ComandaMancare(const ComandaMancare &c):Comanda(c) {
    this->numeLocal = c.numeLocal;
}

ComandaMancare& ComandaMancare::operator=(const ComandaMancare &c) {
    if(this != &c)
    {
        Comanda::operator=(c);
        this->numeLocal = c.numeLocal;
    }

    return *this;
}

const string &ComandaMancare::getNumeLocal() const {
    return numeLocal;
}

void ComandaMancare::setNumeLocal(const string &numeLocal) {
    ComandaMancare::numeLocal = numeLocal;
}

class ComandaFastFood: virtual public ComandaMancare
{
    int discount;
public:
    ComandaFastFood();
    ComandaFastFood(string nume, string adresa, double pret, int timp, vector<string>produse, vector<int>cantitate, string local, int disc);
    ComandaFastFood(const ComandaFastFood& c);
    ComandaFastFood& operator= (const ComandaFastFood& c);

    virtual ostream& afisare(ostream& os) const
    {
        ComandaMancare::afisare(os);
        os << "Discount: "<<this->discount<<"%"<<endl;
        return os;
    }

    virtual istream& citire(istream& is)
    {
        ComandaMancare::citire(is);
        cout << "Introduceti discountul: "<<endl;
        is>> this->discount;

        return is;
    }

    int getDiscount() const;
    void setDiscount(int discount);
};

ComandaFastFood::ComandaFastFood():ComandaMancare(), Comanda() {
    this->discount = 0;
}

ComandaFastFood::ComandaFastFood(string nume, string adresa, double pret, int timp, vector<string> produse,
                                 vector<int> cantitate, string local, int disc):ComandaMancare(nume, adresa, pret, timp, produse, cantitate, local), Comanda(nume, adresa, pret, timp, produse, cantitate) {
    this->discount = disc;
}

ComandaFastFood::ComandaFastFood(const ComandaFastFood &c):ComandaMancare(c), Comanda(c) {
    this->discount = c.discount;
}

int ComandaFastFood::getDiscount() const {
    return discount;
}

void ComandaFastFood::setDiscount(int discount) {
    ComandaFastFood::discount = discount;
}

ComandaFastFood& ComandaFastFood::operator=(const ComandaFastFood &c) {
    if(this != &c)
    {
        ComandaMancare::operator=(c);
        this->discount = c.discount;
    }
    return *this;
}

class ComandaRestaurant: virtual public ComandaMancare
{
    bool tacamuri;
public:
    ComandaRestaurant();
    ComandaRestaurant(string nume, string adresa, double pret, int timp, vector<string>produse, vector<int>cantitate, string local, bool tacam);
    ComandaRestaurant(const ComandaRestaurant& c);
    ComandaRestaurant& operator= (const ComandaRestaurant& c);

    virtual ostream& afisare(ostream& os) const
    {
        ComandaMancare::afisare(os);
        if(tacamuri)
            os << "Tacamurile sunt incluse"<<endl;
        else os << "Nu sunt incluse tacamuri"<<endl;
        return os;
    }

    virtual istream& citire(istream& is)
    {
        ComandaMancare::citire(is);
        cout << "Doriti tacamuri? [1/0] "<<endl;
        is>> this->tacamuri;

        return is;
    }

    bool isTacamuri() const;

    void setTacamuri(bool tacamuri);
};

ComandaRestaurant::ComandaRestaurant():ComandaMancare(), Comanda() {
    this->tacamuri = false;
}

ComandaRestaurant::ComandaRestaurant(string nume, string adresa, double pret, int timp, vector<string> produse,
                                 vector<int> cantitate, string local, bool tacam):ComandaMancare(nume, adresa, pret, timp, produse, cantitate, local), Comanda(nume, adresa, pret, timp, produse, cantitate) {
    this->tacamuri = tacam;
}

ComandaRestaurant::ComandaRestaurant(const ComandaRestaurant &c):ComandaMancare(c), Comanda(c) {
    this->tacamuri = c.tacamuri;
}

ComandaRestaurant& ComandaRestaurant::operator=(const ComandaRestaurant &c) {
    if(this != &c)
    {
        ComandaMancare::operator=(c);
        this->tacamuri = c.tacamuri;
    }
    return *this;
}

bool ComandaRestaurant::isTacamuri() const {
    return tacamuri;
}

void ComandaRestaurant::setTacamuri(bool tacamuri) {
    ComandaRestaurant::tacamuri = tacamuri;
}

class ComandaMedicamente: virtual public Comanda
{
    vector<bool>antibiotic;
public:
    ComandaMedicamente();
    ComandaMedicamente(string nume, string adresa, double pret, int timp, vector<string>produse, vector<int>cantitate, vector<bool>antib);
    ComandaMedicamente(const ComandaMedicamente& c);
    ComandaMedicamente& operator= (const ComandaMedicamente& c);

    virtual ostream& afisare(ostream& os) const
    {
        Comanda::afisare(os);
        for(int i = 0; i < antibiotic.size(); i++) {
            if(antibiotic[i] == 0)
                os << "Medicamentul nu e antibiotic"<<endl;
            else os << "Medicamentul e antibiotic"<<endl;
        }
        return os;
    }

    const vector<bool> &getAntibiotic() const;
    void setAntibiotic(const vector<bool> &antibiotic);

    virtual istream& citire(istream& is)
    {
        Comanda::citire(is);
        for(int i = 0; i < this->produse.size(); i++) {
            cout << "Introduceti daca medicamentul introdus anterior e antibiotic sau nu[1/0]: " << endl;
            bool var;
            is >> var;
            antibiotic.push_back(var);
        }

        return is;
    }
};

ComandaMedicamente::ComandaMedicamente():Comanda() {
    this->antibiotic = {};
}

ComandaMedicamente::ComandaMedicamente(string nume, string adresa, double pret, int timp, vector<string> produse,
                               vector<int> cantitate, vector<bool>antib):Comanda(nume, adresa, pret, timp, produse, cantitate) {
    this->antibiotic = antib;
}

ComandaMedicamente::ComandaMedicamente(const ComandaMedicamente &c):Comanda(c) {
    this->antibiotic = c.antibiotic;
}

ComandaMedicamente& ComandaMedicamente::operator=(const ComandaMedicamente &c) {
    if(this != &c)
    {
        Comanda::operator=(c);
        this->antibiotic = c.antibiotic;
    }

    return *this;
}

const vector<bool> &ComandaMedicamente::getAntibiotic() const {
    return antibiotic;
}

void ComandaMedicamente::setAntibiotic(const vector<bool> &antibiotic) {
    ComandaMedicamente::antibiotic = antibiotic;
}

class ComandaTigara: virtual public Comanda
{
    bool clasice;
    bool rezerva;
public:
    ComandaTigara();
    ComandaTigara(string nume, string adresa, double pret, int timp, vector<string>produse, vector<int>cantitate, bool clasic, bool rez);
    ComandaTigara(const ComandaTigara& c);
    ComandaTigara& operator= (const ComandaTigara& c);

    virtual ostream& afisare(ostream& os) const
    {
        Comanda::afisare(os);
        if(clasice == 0) os << "Tigarile sunt rezerve de tutun"<<endl;
        else if(clasice == 1) os << "Tigarile sunt clasice"<<endl;
        return os;
    }

    bool isClasice() const;
    void setClasice(bool clasice);

    virtual istream& citire(istream& is)
    {
        Comanda::citire(is);
        cout << "Precizati daca tigarile sunt clasice[1/0] sau nu"<<endl;
        is >> this->clasice;
        if(!this->clasice) this->rezerva = true;

        return is;
    }

    bool isRezerva() const;
    void setRezerva(bool rezerva);
};

ComandaTigara::ComandaTigara():Comanda() {
    this->clasice = this->rezerva = false;
}

ComandaTigara::ComandaTigara(string nume, string adresa, double pret, int timp, vector<string> produse,
                                       vector<int> cantitate, bool clasic, bool rez):Comanda(nume, adresa, pret, timp, produse, cantitate) {
    this->clasice = clasic;
    this->rezerva = rez;
}

bool ComandaTigara::isRezerva() const {
    return rezerva;
}

void ComandaTigara::setRezerva(bool rezerva) {
    ComandaTigara::rezerva = rezerva;
}

ComandaTigara::ComandaTigara(const ComandaTigara &c):Comanda(c) {
    this->clasice = c.clasice;
    this->rezerva = c.rezerva;
}

ComandaTigara& ComandaTigara::operator=(const ComandaTigara &c) {
    if(this != &c)
    {
        Comanda::operator=(c);
        this->clasice = c.clasice;
        this->rezerva = c.rezerva;
    }

    return *this;
}

bool ComandaTigara::isClasice() const {
    return clasice;
}

void ComandaTigara::setClasice(bool clasice) {
    ComandaTigara::clasice = clasice;
}

class Meniu {

    static Meniu *instance;
    Meniu() {}
    Meniu(const Meniu &m) = delete;
    Meniu(Meniu &&m) = delete;
    Meniu &operator=(const Meniu &m) = delete;
    Meniu &operator=(Meniu &&m) = delete;

    vector<Comanda*> comenzi;

public:
    ~Meniu();
    static Meniu *getInstance() {
        if (!instance)
            instance = new Meniu();

        return instance;
    }

    static void cleanInstance() {
        if(instance)
            delete instance;
    }

    void citire();
    void adaugare();
    void afisare();
    void stergereID();
    void cautaID();
    void cautaNume();

};

void Meniu::citire() {
    cout << "Introduceti nr de comenzi pe care le cititi"<<endl;
    int n;
    cin >> n;
    for(int i =0; i <n; i++)
    {
        cout << "Introduceti tipul de comanda: 1 - FastFood, 2-Restaurant, 3-Medicamente, 4-Tigari"<<endl;
        int opt;
        cin >> opt;
        Comanda* c = nullptr;
        if(opt == 1)
        {
            c = new ComandaFastFood();
        }
        else if(opt == 2) c = new ComandaRestaurant();
        else if (opt == 3) c= new ComandaMedicamente();
        else if(opt == 4) c = new ComandaTigara();
        if(c)
        {
            cout << "Introduceti datele comenzii: "<<endl;
            cin >> *c;
            comenzi.push_back(c);
        }
    }
}

void Meniu::adaugare() {
    cout << "Introduceti tipul de comanda pe care o adaugati: 1 - FastFood, 2-Restaurant, 3-Medicamente, 4-Tigari"<<endl;
    int opt;
    cin >> opt;
    Comanda* c = nullptr;
    if(opt == 1)
    {
        c = new ComandaFastFood();
    }
    else if(opt == 2) c = new ComandaRestaurant();
    else if (opt == 3) c= new ComandaMedicamente();
    else if(opt == 4) c = new ComandaTigara();
    if(c)
    {
        cout << "Introduceti datele comenzii: "<<endl;
        cin >> *c;
        comenzi.push_back(c);
    }
}

void Meniu::afisare() {
    for(int  i = 0; i < comenzi.size(); i++)
    {
        cout << "DATELE COMENZII: "<<endl;
        cout << *comenzi[i]<<endl;
    }
}

void Meniu::stergereID() {
    cout << "Introduceti ID-ul comenzii pe care doriti sa o stergeti"<<endl;
    int id,i;
    cin>> id;
    for (i = 0; i < comenzi.size(); i++)
    {
        if(comenzi[i]->getId() == id) {
            //delete comenzi[i];
            cout << "Comanda a fost stearsa cu succes" << endl;
            break;
        }
    }
    if(i == comenzi.size()) cout << "Nu s-a gasit nicio comanda cu id-ul introdus"<<endl;
}

void Meniu::cautaID() {
    cout << "Introduceti ID-ul comenzii pe care doriti sa o gasiti"<<endl;
    int id,i;
    cin>> id;
    for (i = 0; i < comenzi.size(); i++)
    {
        if(comenzi[i]->getId() == id) {
            cout << "DATELE COMENZII: "<<endl;
            cout <<*comenzi[i]<< endl;
            break;
        }
    }
    if(i == comenzi.size()) cout << "Nu s-a gasit nicio comanda cu id-ul introdus"<<endl;
}

void Meniu::cautaNume() {
    cout << "Introduceti numele clientului a carui comanda doriti sa gasiti"<<endl;
    int i;
    string nume;
    cin>> nume;
    for (i = 0; i < comenzi.size(); i++)
    {
        if(comenzi[i]->getNume() == nume) {
            cout << "DATELE COMENZII CLIENTULUI : "<<endl;
            cout <<*comenzi[i]<< endl;
            break;
        }
    }
    if(i == comenzi.size()) cout << "Nu s-a gasit nicio comanda pentru numele introdus"<<endl;
}

Meniu::~Meniu()
{
    for(int i = 0; i < comenzi.size(); i++)
        delete comenzi[i];
    comenzi.clear();
}

Meniu* Meniu::instance = nullptr;


void optiuniMeniu()
{
    cout << "1. Citire n comenzi"<<endl;
    cout << "2. Adauga comanda noua"<<endl;
    cout << "3. Afiseaza comenzi"<<endl;
    cout << "4.Sterge comanda dupa id"<<endl;
    cout << "5.Cauta comanda dupa id"<<endl;
    cout << "6.Cauta comanda dupa numele clientului"<<endl;
}

int main()
{
    Meniu* m = Meniu::getInstance();

    while(1)
    {
        try{
            optiuniMeniu();
            int nrOpt;
            cin >> nrOpt;
            if(nrOpt < 1 || nrOpt > 11)
                throw string("Optiune introdusa gresit");
            else {
                if (nrOpt == 1) {m->citire(); }
                else if (nrOpt == 2) { m->adaugare(); }
                else if (nrOpt == 3) { m->afisare(); }
                else if (nrOpt == 4) {m->stergereID(); }
                else if (nrOpt == 5) {m->cautaID();}
                else if(nrOpt == 6){
                    m -> cautaNume();
                }
                else if (nrOpt == 11) break;
            }
        }
        catch(string s){cout << s << endl;}
    }

    m->cleanInstance();
    return 0;
}


