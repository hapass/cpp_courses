#include "test_runner.h"
#include "rectangle.h"

void TestRectangleSize() {
    Rectangle r(2, 5);
    AssertEqual(r.GetWidth(), 2, "2x5 width");
    AssertEqual(r.GetHeight(), 5, "2x5 height");
    AssertEqual(r.GetArea(), 10, "2x5 area");
    AssertEqual(r.GetPerimeter(), 14, "2x5 perimeter");
}

int main() {
    TestRunner r;
    r.RunTest(TestRectangleSize, "TestRectangleSize");
    return 0;
}