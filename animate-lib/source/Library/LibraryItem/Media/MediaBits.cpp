#include "MediaBits.h"

#include "core/io/file_stream.h"
#include "core/stb/stb.h"

#include "XFL/DOM/Items/DOMMediaItem.h"

namespace Animate::Library
{
    void MediaBits::FromImage(const std::filesystem::path& path)
    {
        m_bitmap.FromImage(path);
        m_source_path = path;
    }

    void MediaBits::UpdateImage(const std::filesystem::path& path)
    {
        bool first_load = !m_bitmap.Loaded();
        FromImage(path);

        if (!first_load)
        {
            UpdateFromSource();
        }
    }

    void MediaBits::WriteXFL(XFL::XFLWriter& writer) const
    {
        DOM::DOMMediaItem item(DOM::DOMMediaItem::Type::Bitmap);
        InitializeDOMItem(item);

        writer.WriteDOMBitmapItem(
            item, 
            m_allow_smooth, 
            (uint32_t)m_compression, 
            m_compression == CompressionType::Photo, 
            m_quality,
            GetXFLMediaPath()
        );
    }

    void MediaBits::WriteXFLContent(XFL::XflIoFile& file) const
    {
        m_bitmap.WriteXFLContent(file);
    }
}