#include<iostream>
#include<array>
#include "Polynomial.hpp"

constexpr size_t k = 5;
constexpr size_t N = 15;

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
	const auto& barPolynomials = ComputeBarPolynomials();
	for(const auto& polynomial : barPolynomials) {
		std::cout << polynomial << std::endl;
	}
	system("pause");
	return 0;
}

