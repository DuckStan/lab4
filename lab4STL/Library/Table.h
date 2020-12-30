#pragma once
#ifndef _TABLE_H_
#define _TABLE_H_
#include <iostream>
#include <vector>
#include "Army.h"
#include <string>

namespace Matrix {
	const char status[][20] = { "Ok", "Injured", "Dead", "Missing"};
	struct Item {
		int key;
		int status;
		Army::Soldier* info;
	};
	std::ostream& operator <<(std::ostream& os, const std::vector<Item>::const_iterator p);
	class Table {
	private:
		std::vector<Item> arr;
		friend class ConstTableIt;
		bool find_element(int g_key);
	public:
		Table(){}
		Table(const Table&);
		~Table();
		Table& operator = (const Table&);
		typedef ConstTableIt Const_Iterator;
		Const_Iterator find(int key)const;
		bool insert(int g_key, int g_status, const Army::Soldier* g_soldat);
		bool replace(const int g_key, const int g_status, const Army::Soldier* g_soldat);
		bool remove(const int key);
		bool edit_element(int g_key);
		int get_amount_of_fighters(int condition = 0, int g_rank = 69, int g_spec = 69, int g_status = 69);
		bool change_status(const int g_key, const int g_status);
		Const_Iterator begin() const;
		Const_Iterator end() const;
	};
	class ConstTableIt {
	private:
		std::vector<Item>::const_iterator cur;
	public:
		ConstTableIt(){}
		ConstTableIt(std::vector<Item>::iterator ob) :cur(ob) {}
		ConstTableIt(std::vector<Item>::const_iterator ob) :cur(ob) {}
		int operator !=(const ConstTableIt&) const;
		int operator ==(const ConstTableIt&) const;
		const Item& operator *();
		const Item* operator ->();
		ConstTableIt& operator ++();
		ConstTableIt operator ++(int);
	};
}

#endif
