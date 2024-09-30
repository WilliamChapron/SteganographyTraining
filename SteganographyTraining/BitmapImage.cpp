#include "BitmapImage.h"

BitmapImage::BitmapImage() : pixelData(nullptr), rowPadded(0)
{
}

BitmapImage::~BitmapImage()
{
    if (pixelData) {
        delete[] pixelData;
    }
}

bool BitmapImage::Load(const std::string& filePath)
{
    std::cout << "Tentative de chargement de l'image BMP depuis : " << filePath << std::endl;

    std::ifstream file(filePath, std::ios::binary);
    if (!file) {
        std::cout << "Erreur : Impossible d'ouvrir le fichier " << filePath << std::endl;
        return false;
    }

    if (!ReadFileHeader(file)) {
        return false;
    }

    if (!ReadInfoHeader(file)) {
        return false;
    }

    return ReadPixelData(file);
}

bool BitmapImage::ReadFileHeader(std::ifstream& file)
{
    file.read(reinterpret_cast<char*>(&fileHeader), sizeof(fileHeader));

    if (fileHeader.bfType != 0x4D42) {
        std::cout << "Erreur : Le fichier n'est pas un fichier BMP valide." << std::endl;
        return false;
    }

    std::cout << "File Header:" << std::endl;
    std::cout << "  bfType: " << fileHeader.bfType << std::endl;
    std::cout << "  bfSize: " << fileHeader.bfSize << std::endl;
    std::cout << "  bfReserved1: " << fileHeader.bfReserved1 << std::endl;
    std::cout << "  bfReserved2: " << fileHeader.bfReserved2 << std::endl;
    std::cout << "  bfOffBits: " << fileHeader.bfOffBits << std::endl;

    return true;
}

bool BitmapImage::ReadInfoHeader(std::ifstream& file)
{
    file.read(reinterpret_cast<char*>(&infoHeader), sizeof(infoHeader));

    std::cout << "Info Header:" << std::endl;
    std::cout << "  biSize: " << infoHeader.biSize << std::endl;
    std::cout << "  biWidth: " << infoHeader.biWidth << std::endl;
    std::cout << "  biHeight: " << infoHeader.biHeight << std::endl;
    std::cout << "  biPlanes: " << infoHeader.biPlanes << std::endl;
    std::cout << "  biBitCount: " << infoHeader.biBitCount << std::endl;
    std::cout << "  biCompression: " << infoHeader.biCompression << std::endl;
    std::cout << "  biSizeImage: " << infoHeader.biSizeImage << std::endl;
    std::cout << "  biXPelsPerMeter: " << infoHeader.biXPelsPerMeter << std::endl;
    std::cout << "  biYPelsPerMeter: " << infoHeader.biYPelsPerMeter << std::endl;
    std::cout << "  biClrUsed: " << infoHeader.biClrUsed << std::endl;
    std::cout << "  biClrImportant: " << infoHeader.biClrImportant << std::endl;

    if (infoHeader.biBitCount != 24) {
        std::cout << "Erreur! Seuls les fichiers BMP 24 bits sont supportes." << std::endl;
        return false;
    }

    int bytesPerPixel = infoHeader.biBitCount / 8;
    rowPadded = (infoHeader.biWidth * bytesPerPixel);

    return true;
}

bool BitmapImage::ReadPixelData(std::ifstream& file)
{
    pixelData = new uint8_t[rowPadded * infoHeader.biHeight];
    file.read(reinterpret_cast<char*>(pixelData), rowPadded * infoHeader.biHeight);

    std::cout << "Donnees de l'image chargees avec succes." << std::endl;
    std::cout << "Le fichier BMP est au format 24 bits." << std::endl;
    std::cout << "Image BMP chargee correctement." << std::endl;

    return true;
}

bool BitmapImage::Save(const std::string& filePath)
{
    std::ofstream file(filePath, std::ios::binary);
    if (!file) {
        std::cout << "Erreur : Impossible de sauvegarder l'image." << std::endl;
        return false;
    }

    WriteFileHeader(file);
    WriteInfoHeader(file);
    WritePixelData(file);

    std::cout << "Image sauvegardee avec succes dans : " << filePath << std::endl;
    return true;
}

void BitmapImage::WriteFileHeader(std::ofstream& file)
{
    file.write(reinterpret_cast<char*>(&fileHeader), sizeof(fileHeader));
}

void BitmapImage::WriteInfoHeader(std::ofstream& file)
{
    file.write(reinterpret_cast<char*>(&infoHeader), sizeof(infoHeader));
}

void BitmapImage::WritePixelData(std::ofstream& file)
{
    file.write(reinterpret_cast<char*>(pixelData), rowPadded * infoHeader.biHeight);
}

uint8_t* BitmapImage::GetPixelData() {
    return pixelData;
}

int BitmapImage::GetWidth() const {
    return infoHeader.biWidth;
}

int BitmapImage::GetHeight() const {
    return infoHeader.biHeight;
}

int BitmapImage::GetRowPadded() const {
    return rowPadded;
}
