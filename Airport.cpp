#include <iostream>
#include "Airport.h"
#include "BuyTicket.h"
using namespace std;
Airport::Airport()
{
}

// Airport::Airport(const Airport &aport)
// {
// 	_pl = aport._pl;
// }
Airport::Airport(const Airport &pl, const Airport &fl, const Airport &bt)
{
	_pl = pl._pl;
	_fl = fl._fl;
	_bt = bt._bt;
}

Airport::~Airport()
{
}

AirportSystem *Airport::GetPlane(int pos) const
{
	if (pos < 0 || pos >= _pl.size())
		throw "Vi tri truy cap khong hop le";
	return _pl[pos];
}
AirportSystem *Airport::GetFlight(int pos) const
{
	if (pos < 0 || pos >= _fl.size())
		throw "Vi tri truy cap khong hop le";
	return _fl[pos];
}
AirportSystem *Airport::GetTicket(int pos) const
{
	if (pos < 0 || pos >= _bt.size())
		throw "Vi tri truy cap khong hop le";
	return _bt[pos];
}
void Airport::getDSMB()
{
	for (int i = 0; i < _pl.size(); ++i)
	{
		// cout << _pl[i];
		cout << "Chuyen bay " << ((Flight *)_pl[i])->GetMaChuyenBay() << endl;
		cout << "May bay " << ((Plane *)_fl[i])->GetMaHieu() << endl;
	}
}
bool Airport::IsExist(int option, AirportSystem *as) const
{
	switch (option)
	{
	case 0:
	{
		for (int i = 0; i < _fl.size(); ++i)
			if (((Flight *)as)->GetISFC() == ((Flight *)_fl[i])->GetISFC())
				return true;
	}
	case 1:
	{
		for (int i = 0; i < _pl.size(); ++i)
			if (((Plane *)as)->GetCodeMB() == ((Plane *)_pl[i])->GetCodeMB())
				return true;
	}
	default:
	{
		break;
	}
	}
	return false;
}

void Airport::LoadDataFromFile(int option)
{
	ifstream input;
	switch (option)
	{
	case 0:
	{
		input.open(FLIGHT_DATA_PATH);
		if (input.fail())
			throw "loi doc file";
		while (1)
		{
			AirportSystem *fl = NULL;
			fl = new Flight;
			if (!fl)
				throw "Loi cap phat";
			fl->InputFile(input);
			if (input.eof())
				break;
			_fl.push_back(fl);
			input.ignore();
		}
		break;
	}
	case 1:
	{
		input.open(PLANES_DATA_PATH);
		if (input.fail())
			throw "loi doc file";
		while (1)
		{
			AirportSystem *as = NULL;
			as = new Plane;
			if (!as)
				throw "Loi cap phat";
			as->InputFile(input);
			if (input.eof())
				break;
			_pl.push_back(as);
			input.ignore();
		}
		break;
	}
	default:
	{
		input.open(TICKET_DATA_PATH);
		if (input.fail())
			throw "loi doc file";
		while (1)
		{
			AirportSystem *bt = NULL;
			bt = new BuyTicket;
			if (!bt)
				throw "Loi cap phat";
			bt->InputFile(input);
			if (input.eof())
				break;
			_bt.push_back(bt);
			input.ignore();
		}
		break;
	}
	}
	input.close();
}

void Airport::OutputDataToFile(int option)
{
	ofstream out;
	switch (option)
	{
	case 0:
	{
		out.open(FLIGHT_DATA_PATH, ios::out);
		if (out.fail())
			throw "Loi doc file";
		for (int i = 0; i < _fl.size(); ++i) // fix
			_fl[i]->OutputFile(out);
		break;
	}
	case 1:
	{
		out.open(PLANES_DATA_PATH, ios::out);
		if (out.fail())
			throw "Loi doc file";
		for (int i = 0; i < _pl.size(); ++i)
			_pl[i]->OutputFile(out);
		break;
	}
	default:
	{
		out.open(TICKET_DATA_PATH, ios::out);
		if (out.fail())
			throw "Loi doc file";
		for (int i = 0; i < _bt.size(); ++i)
			_bt[i]->OutputFile(out);
		break;
	}
	}
	// if (out.fail())
	// 	throw "Loi doc file";
	// for (int i = 0; i < _pl.size(); ++i)
	// 	_pl[i]->OutputFile(out);
	out.close();
}

void Airport::Show(int option)
{
	LoadDataFromFile(option);
	vector<AirportSystem *> tmp;

	if (option == 0)
		tmp = _fl;
	else if (option == 1)
		tmp = _pl;
	else
		tmp = _bt;
	for (int i = 0; i < tmp.size(); ++i)
	{
		TextColor(SHOW_COLOR);
		cout << "\n " << i + 1; // NAM
		TextColor(7);
		tmp[i]->Output();
	}
}
void Airport::ShowMainInfo(int option)
{
	LoadDataFromFile(option);
	vector<AirportSystem *> tmp;

	if (option == 0)
		tmp = _fl;
	else if (option == 1)
		tmp = _pl;
	else
		tmp = _bt;
	for (int i = 0; i < tmp.size(); ++i)
	{
		TextColor(SHOW_COLOR);
		cout << "\n";
		TextColor(7);

		tmp[i]->OutputMainInfo();
	}
}

void Airport::Add(int option)
{
	LoadDataFromFile(option);
	ofstream output;
	switch (option)
	{
	case 0:
	{

		output.open(FLIGHT_DATA_PATH, ios::app);
		if (output.fail())
			throw "Loi doc file";
		AirportSystem *flight = new Flight;
		if (flight == NULL)
			throw "Khong the cap phat bo nho";

		flight->Input();
		if (!IsExist(option, flight))
		{

			flight->OutputFile(output);
			output.close();
		}
		else
			cout << "\n bay da ton tai trong database !";

		break;
	}
	case 1:
	{
		output.open(PLANES_DATA_PATH, ios::app);
		if (output.fail())
			throw "Loi doc file";
		Plane *planes = new Plane;
		if (planes == NULL)
			throw "Khong the cap phat bo nho";

		fflush(stdin);
		planes->Input();
		if (!IsExist(option, planes))
			planes->OutputFile(output);
		else
			cout << "\nMay bay da da ton tai  !";
		break;
	}
	case 2:
	{

		output.open(TICKET_DATA_PATH, ios::app);
		if (output.fail())
			throw "Loi doc file";
		BuyTicket *bt = new BuyTicket;
		if (bt == NULL)
			throw "Khong the cap phat bo nho";
		fflush(stdin);

		bt->Input();
		for (int i = 0; i < _bt.size(); ++i)
			if (((BuyTicket *)bt)->GetUserCode() == ((BuyTicket *)_bt[i])->GetUserCode())
			{
				if (((BuyTicket *)bt)->GetUserCode() == ((BuyTicket *)_bt[i])->GetUserCode())
					bt->OutputFile(output);
				else
					cerr << "\n=== ERROR: Trung ID nhung khac thong tin ===" << endl;
				output.close();
				return;
			}
		if (!IsExist(option, bt))
			bt->OutputFile(output);
		else
			cout << "\nVe ton tai  !";
		break;
	}
	}
}

void Airport::Delete(int option)
{
	int found;
	char confirm[4];
	switch (option)
	{
	case 0:
	{
		found = Search(option, 0);
		if (found == NOT_FOUND)
		{
			cout << "\n========= KHONG TIM THAY TRONG DANH SACH  ==========" << endl;
			return;
		}
		while (1)
		{
			cout << "Nhan \"yes\" de xac nhan xoa may bay nay: ";
			cin >> confirm;

			if (strcmp(confirm, "yes") == 0)
			{

				_fl.erase(_fl.begin() + found);
				cout << "\n========= XOA THANH CONG ==========" << endl;
				break;
			}
			else
				return;
		}
	}
	break;
	case 1:
	{
		found = Search(option, 1);
		if (found == NOT_FOUND)
		{
			cout << "\n========= KHONG TIM THAY TRONG DANH SACH  ==========" << endl;
			return;
		}
		while (1)
		{
			cout << "Nhan \"yes\" de xac nhan xoa may bay nay: ";
			cin >> confirm;

			if (strcmp(confirm, "yes") == 0)
			{

				_pl.erase(_pl.begin() + found);
				cout << "\n========= XOA THANH CONG ==========" << endl;
				break;
			}
			else
				return;
		}
	}
	break;
	default:
	{
		found = Search(option, 0);
		if (found == NOT_FOUND)
		{
			cout << "\n========= KHONG TIM THAY TRONG DANH SACH  ==========" << endl;
			return;
		}
		while (1)
		{
			cout << "Nhan \"yes\" de xac nhan xoa may bay nay: ";
			cin >> confirm;

			if (strcmp(confirm, "yes") == 0)
			{

				_bt.erase(_bt.begin() + found);
				cout << "\n========= XOA THANH CONG ==========" << endl;
				break;
			}
			else
				return;
		}
		break;
	}
	}
	OutputDataToFile(option);
}

int Airport::Search(int option, int type)
{

	LoadDataFromFile(option);

	switch (option)
	{
	case 0:
	{
		switch (type)
		{
		case 0:
		{
			// search by title
			cout << "\nNhap ma chuyen bay: ";
			string maChuyenBay;
			fflush(stdin);
			getline(cin, maChuyenBay);
			for (int i = 0; i < _fl.size(); i++)
				if (ToLower(((Flight *)_fl[i])->GetMaChuyenBay()) == ToLower(maChuyenBay))
					return i;
			return NOT_FOUND;
		}

		case 1:
		{
			// search by ISFC
			string ISFC;
			fflush(stdin);
			while (1)
			{
				cout << "\nNhap ma ISFC-9: ";
				getline(cin, ISFC);
				if (Flight::CheckFC(ISFC))
					break;
			}
			for (int i = 0; i < _fl.size(); ++i)
				if (ToLower(((Flight *)_fl[i])->GetISFC()) == ToLower(ISFC))
					return i;
			return NOT_FOUND;
		}
		}
	}
	case 1:
	{
		switch (type)
		{
		case 0:
		{
			// search by name

			cout << "\nNhap loai may bay: ";
			string name;
			fflush(stdin);
			getline(cin, name);
			for (int i = 0; i < _pl.size(); ++i)
				if (ToLower(((Plane *)_pl[i])->GetLoaiMB()) == ToLower(name))
					return i;
			return NOT_FOUND;
		}
		case 1:
		{
			// search by ID
			cout << "\nNhap ma hieu: ";
			string maHieu;
			fflush(stdin);
			getline(cin, maHieu);
			for (int i = 0; i < _pl.size(); ++i)
				if (ToLower(((Plane *)_pl[i])->GetMaHieu()) == ToLower(maHieu))
					return i;
			return NOT_FOUND;
		}
		default:
			cout << "Vui long nhap lai";
			break;
		}
	}
	default:
	{

		cout << "\nNhap ten nguoi mua ve: ";
		string name_ID;
		getline(cin, name_ID);
		for (int i = 0; i < _bt.size(); ++i)
		{
			string r_name = ((BuyTicket *)_bt[i])->GetName();
			string r_ID = ((BuyTicket *)_bt[i])->GetID();
			if (ToLower(r_name) == ToLower(name_ID))
				return i;
		}
		return NOT_FOUND;
	}
	}
}
void Airport::Edit(int option)
{
	int found = Search(option, 0);
	if (found == NOT_FOUND)
	{
		cout << "\n========= KHONG TIM THAY TRONG DANH SACH  ==========" << endl;
		return;
	}
	int type;
	switch (option)
	{
	case 0:
	{
		TextColor(SHOW_COLOR);
		cout << setw(61) << right << "========== TIM THAY ==========" << endl;
		cout << "  |   Ma hieu  |   Ma chuyen bay   |     Noi den     |     Noi di     |     IFSC     |     Gia ve" << endl;
		cout << "=======================================================================================================" << endl;
		_fl[found]->Output();
		TextColor(3);
		cout << "\n0-Sua Tat Ca, 1-Ma chuyen bay, 2-Noi Den, 3-Noi Di, 4-ISFC, >> ";
		cin >> type;
		if (cin.fail())
			throw "Du lieu nhap khong la so";
		fflush(stdin);
		TextColor(11);
		switch (type)
		{
		case 0:
		{
			cout << "\n\t===== Nhap thong tin can chinh sua =====" << endl;
			_fl[found]->Input();
			break;
		}
		case 1:
		{
			cout << "\n\t===== Nhap thong tin can chinh sua =====" << endl;
			cout << "Nhap ma chuyen bay: ";
			string MaChuyenBay;
			getline(cin, MaChuyenBay);
			((Flight *)_fl[found])->SetMaChuyenBay(MaChuyenBay);
			break;
		}
		case 2:
		{
			cout << "\n\t===== Nhap thong tin can chinh sua =====" << endl;
			cout << "Nhap noi den: ";
			string NoiDen;
			getline(cin, NoiDen);
			((Flight *)_fl[found])->SetNoiDen(NoiDen);
			break;
		}
		case 3:
		{
			cout << "\n\t===== Nhap thong tin can chinh sua =====" << endl;
			cout << "Nhap noi di: ";
			string NoiDi;
			getline(cin, NoiDi);
			((Flight *)_fl[found])->SetNoiDi(NoiDi);
			break;
		}

		case 4:
		{
			cout << "\n\t===== Nhap thong tin can chinh sua =====" << endl;
			string ISFC;
			while (1)
			{
				cout << "Nhap ISFC: ";
				getline(cin, ISFC);
				if (Flight::CheckFC(ISFC))
					break;
			}
			((Flight *)_fl[found])->SetISFC(ISFC);
			break;
		}
		default:
		{
			cout << "Vui long lua chon dung!!";
			break;
		}
		}
		break;
	}
	case 1:
	{
		TextColor(SHOW_COLOR);
		cout << setw(60) << right << "========== TIM THAY ==========" << endl;
		cout << "  |     Ma hieu     |     Loai     |     Code     |     So day     |     So ghe     |     So ve" << endl;
		cout << "===============================================================================================" << endl;
		_pl[found]->Output();
		TextColor(3);
		cout << "\n0-Sua Tat Ca, 1-Ma Hieu, 2-Loai, 3-Code MB, 4-So Day, 5-So Ghe >> ";
		cin >> type;
		if (cin.fail())
			throw "Du lieu nhap khong la so";
		fflush(stdin);
		TextColor(11);
		switch (type)
		{
		case 0:
		{
			cout << "\n\t===== Nhap thong tin can chinh sua =====" << endl;
			_pl[found]->Input();
			break;
		}
		case 1:
		{
			cout << "\n\t===== Nhap thong tin can chinh sua =====" << endl;
			cout << "Nhap ma hieu may bay: ";
			string name;
			getline(cin, name);
			((Plane *)_pl[found])->SetMaHieu(name);
			break;
		}
		case 2:
		{
			cout << "\n\t===== Nhap thong tin can chinh sua =====" << endl;
			cout << "Nhap loai may bay: ";
			string loai;
			getline(cin, loai);
			((Plane *)_pl[found])->SetLoaiMB(loai);
			break;
		}

		case 3:
		{
			cout << "\n\t===== Nhap thong tin can chinh sua =====" << endl;
			string Code;
			while (1)
			{
				cout << "Nhap loai may: ";
				getline(cin, Code);
				if (Plane::CheckCode(Code))
					break;
			}
			((Plane *)_pl[found])->SetCodeMB(Code);
			break;
		}
		case 4:
		{
			cout << "\n\t===== Nhap thong tin can chinh sua =====" << endl;
			int age = 0;
			while (1)
			{
				cout << "Nhap so day: ";
				cin >> age;
				if (age > 0)
					break;
			}
			((Plane *)_pl[found])->SetSoDay(age);
			break;
		}
		default:
		{
			cout << "\n\t===== Nhap thong tin can chinh sua =====" << endl;
			int age = 0;
			while (1)
			{
				cout << "Nhap so ghe: ";
				cin >> age;
				if (age > 0)
					break;
			}
			((Plane *)_pl[found])->SetSoGhe(age);
			break;
		}
		}
		break;
	}
	default:
		break;
	}
	OutputDataToFile(option);
}

// void Airport::BuyTickets()
// {
// 	this->Add(2);
// }
