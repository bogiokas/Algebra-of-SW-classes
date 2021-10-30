#include<iostream>
#include<array>
#include<vector>
#include<set>
#include<cassert>

constexpr size_t k = 3;
constexpr size_t N = 10;

template<class Element>
class BinarySet {
public:
	BinarySet() = default;

	void Insert(const Element& e) {
		auto it = m_elements.find(e);
		if(it != m_elements.end()) m_elements.erase(it);
		else m_elements.insert(e);
	}
	const std::set<Element>& GetElements() const {
		return m_elements;
	}

	friend std::ostream& operator<< (std::ostream& out, const BinarySet& curr) {
		for(const auto& element : curr.m_elements) {
			out<<element<<" ";
		}
		return out;
	}
private:
	std::set<Element> m_elements;
};

class Monomial {
public:
	Monomial() = default;
	Monomial(const Monomial&) = default;

	bool operator<(const Monomial& other) const {
		for(size_t i=0; i<k; i++) {
			if(other.m_exponents[i] < m_exponents[i]) return true;
			else if(other.m_exponents[i] > m_exponents[i]) return false;
		}
		return false;
	}

	void MultiplyByVariable(size_t i) {
		assert( i <= k );
		m_exponents[i-1]++;
	}
	const std::array<size_t, k>& GetExponents() const {
		return m_exponents;
	}
	
	friend std::ostream& operator<< (std::ostream& out, const Monomial& curr) {
		out<<"|";
		for( auto exponent : curr.m_exponents ) {
			out<<exponent<<"|";
		}
		return out;
	}
private:
	std::array<size_t, k> m_exponents;
};

using Polynomial = BinarySet<Monomial>;

int main() {
	std::array<Polynomial, N+1> barPolynomials;
	barPolynomials[0].Insert(Monomial());
	for(size_t i = 1; i <= N; i++) {
		auto& polynomial = barPolynomials[i];
		for(size_t l = 1; l <= i && l <= k; l++) {
			auto& previousPolynomial = barPolynomials[i-l];
			for(const auto& previousMonomial : previousPolynomial.GetElements()) {
				auto monomial = Monomial(previousMonomial);
				monomial.MultiplyByVariable(l);
				polynomial.Insert(monomial);
			}
		}
		std::cout<<polynomial<<std::endl;
	}
	int m;
	std::cin>>m;
	return 0;
}
