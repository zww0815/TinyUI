#pragma once
#include "Control/TinyControl.h"
#include "RenderTask.h"
#include "AudioEncode.h"
#include "VideoEncode.h"
#include "PublishTask.h"

using namespace DXFramework;

class DXWindow : public TinyControl
{
	DECLARE_DYNAMIC(DXWindow)
public:
	DXWindow();
	virtual ~DXWindow();
	DWORD RetrieveStyle() OVERRIDE;
	DWORD RetrieveExStyle() OVERRIDE;
	LPCSTR RetrieveClassName() OVERRIDE;
	LPCSTR RetrieveTitle() OVERRIDE;
	HICON RetrieveIcon() OVERRIDE;
	LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) OVERRIDE;
	LRESULT OnDestory(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) OVERRIDE;
	LRESULT OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) OVERRIDE;
	LRESULT OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) OVERRIDE;
	LRESULT OnPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) OVERRIDE;
	LRESULT OnErasebkgnd(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) OVERRIDE;
public:
	BOOL Create(HWND hParent, INT x, INT y, INT cx, INT cy);
private:
	TinyScopedPtr<RenderTask>			m_renderTask;
	TinyScopedPtr<AudioEncode>		m_audioTask;
	TinyScopedPtr<VideoEncode>		m_videoTask;
	TinyScopedPtr<PublishTask>			m_publishTask;
};

