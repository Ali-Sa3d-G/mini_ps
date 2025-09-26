#include "Image_Class.h"
#include <iostream>
#include <string>

using namespace std;

class ImageEditor {
public:
    Image toGray(const Image& src) { // filter 1
        Image dst = src;
        for (int x = 0; x < dst.width; x++) {
            for (int y = 0; y < dst.height; y++) {
                int r = dst(x, y, 0);
                int g = dst(x, y, 1);
                int b = dst(x, y, 2);
                int gray = (r + g + b) / 3;
                dst(x, y, 0) = dst(x, y, 1) = dst(x, y, 2) = gray;
            }
        }
        return dst;
    }

    Image invert_image(const Image& src) { // filter 3
        Image dst = src;
        for (int i = 0; i < dst.width; i++) {
            for (int j = 0; j < dst.height; j++) {
                for (int z=0; z<3; z++) {
                    dst(i,j,z)=255-dst(i,j,z);
                }
            }
        }
        return dst;
    }

    void saveImage( Image& img, const string& filename) {
        img.saveImage(filename);
    }
};

void menu() {
    cout << "Filters available: \n 1.To gray \n 2........ \n 3.Invert colors \n " << endl;
    cout << "Which filter do you want to apply? " << endl;
}

Image process(int filter_number , Image image , string pictureName) {
    ImageEditor editor;
    Image resultImg = image;

    if (filter_number == 1) {
        resultImg = editor.toGray(image);
    }
    else if (filter_number == 2) {
        resultImg = editor.invert_image(image);
    }
    string outputName = pictureName + "_filtered.png";
    editor.saveImage(resultImg, outputName);
    cout << "Image saved as " << outputName << endl;
}

int main() {
    string pictureName, extention;
    cout << "Enter the picture name (without extension): " << endl;
    cin >> pictureName;

    cout << "Enter the image extention : " << endl;
    cin >> extention;

    string picturePath = pictureName + "." + extention;
    Image image(picturePath);

    menu();

    int filter_number;
    cin >> filter_number;

    ImageEditor editor;
    Image resultImg = image;

    process(filter_number,image, pictureName);

    return 0;
}