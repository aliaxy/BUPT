//
// Created by aruve on 2022/11/14.
//

#include "bitmap.h"

bitmap::bitmap() {
  this->fileHeader = new FILEHEAD;
  this->infoHeader = new INFOHEAD;
}

bitmap::~bitmap() {
  delete this->fileHeader;
  delete this->infoHeader;
  delete this->pixelInfo;
  this->pixelCnt.clear();
}

void bitmap::loadBmp(std::string src) {
  std::ifstream fin;
  fin.open(src, std::ios::binary);
  if (!fin.is_open()) {
    std::cerr << "cannot open the file\n";
    return;
  }

  fin.read((char *) this->fileHeader, sizeof(FILEHEAD));
  fin.read((char *) this->infoHeader, sizeof(INFOHEAD));

  this->colorInfo = new COLORINFO[this->infoHeader->biClrUsed];
  this->pixelInfo = new uint8_t[this->fileHeader->bfSize - this->fileHeader->bfOffBits];

  fin.read((char *) this->colorInfo, sizeof(COLORINFO) * this->infoHeader->biClrUsed);
  fin.read((char *) this->pixelInfo, sizeof(uint8_t) * (this->fileHeader->bfSize - this->fileHeader->bfOffBits));
}

void bitmap::savePixel() {
  int n = this->fileHeader->bfSize - this->fileHeader->bfOffBits;
  for (int i = 0; i < n; i++) {
    if (pixelCnt.find(this->pixelInfo[i]) == this->pixelCnt.end()) {
      this->pixelCnt[this->pixelInfo[i]] = 1;
    } else {
      this->pixelCnt[this->pixelInfo[i]]++;
    }
  }
}

std::unordered_map<uint8_t, int> bitmap::getPixelCnt() {
  return this->pixelCnt;
}
