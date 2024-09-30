#pragma once

#include <iostream>
#include <fstream>
#include <windows.h>

// Encapsulate Bitmap Window Librairie
class BitmapImage 
{
private:
    BITMAPFILEHEADER fileHeader;
    BITMAPINFOHEADER infoHeader;
    uint8_t* pixelData;

    int width;
    int height;
    int rowPadded;
public:
    BitmapImage();

    ~BitmapImage();

    bool Load(const std::string& filePath);

    bool ReadFileHeader(std::ifstream& file);

    bool ReadInfoHeader(std::ifstream& file);
    bool ReadPixelData(std::ifstream& file);

    bool Save(const std::string& filePath);

    void WriteFileHeader(std::ofstream& file);
    void WriteInfoHeader(std::ofstream& file);
    void WritePixelData(std::ofstream& file);

    uint8_t* GetPixelData();

    int GetWidth() const;
    int GetHeight() const;

    int GetRowPadded() const;
};