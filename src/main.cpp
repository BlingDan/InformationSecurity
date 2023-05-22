#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <fstream>
#include <cstring>
#include <stdio.h>

using namespace std;



//逆初始置换IP1表
static int IP1_Table[64] = {40, 8, 48, 16, 56, 24, 64, 32,
                            39, 7, 47, 15, 55, 23, 63, 31,
                            38, 6, 46, 14, 54, 22, 62, 30,
                            37, 5, 45, 13, 53, 21, 61, 29,
                            36, 4, 44, 12, 52, 20, 60, 28,
                            35, 3, 43, 11, 51, 19, 59, 27,
                            34, 2, 42, 10, 50, 18, 58, 26,
                            33, 1, 41, 9, 49, 17, 57, 25};





//string  key = "5987423651456987";
//string cleartext = "5469875321456045";


/**
 * @brief 异或操作
 * @param a
 * @param b
 * @return
 */
string XOR_(string a, string b)
{
    string ans = "";
    for(int i = 0; i < a.size(); i ++)
    {
        if(a[i] == b[i])
            ans += "0";
        else
            ans += "1";
    }
    return ans;
}

/**
 *
 * @param R
 * @param mode  置换的表
 * @param round 置换轮次
 * @return
 */
string replacement(string R, int* mode, int round)
{
    string arr = "";

    for(int i = 0; i < round; i++)
    {
        arr += R[mode[i] - 1];
    }

    return arr;


}

//移位函数
string shift_tables(string k , int shift)
{
    string tmp = "";
    for(int i = 0; i < shift; i ++)
    {
        for(int j = 1; j < 28; j ++)
            tmp += k[j];
        tmp += k[0];
        k = tmp;
        tmp = "";
    }
    return k;
}

//字节数组转16进制字符串
string bytesToHexString(const char* bytes, const int length)
{
    if (bytes == NULL) {
        return "";
    }
    std::string buff;
    const int len = length;
    for (int j = 0; j < len; j++) {
        int high = bytes[j] / 16, low = bytes[j] % 16;
        buff += (high < 10) ? ('0' + high) : ('a' + high - 10);
        buff += (low < 10) ? ('0' + low) : ('a' + low - 10);
    }
    return buff;
}

//
//16进制字符串 转 字节数组
void hexStringToBytes(const string& hex, char* bytes) {
    int bytelen = hex.length() / 2;
    string strByte;
    int n;
    for (int i = 0; i < bytelen; i ++) {
        strByte = hex.substr(i * 2, 2);
        sscanf_s(strByte.c_str(), "%x", &n);
        bytes[i] = n;
    }
}

/**
 *
 * @param bitString
 * @return 16进制字符串 string
 */
string bit2hex(string bit)
{
    unordered_map<string, string> mp;
    mp["0000"] = "0";
    mp["0001"] = "1";
    mp["0010"] = "2";
    mp["0011"] = "3";
    mp["0100"] = "4";
    mp["0101"] = "5";
    mp["0110"] = "6";
    mp["0111"] = "7";
    mp["1000"] = "8";
    mp["1001"] = "9";
    mp["1010"] = "A";
    mp["1011"] = "B";
    mp["1100"] = "C";
    mp["1101"] = "D";
    mp["1110"] = "E";
    mp["1111"] = "F";

    string hex = "";
    for(int i = 0; i < bit.length(); i += 4)
    {
        string tmp = "";
        for(int j = 0; j < 4; j ++)
            tmp += bit[i+j];

        hex += mp[tmp];
    }
    return hex;
}

/**
 *
 * @param hex 16进制字符串
 * @return 2进制字符串
 */
string hex2bit(string hex)
{
    string str= "";

    for(int i = 0; i < hex.size(); i ++){
        char tmp = hex[i];
        switch(tmp){
            case('0') :str.append("0000"); break;
            case('1') :str.append("0001"); break;
            case('2') :str.append("0010"); break;
            case('3') :str.append("0011"); break;
            case('4') :str.append("0100"); break;
            case('5') :str.append("0101"); break;
            case('6') :str.append("0110"); break;
            case('7') :str.append("0111"); break;
            case('8') :str.append("1000"); break;
            case('9') :str.append("1001"); break;
            case('A') :str.append("1010"); break;
            case('B') :str.append("1011"); break;
            case('C') :str.append("1100"); break;
            case('D') :str.append("1101"); break;
            case('E') :str.append("1110"); break;
            case('F') :str.append("1111"); break;
        }
    }
    return str;
}

/**
 *
 * @param text
 * @param rkb
 * @param rk
 * @return 16进制字符串
 */
string function(string text, vector<string> rkb, vector<string> rk)
{
    text = hex2bit(text);
    //初始置换IP表
    int IP_Table[64] = {58 , 50 , 42 , 34 , 26 , 18 , 10 , 2 , 60 , 52 , 44 , 36 , 28 , 20 , 12 , 4 ,
                        62 , 54 , 46 , 38 , 30 , 22 , 14 , 6 , 64 , 56 , 48 , 40 , 32 , 24 , 16 , 8 ,
                        57 , 49 , 41 , 33 , 25 , 17 , 9 , 1 , 59 , 51 , 43 , 35 , 27 , 19 , 11 , 3 ,
                        61 , 53 , 45 , 37 , 29 , 21 , 13 , 5 , 63 , 55 , 47 , 39 , 31 , 23 , 15 , 7};
    replacement(text, IP_Table, 64);
    text = replacement(text, IP_Table, 64);

//    cout << "初始置换：\t" << bit2hex(text) << endl;

    string left = text.substr(0, 32);
    string right = text.substr(32, 32);
//    cout << "左L" << 0 << ":" << bit2hex(left) << ' ' ;
//    cout << "右R" << 0 << ":" << bit2hex(right) << endl;

    //32->48扩展置换表
    int expansion_table[] = {
            32, 1, 2, 3, 4, 5,
            4, 5, 6, 7, 8, 9,
            8, 9, 10, 11, 12, 13,
            12, 13, 14, 15, 16, 17,
            16, 17, 18, 19, 20, 21,
            20, 21, 22, 23, 24, 25,
            24, 25, 26, 27, 28, 29,
            28, 29, 30, 31, 32, 1
    };

    //S Box
    int s[8][4][16] = { { 14, 4, 13, 1, 2, 15, 11, 8, 3, 10, 6, 12, 5, 9, 0, 7,
                                0, 15, 7, 4, 14, 2, 13, 1, 10, 6, 12, 11, 9, 5, 3, 8,
                                4, 1, 14, 8, 13, 6, 2, 11, 15, 12, 9, 7, 3, 10, 5, 0,
                                15, 12, 8, 2, 4, 9, 1, 7, 5, 11, 3, 14, 10, 0, 6, 13 },
                        { 15, 1, 8, 14, 6, 11, 3, 4, 9, 7, 2, 13, 12, 0, 5, 10,
                                3, 13, 4, 7, 15, 2, 8, 14, 12, 0, 1, 10, 6, 9, 11, 5,
                                0, 14, 7, 11, 10, 4, 13, 1, 5, 8, 12, 6, 9, 3, 2, 15,
                                13, 8, 10, 1, 3, 15, 4, 2, 11, 6, 7, 12, 0, 5, 14, 9 },

                        { 10, 0, 9, 14, 6, 3, 15, 5, 1, 13, 12, 7, 11, 4, 2, 8,
                                13, 7, 0, 9, 3, 4, 6, 10, 2, 8, 5, 14, 12, 11, 15, 1,
                                13, 6, 4, 9, 8, 15, 3, 0, 11, 1, 2, 12, 5, 10, 14, 7,
                                1, 10, 13, 0, 6, 9, 8, 7, 4, 15, 14, 3, 11, 5, 2, 12 },
                        { 7, 13, 14, 3, 0, 6, 9, 10, 1, 2, 8, 5, 11, 12, 4, 15,
                                13, 8, 11, 5, 6, 15, 0, 3, 4, 7, 2, 12, 1, 10, 14, 9,
                                10, 6, 9, 0, 12, 11, 7, 13, 15, 1, 3, 14, 5, 2, 8, 4,
                                3, 15, 0, 6, 10, 1, 13, 8, 9, 4, 5, 11, 12, 7, 2, 14 },
                        { 2, 12, 4, 1, 7, 10, 11, 6, 8, 5, 3, 15, 13, 0, 14, 9,
                                14, 11, 2, 12, 4, 7, 13, 1, 5, 0, 15, 10, 3, 9, 8, 6,
                                4, 2, 1, 11, 10, 13, 7, 8, 15, 9, 12, 5, 6, 3, 0, 14,
                                11, 8, 12, 7, 1, 14, 2, 13, 6, 15, 0, 9, 10, 4, 5, 3 },
                        { 12, 1, 10, 15, 9, 2, 6, 8, 0, 13, 3, 4, 14, 7, 5, 11,
                                10, 15, 4, 2, 7, 12, 9, 5, 6, 1, 13, 14, 0, 11, 3, 8,
                                9, 14, 15, 5, 2, 8, 12, 3, 7, 0, 4, 10, 1, 13, 11, 6,
                                4, 3, 2, 12, 9, 5, 15, 10, 11, 14, 1, 7, 6, 0, 8, 13 },
                        { 4, 11, 2, 14, 15, 0, 8, 13, 3, 12, 9, 7, 5, 10, 6, 1,
                                13, 0, 11, 7, 4, 9, 1, 10, 14, 3, 5, 12, 2, 15, 8, 6,
                                1, 4, 11, 13, 12, 3, 7, 14, 10, 15, 6, 8, 0, 5, 9, 2,
                                6, 11, 13, 8, 1, 4, 10, 7, 9, 5, 0, 15, 14, 2, 3, 12 },
                        { 13, 2, 8, 4, 6, 15, 11, 1, 10, 9, 3, 14, 5, 0, 12, 7,
                                1, 15, 13, 8, 10, 3, 7, 4, 12, 5, 6, 11, 0, 14, 9, 2,
                                7, 11, 4, 1, 9, 12, 14, 2, 0, 6, 10, 13, 15, 3, 5, 8,
                                2, 1, 14, 7, 4, 10, 8, 13, 15, 12, 9, 0, 3, 5, 6, 11 } };

    int P[] = {
            16, 7, 20, 21,
            29, 12, 28, 17,
            1, 15, 23, 26,
            5, 18, 31, 10,
            2, 8, 24, 14,
            32, 27, 3, 9,
            19, 13, 30, 6,
            22, 11, 4, 25
    };
    //迭代
    for(int i = 0; i < 16; i ++)
    {
        string right_expanded = replacement(right, expansion_table, 48);

        string x = XOR_(right_expanded, rkb[i]);

        string op = "";

//        S盒压缩6bit->4bit
        for(int i = 0; i < 8; i ++)
        {
            int row = 2 * (x[i * 6] - '0') + int(x[i * 6 + 5] - '0');
            int col = 8 * int(x[i * 6 + 1] - '0') + 4 * int(x[i * 6 + 2] - '0') + 2 * int(x[i * 6 + 3] - '0') + int (x[i * 6 + 4] - '0');
            int val = s[i][row][col];

            op += char(val / 8 + '0');
            val = val % 8;
            op += char(val / 4 + '0');
            val = val % 4;
            op += char(val / 2 + '0');
            val = val % 2;
            op += char(val + '0');
        }

        op = replacement(op, P, 32);
        left = XOR_(op, left);

        if(i != 15)
            swap(left, right);
//        cout << "Round" << i + 1 << "\t" << bit2hex(left)<< ' ' << bit2hex(right) << "<-----rk:" << rk[i] << endl;
    }

    string combine = left + right;

    string ans = bit2hex(replacement(combine, IP1_Table, 64));
    return ans;
}


/**
 *
 * @param key
 * @param rkb
 * @param rk
 */

void RoundKey(string key, vector<string> *rkb, vector<string> *rk)
{
    key = hex2bit(key);

    //PC1选位表 64->56去掉校验位
    int PC1[] = {
            57, 49, 41, 33, 25, 17, 9,
            1, 58, 50, 42, 34, 26, 18,
            10, 2, 59, 51, 43, 35, 27,
            19, 11, 3, 60, 52, 44, 36,
            63, 55, 47, 39, 31, 23, 15,
            7, 62, 54, 46, 38, 30, 22,
            14, 6, 61, 53, 45, 37, 29,
            21, 13, 5, 28, 20, 12, 4
    };

    key = replacement(key, PC1, 56);

    //PC2选位表 每轮秘钥的置换
    int PC2[] = {
            14, 17, 11, 24, 1, 5,
            3, 28, 15, 6, 21, 10,
            23, 19, 12, 4, 26, 8,
            16, 7, 27, 20, 13, 2,
            41, 52, 31, 37, 47, 55,
            30, 40, 51, 45, 33, 48,
            44, 49, 39, 56, 34, 53,
            46, 42, 50, 36, 29, 32
    };

    //移位表
    int shift_table[16] = {
            1, 1, 2, 2,
            2, 2, 2, 2,
            1, 2, 2, 2,
            2, 2, 2, 1
    };

    string C = key.substr(0, 28);
    string D = key.substr(28, 28);
    //迭代
    for(int i = 0; i < 16; i ++)
    {
        C = shift_tables(C, shift_table[i]);
        D = shift_tables(D, shift_table[i]);

        string combine = C + D;
        //生成48位子秘钥
        combine = replacement(combine, PC2, 48);

        rkb->push_back(combine);
        rk->push_back(bit2hex(combine));
    }

}

/**
 *
 * @param text
 * @param key
 * @param mode 0->加密; 1->解密
 * @return ans 加密或解密后的字符串
 */
string des(string original_text, string key, int mode) {
    vector<string> rkb; //二进制子秘钥集
    vector<string> rk;  //十六进制子秘钥集
    string ans = "";
    //生成子密钥集
    RoundKey(key, &rkb, &rk);

    //加密
    if (mode = 0) {
        ans = function(original_text, rkb, rk);
    }

    if (mode = 1) {
        reverse(rk.begin(), rk.end());
        reverse(rkb.begin(), rkb.end());
        ans = function(original_text, rkb, rk);
    }

    return ans;
}
/**
 *
 * @param data
 * @param text 填充后的分组明文
 * @param textb
 */
void Padding(char input[], vector<string> *text, vector<string> *textb)
{
    string data = bytesToHexString(input, strlen(input));
    for(int i = 0; i < data.size() ; i = i + 8)
    {
        string str = "";

        //PCK5Padding  {1234} -> {12344444}
        if(i + 8 > data.size())
        {
            while(i < data.size())
                str += data[i ++];

            int count = 8 - str.length();
            for(int j = 0; j < count; j ++)
                str += count + '0';

            text->push_back(str);
            textb->push_back(hex2bit(str));
            break;
        }


        for(int j = 0; j < 8; j ++)
            str += data[i + j];
        text->push_back(str);
        textb->push_back(hex2bit(str));

    }
}

/**
 *
 * @param text_b
 * @param IV
 * @param key
 * @param mode  0->加密; 1->解密
 * @return
 */
vector<string> CBC(vector<string> text, string IV, string key, int mode)
{
    vector<string> ans;

    //加密
    if(mode == 0)
    {
        string C = IV;   //迭代密文
        for(int i = 0; i < text.size(); i ++)
        {

            C = des(XOR_(hex2bit(text[i]), hex2bit(C)), key, 0);
            C = bit2hex(C);
            ans.push_back(C);
        }
    }

    //解密
    if(mode == 1)
    {
        string C = IV;
        for(int i = 0; i < text.size(); i ++)
        {
            if(i != 0)
                C = text[i - 1];

            string P = des(text[i], key, 1);
            P = XOR_(hex2bit(P), hex2bit(C));
            ans.push_back(P);
        }
    }

    return ans;
};

/**
 *
 * @param str
 * @return 判断是否是填充的str并处理
 */
string judge(string str)
{
    int last = str.back() - '0';

    bool fg = true;
    for(int i = str.size() - 1; i > str.size() - last - 1; i --)
    {
        if(str[i] != last){
            fg = false;
            break;
        }
        else
            continue;
    }

    if(fg)
    {
        string ans = "";
        for(int i = 0; i < str.size() - last; i ++)
            ans += str[i];
        return ans;
    }

    return str;
}
/**
 *
 * @param data 文件读取字节数据
 * @param count 字节长度
 * @param IV 初始化向量 8B
 * @param key 8B * 3
 * @param mode  0->加密; 1->解密
 */
void DES3(char input_file[], char output_file[],  string key, int mode)
{
    char data[1024];
    fstream file_tmp;
    file_tmp.open(input_file, ios::out | ios::in);
    file_tmp >> data;

    string IV = "12345678";
    vector<string> ans;

    //padding填充返回分组明文
    vector<string> text;
    vector<string> text_b;

    Padding(data, &text, &text_b);

    //三组秘钥
    vector<string> keymap;
    for(int i = 0; i < key.size(); i = i + 8)
    {
        string tmp = "";
        for(int j = 0; j < 8; j ++)
            tmp += key[i + j];
        keymap.push_back(tmp);
    }

    //加密
    if(mode == 0)
    {
        ans = CBC(text, IV, keymap[0], 0);
        ans = CBC(ans, IV, keymap[1], 1);
        ans = CBC(ans, IV, keymap[2], 0);

    }

    //解密
    if(mode == 1)
    {
        ans = CBC(text, IV, keymap[2], 1);
        ans = CBC(ans, IV, keymap[1], 0);
        ans = CBC(ans, IV, keymap[0], 1);

        string last = ans.back();
        ans.pop_back();
        last = judge(last);
        ans.push_back(last);
    }

    char tmp[32];
    for(int i = 0; i < ans.size(); i ++)
    {
        memset(tmp, sizeof tmp, 0);
        tmp = ans[i];
        fwrite( *tmp, sizeof tmp, 16, file);
    }
    return;
}

//简单的交互界面
int getTip()
{
    system("cls");
    puts("+----------------------------------------------------------------+");
    puts("|         Welcome to  3DES file encrpt-decrypt system!           |");
    puts("+-----------------------------------------------------------------");
    puts("\n");
    puts("Please enter the given number:");
    puts("1.encrypt file.");
    puts("2.decrypt file.");
    puts("==================================================================");
    puts("(c)cls (#)exit");
    return 1;
}

//该函数实现从文件流fp中默认提取8个字符，返回为提取到的字符个数。
int get8Bits(FILE*fp,char*str)
{
    int count;
    memset(str,0,8);
    count=fread(str,1,8,fp);
    return count;
}

//自定义读取函数
void fgets_t(unsigned char*str,int count)
{
    fgets((char*)str,count,stdin);
    str[strlen((char*)str)-1]='\0';
}

int main(){
    char data[1024];
    FILE *fp_in,*fp_out;
    unsigned char fin_input;
    unsigned char temp[8+1]={0};
    unsigned char enc_key[16+1]={0};
    unsigned char dec_key[16+1]={0};
    unsigned char buff[16+1]={0};
    unsigned char in_buff[8+1]={0};
    unsigned char in_buff_hex[16+1]={0};
    unsigned char out_buff[8+1]={0};
    unsigned char out_buff_hex[16+1]={0};
    char file_in[32+1]={0};
    char file_out[32+1]={9};

    fstream file;
//    file.open("../test.txt", ios::out | ios::in);
//    file >> data;

    getTip();

    while(1) {
        printf("enter your choice: ");
        memset(temp, 0, 8);
        scanf("%8s", temp);
        do
            fin_input = getchar();
        while (fin_input != '\n' && fin_input != '\xff');
        if (strlen((char *) temp) != 1) {
            puts("you should enter one number!");
            continue;
        }
        if (strlen((char *) temp) == 1 && temp[0] != '#') {
            if (strlen((char *) temp) == 1 && temp[0] != 'c') {
                switch (temp[0]) {
                    case '1':
                        memset(file_in, 0, 32);
                        memset(file_out, 0, 32);
                        memset(enc_key, 0, 16);

                        printf("Input file to encrpt: ");
                        fgets_t((unsigned char *) file_in, 32);
                        if ((fp_in = fopen(file_in, "rb")) == NULL) {
                            perror("file_in");
                            break;
                        }
                        fclose(fp_in);

                        printf("Input filePath to save encrypted file: ");
                        fgets_t((unsigned char *) file_out, 32);
                        if ((fp_out = fopen(file_out, "wb")) == NULL) {
                            perror("file_out");
                            break;
                        }
                        fclose(fp_out);

                        printf("Input 16bytes key like 1234567887654321 : ");
                        memset(buff, 0, 16);
                        fgets_t(buff, 18);
                        if (strlen((char *) buff) != 16) {
                            puts("Key error! you should input 16bytes key!");
                            break;
                        }
                        strcpy((char *) enc_key, (char *) buff);

                        string key(enc_key);
                        DES3(file_in, file_out, enc_key, 0);
                        break;

                    case '2':
                        memset(file_in, 0, 32);
                        memset(file_out, 0, 32);
                        memset(dec_key, 0, 16);

                        printf("Input file to decrypt: ");
                        fgets_t((unsigned char *) file_in, 32);
                        if ((fp_in = fopen(file_in, "rb")) == NULL) {
                            perror("file_in");
                            break;
                        }
                        fclose(fp_in);

                        printf("Input filePath to save decrypted file: ");
                        fgets_t((unsigned char *) file_out, 32);
                        if ((fp_out = fopen(file_out, "wb")) == NULL) {
                            perror("file_out");
                            break;
                        }
                        fclose(fp_out);

                        printf("Input 16bytes key like 1234567887654321 : ");
                        memset(buff, 0, 16);
                        fgets_t(buff, 18);
                        if (strlen((char *) buff) != 16) {
                            puts("Key error! you should input 16bytes key!");
                            break;
                        }
                        strcpy((char *) dec_key, (char *) buff);

                        string key(16,dec_key);
                        DES3(file_in, file_out, key,1);
                        break;

                    default:
                        puts("Wrong args!");
                        break;
                }
            } else
                getTip();
        }

//    DES3(data, strlen(data), "12345678", "00000000", 1);

        return 0;
    }}