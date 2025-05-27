#pragma once

#include "PicObject.h"
#include "PicFrame.h"

#include "Animate/XFL/DOM/Timeline/DOMLayer.h"

namespace Animate::Pic
{
	class Layer : public Object
	{
	public:
		enum class Type
		{
			Normal,
			Guide = 2,
			Folder,
			Clipper,
			Camera 
		};

		enum class AnimationMode
		{
			None,
			Tween,
			Pose,
		};

	public:
		virtual bool IsPicLayer() const override { return true; };
		virtual void WriteXFL(XFL::XFLWriter& writer, uint32_t /*index*/) const override;

	public:
		void SetName(const String& name) { m_name = name; }
		void Initialize(const String& name, size_t duration = 1);

	public:
		Frame& FirstFrame();
		Frame& CreateFrame();

	public:
		bool IsNormal() const { return m_type == Type::Normal; }
		void SetNormal() { m_type = Type::Normal; }

		bool IsFolder() const { return m_type == Type::Folder; }
		void SetFolder() { m_type = Type::Folder; }
		void SetOpenFolder(bool is_open) { m_is_open_folder = is_open; }
		bool IsOpenFolder() const { return m_is_open_folder; }

	protected:
		void Create();

	private:
		String m_name;
		Type m_type = Type::Normal;

		bool m_is_open_folder = false;
	};
}