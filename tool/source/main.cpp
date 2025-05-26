
#include "Document/SketchDocument.h"

using namespace Animate;

static void create_test_symbol(Library::DocumentPage& doc)
{
    auto& controller = doc.GetPage();

	auto& layer1 = controller.AddNewLayer("Layer 1", false, std::nullopt);
    auto& testFrame = layer1.CreateFrame();
    testFrame.SetDuration(10);
}

int main(int argc, char* argv[])
{
    if (argc == 1) return 1;

    Document::SketchDocument document;
    document.SetFrameRate(60);
    document.SetBackgroundColor({ 50, 50, 50 });

    auto& controller = document.GetController();

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

    auto& symbol = controller.MakeSymbol("path/new symbol", Library::DocumentPage::SymbolType::Graphic);
	create_test_symbol(symbol);
    
    try
    {
        document.WriteXFL(argv[1]);
    }
    catch (const std::exception& e)
    {
		std::cout << "error: " << e.what() << std::endl;
    }
    
    std::cout << "Done";
    return 0;
}