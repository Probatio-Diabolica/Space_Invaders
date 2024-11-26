#include"BulletList.hpp"
#include<iostream>

static void swap(Bullet* a, Bullet* b)
{
	Bullet temp = *a;
	*a = *b;
	*b = temp;
}

bulletList::bulletList()
{
    m_size = 0;
    m_top = -1;
    m_array = nullptr;
}
bulletList::bulletList(const bulletList& other)
{
    // Ok here We are :: first set everything to safe initial values, I don't want pesky Segmentation fault/wierd exceptions that may haunt me for no reasons
    m_array = nullptr;
    m_size = 0;
    m_top = -1;

    try {
        // Only if other has valid data
        if (other.m_array != nullptr && other.m_size > 0) {
            m_array = new Bullet[other.m_size];  // Allocate new memory
            m_size = other.m_size;
            m_top = other.m_top;

            // Copy only valid elements (0 to top)
            if (m_top >= 0 && m_top < m_size) {  // Bounds check
                for (int i = 0; i <= m_top; i++) {
                    if (i < m_size) {  // Extra safety check
                        m_array[i] = other.m_array[i];
                    }
                }
            }
        }
    }
    catch (...) {
        // If anything goes wrong, clean up
        if (m_array != nullptr) {
            delete[] m_array;
            m_array = nullptr;
        }
        m_size = 0;
        m_top = -1;
        throw;  // Re-throw the exception
    }

}
bulletList::bulletList(int size) : m_size(size)
{
	m_array = new Bullet[size];
	m_top = -1;
}

bulletList::~bulletList()
{
	if (m_array != nullptr) {  // Check before deletion
		delete[] m_array;
		m_array = nullptr;  // Prevent use after delete
	}
}

int bulletList::getTop() const
{
	return m_top;
}


void bulletList::push(Bullet item)
{
	if(m_top+1 <m_size)m_array[++m_top] = item;
}

//Maybe I'll remove it if I don't feel anything good about it
void bulletList::update()
{
	for (int i = 0; i <= m_top; i++)
	{
		m_array[i].Update();
        if ((!m_array[i].IsActive()))  swap(&m_array[i], &m_array[m_top--]);
	}
}

void bulletList::render()
{
	for (int i = 0; i <= m_top; i++) m_array[i].Draw();
}

void bulletList::reset()
{
    m_top = -1;
}

Bullet& bulletList::operator[](int index)
{
	return m_array[index];
}

bulletList& bulletList::operator=(const bulletList& other)
{
    if (this != &other) {  // Prevent self-assignment
        // Delete old array
        if (m_array != nullptr) {
            delete[] m_array;
        }
        // Copy new data
        m_size = other.m_size;
        m_top = other.m_top;
        m_array = new Bullet[m_size];
        for (int i = 0; i <= m_top; i++) {
            m_array[i] = other.m_array[i];
        }
    }
    return *this;
}

//void bulletList::m_shuffle()
//{
//	if (m_top > 1)
//	{
//		for (int i = 0; i <= m_top; i++)
//		{
//			if (!m_array[i].IsActive()) swap(&m_array[i], &m_array[m_top--]);
//		}
//	}
//	
//}
