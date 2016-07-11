//############################################################################

//「Akita National College of Technology Yamamoto's Laboratory」にて

//http://akita-nct.jp/yamamoto/comp/OpenGL/OpenGL.html
//############################################################################

#ifndef GL_SCREENSHOT_H_INCLUDED
#define GL_SCREENSHOT_H_INCLUDED

#include <stdlib.h> 
#include <iostream>
#include <fstream>
#include <vector>



struct BITMAPFILEHEADER_ {
	//char bfType1;
	//char bfType2;
	unsigned long  bfSize;
	unsigned short bfReserved1;
	unsigned short bfReserved2;
	unsigned long  bfOffBits;
};

struct BITMAPINFOHEADER_ {
	unsigned long  biSize;
	long           biWidth;
	long           biHeight;
	unsigned short biPlanes;
	unsigned short biBitCount;
	unsigned long  biCompression;
	unsigned long  biSizeImage;
	long           biXPixPerMeter;
	long           biYPixPerMeter;
	unsigned long  biClrUsed;
	unsigned long  biClrImporant;
};

class gl_screenshot {

public:
	gl_screenshot(){};
	~gl_screenshot(){};


	bool screenshot(const char* filename, int bpp=32)	{
		const int width    = glutGet(GLUT_WINDOW_WIDTH);   // 画像の大きさ
		const int height   = glutGet(GLUT_WINDOW_HEIGHT);
		const int datasize = height*((((width*bpp/8) + 3) >> 2) << 2);
		const int filesize = 2 + sizeof(BITMAPFILEHEADER_) + sizeof(BITMAPINFOHEADER_) + datasize;

		BITMAPFILEHEADER_ bmfh = {filesize, 0, 0, 54,};
		BITMAPINFOHEADER_ bmih = {40, width, height, 1, bpp, 0, 0, 0, 0, 0, 0,};

		int format;
		if (bpp == 24) {
			format = GL_RGB;
		}
		else if (bpp == 32) {
			format = GL_RGBA;
		}
		else {
			std::cerr << "invalid parameter 'bpp'" << std::endl;
			return false;
		}

		// データをもらう
		std::vector<GLubyte> buf(datasize);
		//glPixelStorei(GL_PACK_ALIGNMENT, 1);
		//glReadBuffer(GL_FRONT);
		glReadPixels(0, 0, width, height, format, GL_UNSIGNED_BYTE, &buf[0]);

		// RGB → BGR
		for (int i=0; i<datasize; i+=bpp/8) {
			std::swap(buf[i], buf[i+2]);
		}

		// 出力
		std::ofstream fs(filename, std::ios::out | std::ios::trunc | std::ios::binary);
		if (!fs) {
			std::cerr << "fstream::open() failed." << std::endl;
			return false;
		}

		fs.write("BM", 2);
		fs.write(reinterpret_cast<const char*>(&bmfh), sizeof(BITMAPFILEHEADER_));
		fs.write(reinterpret_cast<const char*>(&bmih), sizeof(BITMAPINFOHEADER_));
		fs.write(reinterpret_cast<const char*>(&buf[0]), datasize);
		fs.close();

		return true;
	}

};


#endif

