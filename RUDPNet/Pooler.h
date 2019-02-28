#ifndef _POOLER_H_
#define _POOLER_H_

#include <deque>
#include <set>

using std::deque;
using std::set;



/*! 특정 자료형에 대해서 메모리를 미리 생성함
*  
*  @Version  2007. 5. 23
*
*  이호규
*/


template<typename Object>
class  Pooler
{
public:
	typedef	Object		AObject;

private:
	unsigned long	m_dwIncreaseNum;

	deque<AObject*>	m_dequePooler;
	set<AObject*>	m_setRelease;


public:
	Pooler();
	virtual ~Pooler();

	//! 초기화
	bool   Initialize( unsigned long dwInitNum , unsigned long dwIncreaseNum);

	//! 해제
	void    UnInitialize();	

	//! 얻기 , 반환
	Object* Acquire();
	void    Release( AObject* pObject);


protected:
	//! Pooler에 담을 Object 생성
	Object* CreateObject();

};


template<typename Object>
Pooler<Object>::Pooler():
m_dwIncreaseNum(0)
{

}


template<typename Object>
Pooler<Object>::~Pooler()
{
	//! UnInitialize이 호출 안 되었을 떄
	UnInitialize();
}


//! 등록된 Factory object는 Pooler 소멸자에서 delete 해준다.
template<typename Object>
bool   
Pooler<Object>::Initialize( unsigned long dwInitNum , unsigned long dwIncreaseNum )
{	
	bool bResult = false;	

	if( m_dequePooler.empty() )
	{
		m_dwIncreaseNum =	dwIncreaseNum;		

		//! 객체 생성
		for(unsigned int nIndex = 0 ; nIndex < dwInitNum ; nIndex++)
		{
			AObject* pObject = CreateObject();	
			m_dequePooler.push_back(pObject);
		}

		bResult = true;
	}

	return bResult;
}

template<typename Object>
void    
Pooler<Object>::UnInitialize()
{
	//! Pool안의 pObject 삭제
	if( !m_dequePooler.empty() )
	{
		deque<AObject*>::iterator where = m_dequePooler.begin();
		while( where != m_dequePooler.end() )
		{
			delete *where;
			where++;
		}

		m_dequePooler.clear();
	}

	//! Release 목록안의 Object 삭제
	if( !m_setRelease.empty())
	{
		set<AObject*>::iterator where = m_setRelease.begin();
		while( where != m_setRelease.end() )
		{
			delete *where;
			where++;
		}

		m_setRelease.clear();
	}
}


//! Pooler에 담을 Object 생성
template<typename Object>
Object*
Pooler<Object>::CreateObject()
{
	return new AObject;
}

template<typename Object>
Object*
Pooler<Object>::Acquire()
{   	
	AObject* pResult = NULL;

	//! 메모리 부족
	if( m_dequePooler.empty())
	{	
		//! 객체 생성
		for(unsigned int nIndex = 0 ; nIndex < m_dwIncreaseNum ; nIndex++)
		{
			AObject* pObject = CreateObject();	
			m_dequePooler.push_back(pObject);
		}
	}	

	//! 메모리 얻기
	pResult = m_dequePooler.front();
	m_dequePooler.pop_front();

	//! Release 목록에 담기
	m_setRelease.insert(pResult);

	return pResult;		
}


template<typename Object>
void
Pooler<Object>::Release( AObject* pObject)
{
	if( !m_setRelease.empty() )
	{
		//! Release 목록에서 삭제
		set<AObject*>::iterator where = m_setRelease.find(pObject);
		if( where != m_setRelease.end())
		{
			m_setRelease.erase(where);

			//! 메모리 pooler에 저장하기
			pObject->Reset();
			m_dequePooler.push_back(pObject);
		}		
	}	
}






#endif
