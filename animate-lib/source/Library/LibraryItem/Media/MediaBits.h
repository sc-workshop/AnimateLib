#pragma once

#include "Library/LibraryItem/MediaElem.h"

namespace Animate::Library
{
	class MediaBits : public MediaElem
	{
	public:
		enum class Quality
		{
			Lossless
		};
	public:
		using MediaElem::MediaElem;

	public:
		virtual bool IsMediaBits() const override
		{
			return true;
		}

	public:
		bool GetAllowSmooth() const { return m_allow_smooth; }
		void SetAllowSmooth(bool status) { m_allow_smooth = status; }

		virtual void WriteXFL(XFL::XFLWriter& writer) const override;

	private:
		bool m_allow_smooth = false;
	};
}