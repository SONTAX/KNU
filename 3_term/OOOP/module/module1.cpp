#include "task1.h"
#include "task2.h"
#include "task3.h"

void demo_task1() {
	cout << "###DEMO FOR TASK 1###" << endl << endl;

	Technology t1 = { "t1",1 };
	Technology t2 = { "t2",2 };
	Technology t3 = { "t3",3 };
	Technology t4 = { "t4",3 };
	Technology t5 = { "t5",2 };
	Technology t6 = { "t6",1 };

	Developer d1{ "Petro Petrenko",0.7,{ t1,t3 } };
	Developer d2{ "Tom Thomas",0.9999999,{ t1,t2,t3,t4,t5,t6 } };
	Developer d3{ "Ivan Ivanenko",0.896,{ t2,t5 } };
	Developer d4{ "Sim Simon",0.896,{ t1,t3,t5 } };

	Project p1{ "p1",1,{t1,t2},{d1,d3},{},1 };
	Project p2{ "p2",5,{t1,t2,t3},{d2},{},2 };
	Project p3{ "p3",1,{t5},{d4},{p2},3 };
	Project p4{ "p4",4,{t1,t2},{d1},{},3 };
	Project p5{ "p5",5,{ t1,t2,t3,t4,t5,t6 },{d1,d3},{},2 };
	Project p6{ "p6",3,{t1,t2},{d4},{},1 };

	cout << "Was created company with 6 technologies, 4 developers and 6 projects" << endl;
	Company top{ {t1,t2,t3,t4,t5,t6},{d1,d2,d3,d4},{p1,p2,p3,p4,p5,p6 } };
	top.delete_incorrect_projects();
	cout << "There are 3 projects left one of each depends on another" << endl;
	top.all_projects[0].reduce_left_time(350);
	top.all_projects[1].reduce_left_time(350);
	top.all_projects[2].reduce_left_time(350);
	cout << "After time(350) there are " << top.count_finished_projects() << " finished projects" << endl;
	top.all_projects[0].reduce_left_time(-350);
	top.all_projects[1].reduce_left_time(-350);
	top.all_projects[2].reduce_left_time(-350);
	int i = 0;
	while (top.count_finished_projects()!=2) {
		top.all_projects[0].reduce_left_time(1);
		top.all_projects[1].reduce_left_time(1);
		top.all_projects[2].reduce_left_time(1);
		i++;
	}
	cout << "2 projects are finished after time(" << i << ") from the start" << endl << endl;
	cout << "Unfiniched projects:" << endl;
	for (auto left : top.unfinished_projects()) {
		cout << left.get_project_name() << " time to finish it " << left.get_left_time() << endl;
	}
	cout << endl;
}

void demo_task2() {
	cout << endl << endl << "###DEMO FOR TASK 2###" << endl << endl;
	List demo;
	cout << "f(8): ";
	demo.func(8);
	demo.print();
	cout << endl << "f(-25): ";
	demo.func(-25);
	demo.print();
	cout << endl << "f(10f4f12saf133): ";
	string sg = "10f4f12saf133";
	demo.func(sg);
	demo.print();
	std::pair<double, int> pr = std::make_pair(-3.67, -8);
	cout << endl << "f(-3.67,-8): ";
	demo.func(pr);
	demo.print();
	cout << endl << "vector<string> c = { '2' }\nf(c): ";
	vector<string> c = { "2" };
	demo.func(c);
	demo.print();
}

void demo_task3() {
	cout << endl << endl << "###DEMO FOR TASK 3###" << endl << endl;
	cout << "Value S in the start: " << S << endl << endl;
	{
		auto one = make_shared<Alpha>();
		auto two = make_shared<Beta>();
		auto three = make_shared<Gamma>();
		auto four = make_shared<Base>();
	}
	cout << endl;
	cout << "Value S in the end: " << S << endl;
}
int main() {

	demo_task1();
	demo_task2();
	demo_task3();

	return 0;
}
