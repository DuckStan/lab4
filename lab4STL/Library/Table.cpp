#include <iostream>
#include "Table.h"
#include <vector>

namespace Matrix{
	std::ostream& operator <<(std::ostream& os, const std::vector<Item>::const_iterator p) {
		return os << '"' << p->key << '"' << " - " << '"' << status[p->status] << '"' << " - " << p->info;
	}
	Table::Table(const Table& a)
	{
		std::vector<Item>::const_iterator p;
		for (p = a.arr.begin(); p != a.arr.end(); ++p)
			arr.push_back(*p);
	}
	Table::~Table()
	{
		std::vector<Item>::iterator p;
		for (p = arr.begin(); p != arr.end(); ++p) {
			delete p->info;
			p->info = nullptr;
		}
	}
	Table& Table::operator = (const Table& a)
	{
		std::vector<Item>::iterator p;
		if (this != &a) {
			for (p = arr.begin(); p != arr.end(); ++p)
				delete p->info;
			arr.clear();
		
			std::vector<Item>::const_iterator pp;
			for (pp = a.arr.begin(); pp != a.arr.end(); ++pp)
				arr.push_back(*pp);
		}
		return *this;
	}
	bool Table::find_element(const int g_key) {
		std::vector<Item>::iterator p;
		for (p = arr.begin(); p != arr.end(); ++p) {
			if (p->key == g_key) {
				return true;
			}
		}
		return false;
	}
	bool Table::insert(const int g_key, int g_status, const Army::Soldier* g_soldat)
	{
		bool res = false;
		if (find_element(g_key)) {
			std::cout << "There is already a soldier with this number!" << std::endl;
			return res;
		}
		else {
			if ((g_status < 0) || (g_status > 3)) {
				std::cout << "Wrong status!" << std::endl;
				return res;
			}
			Item p;
			p.key = g_key;
			p.status = g_status;
			p.info = g_soldat->clone();
			res = true;
		}
		return res;
	}
	bool Table::remove(const int g_key)
	{
		bool res = false;
		if (find_element(g_key)) {
			std::vector<Item>::iterator p;
			for (p = arr.begin(); p != arr.end(); ++p) {
				if (p->key == g_key) break;
			}
			delete p->info;
			arr.erase(p);
			res = true;
		}
		else {
			std::cout << "No such element buddy!" << std::endl;
			return res;
		}
		return res;
	}
	bool Table::replace(const int g_key, const int g_status, const Army::Soldier* g_soldat)
	{
		bool res = false;
		if (find_element(g_key)) {
			if ((g_status < 0) || (g_status > 3)) {
				std::cout << "Wrong status!" << std::endl;
				return res;
			}
			std::vector<Item>::iterator p;
			for (p = arr.begin(); p != arr.end(); ++p) {
				if (p->key == g_key) break;
			}
			p->status = g_status;
			p->info = g_soldat->clone();
			res = true;
		}
		else {
			std::cout << "No such element buddy!" << std::endl;
			return res;
		}
		return res;
	}
	bool Table::change_status(const int g_key, const int g_status) {
		bool res = false;
		if (find_element(g_key)) {
			if ((g_status < 0) || (g_status > 3)) {
				std::cout << "Wrong status!" << std::endl;
				return res;
			}
			std::vector<Item>::iterator p, p_2;
			for (p = arr.begin(); p != arr.end(); ++p) {
				if (p->key == g_key) break;
			}
			if ((p->status == 2)) {
				std::cout << "Sorry man he is dead";
				return res;
			}
			bool any_sanitar = false;
			for (p_2 = arr.begin(); p_2 != arr.end(); ++p) {
				if (p->info->am_i_sanitar()) any_sanitar = true;
			}
			if ((p->status == 1) || (!any_sanitar)) {
				std::cout << "Sorry man no sanitar to help him. He will die ahahah";
				return res;
			}
			p->status = g_status;
			res = true;
		}
		else {
			std::cout << "No such element buddy!" << std::endl;
			return res;
		}
		return res;
	}
	bool Table::edit_element(int g_key) {
		bool res = false;
		std::vector<Item>::iterator p;
		if (find_element(g_key)) {
			for (p = arr.begin(); p != arr.end(); ++p) {
				if (p->key == g_key) break;
			}
			p->info->edit(std::cin);
			res = true;
		}
		else {
			std::cout << "No such element buddy!" << std::endl;
			return res;
		}
		return res;
	}
	int Table::get_amount_of_fighters(int condition=0, int g_rank=69, int g_spec=69, int g_status = 69) {
		int count = 0;
		if ((condition == 1) && (g_rank!=69)) {
			if ((g_rank < 0) || (g_rank > 11)) {
				throw std::exception("Wrong rank!");
			}
			std::vector<Item>::const_iterator p;
			for (p = arr.begin(); p != arr.end(); ++p) {
				if (p->info->my_rank() == g_rank) count++;
			}
			return count;
		}
		if ((condition == 2) && (g_spec != 69)) {
			if ((g_spec < 0) || (g_spec > 7)) {
				throw std::exception("Wrong spec!");
			}
			std::vector<Item>::const_iterator p;
			for (p = arr.begin(); p != arr.end(); ++p) {
				if (p->info->my_spec() == g_spec) count++;
			}
			return count;
		}
		if (g_status == 69) {
			std::vector<Item>::const_iterator p;
			for (p = arr.begin(); p != arr.end(); ++p) {
				count++;
			}
			return count;
		}
		if(g_status!=69){
			if ((g_status < 0) || (g_status > 3)) {
				throw std::exception("Wrong status!");
			}
			std::vector<Item>::const_iterator p;
			for (p = arr.begin(); p != arr.end(); ++p) {
				if (p->status == g_status) count++;
			}
			return count;
		}
		return count;
	}
	Table::Const_Iterator Table::find(const int g_key) const
	{
		std::vector<Item>::const_iterator p;
		for (p = arr.begin(); p != arr.end(); ++p) {
			if (p->key == g_key) {
				return ConstTableIt(p);
			}
		}
		throw std::exception("No element with that key!");
	}
	Table::Const_Iterator Table::begin() const
	{
		return Table::Const_Iterator(arr.begin());
	}
	Table::Const_Iterator Table::end() const
	{
		return Table::Const_Iterator(arr.end());
	}
	int ConstTableIt::operator !=(const ConstTableIt& it) const
	{
		return cur != it.cur;
	}
	int ConstTableIt::operator ==(const ConstTableIt& it) const
	{
		return cur == it.cur;
	}
	const Item& ConstTableIt::operator *()
	{
		return *cur;
	}
	const Item* ConstTableIt::operator ->()
	{
		return &*cur;
	}
	ConstTableIt& ConstTableIt::operator ++()
	{
		++cur;
		return *this;
	}
	ConstTableIt ConstTableIt::operator ++(int)
	{
		ConstTableIt res(*this);
		++cur;
		return res;
	}
};