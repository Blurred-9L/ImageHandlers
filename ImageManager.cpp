#include "ImageManager.h"
#include "ImageBuffer.h"

#include <fstream>
#include <string>

ImageManager::ImageManager() : filename_(), rawData_(0), fileSize_(0)
{
}

ImageManager::ImageManager(const std::string &filename) : filename_(filename),
    rawData_(0), fileSize_(0)
{
}

ImageManager::~ImageManager()
{
    if (file_.is_open()) {
        file_.close();
    }
    if (rawData_ != 0) {
        delete [] rawData_;
    }
}

std::fstream& ImageManager::file()
{
    return file_;
}

std::string& ImageManager::filename()
{
    return filename_;
}

byte * const ImageManager::rawData() const
{
    return rawData_;
}

int ImageManager::fileSize() const
{
    return fileSize_;
}

void ImageManager::setFilename(const std::string &filename)
{
    filename_ = filename;
}

int ImageManager::openFile()
{
    int retValue = IMG_NO_ERROR;
    
    if (!file_.is_open()) {
        file_.open(filename_.c_str(), std::fstream::in);
        if (file_.is_open()) {
            fileSize_ = 0;
            if (rawData_ != 0) {
                delete[] rawData_;
                rawData_ = 0;
            }
        } else {
            retValue = IMG_INVALID_FILE;
        }
    } else {
        retValue = IMG_ALREADY_OPEN;
    }
    
    return retValue;
}

int ImageManager::readContents()
{
    int retValue = IMG_NO_ERROR;
    
    if (file_.is_open()) {
        file_.seekg(0, file_.end);
        fileSize_ = file_.tellg();
        file_.seekg(0, file_.beg);
        rawData_ = new byte[fileSize_];
    } else {
        retValue = IMG_NOT_OPEN;
    }
    
    return retValue;
}

int ImageManager::closeFile()
{
    if (file_.is_open()) {
        file_.close();
    }
    
    return IMG_NO_ERROR;
}
