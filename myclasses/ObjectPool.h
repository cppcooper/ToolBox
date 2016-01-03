#include <vector>
#include <iterator>
#include <algorithm>


using uint16 = unsigned short;

template<typename T>
class ObjectPool
{
private:
	std::vector<T> m_Array;
	uint16 m_Pos = 0;

public:
	virtual ObjectPool( uint16 poolSize ){
		m_Array = std::vector<T>( poolSize );
	}
	
	T Pop(){
		static T blank;
		if ( m_Pos >= m_Array.capacity() )
			return blank;
		return m_Array[m_Pos++];
	}

	void Push( T t ){
		std::vector<T>::iterator it = std::find( m_Array.begin(), m_Array.end(), t );
		if ( it != m_Array.end() ){
			if ( m_Pos == 0 )
				return;
			m_Array.swap( it, m_Array.begin() + --m_Pos );
		}
	}
};