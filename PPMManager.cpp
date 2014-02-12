#include "PPMManager.h"
#include "ImageBuffer.h"

#include <cstdio>
#include <cstring>

PPMManager::PPMManager() : ImageManager(), ppmType_(0)
{
}

PPMManager::PPMManager(const std::string &filename) : ImageManager(filename), ppmType_(0)
{
}

char PPMManager::ppmType() const
{
    return ppmType_;
}

void PPMManager::setType(PPMType type)
{
    ppmType_ = type;
}

void PPMManager::setMaxColor(unsigned short maxColor)
{
	maxColor_ = maxColor;
}

unsigned short PPMManager::maxColor() const
{
    return maxColor_;
}

ImageBuffer *PPMManager::getImage()
{
    ImageBuffer *buffer = 0;
    int size, width, height;
    int offset, index, dataIndex;
    byte red, green, blue;
    char* data = reinterpret_cast<char*>(rawData_);
    
    if (rawData_ != 0) {
		dataIndex = 0;
		sscanf(data, "%*c%c", &ppmType_);
		dataIndex += 2;
		switch (ppmType_) {
		case PPM_TEXT:
		    sscanf(&data[dataIndex], "%u %u %hu%n", &width, &height, &maxColor_, &offset);
		    buffer = new ImageBuffer(width, height, ImageBuffer::IMAGE_RGB);
		    size = width * height;
		    dataIndex += offset;
		    for (int i = 0; i < size; i++) {
		        sscanf(&data[dataIndex], "%hhu %hhu %hhu%n", &red, &green, &blue, &offset);
		        index = i * 3;
		        buffer->data()[index] = red;
		        buffer->data()[index + 1] = green;
		        buffer->data()[index + 2] = blue;
		    }
		    break;
		case PPM_BIN:
		    sscanf(&data[dataIndex], "%u %u %hu%n", &width, &height, &maxColor_, &offset);
		    buffer = new ImageBuffer(width, height, ImageBuffer::IMAGE_RGB);
		    size = width * height;
		    dataIndex += offset;
		    dataIndex += 1;
		    for (int i = 0; i < size; i++) {
		        index = i * 3;
		        memcpy(&red, &rawData_[dataIndex], sizeof(byte));
		        memcpy(&green, &rawData_[dataIndex], sizeof(byte));
		        memcpy(&blue, &rawData_[dataIndex], sizeof(byte));
		        dataIndex += 3;
		        buffer->data()[index] = red;
		        buffer->data()[index + 1] = green;
		        buffer->data()[index * 2] = blue;
		    }
		    break;
		default:
		    delete buffer;
		    buffer = 0;
		}
    }
    
    return buffer;
}

int PPMManager::writeBuffer(ImageBuffer &buffer)
{
    int size = buffer.width() * buffer.height();
    int index;
    int retValue = IMG_NO_ERROR;
    unsigned char * pixel = 0;
    
    if (buffer.type() == ImageBuffer::IMAGE_RGB) {
		if (!file_.is_open()) {
		    file_.open(filename_.c_str(), std::fstream::out);
		    switch (ppmType_) {
		    case PPM_TEXT:
		        file_ << "P3" << std::endl;
		        file_ << buffer.width() << " " << buffer.height() << std::endl;
		        file_ << maxColor_ << std::endl;
		        for (int i = 0; i < size; i++) {
		            index = i * 3;
		            file_ << (unsigned)buffer.data()[index] << " "
		                  << (unsigned)buffer.data()[index + 1] << " "
		                  << (unsigned)buffer.data()[index + 2] << std::endl;
		        }
		        break;
		    case PPM_BIN:
		        file_ << "P6" << std::endl;
		        file_ << buffer.width() << " " << buffer.height() << std::endl;
		        file_ << maxColor_ << std::endl;
		        for (int i = 0; i < size; i++) {
		            index = i * 3;
		            pixel = &buffer.data()[index];
		            file_.write(reinterpret_cast<char*>(&pixel[0]), sizeof(byte));
		            file_.write(reinterpret_cast<char*>(&pixel[1]), sizeof(byte));
		            file_.write(reinterpret_cast<char*>(&pixel[2]), sizeof(byte));
		        }
		        break;
		    }
		    file_.close();
		} else {
		    retValue = IMG_ALREADY_OPEN;
		}
    } else {
    	retValue = PPM_NOT_PPM;
    }

    return retValue;
}
