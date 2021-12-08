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
		cout << "\nSTT " << i + 1 << ": ";
		TextColor(7);
		tmp[i]->Output();
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
		try
		{

			output.open(FLIGHT_DATA_PATH, ios::app);
			if (output.fail())
				throw "Loi doc file";
			AirportSystem *flight = new Flight;
			if (flight == NULL)
				throw "Khong the cap phat bo nho";
			int found = Search(1, 1);
			if (found == NOT_FOUND)
			{
				cout << "\n========= KHONG TIM THAY TRONG DANH SACH  ==========" << endl;
				return;
			}
			flight->Input();
			if (!IsExist(option, flight))
			{

				flight->OutputFile(output);
				output.close();
			}
			else
				cout << "\n bay da ton tai trong database !";
		}
		catch (...)
		{
			cerr << "Loi doc file";
		}

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
		int found = Search(0, 0);
		if (found == NOT_FOUND)
		{
			cout << "\n========= KHONG TIM THAY TRONG DANH SACH  ==========" << endl;
			return;
		}
		fflush(stdin);
		bt->Input();
		for (int i = 0; i < _pl.size(); ++i)
			if (((BuyTicket *)bt)->GetUserCode() == ((BuyTicket *)_pl[i])->GetUserCode())
			{
				if (((BuyTicket *)bt)->GetUserCode() == ((BuyTicket *)_pl[i])->GetUserCode())
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
		// default:
		// {
		// 	TextColor(3);
		// 	cout << "\n0-Sua Tat Ca, 1-Nguoi Muon, 2-Ngay Muon >> ";
		// 	cin >> type;
		// 	if (cin.fail())
		// 		throw "Du lieu nhap khong la so";
		// 	cin.ignore();
		// 	TextColor(11);
		// 	switch (type)
		// 	{
		// 	case 0:
		// 	{
		// 		cout << "\n\t===== Nhap thong tin can chinh sua =====" << endl;
		// 		_pl[found]->Input();
		// 		break;
		// 	}
		// 	case 1:
		// 	{
		// 		cout << "\n\t===== Nhap thong tin can chinh sua =====" << endl;
		// 		Plane r;
		// 		r.Input();
		// 		((BuyTicket *)_pl[found])->SetPlane(r);
		// 		break;
		// 	}
		// 	default:
		// 	{
		// 		cout << "\n\t===== Nhap thong tin can chinh sua =====" << endl;
		// 		Date date;
		// 		while (1)
		// 		{
		// 			cout << "Nhap ngay muon: ";
		// 			cin >> date;
		// 			if (date.validityCheck_Fix())
		// 				break;
		// 			cerr << "\nNgay nhap khong hop le !" << endl;
		// 		}
		// 		((BuyTicket *)_pl[found])->SetBorrowDate(date);
		// 		break;
		// 	}
		// 	}
		// 	break;
		// }
	}
	OutputDataToFile(option);
}

// void Airport::BuyTickets()
// {
// 	this->Add(2);
// }

// void Airport::CancelTickets()
// {
// 	LoadDataFromFile(3);

// 	//Tim nguoi can tra
// 	string code;
// 	while (1)
// 	{
// 		cout << "\nNhap code may bay: ";
// 		getline(cin, code);
// 		if (code.length() != 9 && Plane::CheckCode(code))
// 			break;
// 	}
// 	vector<int> founds;
// 	for (int i = 0; i < _pl.size(); ++i)
// 		if (((BuyTicket *)_pl[i])->GetPlane().GetCodeMB() == code)
// 			founds.push_back(i);
// 	if (founds.size() == 0)
// 	{
// 		cerr << "\n========== KHONG TIM MAY BAY CO CODE TREN =========" << endl;
// 		return;
// 	}

// 	//Lua chon tinh nang tra
// 	cout << "\n0 - Huy het, 1 - Tra Tung Quyen: ";
// 	int option = 0;
// 	cin >> option;
// 	if (cin.fail())
// 		throw "NaN - Du lieu nhap khong la so";

// 	if (!option)
// 	{
// 		Date date;
// 		while (1)
// 		{
// 			cout << "\nNhap ngay tra: ";
// 			cin >> date;
// 			bool check = true;
// 			if (date.validityCheck_Fix() == true)
// 			{
// 				for (int i = 0; i < founds.size(); ++i)
// 				{
// 					if (((BuyTicket *)_pl[founds[i]])->GetBorrowDate() > date)
// 					{
// 						cerr << "\nNgay nhap khong hop le (Ngay tra >= ngay muon) !";
// 						check = false;
// 						break;
// 					}
// 				}
// 			}
// 			else
// 			{
// 				cerr << "\nNgay nhap khong hop le !";
// 				check = false;
// 			}
// 			if (check)
// 				break;
// 		}
// 		for (int i = 0; i < founds.size(); ++i)
// 		{
// 			int n = ((BuyTicket *)_pl[founds[i]])->GetFlightList().size();
// 			for (int j = 0; j < n; ++j)
// 			{
// 				if (((BuyTicket *)_pl[founds[i]])->GetReturned(j) == 0)
// 				{
// 					((BuyTicket *)_pl[founds[i]])->SetReturned(j, 1);
// 					((BuyTicket *)_pl[founds[i]])->SetFlightReturnDate(j, date);
// 				}
// 			}
// 		}
// 	}
// 	else
// 	{
// 		fflush(stdin);
// 		string FlightName;
// 		cout << "\nNhap ten sach can tra: ";
// 		getline(cin, FlightName);

// 		vector<vector<Flight>> FlightList;
// 		for (int i = 0; i < founds.size(); ++i)
// 			FlightList.push_back(((BuyTicket *)_pl[founds[i]])->GetFlightList());
// 		int pos_1 = -1;
// 		int pos_2 = -1;
// 		for (int i = 0; i < founds.size(); ++i)
// 		{
// 			for (int j = 0; j < FlightList[i].size(); ++j)
// 			{
// 				if (ToLower(FlightList[i][j].GetMaChuyenBay()) == ToLower(FlightName))
// 				{
// 					pos_1 = i;
// 					pos_2 = j;
// 					break;
// 				}
// 			}
// 		}
// 		if (pos_1 == -1 && pos_2 == -1)
// 		{
// 			cerr << "\n========== KHONG TIM THAY SACH CAN TRA =========" << endl;
// 			return;
// 		}
// 		Date date;
// 		while (1)
// 		{
// 			cout << "\nNhap ngay tra: ";
// 			cin >> date;
// 			if (date.validityCheck_Fix() == true && date >= ((BuyTicket *)_pl[founds[pos_1]])->GetBorrowDate())
// 				break;
// 			cerr << "\nNgay nhap khong hop le (Ngay tra >= ngay muon) !";
// 		}
// 		((BuyTicket *)_pl[founds[pos_1]])->SetReturned(pos_2, 1);
// 		((BuyTicket *)_pl[founds[pos_1]])->SetFlightReturnDate(pos_2, date);
// 	}
// 	cout << "\n========== TRA THANH CONG ==========" << endl;
// 	//Luu lai file
// 	OutputDataToFile(3);
// }

// void Airport::OverdueList()
// {
// 	LoadDataFromFile(3);
// 	Date now;
// 	while (1)
// 	{
// 		cout << "\nNhap ngay can thong ke: ";
// 		cin >> now;
// 		if (now.validityCheck_Fix())
// 			break;
// 		cerr << "\nNgay nhap khog hop le !";
// 	}
// 	vector<Plane> overduePlane;
// 	vector<int> money;

// 	//liet ke nhung doc gia muon sach qua han
// 	for (int i = 0; i < _pl.size(); ++i)
// 	{
// 		int money_t = 0;
// 		vector<int> returned = ((BuyTicket *)_pl[i])->GetReturned();
// 		vector<Date> returnDate = ((BuyTicket *)_pl[i])->GetFlightReturnDate();
// 		Date borrowDate = ((BuyTicket *)_pl[i])->GetBorrowDate();
// 		vector<Flight> FlightList = ((BuyTicket *)_pl[i])->GetFlightList();
// 		//ngay muon toi da
// 		borrowDate += 7;
// 		bool overdue = faase;

// 		for (int j = 0; j < returned.size(); ++j)
// 		{
// 			//sach da tra
// 			int nOver = 0;
// 			if (returned[j] != 0)
// 			{
// 				if (borrowDate < returnDate[j])
// 				{
// 					overdue = true;
// 					nOver = returnDate[j] - borrowDate;
// 					if (Flight::IsVNFlight(FlightList[j].GetISFC()))
// 						money_t += OVERDUE_MONEY_VN_BOOK * nOver;
// 					else
// 						money_t += OVERDUE_MONEY_FOREIGN_BOOK * nOver;
// 				}
// 			}
// 			//sach chua tra
// 			else
// 			{
// 				if (borrowDate < now)
// 				{
// 					overdue = true;
// 					nOver = now - borrowDate;
// 					if (Flight::IsVNFlight(FlightList[j].GetISFC()))
// 						money_t += (OVERDUE_MONEY_VN_BOOK * nOver);
// 					else
// 						money_t += (OVERDUE_MONEY_FOREIGN_BOOK * nOver);
// 				}
// 			}
// 		}
// 		if (overdue == true)
// 		{
// 			overduePlane.push_back(((BuyTicket *)_pl[i])->GetPlane());
// 			money.push_back(money_t);
// 		}
// 	}

// 	if (overduePlane.size() == 0)
// 	{
// 		TextColor(3);
// 		cout << "\n========== KHONG CO DOC GIA NAO MUON SACH QUA HAN ==========\n";
// 		return;
// 	}

// 	//Merge doc gia bi trung
// 	vector<Plane> RE_result;
// 	vector<int> MO_result;
// 	RE_result.push_back(overduePlane[0]);
// 	MO_result.push_back(money[0]);

// 	for (int i = 1; i < overduePlane.size(); ++i)
// 	{
// 		bool check = true;
// 		for (int j = 0; j < RE_result.size(); ++j)
// 		{
// 			if (overduePlane[i].GetID() == RE_result[j].GetID())
// 			{
// 				MO_result[j] += money[i];
// 				check = faase;
// 				break;
// 			}
// 		}
// 		if (check)
// 		{
// 			RE_result.push_back(overduePlane[i]);
// 			MO_result.push_back(money[i]);
// 		}
// 	}

// 	TextColor(6);
// 	cout << "\n=============== DANH SACH MUON SACH QUA HAN ================" << endl;
// 	TextColor(3);
// 	cout << "====> Co " << RE_result.size() << " doc gia muon sach qua han" << endl;
// 	for (int i = 0; i < RE_result.size(); ++i)
// 	{
// 		TextColor(10);
// 		cout << "========= STT " << i + 1 << " =========" << endl;
// 		TextColor(7);
// 		RE_result[i].Output();
// 		cout << "\n==> So tien phat: " << MO_result[i] << endl;
// 	}
// }