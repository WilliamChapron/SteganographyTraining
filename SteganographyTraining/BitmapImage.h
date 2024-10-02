#pragma once

#include <iostream>
#include <fstream>
#include <windows.h>

// Encapsulate Bitmap Window Librairie
class BitmapImage 
{
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

    inline uint8_t* GetPixelData() { return m_pPixelData;}
    inline int GetWidth() const { return m_infoHeader.biWidth;}
    inline int GetHeight() const { return m_infoHeader.biHeight;}
    inline int GetRowPadded() const { return m_rowPadded;}

    BITMAPFILEHEADER m_fileHeader;
    BITMAPINFOHEADER m_infoHeader;
    uint8_t* m_pPixelData;


    // W
    std::string m_currentImgPath;

    int m_width;
    int m_height;
    int m_rowPadded;

private:

};