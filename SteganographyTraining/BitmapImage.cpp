#include <stdio.h>
#include <iostream>
#include "BitmapImage.h"

BitmapImage::BitmapImage()
{
    m_fileHeader = new BITMAPFILEHEADER;
    m_infoHeader = new BITMAPINFOHEADER;
    m_info = new BITMAPINFO;
    m_pixels = nullptr;
};
BitmapImage::~BitmapImage()
{
    delete[] m_pixels;
    delete m_fileHeader;
    delete m_infoHeader;
    delete m_info;
};

bool BitmapImage::loadFile(const char* fileName)
{
    FILE* file;
    fopen_s(&file, fileName, "rb");
    if (file == NULL)
        throw "NoBMP";
    fseek(file, 0, SEEK_END);
    int size = ftell(file);
    uint8_t bufferHeader[54] = {};
    m_pixels = new uint8_t[size - 54];
    fseek(file, 0, SEEK_SET);
    fread(bufferHeader, sizeof(uint8_t), 54, file);

    m_fileHeader->bfType = *(uint16_t*)(bufferHeader);
    m_fileHeader->bfSize = *(uint32_t*)(bufferHeader + 2);
    m_fileHeader->bfReserved1 = *(uint16_t*)(bufferHeader + 6);
    m_fileHeader->bfReserved2 = *(uint16_t*)(bufferHeader + 8);
    m_fileHeader->bfOffBits = *(uint32_t*)(bufferHeader + 10);

    m_infoHeader->biSize = *(uint32_t*)(bufferHeader + 14);
    m_infoHeader->biWidth = *(uint32_t*)(bufferHeader + 18);
    m_infoHeader->biHeight = *(uint32_t*)(bufferHeader + 22);
    m_infoHeader->biPlanes = *(uint16_t*)(bufferHeader + 26);
    m_infoHeader->biBitCount = *(uint16_t*)(bufferHeader + 28);
    m_infoHeader->biCompression = *(uint32_t*)(bufferHeader + 30);
    m_infoHeader->biSizeImage = *(uint32_t*)(bufferHeader + 34);
    m_infoHeader->biXPelsPerMeter = *(uint32_t*)(bufferHeader + 38);
    m_infoHeader->biYPelsPerMeter = *(uint32_t*)(bufferHeader + 42);
    m_infoHeader->biClrUsed = *(uint32_t*)(bufferHeader + 46);
    m_infoHeader->biClrImportant = *(uint32_t*)(bufferHeader + 50);

    m_info = (BITMAPINFO*)m_infoHeader;

    fread(m_pixels, sizeof(uint8_t), size - m_fileHeader->bfOffBits, file);
    fclose(file);
    return true;
}

bool BitmapImage::saveFile(const char* fileName)
{
    FILE* file;
    fopen_s(&file, fileName, "wb");
    fwrite(m_fileHeader, sizeof(uint8_t), 14, file);
    fwrite(m_infoHeader, sizeof(uint8_t), 40, file);
    fwrite(m_pixels, sizeof(uint8_t), m_fileHeader->bfSize, file);
    fclose(file);
    return 1;
}