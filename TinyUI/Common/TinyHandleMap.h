#pragma once
#include "TinyWindowMsg.h"
#include "TinyCollection.h"

namespace TinyUI
{
	/// <summary>
	/// ���ӳ����
	/// </summary>
	template<class T = HANDLE, class V = void*>
	class TinyHandleMap
	{
		DISALLOW_COPY_AND_ASSIGN(TinyHandleMap)
	public:
		TinyHandleMap();
		~TinyHandleMap();
		V* Lookup(T& _key);
		V* Lookup(const T& _key) const;
		V* operator[](T& _key);
		V* operator[](const T& _key) const;
		void Add(const T& _key, const V& _value);
		void Remove(const T& _key);
		void RemoveAll();
		INT GetSize() const;
	private:
		TinySimpleMap<T, V> m_handleMap;
	};
	template<class T, class V>
	TinyHandleMap<T, V>::TinyHandleMap()
	{

	}
	template<class T, class V>
	TinyHandleMap<T, V>::~TinyHandleMap()
	{
		m_handleMap.RemoveAll();
	}
	template<class T, class V>
	V* TinyHandleMap<T, V>::Lookup(T& _key)
	{
		return m_handleMap.Lookup(_key);
	}
	template<class T, class V>
	V* TinyHandleMap<T, V>::Lookup(const T& _key) const
	{
		return m_handleMap.Lookup(_key);
	}
	template<class T, class V>
	V* TinyHandleMap<T, V>::operator[](T& _key)
	{
		return m_handleMap.GetValue(_key);
	}
	template<class T, class V>
	V* TinyHandleMap<T, V>::operator[](const T& _key) const
	{
		return m_handleMap.GetValue(_key);
	}
	template<class T, class V>
	void TinyHandleMap<T, V>::Add(const T& _key, const V& _value)
	{
		m_handleMap.Add(_key, _value);
	}
	template<class T, class V>
	void TinyHandleMap<T, V>::Remove(const T& _key)
	{
		m_handleMap.Remove(_key);
	}
	template<class T, class V>
	void TinyHandleMap<T, V>::RemoveAll()
	{
		m_handleMap.RemoveAll();
	}
	template<class T, class V>
	INT TinyHandleMap<T, V>::GetSize() const
	{
		return m_handleMap.GetSize();
	}

	/// <summary>
	/// ���ھ����
	/// </summary>
	class TinyHandleHWND :public TinyWindowMsg, public TinyMessageFilter
	{
	public:
		TinyHandleHWND();
		~TinyHandleHWND();
		operator HWND() const;
		HWND Handle() const;
		BOOL operator==(const TinyHandleHWND& obj) const;
		BOOL operator!=(const TinyHandleHWND& obj) const;
		BOOL Attach(HWND hWND);
		HWND Detach();
		static TinyHandleHWND* Lookup(HWND hWND);
	public:
		HWND m_hWND;
	};

	template<typename T, typename Traits>
	class TinyGenericHandle
	{
	public:
		TinyGenericHandle();
		~TinyGenericHandle();
		operator T() const;
		T Handle() const;
		BOOL operator==(const TinyGenericHandle& obj) const;
		BOOL operator!=(const TinyGenericHandle& obj) const;
		BOOL Attach(T myT);
		T Detach();
		static TinyGenericHandle* Lookup(T myT);
	public:
		T m_myT;
	};
	template<typename T, typename Traits>
	TinyGenericHandle<T, Traits>::TinyGenericHandle()
		:m_myT(NULL)
	{

	}
	template<typename T, typename Traits>
	TinyGenericHandle<T, Traits>::operator T() const
	{
		return m_myT == NULL ? NULL : m_myT;
	}
	template<typename T, typename Traits>
	T TinyGenericHandle<T, Traits>::Handle() const
	{
		return m_myT == NULL ? NULL : m_myT;
	}
	template<typename T, typename Traits>
	BOOL TinyGenericHandle<T, Traits>::operator == (const TinyGenericHandle<T, Traits>& obj) const
	{
		return obj.m_myT == m_myT;
	}
	template<typename T, typename Traits>
	BOOL TinyGenericHandle<T, Traits>::operator != (const TinyGenericHandle<T, Traits>& obj) const
	{
		return obj.m_myT != m_myT;
	}
	template<typename T, typename Traits>
	BOOL TinyGenericHandle<T, Traits>::Attach(T myT)
	{
		if (myT == NULL)
		{
			return FALSE;
		}
		m_myT = myT;
		return Traits::Attach(this);
	}
	template<typename T, typename Traits>
	T TinyGenericHandle<T, Traits>::Detach()
	{
		T myT = m_myT;
		if (myT != NULL)
		{
			Traits::Detach(myT);
		}
		m_myT = NULL;
		return myT;
	}
	template<typename T, typename Traits>
	typename TinyGenericHandle<T, Traits>* TinyGenericHandle<T, Traits>::Lookup(T myT)
	{
		return Traits::Lookup(myT);
	}
	/// <summary>
	/// �˵������
	/// </summary>
	class TinyHandleHMENU
	{
	public:
		TinyHandleHMENU();
		~TinyHandleHMENU();
		operator HMENU() const;
		HMENU Handle() const;
		BOOL operator==(const TinyHandleHMENU& obj) const;
		BOOL operator!=(const TinyHandleHMENU& obj) const;
		BOOL Attach(HMENU hMENU);
		HMENU Detach();
		static TinyHandleHMENU* Lookup(HMENU hMENU);
	public:
		HMENU m_hMENU;
	};
	/// <summary>
	/// DC�����
	/// </summary>
	class TinyHandleHDC
	{
	public:
		TinyHandleHDC();
		~TinyHandleHDC();
		operator HDC() const;
		HDC Handle() const;
		BOOL operator==(const TinyHandleHDC& obj) const;
		BOOL operator!=(const TinyHandleHDC& obj) const;
		BOOL Attach(HDC hDC);
		HDC Detach();
		static TinyHandleHDC* Lookup(HDC hDC);
	public:
		HDC m_hDC;
	};
	/// <summary>
	/// BITMAP�����
	/// </summary>
	class TinyHandleHBITMAP
	{
	public:
		TinyHandleHBITMAP();
		~TinyHandleHBITMAP();
		operator HBITMAP() const;
		HBITMAP Handle() const;
		BOOL operator==(const TinyHandleHBITMAP& obj) const;
		BOOL operator!=(const TinyHandleHBITMAP& obj) const;
		BOOL Attach(HBITMAP hBITMAP);
		HBITMAP Detach();
		static TinyHandleHBITMAP* Lookup(HBITMAP hBITMAP);
	public:
		HBITMAP m_hBITMAP;
	};
	/// <summary>
	/// FONT�����
	/// </summary>
	class TinyHandleHFONT
	{
	public:
		TinyHandleHFONT();
		~TinyHandleHFONT();
		operator HFONT() const;
		HFONT Handle() const;
		BOOL operator==(const TinyHandleHFONT& obj) const;
		BOOL operator!=(const TinyHandleHFONT& obj) const;
		BOOL Attach(HFONT hFONT);
		HFONT Detach();
		static TinyHandleHFONT* Lookup(HFONT hFONT);
	public:
		HFONT m_hFONT;
	};
	/// <summary>
	/// PEN�����
	/// </summary>
	class TinyHandleHPEN
	{
	public:
		TinyHandleHPEN();
		~TinyHandleHPEN();
		operator HPEN() const;
		HPEN Handle() const;
		BOOL operator==(const TinyHandleHPEN& obj) const;
		BOOL operator!=(const TinyHandleHPEN& obj) const;
		BOOL Attach(HPEN hPEN);
		HPEN Detach();
		static TinyHandleHPEN* Lookup(HPEN hPEN);
	public:
		HPEN m_hPEN;
	};
	/// <summary>
	/// BRUSH�����
	/// </summary>
	class TinyHandleHBRUSH
	{
	public:
		TinyHandleHBRUSH();
		~TinyHandleHBRUSH();
		operator HBRUSH() const;
		HBRUSH Handle() const;
		BOOL operator==(const TinyHandleHBRUSH& obj) const;
		BOOL operator!=(const TinyHandleHBRUSH& obj) const;
		BOOL Attach(HBRUSH hBRUSH);
		HBRUSH Detach();
		static TinyHandleHBRUSH* Lookup(HBRUSH hBRUSH);
	public:
		HBRUSH m_hBRUSH;
	};
	/// <summary>
	/// PALETTE�����
	/// </summary>
	class TinyHandleHPALETTE
	{
	public:
		TinyHandleHPALETTE();
		~TinyHandleHPALETTE();
		operator HPALETTE() const;
		HPALETTE Handle() const;
		BOOL operator==(const TinyHandleHPALETTE& obj) const;
		BOOL operator!=(const TinyHandleHPALETTE& obj) const;
		BOOL Attach(HPALETTE hPALETTE);
		HPALETTE Detach();
		static TinyHandleHPALETTE* Lookup(HPALETTE hPALETTE);
	public:
		HPALETTE m_hPALETTE;
	};
	/// <summary>
	/// RGN�����
	/// </summary>
	class TinyHandleHRGN
	{
	public:
		TinyHandleHRGN();
		~TinyHandleHRGN();
		operator HRGN() const;
		HRGN Handle() const;
		BOOL operator==(const TinyHandleHRGN& obj) const;
		BOOL operator!=(const TinyHandleHRGN& obj) const;
		BOOL Attach(HRGN hHRGN);
		HRGN Detach();
		static TinyHandleHRGN* Lookup(HRGN hHRGN);
	public:
		HRGN m_hHRGN;
	};
	/// <summary>
	/// IMAGELIST�����
	/// </summary>
	class TinyHandleHIMAGELIST
	{
	public:
		TinyHandleHIMAGELIST();
		~TinyHandleHIMAGELIST();
		operator HIMAGELIST() const;
		HIMAGELIST Handle() const;
		BOOL operator==(const TinyHandleHIMAGELIST& obj) const;
		BOOL operator!=(const TinyHandleHIMAGELIST& obj) const;
		BOOL Attach(HIMAGELIST hIMAGELIST);
		HIMAGELIST Detach();
		static TinyHandleHIMAGELIST* Lookup(HIMAGELIST hIMAGELIST);
	public:
		HIMAGELIST m_hIMAGELIST;
	};
}

