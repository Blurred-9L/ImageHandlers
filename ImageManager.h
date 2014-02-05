#ifndef IMAGE_MANAGER_H
#define IMAGE_MANAGER_H

#include <fstream>
#include <string>

typedef unsigned char byte;

class ImageBuffer;

class ImageManager {
private:
    std::fstream file_;
    std::string filename_;
    byte *rawData_;
    int fileSize_;
    
public:
    enum ImageManagerStatus {
        IMG_NO_ERROR = 0,
        IMG_INVALID_FILE = -1,
        IMG_ALREADY_OPEN = -2,
        IMG_NOT_OPEN = -3
    };

    ImageManager();
    explicit ImageManager(const std::string &filename);
    ~ImageManager();
    std::fstream& file();
    std::string& filename();
    byte * const rawData() const;
    int fileSize() const;
    void setFilename(const std::string &filename);
    int openFile();
    virtual int readContents();
    int closeFile();
    virtual int getImage(ImageBuffer &buffer) = 0;
    virtual int writeBuffer(ImageBuffer &buffer) = 0;
};

#endif // Not IMAGE_MANAGER_H
