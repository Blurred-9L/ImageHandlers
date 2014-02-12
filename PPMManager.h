#ifndef PPM_MANAGER_H
#define PPM_MANAGER_H

#include "ImageManager.h"

class ImageBuffer;

class PPMManager : public ImageManager {
private:
    char ppmType_;
    unsigned short maxColor_;
    
public:
    enum PPMType {
        PPM_TEXT = '3',
        PPM_BIN = '6'
    };
    
    enum PPMStatus {
        PPM_NOT_PPM = -4
    };

    PPMManager();
    PPMManager(const std::string &filename);
    char ppmType() const;
    unsigned short maxColor() const;
    void setType(PPMType type);
    void setMaxColor(unsigned short maxColor);
    virtual ImageBuffer *getImage();
    virtual int writeBuffer(ImageBuffer &buffer);
};

#endif // Not PPM_MANAGER_H
