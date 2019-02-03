#pragma once

#include <iostream>

namespace JWEngine
{
	static constexpr size_t not_specified = UINT32_MAX;
	
	template <typename T>
	class JWDynamicArray
	{
	public:
		JWDynamicArray()
		{
			m_pData = nullptr;
			m_Size = 0;
			m_Capacity = 0;
		};

		~JWDynamicArray()
		{
			m_Size = 0;
			DeleteArray();
		};

		auto size() const->size_t
		{
			return m_Size;
		}

		auto capacity() const->size_t
		{
			return m_Capacity;
		}

		// Empty all the elements, and reset the capacity
		void clear()
		{
			m_Size = 0;
			DeleteArray();

			NewArray(2);
		}

		// Empty all the elements, but the capacity remains as the same
		void empty()
		{
			m_Size = 0;

			if (m_pData)
			{
				memset(m_pData, 0, sizeof(T) * m_Capacity);
			}
		}

		// Push new value to the back of the dynamic array
		void push_back(T value)
		{
			if (!m_Capacity)
			{
				// Dynamic array not allocated yet
				// allocate for the first time the dynamic array with capacity = 2
				NewArray(2);
			}

			m_Size++;
			if (m_Size >= m_Capacity)
			{
				// First, set value
				m_pData[m_Size - 1] = value;

				// Dynamic array needs to be expanded
				// now save the current dynamic array's data
				size_t temp_capacity = m_Capacity;
				T* temp_p_data = nullptr;
				temp_p_data = new T[temp_capacity];
				memcpy(temp_p_data, m_pData, temp_capacity * sizeof(T));

				// Delete the current dynamic array
				DeleteArray();

				// Multiply the capacity by 2 for the expansion
				// of the newly allocated dynamic array
				NewArray(temp_capacity * 2);

				// Copy the saved data
				memcpy(m_pData, temp_p_data, temp_capacity * sizeof(T));
				delete[] temp_p_data;
			}
			else
			{
				// No need to expand the dynamic array, just set value
				m_pData[m_Size - 1] = value;
			}
		}

		// Pop(delete) the last element of the dynamic array
		// this doesn't change the capacity of the dynamic array
		void pop_back()
		{
			if (m_Size)
			{
				m_Size--;
				memset(m_pData + m_Size, 0, sizeof(T));
			}
		}

		// operator overloading
		T& operator[] (size_t index)
		{
			if (m_Size)
			{
				// Dynamic array has been allocated
				if (index > m_Size - 1)
				{
					index = m_Size - 1;
				}

				return m_pData[index];
			}
			else
			{
				// Dynamic array not allocated yet
				return nullptr;
			}
		}

	private:
		void NewArray(size_t Capacity)
		{
			if (!m_pData)
			{
				m_pData = new T[Capacity];
				memset(m_pData, 0, Capacity * sizeof(T));
				m_Capacity = Capacity;
			}
		}

		void DeleteArray()
		{
			if (m_pData)
			{
				delete[] m_pData;
				m_pData = nullptr;
				m_Capacity = 0;
			}
		}

	private:
		T* m_pData;
		size_t m_Size; // Current size of the array elements that have data
		size_t m_Capacity; // Current maximum size of the array
	};
};