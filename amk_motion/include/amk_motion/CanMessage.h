/**
 * @file CanMessage.h
 * @author ZX (1476600177@qq.com)
 * @brief 安防机器人（AMK）底盘控制接口
 * @version 0.1
 * @date 2021-01-08
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#pragma once
#include <iostream>
#include "controlcan.h"
using namespace std;

#define STATUS_OK 1
#define ZHENSHU 2
#define WRITESAVE 0x1E
#define WRITENOSAVE 0x24
#define SETSPD 0x28
#define WRITE2SAVE 0x21
#define PI 3.14

class CanMessage
{
public:
    // 显示菜单
    void ShowMenu();
    // 打开设备
    void OpenDevice();
    // 关闭设备
    void CloseDevice();
    // enableFlag = true，使能，enableFlag = false，去使能，
    void EnableNodes(bool enableFlag);
    // 设置目标线速度和角速度
    void SetAimSpd(float LinearSpd, float AngularSpd);
    // 设置底盘底盘运动学参数
    void SetVehicleParameters(float B, float L, float D, int n)
    {
        B = 0.586; //轮距
        L = 0.498; //轴距
        D = 0.33;  //车轮直径
        n = 30;    //减速比

        this->_B = B;
        this->_L = L;
        this->_D = D;
        this->_n = n;
    }

private:
    // 将十进制转换为十六进制字符串输出显示
    int D_TO_X(int x);
    // 传入十进制负数，返回负数补码的高八位和低八位的数值
    int *Complement(int number);
    // 将十进制正数转换成十六进制字符串，传给HextoHex4HL()函数
    string DecIntToHexStr(int num);
    // 将十六进制字符串转换为两位十六进制字符串，返回正数原码的高八位和低八位的数值
    int *HextoHex4HL(string str);
    // 将十六进制字符串转换为十进制数值，供HextoHex4HL()函数调用
    int HTOI(string s);
    // 传入的数分正负讨论，返回原码或补码
    int *NumToNumHL(int num);
    // 发送控制报文
    void MoveAction(int dataFL_H, int dataFL_L, int dataFR_H, int dataFR_L, int dataRL_H, int dataRL_L, int dataRR_H, int dataRR_L);

    // 运动学参数
    float _B; //轮距
    float _L; //轴距
    float _D; //车轮直径
    int _n;   //减速比

    // 运动学模型计算出的四轮轮速
    int WheelSpdRpm_FL, WheelSpdRpm_FR, WheelSpdRpm_RL, WheelSpdRpm_RR;
    // 给驱动器寄存器赋值的轮速信息
    int SpdFL_H, SpdFL_L, SpdFR_H, SpdFR_L, SpdRL_H, SpdRL_L, SpdRR_H, SpdRR_L;
    // 帧数据报文显示数据
    int DtoX_H, DtoX_L;
    // 打开设备标志位
    bool openFlag = false;
    // 使能标志位
    bool enableFlag = false;
};
