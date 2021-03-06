#include "ImageBuffer.h"

ImageBuffer::ImageBuffer(unsigned width, unsigned height, ImageType type, ImageAlign align, bool topDown) :
    width_(width), height_(height), type_(type), alignment_(align), topDownOrder_(topDown)
{
	int size;
	
    bitsPerPixel_ = type_ * 8;
    rowSize_ = width_ + ((alignment_ - (width_ % alignment_)) % alignment_);
    size = rowSize_ * height_;
    if (type == IMAGE_RGB) {
    	size *= 3;
    } else if (type == IMAGE_RGBA) {
    	size *= 4;
    }
    data_ = new byte[size];
}

ImageBuffer::~ImageBuffer()
{
    if (data_ != 0) {
        delete [] data_;
    }
}

byte * const ImageBuffer::data() const
{
    return data_;
}

unsigned ImageBuffer::width() const
{
    return width_;
}

unsigned ImageBuffer::height() const
{
    return height_;
}

unsigned ImageBuffer::rowSize() const
{
    return rowSize_;
}

ImageBuffer::ImageType ImageBuffer::type() const
{
    return type_;
}

char ImageBuffer::bitsPerPixel() const
{
    return bitsPerPixel_;
}

ImageBuffer::ImageAlign ImageBuffer::alignment() const
{
    return alignment_;
}

bool ImageBuffer::isTopDown()
{
    return topDownOrder_;
}
