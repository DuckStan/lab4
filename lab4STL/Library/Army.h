#pragma once
#ifndef _ARMY_H_
#define _ARMY_H_

#include <iostream>
#include "Table.h"

namespace Army{
	const char *def = "Unknown";
	const char ranks[][20] = { "Officer Cadet", "Second Lieutenant", "Lieutenant", "Captain", "Major", "Lieutenant-Colonel", "Colonel", "Brigadier", "Major-General","Lieutenant-General", "General", "Field-Marshal" };
	const char specs[][20] = { "Pehota", "Specnaz", "Razvedchik", "Sniper", "Saper", "RHBZ", "Sanitar", "Radist" };
	const char hq_posts[][20] = { "military HQ", "army HQ", "corps HQ", "division HQ", "brigade HQ" };
	const char locations[][20] = { "North", "South", "West", "East"};

	struct Instruction {
		char* words = nullptr;
		int reglament;
	};
	int dialog_window(std::istream& is, int class_type);
class Person{
private:
	char* name=nullptr;
	char* surname=nullptr;
	char* patronymic=nullptr;
	int rank;
	int uniform_size;
public:
	//constructor
	Person();
	Person(char* g_name, char* g_surname, char* g_patronymic, int g_rank, int g_uniform_size);
	Person(const Person& p);
	//destructor
	~Person() {
		delete[] name;
		delete[] surname;
		delete[] patronymic;
	}
	//operator overload
	friend std::ostream& operator <<(std::ostream&, const Person&);
	friend std::istream& operator >>(std::istream&, Person&);
	//getters
	char* get_name() const { return name; }
	char* get_surname() const { return surname; }
	char* get_patronymic() const { return patronymic; }
	int get_rank() const { return rank; }
	int get_uniform_size() const { return uniform_size; }
	//setters
	Person& set_name(char* g_name);
	Person& set_surname(char* g_surname);
	Person& set_patronymic(char* g_patronymic);
	Person& set_rank(int g_rank);
	Person& set_uniform_size(int g_uniform_size);
};
class Soldier {
protected:
	virtual std::ostream& show(std::ostream&, int condition = 0)const = 0;
	virtual std::istream& get(std::istream&, int condition = 0) = 0;
public:
	virtual std::istream& edit(std::istream&, int condition = 0) = 0;
	virtual bool am_i_sanitar() = 0;
	virtual int my_rank() = 0;
	virtual int my_spec() = 0;
	virtual Soldier* clone()const = 0;
	friend std::ostream& operator <<(std::ostream&, const Soldier&);
	friend std::istream& operator >>(std::istream&, Soldier&);
	virtual ~Soldier() = 0;
};
class Field_fighter : virtual public Soldier{
private:
	Person person;
protected:
	int spec;
	char** orders=nullptr;
	int n_orders=0;
	virtual std::ostream& show(std::ostream&, int condition = 0)const;
	virtual std::istream& get(std::istream&, int condition = 0);
	virtual std::istream& edit(std::istream&, int condition = 0);
	virtual bool am_i_sanitar();
	virtual int my_rank();
	virtual int my_spec();
	void delete_orders(char** some_orders);
	int delete_order(int order_n);
public:
	//constructors
	Field_fighter(): person(), spec(0), n_orders(0){}
	Field_fighter(char* g_name, char* g_surname, char* g_patronymic, int g_rank, int g_uniform_size, int spec=0, char *order=nullptr);
	Field_fighter(const Person& p, int spec = 0, char* order = nullptr);
	virtual Field_fighter* clone() const {
		return new Field_fighter(*this);
	}
	//destructor
	~Field_fighter();
	//getters
	const char* get_spec() const { return specs[spec]; }
	char* get_recent_order() const{ if (n_orders > 0) return orders[0]; else return nullptr; }
	char* get_last_order() const{ if (n_orders > 0) return orders[n_orders - 1]; else return nullptr; }
	//setters
	Field_fighter& add_order(char* g_order = nullptr);
	Field_fighter& set_spec(int g_spec = 0);
};
class Staff_officer: virtual public Soldier {
private:
	Person person;
protected:
	int hq_post;
	int n_instructions;
	Instruction *instructions=nullptr;
	virtual std::ostream& show(std::ostream&, int condition = 0)const;
	virtual std::istream& get(std::istream&, int condition = 0);
	virtual std::istream& edit(std::istream&, int condition = 0);
	virtual bool am_i_sanitar();
	virtual int my_rank();
	virtual int my_spec();
	void delete_instructions(Instruction* some_instr);
	int delete_instr(int instr_reg);
public:
	//constructors
	Staff_officer() : person(), hq_post(0), n_instructions(0) {}
	Staff_officer(char* g_name, char* g_surname, char* g_patronymic, int g_rank, int g_uniform_size, int g_hq_post = 1, char* g_words = nullptr, int g_reg = 0);
	Staff_officer(const Person& p, int g_hq_post = 1, char* g_words = nullptr, int g_reg = 0);
	virtual Staff_officer* clone() const {
		return new Staff_officer(*this);
	}
	//destructor
	~Staff_officer();
	//getters
	const char* get_post() const { return hq_posts[hq_post]; }
	char* get_recent_instruction() const{ if (n_instructions > 0) return instructions[0].words; else return nullptr; }
	char* get_last_instruction() const{ if (n_instructions > 0) return instructions[n_instructions - 1].words; else return nullptr; }
	//setters
	Staff_officer& add_instruction(int g_reg, char* g_words = nullptr);
	Staff_officer& set_post(int g_post = 0);
};
class Field_commander: public Field_fighter, public Staff_officer {
private:
	Subdivision* subdivision;
	Person person;
protected:
	virtual std::ostream& show(std::ostream&, int condition = 0)const;
	virtual std::istream& get(std::istream&, int condition = 0);
	virtual std::istream& edit(std::istream&, int condition = 0);
	virtual int my_rank();
	virtual int my_spec();
	virtual bool am_i_sanitar();
public:
	Field_commander() : person(), Field_fighter(), Staff_officer(){}
	virtual Field_commander* clone() const {
		return new Field_commander(*this);
	}
	Subdivision* get_subdivision();
	int set_subdivision_table(Matrix::Table g_table) { subdivision->set_table(g_table); return 0; }
};
class Max_commander: public Staff_officer {
private:
	Subdivision* subdivision;
	Person person;
protected:
	virtual std::ostream& show(std::ostream&, int condition = 0)const;
	virtual std::istream& get(std::istream&, int condition = 0);
	virtual std::istream& edit(std::istream&, int condition = 0);
	virtual bool am_i_sanitar();
	virtual int my_rank();
	virtual int my_spec();
public:
	Max_commander() : person(), Staff_officer() {}
	virtual Max_commander* clone() const {
		return new Max_commander(*this);
	}
};
class Subdivision {
private:
	Matrix::Table table;
	int location;
	int type;//shtab ili ne shtab?
public:
	//constructors
	Subdivision() : table(), location(0), type(0){}
	Subdivision(Matrix::Table &g_table, int g_location = 0, int g_type = 0);
	//getters
	Matrix::Table get_table() const { return table; }
	int get_location() const { return location; }
	int get_type() const { return type; }
	//setters
	int set_table(Matrix::Table& g_table) { table = g_table; return 0; }
	int set_location(int g_location);
	int set_type(int g_type = 1) {
		if ((g_type == 0) || (g_type == 1)) { type = g_type; return 0; }
		else throw std::exception("Invalid subdivision type!");
		return 0;
	}
};
class Infield {
private:
	Field_commander *commander_1=nullptr, *commander_2=nullptr;
	int location;
	int duration;
public:
	int get_soldier(int g_key) const;
	int edit_soldier(int g_key);
	int get_n(int team, int condition = 0, int g_rank = 69, int g_spec = 69) const;
	int delete_soldier(int g_key);
	int swap_soldier(int g_key);
};
}


#endif