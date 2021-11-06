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
	const auto perm = Permutation<k>(true);
	auto comp = [&perm](const Monomial<k>& a, const Monomial<k>& b) {
		return a.IsLessThan(b, perm);
	};
	const auto& barPolynomials = ComputeBarPolynomials();
//	for(const auto& polynomial : barPolynomials) {
//		std::cout << polynomial << std::endl;
//	}
	
	std::vector<Polynomial<k>> basis;
	for(size_t m=2; m<=N-k+1; ++m) {
		std::cout<<"------------------------"<<std::endl;
		basis.clear();
		for(size_t j=0; j<k-1; ++j) {
			basis.push_back(barPolynomials[m+j]);
		}
		for( const auto& polynomial : basis ) {
			std::cout<<polynomial<<", ";
		}
		std::cout<<std::endl;
/*		Buchberger<k, decltype(comp)> bb(comp, basis);
		const auto gBasis = bb.ComputeGroebnerBasis();
		for( const auto& polynomial : gBasis ) {
			std::cout<<polynomial<<", ";
		}
		std::cout<<std::endl<<std::endl;*/
		Buchberger<k, decltype(comp)> bb2(comp, basis);
		const auto gMinBasis = bb2.ComputeMinimalGroebnerBasis();
		for( const auto& polynomial : gMinBasis ) {
			std::cout<<polynomial<<", ";
		}
		std::cout<<std::endl;
	}
	
	system("pause");
	return 0;
}

