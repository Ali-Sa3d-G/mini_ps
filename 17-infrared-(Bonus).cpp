/*
    CS213_Opject Orinted Programing_A1_Part1
        *1.Name: Abdullah Youssef Abdullah- ID: 20240331 - Implemented filtes 1(Grayscale Conversion) & 4(Merge Images) 
        *2.Name: Ali Ahmed Mahmoud - ID: 20240337 - Implemented filters 2(Black and White) & 5(Flip Image)
        *3.Name: Yassin Mohamed Abdelaziz - ID: 20240663 - Implemented filters 3(Invert Image) & 6(Rotate Image)
*/


#include "Image_Class.h"
#include <iostream>
#include <string>
#include <algorithm>
#include <cmath>

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
    Image margeImages(const Image& src , const Image& src2 )  { // filter 4    
        bool sameWidth=0, sameHeigth=0;
        if (src.width == src2.width)
        {
            sameWidth=1;
        }
        if (src.height == src2.height)
        {
            sameHeigth=1;
        }
        if (sameWidth && sameHeigth)
        {
            Image dst = src;
            for (int i = 0; i < src.width; i++)
            {
                for (int j = 0; j < src.height; j++)
                {
                    for ( int k = 0; k < 3; k++)
                    {
                        int pix = (src(i,j,k)+src2(i,j,k))/2;
                        dst(i,j,k) =pix;
                    }
                    
                }
                
            }
            
        return dst;
        }
        else 
        {
            int min_w=min(src.width,src2.width),min_h=min(src.height,src2.height),pix;
            int max_w=max(src.width,src2.width),max_h=max(src.height,src2.height);
            Image dst;
                if (src.width < src2.width && src.height < src2.height )
                {  
                    dst=src2;
                    for (int i = 0; i < max_w; i++)
                    {
                        for (int j = 0; j < max_h; j++)
                        {
                            for (int k = 0; k < 3; k++)
                            {
                                if (i<min_w &&   j<min_h)
                                {
                                    pix = (src(i,j,k)+src2(i,j,k))/2;
                                    dst(i,j,k) =pix;
                                }

                            }
                            
                        }
                        
                    }
                    
                }
                else if (src.width > src2.width && src.height > src2.height )
                {
                    dst=src;
                    for (int i = 0; i < max_w; i++)
                    {
                        for (int j = 0; j < max_h; j++)
                        {
                            for (int k = 0; k < 3; k++)
                            {
                                if (i<min_w &&   j<min_h)
                                {
                                    pix = (src(i,j,k)+src2(i,j,k))/2;
                                    dst(i,j,k) =pix;
                                }

                            }
                            
                        }
                        
                    }
                }
                else
                {  
                    Image dst(min_w,min_h);
                    for (int i = 0; i < min_w; i++)
                    {
                        for (int j = 0; j < min_h; j++)
                        {
                            for (int k = 0; k < 3; k++)
                            {
                                pix = (src(i,j,k)+src2(i,j,k))/2;
                                dst(i,j,k) =pix;
                            }
                            
                        }
                        
                    }                 
                }
                  
        return dst;
        }
        
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

    Image Dark(const Image &scr) // Filter 7.1 
    {
        Image dst=scr;
        for (int i = 0; i < dst.width; i++)
        {
            for (int j = 0; j < dst.height; j++)
            {
                for (int k = 0; k < 3; k++)
                {
                    dst(i,j,k)=scr(i,j,k)/2;
                }
                
            }
            
        }
       return dst; 
    }
        Image light(const Image &scr) // Filter 7.2
    {
        Image dst=scr;
        for (int i = 0; i < dst.width; i++)
        {
            for (int j = 0; j < dst.height; j++)
            {
                for (int k = 0; k < 3; k++)
                {
                    dst(i,j,k)=min(255,int(scr(i,j,k)*1.5));
                }
                
            }
            
        }
       return dst; 
    }
    Image edges(const Image &scr) // filter 10
    {
        Image dst =scr;
        for (int i = 0; i < dst.width-1; i++)
        {
            for (int j = 0; j < dst.height-1; j++)
            {
                double  x =0.299*scr (i,j,0) + 0.587*scr (i,j,1) + 0.114*scr (i,j,2);
                double  y=0.299*scr (i+1,j,0) + 0.587*scr (i+1,j,1) + 0.114*scr (i+1,j,2);
                double  z=0.299*scr (i,j+1,0) + 0.587*scr (i,j+1,1) + 0.114*scr (i,j+1,2);
                if (abs(x-y)>30 || abs(x-z)>30)
                {
                    dst(i,j,0)=dst(i,j,1)=dst(i,j,2)=0;
                }
                else
                {
                    dst(i,j,0)=dst(i,j,1)=dst(i,j,2)=255;
                }
                
                
            }
            
        }
        dst(dst.width-1,dst.height-1,0)=dst(dst.width-1,dst.height-1,1)=dst(dst.width-1,dst.height-1,2)=255;
        return dst;
    }
    Image Infrared(const Image &scr)  // filter 17
   {
       Image dst = scr;
       for (int i = 0; i < scr.width; i++)
       {
            for (int j = 0; j < scr.height; j++)
            {
                dst(i, j, 0) = 255;
                dst(i, j, 1) = 250-min(200,int(dst(i, j, 1)+dst(i, j, 2))/2);
                dst(i, j, 2) = dst(i, j, 1);
            }
        }
        return dst;
   }

};

void menu() {
    cout << "Filters available: \n";
    cout << " 1. Gray filter\n";
    cout << " 2. Black & White filter\n";
    cout << " 3. Invert colors\n";
    cout << " 4. Marge 2 images\n";
    cout << " 5. Flip image\n";
    cout << " 6. Rotate image\n";
    cout << " 7. Darken and Lighten Image\n";
    cout << " 10. Detect Image Edges\n";
    cout << " 13. Infrared\n";
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
    else if (filter_number == 4)
    {
        string secondName,secondExtention , picturePath;
        cout<< "Enter second image name\n";
        cin>>secondName;
        cout<< "Enter second image extention\n";
        cin>>secondExtention;
        picturePath=secondName + "." + secondExtention;
        Image second(picturePath) ;
        resultImg = editor.margeImages(image,second);


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
    else if (filter_number == 7)
    {
        int DarkOrLight;
        cout << "1. Darken\n";
        cout << "2. lighten\n";
        cin >>DarkOrLight;
        if (DarkOrLight == 1)
        {
            resultImg = editor.Dark(image);
        }
        else if (DarkOrLight == 2)
        {
            resultImg = editor.light(image);
        }
    }
    else if (filter_number == 10)
    {
        resultImg = editor.edges(image);
    }
    else if (filter_number == 13)
    {
        resultImg = editor.Infrared(image);
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
