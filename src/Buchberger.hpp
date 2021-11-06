#pragma once
#include<vector>
#include<iostream>

#include "Polynomial.hpp"

template<size_t K, class Compare> class Buchberger {
public:
	Buchberger(Compare cmp, const std::vector<Polynomial<K>> basis)
		: m_cmp(cmp)
		, m_basis(basis)
		, m_basisPairs()
	{
		for(size_t i=0; i<m_basis.size(); ++i) {
			for(size_t j=i+1; j<m_basis.size(); ++j) {
				m_basisPairs.push_back({i,j}); //TODO: emplace_back
			}
		}
	}

	std::vector<Polynomial<K>> ComputeGroebnerBasis() {
		while(!m_basisPairs.empty()) {
			auto pair = m_basisPairs.back();
			m_basisPairs.pop_back();
			const auto S = CreateSyzygy(m_basis[pair[0]], m_basis[pair[1]]);
			const auto NF = NormalForm(S);
//Print();
//std::cout<<"f= "<<m_basis[pair[0]]<<std::endl;
//std::cout<<"g= "<<m_basis[pair[1]]<<std::endl;
//std::cout<<"S(f,g)= "<<S<<std::endl;
//std::cout<<"NF(S)= "<<NF<<std::endl;
			if(!NF.IsZero()) {
				size_t N = m_basis.size();
				m_basis.push_back(NF);
				for(size_t i=0; i<N; ++i) {
					m_basisPairs.push_back({i,N}); // TODO: emplace_back
				}
			}
		}
		return m_basis;
	}
	
	std::vector<Polynomial<K>> ComputeMinimalGroebnerBasis() {
		auto result = ComputeGroebnerBasis();
		for(size_t reverseI=result.size(); reverseI>0; --reverseI) {
			size_t i=reverseI-1;
			for(size_t j=0; j<result.size(); ++j) {
				if(i==j) continue;
				if(result[j].LeadingTerm(m_cmp).Divides(result[i].LeadingTerm(m_cmp))) {
					result.erase(result.begin() + i);
					break;
				}
			}
		}
		return result;
	}
	
	std::vector<Polynomial<K>> ComputeReducedGroebnerBasis() {
		
	}

private:
	Polynomial<K> CreateSyzygy(const Polynomial<K>& f, const Polynomial<K>& g) const {
		const auto ltF = f.LeadingTerm(m_cmp);
		const auto ltG = g.LeadingTerm(m_cmp);
		const auto& lcm = ltF.LeastCommonDivisor(ltG);
		return f * ( ltG / lcm ) + g * ( ltF / lcm );
	}

	Polynomial<K> NormalForm(const Polynomial<K>& f) const {
		Polynomial<K> result = f;
		bool reduced = true;
		while(reduced && !result.IsZero()) {
			const auto& ltResult = result.LeadingTerm(m_cmp);
			reduced = false;
			for( const auto& polynomial : m_basis ) {
				const auto& ltOther = polynomial.LeadingTerm(m_cmp);
				if(ltOther.Divides(ltResult)) {
					result.ReduceByMod(polynomial, m_cmp);
					reduced = true;
					break;
				}
			}
		}
		return result;
	}

	void Print() const {
		std::cout<<"Basis:"<<std::endl;
		for(const auto& polynomial : m_basis) {
			std::cout<<polynomial<<std::endl;
		}
	}
private:
	Compare m_cmp;
	std::vector<Polynomial<K>> m_basis;
	std::vector<std::array<size_t, 2>> m_basisPairs;
};
