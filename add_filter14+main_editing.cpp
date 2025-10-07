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
#include <vector>

using namespace std;

struct pixels {          // needed for filter 14
    int red,green,blue;
};

Image colored_image(Image x , int color) {     // Needed for filter 9   yassen mohamed
    if (color == 1) {
        Image result(x.width+100,x.height+100);
        for (int i = 0; i < result.width; i++) {
            for (int j = 0; j < result.height; j++) {
                for (int k = 0; k < 3; k++) {
                    result(i,j,k)=0;
                }
            }
        }
        return result;
    }
    else if (color == 2) {
        Image result(x.width+100,x.height+100);
        for (int i = 0; i < result.width; i++) {
            for (int j = 0; j < result.height; j++) {
                result(i,j,0)=255;
                result(i,j,1)=0;
                result(i,j,2)=0;
            }
        }
        return result;
    }
    else if (color == 3) {
        Image result(x.width+100,x.height+100);
        for (int i = 0; i < result.width; i++) {
            for (int j = 0; j < result.height; j++) {
                result(i,j,0)=0;
                result(i,j,1)=255;
                result(i,j,2)=0;
            }
        }
        return result;
    }
    else if (color == 4) {
        Image result(x.width+100,x.height+100);
        for (int i = 0; i < result.width; i++) {
            for (int j = 0; j < result.height; j++) {
                result(i,j,0)=0;
                result(i,j,1)=0;
                result(i,j,2)=255;
            }
        }
        return result;
    }
    else if (color == 5) {
        Image result(x.width+100,x.height+100);
        for (int i = 0; i < result.width; i++) {
            for (int j = 0; j < result.height; j++) {
                result(i,j,0)=255;
                result(i,j,1)=255;
                result(i,j,2)=255;
            }
        }
        return result;
    }
    else if (color == 6) {
        Image result(x.width+100,x.height+100);
        for (int i = 0; i < result.width; i++) {
            for (int j = 0; j < result.height; j++) {
                result(i,j,0)=255;
                result(i,j,1)=255;
                result(i,j,2)=0;
            }
        }
        return result;
    }
    else if (color == 7) {
        Image result(x.width+100,x.height+100);
        for (int i = 0; i < result.width; i++) {
            for (int j = 0; j < result.height; j++) {
                result(i,j,0)=255;
                result(i,j,1)=0;
                result(i,j,2)=255;
            }
        }
        return result;
    }
    throw invalid_argument("Invalid color option");
}

class ImageEditor {
public:
    Image toGray(const Image& src) { // filter 1                       Abdullah Youssef Abdullah 20240331
        Image dst = src;
        for (int i = 0; i < dst.width; i++)
        {
            for (int j = 0; j < dst.height; j++)
            {
                int gray=0;
                gray = (dst(i,j,0)+dst(i,j,1)+dst(i,j,2))/3;
                for (int k = 0; k < 3; k++)
                {
                    dst(i,j,k)=gray;
                }

            }
        }
        return dst;
    }

    Image toBlackWhite(const Image& src, int limit = 128) { // filter 2  Ali Saad
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

    Image invert_image(const Image& src) { // filter 3   yassen mohamed
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
    Image margeImages(const Image& src , const Image& src2 )  { // filter 4       Abdullah Youssef Abdullah 20240331
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

    Image flip_image(const Image& src, bool horizontal) { // filter 5   Ali Saad
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

    Image rotate_image_180(const Image &scr) {   // yassen mohamed
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

    Image rotate_image_270(const Image &scr ) { // 270 degree    yassen mohamed
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

    Image rotate_image_90(const Image &scr) {   // yassen mohamed
        Image tmp = rotate_image_270(scr);
        return rotate_image_180(tmp);
    }

    void saveImage( Image& img, const string& filename) {
        img.saveImage(filename);
    }

    Image Dark(const Image &scr) // Filter 7.1         Abdullah Youssef Abdullah 20240331
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
        Image light(const Image &scr) // Filter 7.2     Abdullah Youssef Abdullah 20240331
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


    Image crop_image(const Image& src) { // Filter 8  Ali Saad
        int X, Y, W, H;

        cout << "Enter top-left corner (X,Y): ";
        cin >> X >> Y;
        cout << "Enter width and height (W,H): ";
        cin >> W >> H;

        if (X < 0 || Y < 0 || X + W > src.width || Y + H > src.height) {
            cout << "Error: Crop dimensions are out of image bounds!" << "\n";
            return src;
        }

        Image dst(W, H);

        for (int x = 0; x < W; x++) {
            for (int y = 0; y < H; y++) {
                for (int c = 0; c < 3; c++) { // copy R,G,B channels
                    dst(x, y, c) = src(X + x, Y + y, c);
                }
            }
        }

        return dst;
    }

    Image add_simple_frame(const Image &scr , const int &color) {   // filter 9.1  yassen mohamed
        Image dst = colored_image(scr,color);
        for (int i = 50; i < dst.width-50; i++) {
            for (int j = 50; j < dst.height-50; j++) {
                for (int k = 0; k < 3; k++){
                    dst(i,j,k)=scr(i-50,j-50,k);
                }
            }
        }
        return dst;
    }

    Image add_decorated_frame(const Image &scr ) {                 // filter 9.2  yassen mohamed
        ImageEditor x;
        cout << "Choose the color of frame : \n 1.Black \n 2.Red \n 3.Green \n 4.Blue \n 5.White"<<endl;
        int frame_color; cin >> frame_color;
        cout << "Enter color of squares in corner : \n 1.White \n 2.Black " << endl;
        int sqr_color; cin >> sqr_color;
        Image dst = scr;
        for (int i = 0; i < 50; i++) {
            for (int j = 0; j < 50; j++) {
                for (int k = 0; k < 3; k++) {
                    if (sqr_color == 1){
                        dst(i,j,k)=255;
                    }
                    else {
                        dst(i,j,k)=0;
                    }
                }
            }
        }
        for (int i = 0; i < 50; i++) {
            for (int j = dst.height-1; j >= dst.height-51; j--) {
                for (int k = 0; k < 3; k++) {
                    if (sqr_color == 1){
                        dst(i,j,k)=255;
                    }
                    else {
                        dst(i,j,k)=0;
                    }
                }
            }
        }
        for (int i = dst.width-1; i >= dst.width-51; i--) {
            for (int j = 0; j < 50; j++) {
                for (int k = 0; k < 3; k++) {
                    if (sqr_color == 1){
                        dst(i,j,k)=255;
                    }
                    else {
                        dst(i,j,k)=0;
                    }
                }
            }
        }
        for (int i = dst.width-1; i >= dst.width-51; i--) {
            for (int j = dst.height-1; j >= dst.height-51; j--) {
                for (int k = 0; k < 3; k++) {
                    if (sqr_color == 1){
                        dst(i,j,k)=255;
                    }
                    else {
                        dst(i,j,k)=0;
                    }
                }
            }
        }
        dst = x.add_simple_frame(dst,frame_color);
        for (int i = 0; i < 10; i++) {
            for (int j = 0; j < dst.height; j++) {
                for (int k = 0; k < 3; k++) {
                    if (sqr_color == 1){
                        dst(i,j,k)=255;
                    }
                    else {
                        dst(i,j,k)=0;
                    }
                }
            }
        }
        for (int i = 0; i < dst.width; i++) {
            for (int j = 0; j < 10; j++) {
                for (int k = 0; k < 3; k++) {
                    if (sqr_color == 1){
                        dst(i,j,k)=255;
                    }
                    else {
                        dst(i,j,k)=0;
                    }
                }
            }
        }
        for (int i = dst.width-10; i < dst.width; i++) {
            for (int j = 0; j < dst.height; j++) {
                for (int k = 0; k < 3; k++) {
                    if (sqr_color == 1){
                        dst(i,j,k)=255;
                    }
                    else {
                        dst(i,j,k)=0;
                    }
                }
            }
        }
        for (int i = 0; i < dst.width; i++) {
            for (int j = dst.height-10; j < dst.height; j++) {
                for (int k = 0; k < 3; k++) {
                    if (sqr_color == 1){
                        dst(i,j,k)=255;
                    }
                    else {
                        dst(i,j,k)=0;
                    }
                }
            }
        }
        for (int i = 40; i <= 50; i++) {
            for (int j = 50; j < dst.height-50; j++) {
                for (int k = 0; k < 3; k++) {
                    if (sqr_color == 1){
                        dst(i,j,k)=255;
                    }
                    else {
                        dst(i,j,k)=0;
                    }
                }
            }
        }
        for (int i = 40; i <= dst.width-50; i++) {
            for (int j = 40; j <= 50; j++) {
                for (int k = 0; k < 3; k++) {
                    if (sqr_color == 1){
                        dst(i,j,k)=255;
                    }
                    else {
                        dst(i,j,k)=0;
                    }
                }
            }
        }
        for (int i = dst.width-50; i < dst.width-40; i++) {
            for (int j = 40; j <= dst.height-50; j++) {
                for (int k = 0; k < 3; k++) {
                    if (sqr_color == 1){
                        dst(i,j,k)=255;
                    }
                    else {
                        dst(i,j,k)=0;
                    }
                }
            }
        }
        for (int i = 40; i < dst.width-40; i++) {
            for (int j = dst.height-50; j <= dst.height-40; j++) {
                for (int k = 0; k < 3; k++) {
                    if (sqr_color == 1){
                        dst(i,j,k)=255;
                    }
                    else {
                        dst(i,j,k)=0;
                    }
                }
            }
        }
        return dst;
    }

    Image edges(const Image &scr) // filter 10     Abdullah Youssef Abdullah 20240331
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



    Image resize_image(const Image& src) { // Filter 11  Ali Saad
        int choice;
        cout << "Resize by: \n";
        cout << "1. New dimensions: (width & height)\n";
        cout << "2. Scale ratio :\n";
        cout << "Enter your choice: ";
        cin >> choice;

        int newWidth, newHeight;

        if (choice == 1) {
            cout << "Enter new width: ";
            cin >> newWidth;
            cout << "Enter new height: ";
            cin >> newHeight;
        }
        else if (choice == 2) {
            double scale;
            cout << "Enter scale percentage: ";
            cin >> scale;
            scale /= 100.0;
            newWidth = static_cast<int>(src.width * scale);
            newHeight = static_cast<int>(src.height * scale);
        }
        else {
            cout << "Invalid choice.\n";
            return src;
        }

        Image dst(newWidth, newHeight);

        for (int x = 0; x < newWidth; x++) {
            for (int y = 0; y < newHeight; y++) {
                int srcX = static_cast<int>(x * src.width / newWidth);
                int srcY = static_cast<int>(y * src.height / newHeight);
                for (int c = 0; c < 3; c++) {
                    dst(x, y, c) = src(srcX, srcY, c);
                }
            }
        }

        return dst;
    }

    Image blur_image(const Image &src) {    // filter 12   yassen mohamed
        Image dst = src;
        int width = src.width;
        int height = src.height;

        for (int i = 2; i < width - 2; i++) {
            for (int j = 2; j < height - 2; j++) {
                for (int k = 0; k < 3; k++) {
                    int sum = 0;
                    for (int x = -2; x <= 2; x++) {
                        for (int y = -2; y <= 2; y++) {
                            sum += src(i + x, j + y, k);
                        }
                    }
                    dst(i, j, k) = sum / 25;
                }
            }
        }
        return dst;
    }

    Image sun_ray(const Image &scr) {        // filter 13 yassen mohamed
        Image dst = scr;
        for (int i = 0; i< dst.width; i++) {
            for (int j = 0; j < dst.height; j++) {
                dst(i,j,0) = min(dst(i,j,0)+30,255);
                dst(i,j,1) = min(dst(i,j,1)+30,255);
            }
        }
        return dst;
    }

    Image oil_painting(const Image &scr) {     // filter 14 yassen mohamed
        Image dst = scr;
        for (int i = 1; i < dst.width-1; i++) {
            for (int j = 1; j < dst.height-1; j++) {

                vector<pixels> bin[8];
                for (int x = i - 1; x <= i + 1; x++) {
                    for (int y = j - 1; y <= j + 1; y++) {
                        double intensity=0.299*dst(x,y,0)+0.587*dst(x,y,1)+0.114*dst(x,y,2);
                            if (intensity <= 31) {
                                pixels colors;
                                colors.red = dst(x,y,0);
                                colors.green = dst(x,y,1);
                                colors.blue = dst(x,y,2);
                                bin[0].push_back(colors);
                            }
                            else if (intensity <= 62) {
                                pixels colors;
                                colors.red = dst(x,y,0);
                                colors.green = dst(x,y,1);
                                colors.blue = dst(x,y,2);
                                bin[1].push_back(colors);
                            }
                            else if (intensity <= 93) {
                                pixels colors;
                                colors.red = dst(x,y,0);
                                colors.green = dst(x,y,1);
                                colors.blue = dst(x,y,2);
                                bin[2].push_back(colors);
                            }
                            else if (intensity <= 124) {
                                pixels colors;
                                colors.red = dst(x,y,0);
                                colors.green = dst(x,y,1);
                                colors.blue = dst(x,y,2);
                                bin[3].push_back(colors);
                            }
                            else if (intensity <= 155) {
                                pixels colors;
                                colors.red = dst(x,y,0);
                                colors.green = dst(x,y,1);
                                colors.blue = dst(x,y,2);
                                bin[4].push_back(colors);
                            }
                            else if (intensity <= 186) {
                                pixels colors;
                                colors.red = dst(x,y,0);
                                colors.green = dst(x,y,1);
                                colors.blue = dst(x,y,2);
                                bin[5].push_back(colors);
                            }
                            else if (intensity <= 217) {
                                pixels colors;
                                colors.red = dst(x,y,0);
                                colors.green = dst(x,y,1);
                                colors.blue = dst(x,y,2);
                                bin[6].push_back(colors);
                            }
                            else if (intensity <= 255) {
                                pixels colors;
                                colors.red = dst(x,y,0);
                                colors.green = dst(x,y,1);
                                colors.blue = dst(x,y,2);
                                bin[7].push_back(colors);
                            }
                    }
                }
                int freq = 0;
                int position;
                for (int z = 0; z < 8; z++) {
                    if (bin[z].size() > freq) {
                        freq = bin[z].size();
                        position = z;
                    }
                }
                int new_r=0 , new_g=0 , new_b=0;
                for (int z = 0; z < bin[position].size(); z++) {
                    new_r += bin[position][z].red;
                    new_g += bin[position][z].green;
                    new_b += bin[position][z].blue;
                }
                new_r /= bin[position].size();
                new_g /= bin[position].size();
                new_b /= bin[position].size();
                dst(i,j,0) = new_r;
                dst(i,j,1) = new_g;
                dst(i,j,2) = new_b;
            }
        }
        return dst;
    }

    Image TV_Screen(const Image& src) {   // Filter 15 : Bonus : Ali Saad
        Image dst = src;
        int w = dst.width;
        int h = dst.height;

        int scan_interval = 4;
        int scan_thickness = 1;
        double scan_darkness = 0.5;

        for (int y = 0; y < h; y++) {
            if ((y % scan_interval) < scan_thickness) {
                for (int x = 0; x < w; x++) {
                    for (int c = 0; c < 3; c++) {
                        dst(x, y, c) = static_cast<int>(dst(x, y, c) * scan_darkness);
                    }
                }
            }
        }

        double noise_strength = 0.08;
        for (int x = 0; x < w; x++) {
            for (int y = 0; y < h; y++) {
                int noise = (rand() % 256) - 128;
                for (int c = 0; c < 3; c++) {
                    int v = dst(x, y, c) + static_cast<int>(noise * noise_strength);
                    if (v < 0) v = 0;
                    if (v > 255) v = 255;
                    dst(x, y, c) = v;
                }
            }
        }

        return dst;
    }

    Image Purple(const Image &scr) // Filter 16      Abdullah Youssef Abdullah 20240331
    {
        Image dst = scr;
        for (int i = 0; i < dst.width; i++)
        {
            for (int j = 0; j < dst.height; j++)
            {
                dst(i,j,0)= min(255,int(scr(i,j,0)*1.1));
                dst(i,j,1)= int(scr(i,j,1)*0.8);
                dst(i,j,2)= min(255,int(scr(i,j,2)*1.2));
            }

        }
        return dst ;
    }
    Image Infrared(const Image &scr)  // Filter 17    Abdullah Youssef Abdullah 20240331
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
   Image Skewing(const Image &scr)
{
    double angle = 90 * 3.14159265358979323846  / 180;
    double skew = tan(angle);

    int h = scr.height;
    int w = scr.width + h * skew;
    Image dst(w, h);

    for (int i = 0; i < w; i++)
    {
        for (int j = 0; j < h; j++)
        {
            for (int k = 0; k < 3; k++)
            {
                int srcX = int(i-(j * skew ));
                if (srcX >= 0 && srcX < scr.width)
                {
                    dst(i, j, k) = scr(srcX, j, k);
                }
                else
                {
                    dst(i, j, k) = 255;
                }
            }
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
    cout << " 8. Crop Image\n";
    cout << " 9. Add frame\n";
    cout << " 10. Detect Image Edges\n";
    cout << " 11. Resize Image\n";
    cout << " 12. Blur image \n";
    cout << " 13. Sun ray\n";
    cout << " 14. Oil painting picture\n";
    cout << " 15. TV Screen filter\n";
    cout << " 16. Purple\n";
    cout << " 17. Infrared\n";
    cout << " 18. Skewing image\n";
    cout << "\nWhich filter do you want to apply? " << endl;
}

void process(int filter_number , Image image , string pictureName) {
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
    else if (filter_number == 8) {
    resultImg = editor.crop_image(image);
    }
    else if (filter_number == 9) {
        cout << "You want a : 1.simple frame ..or.. 2.decorated ?" << endl;
        int frame_type; cin >> frame_type;
        if (frame_type == 1) {
            cout << "Frames are : \n 1.Black \n 2.Red \n 3.Green \n 4.Blue \n 5.White \n 6.Yellow \n 7.Purple"<<endl;
            cout << "Enter the number of the frame that you want : "<<endl;
            int frame_color; cin >> frame_color;
            resultImg = editor.add_simple_frame(image,frame_color);
        }
        else if (frame_type == 2) {
            cout << "Frame is : 1.squares in the corners \n "<<endl;
            resultImg = editor.add_decorated_frame(image);
        }
    }
    else if (filter_number == 10)
    {
        resultImg = editor.edges(image);
    }
    else if (filter_number == 11) {
    resultImg = editor.resize_image(image);
    }
    else if (filter_number == 12) {
        resultImg = editor.blur_image(image);
    }
    else if (filter_number == 13)
    {
        resultImg = editor.sun_ray(image);
    }
    else if (filter_number == 14) {
        resultImg = editor.oil_painting(image);
    }
    else if (filter_number == 15) {
        resultImg = editor.TV_Screen(image);
    }
    else if (filter_number == 16) {
        resultImg = editor.Purple(image);
    }
    else if (filter_number == 17) {
        resultImg = editor.Infrared(image);
    }
    else if (filter_number == 18)
    {
        resultImg = editor.Skewing(image);
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
    process(filter_number,image, pictureName);

    bool statment = true;
    while (statment) {

        cout << "Do you want to do another filter ? \n";
        cout << "1. YES \n2. NO \n";
        int answer; cin >> answer;
        if (answer == 1) {
            cout << "The same image has been filter or another image ? \n";
            cout << "If the same image filtered , enter (1) \nIf another image , enter (2)\n";
            int answer2; cin >> answer2;
            if (answer2 == 1) {
                picturePath = pictureName + "_filtered.png";
                Image imagee(picturePath);
                menu();
                cin >> filter_number;
                process(filter_number,imagee, pictureName);
            }
            else if (answer2 == 2) {
                cout << "Enter the picture name (without extension): " << endl;
                cin >> pictureName;

                cout << "Enter the image extention : " << endl;
                cin >> extention;

                picturePath = pictureName + "." + extention;
                Image imagee(picturePath);
                menu();
                cin >> filter_number;
                process(filter_number,imagee, pictureName);
            }
            else {
                cerr << "False input \n The programe will stop. \n";
            }
        }
        else if (answer == 2) {
            statment = false;
            cout << "The programe has stopped.\n";
        }
        else {
            cerr << "False input \n The programe will stop. \n";
        }
    }
    return 0;
}