
#include "Document/SketchDocument.h"

using namespace Animate;

static void create_test_symbol(Library::DocumentPage& doc, Library::MediaBits& testImage)
{
    auto& controller = doc.GetPage();

	auto& layer1 = controller.AddNewLayer("Layer 1", false, std::nullopt);
    auto& testFrame = layer1.CreateFrame();
    testFrame.SetDuration(10);
	testFrame.AddBitmapChildren(testImage);
}

int main(int argc, char* argv[])
{
    if (argc == 1) return 1;

    Document::SketchDocument document;
    document.SetFrameRate(60);
    document.SetBackgroundColor({ 50, 50, 50 });

    auto& controller = document.GetController();

    auto& folder = controller.MakeFolder(u"�����-�� �����");
    folder.SetExpanded(true);
     
    auto& children_folder = controller.MakeFolder(u"�����-�� �������� �����");
    auto& big_path = controller.MakeFolders(u"�����/�������/����");
    children_folder.SetParent(folder);
    
    auto& not_funy_bitmap_but_why_not = controller.MakeBitmap("path/to/bitmap/funny bitmap");
    not_funy_bitmap_but_why_not.FromImage("../../tool/assets/crow.png");
    not_funy_bitmap_but_why_not.SetAllowSmooth(true);
    not_funy_bitmap_but_why_not.SetCompression(Library::MediaBits::CompressionType::Lossless);
    
    auto& funny_bitmap = controller.MakeBitmap("path/to/bitmap/funny bitmap");
    funny_bitmap.SetAllowSmooth(true);
    funny_bitmap.FromImage("../../tool/assets/you.png");

    auto& symbol = controller.MakeSymbol("path/new symbol", Library::DocumentPage::SymbolType::Graphic);
	create_test_symbol(symbol, funny_bitmap);
    
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