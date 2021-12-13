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
	_trangThai = 0;
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
	_trangThai = Flight._trangThai;
}
Flight::Flight(const string &maChuyenBay, const string &noiDen, const string &noiDi, const string &ISFC, double giaVe, int ngay, int thang, int nam, int gio, int phut, int trangThai)
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
	_trangThai = trangThai;
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
int Flight::GetTrangThai() const
{
	return _trangThai;
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
void Flight::SetGia(double giaVe)
{
	if (giaVe > 0)
		_giaVe = giaVe;
}
void Flight::SetNgay(int ngay)
{
	_ngay = ngay;
}
void Flight::SetThang(int thang)
{
	_thang = thang;
}
void Flight::SetNam(int nam)
{
	_nam = nam;
}
void Flight::SetTrangThai(int trangThai)
{
	_trangThai = trangThai;
}

bool Flight::CheckFC(const string &ISFC)
{
	if (IsEmpty(ISFC))
		return false;

	if (ISFC.length() != 9)
	{
		cerr << "\nMa ISFC gom 9 ki tu!";
		return false;
	}
	string check;
	check = check + ISFC[0] + ISFC[1] + ISFC[2];
	if (check != FLIGHT_CODE_9 && check != _FLIGHT_CODE_9)
	{
		cerr << "\nMa ISFC-9 bat dau bang VJA hoac VNA !";
		return false;
	}
	return true;
}

// bool Flight::IsVNFlight(const string &ISFC)
// {
// 	if (CheckFC(ISFC))
// 		if (ISFC.substr(3, 3) == ISFC_VN)
// 			return true;
// 	return false;
// }

string Flight::FormatISFC() const
{
	string res = _ISFC;
	res.insert(3, "-");
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
bool Flight::CheckDay(int ngay, int thang, int nam)
{
	tm *crt = currentTime();
	int yearHT = crt->tm_year + 1900; // tm_year cchi tra ve 120
	int monthHT = crt->tm_mon + 1;
	int dayHT = crt->tm_mday;
	if (nam >= yearHT)
		return true;
	else if (ngay >= dayHT && thang >= monthHT)
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
		cout << "\nNhap ma chuyen bay: ";
		getline(cin, _maChuyenBay);
		if (!IsEmpty(_maChuyenBay))
			break;
	}

	while (1)
	{
		cout << "\nNhap noi den:";
		getline(cin, _noiDen);
		if (!IsEmpty(_noiDen))
			break;
	}
	while (1)
	{
		cout << "\nNhap noi di: ";
		getline(cin, _noiDi);
		if (!IsEmpty(_noiDi))
			break;
	}

	while (1)
	{
		cout << "\nNhap ISFC-9: ";
		getline(cin, _ISFC);
		if (CheckFC(_ISFC))
			break;
	}
	while (1)
	{

		cout << "\nNgay mua (dd/mm/yyyy): ";
		while (1)
		{
			cout << "\nNhap ngay: ";
			cin >> _ngay;
			if (ValidateDay(_ngay))
				break;
			cout << "\nNgay nhap khong hop le !";
		}
		while (1)
		{
			cout << "\nNhap thang: ";
			cin >> _thang;
			if (ValidateMonth(_thang))
				break;
			cout << "\nThang nhap khong hop le !";
		}
		while (1)
		{
			cout << "\nNhap nam: ";
			cin >> _nam;

			if (ValidateYear(_nam))
				break;
			cout << "\nNam nhap khong hop le !";
		}
		if (CheckDay(_ngay, _thang, _nam))
		{
			_trangThai = 1;
			break;
		}
		cout << "\nVui long nhap ngay lon hon ngay hien tai!";
	}
	while (1)
	{
		cout << "\nNhap gio: ";
		cin >> _gio;
		if (_gio < 24)
			break;
		cout << "\nGio khong hop le!";
	}
	while (1)
	{
		cout << "\nNhap phut: ";
		cin >> _phut;
		if (_phut < 60)
			break;
		cout << "\nPhut khong hop le!";
	}
	while (1)
	{
		cout << "\nNhap gia ve: ";
		cin >> _giaVe;
		if (cin.fail())
		{
			cerr << "NaN - du lieu nhap phai la 1 so !";
			exit(0);
		}
		if (_giaVe > 0)
			break;
		cerr << "\nGia ve phai lon hon 0 !";
	}
}
void Flight::Output()
{
	// NAM
	TextColor(SHOW_COLOR);
	string tt = _trangThai == 1 ? "Sap khoi hanh" : "Da bay";
	cout << "  |   " << setw(9) << left << _maHieu
		 << "|        " << setw(11) << _maChuyenBay
		 << "|     "
		 << setw(12) << _noiDen
		 << "|     "
		 << setw(11) << _noiDi

		 << "|  "
		 << setw(12) << FormatISFC()
		 << "|     " << _giaVe << "$"
		 << "|      " << _ngay << "/" << _thang << "/" << _nam << ", " << _gio << ":" << _phut
		 << "|        " << tt;
}
void Flight::OutputMainInfo()
{
	if (_trangThai == 1)
	{
		cout << "|        " << left << setw(11) << _ISFC
			 << "|     "
			 << setw(12) << _noiDen
			 << "|     "
			 << setw(11) << _noiDi
			 << "|     " << _giaVe << "$"
			 << "|      " << _ngay << "/" << _thang << "/" << _nam << ", " << _gio << ":" << _phut;
		TextColor(7);
	}
	else
		cout << "";
}

void Flight::InputFile(ifstream &input)
{
	getline(input, _maHieu);
	getline(input, _maChuyenBay);
	getline(input, _noiDen);
	getline(input, _noiDi);
	getline(input, _ISFC);
	input >> _giaVe;
	input >> _ngay;
	input >> _thang;
	input >> _nam;
	input >> _gio;
	input >> _phut;
	input >> _trangThai;
	// input.clear();
}
void Flight::OutputFile(ofstream &out)
{
	out << _maHieu << endl;
	out << _maChuyenBay << endl;
	out << _noiDen << endl;
	out << _noiDi << endl;
	out << _ISFC << endl;
	out << _giaVe << endl;
	out << _ngay << endl;
	out << _thang << endl;
	out << _nam << endl;
	out << _gio << endl;
	out << _phut << endl;
	out << _trangThai << endl;
	out.clear();
}

Flight &Flight::operator=(const Flight &Flight)
{
	_maChuyenBay = Flight._maChuyenBay;
	_noiDen = Flight._noiDen;
	_noiDi = Flight._noiDi;
	_ISFC = Flight._ISFC;
	_giaVe = Flight._giaVe;
	_ngay = Flight._ngay;
	_thang = Flight._thang;
	_nam = Flight._nam;
	_gio = Flight._gio;
	_phut = Flight._phut;
	_trangThai = Flight._trangThai;
	return *this;
}

ostream &operator<<(ostream &os, const Flight &Flight)
{
	os << Flight._maChuyenBay << endl;
	os << Flight._noiDen << endl;
	os << Flight._noiDi << endl;
	os << Flight._ISFC << endl;
	os << Flight._giaVe << endl;
	os << Flight._ngay << endl;
	os << Flight._thang << endl;
	os << Flight._nam << endl;
	os << Flight._gio << endl;
	os << Flight._phut << endl;
	os << Flight._trangThai << endl;
	return os;
}
