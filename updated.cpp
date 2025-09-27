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

    Image toBlackWhite(const Image& src, int limit = 128) { // filter 2
        Image dst = src;
        for (int x = 0; x < dst.width; x++) {
            for (int y = 0; y < dst.height; y++) {
                int r = dst(x, y, 0);
                int g = dst(x, y, 1);
                int b = dst(x, y, 2);

                int gray = (r + g + b) / 3;

                int bw;

                if (gray >= limit) {
                    bw = 255;  // white
                } 
                else {
                    bw = 0;    // black
                }

                dst(x, y, 0) = dst(x, y, 1) = dst(x, y, 2) = bw;
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

    Image flip_image(const Image& src, bool horizontal) { // filter 5
        Image dst = src;

        if (horizontal) {
            // Horizontal flip:
            for (int x = 0; x < dst.width; x++) {
                for (int y = 0; y < dst.height; y++) {
                    for (int c = 0; c < 3; c++) {
                        dst(x, y, c) = src(dst.width - 1 - x, y, c);
                    }
                }
            }
        } 
        else {
            // Vertical flip:
            for (int x = 0; x < dst.width; x++) {
                for (int y = 0; y < dst.height; y++) {
                    for (int c = 0; c < 3; c++) {
                        dst(x, y, c) = src(x, dst.height - 1 - y, c);
                    }
                }
            }
        }

        return dst;
    }

    Image rotate_image_180(const Image &scr) {
        Image dst(scr.width,scr.height);
        for (int i = scr.width-1; i >= 0; i--) {
            for (int j = scr.height-1; j >= 0; j--) {
                for (int k = 0; k < 3; k++) {
                    dst(scr.width-i-1,scr.height-j-1,k)=scr(i,j,k);
                }
            }
        }
        return dst;
    }

    Image rotate_image_270(const Image &scr ) { // 270 degree
        Image dst(scr.height, scr.width);
        for (int i = 0; i < scr.height; i++) {
            for (int j = 0; j < scr.width; j++) {
                for (int k = 0; k < 3; k++){
                    dst(i,j,k) = scr(scr.width-1-j , i, k);
                }
            }
        }
        return dst;
    }

    Image rotate_image_90(const Image &scr) {
        Image tmp = rotate_image_270(scr);
        return rotate_image_180(tmp);
    }

    void saveImage( Image& img, const string& filename) {
        img.saveImage(filename);
    }
};

void menu() {
    cout << "Filters available: \n";
    cout << " 1. Gray filter\n";
    cout << " 2. Black & White filter\n";
    cout << " 3. Invert colors\n";
    cout << " 5. Flip image\n";
    cout << " 6. Rotate image\n";
    cout << "\nWhich filter do you want to apply? " << endl;
}

Image process(int filter_number , Image image , string pictureName) {
    ImageEditor editor;
    Image resultImg = image;

    if (filter_number == 1) {
        resultImg = editor.toGray(image);
    }
    else if (filter_number == 2) {
        resultImg = editor.toBlackWhite(image);
    }
    else if (filter_number == 3) {
        resultImg = editor.invert_image(image);
    }
    else if (filter_number == 5) {
        int choice;
        cout << "Flip horizontally (1) or vertically (0)? \n";
        cin >> choice;
        resultImg = editor.flip_image(image, choice == 1);
    }
    else if (filter_number == 6) {
        int rotation_angle;
        cout << "Enter the rotation angle (90,180,270) : " << endl;
        cin >> rotation_angle;
        if (rotation_angle == 90) {
            resultImg = editor.rotate_image_90(image);
        }
        else if (rotation_angle == 180) {
            resultImg = editor.rotate_image_180(image);
        }
        else if (rotation_angle == 270) {
            resultImg = editor.rotate_image_270(image);
        }
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
