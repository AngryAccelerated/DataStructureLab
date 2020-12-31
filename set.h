#ifndef SET_H
#define SET_H

#include "container.h"
template<class T = DynamicArray, class Iter = DynamicArray::Iterator>
class Set
{
public:
	Set() = default;
	Set(std::initializer_list<int> list)
	{
		m_container.append(list);
	}
    friend std::ostream& operator<<(std::ostream& os, const Set& set)
	{
		os << set.m_container;
		return os;
	}
	bool add(const int& value)
	{
		if (!m_container.contains(value))
			m_container.append(value);
		return true;
	}
	bool insert(const int& dest, const int& source)
	{
		if (!m_container.contains(source))
			m_container.insert(dest, source);
		return true;
	}
	bool remove(const int& value)
	{
		return m_container.remove(value);
	}
	bool removeAll()
	{
		return m_container.removeAll();
	}
	static bool Intersection(const Set& set1, const Set& set2, Set& result)
	{
		if (set1.m_container.count() == 0 || set2.m_container.count() == 0 || result.m_container.count() != 0)
			return false;
		set1.sort();
		set2.sort();
		for (Iter iterA = set1.m_container.begin(), iterB = set2.m_container.begin(); iterA != set1.m_container.end() && iterB != set2.m_container.end();)
		{
			int diff = iterA.data() - iterB.data();
			if (diff == 0)
			{
				result.m_container.append(iterA.data());
				iterB.next();
				iterA.next();
			}
			else if (diff > 0)
				iterB.next();
			else
				iterA.next();
		}

		return true;
	}
	//result = lhs - rhs
	static bool Difference(const Set& lhs, const Set& rhs, Set& result)
	{
		if (lhs.m_container.count() == 0 || rhs.m_container.count() == 0 || result.m_container.count() != 0)
			return false;

		result = lhs;
		
		Set intersection;
		Intersection(lhs, rhs, intersection);
		for (Iter iter = intersection.m_container.begin();  iter != intersection.m_container.end(); iter.next())
			result.remove(iter.data());
		return true;
	}

	static bool Union(const Set& set1, const Set& set2, Set& result)
	{
		if (set1.m_container.count() == 0 || set2.m_container.count() == 0 || result.m_container.count() != 0)
			return false;
		for (Iter iterA = set1.m_container.begin(); iterA != set1.m_container.end(); iterA.next())
			result.m_container.append(iterA.data());

		for (Iter iterB = set2.m_container.begin(); iterB != set2.m_container.end(); iterB.next())
			result.m_container.append(iterB.data());
		
		Set intersection;
		Intersection(set1, set2, intersection);
		for (Iter iter = intersection.m_container.begin(); iter != intersection.m_container.end(); iter.next())
			result.remove(iter.data());

		result.sort();
		return true;
	}
	Set& intersect(const Set& set)
	{
		Set result;
		Intersection(*this, set, result);
		*this = result;
		return *this;
	}
	Set& subtract(const Set& set)
	{
		Difference(*this, set, *this);
		return *this;
	}
	Set& unite(const Set& set)
	{
		Set result;
		Union(*this, set, result);
		*this = result;
		return *this;
	} 

	Set& operator=(const Set& set)
	{
		m_container = set.m_container;
		return *this;
	}

	bool sort()const
	{
		if (m_container.count() == 0)
			return false;
		for (Iter iter = m_container.begin(); iter != m_container.end(); iter.next())
		{
			for (Iter iterInner = iter.nextIterator(); iterInner != m_container.end(); iterInner.next())
			{
				if (iter.data() > iterInner.data())
				{
					int temp = iter.data();
					iter.setData(iterInner.data());
					iterInner.setData(temp);
				}
			}
		}
		return true;
	}
private:
	T m_container;
};
#endif
