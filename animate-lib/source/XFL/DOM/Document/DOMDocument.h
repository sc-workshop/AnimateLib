#pragma once

#include <string>
#include <array>

#include "XFL/DOM/DOMElement.h"

#include <core/math/color_rgb.h>

namespace Animate::DOM
{
	class FLDocument : public DOMElement
	{
	public:
		enum class Attributes : uint32_t
		{
			BackgroundColor,
			BackgroundAlpha,
			PasteboardColorCheck,
			Width,
			Height,
			FrameRate,
			CurrentTimeline,
			XflVersion,
			CreatorInfo,
			Platform,
			VersionInfo,
			MajorVersion,
			MinorVersion,
			BuildNumber,
			GridSpacingX,
			GridSpacingY,
			GridColor,
			GridSnapAccuracy,
			GridSnapTo,
			GuidesColor,
			GuidesLocked,
			GuidesSnapAccuracy,
			GuidesSnapTo,
			GuidesVisible,
			GridVisible,
			RulerVisible,
			PixelSnap,
			BitmapSnap,
			SnapAlign,
			SnapAlignBorder,
			SnapAlignBorderSpacing,
			SnapAlignHorizontalCenter,
			SnapAlignHorizontalSpacing,
			SnapAlignVerticalCenter,
			SnapAlignVerticalSpacing,
			ObjectsSnapTo,
			NextSymbolIdentifier,
			NextMediaIdentifier,
			NextTextFieldIdentifier,
			BreakPointCount,
			PinnedBrushSizes,
			PinnedEraserSizes,
			TimelineHeight,
			TimelineLabelWidth,
			HasPostProcessor,
			PostProcessorName,
			AdjustViewAngle3D,
			ViewAngle3D,
			VanishingPoint3DX,
			VanishingPoint3DY,
			PreviewFrame,
			TemplateFilename,
			TemplateDescription,
			SharedLibraryURL,
			ExportComponentSchemasToSwf,
			RulerUnitType,
			PreviewMode,
			TabOrderMode,
			HasLanguagePanelData,
			LanguageAvailableIndex,
			LanguageAvailableList,
			LanguageURL,
			LanguageDefault,
			LanguageForStage,
			LanguageAutoDetect,
			LanguageStringReplaceMethod,
			UseCarbonLineSpacing,
			NextSceneIdentifier,
			NextItemIdentifier,
			PostProcessorGUID,
			PostProcessorHRef,
			ViewOptionsAnimationControlVisible,
			ViewOptionsButtonsActive,
			ViewOptionsPasteBoardView,
			ViewOptionsLivePreview,
			PlayOptionsPlayLoop,
			PlayOptionsPlayPages,
			PlayOptionsPlayFrameActions,
			PlayOptionsPlaySounds,
			AccName,
			Description,
			Shortcut,
			TabIndex,
			Silent,
			ForceSimple,
			AutoLabeling,
			HasAccessibleData,
			TabRulerVisible,
			AutoSaveEnabled,
			AutoSaveIntervalMinutes,
			AutoSaveHasPrompted,
			ScaleContentWithStage,
			FiletypeGUID,
			FiletypeName,
			FileGUID
		};

		static inline std::array AttributeNames =
		{
			"backgroundColor",
			"backgroundAlpha",
			"pasteboardColorCheck",
			"width",
			"height",
			"frameRate",
			"currentTimeline",
			"xflVersion",
			"creatorInfo",
			"platform",
			"versionInfo",
			"majorVersion",
			"minorVersion",
			"buildNumber",
			"gridSpacingX",
			"gridSpacingY",
			"gridColor",
			"gridSnapAccuracy",
			"gridSnapTo",
			"guidesColor",
			"guidesLocked",
			"guidesSnapAccuracy",
			"guidesSnapTo",
			"guidesVisible",
			"gridVisible",
			"rulerVisible",
			"pixelSnap",
			"bitmapSnap",
			"snapAlign",
			"snapAlignBorder",
			"snapAlignBorderSpacing",
			"snapAlignHorizontalCenter",
			"snapAlignHorizontalSpacing",
			"snapAlignVerticalCenter",
			"snapAlignVerticalSpacing",
			"objectsSnapTo",
			"nextSymbolIdentifier",
			"nextMediaIdentifier",
			"nextTextFieldIdentifier",
			"breakPointCount",
			"pinnedBrushSizes",
			"pinnedEraserSizes",
			"timelineHeight",
			"timelineLabelWidth",
			"hasPostProcessor",
			"postProcessorName",
			"adjustViewAngle3D",
			"viewAngle3D",
			"vanishingPoint3DX",
			"vanishingPoint3DY",
			"previewFrame",
			"templateFilename",
			"templateDescription",
			"sharedLibraryURL",
			"exportComponentSchemasToSwf",
			"rulerUnitType",
			"previewMode",
			"tabOrderMode",
			"hasLanguagePanelData",
			"languageAvailableIndex",
			"languageAvailableList",
			"languageURL",
			"languageDefault",
			"languageForStage",
			"languageAutoDetect",
			"languageStringReplaceMethod",
			"useCarbonLineSpacing",
			"nextSceneIdentifier",
			"nextItemIdentifier",
			"postProcessorGUID",
			"postProcessorHRef",
			"viewOptionsAnimationControlVisible",
			"viewOptionsButtonsActive",
			"viewOptionsPasteBoardView",
			"viewOptionsLivePreview",
			"playOptionsPlayLoop",
			"playOptionsPlayPages",
			"playOptionsPlayFrameActions",
			"playOptionsPlaySounds",
			"accName",
			"description",
			"shortcut",
			"tabIndex",
			"silent",
			"forceSimple",
			"autoLabeling",
			"hasAccessibleData",
			"tabRulerVisible",
			"autoSaveEnabled",
			"autoSaveIntervalMinutes",
			"autoSaveHasPrompted",
			"scaleContentWithStage",
			"filetypeGUID",
			"filetypeName",
			"fileGUID"
		};

		static const char* GetAtributeName(Attributes attribute)
		{
			return AttributeNames[(uint32_t)attribute];
		}

	public:
		static const inline wk::ColorRGB BackgroundColor_Default = { 0xFF, 0xFF, 0xFF };

	public:
		virtual ElementTag GetTag()
		{
			return ElementTag::DOMDocument;
		}

		void SetAttributes(XFL::XFLWriter& writer)
		{
			writer.WriteAttr(
				GetAtributeName(Attributes::BackgroundColor),
				backgroundColor,
				BackgroundColor_Default
			);

			writer.WriteAttr(
				GetAtributeName(Attributes::Width),
				width
			);

			writer.WriteAttr(
				GetAtributeName(Attributes::Height),
				width
			);

			writer.WriteAttr(
				GetAtributeName(Attributes::FrameRate),
				frameRate
			);

			writer.WriteAttr(
				GetAtributeName(Attributes::XflVersion),
				xflVersion
			);

			writer.WriteAttr(
				GetAtributeName(Attributes::CreatorInfo),
				creator
			);

			writer.WriteAttr(
				GetAtributeName(Attributes::Platform),
				platform
			);

			writer.WriteAttr(
				GetAtributeName(Attributes::VersionInfo),
				versionInfo
			);

			writer.WriteAttr(
				GetAtributeName(Attributes::MajorVersion),
				majorVersion
			);

			writer.WriteAttr(
				GetAtributeName(Attributes::MinorVersion),
				minorVersion
			);

			writer.WriteAttr(
				GetAtributeName(Attributes::BuildNumber),
				buildNumber
			);
		}

	public:
		const char* xflVersion = "";
		const char* creator = "";
		const char* platform = "";
		std::string versionInfo;
		int majorVersion = 0;
		int minorVersion = 0;
		int buildNumber = 0;
		int frameRate = 0;
		wk::ColorRGB backgroundColor = BackgroundColor_Default;

		uint32_t width = 0;
		uint32_t height = 0;
	};
}