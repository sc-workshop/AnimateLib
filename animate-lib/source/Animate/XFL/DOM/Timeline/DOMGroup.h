#pragma once

#include "Animate/XFL/DOM/DOMElement.h"

namespace Animate::DOM
{
	class DOMGroup : public DOMElement
	{
	public:
		virtual ElementTag GetTag()
		{
			return ElementTag::DOMGroup;
		}

		void SetAttributes(XFL::XFLWriter&) { }
	};
}