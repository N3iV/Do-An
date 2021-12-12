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
	double _giaVe;
	int _trangThai;

public:
	Flight();
	Flight(const Flight &);
	Flight(const string &maChuyenBay, const string &noiDen, const string &noiDi, const string &ISFC, double giaVe, int ngay, int thang, int nam, int trangThai);
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
	int GetTrangThai() const;

	void SetMaChuyenBay(const string &title);
	void SetMaHieu(const string &title);
	void SetNoiDen(const string &noiDen);
	void SetNoiDi(const string &noiDi);
	void SetISFC(const string &ISFC);
	void SetGia(double price);
	void SetNgay(int);
	void SetThang(int);
	void SetNam(int);
	void SetTrangThai(int);

	string GetKey();
	void SetKey(const string &);

	//* ---- VALIDATE ---- *//
	static bool CheckFC(const string &ISFC);
	bool isLeapYear();
	bool ValidateYear(int nam);
	bool ValidateMonth(int thang);
	bool ValidateDay(int ngay);
	bool CheckDay(int ngay, int thang, int nam);
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
