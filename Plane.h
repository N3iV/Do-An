#pragma once
#include "Display.h"
#include "AirportSystem.h"
#ifndef _PLANES_
#define _PLANES_

class Plane : public AirportSystem
{
private:
	string _maHieu;
	string _loaiMB;
	string _code;
	int _soDay;
	int _soGhe;

public:
	Plane();
	Plane(const Plane &users);
	Plane(string maHieu, string loaiMB, string code, int soDay, int soGhe);
	~Plane();

	string GetMaHieu() const;
	string GetLoaiMB() const;
	string GetCodeMB() const; // dung const vi` khong cho thay doi
	int GetSoDay() const;
	int GetSoGhe() const;
	int GetVe() const;

	void SetMaHieu(const string &name);
	void SetLoaiMB(const string &name);
	void SetCodeMB(const string &code);
	void SetSoDay(int age);
	void SetSoGhe(int soGhe);
	static bool CheckCode(const string &code);
	static bool CheckMaMayBay(const string &maHieu);

	void PrintSeats();
	void Input();
	void Output();

	void InputFile(ifstream &input);
	void OutputFile(ofstream &path);
	string GetKey();
	Plane &operator=(const Plane &r);
	friend ostream &operator<<(ostream &os, const Plane &users);
	friend bool operator==(const Plane &r1, const Plane &r2);
};

#endif
