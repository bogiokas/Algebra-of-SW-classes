#include<set>

template<class Element> class BinarySet {
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

private:
	std::set<Element> m_elements;
};
