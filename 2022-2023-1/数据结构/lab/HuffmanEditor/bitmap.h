//
// Created by aruve on 2022/11/14.
//

#ifndef HUFFMANEDITOR__BITMAP_H_
#define HUFFMANEDITOR__BITMAP_H_

#include "common.h"

/* 文件信息头结构 */
typedef struct BITMAPFILEHEADER {
  uint16_t bfType;                 // 必须是BM字符串 对应的十六进制为0x4d42
  uint32_t bfSize;                 // 文件大小 以字节为单位(2-5字节)
  uint16_t bfReserved1;            // 保留 必须设置为0 (6-7字节)
  uint16_t bfReserved2;            // 保留 必须设置为0 (8-9字节)
  uint32_t bfOffBits;              // 从文件头到像素数据的偏移 (10-13字节)
} __attribute__((packed)) FILEHEAD;// 取消内存对齐

/* 图像信息头结构 */
typedef struct BITMAPINFOHEADER {
  uint32_t biSize;         // 此结构体的大小 (14-17字节)
  uint32_t biWidth;        // 图像的宽  (18-21字节)
  uint32_t biHeight;       // 图像的高  (22-25字节)
  uint16_t biPlanes;       // 表示bmp图片的平面数 恒等于1 (26-27字节)
  uint16_t biBitCount;     // 一像素所占的位数 一般为24   (28-29字节)
  uint32_t biCompression;  // 图像数据压缩的类型 0为不压缩。 (30-33字节)
  uint32_t biSizeImage;    // 像素数据所占大小 等于上面文件头结构中bfSize-bfOffBits (34-37字节)
  uint32_t biXPelsPerMeter;// 水平分辨率 用像素/米表示 一般为0 (38-41字节)
  uint32_t biYPelsPerMeter;// 垂直分辨率 用像素/米表示 一般为0 (42-45字节)
  uint32_t biClrUsed;      // 实际使用的彩色表中的颜色索引 0说明使用所有调色板项 (46-49字节)
  uint32_t biClrImportant; // 说明对图象显示有重要影响的颜色索引数 0表示都重要 (50-53字节)
} __attribute__((packed)) INFOHEAD;// 取消内存对齐

/* 图像素信息结构 (调色板) */
typedef struct BITMAPCOLORINfO {
  uint8_t rgbBlue; // 该颜色的蓝色分量 (值范围为0-255)
  uint8_t rgbGreen;// 该颜色的绿色分量 (值范围为0-255)
  uint8_t rgbRed;  // 该颜色的红色分量 (值范围为0-255)
  uint8_t rgbAlpha;// 保留，必须为0
} COLORINFO;

/* 位图类 */
class bitmap {
 public:                                         // 公有成员 对外可见
  bitmap();                                      // 构造函数
  ~bitmap();                                     // 析构函数
  void loadBmp(std::string);                     // 加载位图
  void savePixel();                              // 保存每个像素点的出现频度
  std::unordered_map<uint8_t, int> getPixelCnt();// 获取每个像素点的出现频度
  
 private:                                   // 私有成员 对外不可见
  const int PIXELSZIE = 256;                // 调色板大小
  FILEHEAD *fileHeader;                     // 文件信息头
  INFOHEAD *infoHeader;                     // 图像信息头
  COLORINFO *colorInfo;                     // 调色板
  uint8_t *pixelInfo;                       // 所有像素点
  std::unordered_map<uint8_t, int> pixelCnt;// 每个像素点的出现频度
};

#endif//HUFFMANEDITOR__BITMAP_H_
