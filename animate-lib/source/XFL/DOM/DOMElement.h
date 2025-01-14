#pragma once

#include "XFL/Writer.h"
#include "XFL/SerizalizeTraits.h"
#include "DOMElements.h"

namespace Animate::DOM
{
	class DOMElement
	{
	public:
		virtual ElementTag GetTag() = 0;
		virtual void SetAttributes(XFL::XFLWriter& writer) = 0;
	};
}