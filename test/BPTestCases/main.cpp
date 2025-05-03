#include <gmock/gmock.h>

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv); // lets init a GUI app to avoid unwanted exceptions from GUI related classes
    testing::InitGoogleTest(&argc, argv);
    testing::InitGoogleMock(&argc, argv);
    return RUN_ALL_TESTS();
}
