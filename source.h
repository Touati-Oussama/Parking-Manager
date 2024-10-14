#include<iostream>
#include<string>
#include<vector>
#include<map>
#include <fstream>
#include<list>
using namespace std;

class Date{
public:
    int heure ,jour, mois, annee;
public:
    Date(){};
    Date(int, int, int, int);
    ~Date(){};
    friend ostream& operator<<(ostream& out, const Date& D);
    friend istream& operator>>(istream& in, Date& D);
    friend ostream& operator<<(ostream& out, Date* D);
    friend istream& operator>>(istream& in, Date* D);
    bool operator>(Date&);
    bool operator<(const Date& d) const{
        if (annee < d.annee) {
            return true;
        } else if (annee > d.annee) {
            return false;
        } else if (mois < d.mois) {
            return true;
        } else if (mois > d.mois) {
            return false;
        } else {
            return jour < d.jour;
        }
    }
    bool operator-(const Date& d) const{
        if ((annee - d.annee) < 0) {
            return true;
        } else if ((annee > d.annee)> 0) {
            return false;
        } else if ((mois < d.mois) < 0) {
            return true;
        } else if ((mois > d.mois)> 0) {
            return false;
        } else {
            if ((jour < d.jour) < 0){
                return true;
            }
            else
                return false;
        }
    }
    Date& operator=(const Date& D);
    int getAnnee()const;
    int getMois()const;
    int getJour()const;
};

class Ticket{
private:
    static inline int nb_Ticket = 0;
    int id;
    int matricule_voiture;
    Date *date_entree;
    Date *date_sortie;
    float montant;
    bool etat_paiement;
public:
    Ticket(): matricule_voiture(0), date_entree(nullptr), date_sortie(nullptr), montant(0.0), etat_paiement(false){ Ticket::nb_Ticket += 1; this->id = Ticket::nb_Ticket;};
    Ticket(int, Date*, Date*);
    Ticket(const Ticket&);
    ~Ticket();
    void calcul_montant(float);
    void Payer();
    bool getEtat();
    friend ostream& operator<<(ostream& out, const Ticket& T);
    friend istream& operator>>(istream& in, Ticket& T);
    friend ostream& operator<<(ostream& out, const Ticket* T);
    friend istream& operator>>(istream& in, Ticket* T);
    Ticket& operator=(const Ticket& T);
    float getMontant();
    Date getDateSortie();
    void setMontant(float remise);
    void setMatricule(int);
    bool operator==(Ticket);
    bool operator<(Ticket);
};


class Vehicule
{
protected:
    static int nb_vehicules;
    int matricule;
    string marque;
    Ticket* ticket;
public:
    Vehicule():matricule(0), marque(""), ticket(nullptr){nb_vehicules++;};
    Vehicule(int, string);
    Vehicule(const Vehicule&);
    virtual ~Vehicule();
    void affecter_ticket(Ticket* ticket);
    void retirer_ticket();
    friend ostream& operator<<(ostream& out, const Vehicule& V);
    friend istream& operator>>(istream& in, Vehicule& V);
    friend ostream& operator<<(ostream& out, const Vehicule* V);
    friend istream& operator>>(istream& in, Vehicule* V);
    Vehicule& operator=(const Vehicule& V);
    Ticket& getTicket();
    int getMat();
    string getMarque(){return this->marque;};
};

template<class T>
class Liste
{
private:
    list<T> ListeElements;
public:
    Liste<T>(){};
    Liste<T>(const Liste<T>&);
    ~Liste<T>();
    template<class U>
    friend ostream& operator<<(ostream& out, Liste<U>& L);
    template<class U>
    friend istream& operator>>(istream& in, Liste<U>& L);
    Liste& operator=(const Liste& L);
    void ajouter(T);
    void supprimer(T);
    void enregistrer_fichier();
    void lire_fichier();
};
template<class T>
Liste<T>::Liste(const Liste<T>& L){
    for (auto itr = L.ListeElements.begin(); itr != L.ListeElements.end(); itr++)
        this->ListeElements.push_back(*itr);
}
template<class T>
Liste<T>::~Liste(){
    if(this->ListeElements.size()!=0) this->ListeElements.clear();
}
template<class T>
ostream& operator<<(ostream& out, Liste<T>& L){
    out<<"----------- La liste ------------"<<endl;
    for(auto itr = L.ListeElements.begin(); itr != L.ListeElements.end(); itr++) {
            out<<*itr;
            out<<"------------------------"<<endl;
        }
    return out;
}
template<class T>
istream& operator>>(istream& in, Liste<T>& L){
    char rep;
    do
    {
        T e;;
        in>>e;
        L.ListeElements.push_back(e);
        cout<<"Ajouter une autre element ? (O/N)";
        cin>> rep ;
    } while(rep=='o'|| rep =='O') ;
    return in ;
}
template<class T>
Liste<T>& Liste<T>::operator=(const Liste<T>& L){
    if(this != &L)
    {
        if(this->ListeElements.size()!=0) this->ListeElements.clear();
        for(auto itr = L.ListeElements.begin(); itr != L.ListeElements.end(); itr++)
            this->ListeElements.push_back(*itr);
    }
    return *this;
}
template<class T>
void Liste<T>::ajouter(T e){
    this->ListeElements.push_back(e);
    cout << "Element ajoute a la liste"<< endl;
}
template<class T>
void Liste<T>::supprimer(T e){
    auto foundIterator = find(ListeElements.begin(), ListeElements.end(), e);
    if (foundIterator != ListeElements.end()) {
        ListeElements.erase(foundIterator);
        cout << "Element supprime de la liste"<< endl;
    } else {
        cout << "Element n'existe pas dans la liste!"<< endl;
    }
}
template<class T>
void Liste<T>::enregistrer_fichier(){
    ofstream fo("Tickets.txt");
    if(!fo)
    {
        cout<<"\n erreur fichier tickets";
        return;
    }
    ListeElements.sort();
    for (auto itr = ListeElements.begin(); itr != ListeElements.end(); itr++)
        fo<<&(*itr);
    fo.close();
}
template<class T>
void Liste<T>::lire_fichier(){
    ifstream fi("Tickets.txt");
    if(!fi)
    {
        cout<<"\n erreur fichier tickets";
        return;
    }
    T *t;
    while(fi>>t)
    {
        ListeElements.push_back(*t);
    }
    fi.close();
}

class Voiture: public Vehicule
{
private:
    int puissance;
    int nb_cylindres;
    int nb_portes;

public:
    Voiture():Vehicule(),puissance(0),nb_cylindres(0),nb_portes(0){};
    Voiture(int, string, int, int, int);
    Voiture(const Voiture&);
    ~Voiture(){};
    friend ostream& operator<<(ostream& out, Voiture& V);
    friend istream& operator>>(istream& in, Voiture& V);
    friend ostream& operator<<(ostream& out, Voiture* V);
    friend istream& operator>>(istream& in, Voiture* V);
    friend istream& operator>(istream& in, Voiture* V);
    Voiture& operator=(const Voiture& V);
    int getPuissance(){return this->puissance;};
    int getCylindres(){ return this->nb_cylindres;};
    int getPortes(){return this->nb_portes;};
};
class Moto: public Vehicule
{
protected:;
    int nb_roues;
public:
    Moto():Vehicule(),nb_roues(0){};
    Moto(int, string, int);
    Moto(const Moto&);
    virtual ~Moto()=0;
    friend ostream& operator<<(ostream& out, Moto& M);
    friend istream& operator>>(istream& in, Moto& M);
    friend ostream& operator<<(ostream& out, Moto* M);
    friend istream& operator>>(istream& in, Moto* M);
    Moto& operator=(const Moto& M);
    void setRoues(int n){ this->nb_roues = n;};
    int getRoues();
};
class Moto_classique: public Moto
{
public:
    Moto_classique():Moto(){};
    Moto_classique(int, string, int);
    Moto_classique(const Moto_classique&);
    ~Moto_classique(){};
    friend ostream& operator<<(ostream& out, Moto_classique& M);
    friend istream& operator>>(istream& in, Moto_classique& M);
    friend ostream& operator<<(ostream& out, Moto_classique* M);
    friend istream& operator>>(istream& in, Moto_classique* M);
    friend istream& operator>(istream& in, Moto_classique* M);
    Moto_classique& operator=(const Moto_classique& M);
};
class Moto_lourd: public Moto
{
public:
    Moto_lourd():Moto(){};
    Moto_lourd(int, string, int);
    Moto_lourd(const Moto_lourd&);
    ~Moto_lourd(){};
    friend ostream& operator<<(ostream& out, Moto_lourd& M);
    friend istream& operator>>(istream& in, Moto_lourd& M);
    friend ostream& operator<<(ostream& out, Moto_lourd* M);
    friend istream& operator>>(istream& in, Moto_lourd* M);
    friend istream& operator>(istream& in, Moto_lourd* M);
    Moto_lourd& operator=(const Moto_lourd& M);
};


class ListePrix
{
private:
    float prix_voiture, prix_moto_classique, prix_moto_lourd;
public:
    ListePrix():prix_voiture(0.0),prix_moto_classique(0.0),prix_moto_lourd(0.0){};
    ListePrix(float, float, float);
    ~ListePrix(){};
    friend ostream& operator<<(ostream& out, ListePrix& L);
    friend istream& operator>>(istream& in, ListePrix& L);
    friend ostream& operator<<(ostream& out, ListePrix* L);
    friend istream& operator>>(istream& in, ListePrix* L);
    ListePrix& operator=(const ListePrix& L);
    float getPrix_voiture();
    float getPrix_moto_classique();
    float getPrix_moto_lourd();
};

class Capacite
{
private:
    int nb_max_voitures, nb_max_motos;
public:
    Capacite():nb_max_motos(0),nb_max_voitures(0){};
    Capacite(int, int);
    ~Capacite(){};
    friend ostream& operator<<(ostream& out, Capacite& C);
    friend istream& operator>>(istream& in, Capacite& C);
    friend ostream& operator<<(ostream& out, Capacite* C);
    friend istream& operator>>(istream& in, Capacite* C);
    Capacite& operator=(const Capacite& C);
    int getNb_max_motos();
    int getNb_max_voitures();
};

class Parking
{
private:
    int id;
    string designation;
    string localisation;
    Capacite* capacite;
    int nb_paiements;
    multimap<Date, float> paiements;
    int nb_voitures;
    int nb_motos;
    ListePrix* liste_prix;
    vector<Vehicule*> vehicules;
public:
    Parking();
    Parking(int, string, string, Capacite*, ListePrix*);
    Parking(Parking&);
    ~Parking();
    void ajouter_vehicule(Vehicule* V, Liste<Ticket>& L);
    int chercher_vehicule(int matricule);
    void liberer_place(int pos);
    void liberer_place(Vehicule* V);
    void calcul_nb_places_libres(int* v, int* m);
    float calcul_chiffre_affaires(int);
    float calcul_chiffre_affaires(int, int);
    float calcul_chiffre_affaires(int, int, int);
    friend ostream& operator<<(ostream& out, Parking& P);
    friend istream& operator>>(istream& in, Parking& P);
    Parking& operator=(const Parking& P);
    void enregister_fichier();
    void lire_fichier();
};

class Personne
{
protected:

    int id;
    string nom;
    string prenom;
    Vehicule* vehicule;
public:
    static inline vector <Personne*> personnes;
    Personne(){};
    Personne(string, string, Vehicule*);
    Personne(const Personne&);
    virtual ~Personne();
    int chercher_Vehicule(Parking);
    virtual float calcul_montant() = 0;
    void payer_ticket();
    static inline int nb_Client = 0;
    static inline int nb_Passager = 0;
    friend ostream& operator<<(ostream& out, Personne& P);
    friend istream& operator>>(istream& in, Personne& P);
    friend ostream& operator<<(ostream& out,const Personne* P);
    friend istream& operator>>(istream& in, Personne* P);
    Personne& operator=(const Personne& P);
    Vehicule* getVehicule(){return this->vehicule;};
    int getId(){ return this->id;};
    string gettNom()const{ return this->nom;};
    string getPre(){ return this->prenom;};
    void setId(int id){ this->id = id;};
    void setNom(string nom){ this->nom = nom;};
    void setPre(string prenom){ this->prenom = prenom;};
    void setVehicule(Vehicule* v){ this->vehicule = v;};
};

class Passager: public Personne
{
public:
    Passager();
    Passager( string, string, Vehicule*);
    Passager(const Passager&);
    ~Passager();
    float calcul_montant();
    friend ostream& operator<<(ostream& out, Passager& P);
    friend istream& operator>>(istream& in, Passager& P);
    Passager& operator=(const Passager& P);
};

class Abonnement
{
private:
    int id;
    Date date_deb;
    Date date_exp;
    float remise;
public:
    static inline int nb = 0;
    Abonnement(){Abonnement::nb++;this->id = nb;};
    Abonnement(Date,Date,float);
    ~Abonnement(){};
    friend ostream& operator<<(ostream& out, Abonnement& A);
    friend istream& operator>>(istream& in, Abonnement& A);
    friend ostream& operator<<(ostream& out, Abonnement* A);
    friend istream& operator>>(istream& in, Abonnement* A);
    void afficher();
    Abonnement& operator=(const Abonnement& A);
    bool operator<(Abonnement);
    bool operator-(Abonnement);
    float getRemise();
    int getId(){return this->id;};
    void setId(int id){ this->id = id;};
    Date getDateDeb()const{ return date_deb;};
};

class Client: public Personne
{
private:
    Abonnement* abonnement;
public:
    Client();
    Client(string, string, Vehicule*, Abonnement*);
    Client(const Client&);
    ~Client();
    float calcul_montant();
    friend ostream& operator<<(ostream& out, Client& C);
    friend istream& operator>>(istream& in, Client& C);
    friend ostream& operator<<(ostream& out,const Client* C);
    friend istream& operator>>(istream& in, Client* C);
    Client& operator=(const Client& C);
    Abonnement* getAbon(){ return this->abonnement;};
    void setAb(Abonnement *A){ this->abonnement = A;};
};

class Gestion_Parking
{
    public:
        Parking* parking;
        vector<Personne*>personnes;
        map<int,Abonnement>abonnements;
        list<Vehicule*>liste_vehicules;
        static inline  int nb_abonnements = 0;
        static inline  int nb_clients = 0;
        static inline  int nb_passagers = 0;

    public:
        Gestion_Parking(){};
        Gestion_Parking(Parking*);
        Gestion_Parking(const Gestion_Parking&);
        ~Gestion_Parking();
        Gestion_Parking& operator=(const Gestion_Parking& P);
        void ajouterPersonne(Personne* p);
        Personne* rechercherPersonne(int);
        void supprimerPersonne(Personne*);
        friend ostream& operator<<(ostream& out, Gestion_Parking& L);
        friend istream& operator>>(istream& in, Gestion_Parking& L);
        void enregistrer_fichier();
        void lire_fichier();
        void Initialiser();
        void enregistrer_fichier_perso(Personne *P);
        void enregistrer_fichier_abon(Abonnement *A);
        void lire_fichier_Abonne();
        void afficher_abonnements();
        void ajouter_abonnement(Abonnement *A);
        Abonnement* chercher_abonnement(int id);
        void enregistrer_fichier_list(Vehicule *V);
        void lire_fichier_Vehicule();
        void afficher_vehicules();
        void ajouter_vehicule(Vehicule *V);
        Vehicule* chercher_Vehicule(int id);
        Personne* chercher_personne(string,string);
};

