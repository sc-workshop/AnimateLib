
#include "Document/SketchDocument.h"
#include "Pic/PicBitmap.h"

using namespace Animate;

static void create_test_symbol(Library::DocumentPage& doc, Library::MediaBits& firstImage, Library::MediaBits& secondImage)
{
    auto& controller = doc.GetPage();

    {
        auto& layer = controller.AddNewLayer("First image", false, std::nullopt);
        auto& testFrame = layer.CreateFrame();
        testFrame.SetDuration(10);
        auto& image = testFrame.AddBitmapChildren(firstImage);

        Matrix imageMat;
        imageMat.tx = -((float)firstImage.GetBitmap().GetWidth() / 2);
        imageMat.ty = -((float)firstImage.GetBitmap().GetHeight() / 2);

        image.SetMatrix(imageMat);
    }
	
    {
        auto& layer = controller.AddNewLayer("Second image", false, std::nullopt);
        auto& testFrame = layer.CreateFrame();
        testFrame.SetDuration(20);
        testFrame.AddBitmapChildren(secondImage);
    }
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
    
    auto& not_funy_bitmap_but_why_not = controller.MakeBitmap("path/to/bitmap/funny bitmap");
    not_funy_bitmap_but_why_not.FromImage("../../tool/assets/crow.png");
    not_funy_bitmap_but_why_not.SetAllowSmooth(true);
    not_funy_bitmap_but_why_not.SetCompression(Library::MediaBits::CompressionType::Lossless);
    
    auto& funny_bitmap = controller.MakeBitmap("path/to/bitmap/funny bitmap");
    funny_bitmap.SetAllowSmooth(true);
    funny_bitmap.FromImage("../../tool/assets/you.png");

    auto& symbol = controller.MakeSymbol("path/new symbol", Library::DocumentPage::SymbolType::Graphic);
	create_test_symbol(symbol, funny_bitmap, not_funy_bitmap_but_why_not);
    
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