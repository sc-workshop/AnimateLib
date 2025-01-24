
#include "Document/SketchDocument.h"

using namespace Animate;

int main(int argc, char* argv[])
{
    if (argc == 1) return 1;

    Document::SketchDocument document;
    document.SetFrameRate(60);
    document.SetBackgroundColor({ 0xfc, 0xfc, 0xfc });

    auto& controller = document.GetController();

    controller.ReserveFolders(3);
    auto& folder = controller.MakeFolder(u"�����-�� �����");
    folder.SetExpanded(true);
     
    auto& children_folder = controller.MakeFolder(u"�����-�� �������� �����");
    auto& big_path = controller.MakeFolders(u"�����/�������/����");
    children_folder.SetParent(folder);

    auto& bitmap = controller.MakeBitmap("path/to/bitmap/funny bitmap");
    auto& bitmap_copy = controller.MakeBitmap("path/to/bitmap/funny bitmap");

    
    document.WriteXFL(argv[1]);

    std::cout << "Done";
    return 0;
}