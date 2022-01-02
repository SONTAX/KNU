#pragma once
#include <string>
#include <vector>
#include <random>
#include <ctime>
#include <iostream>

using namespace std;

static int randomInt(int min, int max) {
	static std::random_device rd;
	static std::seed_seq seed{ rd(), static_cast<unsigned int>(time(nullptr)) };
	static std::mt19937_64 gen(seed);
	std::uniform_int_distribution<int> dist(min, max);
	return dist(gen);
}

class Technology {
private:
	std::string name;
	int type;	//increase or reduce with a chance, increase or reduce depend on amount of people in project who know it
	int influence;	//each technology increase or reduce basic project time
public:
	Technology(std::string Name, int Type) {
		name = Name;
		type = Type;
		if (type == 1) {
			influence = 0;
		}
		else if (type == 2) {
			influence = -1;
		}
		else if (type == 3) {
			influence = 1;
		}
		else {
			influence = randomInt(-2, 2);
		}
	}
	std::string get_name() {
		return this->name;
	}
	int get_type() {
		return this->type;
	}
	int get_influence() {
		return this->influence;
	}
};

class Developer {
private:
	std::string full_name;
	double efficiency; //COE from 0 to 1
	std::vector <Technology> known_technologies;
	std::string current_project = "";
public:
	Developer(std::string Full_name, double Efficiency, std::vector <Technology> Known_technologies) {
		full_name = Full_name;
		efficiency = Efficiency;
		known_technologies = Known_technologies;
		current_project = "";
	}
	std::string get_full_name() {
		return this->full_name;
	}
	double get_efficiency() {
		return this->efficiency;
	}
	std::vector <Technology> get_technologies() {
		return this->known_technologies;
	}
	std::string get_current_project() {
		return this->current_project;
	}
	void set_current_project(std::string proj) {
		current_project = proj;
	}
};

class Project {
private:
	std::string project_name;
	int complexity;
	std::vector <Technology> requiered_technologies;
	std::vector <Developer> project_developers;
	std::vector <Project> required_projects;
	int requiered_time = 0;
	int left_time = requiered_time;
	int project_type;
	int set_requiered_time(int a, int b, int c, int d, double e) {	//a = complexity, b = number of developers, c = technologies influence, d = project type, e = developers efficiency
		long basic_time = 30;
		if (d == 1) {
			double cf1 = (1 + a) * basic_time;
			double cf2 = abs(1 - b / 20) * basic_time;
			int cf3 = 5 * c;
			double temp = basic_time + cf1 + cf2 + cf3;
			temp = temp * (1 + (b / e) * (b / e) * (b / e));
			basic_time = (int)temp;
		}
		else if (d == 2) {
			double temp = ((((1 + a) * basic_time) * abs(1 - b / 20)) + (3 * c)) * (1 + randomInt(-2, 2) / 30);
			temp = temp * (1 + (b / e) * (b / e) * (b / e));
			basic_time = (int)temp;
		}
		else if (d == 3) {
			double temp = (((1 + a) * (basic_time + (3 * c))) + (basic_time * abs(1 - b / 20))) * (1 + randomInt(-3, 3) / 30);
			temp = temp * (1 + (b / e) * (b / e) * (b / e));
			basic_time = (int)temp;
		}
		return basic_time;
	}
public:
	bool is_correct = false;
	std::string get_project_name() {
		return this->project_name;
	}
	std::vector <Technology> get_requiered_technologies() {
		return this->requiered_technologies;
	}
	std::vector <Developer> get_project_developers() {
		return this->project_developers;
	}
	std::vector <Project> get_required_projects() {
		return this->required_projects;
	}
	int get_complexity() {
		return this->complexity;
	}
	int get_requiered_time() {
		return this->requiered_time;
	}
	int get_left_time() {
		return this->left_time;
	}
	int get_project_type() {
		return this->project_type;
	}
	void reduce_left_time(int r) {
		left_time = left_time - r;
	}
	void is_project_correct() {
		bool was_tech = false;
		std::vector<std::string> present_technologies;
		for (auto dev : project_developers) {
			was_tech = false;
			if (dev.get_current_project() !="") {
				is_correct = false;
				return;
			}
			for (size_t i = 0; i < dev.get_technologies().size(); i++) {
				Technology dev_tech = dev.get_technologies()[i];
				for (size_t j = 0; j < requiered_technologies.size(); j++) {
					Technology req_tech = requiered_technologies[j];
					if (req_tech.get_name() == dev_tech.get_name()) {
						was_tech = true;
						i = 9999;
						j = 9999;
					}
				}
			}
			if (was_tech == false) {
				is_correct = false;
				return;
			}
			for (auto dev_tech : dev.get_technologies()) {
				for (auto req_tech : requiered_technologies) {
					if (req_tech.get_name() == dev_tech.get_name()) {
						present_technologies.push_back(dev_tech.get_name());
					}
				}
			}
		}
		was_tech = false;
		for (auto req_tech : requiered_technologies) {
			was_tech = false;
			for (size_t i = 0; i < present_technologies.size(); i++) {
				std::string tech = present_technologies[i];
				if (tech == req_tech.get_name()) {
					was_tech = true;
					i = 9999;
				}
			}
			if (was_tech == false) {
				is_correct = false;
				return;
			}
		}
		is_correct = true;
	}
	void assign_project_name_to_developers() {
		for (size_t i = 0; i < this->project_developers.size(); i++) {
			this->project_developers[i].set_current_project(project_name);
		}
	}
	void add_developer(Developer dev1) {
		bool was_tech = false;
		for (size_t i = 0; i < dev1.get_technologies().size(); i++) {
			Technology dev_tech = dev1.get_technologies()[i];
			for (size_t j = 0; j < requiered_technologies.size(); j++) {
				Technology req_tech = requiered_technologies[j];
				if (req_tech.get_name() == dev_tech.get_name()) {
					was_tech = true;
					i = 9999;
					j = 9999;
				}
			}
		}
		if (was_tech) {
			project_developers.push_back(dev1);
		}
		else {
			cout << endl << dev1.get_full_name() << " can`t join project " << this->project_name << endl;
		}
	}
	Project(std::string Project_name, int Complexity, std::vector <Technology> Requiered_technologies,
		std::vector <Developer> Project_developers, std::vector <Project> Required_projects, int Project_type) {
		project_name = Project_name;
		complexity = Complexity;
		requiered_technologies = Requiered_technologies;
		project_developers = Project_developers;
		required_projects = Required_projects;
		project_type = Project_type;
		is_project_correct();
		if (is_correct == true) {
			int technologies_influence = 0;
			for (auto s : requiered_technologies) {
				technologies_influence += s.get_influence();
			}
			double developers_efficiency = 0;
			for (auto s : project_developers) {
				developers_efficiency += s.get_efficiency();
			}
			requiered_time = set_requiered_time(complexity, project_developers.size(), technologies_influence, project_type, developers_efficiency);
			for (auto r_p : required_projects) {
				requiered_time += r_p.get_left_time();
			}
			left_time = requiered_time;
			assign_project_name_to_developers();
		}
	}
};

class Company {
private:
public:
	Company(std::vector <Technology> All_technologies, std::vector <Developer> All_developers, std::vector <Project> All_projects) {
		all_technologies = All_technologies;
		all_developers = All_developers;
		all_projects = All_projects;
	}
	void delete_incorrect_projects() {
		std::vector <Project> temp;
		for (auto prj : all_projects) {
			if (prj.is_correct == true) {
				temp.push_back(prj);
			}
		}
		cout << (all_projects.size() - temp.size()) << " projects was deleted, because they was inncorrect" << endl;
		all_projects = temp;
	}
	int count_finished_projects() {
		int count = 0;
		for (auto prj : all_projects) {
			if (prj.get_left_time()<=0) {
				count++;
			}
		}
		return count;
	}
	std::vector<Project> unfinished_projects() {
		std::vector <Project> temp;
		for (auto prj : all_projects) {
			if (prj.get_left_time() > 0) {
				temp.push_back(prj);
			}
		}
		return temp;
	}
	std::vector <Technology> all_technologies;
	std::vector <Developer> all_developers;
	std::vector <Project> all_projects;
};