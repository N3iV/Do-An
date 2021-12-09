#include "BuyTicket.h"
#include <iomanip>
#include "Airport.h"
using namespace std;
BuyTicket::BuyTicket()
{
	_UserCode = "";
	_Name = "";
	_ID = "";
}

BuyTicket::BuyTicket(const string &UserCode, const string &Name, const string &ID)
{
	_UserCode = UserCode;
	_Name = Name;
	_ID = ID;
}
BuyTicket::~BuyTicket()
{
}
string BuyTicket::GetKey()
{
	return _UserCode;
}
string BuyTicket::GetName() const
{
	return _Name;
}
string BuyTicket::GetID() const
{
	return _ID;
}
string BuyTicket::GetUserCode() const
{
	return _UserCode;
}
string BuyTicket::GetMaCB() const
{
	return _MaChuyenBay;
}
void BuyTicket::SetDate(Date day)
{
	if (day.validityCheck_Fix())
		date = day;
}
void BuyTicket::SetName(const string &Name)
{
	if (!IsEmpty(Name))
		_Name = Name;
}
void BuyTicket::SetID(const string &ID)
{
	if (CheckID(ID))
		_ID = ID;
}
void BuyTicket::SetUserCode(const string &UserCode)
{
	if (CheckUserCode(UserCode))
		_UserCode = UserCode;
}
void BuyTicket::SetMaCB(const string &ma)
{
	if (!IsEmpty(ma))
		_MaChuyenBay = ma;
}

bool BuyTicket::CheckID(const string &ID)
{
	if (IsEmpty(ID))
		return false;

	if (ID.length() != 9)
	{
		cerr << "\nCMND Khach hang gom 9 ki tu!";
		return false;
	}
	for (int i = 0; i < ID.length(); ++i)
		if (ID[i] > '9' || ID[i] < '0')
		{
			cerr << "\nMa Khach hang phai la nhung chu so 0-9 !";
			return false;
		}
	return true;
}

bool BuyTicket::CheckUserCode(const string &UserCode)
{
	if (UserCode.length() != 6)
	{
		cerr << "\nUserCode phai co do dai la 6 !";
		return false;
	}
	for (int i = 0; i < UserCode.length(); ++i)
		if (UserCode[i] > '9' || UserCode[i] < '0')
		{
			cerr << "\nMa Khach hang phai la nhung chu so 0-9 !";
			return false;
		}
	return true;
}

void BuyTicket::Input()
{

	// while (1)
	// {
	// 	cout << "\nNgay mua (dd/mm/yyyy): ";
	// 	cin >> date;
	// 	// if ()
	// 	// 	break;
	// 	// cout << "\nNgay nhap khong hop le !";
	// 	if (date.validityCheck_Fix())
	// 		break;
	// 	cout << "\nVui long nhap ngay hop le va lon hon hoac bang ngay hien tai!!";
	// }
	Airport ap;
	int found = ap.Search(0, 0);
	if (found == NOT_FOUND)
	{
		cout << "\n========= KHONG TIM THAY TRONG DANH SACH  ==========" << endl;
		return;
	}
	_MaChuyenBay = ap.GetFlight(found)->GetKey();
	while (1)
	{
		cout << "\nNhap ten Khach hang: ";
		getline(cin, _Name);
		if (!IsEmpty(_Name))
			break;
	}
	while (1)
	{
		cout << "\nNhap CMND: ";
		getline(cin, _ID);
		if (!IsEmpty(_ID))
			break;
	}
	while (1)
	{
		cout << "\nMa khach hang: ";
		getline(cin, _UserCode);
		if (CheckUserCode(_UserCode))
			break;
	}
}
void BuyTicket::Output()
{

	cout << setiosflags(ios::left)
		 << "\tTen khach hang: "
		 << setw(20) << _Name
		 << "\tCMND: "
		 << setw(10) << _ID
		 << "\tMa khach hang: "
		 << setw(10) << _UserCode
		 << "\tMa Chuyen bay: " << setw(10) << _MaChuyenBay;
	//  << "\tNgay mua ve: "
	//  << setw(10) << date;
}

void BuyTicket::InputFile(ifstream &input)
{
	// input >> date;
	getline(input, _MaChuyenBay);
	getline(input, _Name);
	getline(input, _ID);
	getline(input, _UserCode);
}
void BuyTicket::OutputFile(ofstream &out)
{
	out << _MaChuyenBay << endl;
	out << _Name << endl;
	out << _ID << endl;
	out << _UserCode << endl;
	// out << date << endl;
}

BuyTicket &BuyTicket::operator=(const BuyTicket &BuyTicket)
{
	_Name = BuyTicket._Name;
	_ID = BuyTicket._ID;
	_UserCode = BuyTicket._UserCode;
	return *this;
}

ostream &operator<<(ostream &os, const BuyTicket &BuyTicket)
{
	os << BuyTicket._Name << endl;
	os << BuyTicket._ID << endl;
	os << BuyTicket._UserCode << endl;
	os << BuyTicket._MaChuyenBay << endl;
	// os << BuyTicket.date << endl;
	return os;
}
