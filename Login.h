#include <iomanip>
#include <iostream>
using namespace std;
class Login
{
public:
    Login();
    void dangNhap();
    void dangKi();
    void inputPass(string &);
    bool checkFile(string, const char *);
    void saveFile(string, const char *); // giam bo nho
    long long maHoa(int);                // Dung long long de co the luu dc nhin gia tri hon
    int giaiMa(long long);               // vi` giai ma nen chi can int la` du
private:
    string taiKhoanTmp;
    string matKhauTmp;
    bool quyenTruyCap;
};