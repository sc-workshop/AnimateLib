#pragma once

#include <string>
#include <array>

#include "Animate/XFL/DOM/DOMElement.h"
#include "Animate/TypeTraits.h"

namespace Animate::DOM
{
	class DOMTextRun : public DOMElement
	{
	public:
		virtual ElementTag GetTag()
		{
			return ElementTag::DOMTextRun;
		}

		void SetAttributes(XFL::XFLWriter&)
		{
		}
	};
}