#pragma once
#include<set>
#include<vector>
#include<iostream>
#include "BinarySet.hpp"
#include "Monomial.hpp"

template<size_t K> class Polynomial {
public:
	Polynomial()
		: m_monomials()
	{}
	Polynomial(const std::vector<std::array<size_t, K>>& vectorOfMonomialExponents);

	Polynomial<K>& operator+=(const Monomial<K>& monomial);
	Polynomial<K>& operator+=(Monomial<K>&& monomial);
	Polynomial<K>& operator+=(const Polynomial<K>& other);
	Polynomial<K> operator+(const Polynomial<K>& other) const;

	Polynomial<K>& operator*=(const Monomial<K>& otherMonomial);
	Polynomial<K> operator*(const Monomial<K>& otherMonomial) const;

	template<class Compare> Polynomial<K>& ReduceByMod(const Polynomial<K>& other, Compare cmp);
	template<class Compare> Polynomial<K> Mod(const Polynomial<K>& other, Compare cmp) const;
	
	template<class Compare> Polynomial<K>& ReduceByModFull(const Polynomial<K>& other, Compare cmp);
	template<class Compare> Polynomial<K> ModFull(const Polynomial<K>& other, Compare cmp) const;

	bool IsZero() const;
	template<class Compare> const Monomial<K>& LeadingTerm(Compare cmp) const;

	const std::set<Monomial<K>>& GetMonomials() const {
		return m_monomials.GetElements();
	}
private:
	BinarySet<Monomial<K>> m_monomials;
};


template<size_t K> Polynomial<K>::Polynomial(const std::vector<std::array<size_t, K>>& vectorOfMonomialExponents) {
	for(const auto& monomialExponents : vectorOfMonomialExponents) {
		m_monomials.Insert(Monomial<K>(monomialExponents));
	}
}

template<size_t K> Polynomial<K>& Polynomial<K>::operator+=(const Monomial<K>& monomial) {
	m_monomials.Insert(monomial);
	return *this;
}

template<size_t K> Polynomial<K>& Polynomial<K>::operator+=(Monomial<K>&& monomial) {
	m_monomials.Insert(std::move(monomial));
	return *this;
}

template<size_t K> Polynomial<K>& Polynomial<K>::operator+=(const Polynomial<K>& other) {
	for(const auto& monomial : other.GetMonomials() ) {
		*this += monomial;
	}
	return *this;
}

template<size_t K> Polynomial<K> Polynomial<K>::operator+(const Polynomial<K>& other) const {
	auto result = *this;
	result += other;
	return result;
}

template<size_t K> Polynomial<K>& Polynomial<K>::operator*=(const Monomial<K>& otherMonomial) {
	BinarySet<Monomial<K>> newMonomials;
	for(const auto& monomial : GetMonomials() ) {
		newMonomials.Insert(monomial * otherMonomial);
	}
	m_monomials = std::move(newMonomials);
	return *this;
}		

template<size_t K> Polynomial<K> Polynomial<K>::operator*(const Monomial<K>& otherMonomial) const {
	auto result = *this;
	result *= otherMonomial;
	return result;
}

template<size_t K> template<class Compare> Polynomial<K>& Polynomial<K>::ReduceByMod(const Polynomial<K>& other, Compare cmp) {
	auto div = LeadingTerm(cmp) / other.LeadingTerm(cmp);
	*this += other * div;
	return *this;
}

template<size_t K> template<class Compare> Polynomial<K> Polynomial<K>::Mod(const Polynomial<K>& other, Compare cmp) const {
	auto result = *this;
	result.ReduceByMod(other, cmp);
	return result;
}

template<size_t K> bool Polynomial<K>::IsZero() const {
	return m_monomials.IsEmpty();
}

template<size_t K> template<class Compare> const Monomial<K>& Polynomial<K>::LeadingTerm(Compare cmp) const {
	return m_monomials.GetMaxElement(cmp);
}


template<size_t K> std::ostream& operator<<(std::ostream& out, const Polynomial<K>& curr) {
	for( const auto& element : curr.GetMonomials() ) {
		out<<element<<" ";
	}
	return out;
}
