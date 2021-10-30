#include<iostream>
#include<array>
#include "Polynomial.hpp"

constexpr size_t k = 3;
constexpr size_t N = 25;

std::array<Polynomial<k>, N+1> ComputeBarPolynomials() {
	std::array<Polynomial<k>, N+1> polynomials;
	polynomials[0].Insert(Monomial<k>());
	for(size_t i = 1; i <= N; i++) {
		auto& polynomial = polynomials[i];
		for(size_t l = 1; l <= i && l <= k; l++) {
			auto& previousPolynomial = polynomials[i-l];
			for(const auto& previousMonomial : previousPolynomial.GetElements()) {
				auto monomial = Monomial<k>(previousMonomial);
				monomial.MultiplyByVariable(l);
				polynomial.Insert(monomial);
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

