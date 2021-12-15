#include "Flight.h"
#include <iomanip>
#include "Airport.h"
#include <ctime>
tm *currentTime()
{
	time_t currentTime = time(0);	   // lay date/time hien tai he thong, he thong k có time tra ve -1
	tm *crt = localtime(&currentTime); // trả về con trỏ tới cấu trúc tm biểu diễn local time
	return crt;
}
Flight::Flight()
{
	_maChuyenBay = "";
	_noiDen = "";
	_noiDi = "";
	_ISFC = "";
	_giaVe = 0;
	_ngay = 1;
	_thang = 1;
	_nam = 1900;
	_gio = 0;
	_phut = 0;
}
Flight::Flight(const Flight &Flight)
{
	_maChuyenBay = Flight._maChuyenBay;
	_noiDen = Flight._noiDen;
	_noiDi = Flight._noiDi;
	_ISFC = Flight._ISFC;
	_giaVe = Flight._giaVe;
	_ngay = Flight._ngay;
	_thang = Flight._thang;
	_gio = Flight._gio;
	_phut = Flight._phut;
	_nam = Flight._nam;
}
Flight::Flight(const string &maChuyenBay, const string &noiDen, const string &noiDi, const string &ISFC, const double &giaVe, const int &ngay, const int &thang, const int &nam, const int &gio, const int &phut)
{
	_maChuyenBay = maChuyenBay;
	_noiDen = noiDen;
	_noiDi = noiDi;
	_ISFC = ISFC;
	_giaVe = _giaVe;
	_ngay = ngay;
	_thang = thang;
	_nam = nam;
	_gio = gio;
	_thang = thang;
}
Flight::~Flight()
{
}
string Flight::GetKey()
{
	return _ISFC;
}

string Flight::GetNoiDen() const
{
	return _noiDen;
}

string Flight::GetISFC() const
{
	return _ISFC;
}
string Flight::GetNoiDi() const
{
	return _noiDi;
}
string Flight::GetMaChuyenBay() const
{
	return _maChuyenBay;
}
string Flight::GetMaHieu() const
{
	return _maHieu;
}
double Flight::GetGia() const
{
	return _giaVe;
}
int Flight::GetNgay() const
{
	return _ngay;
}
int Flight::GetThang() const
{
	return _thang;
}
int Flight::GetNam() const
{
	return _nam;
}

int Flight::GetGio() const
{
	return _gio;
}
int Flight::GetPhut() const
{
	return _phut;
}

// *----------------

void Flight::SetKey(const string &ma)
{
	_maHieu = ma;
}
void Flight::SetMaChuyenBay(const string &maChuyenBay)
{
	if (!IsEmpty(maChuyenBay))
		_maChuyenBay = maChuyenBay;
}
void Flight::SetMaHieu(const string &maHieu)
{
	if (!IsEmpty(maHieu))
		_maHieu = maHieu;
}
void Flight::SetNoiDen(const string &noiDen)
{
	if (!IsEmpty(noiDen))
		_noiDen = noiDen;
}
void Flight::SetNoiDi(const string &noiDi)
{
	if (!IsEmpty(noiDi))
		_noiDi = noiDi;
}

void Flight::SetISFC(const string &ISFC)
{
	if (CheckFC(ISFC))
		_ISFC = ISFC;
}
void Flight::SetGia(const double &giaVe)
{
	if (giaVe > 0)
		_giaVe = giaVe;
}
void Flight::SetNgay(const int &ngay)
{
	if (ValidateDay(_ngay))
		_ngay = ngay;
}
void Flight::SetThang(const int &thang)
{
	if (ValidateMonth(_thang))
		_thang = thang;
}
void Flight::SetNam(const int &nam)
{
	if (ValidateYear(_nam))
		_nam = nam;
}

void Flight::SetGio(const int &gio)
{
	if (_gio < 24)
		_gio = gio;
}
void Flight::SetPhut(const int &phut)
{
	if (_phut < 60)
		_phut = phut;
}

bool Flight::CheckFC(const string &ISFC)
{
	if (IsEmpty(ISFC))
	{
		gotoxy(0, 11);
		cout << "                                          ";
		return false;
	}

	if (ISFC.length() != 9)
	{
		TextColor(12);
		cerr << "\nMa ISFC gom 9 ki tu!" << setw(20);
		gotoxy(0, 11);
		cout << "                                          ";
		return false;
	}
	string check;
	check = check + ISFC[0] + ISFC[1];
	if (check != FLIGHT_CODE_TN && check != FLIGHT_CODE_QT)
	{
		TextColor(12);
		cerr << "\nMa ISFC-9 bat dau bang TN hoac QT !";
		gotoxy(0, 11);
		cout << "                                          ";
		return false;
	}
	return true;
}

string Flight::FormatISFC() const
{
	string res = _ISFC;
	res.insert(2, "-");
	return res;
}

//*------HELPER---------*//

bool Flight::isLeapYear()
{
	if (_nam % 4 == 0)
	{
		if (_nam % 100 == 0)
		{
			if (_nam % 400 != 0)
				return false;
			else
				return true;
		}
		return true;
	}
	return false;
}
bool Flight::ValidateYear(int nam)
{
	bool check = true;

	if (nam < 1900)
	{
		nam = 1900;
		check = false;
	}

	return check;
}
bool Flight::ValidateMonth(int thang)
{
	bool check = true;

	if (thang < 1 || thang > 12)
	{
		thang = 1;
		check = false;
	}
	return check;
}
bool Flight::ValidateDay(int ngay)
{
	bool check = true;

	if (ngay < 1 || ngay > 31)
	{
		ngay = 1;
		check = false;
	}
	else
	{
		switch (_thang)
		{
		case 2:
		{
			if (this->isLeapYear())
			{
				if (ngay > 29)
				{
					ngay = 29;
					check = false;
				}
			}
			else
			{
				if (ngay > 28)
				{
					ngay = 28;
					check = false;
				}
			}
			break;
		}
		case 4:
		case 6:
		case 9:
		case 11:
		{
			if (ngay > 30)
			{
				ngay = 30;
				check = false;
			}
			break;
		}
		default:
			break;
		}
	}
	return check;
}
bool Flight::CheckDay(int ngay, int thang, int nam, int gio)
{
	tm *crt = currentTime();
	int currentYear = crt->tm_year + 1900; // tm_year cchi tra ve 120
	int currentMonth = crt->tm_mon + 1;
	int currentDay = crt->tm_mday;
	int currentHour = crt->tm_hour;
	int currentMinute = crt->tm_min;
	if (nam > currentYear || nam == currentYear && thang > currentMonth || thang == currentMonth && ngay > currentDay || ngay == currentDay && gio > currentHour)
	{
		return true;
	}

	return false;
}
// Validate date

void Flight::Input()
{

	while (1)
	{
		gotoxy(0, 5);
		cout << "Nhap ma chuyen bay: ";
		getline(cin, _maChuyenBay);
		if (!IsEmpty(_maChuyenBay))
			break;
	}

	while (1)
	{
		gotoxy(0, 7);
		cout << "Nhap noi den:";
		getline(cin, _noiDen);
		if (!IsEmpty(_noiDen))
			break;
	}
	while (1)
	{
		gotoxy(0, 9);
		cout << "Nhap noi di: ";
		getline(cin, _noiDi);
		if (!IsEmpty(_noiDi))
			break;
	}

	while (1)
	{
		TextColor(13);
		gotoxy(0, 11);
		cout << "Nhap ISFC-9: ";
		getline(cin, _ISFC);
		if (CheckFC(_ISFC))
			break;
	}
	while (1)
	{
		gotoxy(0, 13);
		cout << "Ngay bay: (dd/mm/yyyy, hh:mimi)      ";
		while (1)
		{
			TextColor(13);
			gotoxy(0, 14);
			cout << "Nhap ngay: ";
			cin >> _ngay;
			if (ValidateDay(_ngay))
				break;
			TextColor(12);
			cout << "\nNgay nhap khong hop le !";
		}
		while (1)
		{
			TextColor(13);
			gotoxy(13, 14);
			cout << "/";
			cin >> _thang;
			if (ValidateMonth(_thang))
				break;
			TextColor(12);
			cout << "\nThang nhap khong hop le !";
		}
		while (1)
		{
			TextColor(13);
			gotoxy(16, 14);
			cout << "/";
			cin >> _nam;

			if (ValidateYear(_nam))
				break;
			TextColor(12);
			cout << "\nNam nhap khong hop le !";
		}
		while (1)
		{
			TextColor(13);
			gotoxy(21, 14);
			cout << ", ";
			cin >> _gio;
			if (_gio < 24)
				break;
			TextColor(12);
			cout << "\nGio khong hop le!         ";
		}
		while (1)
		{
			TextColor(13);
			gotoxy(25, 14);
			cout << ":";
			cin >> _phut;
			if (_phut < 60)
				break;
			TextColor(12);
			cout << "\nphut khong hop le!        ";
		}

		if (CheckDay(_ngay, _thang, _nam, _gio))
		{
			break;
		}

		cout << "\nVui long nhap ngay lon hon ngay hien tai!";
	}

	while (1)
	{
		gotoxy(0, 16);
		cout << "                                                 ";
		gotoxy(0, 16);
		cout << "Nhap gia ve: ";
		cin >> _giaVe;
		if (cin.fail())
		{
			TextColor(12);
			cerr << "\nNaN - du lieu nhap phai la 1 so !";
			exit(0);
		}
		if (_giaVe > 0)
			break;
		TextColor(12);
		cerr << "\nGia ve phai lon hon 0 !";
	}
}
void Flight::Output()
{
	// NAM
	TextColor(SHOW_COLOR);
	string tt = CheckDay(_ngay, _thang, _nam, _gio) ? "Sap khoi hanh" : "Da bay";
	string time = to_string(_ngay) + "/" + to_string(_thang) + "/" + to_string(_nam) + ", " + to_string(_gio) + ":" + to_string(_phut);
	cout << "|   " << setw(9) << left << _maHieu
		 << "|        " << setw(11) << _maChuyenBay
		 << "|     "
		 << setw(12) << _noiDen
		 << "|     "
		 << setw(11) << _noiDi

		 << "|  "
		 << setw(12) << FormatISFC()
		 << "|       " << setw(11) << _giaVe
		 << "|  " << setw(19) << time
		 << "|     " << setw(8) << tt;
}
void Flight::OutputMainInfo()
{
	if (CheckDay(_ngay, _thang, _nam, _gio))
	{
		cout << left << setw(12) << setfill(' ') << _ISFC
			 << "|    "
			 << setw(11) << _noiDen
			 << "|    "
			 << setw(11) << _noiDi
			 << "|     "
			 << setw(9) << _giaVe
			 << "|  "
			 << _ngay << "/" << _thang << "/" << _nam << ", " << _gio << ":" << _phut;
		TextColor(7);
	}
	else
		cout.clear();
}

void Flight::InputFile(ifstream &input)
{
	getline(input, _maHieu);
	getline(input, _maChuyenBay);
	getline(input, _noiDen);
	getline(input, _noiDi);
	getline(input, _ISFC);
	input >> _ngay;
	input >> _thang;
	input >> _nam;
	input >> _gio;
	input >> _phut;
	input >> _giaVe;
	// input.clear();
}
void Flight::OutputFile(ofstream &out)
{
	out << _maHieu << endl;
	out << _maChuyenBay << endl;
	out << _noiDen << endl;
	out << _noiDi << endl;
	out << _ISFC << endl;
	out << _ngay << "\t";
	out << _thang << "\t";
	out << _nam << "\t";
	out << _gio << "\t";
	out << _phut << endl;
	out << _giaVe << endl;
	out.clear();
}

Flight &Flight::operator=(const Flight &Flight)
{
	_maChuyenBay = Flight._maChuyenBay;
	_noiDen = Flight._noiDen;
	_noiDi = Flight._noiDi;
	_ISFC = Flight._ISFC;
	_ngay = Flight._ngay;
	_thang = Flight._thang;
	_nam = Flight._nam;
	_gio = Flight._gio;
	_phut = Flight._phut;
	_giaVe = Flight._giaVe;
	return *this;
}

ostream &operator<<(ostream &os, const Flight &Flight)
{
	os << Flight._maChuyenBay << endl;
	os << Flight._noiDen << endl;
	os << Flight._noiDi << endl;
	os << Flight._ISFC << endl;
	os << Flight._ngay << "\t";
	os << Flight._thang << "\t";
	os << Flight._nam << "\t";
	os << Flight._gio << "\t";
	os << Flight._phut << endl;
	os << Flight._giaVe << endl;
	return os;
}