#include "Inventaire.h"
#include "Paiement.h"
#include "Abonnement.h"
#include <stack>

class CommandYogourt
{

public:
    CommandYogourt(Inventaire& Inventaire, std::unique_ptr<Paiement>& paiement, Abonnement& abonnement);
    ~CommandYogourt();

    void typeYogourt(std::string Yogourt);
    void selYogourt(int index);
    void undo();
    void redo();
    void appliquerGarniture(Garniture& garniture);
    void mode(std::unique_ptr<Paiement>& paiement);
    void pay();
    void pay(std::unique_ptr<Paiement>& paiement);
    int total();
    int totalProjete();
    std::string paiement();
    void sub(std::string garniture,  std::function<void(std::string)>& abonne);
    void unSub(std::function<void(std::string)>& abonne, std::string nom);
    void subs(std::function<void(std::string)>& abonne);

    int yogourtActif = 0;

private:
    std::vector<std::unique_ptr<Yogourt>> yogourts_;
    Inventaire& inventaire_;
    std::unique_ptr<Paiement>& paiement_;
    Abonnement& abonnement_;
    std::vector<std::stack<Garniture&>> actionHistorique_;
};



