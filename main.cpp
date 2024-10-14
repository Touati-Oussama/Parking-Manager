#include <iostream>
#include "source.cpp"
#include <algorithm>
using namespace std;


bool CompareAbonnementsByDate(Abonnement& a,Abonnement& b) {
  return a.getDateDeb() < b.getDateDeb();
}
int main()
{
    Date *d1 = new Date(2023,11,11,10);
    Date *d2 = new Date(2023,11,12,14);
    Ticket *t = new Ticket(12,d1,d2);
    Vehicule *v = new Voiture(10,"Porsche",10,10,10);
    Vehicule *m = new Moto_classique(11,"Piago",2);
    Vehicule *m2 = new Moto_lourd(12,"Quad",4);
    Vehicule *v2 = new Voiture(13,"BMW",10,10,10);
    Vehicule *v3 = new Voiture(13,"GOLF 6",10,10,10);
    Capacite* ca=new Capacite(2,2);
    ListePrix* l=new ListePrix(10,5,7.5);
    Abonnement *a = new Abonnement(*d1,*d2,25.0);
    Abonnement *a1 = new Abonnement(*d1,*d2,35.0);
    Abonnement *a2 = new Abonnement(*d1,*d2,10.0);
    Parking *P2 = new Parking(1,"Parking Privee", "Tunis",ca,l);
    //P2->ajouter_vehicule(v);
    /*P2->ajouter_vehicule(m);
    P2->ajouter_vehicule(m2);
    //P2->enregistrer_fichier();
    //cout<<P2->chercher_vehicule(100);
    cout<<*P2;
    cout<<"---------------------------------------"<<endl;*/
    /*Client *c1 = new Client("Oussama","Touati",m,a);
    Passager *p = new Passager("Ahmed","Touati",v);
    Client *c2 = new Client("Melek","Hajri",m2,a1);
    Passager *p2 = new Passager("Fares","Touati",v2);*/
    Gestion_Parking *lp = new Gestion_Parking(P2);
    /*lp->enregistrer_fichier_list(v);
    lp->enregistrer_fichier_list(m);
    lp->enregistrer_fichier_list(m2);
    lp->enregistrer_fichier_list(v2);
    lp->enregistrer_fichier_list(v3);*/
    /*lp->enregistrer_fichier_abon(a);
    lp->enregistrer_fichier_abon(a1);
    lp->enregistrer_fichier_abon(a2);*/
    /*lp->enregistrer_fichier_perso(c1);
    lp->enregistrer_fichier_perso(p);
    lp->enregistrer_fichier_perso(c2);
    lp->enregistrer_fichier_perso(p2);*/
    /*
    lp->lire_fichier_Abonne();
    //lp->afficher_abonnements();
    lp->lire_fichier();
    /*Client *c3 = new Client();
    cin>>*c3;*/
    //Personne::enregistrer_fichier();
    /*Abonnement *ab = new Abonnement();
    cin>>*ab;
    cout<<*ab;*/
    //cin>>*lp;

    /*lp->ajouter_abonnement(a);
    lp->ajouter_abonnement(a1);
    lp->ajouter_abonnement(a2);

    cout<<*lp;*/
    //lp->ajouter_vehicule(v);
    //lp->ajouter_vehicule(m);
    //lp->lire_fichier_Vehicule();
    //lp->afficher_vehicules();
    //lp->enregistrer_fichier_list(m);
    //lp->enregistrer_fichier_list(v);
    /*cin>>*lp;*/

    /*lp->ajouterPersonne(c1);
    lp->ajouterPersonne(p);
    lp->ajouterPersonne(c2);
    lp->enregistrer_fichier();*/
    /*lp->enregistrer_fichier_perso(c1);
    lp->enregistrer_fichier_perso(p);
    lp->enregistrer_fichier_perso(c2);*/
    //cin>>*lp;
    /*lp->lire_fichier();
    cout<<*lp;*/
    //cin>>*lp;
    lp->Initialiser();
    //cin>>*lp;
    lp->lire_fichier();
    cout<<"*************************************************************************************************************"<<endl;
    //lp->enregistrer_fichier();
    //cout<<*lp;
    string prenom = "Oussama";
    string nom = "Touati";
    /*auto it = std::find_if(lp->personnes.begin(), lp->personnes.end(), [personNameToFind](const Personne& p) -> bool {
        return p.gettNom() == personNameToFind;
    });*/
    //Personne *p = lp->chercher_personne(nom,prenom);
    /*auto it = std::find(lp->personnes.begin(), lp->personnes.end(),p);
    if (it != lp->personnes.end())
        cout<<"------- Yes ---"<<endl;
    else
        cout<<"------- Non ---"<<endl;*/
    //cout<<*lp;
    //lp->personnes.erase(it);
    //lp->supprimerPersonne(p);
    //cout<<*lp;
    //cout<<*lp;
    lp->lire_fichier_Abonne();
    lp->afficher_abonnements();
    return 0;
}


