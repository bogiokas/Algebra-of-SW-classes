#include<array>
#include<set>
#include<cassert>
#include "BinarySet.hpp"
#include<iostream>
//#include "Counter.hpp"

template<int K> class Monomial {
public:
	Monomial() = default;
	Monomial(const Monomial&) = default;
	Monomial(Monomial&&) = default;
	Monomial<K>& operator=(const Monomial<K>&) = default;
	Monomial<K>& operator=(Monomial<K>&&) = default;

	bool operator<(const Monomial<K>& other) const {
		for(size_t i=0; i<K; i++) {
			if(other.m_exponents[i] < m_exponents[i]) return true;
			else if(other.m_exponents[i] > m_exponents[i]) return false;
		}
		return false;
	}

	Monomial<K>& operator*=(size_t i) {
		assert( i <= K );
		m_exponents[i-1]++;
		return *this;
	}
	
	Monomial<K> operator*(size_t i) const {
		auto result = *this;
		result *= i;
		return result;
	}
	
	const std::array<size_t, K>& GetExponents() const {
		return m_exponents;
	}

private:
	std::array<size_t, K> m_exponents;
};

template<int K> static constexpr Monomial<K> CONST_MONOMIAL = Monomial<K>();

template<int K> class Polynomial {
public:
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

	const std::set<Monomial<K>>& GetMonomials() const {
		return m_monomials.GetElements();
	}
private:
	BinarySet<Monomial<K>> m_monomials;
};


template<int K> std::ostream& operator<< (std::ostream& out, const Polynomial<K>& curr) {
	for( const auto& element : curr.GetMonomials() ) {
		out<<element<<" ";
	}
	return out;
}

template<int K> std::ostream& operator<< (std::ostream& out, const Monomial<K>& curr) {
	out<<"|";
	for( auto exponent : curr.GetExponents() ) {
		out<<exponent<<"|";
	}
	return out;
}

