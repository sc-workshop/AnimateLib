#pragma once

#include "Library/LibraryItem.h"

namespace Animate::Document
{
	class LibraryController;
	class SketchDocument;
}

namespace Animate::Library
{
	class DocumentPage : public LibraryItem
	{
	public:
		enum class SymbolType
		{
			Graphic = 0,
			MovieClip,
			Button,
			IkContainer,
			Puppet,
			PuppetBase,
			Media3D
		};

		friend Document::LibraryController;

	public:
		using LibraryItem::LibraryItem;

	public:
		virtual bool IsDocumentPage() const
		{
			return true;
		}

	public:
		virtual time_t GetModDateForLibrary() const { return m_last_modify_time; };
		virtual void SetModDateForLibrary(time_t t) { m_last_modify_time = t; }

		virtual void WriteXFL(XFL::XFLFile& file, XFL::XFLWriter& writer) const override;
		virtual void WriteXFLSymbol(XFL::XFLFile& file) const;
		virtual void WriteXFLTimeline(XFL::XFLWriter& writer) const;

	protected:
		void CreateSymbol(Document::SketchDocument& root);
		void Create(Document::SketchDocument& root, bool is_scene);

	protected:
		SymbolType m_type = SymbolType::Graphic;
		time_t m_creation_time = 0;
		time_t m_last_modify_time = 0;
	};
}