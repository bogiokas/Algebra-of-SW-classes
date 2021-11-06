#pragma once
#include<array>
#include<set>
#include<cassert>

template<size_t K> std::array<size_t, K> CreateAscendingArrayOfFirstIntegers()
{
	std::array<size_t, K> result {};
	for(size_t i=0; i<K; ++i)
	{
		result[i] = i+1;
	}
	return result;
}

template<size_t K> std::array<size_t, K> CreateDescendingArrayOfFirstIntegers()
{
	std::array<size_t, K> result {};
	for(size_t i=0; i<K; ++i)
	{
		result[i] = K-i;
	}
	return result;
}

template <size_t K> class Permutation {
public:
	Permutation(bool ascending=true)
		: m_table(ascending? CreateAscendingArrayOfFirstIntegers<K>() : CreateDescendingArrayOfFirstIntegers<K>())
	{
	}

	Permutation(const std::array<size_t, K>& table)
		: m_table(table)
	{
		assert(IsValid());
	}
	
	template<typename... Args> Permutation(Args... args)
		: m_table{static_cast<size_t>(args)...}
	{
		assert(IsValid());
	}

	
	const size_t& operator[](size_t i) const {
		assert( i <= K && i > 0u );
		return m_table[i - 1];
	}

private:
	bool IsValid() const {
		for(size_t elt : m_table) {
			if(elt == 0 || elt > K) return false;
		}
		std::set<size_t> tempSet(m_table.begin(), m_table.end());
		if(tempSet.size() < K) return false;
		return true;
	}

	std::array<size_t, K> m_table;
};


template<size_t K> std::ostream& operator<< (std::ostream& out, const Permutation<K>& curr) {
	for( size_t i = 1; i < K; ++i) {
		out<<curr[i]<<"-";
	}
	out<<curr[K];
	return out;
}
