#include <iostream>

#include "../PPMManager.h"
#include "../ImageBuffer.h"

int main()
{
	PPMManager myImage("my_ppm.ppm");
	ImageBuffer buffer(10, 10, ImageBuffer::IMAGE_RGB);
	int size = buffer.width() * buffer.height();
	int index;
	
	// Puts all pixels on white.
	std::cout << size << std::endl;
	for (int i = 0; i < size * 3; i++) {
		buffer.data()[i] = 0xFF;
	}
	
	// Sets type to text.
	myImage.setType(PPMManager::PPM_TEXT);
	myImage.setMaxColor(255);
	// Writes image
	myImage.writeBuffer(buffer);
	
	return 0;
}
