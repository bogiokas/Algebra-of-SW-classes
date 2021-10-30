#include<array>
#include<cassert>
#include "BinarySet.hpp"

#include<iostream>

template<int K> class Monomial {
public:
	Monomial() = default;
	Monomial(const Monomial&) = default;

	bool operator<(const Monomial<K>& other) const {
		for(size_t i=0; i<K; i++) {
			if(other.m_exponents[i] < m_exponents[i]) return true;
			else if(other.m_exponents[i] > m_exponents[i]) return false;
		}
		return false;
	}

	void MultiplyByVariable(size_t i) {
		assert( i <= K );
		m_exponents[i-1]++;
	}

	const std::array<size_t, K>& GetExponents() const {
		return m_exponents;
	}
	
private:
	std::array<size_t, K> m_exponents;
};

template<int K> using Polynomial = BinarySet<Monomial<K>>;

template<int K> std::ostream& operator<< (std::ostream& out, const Polynomial<K>& curr) {
	for( const auto& element : curr.GetElements() ) {
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

