#ifndef IMAGE_BUFFER_H
#define IMAGE_BUFFER_H

typedef unsigned char byte;

class ImageBuffer {
public:
    enum ImageType {
        IMAGE_GRAY = 0,
        IMAGE_RED = 1,
        IMAGE_GREEN = 2,
        IMAGE_BLUE = 4,
        IMAGE_ALPHA = 8,
        IMAGE_RGB = 7,
        IMAGE_RGBA = 15
    };
    
    enum ImageAlign {
        ALIGN_8 = 1,
        ALIGN_16 = 2,
        ALIGN_32 = 4
    };
    
private:
    byte *data_;
    unsigned width_;
    unsigned height_;
    unsigned rowSize_;
    ImageType type_;
    char bitsPerPixel_;
    ImageAlign alignment_;
    bool topDownOrder_;
    
public:
    ImageBuffer(unsigned width, unsigned height, ImageType type = IMAGE_GRAY, ImageAlign align = ALIGN_8, bool topDown = true);
    ~ImageBuffer();
    byte * const data() const;
    unsigned width() const;
    unsigned height() const;
    unsigned rowSize() const;
    ImageType type() const;
    char bitsPerPixel() const;
    ImageAlign alignment() const;
    bool isTopDown();
};

#endif // Not IMAGE_MANAGER_H
