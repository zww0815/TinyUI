#pragma once
#include "TinyCollection.h"
#include <memory>

namespace TinyUI
{
	template<typename R>
	class FunctorBase
	{
	public:
		typedef R				ReturnType;
		typedef FunctorBase<R>	SelfType;
	public:
		virtual const void *Target() const = 0;
		virtual const type_info& TargetType() const = 0;
		virtual FunctorBase* DoClone() const = 0;
		virtual BOOL operator==(const FunctorBase&) const = 0;
		virtual ~FunctorBase() NOEXCEPT
		{
		};
	public:
		template <class U>
		static U* Clone(U* pObj)
		{
			if (!pObj) return 0;
			U* pClone = static_cast<U*>(pObj->DoClone());
			assert(typeid(*pClone) == typeid(*pObj));
			return pClone;
		}
	};
	//////////////////////////////////////////////////////////////////////////
	template<typename R>
	class Functor;
	template<typename R, typename... Args>
	class Functor<R(Args...)> : public FunctorBase < R >
	{
	public:
		typedef R	ReturnType;
		virtual R	operator()(Args...) = 0;
	};
	//////////////////////////////////////////////////////////////////////////
	template<typename R, typename FunctionType, typename... Args>
	class UnaryFunctor : public Functor < R(Args...) >
	{
	public:
		typedef R					ReturnType;
		typedef Functor<R(Args...)> FunctorType;
	public:
		UnaryFunctor(const FunctionType& fType)
			: m_fType(fType)
		{
		}
		UnaryFunctor(const UnaryFunctor& other)
			:m_fType(other.m_fType)
		{
		}
		UnaryFunctor& operator = (const UnaryFunctor& other)
		{
			if (&other != this)
			{
				m_fType = other.m_fType;
			}
			return *this;
		}
		UnaryFunctor* DoClone() const override
		{
			return new UnaryFunctor(*this);
		}
		const void *Target() const override
		{
			return m_fType != NULL ? reinterpret_cast<const void*>(m_fType) : NULL;
		}
		const type_info& TargetType() const override
		{
			return m_fType != NULL ? typeid(m_fType) : typeid(void);
		}
	public:
		BOOL operator==(const typename FunctorType::SelfType& fType) const
		{
			if (typeid(*this) != typeid(fType))
			{
				return FALSE;
			}
			const UnaryFunctor& s = static_cast<const UnaryFunctor&>(fType);
			return  m_fType == s.m_fType;
		}
		ReturnType operator()(Args... args)
		{
			return m_fType(args...);
		}
	private:
		FunctionType m_fType;
	};
	//////////////////////////////////////////////////////////////////////////
	template <typename R, typename InstanceType, typename FunctionType, typename... Args>
	class BinaryFunctor : public Functor < R(Args...) >
	{
	public:
		typedef R					ReturnType;
		typedef Functor<R(Args...)> FunctorType;
	public:
		BinaryFunctor(const InstanceType& iType, const FunctionType& fType)
			: m_iType(iType), m_fType(fType)

		{
		}
		BinaryFunctor(const BinaryFunctor& other)
			:m_iType(other.m_iType), m_fType(other.m_fType)
		{
		}
		BinaryFunctor& operator = (const BinaryFunctor& other)
		{
			if (&other != this)
			{
				m_fType = other.m_fType;
				m_iType = other.m_iType;
			}
			return *this;
		}
		BinaryFunctor* DoClone() const override
		{
			return new BinaryFunctor(*this);
		}

		const void *Target() const override
		{
			return m_fType != NULL ? reinterpret_cast<const void*>(&m_fType) : NULL;
		}
		const type_info& TargetType() const override
		{
			return m_fType != NULL ? typeid(m_fType) : typeid(void);
		}
	public:
		BOOL operator==(const typename FunctorType::SelfType& fType) const
		{
			if (typeid(*this) != typeid(fType))
			{
				return FALSE;
			}
			const BinaryFunctor& s = static_cast<const BinaryFunctor&>(fType);
			return  m_iType == s.m_iType && m_fType == s.m_fType;
		}
		ReturnType operator()(Args... args)
		{
			return ((*m_iType).*m_fType)(args...);
		}
	private:
		InstanceType	m_iType;
		FunctionType	m_fType;
	};
	//////////////////////////////////////////////////////////////////////////
	template <typename R, typename...Args>
	class DelegateBase
	{
	public:
		typedef R					ReturnType;
		typedef Functor<R(Args...)>	FunctorType;
	public:
		DelegateBase()
			:m_my(NULL)
		{

		}
		DelegateBase(const DelegateBase& db)
			:m_my(FunctorType::Clone(db.m_my.Ptr()))
		{
		}
		DelegateBase& operator=(const DelegateBase& other)
		{
			if (&other != this)
			{
				DelegateBase copy(other);
				FunctorType* ps = m_my.Release();
				m_my.Reset(copy.m_my.Release());
				copy.m_my.Reset(ps);
			}
			return *this;
		}
		template <typename FunctionType>
		DelegateBase(const FunctionType& fType)
			: m_my(new UnaryFunctor<R, FunctionType, Args...>(fType))
		{

		}
		template <class InstanceType, typename FunctionType>
		DelegateBase(const InstanceType& iType, FunctionType mType)
			: m_my(new BinaryFunctor<R, InstanceType, FunctionType, Args...>(iType, mType))
		{

		}
		template <typename FunctionType>
		void BindDelegate(const FunctionType& fType)
		{
			m_my.Reset(new UnaryFunctor<R, FunctionType, Args...>(fType));
		}
		template <class InstanceType, typename FunctionType>
		void BindDelegate(const InstanceType& iType, FunctionType mType)
		{
			m_my.Reset(new BinaryFunctor<R, InstanceType, FunctionType, Args...>(iType, mType));
		}
		BOOL IsEmpty() const
		{
			return m_my.Ptr() == NULL;
		}
		void Release()
		{
			m_my.Reset(NULL);
		}
		const void *Target() const
		{
			return m_my->Target();
		}
		const type_info& TargetType() const
		{
			return m_my->TargetType();
		}
	public:
		BOOL operator==(const DelegateBase& other) const
		{
			if (m_my.Ptr() == NULL && other.m_my.Ptr() == NULL)
			{
				return TRUE;
			}
			if (m_my.Ptr() != NULL && other.m_my.Ptr() != NULL)
			{
				return (*m_my.Ptr()) == *(other.m_my.Ptr());
			}
			return FALSE;
		}
		BOOL operator!=(const DelegateBase& other) const
		{
			return !(*this == other);
		}
		ReturnType operator()(Args... args) const
		{
			return (*m_my)(args...);
		}
	private:
		TinyAutoPtr<FunctorType>	m_my;
	};
	//////////////////////////////////////////////////////////////////////////
	template<typename R>
	class Delegate;
	template<typename R, typename... Args>
	class Delegate<R(Args...)> : public DelegateBase < R, Args... >
	{
	public:
		typedef DelegateBase<R, Args... > BaseType;
	protected:
		Delegate() : BaseType(){}
	public:
		Delegate(const Delegate& os) : BaseType()
		{
			if (!os.IsEmpty())
			{
				BaseType::operator=(os);
			}
		}
		template<class FunctionType>
		Delegate(const FunctionType& fType) : BaseType(fType)
		{
			BaseType::BindDelegate(fType);
		}
		template<class InstanceType, class FunctionType>
		Delegate(const InstanceType& iType, const FunctionType& fType) : BaseType(iType, fType)
		{
			BaseType::BindDelegate(iType, fType);
		}
	};
};

