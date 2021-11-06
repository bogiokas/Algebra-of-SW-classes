#pragma once
#include<array>
#include<cassert>
#include<iostream>
#include "Permutation.hpp"
//#include "Counter.hpp"

template<size_t K> class Monomial {
public:
	Monomial() = default;
	Monomial(const std::array<size_t, K>& exponents)
		: m_exponents(exponents)
	{}
	Monomial(std::array<size_t, K>&& exponents)
		: m_exponents(exponents)
	{}
	Monomial(const Monomial&) = default;
	Monomial(Monomial&&) = default;
	Monomial<K>& operator=(const Monomial<K>&) = default;
	Monomial<K>& operator=(Monomial<K>&&) = default;
	
	bool IsLessThan(const Monomial<K>& other, Permutation<K> perm) const {
		for(size_t i=1; i<=K; i++) {
			const size_t index = perm[i];
			if(m_exponents[index-1] < other.m_exponents[index-1]) return true;
			else if(m_exponents[index-1] > other.m_exponents[index-1]) return false;
		}
		return false;
	}

	bool operator<(const Monomial<K>& other) const {
		return IsLessThan(other, Permutation<K>(true));
	}

	Monomial<K>& operator*=(size_t i) {
		assert( i <= K && i > 0);
		m_exponents[i-1]++;
		return *this;
	}
	
	Monomial<K> operator*(size_t i) const {
		auto result = *this;
		result *= i;
		return result;
	}
	
	Monomial<K>& operator*=(const Monomial<K>& other) {
		for(size_t i=0; i<K; ++i) {
			m_exponents[i] += other.m_exponents[i];
		}
		return *this;
	}
	
	Monomial<K> operator*(const Monomial<K>& other) const {
		auto result = *this;
		result *= other;
		return result;
	}
	
	Monomial<K>& operator/=(const Monomial<K>& other) {
		assert(other.Divides(*this));
		for(size_t i=0; i<K; ++i) {
			m_exponents[i] -= other.m_exponents[i];
		}
		return *this;
	}
	
	Monomial<K> operator/(const Monomial<K>& other) const {
		auto result = *this;
		result /= other;
		return result;
	}
	
	bool Divides(const Monomial<K>& other) const {
		for(size_t i=0; i<K; ++i) {
			if(m_exponents[i] > other.m_exponents[i]) return false;
		}
		return true;
	}
	
	Monomial<K> LeastCommonDivisor(const Monomial<K>& other) const {
		std::array<size_t, K> lcmExponents;
		for(size_t i=0 ; i<K; ++i)
		{
			lcmExponents[i] = std::min(m_exponents[i], other.m_exponents[i]);
		}
		return Monomial(lcmExponents);
	}
	
	const std::array<size_t, K>& GetExponents() const {
		return m_exponents;
	}

private:
	std::array<size_t, K> m_exponents;
};

template<size_t K> static constexpr Monomial<K> CONST_MONOMIAL = Monomial<K>();


template<size_t K> std::ostream& operator<< (std::ostream& out, const Monomial<K>& curr) {
	out<<"|";
	for( auto exponent : curr.GetExponents() ) {
		out<<exponent<<"|";
	}
	return out;
}
