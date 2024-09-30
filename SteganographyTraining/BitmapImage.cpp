#include "BitmapImage.h"

BitmapImage::BitmapImage() : m_pPixelData(nullptr), m_rowPadded(0)
{
}

BitmapImage::~BitmapImage()
{
    if (m_pPixelData) {
        delete[] m_pPixelData;
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
    file.read(reinterpret_cast<char*>(&m_fileHeader), sizeof(m_fileHeader));

    if (m_fileHeader.bfType != 0x4D42) {
        std::cout << "Erreur : Le fichier n'est pas un fichier BMP valide." << std::endl;
        return false;
    }

    std::cout << "File Header:" << std::endl;
    std::cout << "  bfType: " << m_fileHeader.bfType << std::endl;
    std::cout << "  bfSize: " << m_fileHeader.bfSize << std::endl;
    std::cout << "  bfReserved1: " << m_fileHeader.bfReserved1 << std::endl;
    std::cout << "  bfReserved2: " << m_fileHeader.bfReserved2 << std::endl;
    std::cout << "  bfOffBits: " << m_fileHeader.bfOffBits << std::endl;

    return true;
}

bool BitmapImage::ReadInfoHeader(std::ifstream& file)
{
    file.read(reinterpret_cast<char*>(&m_infoHeader), sizeof(m_infoHeader));

    std::cout << "Info Header:" << std::endl;
    std::cout << "  biSize: " << m_infoHeader.biSize << std::endl;
    std::cout << "  biWidth: " << m_infoHeader.biWidth << std::endl;
    std::cout << "  biHeight: " << m_infoHeader.biHeight << std::endl;
    std::cout << "  biPlanes: " << m_infoHeader.biPlanes << std::endl;
    std::cout << "  biBitCount: " << m_infoHeader.biBitCount << std::endl;
    std::cout << "  biCompression: " << m_infoHeader.biCompression << std::endl;
    std::cout << "  biSizeImage: " << m_infoHeader.biSizeImage << std::endl;
    std::cout << "  biXPelsPerMeter: " << m_infoHeader.biXPelsPerMeter << std::endl;
    std::cout << "  biYPelsPerMeter: " << m_infoHeader.biYPelsPerMeter << std::endl;
    std::cout << "  biClrUsed: " << m_infoHeader.biClrUsed << std::endl;
    std::cout << "  biClrImportant: " << m_infoHeader.biClrImportant << std::endl;

    if (m_infoHeader.biBitCount != 24) {
        std::cout << "Erreur! Seuls les fichiers BMP 24 bits sont supportes." << std::endl;
        return false;
    }

    int bytesPerPixel = m_infoHeader.biBitCount / 8;
    m_rowPadded = (m_infoHeader.biWidth * bytesPerPixel);

    return true;
}

bool BitmapImage::ReadPixelData(std::ifstream& file)
{
    m_pPixelData = new uint8_t[m_rowPadded * m_infoHeader.biHeight];
    file.read(reinterpret_cast<char*>(m_pPixelData), m_rowPadded * m_infoHeader.biHeight);

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
    file.write(reinterpret_cast<char*>(&m_fileHeader), sizeof(m_fileHeader));
}

void BitmapImage::WriteInfoHeader(std::ofstream& file)
{
    file.write(reinterpret_cast<char*>(&m_infoHeader), sizeof(m_infoHeader));
}

void BitmapImage::WritePixelData(std::ofstream& file)
{
    file.write(reinterpret_cast<char*>(m_pPixelData), m_rowPadded * m_infoHeader.biHeight);
}
