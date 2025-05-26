#pragma once

#include <string>
#include <array>

#include "XFL/DOM/DOMElement.h"

#include "TypeTraits.h"

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

		static const char* GetAtributeName(Attributes attribute)
		{
			return AttributeNames[(uint32_t)attribute];
		}

	public:
		virtual ElementTag GetTag()
		{
			return ElementTag::DOMFrame;
		}

		void SetAttributes(XFL::XFLWriter& writer)
		{
			writer.WriteAttr(
				GetAtributeName(Attributes::Index),
				index
			);

			writer.WriteAttr(
				GetAtributeName(Attributes::Duration),
				duration
			);

			writer.WriteAttr(
				GetAtributeName(Attributes::KeyMode),
				keyMode
			);

			// TODO: rest of props
		}

	public:
		uint32_t index = 0;
		uint32_t duration = 0;
		uint32_t keyMode = 9728;
	};
}