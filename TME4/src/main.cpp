#include "Banque.h"
#include <chrono>
#include <iostream>

using namespace std;

const int NB_THREAD = 10;
const unsigned int NB_COMPTE = 50;
const unsigned int MONTANT_INIT = 100;
const unsigned int  SOLDE_INIT = NB_COMPTE * MONTANT_INIT;

// Opérations réalisé par les thread

void operation_thread(pr::Banque & maBanque){
	// On choissit nos deux comptes
	unsigned int  debiteur = rand()%NB_COMPTE;
	unsigned int  crediteur = rand()%NB_COMPTE;

	while (crediteur==debiteur){
		crediteur = rand()%NB_COMPTE;
	}

	// On détermine le montant 
	int montant = rand()%100;
	// On sécurise l'opération
	
	if (crediteur < debiteur){
		maBanque[crediteur].getMutex().lock();
		maBanque[debiteur].getMutex().lock();
	}else {
		maBanque[debiteur].getMutex().lock();
		maBanque[crediteur].getMutex().lock();
	}
	
	// On réalise des lock avec l'ordre du système 
	maBanque.transfert(crediteur,debiteur,montant);
	// On débloque les compte 
	maBanque[crediteur].getMutex().unlock();
	maBanque[debiteur].getMutex().unlock();

}

int main () {

	vector<thread> threads;
	//On crée notre banque 
	pr::Banque societe_general (NB_COMPTE,MONTANT_INIT);
	// TODO : creer des threads qui font ce qui est demandé
	for(int i =0 ; i<NB_THREAD ;i++){
		threads.push_back(thread (operation_thread,ref(societe_general)));
	}

	for (auto & t : threads) {
		t.join();
	}

	// TODO : tester solde = NB_THREAD * JP
	cout << "Le bilan de la banque est : " << societe_general.comptabiliser(SOLDE_INIT) << endl;
	return 0;
}
