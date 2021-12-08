#pragma once
#ifndef _BUYTICKET_
#define _BUYTICKET_
#include "AirportSystem.h"
#include "Airport.h"
#include "Date.h"
class BuyTicket : public AirportSystem
{
private:
	vector<AirportSystem *> _as;
	string _Name;
	string _UserCode;
	string _ID;
	Date date;

public:
	BuyTicket();
	BuyTicket(const string &, const string &, const string &);
	~BuyTicket();
	string GetMaCB() const;
	string GetName() const;
	string GetUserCode() const;
	string GetID() const;

	void SetMaCB(const string &);
	void SetName(const string &);
	void SetUserCode(const string &);
	void SetID(const string &);
	void SetDate(Date date);
	static bool CheckUserCode(const string &);
	static bool CheckID(const string &);

	void Input();
	void Output();
	string FormatUserCode() const;

	void InputFile(ifstream &input);
	void OutputFile(ofstream &path);

	BuyTicket &operator=(const BuyTicket &BuyTicket);
	friend ostream &operator<<(ostream &os, const BuyTicket &BuyTicket);
};
#endif
