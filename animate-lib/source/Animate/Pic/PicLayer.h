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
			Clipper, // Also knows as Mask layer
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
		size_t GetNumFrames();
		Frame& CreateFrame();

	public:
		bool IsNormal() const { return m_type == Type::Normal; }
		void SetNormal() { m_type = Type::Normal; }

		bool IsFolder() const { return m_type == Type::Folder; }
		void SetFolder() { m_type = Type::Folder; }
		void SetOpenFolder(bool is_open) { m_is_open_folder = is_open; }
		bool IsOpenFolder() const { return m_is_open_folder; }
		bool IsCameraLayer() const { return m_type == Type::Camera;  }

	public:
		PicIterator<Frame> begin() { return PicIterator<Frame>::CreateBegin(*this); }
		PicIterator<Frame> end() { return PicIterator<Frame>::CreateEnd(*this); }

	protected:
		void Create();

		virtual Object* CloneObject()
		{
			return new Layer(*this);
		}

	private:
		String m_name;
		Type m_type = Type::Normal;

		bool m_is_open_folder = false;
	};
}