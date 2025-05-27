#pragma once

#include "Animate/XFL/Writer.h"
#include "Animate/XFL/SerizalizeTraits.h"
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