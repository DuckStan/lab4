#include "pch.h"
#include "Army.h"

namespace Army {
	Person& Person::set_name(char* g_name) {
		if (name != nullptr) {
			delete[] name;
		}
		name = new char[strlen(g_name) + 1];
		for (int i = 0; i < strlen(g_name) + 1; i++) {
			name[i] = g_name[i];
		}
		return *this;
	}
	Person& Person::set_surname(char* g_surname) {
		if (surname != nullptr) {
			delete[] surname;
		}
		surname = new char[strlen(g_surname) + 1];
		for (int i = 0; i < strlen(g_surname) + 1; i++) {
			surname[i] = g_surname[i];
		}
		return *this;
	}
	Person& Person::set_patronymic(char* g_patronymic) {
		if (patronymic != nullptr) {
			delete[] patronymic;
		}
		patronymic = new char[strlen(g_patronymic) + 1];
		for (int i = 0; i < strlen(g_patronymic) + 1; i++) {
			surname[i] = g_patronymic[i];
		}
		return *this;
	}
	Person::Person() : rank(0), uniform_size(48) {
		name = new char[strlen(def) + 1];
		surname = new char[strlen(def) + 1];
		patronymic = new char[strlen(def) + 1];
		for (int i = 0; i < strlen(def) + 1; i++) {
			name[i] = def[i];
			surname[i] = def[i];
			patronymic[i] = def[i];
		}
	}
	Person& Person::set_rank(int g_rank) {
		if ((g_rank >= 0) && (g_rank <= 11)) rank = g_rank; else throw std::exception("Invalid rank!");
		return *this; 
	}
	Person& Person::set_uniform_size(int g_uniform_size) { 
		if ((g_uniform_size >= 0) && (g_uniform_size <= 11)) uniform_size = g_uniform_size; else throw std::exception("Invalid uniform size!");
		return *this; 
	}
	Person::Person(char* g_name, char* g_surname, char* g_patronymic, int g_rank, int g_uniform_size) {
		try {
			set_name(g_name);
			set_surname(g_surname);
			set_patronymic(g_patronymic);
			set_rank(g_rank);
			set_uniform_size(g_uniform_size);
		}
		catch (std::exception &ex) {
			std::cout << ex.what() << std::endl;
		}
		
	}
	Person::Person(const Person& p){
		Person(p.name, p.surname, p.patronymic, p.rank, p.uniform_size);
	}
	std::ostream& operator <<(std::ostream& os, const Person& p)
	{
		return os << p.name << " " << p.surname << " " << p.patronymic << ranks[p.rank] << p.uniform_size;
	}
	std::istream& operator >>(std::istream& is, Person& p)
	{
		char g_name[20];
		char g_surname[20];
		char g_patronymic[20];
		int g_rank, g_uniform_size;

		std::cout << "Please, input the name, surname, patronymic, rank and uniform size:" << std::endl;
		is >> g_name >> g_surname >> g_patronymic >> g_rank >> g_uniform_size;

		if (is.good()) {
			try {
				p.set_name(g_name);
				p.set_surname(g_surname);
				p.set_patronymic(g_patronymic);
				p.set_rank(g_rank);
				p.set_uniform_size(g_uniform_size);
			}
			catch (std::exception& ex) {
				throw std::exception(ex.what());
			}
		}
		else {
			throw std::exception("Something went wrong with the stream!");
		}
		return is;
	}
	void Field_fighter::delete_orders(char **some_orders) {
		if (some_orders != nullptr) {
			for (int i = 0; i < sizeof(some_orders)/sizeof(char**); i++) {
				delete[] some_orders[i];
			}
			delete[] some_orders;
		}
	}
	int Field_fighter::delete_order(int order_n) {
		if ((order_n > n_orders) || (order_n < 0)) throw std::exception("Invalid order number!");
		delete[] orders[order_n-1];
		for (int i = order_n-1; i < n_orders-1; i++) {
			orders[i] = orders[i + 1];
		}
		char** temp = nullptr;
		temp = orders;
		orders = new char* [n_orders - 1];
		for (int i = 0; i < n_orders-1; i++) {
			orders[i] = temp[i];
		}
		delete_orders(temp);
		return 0;
	}
	Field_fighter& Field_fighter::add_order(char* g_order = nullptr) {
		if (g_order != nullptr) {
			char** temp = nullptr;
			temp = orders;
			orders = new char*[n_orders+1];
			for (int i = 0; i < n_orders; i++) {
				orders[i] = new char[strlen(temp[i]) + 1];
				for (int j = 0; j < strlen(temp[i])+1; j++) {
					orders[i][j] = temp[i][j];
				}
			}
			delete_orders(temp);
			for (int i = 0; i < strlen(g_order) + 1; i++) {
				orders[n_orders][i] = g_order[i];
			}
			n_orders++;
		}
		else {
			throw std::exception("Where is the order?");
		}
		return *this;
	}
	Field_fighter& Field_fighter::set_spec(int g_spec = 0) {
		if ((g_spec >= 0) && (g_spec <= 7)) spec = g_spec; else throw std::exception("Invalid spec number!");
		return *this;
	}
	Field_fighter::Field_fighter(char* g_name, char* g_surname, char* g_patronymic, int g_rank, int g_uniform_size, int g_spec = 0, char* g_order = nullptr) : person(g_name,  g_surname,  g_patronymic, g_rank,  g_uniform_size){
		try {
		add_order(g_order);
		set_spec(g_spec);
		}
		catch (std::exception& ex) {
			std::cout << ex.what() << std::endl;
		}
	}
	Field_fighter::Field_fighter(const Person& p, int g_spec = 0, char* g_order = nullptr): person(p) {
		try {
			add_order(g_order);
			set_spec(g_spec);
		}
		catch (std::exception& ex) {
			std::cout << ex.what() << std::endl;
		}
	}
	Field_fighter:: ~Field_fighter() {
		delete_orders(orders);
	}
	std::ostream& Field_fighter::show(std::ostream& os, int condition = 0)const
	{
		if (condition == 0) {
			os << "Field Fighter: " << person;
		}

		os << get_spec() << std::endl;

		os << "Orders available:" << std::endl;
		for (int i = 0; i < n_orders; i++) {
			os << i << ". " << orders[i] << std::endl;
		}

		return os << std::endl;
	}
	std::istream& Field_fighter::get(std::istream& is, int condition = 0){

		if (condition == 0) {
			try {
				is >> person;
			}
			catch (std::exception& ex) {
				throw std::exception(ex.what());
			}
		}

		int g_spec;
		std::cout << "List of specialties:" << std::endl;
		for (int i = 0; i < 8; i++) {
			std::cout << i << ". " << specs[i] << std::endl;
		}
		std::cout << "Choose one of them:";
		is >> g_spec;
		try {
			set_spec(g_spec);
		}
		catch (std::exception& ex) {
			throw std::exception(ex.what());
		}
		while (1) {
			int done = 0;
			std::cout << "Input the order:" << std::endl;
			char temp[20];
			is >> temp;
			if (is.good()) {
				try {
					add_order(temp);
				}
				catch (std::exception& ex) {
					throw std::exception(ex.what());
				}
			}
			else {
				throw std::exception("Something bad happened to the stream!");
			}
			std::cout << "Input 1 if you are done:" << std::endl;
			std::cin >> done;
			if (done == 1) break;
		}
		return is;
	}
	int dialog_window(std::istream& is,int class_type) {
		int k = 0;
		std::cout << "What do you want to edit?" << std::endl;
		std::cout << "0. Exit" << std::endl;
		std::cout << "1. Name" << std::endl;
		std::cout << "2. Surname" << std::endl;
		std::cout << "3. Patronymic" << std::endl;
		std::cout << "4. Rank" << std::endl;
		std::cout << "5. Uniform size" << std::endl;

		if ((class_type == 1) || (class_type == 3)) {
			std::cout << "6. Specialty" << std::endl;
			std::cout << "7. Orders" << std::endl;
		}
		if ((class_type == 2) || (class_type == 4)) {
			std::cout << "6. HQ Post" << std::endl;
			std::cout << "7. Instructions" << std::endl;
		}
		if ((class_type == 3)) {
			std::cout << "8. HQ Post" << std::endl;
			std::cout << "9. Instructions" << std::endl;
		}
		std::cout << "Input the number: ";
		is >> k;
		return k;
	}
	template <class T>
	int set_person_parameters(std::istream& is,T& obj,int p) {
		if ((p <= 0) || (p > 5)) throw std::exception(" Our parameter was hacked");
		switch (p) {
		case 1:
			char g_name[20];
			std::cout << "Input the new name: ";
			is >> g_name;
			if (is.good()) {
				try {
					obj.person.set_name(g_name);
				}
				catch (std::exception& ex) {
					throw std::exception(ex.what());
				}
			}
			else {
				throw std::exception("Something bad happened to the stream!");
			}
		case 2:
			char g_surname[20];
			std::cout << "Input the new surname: ";
			is >> g_surname;
			if (is.good()) {
				try {
					obj.person.set_surname(g_surname);
				}
				catch (std::exception& ex) {
					throw std::exception(ex.what());
				}
			}
			else {
				throw std::exception("Something bad happened to the stream!");
			}
		case 3:
			char g_patronymic[20];
			std::cout << "Input the new patronymic: ";
			is >> g_patronymic;
			if (is.good()) {
				try {
					obj.person.set_patronymic(g_patronymic);
				}
				catch (std::exception& ex) {
					throw std::exception(ex.what());
				}
			}
			else {
				throw std::exception("Something bad happened to the stream!");
			}
		case 4:
			int g_rank;
			std::cout << "Input the new rank: ";
			is >> g_rank;
			if (is.good()) {
			try {
				obj.person.set_rank(g_rank);
			}
			catch (std::exception& ex) {
				throw std::exception(ex.what());
			}
			}
			else {
				throw std::exception("Something bad happened to the stream!");
			}
		case 5:
			int g_uniform_size;
			std::cout << "Input the new uniform size: ";
			is >> g_unfirom_size;
			if (is.good()) {
				try {
					obj.person.set_uniform_size(g_uniform_size);
				}
				catch (std::exception& ex) {
					throw std::exception(ex.what());
				}
			}
			else {
				throw std::exception("Something bad happened to the stream!");
			}

		}
		return 0;
	}
	std::istream& Field_fighter::edit(std::istream& is, int condition = 0) {
		while (1) {
			int k = 0;
			k=dialog_window(is, 1);
			switch (k) {
			case 0: return is;
			case 1:
				try {
					set_person_parameters(is,*this, 1);
				}
				catch (std::exception& ex) {
					std::cout << ex.what() << std::endl;
				}
			case 2:
				try {
					set_person_parameters(is, *this, 2);
				}
				catch (std::exception& ex) {
					std::cout << ex.what() << std::endl;
				}
			case 3:
				try {
					set_person_parameters(is, *this, 3);
				}
				catch (std::exception& ex) {
					std::cout << ex.what() << std::endl;
}
			case 4:
				try {
					set_person_parameters(is, *this, 4);
				}
				catch (std::exception& ex) {
					std::cout << ex.what() << std::endl;
				}
			case 5:
				try {
					set_person_parameters(is, *this, 5);
				}
				catch (std::exception& ex) {
					std::cout << ex.what() << std::endl;
				}
			case 6:
				int g_spec;
				std::cout << "List of specialties:" << std::endl;
				for (int i = 0; i < 8; i++) {
					std::cout << i << ". " << specs[i] << std::endl;
				}
				std::cout << "Choose one of them:";
				is >> g_spec;
				try {
					set_spec(g_spec);
				}
				catch (std::exception& ex) {
					std::cout << ex.what() << std::endl;
				}
			case 7:
				while (1) {
					int action = 0;
					std::cout << "0. Done here" << std::endl;
					std::cout << "1. Add order" << std::endl;
					std::cout << "2. Delete order" << std::endl;
					std::cout << "Do what you want: ";
					is >> action;
					switch (action) {
					case 0:
						break;
					case 1:
						std::cout << "Input order: ";
						char temp[20];
						is >> temp;
						if (is.good()) {
							try {
								add_order(temp);
							}
							catch (std::exception& ex) {
								std::cout << ex.what() << std::endl;
							}
						}
						else {
							throw std::exception("Something bad happened to the stream!");
						}
					case 2:
						int order_n;
						std::cout << "Which order?";
						is >> order_n;
						if (is.good()) {
							try {
								delete_order(order_n);
							}
							catch (std::exception& ex) {
								std::cout << ex.what() << std::endl;
							}
						}
						else {
							std::cout << "Something bad happened to the stream!" << std::endl;
						}
					default:
						std::cout << "What the hell, you didnt choose anything good!" << std::endl;
					}
				}
			default:
				std::cout << "You have inputted some strange stuff man!" << std::endl;
			}
		}

		return is;
	}
	void Staff_officer::delete_instructions(Instruction* some_instr) {
		if (some_instr != nullptr) {
			for (int i = 0; i < sizeof(some_instr) / sizeof(Instruction); i++) {
				delete[] some_instr[i].words;
			}
			delete[] some_instr;
		}
	}
	int Staff_officer::delete_instr(int order_reg) {
		for (int i = 0; i < n_instructions; i++) {
			if (instructions[i].reglament == order_reg) {
				delete[] instructions[i].words;
				for (int j = i; j < n_instructions - 1;i++) {
					instructions[i] = instructions[i + 1];
				}
				Instruction* temp = nullptr;
				temp = instructions;
				instructions = new Instruction[n_instructions - 1];
				for (int i = 0; i < n_instructions - 1; i++) {
					instructions[i] = temp[i];
				}
				delete_instructions(temp);
			}
			return 0;
		}
	}
	Staff_officer& Staff_officer::add_instruction(int g_reg=0, char* g_words = nullptr) {
		if ((g_words != nullptr) && (g_reg!=0)) {
			Instruction* temp = nullptr;
			temp = instructions;
			instructions = new Instruction[n_instructions + 1];
			for (int i = 0; i < n_instructions; i++) {
				instructions[i].words = new char[strlen(temp[i].words) + 1];
				for (int j = 0; j < strlen(temp[i].words) + 1; j++) {
					instructions[i].words[j] = temp[i].words[j];
				}
				instructions[i].reglament = temp[i].reglament;
			}
			delete_instructions(temp);
			for (int i = 0; i < strlen(g_words) + 1; i++) {
				instructions[n_instructions].words[i] = g_words[i];
				instructions[n_instructions].reglament = g_reg;
			}
			n_instructions++;
		}
		else {
			throw std::exception("Where is the instruction/reglament?");
		}
		return *this;
	}
	Staff_officer& Staff_officer::set_post(int g_post = 0) {
		if ((g_post >= 0) && (g_post <= 4)) hq_post = g_post; else throw std::exception("You have picked the wrong hq post, fool!");
		return *this;
	}
	Staff_officer::Staff_officer(char* g_name, char* g_surname, char* g_patronymic, int g_rank, int g_uniform_size, int g_hq_post = 1, char* g_words = nullptr, int g_reg = 0): person(g_name, g_surname, g_patronymic, g_rank, g_uniform_size) {
		try {
			add_instruction(g_reg, g_words);
			set_post(g_hq_post);
		}
		catch (std::exception &ex) {
			std::cout << ex.what() << std::endl;
		}
	}
	Staff_officer::Staff_officer(const Person& p, int g_hq_post = 1, char* g_words = nullptr, int g_reg = 0):person(p) {
		try {
			add_instruction(g_reg, g_words);
			set_post(g_hq_post);
		}
		catch (std::exception& ex) {
			std::cout << ex.what() << std::endl;
		}
	}
	Staff_officer::~Staff_officer() {
		delete_instructions(instructions);
	}
	std::ostream& Staff_officer::show(std::ostream& os, int condition = 0)const
	{
		if (condition == 0){
			os << "Staff officer: " << person;
		}
		 os << get_post() << std::endl;

		os << "Instructions available:" << std::endl;
		for (int i = 0; i < n_instructions; i++) {
			os << i << ". " << instructions[i].words << " " << instructions[i].reglament << std::endl;
		}
		return os << std::endl;
	}
	std::istream& Staff_officer::get(std::istream& is, int condition = 0)
	{
		if (condition == 0) {
			try {
				is >> person;
			}
			catch (std::exception& ex) {
				std::cout << ex.what() << std::endl;
				throw std::exception("Personal info couldnt be gathered!");
			}
		}

		int g_post;
		std::cout << "List of hq posts:" << std::endl;
		for (int i = 0; i < 6; i++) {
			std::cout << i << ". " << hq_posts[i] << std::endl;
		}
		std::cout << "Choose one of them:";
		is >> g_post;
		try{
			set_post(g_post);
		}
		catch (std::exception& ex) {
			throw std::exception(ex.what());
		}
		
		while (1) {
			int done = 0;
			std::cout << "Input the order and the reglament:" << std::endl;
			char temp[20];
			int g_reg=0;
			is >> temp >> g_reg;
			if (is.good()) {
				try {
					add_instruction(g_reg, temp);
				}
				catch (std::exception& ex) {
					throw std::exception(ex.what());
				}
			}
			else {
				throw std::exception("Something bad happened to the stream!");
			}
			std::cout << "Input 1 if you are done:" << std::endl;
			std::cin >> done;
			if (done == 1) break;
		}
		return is;
	}
	std::istream& Staff_officer::edit(std::istream& is, int condition = 0) {
		while (1) {
			int k = 0;
			k = dialog_window(is, 2);
			switch (k) {
			case 0: return is;
			case 1:
				try {
					set_person_parameters(is, *this, 1);
				}
				catch (std::exception& ex) {
					std::cout << ex.what() << std::endl;
				}
			case 2:
				try {
					set_person_parameters(is, *this, 2);
				}
				catch (std::exception& ex) {
					std::cout << ex.what() << std::endl;
				}
			case 3:
				try {
					set_person_parameters(is, *this, 3);
				}
				catch (std::exception& ex) {
					std::cout << ex.what() << std::endl;
				}
			case 4:
				try {
					set_person_parameters(is, *this, 4);
				}
				catch (std::exception& ex) {
					std::cout << ex.what() << std::endl;
				}
			case 5:
				try {
					set_person_parameters(is, *this, 5);
				}
				catch (std::exception& ex) {
					std::cout << ex.what() << std::endl;
				}
			case 6:
				int g_post;
				std::cout << "List of hq posts:" << std::endl;
				for (int i = 0; i < 5; i++) {
					std::cout << i << ". " << hq_posts[i] << std::endl;
				}
				std::cout << "Choose one of them:";
				is >> g_post;
				try {
					set_post(g_post);
				}
				catch (std::exception& ex) {
					std::cout << ex.what() << std::endl;
				}
			case 7:
				while (1) {
					int action = 0;
					std::cout << "0. Done here" << std::endl;
					std::cout << "1. Add instruction" << std::endl;
					std::cout << "2. Delete instruction" << std::endl;
					std::cout << "Do what you want: ";
					is >> action;
					switch (action) {
					case 0:
						break;
					case 1:
						std::cout << "Input instruction and reglament: ";
						char temp[20];
						int g_reg=0;
						is >> temp >> g_reg;
						if (is.good()) {
							try {
								add_instruction(g_reg, temp);
							}
							catch (std::exception& ex) {
								std::cout << ex.what() << std::endl;
							}
						}
						else {
							throw std::exception("Something bad happened to the stream!");
						}
					case 2:
						int order_n;
						std::cout << "Which instruction?";
						is >> order_n;
						if (is.good()) {
							try {
								delete_instr(order_n);
							}
							catch (std::exception& ex) {
								std::cout << ex.what() << std::endl;
							}
						}
						else {
							std::cout << "Something bad happened to the stream!" << std::endl;
						}
					default:
						std::cout << "What the hell, you didnt choose anything good!" << std::endl;
					}
				}
			default:
				std::cout << "You have inputted some strange stuff man!" << std::endl;
			}
		}

		return is;
	}
	std::ostream& Field_commander::show(std::ostream& os, int condition = 0)const
	{
		if (condition == 0) {
			os << "Field commander: " << person;
		}
		Field_fighter::show(os, 1);
		Staff_officer::show(os, 1);

		return os << std::endl;
	}
	std::istream& Field_commander::get(std::istream& is, int condition = 0)
	{
		if (condition == 0) {
			try {
				is >> person;
			}
			catch (std::exception& ex) {
				std::cout << ex.what() << std::endl;
				throw std::exception("Personal info couldnt be gathered!");
			}
		}

		try {
			Field_fighter::get(is, 1);
		}
		catch (std::exception& ex) {
			std::cout << ex.what() << std::endl;
			throw std::exception("Orders couldnt be gathered!");
		}
		try {
			Staff_officer::get(is, 1);
		}
		catch (std::exception& ex) {
			std::cout << ex.what() << std::endl;
			throw std::exception("Instructions couldnt be gathered!");
		}

		return is;
	}
	std::istream& Field_commander::edit(std::istream& is, int condition = 0) {
		while (1) {
			int k = 0;
			k = dialog_window(is, 3);
			switch (k) {
			case 0: return is;
			case 1:
				try {
					set_person_parameters(is, *this, 1);
				}
				catch (std::exception& ex) {
					std::cout << ex.what() << std::endl;
				}
			case 2:
				try {
					set_person_parameters(is, *this, 2);
				}
				catch (std::exception& ex) {
					std::cout << ex.what() << std::endl;
				}
			case 3:
				try {
					set_person_parameters(is, *this, 3);
				}
				catch (std::exception& ex) {
					std::cout << ex.what() << std::endl;
				}
			case 4:
				try {
					set_person_parameters(is, *this, 4);
				}
				catch (std::exception& ex) {
					std::cout << ex.what() << std::endl;
				}
			case 5:
				try {
					set_person_parameters(is, *this, 5);
				}
				catch (std::exception& ex) {
					std::cout << ex.what() << std::endl;
				}
			case 6:
				int g_spec;
				std::cout << "List of specialties:" << std::endl;
				for (int i = 0; i < 8; i++) {
					std::cout << i << ". " << specs[i] << std::endl;
				}
				std::cout << "Choose one of them:";
				is >> g_spec;
				try {
					set_spec(g_spec);
				}
				catch (std::exception& ex) {
					std::cout << ex.what() << std::endl;
				}
			case 7:
				while (1) {
					int action = 0;
					std::cout << "0. Done here" << std::endl;
					std::cout << "1. Add order" << std::endl;
					std::cout << "2. Delete order" << std::endl;
					std::cout << "Do what you want: ";
					is >> action;
					switch (action) {
					case 0:
						break;
					case 1:
						std::cout << "Input order: ";
						char temp[20];
						is >> temp;
						if (is.good()) {
							try {
								add_order(temp);
							}
							catch (std::exception& ex) {
								std::cout << ex.what() << std::endl;
							}
						}
						else {
							throw std::exception("Something bad happened to the stream!");
						}
					case 2:
						int order_n;
						std::cout << "Which order?";
						is >> order_n;
						if (is.good()) {
							try {
								delete_order(order_n);
							}
							catch (std::exception& ex) {
								std::cout << ex.what() << std::endl;
							}
						}
						else {
							std::cout << "Something bad happened to the stream!" << std::endl;
						}
					default:
						std::cout << "What the hell, you didnt choose anything good!" << std::endl;
					}
				}
			case 8:
				int g_post;
				std::cout << "List of hq posts:" << std::endl;
				for (int i = 0; i < 5; i++) {
					std::cout << i << ". " << hq_posts[i] << std::endl;
				}
				std::cout << "Choose one of them:";
				is >> g_post;
				try {
					set_post(g_post);
				}
				catch (std::exception& ex) {
					std::cout << ex.what() << std::endl;
				}
			case 9:
				while (1) {
					int action = 0;
					std::cout << "0. Done here" << std::endl;
					std::cout << "1. Add instruction" << std::endl;
					std::cout << "2. Delete instruction" << std::endl;
					std::cout << "Do what you want: ";
					is >> action;
					switch (action) {
					case 0:
						break;
					case 1:
						std::cout << "Input instruction and reglament: ";
						char temp[20];
						int g_reg = 0;
						is >> temp >> g_reg;
						if (is.good()) {
							try {
								add_instruction(g_reg, temp);
							}
							catch (std::exception& ex) {
								std::cout << ex.what() << std::endl;
							}
						}
						else {
							throw std::exception("Something bad happened to the stream!");
						}
					case 2:
						int order_n;
						std::cout << "Which instruction?";
						is >> order_n;
						if (is.good()) {
							try {
								delete_instr(order_n);
							}
							catch (std::exception& ex) {
								std::cout << ex.what() << std::endl;
							}
						}
						else {
							std::cout << "Something bad happened to the stream!" << std::endl;
						}
					default:
						std::cout << "What the hell, you didnt choose anything good!" << std::endl;
					}
				}
			default:
				std::cout << "You have inputted some strange stuff man!" << std::endl;
			}
		}
		return is;
	}
	Subdivision* Field_commander::get_subdivision() {
		return subdivision;
	}
	std::ostream& Max_commander::show(std::ostream& os, int condition = 0)const {
		if (condition == 0) {
			os << "Max commander: " << person;
		}
		Staff_officer::show(os, 1);
		return os << std::endl;
	}
	
	std::istream& Max_commander::get(std::istream& is, int condition = 0)
	{
		if (condition == 0) {
			try {
				is >> person;
			}
			catch (std::exception& ex) {
				std::cout << ex.what() << std::endl;
				throw std::exception("Personal info couldnt be gathered!");
			}
		}
		try {
			Staff_officer::get(is, 1);
		}
		catch (std::exception& ex) {
			std::cout << ex.what() << std::endl;
			throw std::exception("Instructions couldnt be gathered!");
		}
		return is;
	}
	std::istream& Max_commander::edit(std::istream& is, int condition = 0) {
		Staff_officer::edit(is);
	}
	std::ostream& operator <<(std::ostream& os, const Soldier& p)
	{
		return p.show(os);
	}
	std::istream& operator >>(std::istream& is, Soldier& p)
	{
		return p.get(is);
	}
	bool Field_fighter::am_i_sanitar() {
		if (spec == 6) return true;
		else return false;
	}
	bool Staff_officer::am_i_sanitar() {
		return false;
	}
	bool Field_commander::am_i_sanitar() {
		if (spec == 6) return true;
		else return false;
	}
	bool Max_commander::am_i_sanitar() {
		return false;
	}
	int Field_fighter::my_rank() {
		return person.get_rank();
	}
	int Field_fighter::my_spec() {
		return spec;
	}
	int Staff_officer::my_rank() {
		return person.get_rank();
	}
	int Staff_officer::my_spec() {
		return 69;
	}
	int Field_commander::my_rank() {
		return person.get_rank();
	}
	int Field_commander::my_spec() {
		return spec;
	}
	int Max_commander::my_rank() {
		return person.get_rank();
	}
	int Max_commander::my_spec() {
		return 69;
	}
	int Subdivision::set_location(int g_location) {
		if (type == 0) throw std::exception("This subdivision is HQ, cannot change location!");
		if (type == 1) {
			if ((g_location >= 0) && (g_location <= 4)) location = g_location;
			else throw std::exception("Invalid location!");
		}
		return 0;
	}
	int Subdivision::set_type(int g_type = 1) {
		if ((g_type == 0) || (g_type == 1)) { type = g_type; return 0; }
		else throw std::exception("Invalid subdivision type!");
		return 0;
	}
	Subdivision::Subdivision(Matrix::Table& g_table, int g_location = 0, int g_type = 0):table(g_table) {
		try {
			set_location(g_location);
		}
		catch (std::exception& ex) {
			std::cout << ex.what() << std::endl;
		}	
		try {
			set_type(g_type);
		}
		catch (std::exception& ex) {
			std::cout << ex.what() << std::endl;
		}
	}
	int Infield::get_soldier(int g_key) const {
		Subdivision* sub_1 = nullptr, * sub_2 = nullptr;
		sub_1 = commander_1->get_subdivision();
		sub_2 = commander_2->get_subdivision();
		Matrix::Table table_1, table_2;
		table_1 = sub_1->get_table();
		table_2 = sub_2->get_table();

		Matrix::ConstTableIt p_1, p_2;
		bool in_1 = true, in_2 = true;
		try {
			p_1=table_1.find(g_key);
		}
		catch (std::exception& ex) {
			in_1 = false;
		}
		try {
			p_1 = table_1.find(g_key);
		}
		catch (std::exception& ex) {
			in_2 = false;
		}

		if ((!in_1) && (!in_2)) {
			std::cout << "No such soldier!" << std::endl;
			return 0;
		}
		if (in_1) {
			std::cout << p_1->info << std::endl;
		}
		if (in_2) {
			std::cout << p_2->info << std::endl;
		}
		return 0;
	}
	int Infield::edit_soldier(int g_key) {
		Subdivision* sub_1 = nullptr, * sub_2 = nullptr;
		sub_1 = commander_1->get_subdivision();
		sub_2 = commander_2->get_subdivision();
		Matrix::Table table_1, table_2;
		table_1 = sub_1->get_table();
		table_2 = sub_2->get_table();

		Matrix::ConstTableIt p_1, p_2;
		bool in_1 = true, in_2 = true;
		try {
			p_1 = table_1.find(g_key);
		}
		catch (std::exception& ex) {
			in_1 = false;
		}
		try {
			p_1 = table_1.find(g_key);
		}
		catch (std::exception& ex) {
			in_2 = false;
		}

		if ((!in_1) && (!in_2)) {
			std::cout << "No such soldier!" << std::endl;
			return 0;
		}
		if (in_1) {
			p_1->info->edit(std::cin);
		}
		if (in_2) {
			p_2->info->edit(std::cin);
		}
		return 0;
	}
	int Infield::get_n(int team, int condition=0, int g_rank=69, int g_spec=69) const {
		Subdivision* sub_1 = nullptr, * sub_2 = nullptr;
		sub_1 = commander_1->get_subdivision();
		sub_2 = commander_2->get_subdivision();
		Matrix::Table table_1, table_2;
		table_1 = sub_1->get_table();
		table_2 = sub_2->get_table();

		int count=0;
		if (team == 1) {
			try {
				count=table_1.get_amount_of_fighters(condition, g_rank, g_spec);
			}
			catch (std::exception& ex) {
				std::cout << ex.what() << std::endl;
			}
			return count;
		}
		else {
			try {
				count = table_2.get_amount_of_fighters(condition, g_rank, g_spec);
			}
			catch (std::exception& ex) {
				std::cout << ex.what() << std::endl;
			}
			return count;
		}
		return count;
	}
	int Infield::delete_soldier(int g_key) {
		Subdivision* sub_1 = nullptr, * sub_2 = nullptr;
		sub_1 = commander_1->get_subdivision();
		sub_2 = commander_2->get_subdivision();
		Matrix::Table table_1, table_2;
		table_1 = sub_1->get_table();
		table_2 = sub_2->get_table();

		Matrix::ConstTableIt p_1, p_2;
		bool in_1 = true, in_2 = true;
		try {
			p_1 = table_1.find(g_key);
		}
		catch (std::exception& ex) {
			in_1 = false;
		}
		try {
			p_1 = table_1.find(g_key);
		}
		catch (std::exception& ex) {
			in_2 = false;
		}

		if ((!in_1) && (!in_2)) {
			std::cout << "No such soldier!" << std::endl;
			return 0;
		}
		if (in_1) {
			table_1.remove(g_key);
			commander_1->set_subdivision_table(table_1);
		}
		if (in_2) {
			table_2.remove(g_key);
			commander_1->set_subdivision_table(table_2);
		}
		return 0;
	}
	int Infield::swap_soldier(int g_key) {
		Subdivision* sub_1 = nullptr, * sub_2 = nullptr;
		sub_1 = commander_1->get_subdivision();
		sub_2 = commander_2->get_subdivision();
		Matrix::Table table_1, table_2;
		table_1 = sub_1->get_table();
		table_2 = sub_2->get_table();

		Matrix::ConstTableIt p_1, p_2;
		bool in_1 = true, in_2 = true;
		try {
			p_1 = table_1.find(g_key);
		}
		catch (std::exception& ex) {
			in_1 = false;
		}
		try {
			p_1 = table_1.find(g_key);
		}
		catch (std::exception& ex) {
			in_2 = false;
		}

		if ((!in_1) && (!in_2)) {
			std::cout << "No such soldier!" << std::endl;
			return 0;
		}
		if (in_1) {
			table_2.insert(p_1->key, p_1->status, p_1->info);
			table_1.remove(g_key);
			commander_1->set_subdivision_table(table_1);
			commander_2->set_subdivision_table(table_2);
		}
		if (in_2) {
			table_1.insert(p_1->key, p_1->status, p_1->info);
			table_2.remove(g_key);
			commander_1->set_subdivision_table(table_1);
			commander_2->set_subdivision_table(table_2);
		}
		return 0;
	}
}
