#pragma once

#include <string>
#include <array>

#include "Animate/Library/Properties/GraphicEffectInstance.h"

namespace Animate::DOM
{
	class BlendMode {
	public:
		using Mode = Animate::Library::GraphicEffectInstance::BlendMode;
		static inline std::array Type =
		{
			"normal",
			"layer",
			"darken",
			"multiply",
			"lighten",
			"screen",
			"overlay",
			"hardlight",
			"add",
			"subtract",
			"difference",
			"invert",
			"alpha",
			"erase"
		};

		static const char* GetName(Mode mode) {
			return Type[(uint32_t)mode];
		}

		static void Write(XFL::XFLWriter& writer, String name, Mode blendMode) {
			writer.WriteAttr(name, GetName(blendMode), GetName(Mode::Normal));
		}
	};
}