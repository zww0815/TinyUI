#pragma once
#include "../Common/TinyString.h"
#include "../Common/TinyWindow.h"
#include "../Common/TinyEvent.h"
#include "../Render/TinyGDI.h"

namespace TinyUI
{
#define STATE_BEGIN			   0x00000000L
#define STATE_ENABLED          0x00000000L
#define STATE_GRAYED           0x00000001L
#define STATE_DISABLED         0x00000002L
#define STATE_UNCHECKED        0x00000000L
#define STATE_CHECKED          0x00000004L
#define STATE_UNHILITE         0x00000000L
#define STATE_HILITE           0x00000008L
	/// <summary>
	/// ���ڿؼ���
	/// </summary>
	class TinyControl : public TinyWindow
	{
		DECLARE_DYNAMIC(TinyControl)
	public:
		TinyControl();
		virtual ~TinyControl();
	private:
		static HHOOK m_pHook;
		static LRESULT CALLBACK CbtFilterHook(INT code, WPARAM wParam, LPARAM lParam);
	public:
		LPCSTR	RetrieveClassName() OVERRIDE;
		LPCSTR	RetrieveTitle() OVERRIDE;
		HICON	RetrieveIcon() OVERRIDE;
		DWORD	RetrieveStyle() OVERRIDE;
		DWORD	RetrieveExStyle() OVERRIDE;
		virtual BOOL Create(HWND hParent, INT x, INT y, INT cx, INT cy, BOOL bHook = TRUE);
	public:
		BOOL	ShowWindow(INT nCmdShow) throw();
		BOOL	UpdateWindow() throw();
		BOOL	GetWindowRect(LPRECT lprect);
		BOOL	GetClientRect(LPRECT lprect);
		DWORD	GetStyle() const;
		DWORD	GetExStyle() const;
		void	CenterWindow(HWND parent, SIZE pref) throw();
		//////////////////////////////////////////////////////////////////////////
	public:
		BEGIN_MSG_MAP(TinyControl, TinyWindow)
			MESSAGE_HANDLER(WM_CREATE, OnCreate)
			MESSAGE_HANDLER(WM_DESTROY, OnDestory)
			MESSAGE_HANDLER(WM_CLOSE, OnClose)
			MESSAGE_HANDLER(WM_SIZE, OnSize)
			MESSAGE_HANDLER(WM_MOVE, OnMove)
			MESSAGE_HANDLER(WM_SETCURSOR, OnSetCursor)
			MESSAGE_HANDLER(WM_NCMOUSEMOVE, OnNCMouseMove)
			MESSAGE_HANDLER(WM_NCMOUSEHOVER, OnNCMouseHover)
			MESSAGE_HANDLER(WM_NCMOUSELEAVE, OnNCMouseLeave)
			MESSAGE_HANDLER(WM_NCHITTEST, OnNCHitTest)
			MESSAGE_HANDLER(WM_NCPAINT, OnNCPaint)
			MESSAGE_HANDLER(WM_NCLBUTTONDOWN, OnNCLButtonDown)
			MESSAGE_HANDLER(WM_NCLBUTTONUP, OnNCLButtonUp)
			MESSAGE_HANDLER(WM_NCLBUTTONDBLCLK, OnNCLButtonDBClick)
			MESSAGE_HANDLER(WM_NCRBUTTONDOWN, OnNCRButtonDown)
			MESSAGE_HANDLER(WM_NCRBUTTONUP, OnNCRButtonUp)
			MESSAGE_HANDLER(WM_NCRBUTTONDBLCLK, OnNCRButtonDBClick)
			MESSAGE_HANDLER(WM_NCACTIVATE, OnNCActivate)
			MESSAGE_HANDLER(WM_NCCALCSIZE, OnNCCalcSize)
			MESSAGE_HANDLER(WM_PAINT, OnPaint)
			MESSAGE_HANDLER(WM_ERASEBKGND, OnErasebkgnd)
			MESSAGE_HANDLER(WM_MOUSEMOVE, OnMouseMove)
			MESSAGE_HANDLER(WM_MOUSELEAVE, OnMouseLeave)
			MESSAGE_HANDLER(WM_MOUSEWHEEL, OnMouseWheel)
			MESSAGE_HANDLER(WM_LBUTTONDOWN, OnLButtonDown)
			MESSAGE_HANDLER(WM_LBUTTONUP, OnLButtonUp)
			MESSAGE_HANDLER(WM_LBUTTONDBLCLK, OnRButtonDBClick)
			MESSAGE_HANDLER(WM_RBUTTONDOWN, OnRButtonDown)
			MESSAGE_HANDLER(WM_RBUTTONUP, OnRButtonUp)
			MESSAGE_HANDLER(WM_MBUTTONDOWN, OnMButtonDown)
			MESSAGE_HANDLER(WM_MBUTTONUP, OnMButtonUp)
			MESSAGE_HANDLER(WM_RBUTTONDBLCLK, OnRButtonDBClick)
			MESSAGE_HANDLER(WM_MOUSEHOVER, OnMouseHover)
			MESSAGE_HANDLER(WM_ACTIVATE, OnActivate)
			MESSAGE_HANDLER(WM_TIMER, OnTimer)
			MESSAGE_HANDLER(WM_COMMAND, OnCommand)
			MESSAGE_HANDLER(WM_NOTIFY, OnNotify)
			MESSAGE_HANDLER(WM_COMMANDREFLECT, OnCommandReflect)
			MESSAGE_HANDLER(WM_DRAWITEMREFLECT, OnDrawItemReflect)
			MESSAGE_HANDLER(WM_NOTIFYREFLECT, OnNotifyReflect)
			MESSAGE_HANDLER(WM_MEASUREITEMREFLECT, OnMeasureItemReflect)
			MESSAGE_HANDLER(WM_DELETEITEMREFLECT, OnDeleteItemReflect)
			MESSAGE_HANDLER(WM_KEYDOWN, OnKeyDown)
			MESSAGE_HANDLER(WM_KEYUP, OnKeyUp)
			MESSAGE_HANDLER(WM_CHAR, OnChar)
			MESSAGE_HANDLER(WM_SETFOCUS, OnSetFocus)
			MESSAGE_HANDLER(WM_KILLFOCUS, OnKillFocus)
		END_MSG_MAP()
		virtual LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
		virtual LRESULT OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
		virtual LRESULT OnPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
		virtual LRESULT OnNCMouseMove(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
		virtual LRESULT OnNCMouseHover(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
		virtual LRESULT OnNCMouseLeave(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
		virtual LRESULT OnNCHitTest(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
		virtual LRESULT OnNCPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
		virtual LRESULT OnNCLButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
		virtual LRESULT OnNCLButtonUp(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
		virtual LRESULT OnNCLButtonDBClick(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
		virtual LRESULT OnNCRButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
		virtual LRESULT OnNCRButtonUp(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
		virtual LRESULT OnNCRButtonDBClick(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
		virtual LRESULT OnNCActivate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
		virtual LRESULT OnNCCalcSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
		virtual LRESULT OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
		virtual LRESULT OnMove(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
		virtual LRESULT OnErasebkgnd(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
		virtual LRESULT OnMouseMove(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
		virtual LRESULT OnMouseLeave(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
		virtual LRESULT OnMouseWheel(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
		virtual LRESULT OnMouseHover(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
		virtual LRESULT OnLButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
		virtual LRESULT OnLButtonUp(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
		virtual LRESULT OnLButtonDBClick(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
		virtual LRESULT OnRButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
		virtual LRESULT OnRButtonUp(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
		virtual LRESULT OnRButtonDBClick(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
		virtual LRESULT OnMButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
		virtual LRESULT OnMButtonUp(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
		virtual LRESULT OnMButtonDBClick(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
		virtual LRESULT OnDestory(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
		virtual LRESULT OnSetCursor(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
		virtual LRESULT OnTimer(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
		virtual LRESULT OnActivate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
		virtual LRESULT OnCommand(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
		virtual LRESULT OnCommandReflect(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
		virtual LRESULT OnNotify(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
		virtual LRESULT OnNotifyReflect(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
		virtual LRESULT OnDeleteItemReflect(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
		virtual LRESULT OnDrawItemReflect(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
		virtual LRESULT OnMeasureItem(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
		virtual LRESULT OnMeasureItemReflect(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
		virtual LRESULT OnKeyDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
		virtual LRESULT OnKeyUp(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
		virtual LRESULT OnChar(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
		virtual LRESULT OnSetFocus(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
		virtual LRESULT OnKillFocus(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	public:
		Event<void(UINT, WPARAM, LPARAM, BOOL&)> EVENT_Create;
		Event<void(UINT, WPARAM, LPARAM, BOOL&)> EVENT_Destory;
	};
	SELECTANY HHOOK TinyControl::m_pHook = NULL;
}


