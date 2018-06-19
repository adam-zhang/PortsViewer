#ifndef __SINGLETON__H
#define __SINGLETON__H
//#include "CriticalSection.h"
#include <memory>

class FakeLocker
{
	public:
		void lock() {}
		void unlock() {}
};

//class RealLocker
//{
//	private:
//		CriticalSection mtx;
//	public:
//		void lock()
//		{
//			mtx.Lock();
//		}

//		void unlock() 
//		{
//			mtx.Unlock();
//		}
//};

template<typename T, typename LOCKER = FakeLocker>
class Singleton
{
	private:
		static std::shared_ptr<T> instance_;
		static LOCKER locker_;
	public:
		static T& instance()
		{
			if (!instance_)
			{
				locker_.lock();
				if (!instance_)
					instance_ = std::make_shared<T>();
				locker_.unlock();
			}
			return *instance_;
		}
};

template<typename T, typename LOCKER>
std::shared_ptr<T> Singleton<T, LOCKER>::instance_ = 0;

template<typename T, typename LOCKER>
LOCKER Singleton<T, LOCKER>::locker_;

#endif//__SINGLETON__H
