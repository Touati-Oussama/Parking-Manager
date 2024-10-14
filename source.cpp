#include<iostream>
#include<string>
#include<vector>
#include<map>
#include "source.h"
#include<fstream>
#include <algorithm>

/*********************************************************** Date ***************************************************************************/
Date::Date(int annee,int mois, int jour, int heure){
    this->annee = annee;
    this->mois = mois;
    this->jour = jour;
    this->heure = heure;
}
ostream& operator<<(ostream& out, const Date& D){
    out<<"Le date est: " <<D.jour <<"/"<<D.mois<<"/"<<D.annee<< " " <<D.heure<<"H. "<<endl;
    return out;
}
istream& operator>>(istream& in, Date& D){
    cout<<"Donnez La date AA/MM/JJ HH: "<<endl;
    in>>D.annee;
    in>>D.mois;
    in>>D.jour;
    in>>D.heure;
    in.ignore();
    return in;
}
bool Date::operator>(Date& d){
    if (this->annee > d.annee)
        return true;
    else if (this->annee < d.annee) {
        return false;
    }
    else {
        if (this->mois > d.mois)
            return true;
        else if (this->mois < d.mois)
            return false;
        else {
            if (this->jour > d.jour)
                return true;
            else if (this->jour < d.jour)
                return false;
            else {
                if (this->heure >= d.heure)
                    return true;
                else
                    return false;
            }
        }
    }
}
ostream& operator<<(ostream& out, Date* D){
    out<<D->heure<<" "<<D->jour <<" "<<D->mois<<" "<<D->annee<<" ";
    return out;
}
istream& operator>>(istream& in, Date* D){
    in>>D->heure>>D->jour>>D->mois>>D->annee;
    return in;
}
int Date::getAnnee()const{return this->annee;}
int Date::getMois()const{return this->mois;}
int Date::getJour()const{return this->jour;}
Date& Date::operator=(const Date& D){
    this->annee = D.annee;
    this->mois = D.mois;
    this->jour = D.jour;
    this->heure = D.heure;
    return *this;
}


/*********************************************************** Ticket ***************************************************************************/
Ticket::Ticket(int matricule_voiture, Date* date_entree, Date* date_sortie){
    try {
            if (*date_sortie-*date_entree == 0){
                //throw std::invalid_argument("Erreur!! Au niveau de ticket La date de sortie doit etre superieure a la date d entree! ");
            }
            Ticket::nb_Ticket += 1;
            this->id = Ticket::nb_Ticket;
            this->matricule_voiture = matricule_voiture;
            this->montant = 0;
            this->etat_paiement = false;
            this->date_entree = new Date(*date_entree);
            this->date_sortie = new Date(*date_sortie);
    }
    catch (std::invalid_argument& e) {
        std::cerr << e.what() << std::endl;
    }
}
Ticket::Ticket(const Ticket& ticket){
    this->id = ticket.id;
    this->matricule_voiture = ticket.matricule_voiture;
    Date *de = new Date(*ticket.date_entree);
    Date *ds = new Date(*ticket.date_sortie);
    this->date_entree = de;
    this->date_sortie = ds;
    this->montant = ticket.montant;
    this->etat_paiement = ticket.etat_paiement;
}
Ticket::~Ticket(){
    delete this->date_entree;
    this->date_entree=nullptr;
    delete this->date_sortie;
    this->date_sortie=nullptr;
}
void Ticket::calcul_montant(float prix){
    int nbHeures = *this->date_sortie - *this->date_entree;
    this->montant = nbHeures * prix;
}
void Ticket::Payer(){
    this->etat_paiement = true;
}
bool Ticket::getEtat(){
    return this->etat_paiement;
}
ostream& operator<<(ostream& out, const Ticket& T){
    out<<"L'id de ticket: "<<T.id<<endl;
    out<<"La matricule de vehicule: "<<T.matricule_voiture<<endl;
    out<<"Date d entree: "<<*T.date_entree;
    out<<"Date de sortie: "<<*T.date_sortie;
    out<<"Le montant a payer est: "<<T.montant<<"DT."<<endl;
    if (T.etat_paiement)
        out<<"L etat de paiement est: Paye!"<<endl;
    else
        out<<"L etat de paiement est: Non Paye!"<<endl;
    return out;
}
istream& operator>>(istream& in, Ticket& T){
    try {
                T.date_entree = new Date();
                cout<<"Saisir date d entree: "<<endl;
                in>>*T.date_entree;
                T.date_sortie = new Date();
                cout<<"Saisir date de sortie: "<<endl;
                in>>*T.date_sortie;
            if (*T.date_sortie-*T.date_entree == 0){
                throw std::invalid_argument("Erreur!! Au niveau de ticket La date de sortie doit etre superieure a la date d entree! ");
            }
             return in;
    }
    catch (std::invalid_argument& e) {
        std::cerr << e.what() << std::endl;
    }
}
ostream& operator<<(ostream& out, const Ticket* T){
    out<<T->id<<" "<<T->matricule_voiture<<" "<<T->date_entree<<T->date_sortie<<T->montant<<" "<<T->etat_paiement<<" ";
    return out;
}
istream& operator>>(istream& in, Ticket* T){
    /*in>>T->id>>T->matricule_voiture>>T->date_entree>>T->date_sortie>>T->montant>>T->etat_paiement;
    return in;*/
    T->date_entree = new Date();
    T->date_sortie = new Date();
    in>>T->id>>T->matricule_voiture>>T->date_entree>>T->date_sortie>>T->montant>>T->etat_paiement;
    return in;
}
Ticket& Ticket::operator=(const Ticket& T){
    if (this != &T){
        delete T.date_entree;
        delete T.date_sortie;
        this->id = T.id;
        this->matricule_voiture = T.matricule_voiture;
        this->date_entree = new Date(*T.date_entree);
        this->date_sortie = new Date(*T.date_sortie);
        this->montant = T.montant;
        this->etat_paiement = T.etat_paiement;
    }
    return *this;
}
float Ticket::getMontant(){ return this->montant; };
Date Ticket::getDateSortie(){return *(this->date_sortie);};
void Ticket::setMontant(float remise){
    this->montant -= (montant * remise)/100;
}
void Ticket::setMatricule(int matricule){
    this->matricule_voiture = matricule;
}
bool Ticket::operator==(Ticket T){
    if(this->id == T.id)
        return true;
    else return false;
}
bool Ticket::operator<(Ticket T){
    if(*this->date_entree<*T.date_entree)
        return true;
    else return false;
}

/*********************************************************** Vehicule ***************************************************************************/
int Vehicule::nb_vehicules = 0;
Vehicule::Vehicule(int matricule, string marque){
    this->nb_vehicules++;
    this->matricule = matricule;
    this->marque = marque;
    if(this->ticket!=nullptr)
        this->ticket = nullptr;
}
Vehicule::Vehicule(const Vehicule&v){
    this->nb_vehicules++;
    this->matricule = v.matricule;
    this->marque = v.marque;
    if(v.ticket!=nullptr)
        this->ticket = new Ticket(*v.ticket);
    else
        this->ticket = nullptr;

}
Vehicule::~Vehicule(){
    if(this->ticket!=nullptr)
    {
        delete this->ticket;
        this->ticket=nullptr;
    }
    this->nb_vehicules--;
}
void Vehicule::affecter_ticket(Ticket* ticket){
    this->ticket = ticket;
}
void Vehicule::retirer_ticket(){
    delete this->ticket;
    this->ticket = nullptr;

}
ostream& operator<<(ostream& out,  const Vehicule& V){
    out<<"------ Caracteristiques de Vehicule: ------"<<endl;
    out<<"Matricule de vehicule: "<<V.matricule<<endl;
    out<<"Marque de vehicule: "<<V.marque<<endl;
    if(V.ticket!=nullptr){
        out<<"------ Caracteristiques de Ticket: ------"<<endl;
        out<<"Ticket: "<<*V.ticket<<endl;
    }
}
istream& operator>>(istream& in, Vehicule& V){
    if(V.ticket!=nullptr)
    {
        delete V.ticket;
        V.ticket = nullptr;
    }
    cout<<"Saisir la matricule: "<<endl;
    in>>V.matricule;
    cout<<"Saisir la marque: "<<endl;
    in>>V.marque;
    return in;
}
ostream& operator<<(ostream& out,  const Vehicule* V){
    out<<V->matricule<<" "<<V->marque<<" "<<V->ticket;
    return out;
}
istream& operator>>(istream& in, Vehicule* V){

    /*if(V->ticket!=nullptr)
    {
        delete V->ticket;
        V->ticket = nullptr;
    }
    V->ticket = new Ticket();
    in>>V->matricule>>V->marque>>V->ticket;
    return in;*/

    V->ticket = new Ticket();
    in>>V->matricule>>V->marque>>V->ticket;
    return in;
}
Vehicule& Vehicule::operator=(const Vehicule& V){
    if (this != &V)
        {
            this->matricule = V.matricule;
            this->marque = V.marque;
            if (this->ticket != nullptr)
                delete this->ticket;
            if (V.ticket != nullptr)
                this->ticket = new Ticket(*V.ticket);
            else
                this->ticket = nullptr;
        }
        return *this;
};
Ticket& Vehicule::getTicket(){
    return *this->ticket;
}
int Vehicule::getMat(){
    return this->matricule;
}

/*********************************************************** Voiture ***************************************************************************/
Voiture::Voiture(int matricule, string marque, int puissance, int nb_cylindres, int nb_portes):Vehicule(matricule, marque){
    this->puissance=puissance;
    this->nb_cylindres=nb_cylindres;
    this->nb_portes=nb_portes;
}
Voiture::Voiture(const Voiture& V):Vehicule(V){
    this->puissance=V.puissance;
    this->nb_cylindres=V.nb_cylindres;
    this->nb_portes=V.nb_portes;
}
ostream& operator<<(ostream& out, Voiture& V){
    /*out<<"-------------------------------- Voiture: ----------------"<<endl<<"La matricule est: "<<V.matricule<<endl<<"La marque est: "<<V.marque<<endl;
    out<<"Nombre de cylindres: "<<V.nb_cylindres<<endl;
    out<<"Puissance: "<<V.puissance<<endl;
    out<<"Nombre de portes: "<<V.nb_portes<<endl;
    if(V.ticket!=nullptr)
        out<<*V.ticket<<endl;
    return out;*/
    out<<"-------------------------------- Voiture: ----------------"<<endl<<"La matricule est: "<<V.matricule<<endl<<"La marque est: "<<V.marque<<endl;
    out<<"Nombre de cylindres: "<<V.nb_cylindres<<endl;
    out<<"Puissance: "<<V.puissance<<"CV"<<endl;
    out<<"Nombre de portes: "<<V.nb_portes<<endl;
    if(V.ticket!=nullptr)
        out<<*V.ticket<<endl;
    return out;
}
istream& operator>>(istream& in, Voiture& V){
    in>>static_cast<Vehicule&>(V);
    cout<<"Saisir le nombre de cylindres: "<<endl;
    in>>V.nb_cylindres;
    cout<<"Saisir la puissance: "<<endl;
    in>>V.puissance;
    cout<<"Saisir le nombre de portes: "<<endl;
    in>>V.nb_portes;
    /*cout<<"--- Saisir Ticket -- "<<endl;
    V.ticket = new Ticket();
    V.ticket->setMatricule(V.matricule);
    in>>*V.ticket;*/
    return in;
}
ostream& operator<<(ostream& out, Voiture* V){
   out<<V->matricule<<" "<<V->marque<<" "<<V->puissance<<" "<<V->nb_cylindres<<" "<<V->nb_portes<<" ";
   if (V->ticket != nullptr)
    out<<V->ticket;
   return out;
}
istream& operator>>(istream& in, Voiture* V){
    V->ticket = new Ticket();
    in>>V->matricule>>V->marque>>V->puissance>>V->nb_cylindres>>V->nb_portes>>V->ticket;
}
ostream& operator<(ostream& out, Voiture* V){
   out<<V->getMat()<<" "<<V->getMarque()<<" "<<V->getPuissance()<<" "<<V->getCylindres()<<" "<<V->getPortes()<<" ";
   return out;
}
istream& operator>(istream& in, Voiture* V){
    in>>V->matricule>>V->marque>>V->puissance>>V->nb_cylindres>>V->nb_portes;
}
Voiture& Voiture::operator=(const Voiture& V){
    if(this!=&V)
    {
        Vehicule::operator=(V);
        this->nb_cylindres=V.nb_cylindres;
        this->puissance=V.puissance;
        this->nb_portes=V.nb_portes;
    }
    return *this;
}


/*********************************************************** Moto ***************************************************************************/
Moto::Moto(int matricule, string marque, int nb_roues):Vehicule(matricule, marque){
    this->nb_roues=nb_roues;
}
Moto::Moto(const Moto& M):Vehicule(M){
    this->nb_roues=nb_roues;
}
Moto::~Moto(){
    if(this->ticket!=nullptr)
    {
        delete this->ticket;
        this->ticket=nullptr;
    }
    this->nb_vehicules--;
}
ostream& operator<<(ostream& out, Moto& M){
    out<<"--------------------Moto: ----------------------"<<endl<<"La matricule est: "<<M.matricule<<endl<<"La marque est: "<<M.marque<<endl;
    out<<"Le nombre de roues est: "<<M.nb_roues<<endl;
    if(M.ticket!=nullptr)
        out<<*M.ticket<<endl;
    return out;
}
istream& operator>>(istream& in, Moto& M){
    in>>static_cast<Vehicule&>(M);
    cout<<"Saisir le nombre de roues: "<<endl;
    in>>M.nb_roues;
    /*cout<<"--- Saisir Ticket -- "<<endl;
    M.ticket = new Ticket();
    M.ticket->setMatricule(M.matricule);
    in>>*M.ticket;*/
    return in;
}
ostream& operator<<(ostream& out, Moto* M){
    out<<M->matricule<<" "<<M->marque<<" "<<M->nb_roues<<" "<<M->ticket;
    return out;
}
istream& operator>>(istream& in, Moto* M){
    M->ticket = new Ticket();
    in>>M->matricule>>M->marque>>M->nb_roues>>M->ticket;
    return in;
}
Moto& Moto::operator=(const Moto& M){
    if(this!=&M)
    {
        Vehicule::operator=(M);
        this->nb_roues=M.nb_roues;
    }
    return *this;
}
int Moto::getRoues(){
    return this->nb_roues;
}

/*********************************************************** Moto_classqiue ***************************************************************************/
Moto_classique::Moto_classique(int matricule, string marque, int nb_roues):Moto(matricule, marque, nb_roues){}
Moto_classique::Moto_classique(const Moto_classique& M):Moto(M){}
ostream& operator<<(ostream& out, Moto_classique& M){
    out<<"--------------------------- Moto:(classique) --------------------"<<endl<<"La matricule est: "<<M.matricule<<endl<<"La marque est: "<<M.marque<<endl;
    out<<"Le nombre de roues est: "<<M.nb_roues<<endl;
    if(M.ticket!=nullptr)
        out<<*M.ticket<<endl;
    return out;
}
istream& operator>>(istream& in, Moto_classique& M){
    in>>static_cast<Moto&>(M);
    return in;
}
ostream& operator<<(ostream& out, Moto_classique* M){
    out<<M->matricule<<" "<<M->marque<<" "<<M->nb_roues<<" ";
    if (M->ticket != nullptr)
        out<<M->ticket;
    return out;
}
ostream& operator<(ostream& out, Moto_classique* M){
    out<<M->getMat()<<" "<<M->getMarque()<<" "<<M->getRoues()<<" ";
    return out;
}
istream& operator>>(istream& in, Moto_classique* M){
    M->ticket = new Ticket();
    in>>M->matricule>>M->marque>>M->nb_roues>>M->ticket;
    return in;
}
istream& operator>(istream& in, Moto_classique* M){
    in>>M->matricule>>M->marque>>M->nb_roues;
    return in;
}
Moto_classique& Moto_classique::operator=(const Moto_classique& M){
    if(this!=&M)
    {
        Moto::operator=(M);
    }
    return *this;
}


/*********************************************************** Moto_lourd ***************************************************************************/
Moto_lourd::Moto_lourd(int matricule, string marque, int nb_roues):Moto(matricule, marque, nb_roues){}
Moto_lourd::Moto_lourd(const Moto_lourd& M):Moto(M){}
ostream& operator<<(ostream& out, Moto_lourd& M){
    out<<"-------------------------Moto:(lourde) ----------------------"<<endl<<"La matricule est: "<<M.matricule<<endl<<"La marque est: "<<M.marque<<endl;
    out<<"Le nombre de roues est: "<<M.nb_roues<<endl;
    if(M.ticket!=nullptr)
        out<<*M.ticket<<endl;
    return out;
}
istream& operator>>(istream& in, Moto_lourd& M){
    in>>static_cast<Moto&>(M);
    return in;
}
ostream& operator<<(ostream& out, Moto_lourd* M){
    out<<M->matricule<<" "<<M->marque<<" "<<M->nb_roues<<" ";
    if (M->ticket != nullptr)
        out<<M->ticket;
    return out;
}
ostream& operator<(ostream& out, Moto_lourd* M){
    out<<M->getMat()<<" "<<M->getMarque()<<" "<<M->getRoues()<<" ";
    return out;
}
istream& operator>>(istream& in, Moto_lourd* M){
    M->ticket = new Ticket();
    in>>M->matricule>>M->marque>>M->nb_roues>>M->ticket;
    return in;
}
istream& operator>(istream& in, Moto_lourd* M){
    in>>M->matricule>>M->marque>>M->nb_roues;
    return in;
}
Moto_lourd& Moto_lourd::operator=(const Moto_lourd& M){
    if(this!=&M)
    {
        Moto::operator=(M);
    }
    return *this;
}


/*********************************************************** Personne ***************************************************************************/
Personne::Personne( string nom , string prenom , Vehicule* v){
    //this->id = id;
    this->nom = nom;
    this->prenom = prenom;
    this->vehicule = v;
}
Personne::Personne(const Personne& p){
    this->id = p.id;
    this->nom = p.nom;
    this->prenom = p.prenom;
    this->vehicule = new Vehicule(*p.vehicule);
}
Personne::~Personne(){
    delete this->vehicule;
    this->vehicule = nullptr;
};
void Personne::payer_ticket(){
    this->vehicule->getTicket().Payer();
    if (this->vehicule->getTicket().getEtat())
        cout<<"----------- Paiement effectuee ! ---------------"<<endl;
    else
        cout<<"----------- Paiement Non effectuee ! ---------------"<<endl;
}
ostream& operator<<(ostream& out, Personne& P){
    out<<"------------ Caracteristiques de Personne -----------"<<endl;
    out<<"L id de personne est: "<<P.id<<endl;
    out<<"Le nom de personne est: "<<P.nom<<endl;
    out<<"Le prenom de personne est: "<<P.prenom<<endl;
    out<<"------------ Cordonnees de sa vehicule:"<<endl;
    if(typeid(*P.vehicule)==typeid(Voiture))
        out<<static_cast<Voiture&>(*P.vehicule);
    else if(typeid(*P.vehicule)==typeid(Moto_classique))
        out<<static_cast<Moto_classique&>(*P.vehicule);
    else if(typeid(*P.vehicule)==typeid(Moto_lourd))
        out<<static_cast<Moto_lourd&>(*P.vehicule);
    return out;
}
istream& operator>>(istream& in, Personne& P){
    cout<<"------------ Cordonnees de Personne -----------"<<endl;
    cout<<"Donnez l'id de personne: "<<endl;
    in>>P.id;
    cout<<"Donnez le nom de personne: "<<endl;
    in>>P.nom;
    cout<<"Donnez le prenom de personne: "<<endl;
    in>>P.prenom;
    P.vehicule = new Vehicule();
    int choix;
    cout<<"------------ Cordonnees de Vehicule: "<<endl;
    cout<<"Choisir le type de votre vehicule: "<<endl;
    cout<<"Pour saisir une voiture choisir 1"<<endl;
    cout<<"Pour saisir une moto classique choisir 2"<<endl;
    cout<<"Pour saisir une moto lourde choisir 3"<<endl;
    cin>>choix;
    if(choix==1)
    {
        Voiture* v = new Voiture();
        in>>*v;
        P.vehicule = v;
    }
    else if(choix==2)
    {
        Moto_classique* m = new Moto_classique();
        in>>*m;
        P.vehicule = m;
    }
    else if(choix==3)
    {
        Moto_lourd* m = new Moto_lourd();
        in>>*m;
        P.vehicule = m;
    }
    return in;
}
ostream& operator<<(ostream& out,const Personne* P){
    out<<P->id<<" "<<P->nom<<" "<<P->prenom;
    if(typeid(*P->vehicule)==typeid(Voiture))
        out<<" "<<static_cast<Voiture&>(*P->vehicule);
    else if(typeid(*P->vehicule)==typeid(Moto_classique))
        out<<" "<<static_cast<Moto_classique&>(*P->vehicule);
    else if(typeid(*P->vehicule)==typeid(Moto_lourd))
        out<<" "<<static_cast<Moto_lourd&>(*P->vehicule);
    return out;
}
istream& operator>>(istream& in, Personne* P){
    in>>P->id>>P->nom>>P->prenom;
    /*P->vehicule = new Vehicule();
    int choix;
    cout<<"------------ Cordonnees de Vehicule: "<<endl;
    cout<<"Choisir le type de votre vehicule: "<<endl;
    cout<<"Pour saisir une voiture choisir 1"<<endl;
    cout<<"Pour saisir une moto classique choisir 2"<<endl;
    cout<<"Pour saisir une moto lourde choisir 3"<<endl;
    cin>>choix;
    if(choix==1)
    {
        Voiture* v = new Voiture();
        in>>*v;
        P->vehicule = v;
    }
    else if(choix==2)
    {
        Moto_classique* m = new Moto_classique();
        in>>*m;
        P->vehicule = m;
    }
    else if(choix==3)
    {
        Moto_lourd* m = new Moto_lourd();
        in>>*m;
        P->vehicule = m;
    }*/
    return in;
}
Personne& Personne::operator=(const Personne& P){
    if (this != &P){
        if(this->vehicule != nullptr)
        {
            delete this->vehicule;
            this->vehicule = nullptr;
        }
        this->id = P.id;
        this->nom = P.nom;
        this->prenom = P.prenom;
        if(P.vehicule != nullptr)
        {
            if(typeid(*P.vehicule) == typeid(Voiture))
                this->vehicule = new Voiture(static_cast<const Voiture&>(*P.vehicule));
            else if(typeid(*P.vehicule) == typeid(Moto_classique))
                this->vehicule = new Moto_classique(static_cast<const Moto_classique&>(*P.vehicule));
            else if(typeid(*P.vehicule) == typeid(Moto_lourd))
                this->vehicule = new Moto_lourd(static_cast<const Moto_lourd&>(*P.vehicule));
        }
    }
    return *this;
}
float Personne::calcul_montant(){
    return this->vehicule->getTicket().getMontant();
}
int Personne::chercher_Vehicule(Parking P){

    try {
            int x = P.chercher_vehicule(this->vehicule->getMat());
            if (x == -1){
                throw std::invalid_argument("Ce matricule n'existe pas!");
            }
            else
                return x;
    } catch (std::invalid_argument& e) {
        std::cerr << e.what() << std::endl;
        return -1;
    }

}

/*********************************************************** Passager ***************************************************************************/
Passager::Passager(){
    Personne::nb_Passager += 1;
    this->id = Personne::nb_Passager;
}
Passager::Passager(string nom, string prenom, Vehicule* v): Personne(nom,prenom,v){
    Personne::nb_Passager += 1;
    this->id = Personne::nb_Passager;
    Personne::personnes.push_back(this);
};
Passager::~Passager(){
    delete this->vehicule;
    this->vehicule = nullptr;
    Personne::nb_Passager--;
}
float Passager::calcul_montant(){
    return this->vehicule->getTicket().getMontant();
}
Passager::Passager(const Passager& P): Personne(P){};
ostream& operator<<(ostream& out, Passager& P){
    out<<"------------ Caracteristiques de Passager -----------"<<endl;
    out<<"L id de passager est: "<<P.id<<endl;
    out<<"Le nom de passager est: "<<P.nom<<endl;
    out<<"Le prenom de passager est: "<<P.prenom<<endl;
    out<<"------------ Cordonnees de vehicule:"<<endl;
    if(typeid(*P.vehicule)==typeid(Voiture))
        out<<static_cast<Voiture&>(*P.vehicule);
    else if(typeid(*P.vehicule)==typeid(Moto_classique))
        out<<static_cast<Moto_classique&>(*P.vehicule);
    else if(typeid(*P.vehicule)==typeid(Moto_lourd))
        out<<static_cast<Moto_lourd&>(*P.vehicule);
    else out<<"rien";
    return out;
}
istream& operator>>(istream& in, Passager& P){
    cout<<"------------ Cordonnees de Passager -----------"<<endl;
    /*cout<<"Donnez l'id de passager: "<<endl;
    in>>P.id;*/
    cout<<"Donnez le nom de passager: "<<endl;
    in>>P.nom;
    cout<<"Donnez le prenom de passager: "<<endl;
    in>>P.prenom;
    P.vehicule = new Vehicule();
    int choix;
    cout<<"------------ Cordonnees de Vehicule: "<<endl;
    cout<<"Choisir le type de votre vehicule: "<<endl;
    cout<<"Pour saisir une voiture choisir 1"<<endl;
    cout<<"Pour saisir une moto classique choisir 2"<<endl;
    cout<<"Pour saisir une moto lourde choisir 3"<<endl;
    cin>>choix;
    if(choix==1)
    {
        Voiture* v = new Voiture();
        in>>*v;
        P.vehicule = v;
    }
    else if(choix==2)
    {
        Moto_classique* m = new Moto_classique();
        in>>*m;
        P.vehicule = m;
    }
    else if(choix==3)
    {
        Moto_lourd* m = new Moto_lourd();
        in>>*m;
        P.vehicule = m;
    }
    return in;
}
Passager& Passager::operator=(const Passager& P){
    Personne::operator=(P);
}

/*********************************************************** Abonnement ***************************************************************************/
Abonnement::Abonnement(Date dd,Date de,float remise){
    try{
        if (de-dd <= 24)
                //throw std::invalid_argument("Erreur!! Au niveau d abonnement La date d expiration doit etre superieure a la date de debut! ");
        this->date_deb = dd;
        this->date_exp = de;
        this->remise = remise;
        Abonnement::nb++;
        this->id = nb;
    }
        catch (std::invalid_argument& e) {
        std::cerr << e.what() << std::endl;
    }
}
ostream& operator<<(ostream& out, Abonnement& A){
    out<<"L id de l abonnement est: "<<A.id<<endl;
    out<<"La date de debut est: "<<A.date_deb.annee<<"/"<<A.date_deb.mois<<"/"<<A.date_deb.jour<<endl;
    out<<"La date d expiration est: "<<A.date_exp.annee<<"/"<<A.date_exp.mois<<"/"<<A.date_exp.jour<<endl;
    out<<"Le remise est: "<<A.remise<<"%."<<endl;
    out<<"--------------------------------------"<<endl;
    return out;
}
void Abonnement::afficher(){

    cout<<"L id de l abonnement est: "<<id<<endl;
    cout<<"La date de debut est: "<<date_deb.annee<<"/"<<date_deb.mois<<"/"<<date_deb.jour<<endl;
    cout<<"La date d expiration est: "<<date_exp.annee<<"/"<<date_exp.mois<<"/"<<date_exp.jour<<endl;
    cout<<"Le remise est: "<<remise<<"%."<<endl;
    cout<<"-------------------------------------------------"<<endl;
}
istream& operator>>(istream& in, Abonnement& A){
    try {
                cout<<"Donnez La date de debut d abonnement: "<<endl;
                in>>A.date_deb;
                cout<<"Donnez La date d expiration d abonnement: "<<endl;
                in>>A.date_exp;
                if (A.date_exp-A.date_deb <= 24){
                    throw std::invalid_argument("Erreur!! Au niveau d abonnement La date d expiration doit etre superieure a la date de debut! ");
                }
    }
    catch (std::invalid_argument& e) {
        std::cerr << e.what() << std::endl;
    }
    cout<<"Donnez la pourcentage de remise: "<<endl;
    in>>A.remise;
    return in;

}
ostream& operator<<(ostream& out, Abonnement* A){
        out<<A->id<<" "<<A->date_deb.annee<<" "<<A->date_deb.mois<<" "<<A->date_deb.jour<<" "<<A->date_deb.heure<<" "<<A->date_exp.annee<<" "<<A->date_exp.mois<<" "<<A->date_exp.jour<<" "<<A->date_exp.heure<<" "<< A->remise;
    return out;
}
istream& operator>>(istream& in, Abonnement* A){
    //in>>A->id>>A->date_deb>>A->date_exp>>A->remise;
    in>>A->id>>A->date_deb.annee>>A->date_deb.mois>>A->date_deb.jour>>A->date_deb.heure>>A->date_exp.annee>>A->date_exp.mois>>A->date_exp.jour>>A->date_exp.heure>>A->remise;
    return in;
}
Abonnement& Abonnement::operator=(const Abonnement& A){
    if(this != &A){
        this->date_deb = A.date_deb;
        this->date_exp =  A.date_exp;
        this->remise = A.remise;
    }
}
float Abonnement::getRemise(){ return this->remise;};
bool Abonnement::operator<(Abonnement A){
    if(this->date_deb<A.date_deb)
        return true;
    else return false;
}

bool Abonnement::operator-(Abonnement A){
    return this->date_deb-A.date_deb;
}
/*********************************************************** Client ***************************************************************************/
Client::Client(){
    Personne::nb_Client += 1;
    this->id = Personne::nb_Client;
}
Client::Client(string nom, string prenom, Vehicule* v, Abonnement* a): Personne(nom,prenom,v){
    this->abonnement = a;
    Personne::nb_Client += 1;
    this->id = Personne::nb_Client;
    Personne::personnes.push_back(this);
}
Client::Client(const Client& client) : Personne(client){
    this->abonnement = new Abonnement(*client.abonnement);
}
Client::~Client(){
    delete this->vehicule;
    delete this->abonnement;
    this->vehicule = nullptr;
    this->abonnement = nullptr;
    Personne::nb_Client--;

}
ostream& operator<<(ostream& out, Client& C){
    out<<"------------ Caracteristiques de client -----------"<<endl;
    out<<"L id de client est: "<<C.id<<endl;
    out<<"Le nom de client est: "<<C.nom<<endl;
    out<<"Le prenom de client est: "<<C.prenom<<endl;
    out<<"L abonnement est: "<<endl;
    out<<*C.abonnement;
    out<<"------------ Cordonnees de vehicule:"<<endl;
    if(typeid(*C.vehicule)==typeid(Voiture))
        out<<static_cast<Voiture&>(*C.vehicule);
    else if(typeid(*C.vehicule)==typeid(Moto_classique))
        out<<static_cast<Moto_classique&>(*C.vehicule);
    else if(typeid(*C.vehicule)==typeid(Moto_lourd))
        out<<static_cast<Moto_lourd&>(*C.vehicule);
    return out;
}
istream& operator>>(istream& in, Client& C){
    cout<<"------------ Cordonnees de client -----------"<<endl;
    /*cout<<"Donnez l'id de client: "<<endl;
    in>>C.id;*/
    cout<<"Donnez le nom de client: "<<endl;
    in>>C.nom;
    cout<<"Donnez le prenom de client: "<<endl;
    in>>C.prenom;
    C.abonnement = new Abonnement();
    cout<<"------------ Cordonnees d abonnement ----"<<endl;
    in>>*C.abonnement;
    C.vehicule = new Vehicule();
    int choix;
    cout<<"------------ Cordonnees de Vehicule: "<<endl;
    cout<<"Choisir le type de votre vehicule: "<<endl;
    cout<<"Pour saisir une voiture choisir 1"<<endl;
    cout<<"Pour saisir une moto classique choisir 2"<<endl;
    cout<<"Pour saisir une moto lourde choisir 3"<<endl;
    cin>>choix;
    if(choix==1)
    {
        Voiture* v = new Voiture();
        in>>*v;
        C.vehicule = v;
    }
    else if(choix==2)
    {
        Moto_classique* m = new Moto_classique();
        in>>*m;
        C.vehicule = m;
    }
    else if(choix==3)
    {
        Moto_lourd* m = new Moto_lourd();
        in>>*m;
        C.vehicule = m;
    }
    Personne::personnes.push_back(&C);
    return in;
}
ostream& operator<<(ostream& out,const Client* C){
    out<<C->id<<" "<<C->nom<<" "<<C->prenom<<" "<<C->abonnement;
    return out;
}
istream& operator>>(istream& in, Client* C){
    in>>C->nom>>C->prenom;
    C->abonnement = new Abonnement();
    in>>C->abonnement;
    return in;
}
Client& Client::operator=(const Client& C){

    if (this != &C){
        Personne::operator=(C);
        if (this->abonnement != nullptr)
                delete this->abonnement;
        if (C.abonnement != nullptr)
            this->abonnement = new Abonnement(*C.abonnement);
        else
            this->abonnement = nullptr;
        /*delete this->vehicule;
        this->vehicule = NULL;
        this->id = P.id;
        this->nom = P.nom;
        this->prenom = P.prenom;
        this->vehicule = new Vehicule(*P.vehicule);*/
    }
    return *this;
}
float Client::calcul_montant(){
    this->vehicule->getTicket().setMontant(this->abonnement->getRemise());
    return this->vehicule->getTicket().getMontant();
};


/*********************************************************** Liste des prix ***************************************************************************/
ListePrix::ListePrix(float prix_voiture, float prix_moto_classique, float prix_moto_lourd){
    this->prix_voiture = prix_voiture;
    this->prix_moto_classique = prix_moto_classique;
    this->prix_moto_lourd = prix_moto_lourd;
}
ostream& operator<<(ostream& out, ListePrix& L){
    out<<"Le prix horaire pour une voiture est: "<<L.prix_voiture<<endl;
    out<<"Le prix horaire pour une moto classique est: "<<L.prix_moto_classique<<endl;
    out<<"Le prix horaire pour une moto lourde est: "<<L.prix_moto_lourd<<endl;
    return out;
}
istream& operator>>(istream& in, ListePrix& L){
    cout<<"Saisir le prix horaire pour une voiture: "<<endl;
    in>>L.prix_voiture;
    cout<<"Saisir le prix horaire pour une moto classique: "<<endl;
    in>>L.prix_moto_classique;
    cout<<"Saisir le prix horaire pour une moto lourde: "<<endl;
    in>>L.prix_moto_lourd;
    return in;
}
ListePrix& ListePrix::operator=(const ListePrix& L){
    if(this != &L)
    {
        this->prix_voiture = L.prix_voiture;
        this->prix_moto_classique = L.prix_moto_classique;
        this->prix_moto_lourd = L.prix_moto_lourd;
    }
    return *this;
}
ostream& operator<<(ostream& out, ListePrix* L){
    out<<L->prix_voiture<<" "<<L->prix_moto_classique<<" "<<L->prix_moto_lourd<<" ";
    return out;
}
istream& operator>>(istream& in, ListePrix* L){
    in>>L->prix_voiture>>L->prix_moto_classique>>L->prix_moto_lourd;
    return in;
}
float ListePrix::getPrix_voiture(){
    return this->prix_voiture;
}
float ListePrix::getPrix_moto_classique(){
    return this->prix_moto_classique;
}
float ListePrix::getPrix_moto_lourd(){
    return this->prix_moto_lourd;
}


/*********************************************************** Capacite ***************************************************************************/
Capacite::Capacite(int nb_max_voitures, int nb_max_motos){
    this->nb_max_voitures = nb_max_voitures;
    this->nb_max_motos = nb_max_motos;
}
ostream& operator<<(ostream& out, Capacite& C){
    out<<"Le nombre max de voitures est: "<<C.nb_max_voitures<<endl;
    out<<"Le nombre max de motos est: "<<C.nb_max_motos<<endl;
    return out;
}
istream& operator>>(istream& in, Capacite& C){
    cout<<"Saisir Le nombre max de voitures: "<<endl;
    in>>C.nb_max_voitures;
    cout<<"Saisir Le nombre max de motos: "<<endl;
    in>>C.nb_max_motos;
    return in;
}
Capacite& Capacite::operator=(const Capacite& C){
    if(this != &C)
    {
        this->nb_max_voitures = C.nb_max_voitures;
        this->nb_max_motos = C.nb_max_motos;
    }
    return *this;
}
ostream& operator<<(ostream& out, Capacite* C){
    out<<C->nb_max_voitures<<" "<<C->nb_max_motos<<" ";
    return out;

}
istream& operator>>(istream& in, Capacite* C){
    in>>C->nb_max_voitures>>C->nb_max_motos;
    return in;
}
int Capacite::getNb_max_motos(){
    return this->nb_max_motos;
}
int Capacite::getNb_max_voitures(){
    return this->nb_max_voitures;
}


/*********************************************************** Parking ***************************************************************************/
Parking::Parking(){
    this->id = 0;
    this->designation = "";
    this->localisation = "";
    this->capacite = nullptr;
    this->nb_paiements = 0;
    this->nb_voitures = 0;
    this->nb_motos = 0;
    this->liste_prix = nullptr;
}
Parking::Parking(int id, string designation, string localisation, Capacite* capacite, ListePrix* liste_prix){
    this->id = id;
    this->designation = designation;
    this->localisation = localisation;
    this->capacite = new Capacite(*capacite);
    this->nb_paiements = 0;
    this->nb_voitures = 0;
    this->nb_motos = 0;
    this->liste_prix = new ListePrix(*liste_prix);
}
Parking::Parking(Parking& P){
    this->id = P.id;
    this->designation = P.designation;
    this->localisation = P.localisation;
    if(P.capacite != nullptr)
        this->capacite = new Capacite(*P.capacite);
    this->nb_paiements = P.nb_paiements;
    multimap<Date, float>::iterator itr;
    for (itr = P.paiements.begin(); itr != P.paiements.end(); ++itr)
        this->paiements.insert(pair<Date, float>(itr->first, itr->second));
    this->nb_voitures = P.nb_voitures;
    this->nb_motos = P.nb_motos;
    if(P.liste_prix != nullptr)
        this->liste_prix = new ListePrix(*P.liste_prix);
    Vehicule* v;
    for(unsigned int i = 0; i<P.vehicules.size(); i++)
    {
        if(typeid(*P.vehicules[i]) == typeid(Voiture))
            v = new Voiture(static_cast<const Voiture&>(*P.vehicules[i]));
        else if(typeid(*P.vehicules[i]) == typeid(Moto_classique))
            v = new Moto_classique(static_cast<const Moto_classique&>(*P.vehicules[i]));
        else if(typeid(*P.vehicules[i]) == typeid(Moto_lourd))
            v = new Moto_lourd(static_cast<const Moto_lourd&>(*P.vehicules[i]));
        this->vehicules.push_back(v);
    }
}
Parking::~Parking(){
    delete this->capacite;
    this->capacite=nullptr;
    delete this->liste_prix;
    this->liste_prix=nullptr;
    for(unsigned int i=0; i<this->vehicules.size(); i++)
        this->vehicules[i]->retirer_ticket();
    this->vehicules.clear();
}
void Parking::ajouter_vehicule(Vehicule* V, Liste<Ticket>& L){
    Ticket* t = new Ticket();
    t->setMatricule(V->getMat());
    if(typeid(*V) == typeid(Voiture))
        if(this->nb_voitures < this->capacite->getNb_max_voitures())
        {
            cout<<"Ajout de la voiture ayant la matricule: "<<V->getMat()<<" au parking"<<endl;
            cin>>*t;
            t->calcul_montant(this->liste_prix->getPrix_voiture());
            L.ajouter(*t);
            V->affecter_ticket(t);
            this->vehicules.push_back(V);
            this->nb_voitures += 1;
        }

        else cout<<"La capapité maximale des voitures est atteintes"<<endl;
    else if(typeid(*V) == typeid(Moto_classique))
            if(this->nb_motos < this->capacite->getNb_max_motos())
            {
                cout<<"Ajout de la moto classique ayant la matricule: "<<V->getMat()<<" au parking"<<endl;
                cin>>*t;
                t->calcul_montant(this->liste_prix->getPrix_moto_classique());
                L.ajouter(*t);
                V->affecter_ticket(t);
                this->vehicules.push_back(V);
                this->nb_motos += 1;
            }
            else cout<<"La capapité maximale des Motos est atteintes"<<endl;
    else if(typeid(*V) == typeid(Moto_lourd))
            if(this->nb_motos < this->capacite->getNb_max_motos())
            {
                cout<<"Ajout de la moto lourde ayant la matricule: "<<V->getMat()<<" au parking"<<endl;
                cin>>*t;
                t->calcul_montant(this->liste_prix->getPrix_moto_lourd());
                L.ajouter(*t);
                V->affecter_ticket(t);
                this->vehicules.push_back(V);
                this->nb_motos += 1;
            }
            else cout<<"La capapité maximale des Motos est atteintes"<<endl;
}
int Parking::chercher_vehicule(int matricule){
    try {
        for(unsigned int i = 0; i<this->vehicules.size(); i++)
            if(this->vehicules[i]->getMat() == matricule)
                return i;
        throw std::invalid_argument("Ce matricule n'existe pas!");
    } catch (std::invalid_argument& e) {
        std::cerr << e.what() << std::endl;
        return -1;
    }
}
void Parking::liberer_place(int pos){
        if(typeid(*this->vehicules[pos])==typeid(Voiture))
            this->nb_voitures-=1;
        else if(typeid(*this->vehicules[pos])==typeid(Moto_classique)||typeid(*this->vehicules[pos])==typeid(Moto_lourd))
            this->nb_motos-=1;
        vehicules.erase(vehicules.begin()+pos);
}
void Parking::liberer_place(Vehicule* V){
    if(V->getTicket().getEtat())
    {
        this->paiements.insert(pair<Date, float>(V->getTicket().getDateSortie(),V->getTicket().getMontant()));
        this->nb_paiements++;
        V->retirer_ticket();
        liberer_place(chercher_vehicule(V->getMat()));
    }
    else cout<<"Le ticket de cette vehicule n'est pas encore paye!"<<endl<<"Le payer d'abord"<<endl;
}
void Parking::calcul_nb_places_libres(int* v, int* m){
    *v = this->capacite->getNb_max_voitures()- this->nb_voitures;
    *m = this->capacite->getNb_max_motos() - this->nb_motos;
}
float Parking::calcul_chiffre_affaires(int annee){
    float CA = 0;
    for (auto itr = paiements.begin(); itr != paiements.end(); ++itr) {
        if(itr->first.getAnnee() == annee)
            CA += itr->second;
    }
    return CA;
}
float Parking::calcul_chiffre_affaires(int annee, int mois){
    float CA = 0;
    for (auto itr = paiements.begin(); itr != paiements.end(); ++itr) {
        if(itr->first.getAnnee() == annee && itr->first.getMois() == mois)
            CA += itr->second;
    }
    return CA;
}
float Parking::calcul_chiffre_affaires(int annee, int mois, int jour){
    float CA = 0;
    for (auto itr = paiements.begin(); itr != paiements.end(); ++itr) {
        if(itr->first.getAnnee() == annee && itr->first.getMois() == mois && itr->first.getJour() == jour)
            CA += itr->second;
    }
    return CA;
}
istream& operator>>(istream& in, Parking& P){
    cout<<"Entrez les informations pour le parking: "<<endl;
    cout<<"ID du parking: ";
    in>>P.id;
    cout<<"Designation du parking: ";
    in>>P.designation;
    cout<<"Localisation du parking: ";
    in>>P.localisation;
    cout<<"Capacite du parking: "<<endl;
    P.capacite = new Capacite();
    in>>*(P.capacite);
    cout<<"Liste des prix: "<<endl;
    P.nb_paiements = 0;
    multimap<Date, float>::iterator itr;
    for (itr = P.paiements.begin(); itr != P.paiements.end(); ++itr)
        P.paiements.erase(itr);
    P.liste_prix = new ListePrix();
    in>>*(P.liste_prix);
    char rep;
    int choix;
    Ticket* t;
    cout<<"Pour saisir une voiture choisir 1"<<endl;
    cout<<"Pour saisir une moto classique choisir 2"<<endl;
    cout<<"Pour saisir une moto lourde choisir 3"<<endl;
    do
    {
        int v = P.capacite->getNb_max_voitures() - P.nb_voitures;
        int m = P.capacite->getNb_max_motos() - P.nb_motos;
        //P.calcul_nb_places_libres(nb_v, nb_m);
        cout<<"Entrez un choix: ";
        cin>>choix;
        if(choix==1)
        {
            if(v>0)
            {
                Voiture *V = new Voiture();
                in>>*V;
                t = new Ticket();
                cin>>*t;
                t->setMatricule(V->getMat());
                t->calcul_montant(P.liste_prix->getPrix_voiture());
                V->affecter_ticket(t);
                P.vehicules.push_back(V);
                P.nb_voitures+=1;
            }
            else cout<<"La capacite maximale des voitures est atteinte!"<<endl;

        }
        else if(choix==2)
        {
            if(m>0)
            {
                Moto_classique *M = new Moto_classique();
                in>>*M;
                t = new Ticket();
                cin>>*t;
                t->setMatricule(M->getMat());
                t->calcul_montant(P.liste_prix->getPrix_moto_classique());
                M->affecter_ticket(t);
                P.vehicules.push_back(M);
                P.nb_motos+=1;
            }
            else cout<<"La capacite maximale des motos est atteinte!"<<endl;
        }
        else if(choix==3)
        {
            if(m>0)
            {
                Moto_lourd *M = new Moto_lourd();
                in>>*M;
                t = new Ticket();
                cin>>*t;
                t->setMatricule(M->getMat());
                t->calcul_montant(P.liste_prix->getPrix_moto_lourd());
                M->affecter_ticket(t);
                P.vehicules.push_back(M);
                P.nb_motos+=1;
            }
            else cout<<"La capacite maximale des motos est atteinte!"<<endl;
        }
        cout<<"Ajouter une autre vehicule ? (O/N)";
        cin>> rep ;
    } while(rep=='o'|| rep =='O') ;
    return in ;

}
ostream& operator<<(ostream& out, Parking& P){
    out<<"------------------------ Caracteristiques de Parking -------------"<<endl;
    out<<"Parking ID: "<<P.id<<endl;
    out<<"Designation: "<<P.designation<<endl;
    out<<"Localisation: "<<P.localisation<<endl;
    out<<"Nombre de voitures dans le parking: "<<P.nb_voitures<<endl;
    out<<"Nombre de motos dans le parking: "<<P.nb_motos<<endl;
    out<<"Capacité du parking: "<<endl;
    out<<*(P.capacite);
    out<<"Nombre de paiements: "<<P.nb_paiements<<endl<<"Paiements: "<<endl;
    multimap<Date, float>::iterator itr;
    for (itr = P.paiements.begin(); itr != P.paiements.end(); ++itr)
        out<<"Date: "<<itr->first<<"\tMontant: "<<itr->second<<endl;
    out<<"Liste des prix: "<<endl;
    out<<*(P.liste_prix);
    if(P.vehicules.size()==0)
        out<<"Pas de vehicules dans le parking"<<endl;
    else{
        out<<"-------- Vehicules dans le parking: -------- "<<endl;
        for(unsigned int i=0; i < P.vehicules.size(); i++) {
            if(typeid(*P.vehicules[i])==typeid(Voiture))
                out<<static_cast<Voiture&>(*P.vehicules[i]);
            else if(typeid(*P.vehicules[i])==typeid(Moto_classique))
                out<<static_cast<Moto_classique&>(*P.vehicules[i]);
            else if(typeid(*P.vehicules[i])==typeid(Moto_lourd))
                out<<static_cast<Moto_lourd&>(*P.vehicules[i]);
            out<<"------------------------"<<endl;
        }
    }
    return out;
}
Parking& Parking::operator=(const Parking& P){
  if(this != &P)
    {
        this->id = P.id;
        this->designation = P.designation;
        this->localisation = P.localisation;
        if(this->capacite != nullptr)
            delete this->capacite;
        if(P.capacite != nullptr)
            this->capacite = new Capacite(*P.capacite);
        else this->capacite = nullptr;
        this->nb_paiements = P.nb_paiements;
        multimap<Date, float>::const_iterator itr;
        for (itr = this->paiements.begin(); itr != this->paiements.end(); ++itr)
            this->paiements.erase(itr);
        for (itr = P.paiements.begin(); itr != P.paiements.end(); ++itr)
            this->paiements.insert(pair<Date, float>(itr->first, itr->second));
        this->nb_voitures = P.nb_voitures;
        this->nb_motos = P.nb_motos;
        if(this->liste_prix != nullptr)
        delete this->liste_prix;
        if(P.liste_prix != nullptr)
            this->liste_prix = new ListePrix(*P.liste_prix);
        else this->liste_prix = nullptr;
        this->vehicules.clear();
        Vehicule* v;
        for(unsigned int i = 0; i<P.vehicules.size(); i++)
        {
            if(typeid(*P.vehicules[i]) == typeid(Voiture))
                v = new Voiture(static_cast<Voiture&>(*P.vehicules[i]));
            else if(typeid(*P.vehicules[i]) == typeid(Moto_classique))
                v = new Moto_classique(static_cast<Moto_classique&>(*P.vehicules[i]));
            else if(typeid(*P.vehicules[i]) == typeid(Moto_lourd))
                v = new Moto_lourd(static_cast<Moto_lourd&>(*P.vehicules[i]));
            this->vehicules.push_back(v);
        }
    }
    return *this;
}
void Parking::enregister_fichier(){
    ofstream fo("Parking.txt");
    if(!fo)
    {
        cout<<"\n erreur fichier parking";
        return;
    }
    fo<<this->id<<" "<<this->designation<<" "<<this->localisation<<" "<<this->capacite<<" "<<this->nb_paiements<<" "<<this->nb_voitures<<" "<<this->nb_motos<<" "<<this->liste_prix;
    multimap<Date, float>::iterator itr;
    for (itr = this->paiements.begin(); itr != this->paiements.end(); ++itr)
    {
        Date *dt = new Date(itr->first);
        fo<<dt<<" "<<itr->second<<" ";
    }
    for(unsigned int i=0;i<this->vehicules.size();i++)
    {
        if(typeid(*this->vehicules[i])==typeid(Voiture))
        {
            Voiture* v = new Voiture(static_cast<Voiture&>(*this->vehicules[i]));
            fo<<"1"<<" "<<v;
            delete v;
        }
        else if(typeid(*this->vehicules[i])==typeid(Moto_classique))
        {
            Moto_classique* m = new Moto_classique(static_cast<Moto_classique&>(*this->vehicules[i]));
            Moto_classique q = static_cast<const Moto_classique&>(*this->vehicules[i]);
            cout<<"####################################"<<q.getRoues();
            fo<<"2"<<" "<<m;
            delete m;
        }
        else if(typeid(*this->vehicules[i])==typeid(Moto_lourd))
        {
            Moto_lourd* m = new Moto_lourd(static_cast<Moto_lourd&>(*this->vehicules[i]));
            fo<<"3"<<" "<<m;
            delete m;
        }
    }
    fo.close();
}
void Parking::lire_fichier(){
    ifstream fi("Parking.txt");
    if(!fi)
    {
        cout<<"\n erreur fichier parking";
        return;
    }
    this->capacite = new Capacite;
    this->liste_prix = new ListePrix;
    fi>>this->id>>this->designation>>this->localisation>>this->capacite>>this->nb_paiements>>this->nb_voitures>>this->nb_motos>>this->liste_prix;
    float m;
    for(int i = 0; i<this->nb_paiements; i++)
    {
        Date *d = new Date;
        fi>>d>>m;
        this->paiements.insert(pair<Date, float>(*d,m));
        delete d;
    }
    int val;
    while(fi>>val)
    {
        if(val == 1)
        {
            Voiture* v = new Voiture;
            fi >> v;
            this->vehicules.push_back(v);
        }
        else if(val == 2)
        {
            Moto_classique* m = new Moto_classique;
            cout<<endl<<"moto classique"<<endl;
            fi >> m;
            this->vehicules.push_back(m);
            cout<<"ok";
        }
        else if (val == 3)
        {
            Moto_lourd* m = new Moto_lourd;
            fi >> m;
            this->vehicules.push_back(m);
        }
    }
    fi.close();
}


/*********************************************************** Gestion_Parking ***************************************************************************/
Gestion_Parking::Gestion_Parking(Parking* p){
    this->parking = p;
}
Gestion_Parking::Gestion_Parking(const Gestion_Parking& L){
    this->parking = L.parking;
    //Personne* p;
    for(int i = 0; i<L.personnes.size(); i++)
    {
        if(typeid(*L.personnes[i]) == typeid(Passager)){
            Passager *p = new Passager(static_cast<const Passager&>(*L.personnes[i]));
            this->personnes.push_back(p);
        }

        else if(typeid(*L.personnes[i]) == typeid(Client)){
            Client *p = new Client(static_cast<const Client&>(*L.personnes[i]));
            this->personnes.push_back(p);
        }

    }
}
Gestion_Parking::~Gestion_Parking(){
    delete this->parking;
    this->parking = nullptr;
    for(int i = 0; i<this->personnes.size(); i++)
        delete this->personnes[i];
    this->personnes.clear();
}
Gestion_Parking& Gestion_Parking::operator=(const Gestion_Parking& L){
    if (this != &L){
        this->parking = L.parking;
        Personne* p;
        for(int i = 0; i<L.personnes.size(); i++)
        {
            if(typeid(*L.personnes[i]) == typeid(Passager))
                p = new Passager(static_cast<const Passager&>(*L.personnes[i]));
            else if(typeid(*L.personnes[i]) == typeid(Client))
                p = new Client(static_cast<const Client&>(*L.personnes[i]));
            this->personnes.push_back(p);
        }
    }
    return *this;
}
void Gestion_Parking::ajouterPersonne(Personne* p){
    this->personnes.push_back(p);
}
ostream& operator<<(ostream& out, Gestion_Parking& L){
    out<<"--------------------------------- Voici la liste des personnes: ------------------------------- "<<endl;
    out<<"***********************************************************************************************"<<endl;
    for(int i=0; i < L.personnes.size(); i++) {
            if(typeid(*L.personnes[i]) == typeid(Passager))
               out<<(static_cast<Passager&>(*L.personnes[i]));
            else if(typeid(*L.personnes[i]) == typeid(Client))
               out<<(static_cast<Client&>(*L.personnes[i]));
    out<<"***********************************************************************************************"<<endl;
    }
    return out;
}
istream& operator>>(istream& in, Gestion_Parking& L){
    int choix;
    char rep;
    cout<<"Pour saisir un passager choisir 1"<<endl;
    cout<<"Pour saisir un client choisir 2"<<endl;
    /*Gestion_Parking::nb_passagers = Passager::nb_Passager;
    Gestion_Parking::nb_clients = Passager::nb_Client;*/
    do
    {
        cout<<"Entrez un choix: ";
        cin>>choix;
        if(choix==1)
        {
                Passager *p = new Passager();
                Gestion_Parking::nb_passagers++;
                in>>*p;
                p->setId(Gestion_Parking::nb_passagers);
                //L.personnes.push_back(p);
                //P.nb_voitures+=1;
                L.enregistrer_fichier_perso(p);

        }
        else if(choix==2)
        {
                Client *c = new Client();
                in>>*c;
                Gestion_Parking::nb_clients++;
                c->setId(Gestion_Parking::nb_clients);
                //L.personnes.push_back(c);
                //P.nb_voitures+=1;
                L.enregistrer_fichier_perso(c);
        }

        cout<<"Ajouter une autre personne ? (O/N)";
        cin>> rep ;
    } while(rep=='o'|| rep =='O') ;
    return in ;
}
/*void Gestion_Parking::enregistrer_fichier(){
    ofstream fo("Personne.txt",ios::app);
    if(!fo){
        cout<<"\n Erreur Fichier Personne";
        return;
    }
    ofstream ff("Abonnement.txt");
    if(!ff){
        cout<<"\n Erreur Fichier Abonnement";
        return;
    }
    int i;
    for (unsigned int i = 0; i < this->personnes.size();i++){
        if (typeid(*this->personnes[i]) == typeid(Client)){
            Client *c = new Client(static_cast<Client&>(*this->personnes[i]));
            Passager *p = new Passager(static_cast<Passager&>(*this->personnes[i]));
            fo<<"1 "<<p<<" "<<c->getAbon()->getId()<<" "<<p->getVehicule()->getMat()<<"\n";
            //this->enregistrer_fichier_abon(c->getAbon());
            ff<<c->getAbon()<<"\n";
            //enregistrer_fichier_list(this->personnes[i]->getVehicule());
            delete c;
        }
        else if(typeid(*this->personnes[i]) == typeid(Passager))
        {
            Passager *p = new Passager(static_cast<Passager&>(*this->personnes[i]));
            fo<<"2 "<<p<<" "<<p->getVehicule()->getMat()<<"\n";
            //enregistrer_fichier_list(this->personnes[i]->getVehicule());
            delete p;
        }
         enregistrer_fichier_list(this->personnes[i]->getVehicule());
    }
    ff.close();
    fo.close();
}*/
void Gestion_Parking::enregistrer_fichier(){
    for (int i = 0; i < this->personnes.size(); i++)
        this->enregistrer_fichier_perso(this->personnes[i]);
}
void Gestion_Parking::enregistrer_fichier_perso(Personne *P){
    ofstream fo("Personne.txt",ios::app);
    if(!fo){
        cout<<"\n Erreur Fichier Personne";
        return;
    }
    if (typeid(*P) == typeid(Client)){
            Client *c = new Client(static_cast<Client&>(*P));
            Passager *p = new Passager(static_cast<Passager&>(*P));
            Gestion_Parking::nb_abonnements++;
            c->getAbon()->setId(Gestion_Parking::nb_abonnements);
            fo<<"1 "<<p<<" "<<c->getAbon()->getId()<<" "<<p->getVehicule()->getMat()<<"\n";
            this->enregistrer_fichier_abon(c->getAbon());
            //ff<<c->getAbon()<<"\n";
            delete c;
        }
    else if(typeid(*P) == typeid(Passager))
    {
            Passager *p = new Passager(static_cast<Passager&>(*P));
            fo<<"2 "<<p<<" "<<p->getVehicule()->getMat()<<"\n";
            delete p;
    }
    enregistrer_fichier_list(P->getVehicule());
    fo.close();
}
void Gestion_Parking::lire_fichier(){
    Personne *p;
    int val,v,i;
    ifstream fi("Personne.txt");
    if(!fi) cout<<"\n erreur fichier article ";
    lire_fichier_Abonne();
    lire_fichier_Vehicule();
    while(1){
        fi>>val;
        if(fi.eof()) break;
        if (val == 1){
            p = new Client();
            fi>>p;
            fi>>i;
            fi>>v;
            Client *c = new Client();
            Personne::nb_Client--;
            c->setId(p->getId());
            c->setNom(p->gettNom());
            c->setPre(p->getPre());
            c->setAb(this->chercher_abonnement(i));
            c->setVehicule(this->chercher_Vehicule(v));
            //cout<<*c;
            this->personnes.push_back(c);
            //Gestion_Parking::nb_clients++;
        }
        else if (val == 2 ){
            p = new Passager();
            fi>>p;
            fi>>v;
            p->setVehicule(this->chercher_Vehicule(v));
            this->personnes.push_back(p);
            //Gestion_Parking::nb_passagers++;
        }

    }
    fi.close();
}
void Gestion_Parking::Initialiser(){
    Personne *p;
    int val,v,i;
    ifstream fi("Personne.txt");
    if(!fi) cout<<"\n erreur fichier article ";
    Abonnement *a;
    ifstream fa("Abonnement.txt");
    if(!fa) cout<<"\n erreur fichier article ";
    Gestion_Parking::nb_passagers = 0;
    Gestion_Parking::nb_clients = 0;
    Gestion_Parking::nb_abonnements = 0;
    while(1){
        fi>>val;
        if(fi.eof()) break;
        if (val == 1){
            p = new Client();
            fi>>p;
            fi>>i;
            fi>>v;
            Client *c = new Client();
            Personne::nb_Client--;
            c->setId(p->getId());
            c->setNom(p->gettNom());
            c->setPre(p->getPre());
            c->setAb(this->chercher_abonnement(i));
            c->setVehicule(this->chercher_Vehicule(v));
            //cout<<*c;
            Gestion_Parking::nb_clients++;
        }

        else if (val == 2 ){
            p = new Passager();
            fi>>p;
            fi>>v;
            p->setVehicule(this->chercher_Vehicule(v));
            Gestion_Parking::nb_passagers++;
        }


    }
    a = new Abonnement();
    Abonnement::nb--;
    while(fa >> a)
        Gestion_Parking::nb_abonnements++;
    fi.close();
    fa.close();
}

bool abonnementComparator(pair<int, Abonnement>& a,pair<int, Abonnement>& b) {
    const auto& dateA = a.second.getDateDeb();
    const auto& dateB = b.second.getDateDeb();

    if (dateA.getAnnee() != dateB.getAnnee()) {
        return dateA.getAnnee() < dateB.getAnnee();
    } else if (dateA.getMois() != dateB.getMois()) {
        return dateA.getMois() < dateB.getMois();
    } else {
        return dateA.getJour() < dateB.getJour();
    }
}

void Gestion_Parking::lire_fichier_Abonne(){

    Abonnement *a;
    ifstream fi("Abonnement.txt");
    if(!fi) cout<<"\n erreur fichier article ";
    int i = 0;
    a = new Abonnement();
    Abonnement::nb--;
    while(fi >> a){
        this->ajouter_abonnement(a);

    }
    fi.close();
}
void Gestion_Parking::enregistrer_fichier_abon(Abonnement *A){
    ofstream fo("Abonnement.txt",ios::app);
    if(!fo){
        cout<<"\n Erreur Fichier Abonnement";
        return;
    }
    fo<<A<<"\n";
    fo.close();
}
void Gestion_Parking::afficher_abonnements(){
    map<int,Abonnement>::iterator it;
    cout<<Abonnement::nb;
    //this->abonnements.sort();

    std::vector<std::pair<int, Abonnement>> abonnementsVector;
    for (auto& it : abonnements) {
        abonnementsVector.push_back(it);
    }
    std::sort(abonnementsVector.begin(), abonnementsVector.end(), abonnementComparator);
    cout<<"---------------- Voici la liste des abonnements triee par date de deb ------------"<<endl;
    for (auto& it : abonnementsVector) {
        cout<<it.second;
    }
}
Abonnement* Gestion_Parking::chercher_abonnement(int id){
    map<int,Abonnement>::iterator it;
    for (it = abonnements.begin(); it != abonnements.end(); ++it)
        if (it->second.getId() == id)
            return &it->second;
}
void Gestion_Parking::ajouter_abonnement(Abonnement *A){
    map<int,Abonnement>::iterator it;
    /*for (it = abonnements.begin(); it != abonnements.end(); ++it){
        if((it->second.getId() == A->getId()))
            cout<<"L element existe deja"<<endl;
    }*/

    abonnements.insert( std::pair<int,Abonnement>(A->getId(),*A));
}


void Gestion_Parking::lire_fichier_Vehicule(){
    ifstream fi("Vehicules.txt");
    if(!fi) cout<<"\n erreur fichier parking ";
    int val,i,j;
    string s;
    while(1){
        fi>>val;
        if(fi.eof()) break;
        if (val == 1){
            Voiture* v = new Voiture();
            fi>v;
            this->liste_vehicules.push_back(v);
        }
        else if(val == 2){
            Moto_classique *v = new Moto_classique();
            fi>v;
            this->liste_vehicules.push_back(v);

        }
        else if(val == 3){
            Moto_lourd * v = new Moto_lourd();
            fi>v;
            this->liste_vehicules.push_back(v);
        }
    }
    fi.close();
}
void Gestion_Parking::enregistrer_fichier_list(Vehicule *V){
    ofstream fo("Vehicules.txt",ios::app);
    if(!fo){
        cout<<"\n Erreur Fichier Vehicule";
        return;
    }
    if (typeid(*V) == typeid(Voiture)){
        Voiture *v = new Voiture(static_cast<Voiture&>(*V));
        fo<<"1 ";
        fo<v;
        fo<<"\n";
        delete v;
    }
    else if(typeid(*V) == typeid(Moto_classique))
    {
        Moto_classique* m = new Moto_classique(static_cast<Moto_classique&>(*V));
        m->setRoues(2);
        fo<<"2 ";
        fo<m;
        fo<<"\n";
        delete m;
    }

    else if(typeid(*V)==typeid(Moto_lourd))
    {
        Moto_lourd* m = new Moto_lourd(static_cast<Moto_lourd&>(*V));
        m->setRoues(3);
        fo<<"3 ";
        fo<m;
        fo<<"\n";
        delete m;
    }
    fo.close();
}
void Gestion_Parking::afficher_vehicules(){
    list<Vehicule*>::iterator it;
    cout<<"-------- Vehicules des personnes: -------- "<<endl;
    for(it = this->liste_vehicules.begin(); it != this->liste_vehicules.end(); ++it){
        if(typeid(*(*it))==typeid(Voiture))
            cout<<static_cast<Voiture&>(*(*it));
        else if(typeid(*(*it))==typeid(Moto_classique))
            cout<<static_cast<Moto_classique&>(*(*it));
        else if(typeid(*(*it))==typeid(Moto_lourd))
            cout<<static_cast<Moto_lourd&>(*(*it));
        cout<<"------------------------"<<endl;
    }

}
void Gestion_Parking::ajouter_vehicule(Vehicule *V){
    liste_vehicules.push_back(V);
}
Vehicule* Gestion_Parking::chercher_Vehicule(int id){
    list<Vehicule*>::iterator it;
    for (it = liste_vehicules.begin(); it != liste_vehicules.end(); ++it)
        if ((*it)->getMat() == id)
            return (*it);
    return nullptr;
}

void vider_fichiers(){
    ofstream fp("Personne.txt",std::ios::out | std::ios::trunc);
    if(fp.is_open()){
        fp.close();
    }
    ofstream fa("Abonnement.txt",std::ios::out | std::ios::trunc);
    if(fa.is_open()){
        fa.close();
    }
    ofstream fv("Vehicules.txt",std::ios::out | std::ios::trunc);
    if(fv.is_open()){
        fv.close();
    }
}
Personne* Gestion_Parking::chercher_personne(string nom, string prenom){
    for (int i = 0; i < this->personnes.size(); i++){
        if( (this->personnes[i])->getPre() == prenom && this->personnes[i]->gettNom() == nom)
            {
                return this->personnes[i];
            }
    }
    return nullptr;
}
void Gestion_Parking::supprimerPersonne(Personne *P){
    auto foundIterator = find(this->personnes.begin(), this->personnes.end(),P);
    if (foundIterator != this->personnes.end()) {
        vider_fichiers();
        this->personnes.erase(foundIterator);
        enregistrer_fichier();
        cout << "Personne supprime de la liste"<< endl;
    } else {
        cout << "Personne  n'existe pas dans la liste!"<< endl;
    }
}

