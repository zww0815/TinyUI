#include "../stdafx.h"
#include "TinyVisualDocument.h"
#include "TinyVisualList.h"

namespace TinyUI
{
	namespace Windowless
	{
		TinyVisualList::TinyVisualList(TinyVisual* spvisParent, TinyVisualDocument* vtree)
			:TinyVisual(spvisParent, vtree)
		{

		}
		TinyVisualList::~TinyVisualList()
		{

		}
		TinyString TinyVisualList::RetrieveTag() const
		{
			return TinyVisualTag::LIST;
		}
		void TinyVisualList::SetScrollInfo(INT iMin, INT iMax, INT iPage, INT iPos)
		{
			m_scrollbar->SetScrollInfo(iMin, iMax, iPage, iPos);
		}
		HRESULT	TinyVisualList::OnCreate()
		{
			ASSERT(m_document);
			TinySize size = this->GetSize();
			m_scrollbar = m_document->Create<TinyVisualVScrollBar>(size.cx - 12, 0, 12, size.cy, this);
			m_onPosChange.Reset(new Delegate<void(BOOL, INT, INT, INT)>(this, &TinyVisualList::OnPosChange));
			m_scrollbar->EVENT_PosChange += m_onPosChange;
			return TinyVisual::OnCreate();
		}
		HRESULT TinyVisualList::OnDestory()
		{
			m_scrollbar->EVENT_PosChange -= m_onPosChange;
			return TinyVisual::OnDestory();
		}
		BOOL TinyVisualList::OnDraw(HDC hDC, const RECT& rcPaint)
		{
			return TRUE;
		}
		HRESULT	TinyVisualList::OnMouseEnter()
		{
			m_document->SetFocus(m_scrollbar);
			return FALSE;
		}
		HRESULT	TinyVisualList::OnMouseLeave()
		{
			m_document->SetFocus(NULL);
			return FALSE;
		}
		void TinyVisualList::AdjustLayout(TinyVisual* spvis, INT dx, INT dy)
		{
			while (spvis != NULL)
			{
				TinyRectangle s = spvis->GetRectangle();
				s.OffsetRect(dx, dy);
				spvis->SetPosition(s.Position());
				spvis->SetSize(s.Size());
				spvis = m_document->GetVisual(spvis, CMD_PREV);
			}
		}
		void TinyVisualList::OnPosChange(BOOL bVer, INT code, INT iOldPos, INT iNewPos)
		{
			TinyVisual* spvis = m_document->GetVisual(this, CMD_CHILD);
			spvis = m_document->GetVisual(spvis, CMD_LAST);
			if (spvis == m_scrollbar)
			{
				spvis = m_document->GetVisual(m_scrollbar, CMD_PREV);
			}
			AdjustLayout(spvis, 0, iOldPos - iNewPos);
			TinyRectangle s = m_document->GetWindowRect(this);
			m_document->Invalidate(&s);
		}
	}
}
