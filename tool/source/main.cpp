
#include "Document/SketchDocument.h"

using namespace Animate;

int main(int argc, char* argv[])
{
    if (argc == 1) return 1;

    Document::SketchDocument document;
    document.SetFrameRate(60);
    document.SetBackgroundColor({ 0xfc, 0xfc, 0xfc });
    document.WriteXFL(argv[1]);

    std::cout << "Done";
    return 0;
}