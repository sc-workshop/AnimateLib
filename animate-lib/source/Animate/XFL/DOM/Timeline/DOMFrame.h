#pragma once

#include <string>
#include <array>

#include "Animate/XFL/DOM/DOMElement.h"
#include "Animate/TypeTraits.h"

namespace Animate::DOM
{
	class DOMFrame : public DOMElement
	{
	public:
		enum class Attributes : uint32_t
		{
			Index,
			Duration,
			Name,
			LabelType,
			IsMotionObject,
			VisibleAnimationKeyframes,
			TweenInstanceName,
			TweenType,
			MotionTweenScale,
			MotionTweenRotate,
			MotionTweenRotateTimes,
			MotionTweenOrientToPath,
			MotionTweenColorAlongPath,
			MotionTweenScaleAlongPath,
			MotionTweenSync,
			MotionTweenSnap,
			ShapeTweenBlend,
			HasCustomEase,
			UseSingleEaseCurve,
			Bookmark,
			KeyMode,
			Acceleration,
			SoundEffect,
			SoundName,
			SoundSync,
			SoundLoopMode,
			SoundLoop,
			InPoint44,
			OutPoint44,
			SoundZoomLevel,
			IsIKPose,
			PoseLocations,
			FrameZDepth,
			EaseMethodName,
			ParentLayerIndex,
			RigObjectIndex,
			BlendMode,
			Visible,
			OnionFilteringColorIndex,
			RigPropagationMatrix,
			PropagateRotMap,
			PropagateScaleXMap,
			PropagateScaleYMap,
			PropagateSkewXMap,
			PropagateSkewYMap
		};

		static inline std::array AttributeNames =
		{
			"index",
			"duration",
			"name",
			"labelType",
			"isMotionObject",
			"visibleAnimationKeyframes",
			"tweenInstanceName",
			"tweenType",
			"motionTweenScale",
			"motionTweenRotate",
			"motionTweenRotateTimes",
			"motionTweenOrientToPath",
			"motionTweenColorAlongPath",
			"motionTweenScaleAlongPath",
			"motionTweenSync",
			"motionTweenSnap",
			"shapeTweenBlend",
			"hasCustomEase",
			"useSingleEaseCurve",
			"bookmark",
			"keyMode",
			"acceleration",
			"soundEffect",
			"soundName",
			"soundSync",
			"soundLoopMode",
			"soundLoop",
			"inPoint44",
			"outPoint44",
			"soundZoomLevel",
			"isIKPose",
			"poseLocations",
			"frameZDepth",
			"easeMethodName",
			"parentLayerIndex",
			"rigObjectIndex",
			"blendMode",
			"visible",
			"onionFilteringColorIndex",
			"rigPropagationMatrix",
			"propagateRotMap",
			"propagateScaleXMap",
			"propagateScaleYMap",
			"propagateSkewXMap",
			"propagateSkewYMap"
		};

		static inline std::array LabelTypes = {
			"none",
			"name",
			"comment",
			"anchor"
		};

		static const char* GetAtributeName(Attributes attribute)
		{
			return AttributeNames[(uint32_t)attribute];
		}

		static const char* GetLabelType(int type)
		{
			return LabelTypes[type];
		}

	public:
		virtual ElementTag GetTag()
		{
			return ElementTag::DOMFrame;
		}

		void SetAttributes(XFL::XFLWriter& writer)
		{
			writer.WriteAttr(
				GetAtributeName(Attributes::Name),
				name
			);

			writer.WriteAttr(
				GetAtributeName(Attributes::LabelType),
				GetLabelType(labelType), GetLabelType(0)
			);

			writer.WriteAttr(
				GetAtributeName(Attributes::Index),
				index
			);

			writer.WriteAttr(
				GetAtributeName(Attributes::Duration),
				duration, 1u
			);

			writer.WriteAttr(
				GetAtributeName(Attributes::KeyMode),
				keyMode
			);
		}

	public:
		String name;
		int labelType = 0;
		uint32_t index = 0;
		uint32_t duration = 0;
		uint32_t keyMode = 9728;
	};
}