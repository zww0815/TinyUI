#include "../stdafx.h"
#include "../Common/TinyUtility.h"
#include "TinyIOServer.h"
#include "TinyTCPServer.h"
#include <process.h>

namespace TinyUI
{
	namespace Network
	{
		TinyIOTask::TinyIOTask(IO::TinyIOCP* ps)
			:m_pIOCP(ps)
		{

		}
		TinyIOTask::~TinyIOTask()
		{

		}
		BOOL TinyIOTask::Close(DWORD dwMs)
		{
			ASSERT(m_pIOCP);
			PostQueuedCompletionStatus(m_pIOCP->Handle(), 0, 0, NULL);
			m_close.SetEvent();
			return TinyTaskBase::Close(dwMs);
		}
		BOOL TinyIOTask::Submit()
		{
			m_close.CreateEvent(FALSE, FALSE, GenerateGUID().c_str(), NULL);
			Closure s = BindCallback(&TinyIOTask::OnMessagePump, this);
			return TinyTaskBase::Submit(s);
		}
		void TinyIOTask::OnMessagePump()
		{
			ASSERT(m_pIOCP);
			ULONG_PTR completionKey = 0;
			for (;;)
			{
				if (m_close.Lock(0))
				{
					break;
				}
				DWORD dwNumberOfBytesTransferred = 0;
				LPOVERLAPPED lpOP = NULL;
				if (!GetQueuedCompletionStatus(m_pIOCP->Handle(), &dwNumberOfBytesTransferred, &completionKey, &lpOP, INFINITE))
					continue;
				if (lpOP == NULL)
					break;
				PER_IO_CONTEXT* context = static_cast<PER_IO_CONTEXT*>(lpOP);
				if (dwNumberOfBytesTransferred == 0 && context->OP >= OP_RECV)
				{
					SAFE_DELETE(context);
					break;
				}
				switch (context->OP)
				{
				case OP_ACCEPT:
				{
					SOCKET listen = static_cast<SOCKET>(completionKey);
					TinySocket* scoekt = reinterpret_cast<TinySocket*>(context->Key);
					if (scoekt)
					{
						DWORD dwError = 0;
						if (setsockopt(scoekt->Handle(), SOL_SOCKET, SO_UPDATE_ACCEPT_CONTEXT, (CHAR*)&listen, sizeof(listen)) == SOCKET_ERROR)
						{
							dwError = WSAGetLastError();
						}
						else
						{
							if (!m_pIOCP->Register((HANDLE)scoekt->Handle(), 0))
							{
								dwError = WSAGetLastError();
							}
						}
						if (!context->Complete.IsNull())
						{
							context->Complete(dwError, dwNumberOfBytesTransferred, context->Key);
						}
					}
				}
				break;
				case OP_RECV:
				{

				}
				break;
				case OP_SEND:
				{

				}
				break;
				}
			}
		}
		//////////////////////////////////////////////////////////////////////////
		TinyScopedIOTasks::TinyScopedIOTasks(DWORD dwCount, IO::TinyIOCP* ps)
			:m_myP(NULL),
			m_dwCount(dwCount),
			m_pIOCP(ps)
		{
			m_myP = operator new (dwCount * sizeof(TinyIOTask));
			TinyIOTask *s = reinterpret_cast<TinyIOTask*>(m_myP);
			for (DWORD i = 0; i < dwCount; i++)
			{
				new (&s[i]) TinyIOTask(ps);
			}
		}
		TinyScopedIOTasks::~TinyScopedIOTasks()
		{
			TinyIOTask *s = reinterpret_cast<TinyIOTask*>(m_myP);
			for (DWORD i = 0; i < m_dwCount; i++)
			{
				s[i].~TinyIOTask();
			}
			SAFE_DELETE(m_myP);
		}
		DWORD TinyScopedIOTasks::GetSize() const
		{
			return m_dwCount;
		}
		const TinyIOTask* TinyScopedIOTasks::operator[](INT index) const
		{
			ASSERT(m_myP);
			TinyIOTask *s = reinterpret_cast<TinyIOTask*>(m_myP);
			return s + index;
		}
		TinyIOTask*	TinyScopedIOTasks::operator[](INT index)
		{
			ASSERT(m_myP);
			TinyIOTask *s = reinterpret_cast<TinyIOTask*>(m_myP);
			return s + index;
		}
		//////////////////////////////////////////////////////////////////////////
		TinyIOServer::TinyIOServer(DWORD dwConcurrency)
		{
			m_iocp = new IO::TinyIOCP(dwConcurrency);
			if (!m_iocp)
				throw exception("new TinyIOCP Fail");
			m_tasks.Reset(new TinyScopedIOTasks(dwConcurrency, m_iocp));
			if (!m_tasks)
				throw exception("new TinyScopedIOTasks Fail");
		}
		TinyIOServer::~TinyIOServer()
		{
			Close();
		}
		IO::TinyIOCP*	TinyIOServer::GetIOCP() const
		{
			return m_iocp;
		}
		void TinyIOServer::Run()
		{
			for (DWORD i = 0;i < m_tasks->GetSize();i++)
			{
				TinyIOTask* task = (*m_tasks)[i];
				task->Submit();
			}
		}
		void TinyIOServer::Close()
		{
			for (DWORD i = 0;i < m_tasks->GetSize();i++)
			{
				TinyIOTask* task = (*m_tasks)[i];
				task->Close(INFINITE);
			}
		}
	}
}