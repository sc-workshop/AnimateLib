
#include "Document/SketchDocument.h"

using namespace Animate;

int main(int argc, char* argv[])
{
    if (argc == 1) return 1;

    Document::SketchDocument document;
    document.SetFrameRate(60);
    document.SetBackgroundColor({ 50, 50, 50 });

    auto& controller = document.GetController();

    controller.ReserveFolders(3);
    auto& folder = controller.MakeFolder(u"Какая-то папка");
    folder.SetExpanded(true);
     
    auto& children_folder = controller.MakeFolder(u"Какая-то дочерняя папка");
    auto& big_path = controller.MakeFolders(u"Очень/большой/путь");
    children_folder.SetParent(folder);

    auto& bitmap = controller.MakeBitmap("path/to/bitmap/funny bitmap");
    bitmap.FromImage("../../tool/assets/crow.png");
    bitmap.SetAllowSmooth(true);
    bitmap.SetCompression(Library::MediaBits::CompressionType::Lossless);

    auto& bitmap_copy = controller.MakeBitmap("path/to/bitmap/funny bitmap");
    bitmap_copy.SetAllowSmooth(true);
    bitmap_copy.FromImage("../../tool/assets/you.png");
    
    document.WriteXFL(argv[1]);

    std::cout << "Done";
    return 0;
}