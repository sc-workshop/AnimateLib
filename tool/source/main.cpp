
#include "Document/SketchDocument.h"

using namespace Animate;

int main(int argc, char* argv[])
{
    if (argc == 1) return 1;

    Document::SketchDocument document;
    document.SetFrameRate(60);
    document.SetBackgroundColor({ 0xfc, 0xfc, 0xfc });

    document.GetController().ReserveFolders(2);
    auto& folder = document.GetController().MakeFolder(u"Какая-то папка");
    auto& children_folder = document.GetController().MakeFolder(u"Какая-то дочерняя папка");
    children_folder.SetParent(folder);


    folder.SetExpanded(true);
    document.WriteXFL(argv[1]);

    std::cout << "Done";
    return 0;
}