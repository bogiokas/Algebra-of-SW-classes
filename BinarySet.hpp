#pragma once
#include<set>
#include <algorithm>
#include<iostream>

template<class Element> class BinarySet {
public:
	BinarySet() = default;

	void Insert(const Element& e) {
		auto it = m_elements.find(e);
		if(it != m_elements.end()) m_elements.erase(it);
		else m_elements.insert(e);
	}
	
	void Insert(Element&& e) {
		auto it = m_elements.find(e);
		if(it != m_elements.end()) m_elements.erase(it);
		else m_elements.insert(std::move(e));
	}
	
	bool IsEmpty() const {
		return m_elements.empty();
	}
	
	template<class Compare> const Element& GetMaxElement(Compare cmp) const {
		return *std::max_element(m_elements.cbegin(), m_elements.cend(), cmp);
	}
	
	const std::set<Element>& GetElements() const {
		return m_elements;
	}

	std::set<Element>& GetMutableElements() {
		return m_elements;
	}

private:
	std::set<Element> m_elements;
};
