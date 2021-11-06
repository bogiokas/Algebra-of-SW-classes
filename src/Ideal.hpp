#pragma once
#include<vector>
#include "Polynomial.hpp"

template<int K> class Ideal {
	Ideal(const std::vector<Polynomial<K>>& generators)
		: m_generators(generators)
	{}

	std::vector<Polynomial<K>> CalcGroebnerBasis(const Permutation<K>& perm) const {
		
	}

private:
	std::vector<Polynomial<K>> m_generators;
};
