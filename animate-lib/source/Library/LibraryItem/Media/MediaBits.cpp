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

    void MediaBits::WriteXFL(XFL::XFLFile& /*file*/, XFL::XFLWriter& root) const
    {
        DOM::DOMBitmapItem item;
        InitializeDOMItem(item);

        XFL::XFLWriter writer(root, item);
    }

    void MediaBits::WriteXFLContent(XFL::XflIoFile& file) const
    {
        m_bitmap.WriteXFLContent(file);
    }

    void MediaBits::InitializeDOMItem(DOM::DOMBitmapItem& item) const
    {
        MediaElem::InitializeDOMItem(item);

        item.smooth = m_allow_smooth;
        item.compression = (uint32_t)m_compression;
        item.use_jpeg = m_compression == CompressionType::Photo;
        item.quality = m_quality;
        item.bitmap_href = GetXFLMediaPath();
        item.frame = m_bitmap.GetBounds();
    }
}