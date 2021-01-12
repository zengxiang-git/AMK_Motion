#include "amk_motion/CanMessage.h"

void CanMessage::ShowMenu()
{
    cout << "******************控制指令******************" << endl;
    cout << "打开（1）/使能（7）/去使能（9）/关闭（3）" << endl;
    cout << "前进（8）/后退（2）/左转（4）/右转（6）/零速（5）" << endl;
    cout << "******************************************" << endl;
    cout << "请输入控制指令：";
}

void CanMessage::OpenDevice()
{
    DWORD dwRel = 0;
    dwRel = VCI_OpenDevice(4, 0, 0);
    if (dwRel != STATUS_OK)
    {
        cout << "打开设备失败" << endl;
    }
    else
        cout << "打开设备成功" << endl;

    VCI_INIT_CONFIG vic;
    vic.AccCode = 0x80000008; //验收码
    vic.AccMask = 0xFFFFFFFF; //屏蔽码
    vic.Filter = 1;           //滤波方式
    vic.Reserved = 0;         //保留
    vic.Timing0 = 0x00;
    vic.Timing1 = 0x14; //设置波特率1000kbps
    vic.Mode = 0;       //模式,为0表示正常模式，1只听，2自发自收

    if (VCI_InitCAN(4, 0, 0, &vic) == STATUS_OK) //初始化指定的CAN通道
    {
        if (VCI_StartCAN(4, 0, 0) == STATUS_OK) //启动CAN卡的某一个CAN通道
        {
            cout << "开启CAN成功，类型：" << 4 << "  索引：" << 0 << "  通道：" << 0 << endl;
            openFlag = true;
        }
    }
    else
    {
        cout << "初始化设备失败" << endl;
        openFlag = false;
    }
}

void CanMessage::CloseDevice()
{

    DWORD dwRel;
    dwRel = VCI_CloseDevice(4, 0); //传入参数为设备类型，设备索引
    if (dwRel != STATUS_OK)
    {
        cout << "关闭设备失败" << endl;
    }
    else
    {
        cout << "关闭设备成功" << endl;
        openFlag = false;
    }
}

int CanMessage::D_TO_X(int x)
{
    int i, j, arr[4];
    if (x == 0)
    {
        cout << "0";
        DtoX_H = 0;
        DtoX_L = 0;
    }
    else
    {
        for (i = 0; x != 0; i++)
        {
            arr[i] = x % 16;
            if (arr[i] <= 9)
            {
                arr[i] += '0'; //把数字转换为字符
            }
            else
            {
                switch (arr[i])
                {
                case 10:
                    arr[i] = 'A';
                    break;
                case 11:
                    arr[i] = 'B';
                    break;
                case 12:
                    arr[i] = 'C';
                    break;
                case 13:
                    arr[i] = 'D';
                    break;
                case 14:
                    arr[i] = 'E';
                    break;
                case 15:
                    arr[i] = 'F';
                    break;
                default:
                    cout << "数据有误，请重新输入数据";
                    break;
                }
            }
            x /= 16;
        }
        // cout << "转换为十六进制后的数据为：";
        for (j = i - 1; j >= 0; j--)
        {
            //用cout.put();  如果里面是变量，则显示变量的ASCII值所代表的字符，
            //如果是整数，则显示ASCII值为该整数所代表的字符。里面先计算整数，再将整数转为字符输出。
            cout.put(arr[j]); //cout.put()输出字符 cout.write()输出字符串
        }
        // for (int k = 0; k < 4; k++)
        // {
        //     cout << "数组arr[" << k << "] = " << arr[k] << endl;
        // }
    }
    return DtoX_H, DtoX_L;
}

void CanMessage::EnableNodes(bool enableFlag)
{
    DWORD dwRel_CAN01, dwRel_CAN02, dwRel_CAN03, dwRel_CAN04;
    VCI_CAN_OBJ vco1[ZHENSHU];
    VCI_CAN_OBJ vco2[ZHENSHU];
    VCI_CAN_OBJ vco3[ZHENSHU];
    VCI_CAN_OBJ vco4[ZHENSHU];
    int enableMsg[6] = {0x00, WRITENOSAVE, 0x00, 0x10, 0x00, enableFlag};

    //CAN0通道节点1
    // cout << "CAN0节点1，发送报文数据" << endl;
    for (int i = 0; i < ZHENSHU; i++)
    {
        vco1[i].ID = 0x0101;
        vco1[i].RemoteFlag = 0;
        vco1[i].ExternFlag = 0;
        vco1[i].DataLen = 6;

        for (int j = 0; j < vco1[i].DataLen; j++)
        {
            vco1[i].Data[j] = enableMsg[j];
            D_TO_X(vco1[i].Data[j]);
            cout << " ";
        }
        cout << endl;
    }
    dwRel_CAN01 = VCI_Transmit(4, 0, 0, vco1, ZHENSHU);
    cout << "CAN0通道节点1：发送成功，帧数为：" << dwRel_CAN01 << endl;

    //CAN0通道节点2
    // cout << "CAN0节点2，发送报文数据" << endl;
    for (int i = 0; i < ZHENSHU; i++)
    {
        vco2[i].ID = 0x0102;
        vco2[i].RemoteFlag = 0;
        vco2[i].ExternFlag = 0;
        vco2[i].DataLen = 6;

        for (int j = 0; j < vco2[i].DataLen; j++)
        {
            vco2[i].Data[j] = enableMsg[j];
            D_TO_X(vco2[i].Data[j]);
            cout << " ";
        }
        cout << endl;
    }
    dwRel_CAN02 = VCI_Transmit(4, 0, 0, vco2, ZHENSHU);
    cout << "CAN0通道节点2：发送成功，帧数为：" << dwRel_CAN02 << endl;

    //CAN0通道节点3
    // cout << "CAN0节点3，发送报文数据" << endl;
    for (int i = 0; i < ZHENSHU; i++)
    {
        vco3[i].ID = 0x0103;
        vco3[i].RemoteFlag = 0;
        vco3[i].ExternFlag = 0;
        vco3[i].DataLen = 6;

        for (int j = 0; j < vco3[i].DataLen; j++)
        {
            vco3[i].Data[j] = enableMsg[j];
            D_TO_X(vco3[i].Data[j]);
            cout << " ";
        }
        cout << endl;
    }
    dwRel_CAN03 = VCI_Transmit(4, 0, 0, vco3, ZHENSHU);
    cout << "CAN0通道节点3：发送成功，帧数为：" << dwRel_CAN03 << endl;

    //CAN0通道节点4
    // cout << "CAN0节点4，发送报文数据" << endl;
    for (int i = 0; i < ZHENSHU; i++)
    {
        vco4[i].ID = 0x0104;
        vco4[i].RemoteFlag = 0;
        vco4[i].ExternFlag = 0;
        vco4[i].DataLen = 6;

        for (int j = 0; j < vco4[i].DataLen; j++)
        {
            vco4[i].Data[j] = enableMsg[j];
            D_TO_X(vco4[i].Data[j]);
            cout << " ";
        }
        cout << endl;
    }
    dwRel_CAN04 = VCI_Transmit(4, 0, 0, vco4, ZHENSHU);
    cout << "CAN0通道节点4：发送成功，帧数为：" << dwRel_CAN04 << endl;
}

void CanMessage::SetAimSpd(float LinearSpd, float AngularSpd)
{
    //运动学参数
    // float B = 0.586; //轮距
    // float L = 0.498; //轴距
    // float D = 0.33;  //车轮直径
    // int n = 30;      //减速比

    SetVehicleParameters(_B, _L, _D, _n);

    int *p1;
    int *p2;
    int *p3;
    int *p4;

    float F = (_B * _B + _L * _L) / _B;

    WheelSpdRpm_FL = 30 * _n * (2 * LinearSpd - AngularSpd * F) / PI / _D;
    WheelSpdRpm_FR = 30 * _n * (2 * LinearSpd + AngularSpd * F) / PI / _D;
    WheelSpdRpm_RL = 30 * _n * (2 * LinearSpd - AngularSpd * F) / PI / _D;
    WheelSpdRpm_RR = 30 * _n * (2 * LinearSpd + AngularSpd * F) / PI / _D;

    cout << "计算得到四轮轮速（rpm）为：FL=" << WheelSpdRpm_FL << ",FR=" << WheelSpdRpm_FR << ",RL=" << WheelSpdRpm_RL << ",RR=" << WheelSpdRpm_RR << endl;

    // DecToHex_FL(WheelSpdRpm_FL);
    p1 = NumToNumHL(WheelSpdRpm_FL);
    SpdFL_H = p1[0];
    SpdFL_L = p1[1];
    // cout << "FL：" << "SpdFL_H = " << SpdFL_H << "，SpdFL_L = " << SpdFL_L << endl;
    p2 = NumToNumHL(WheelSpdRpm_FR);
    SpdFR_H = p2[0];
    SpdFR_L = p2[1];
    // cout << "FR：" << "SpdFR_H = " << SpdFR_H << "，SpdFR_L = " << SpdFR_L << endl;
    p3 = NumToNumHL(WheelSpdRpm_RL);
    SpdRL_H = p3[0];
    SpdRL_L = p3[1];
    // cout << "RL：" << "SpdRL_H = " << SpdRL_H << "，SpdRL_L = " << SpdRL_L << endl;
    p4 = NumToNumHL(WheelSpdRpm_RR);
    SpdRR_H = p4[0];
    SpdRR_L = p4[1];
    // cout << "RR：" << "SpdRR_H = " << SpdRR_H << "，SpdRR_L = " << SpdRR_L << endl;

    MoveAction(SpdFL_H, SpdFL_L, SpdFR_H, SpdFR_L, SpdRL_H, SpdRL_L, SpdRR_H, SpdRR_L);
}

// 运动控制报文
void CanMessage::MoveAction(int dataFL_H, int dataFL_L, int dataFR_H, int dataFR_L, int dataRL_H, int dataRL_L, int dataRR_H, int dataRR_L)
{

    DWORD dwRel_CAN01, dwRel_CAN02, dwRel_CAN03, dwRel_CAN04;
    VCI_CAN_OBJ vco1[ZHENSHU];
    VCI_CAN_OBJ vco2[ZHENSHU];
    VCI_CAN_OBJ vco3[ZHENSHU];
    VCI_CAN_OBJ vco4[ZHENSHU];
    int moveMsg_FL[6] = {0x00, SETSPD, 0x00, 0x00, dataFL_H, dataFL_L};
    int moveMsg_FR[6] = {0x00, SETSPD, 0x00, 0x00, dataFR_H, dataFR_L};
    int moveMsg_RL[6] = {0x00, SETSPD, 0x00, 0x00, dataRL_H, dataRL_L};
    int moveMsg_RR[6] = {0x00, SETSPD, 0x00, 0x00, dataRR_H, dataRR_L};

    //CAN0通道节点1
    // cout << "CAN0节点1，发送报文数据" << endl;
    for (int i = 0; i < ZHENSHU; i++)
    {
        vco1[i].ID = 0x0101;
        vco1[i].RemoteFlag = 0;
        vco1[i].ExternFlag = 0;
        vco1[i].DataLen = 6;

        for (int j = 0; j < vco1[i].DataLen; j++)
        {
            vco1[i].Data[j] = moveMsg_FL[j];
            D_TO_X(vco1[i].Data[j]);
            cout << " ";
        }
        cout << endl;
    }
    dwRel_CAN01 = VCI_Transmit(4, 0, 0, vco1, ZHENSHU);
    cout << "CAN0通道节点1：发送成功，帧数为：" << dwRel_CAN01 << endl;

    //CAN0通道节点2
    // cout << "CAN0节点2，发送报文数据" << endl;
    for (int i = 0; i < ZHENSHU; i++)
    {
        vco2[i].ID = 0x0102;
        vco2[i].RemoteFlag = 0;
        vco2[i].ExternFlag = 0;
        vco2[i].DataLen = 6;

        for (int j = 0; j < vco2[i].DataLen; j++)
        {
            vco2[i].Data[j] = moveMsg_FR[j];
            D_TO_X(vco2[i].Data[j]);
            cout << " ";
        }
        cout << endl;
    }
    dwRel_CAN02 = VCI_Transmit(4, 0, 0, vco2, ZHENSHU);
    cout << "CAN0通道节点2：发送成功，帧数为：" << dwRel_CAN02 << endl;

    //CAN0通道节点3
    // cout << "CAN0节点3，发送报文数据" << endl;
    for (int i = 0; i < ZHENSHU; i++)
    {
        vco3[i].ID = 0x0103;
        vco3[i].RemoteFlag = 0;
        vco3[i].ExternFlag = 0;
        vco3[i].DataLen = 6;

        for (int j = 0; j < vco3[i].DataLen; j++)
        {
            vco3[i].Data[j] = moveMsg_RL[j];
            D_TO_X(vco3[i].Data[j]);
            cout << " ";
        }
        cout << endl;
    }
    dwRel_CAN03 = VCI_Transmit(4, 0, 0, vco3, ZHENSHU);
    cout << "CAN0通道节点3：发送成功，帧数为：" << dwRel_CAN03 << endl;

    //CAN0通道节点4
    // cout << "CAN0节点4，发送报文数据" << endl;
    for (int i = 0; i < ZHENSHU; i++)
    {
        vco4[i].ID = 0x0104;
        vco4[i].RemoteFlag = 0;
        vco4[i].ExternFlag = 0;
        vco4[i].DataLen = 6;

        for (int j = 0; j < vco4[i].DataLen; j++)
        {
            vco4[i].Data[j] = moveMsg_RR[j];
            D_TO_X(vco4[i].Data[j]);
            cout << " ";
        }
        cout << endl;
    }
    dwRel_CAN04 = VCI_Transmit(4, 0, 0, vco4, ZHENSHU);
    cout << "CAN0通道节点4：发送成功，帧数为：" << dwRel_CAN04 << endl;
}

// 将十进制转换成十六进制字符串
string CanMessage::DecIntToHexStr(int num)
{
    string str;
    int Temp = num / 16;
    int left = num % 16;
    if (Temp > 0)
        str += DecIntToHexStr(Temp); // 使用迭代
    if (left < 10)
        str += (left + '0');
    else
        str += ('A' + left - 10);

    return str;
}

// 求负数的补码
int *CanMessage::Complement(int number) //求负数补码
{
    int arr[16] = {0}; //范围为 -128 ~ +127
    string str, strH, strL;
    int factor = 1;
    int numH = 0;
    int numL = 0;
    int *temp = new int[2]; //内部动态数组
    int number_0 = number;  //记录当前负数
    number = abs(number);   //取绝对值
    int i = 15;
    while (number != 0) //求出其绝对值原码
    {
        arr[i] = number % 2;
        // cout << "arr[" << i << "] = " << arr[i] << "  ";
        i--;
        number /= 2;
    }
    // cout << endl;
    for (i = 15; i >= 0; i--)
    {
        if (arr[i] == 1)
        {
            // cout << "最右边为1的位为第" << i + 1 << "位" << endl;
            int j;
            for (j = 0; j < i; j++) //从右往左数，第一个1左边的数取反
                if (arr[j] == 1)
                {
                    arr[j] = 0;
                }
                else
                    arr[j] = 1;
            break;
        }
    }
    // cout << number_0 << "的补码为：";
    // for (i = 0; i <= 15; i++)
    //     cout << arr[i];
    // cout << endl;

    // memset 函数是内存赋值函数，用来给某一块内存空间进行赋值的，需要包含头文件#include "string.h"
    // memset(arr, 0, sizeof(arr)); //重置数组各项为0

    // cout << "前半段逆序:" ;
    for (int k = 7; k >= 0; k--)
    {
        int tmp = 0;
        // cout << arr[k] << "  ";
        numH = numH + arr[k] * factor;
        factor *= 2;
    }
    factor = 1;
    // cout << endl;

    // cout << "后半段逆序:" ;
    for (int k = 15; k >= 8; k--)
    {
        int tmp = 0;
        // cout << arr[k] << "  ";
        numL = numL + arr[k] * factor;
        factor *= 2;
    }
    factor = 1;
    // cout << endl;
    strH = DecIntToHexStr(numH);
    strL = DecIntToHexStr(numL);
    // cout << "高八位：" << strH << "，低八位：" << strL << endl;
    // cout << "高八位数值：" << numH << "，低八位数值：" << numL << endl;

    temp[0] = numH;
    temp[1] = numL;
    return temp;
}

// 将十六进制字符串转换为十进制数值
int CanMessage::HTOI(string s)
{
    int res = 0;
    for (int i = 0; i < s.size(); i++)
    {
        // cout << s[i] << "  ";
        int tmp = 0;
        switch (s[i])
        {
        case '0':
            tmp = s[i] - '0';
            break;
        case '1':
            tmp = s[i] - '0';
            break;
        case '2':
            tmp = s[i] - '0';
            break;
        case '3':
            tmp = s[i] - '0';
            break;
        case '4':
            tmp = s[i] - '0';
            break;
        case '5':
            tmp = s[i] - '0';
            break;
        case '6':
            tmp = s[i] - '0';
            break;
        case '7':
            tmp = s[i] - '0';
            break;
        case '8':
            tmp = s[i] - '0';
            break;
        case '9':
            tmp = s[i] - '0';
            break;
        case 'A':
            tmp = s[i] - 'A' + 10;
            break;
        case 'B':
            tmp = s[i] - 'A' + 10;
            break;
        case 'C':
            tmp = s[i] - 'A' + 10;
            break;
        case 'D':
            tmp = s[i] - 'A' + 10;
            break;
        case 'E':
            tmp = s[i] - 'A' + 10;
            break;
        case 'F':
            tmp = s[i] - 'A' + 10;
            break;
        default:
            break;
        }
        res = res * 16 + tmp;
    }
    return res;
}

// 将十六进制字符串转换为两位十六进制字符串，返回高八位和低八位的数值
int *CanMessage::HextoHex4HL(string str)
{
    int length = str.length();
    // cout << "传入字符串位数为：" << length << endl;
    string strH4, strH, strL;
    int numH = 0;
    int numL = 0;
    int *temp = new int[2]; //内部动态数组
    if (length <= 4)
    {
        for (int i = 0; i < 4 - length; i++)
        {
            strH4.append("0");
        }
        strH4.append(str);
    }
    // cout << "四位形式的字符串为：" << strH4 << endl;
    strH.append(strH4, 0, 2); //追加strH4字符串第0个元素起2个元素
    strL.append(strH4, 2, 2); //追加strH4字符串第2个元素起2个元素
    // cout << "高八位：" << strH << ",低八位：" << strL << endl;
    numH = HTOI(strH);
    numL = HTOI(strL);

    temp[0] = numH;
    temp[1] = numL;
    return temp;
}

// 按正负分开讨论
int *CanMessage::NumToNumHL(int num)
{
    int *p;
    if (num >= 0)
    {
        p = HextoHex4HL(DecIntToHexStr(num));
    }
    else
    {
        p = Complement(num);
    }

    // cout << "输出高八位数据：" << p[0] << "，低八位数据：" << p[1] << endl;

    return p;
}
