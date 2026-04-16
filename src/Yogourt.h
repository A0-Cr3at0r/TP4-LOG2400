#pragma once
#include <pch.h>
#include "Garniture.h"
#include "const.h"
#include <vector>

class Yogourt;

class YogourtRegistre : public AlimentRegistre<YogourtRegistre, Yogourt> {
public:
    // Note: arg order is (nom, cout, qte) to match Inventaire registration calls,
    // but AlimentRegistre expects (nom, qte, cout) — reordered in delegating call.
    YogourtRegistre(string&& nom, double cout, unsigned int qte)
        : AlimentRegistre(std::move(nom), qte, cout) {}

    TypeAliment getTypeAliment() override { return TypeAliment::YOGOURT; }
};

class Yogourt : public Aliment<YogourtRegistre> {
public:
    template<typename, typename> friend class AlimentRegistre;

    explicit Yogourt(YogourtRegistre& sorte);
    Yogourt(Yogourt&&)            = default;
    Yogourt& operator=(Yogourt&&) = default;
    Yogourt(const Yogourt&)            = delete;
    Yogourt& operator=(const Yogourt&) = delete;

    void          ajouterGarniture(typeGarniture type, Garniture&& garniture);
    typeGarniture undo();
    bool          hasGarnitures() const;
    double        prixTotal()     const;

    const YogourtRegistre&            getSorteYogourt() const;
    const std::vector<typeGarniture>& getTypes()        const;

private:
    std::vector<Garniture>     _garnitures;
    std::vector<typeGarniture> _types;
};
