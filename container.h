#ifndef CONTAINER_H
#define CONTAINER_H
#include "common.h"
class Container;
class DynamicArray;
class LinkedList;
class Container
{
public:

	virtual bool contains(const int& value)const = 0;
	virtual bool remove(const int& value) = 0;
	virtual bool removeAll() = 0;
	virtual bool append(std::initializer_list<int> list) = 0;
	virtual bool append(const int& value) = 0;
	virtual bool insert(const int& dest, const int& value, InsertDirection direction = InsertDirection::Backward) = 0;
	virtual bool insert(const int& dest, std::initializer_list<int> list, InsertDirection direction = InsertDirection::Backward) = 0;
	virtual int at(const unsigned int& index)const = 0;
	virtual unsigned int count()const = 0;
	
};
class DynamicArray: public Container
{
public:
	DynamicArray(const unsigned int& blockStep = 256, const unsigned int& blockCount = 1,
	             const bool& isAutoVariation = true) :
		m_autoVariation(isAutoVariation), m_count(0), m_blockCount(blockCount), m_blockStep(blockStep),
		m_array(new int[m_blockCount * m_blockStep])
	{
	}

	DynamicArray(std::initializer_list<int> list):
		m_autoVariation(true), m_count(list.size()), m_blockCount(static_cast<unsigned int>(ceil(static_cast<double>(list.size()) / 256))),
		m_blockStep(256), m_array(new int[m_blockCount * m_blockStep])
	{
		append(list);
	}
	
	
	~DynamicArray()
	{
		delete[] m_array;
	}
	friend std::ostream& operator<<(std::ostream& os, const DynamicArray& array)
	{
		os << "{ ";
		for (Iterator iter = array.begin(); iter != array.end(); iter.next())
		{
			if (iter == array.begin())
				os << iter.data();
			else
				os << ", " << iter.data();
		}
		os << " }";
		return os;
	}
	DynamicArray& operator=(const DynamicArray& array)
	{
		removeAll();
		append(array);
		return *this;
	}

	friend class Iterator;

	class Iterator
	{
	public:
		Iterator(int* pointer = nullptr): m_pointer(pointer)
		{
		}

		void next()
		{
			if ((m_pointer + 1) != nullptr)
				m_pointer++;
		}
		Iterator nextIterator()const
		{
			return m_pointer + 1;
		}
		int data() const
		{
			return *(m_pointer);
		}
		bool setData(const int& value)const
		{
			if (nullptr == m_pointer)
				return false;
			*m_pointer = value;
			return true;
		}
		bool operator!=(const Iterator& iterator) const
		{
			return m_pointer != iterator.m_pointer;
		}

		Iterator& operator=(Iterator* node)
		{
			this->m_pointer = node->m_pointer;
			return *this;
		}

		bool operator==(const Iterator& iter)const
		{
			return iter.m_pointer == this->m_pointer;
		}
	private:
		int* m_pointer;
	};

	Iterator begin() const
	{
		return m_array;
	}

	Iterator end() const
	{
		return m_array + m_count;
	}

	int& operator[](int index) const
	{
		return m_array[index];
	}
	int at(const unsigned int& index)const override
	{
		if (index < m_count)
			return m_array[index];
		else
			return INT32_MIN;
	}
	bool contains(const int& value) const override
	{
		for (unsigned int i = 0; i < m_count; i++)
			if (value == m_array[i])
				return true;
		return false;
	}

	bool remove(const int& value)override
	{
		for (int i = 0; i < m_count; i++)
		{
			if (value == m_array[i])
			{
				for (unsigned int j = i; j < m_count; j++)
					m_array[j] = m_array[j + 1];
				m_count--;
				if (m_autoVariation)
					vary();
				return true;
			}
		}
		return false;
	}

	bool append(const DynamicArray& array)
	{
		if (array.count() == 0)
			return false;

		for (Iterator iter = array.begin(); iter != array.end(); iter.next())
			append(iter.data());

		return true;
	}

	bool append(const int& value)override
	{
		m_count++;
		expand();
		m_array[m_count - 1] = value;
		return true;
	}

	bool append(std::initializer_list<int> list)override
	{
		if (list.size() == 0)
			return false;
		for (auto element : list)
			this->append(element);
		return true;
	}

	bool insert(const int& dest, std::initializer_list<int> list, InsertDirection direction = InsertDirection::Backward)override
	{
		if (list.size() == 0)
			return false;
		for (int i = 0; i < m_count; i++)
		{
			if (dest == m_array[i])
			{
				const int old = m_count;
				m_count += list.size();
				vary();
				for (int j = old - 1, k = m_count - 1; j >= i; j--, k--)
					m_array[k] = m_array[j];

				switch (direction)
				{
				case InsertDirection::Forward:
					i--;
					for (auto element : list)
					{
						m_array[++i] = element;
					}
					m_array[i + 1] = dest;
					break;
				case InsertDirection::Backward:
					i++;
					for (auto element : list)
						m_array[i++] = element;

					break;
				}
				return true;
			}
		}
		return false;
	}

	bool insert(const int& dest, const int& value, InsertDirection direction = InsertDirection::Backward)override
	{
		int pos = 0;
		for (int i = 0; i < m_count; i++)
		{
			if (dest == m_array[i])
			{
				m_count++;

				for (int j = m_count - 1; j >= i; j--)
					m_array[j] = m_array[j - 1];

				switch (direction)
				{
				case InsertDirection::Forward:
					m_array[i] = value;
					m_array[i + 1] = dest;
					break;
				case InsertDirection::Backward:
					m_array[i] = dest;
					m_array[i + 1] = value;
					break;
				}


				expand();
				return true;
			}
		}
		return false;
	}

	bool squeeze()
	{
		//squeeze container minimum condition
		if (m_blockCount * m_blockStep / 2 > m_count && m_blockCount > 2)
		{
			//suppose step = 256, blockCount = 5, m_count = 6
			//256 * 5 - 6
			adjust();
			return true;
		}
		return false;
	}

	unsigned int count() const override
	{
		return m_count;
	}

	void setAutoVariation(const bool& value)
	{
		m_autoVariation = value;
	}

	bool autoVariation() const
	{
		return m_autoVariation;
	}

	unsigned int blockCount() const
	{
		return m_blockCount;
	}

	unsigned int blockStep() const
	{
		return m_blockStep;
	}

	bool setArray(std::initializer_list<int> list)
	{
		if (list.size() == 0)
			removeAll();
		else
		{
			m_count = list.size();
			if (list.size() > m_blockStep * m_blockCount)
				adjust();

			int i = 0;
			for (auto element : list)
			{
				m_array[i] = element;
				i++;
			}
		}
		return true;
	}

	bool setArray(int array[] = nullptr, unsigned int count = 0)
	{
		if (nullptr != array && count > 0)
		{
			m_count = count;
			if (count > m_blockStep * m_blockCount)
				adjust();

			for (unsigned int i = 0; i < count; i++)
				m_array[i] = array[i];

			return true;
		}
		return false;
	}

	bool removeAll()override
	{
		m_count = 0;
		m_blockCount = 1;
		vary();
		return true;
	}

	bool clearAll()
	{
		if (m_count == 0)
			return false;
		for (unsigned int i = 0; i < m_count; i++)
			m_array[i] = INT32_MIN;
		m_count = 0;
		return true;
	}

	bool setBlockStep(const int& value)
	{
		if (value * m_blockCount < m_count)
			return false;
		m_blockStep = value;
		return true;
	}

	bool setBlockCount(const int& value)
	{
		if (value * m_blockStep < m_count)
			return false;
		m_blockCount = value;
		return true;
	}

private:
	bool adjust()
	{
		m_blockCount = static_cast<unsigned int>(ceil(static_cast<double>(m_count) / static_cast<double>(m_blockStep)));
		return vary();
	}

	bool expand()
	{
		//if the actual data block reaches the minimum condition..
		if (m_blockStep * m_blockCount * 0.75 < m_count)
		{
			m_blockCount++;
			vary();
			return true;
		}
		return false;
	}

	bool vary()
	{
		int* newArray = new int[m_blockCount * m_blockStep];
		if (m_count > 0)
			std::memcpy(newArray, m_array, sizeof(int) * m_count);
		delete[] m_array;
		m_array = newArray;
		return true;
	}

	bool m_autoVariation;
	unsigned int m_count;
	unsigned int m_blockCount;
	unsigned int m_blockStep;
	int* m_array;
};

class LinkedList : public Container
{
public:
	LinkedList() : m_isCircular(false), m_header(nullptr), m_tail(nullptr)
	{
	}

	LinkedList(std::initializer_list<int> list) : m_isCircular(false), m_header(nullptr), m_tail(nullptr)
	{
		append(list);
	}


	friend std::ostream& operator<<(std::ostream& os, const LinkedList& list)
	{
		os << "{ ";
		for (Iterator iter = list.begin(); iter != list.end(); iter.next())
		{
			if (iter == list.begin())
				os << iter.data();
			else
				os << ", " << iter.data();
		}
		os << " }";
		return os;
	}

	friend struct Node;
	friend class Iterator;

	~LinkedList()
	{
		removeAll();
	}

	struct Node
	{
		Node(const int& value) : data(value), previous(nullptr), next(nullptr)
		{
		}

		int data;
		Node* previous;
		Node* next;
	};

	class Iterator
	{
	public:
		Iterator(Node* node = nullptr) : m_node(node)
		{
		}

		int data() const { return m_node->data; }
		
		bool setData(const int& value)
		{
			if (nullptr == m_node)
				return false;
			m_node->data = value;
			return true;
		}
		Iterator& operator=(Node* node)
		{
			this->m_node = node;
			return *this;
		}
		bool operator==(const Iterator& iter)const
		{
			return iter.m_node == this->m_node;
		}
		Iterator operator++(int)
		{
			Iterator iterator = *this;
			++* this;
			return iterator;
		}
		Iterator nextIterator()const
		{
			return m_node->next;
		}
		Iterator& operator++()
		{
			m_node = m_node->next;
			return *this;
		}

		Iterator& operator--()
		{
			m_node = m_node->previous;
			return *this;
		}

		bool operator!=(const Iterator& iterator) const
		{
			return m_node != iterator.m_node;
		}

		void next()
		{
			m_node = m_node->next;
		}

		int operator*() const
		{
			return m_node->data;
		}

		bool isEmpty() const
		{
			return m_node == nullptr;
		}

	private:
		Node* m_node;
	};
	LinkedList& operator=(const LinkedList& list)
	{
		removeAll();
		append(list);
		return *this;
	}
	
	Iterator begin() const
	{
		return m_header;
	}

	Iterator end() const
	{
		return m_tail->next;
	}

	bool contains(const int& value)const override
	{
		Node* node = m_header;
		while ((nullptr != node && !m_isCircular) || (m_isCircular && node->next == m_header))
		{
			if (node->data == value)
				return true;
			node = node->next;
		}
		return false;
	}

	bool insert(const int& dest, std::initializer_list<int> list, InsertDirection direction = InsertDirection::Backward)override
	{
		if (list.size() == 0)
			return false;
		Node* i = m_header;
		while ((nullptr != i && !m_isCircular) || (m_isCircular && i->next == m_header))
		{
			if (i->data == dest)
			{
				Node* temp;
				for (auto element : list)
				{
					temp = new Node(element);
					insert(i, temp, direction);
					if (direction == InsertDirection::Backward)
						i = temp;
				}
				return true;
			}
			i = i->next;
		}
		return false;
		return false;
	}

	bool insert(const int& dest, const int& value, InsertDirection direction = InsertDirection::Backward)override
	{
		Node* i = m_header;
		while ((nullptr != i && !m_isCircular) || (m_isCircular && i->next == m_header))
		{
			if (i->data == dest)
				return insert(i, new Node(value), direction);
			i = i->next;
		}
		return false;
	}

	bool insert(Node* dest = nullptr, Node* src = nullptr, InsertDirection direction = InsertDirection::Backward)
	{
		if (nullptr == dest || nullptr == src)
			return false;
		switch (direction)
		{
		case InsertDirection::Forward:
			src->next = dest;
			src->previous = dest->previous;

			if (dest->previous == nullptr) //insert forward header
				m_header = src;
			else
				dest->previous->next = src;

			dest->previous = src;
			break;
		case InsertDirection::Backward:
			src->next = dest->next;
			src->previous = dest;

			if (dest->next == nullptr)
				m_tail = src;
			else
				dest->next->previous = src;

			dest->next = src;
			break;
		}
		return true;
	}

	bool remove(const int& value)override
	{
		Node* node = m_header;
		while ((nullptr != node && !m_isCircular) || (m_isCircular && node->next == m_header))
		{
			if (node->data == value)
			{
				if (node->next == nullptr && !m_isCircular) // remove tail
				{
					m_tail = node->previous;
					node->previous->next = nullptr;
					delete node;
					return true;
				}
				else if(node == m_header) //remove head
				{
					m_header = node->next;
					node->next->previous = nullptr;
					delete node;
					return true;
				}
				else
				{
					node->previous->next = node->next;
					node->next->previous = node->previous;
					delete node;
					return true;
				}
			}
			node = node->next;
		}
		return false;
	}

	bool append(const LinkedList& list)
	{
		if (list.count() == 0)
			return false;

		for (Iterator iter = list.begin(); iter != list.end(); iter.next())
			append(iter.data());

		return true;
	}

	bool append(const std::initializer_list<int> list)override
	{
		if (list.size() == 0)
			return false;
		for (auto element : list)
			this->append(element);
		return true;
	}

	bool append(const int& value)override
	{
		//empty list
		Node* node = new Node(value);
		if (nullptr == m_tail && nullptr == m_header)
		{
			m_header = node;
			m_tail = node;
			m_header->next = m_tail;
			m_tail->previous = m_header;
			m_header->previous = nullptr;
			m_tail->next = nullptr;
			return true;
		}
		m_tail->next = node;
		node->previous = m_tail;
		m_tail = node;
		return true;
	}
	
	int at(const unsigned int& index)const override
	{
		unsigned int i = 0;
		Node* node = m_header;
		while ((nullptr != node && !m_isCircular) || (m_isCircular && node->next == m_header))
		{
			if (index == i)
				return node->data;
			node = node->next;
			i++;
		}
		return INT32_MIN;
	}

	unsigned int count() const override
	{
		unsigned int count = 0;
		Node* node = m_header;
		while ((nullptr != node && !m_isCircular) || (m_isCircular && node->next == m_header))
		{
			node = node->next;
			count++;
		}
		return count;
	}

	bool removeAll() override
	{
		if (nullptr == m_header)
			return false;
		Node* node = m_header;
		while ((nullptr != node && !m_isCircular) || (m_isCircular && node->next == m_header))
		{
			Node* del = node;
			node = node->next;
			delete del;
		}
		m_header = m_tail = nullptr;
		return true;
	}
	
	bool circularize()
	{
		if (nullptr == m_header && nullptr == m_tail)
			return false;
		m_header->previous = m_tail;
		m_tail->next = m_header;
		m_isCircular = true;
		return true;
	}

	bool decircularize()
	{
		if (nullptr == m_header && nullptr == m_tail)
			return false;
		m_header->previous = nullptr;
		m_tail->next = nullptr;
		m_isCircular = false;
		return true;
	}

	bool isCircularized() const { return m_isCircular; }
private:
	bool m_isCircular;
	Node* m_header;
	Node* m_tail;
};
#endif
