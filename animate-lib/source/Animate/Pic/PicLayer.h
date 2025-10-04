#pragma once

#include "PicObject.h"
#include "PicFrame.h"

namespace Animate::Pic
{
	class Layer : public Object
	{
	public:
		enum class Type
		{
			Normal = 0,
			Folder,
			Clipper, // Also knows as Mask layer
			Guide,
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
		const String& GetName() { return m_name; }
		void SetName(const String& name) { m_name = name; }
		void Initialize(const String& name, size_t duration = 1);
		bool Locked() const { return m_locked; };
		void SetLocked(bool status = true);

	public:
		size_t GetDuration();
		Frame& CreateFrame();

	public:
		bool IsNormal() const { return m_type == Type::Normal; }
		bool IsClipper() const { return m_type == Type::Clipper; }
		bool IsAttachedToMask() const { return ClippedBy() != nullptr; }
		void SetNormal() { m_type = Type::Normal; }

		bool IsFolder() const { return m_type == Type::Folder; }
		void SetFolder() { m_type = Type::Folder; }
		void SetOpenFolder(bool is_open) { m_is_open_folder = is_open; }
		bool IsOpenFolder() const { return m_is_open_folder; }
		bool IsCameraLayer() const { return m_type == Type::Camera;  }

		// Masks
	public:
		Layer* ClippedBy() const;
		void SetClipper();
		void AttachMask(Layer& mask);

	public:
		Iterator<Frame> begin() { return Iterator<Frame>::CreateBegin(*this); }
		Iterator<Frame> end() { return Iterator<Frame>::CreateEnd(*this); }
		ConstIterator<Frame> begin() const { return ConstIterator<Frame>::CreateBegin(*this); }
		ConstIterator<Frame> end() const { return ConstIterator<Frame>::CreateEnd(*this); }

	protected:
		void Create();

		virtual Object* CloneObject() override
		{
			return new Layer(*this);
		}

	private:
		String m_name;
		Type m_type = Type::Normal;

		bool m_locked = false;
		bool m_is_open_folder = false;
		Layer* m_parent_layer = nullptr;
	};
}