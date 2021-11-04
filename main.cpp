#include<iostream>
#include<array>
#include "Polynomial.hpp"
#include "Permutation.hpp"
#include "Buchberger.hpp"

constexpr size_t k = 3;
constexpr size_t N = 10;

std::array<Polynomial<k>, N+1> ComputeBarPolynomials() {
	std::array<Polynomial<k>, N+1> polynomials;
	polynomials[0] += CONST_MONOMIAL<k>;
	for(size_t i = 1; i <= N; i++) {
		auto& polynomial = polynomials[i];
		for(size_t s = 1; s <= k && s <= i; s++) {
			auto& previousPolynomial = polynomials[i-s];
			for(const auto& previousMonomial : previousPolynomial.GetMonomials()) {
				polynomial += previousMonomial * s;
			}
		}
	}	
	return polynomials;
}

int main() {
	/*
	const auto perm = Permutation<k>(false);
	auto comp = [&perm](const Monomial<k>& a, const Monomial<k>& b) {
		return a.IsLessThan(b, perm);
	};
	const auto& barPolynomials = ComputeBarPolynomials();
	for(const auto& polynomial : barPolynomials) {
		std::cout << polynomial << std::endl;
		std::cout << polynomial.LeadingTerm(comp) << std::endl;
	}
	
	std::vector<Polynomial<k>> basis = {barPolynomials[N], barPolynomials[N-1], barPolynomials[N-2], barPolynomials[N-3]};
	Buchberger<k, decltype(comp)> bb(comp, basis);
	const auto S = bb.CreateSyzygy(barPolynomials[N], barPolynomials[N-1]);
	std::cout<< S <<std::endl;
	const auto NF = bb.NormalForm(S);
	std::cout<< NF <<std::endl;
	*/
	
	const auto perm = Permutation<k>();
	auto comp = [&perm](const Monomial<k>& a, const Monomial<k>& b) {
		return a.IsLessThan(b, perm);
	};
	std::vector<Polynomial<k>> basis = {
		Polynomial<k>({ {0,0,1}, {5,0,0} }),
		Polynomial<k>({ {0,1,0}, {3,0,0} }),
	};
	Buchberger<k, decltype(comp)> bb(comp, basis);
	const auto gBasis = bb.ComputeGroebnerBasis();
	for( const auto& polynomial : gBasis ) {
		std::cout<<polynomial<<", ";
	}
	system("pause");
	return 0;
}

