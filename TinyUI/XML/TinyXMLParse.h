#pragma once
#include "../Common/TinyString.h"
#include "../Common/TinyEvent.h"
#include "../Render/TinyGDI.h"
#include "../XML/tinystr.h"
#include "../XML/tinyxml.h"

namespace TinyUI
{
	/// <summary>
	/// XML Skin������ 
	/// </summary>
	class TinyXMLParse : public TinyObject
	{
		DECLARE_DYNAMIC(TinyXMLParse)
	public:
		TinyXMLParse();
		virtual ~TinyXMLParse();
	public:
		BOOL	LoadFile(LPCSTR pzFile);
		BOOL	LoadStream(IStream* ps);
	public:

	};
}



