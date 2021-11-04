#pragma once
#include<set>
#include<vector>
#include<iostream>
#include "BinarySet.hpp"
#include "Monomial.hpp"

template<size_t K> class Polynomial {
public:
	Polynomial() = default;
	Polynomial(const std::vector<std::array<size_t, K>>& vectorOfMonomialExponents) {
		for(const auto& monomialExponents : vectorOfMonomialExponents) {
			m_monomials.Insert(Monomial<K>(monomialExponents));
		}
	}

	Polynomial<K>& operator+=(const Monomial<K>& monomial) {
		m_monomials.Insert(monomial);
		return *this;
	}

	Polynomial<K>& operator+=(Monomial<K>&& monomial) {
		m_monomials.Insert(std::move(monomial));
		return *this;
	}

	Polynomial<K>& operator+=(const Polynomial<K>& other) {
		for(const auto& monomial : other.GetMonomials() ) {
			*this += monomial;
		}
		return *this;
	}

	Polynomial<K> operator+(const Polynomial<K>& other) const {
		auto result = *this;
		result += other;
		return result;
	}

	Polynomial<K>& operator*=(const Monomial<K>& otherMonomial) {
		BinarySet<Monomial<K>> newMonomials;
		for(const auto& monomial : GetMonomials() ) {
			newMonomials.Insert(monomial * otherMonomial);
		}
		m_monomials = std::move(newMonomials);
		return *this;
	}		

	Polynomial<K> operator*(const Monomial<K>& otherMonomial) const {
		auto result = *this;
		result *= otherMonomial;
		return result;
	}

	template<class Compare> Polynomial<K>& ReplaceByMod(const Polynomial<K>& other, Compare cmp) {
		auto div = LeadingTerm(cmp) / other.LeadingTerm(cmp);
		*this += other * div;
		return *this;
	}		

	template<class Compare> Polynomial<K> Mod(const Polynomial<K>& other, Compare cmp) const {
		auto result = *this;
		result.ReplaceByMod(other, cmp);
		return result;
	}

	bool IsZero() const {
		return m_monomials.IsEmpty();
	}

	template<class Compare> const Monomial<K>& LeadingTerm(Compare cmp) const {
		return m_monomials.GetMaxElement(cmp);
	}

	const std::set<Monomial<K>>& GetMonomials() const {
		return m_monomials.GetElements();
	}
private:

	std::set<Monomial<K>>& GetMutableMonomials() {
		return m_monomials.GetMutableElements();
	}
	BinarySet<Monomial<K>> m_monomials;
};


template<size_t K> std::ostream& operator<< (std::ostream& out, const Polynomial<K>& curr) {
	for( const auto& element : curr.GetMonomials() ) {
		out<<element<<" ";
	}
	return out;
}
