#include "PicGroup.h"

#include "Animate/XFL/DOM/Timeline/DOMGroup.h"

namespace Animate::Pic
{
    void Group::WriteXFL(XFL::XFLWriter& writer, uint32_t) const
    {
        DOM::DOMGroup group;
        XFL::XFLWriter group_writer(writer, group);

        WriteXFLMatrix(group_writer);

        auto members = group_writer.CreateProperty(DOM::PropTag::Members);

        uint32_t index = 0;
        for (const auto& member : m_childrens)
        {
            member->SetMatrix(m_matrix);
            member->WriteXFL(members, index++);
        }
    }
}