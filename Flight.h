#pragma once
#ifndef _FLIGHT_
#define _FLIGHT_
#include "AirportSystem.h"
#include "Date.h"
#include "Display.h"
class Flight : public AirportSystem
{
private:
	string _maHieu;
	string _maChuyenBay;
	string _noiDen;
	string _noiDi;
	string _ISFC;
	int _ngay;
	int _thang;
	int _nam;
	int _gio;
	int _phut;
	double _giaVe;
	int _trangThai;

public:
	Flight();
	Flight(const Flight &);
	Flight(const string &, const string &, const string &, const string &, const double &, const int &, const int &, const int &, const int &, const int &);
	~Flight();

	string GetMaChuyenBay() const;
	string GetMaHieu() const;
	string GetNoiDen() const;
	string GetNoiDi() const;
	string GetISFC() const;
	double GetGia() const;
	int GetNgay() const;
	int GetThang() const;
	int GetNam() const;
	int GetGio() const;
	int GetPhut() const;
	int GetTrangThai() const;

	void SetMaChuyenBay(const string &);
	void SetMaHieu(const string &);
	void SetNoiDen(const string &);
	void SetNoiDi(const string &);
	void SetISFC(const string &);
	void SetGia(const double &);
	void SetNgay(const int &);
	void SetThang(const int &);
	void SetNam(const int &);
	void SetGio(const int &);
	void SetPhut(const int &);
	void SetTrangThai(const int &);

	string GetKey();
	void SetKey(const string &);

	//* ---- VALIDATE ---- *//
	static bool CheckFC(const string &);
	bool isLeapYear();
	bool ValidateYear(int);
	bool ValidateMonth(int);
	bool ValidateDay(int);
	bool CheckDay(int, int, int, int);
	string FormatISFC() const;
	//*----------------------*//

	void Input();
	void Output();
	void OutputMainInfo();

	// *---------------------------*//

	void InputFile(ifstream &input);
	void OutputFile(ofstream &path);

	Flight &operator=(const Flight &Flight);
	friend ostream &operator<<(ostream &os, const Flight &Flight);
};
#endif
