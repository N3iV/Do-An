#include <iostream>
#include <fstream>
#include <string>
#include <math.h>
#include "Login.h"
#include "AirportSystem.h"
#include "Display.h"
#include "srilakshmikanthanp/Figlet.hpp"

using namespace srilakshmikanthanp;
using namespace std;
#include <regex>
bool isValid(const string &email)
{

    const regex pattern(
        "(\\w+)(\\.|_)?(\\w*)@(\\w+)(\\.(\\w+))+");

    return regex_match(email, pattern);
}

//?-------------------VALIDATE EMAIL --------------------?//
Login::Login()
{
}
void Login::inputPass(string &tmp)
{
    tmp = "";
    char c;
    do
    {
        c = _getch();

        if ((c == 13 || c == ' ') && !tmp.empty())
        {
            break;
        }
        if ((c == 8 || c == 127) && !tmp.empty())
        {
            cout << "\b \b";
            tmp.erase(tmp.size() - 1);
        }
        else
        {
            tmp.push_back(c);
            _putch('*');
        }

    } while (c != 13 || c != ' ');
}
void Login::dangNhap()
{
    system("cls");
    Figlet figlet(FigletFont::make("Fonts/Standard.flf"), Smushed::make());
    cout << figlet("Dang nhap");

    while (1)
    {

        cout << "Nhap tai khoan va mat khau.";
        while (1)
        {
            cout << "\nEmail:";
            getline(cin, taiKhoanTmp);
            if (!IsEmpty(taiKhoanTmp))
                break;
        }
        int userID = checkFile(taiKhoanTmp, USER_DATA_PATH);
        if (userID != 0)
        {
            cout << "Mat khau (Enter de xac nhan):";
            string matKhauTmp;
            inputPass(matKhauTmp);

            int passwordID = checkFile(matKhauTmp, PASSWORD_DATA_PATH);
            if (userID == passwordID)
            {

                Display display;
                display.DisplayMain();
                cin.get();

                break;
            }
            else
            {
                cout << "\nSai mat khau!\n"
                     << endl;
                system("pause");
                dangNhap();
            }
        }
        else
        {
            cout << "\nTen dang nhap khong dung! \n"
                 << endl;
            system("pause");
            dangNhap();
        }
    }
}
bool Login::checkFile(string attempt, const char *p_fileName)
{
    string line;
    fstream file;
    long long maHoaKiTu;
    file.open(p_fileName, ios::in);
    while (1)
    {

        file >> maHoaKiTu;
        if (maHoaKiTu == 0)
        {
            if (attempt == line)
            {
                file.close();
                return true;
            }
            else
            {
                line.erase(line.begin(), line.end());
            }
        }
        else
        {

            line += (char)giaiMa(maHoaKiTu);
        }

        if (file.peek() == EOF)
        {
            file.close();
            return false;
        }
    }
}
void Login::saveFile(string p_line, const char *p_fileName) // giam bo nho
{
    fstream file;
    file.open(p_fileName, ios::app);
    for (int i = 0; i < p_line.length(); i++)
    {
        file << maHoa(p_line[i]);
        file << "\n";
    }
    file << "0\n"; // de ngan cach cac mat khau/tk
    file.close();
}
void Login::dangKi()
{
    string tk, mk;
    Figlet figlet(FigletFont::make("Fonts/Standard.flf"), Smushed::make());
    system("cls");
    cout << figlet("Dang ky");

    while (1)
    {

        cout << "Vui long nhap email:\t";
        cin >> tk;
        bool checkValidEmail = isValid(tk);
        if (!checkValidEmail)
        {
            cout << "\nEmail khong dung dinh dang!\n";
            cout << "\nVi du: xxx@gmail.com\n\n";
            system("pause");
            return;
        }

        cout << "Vui long nhap mat khau:\t";
        cin >> mk;
        if (!IsEmpty(mk))
            break;
    }
    saveFile(tk, USER_DATA_PATH);
    saveFile(mk, PASSWORD_DATA_PATH);
    dangNhap();
}
long long Login::maHoa(int p_letter) // Dung long long de co the luu dc nhin gia tri hon
{
    return powf(p_letter, 4);
}
int Login::giaiMa(long long p_letter) // vi` giai ma nen chi can int la` du
{
    return powf(p_letter, 1 / 4.f); // .f de trinh bien dich biet chung ta can tra ve du lieu dang float
}