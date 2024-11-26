#include"EnemySegment.hpp"

template<typename temp>
inline enemySegment<temp>::enemySegment()
{
	m_array = nullptr;
	m_top = -1;
	m_size = 0;
}

template<typename temp>
enemySegment<temp>::enemySegment(short int size)
{
	m_array = new temp[size];
	m_top = -1;
	m_size = size;
}

template<typename temp>
inline enemySegment<temp>::enemySegment(const enemySegment& e)
{
	this->m_top = e.m_top;
	this->m_size = e.m_size;
	for (int i = 0; i < e.m_size; i++)
	{
		this[i] = e[i];
	}
}

template<typename temp>
inline void enemySegment<temp>::render() const
{
}

template<typename temp>
inline void enemySegment<temp>::updates()
{

}

template<typename temp>
inline temp& enemySegment<temp>::operator[](int index) const
{
	return m_array[index];
}