#pragma once
#include<set>
#include<algorithm>

template<class Element> class BinarySet {
public:
	BinarySet()
		: m_elements()
	{}

	void Insert(const Element& e);
	void Insert(Element&& e);
	
	bool IsEmpty() const;
	template<class Compare> const Element& GetMaxElement(Compare cmp) const;
	
	const std::set<Element>& GetElements() const {
		return m_elements;
	}

private:
	std::set<Element> m_elements;
};


template<class Element> void BinarySet<Element>::Insert(const Element& e) {
	auto it = m_elements.find(e);
	if(it != m_elements.end()) m_elements.erase(it);
	else m_elements.insert(e);
}
	
template<class Element> void BinarySet<Element>::Insert(Element&& e) {
	auto it = m_elements.find(e);
	if(it != m_elements.end()) m_elements.erase(it);
	else m_elements.insert(std::move(e));
}

template<class Element> bool BinarySet<Element>::IsEmpty() const {
	return m_elements.empty();
}

template<class Element> template<class Compare> const Element& BinarySet<Element>::GetMaxElement(Compare cmp) const {
	return *std::max_element(m_elements.cbegin(), m_elements.cend(), cmp);
}
