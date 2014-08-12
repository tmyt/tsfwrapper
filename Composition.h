#pragma once

#define prop(__type, __name) \
	private: \
	__type m_##__name; \
	public: \
	property __type __name { \
	__type get() { return m_##__name; } \
	void set(__type value) { m_##__name = value; } \
																																																																}

#define propr(__type, __name) \
	private: \
	__type m_##__name; \
	public: \
	property __type __name { \
	__type get() { return m_##__name; } \
																																																																}

#include <Windows.h>
#include <atlcomcli.h>
#include <msctf.h>

namespace TextServiceFramework
{
	public ref class Composition sealed
	{
	private:
		static Composition^ instance;

		CComQIPtr<ITfThreadMgr2> mgr;

		bool getIsInComposition();

		template<typename T, typename U>
		std::vector<CComQIPtr<T>> convertToVector(U* enumInterface)
		{
			ULONG fetched;
			std::vector<CComQIPtr<T>> ret;
			while (1){
				T* obj;
				enumInterface->Next(1, &obj, &fetched);
				if (fetched == 0) break;
				ret.push_back(CComQIPtr<T>(obj));
			}
			return ret;
		}

		Composition();

	public:

		static property Composition^ Instance {
			Composition^ get() {
				if (instance) return instance;
				return (instance = ref new Composition());
			}
		}

		property bool IsInComposition {
			bool get() { return getIsInComposition(); }
		}
	};
}