#include "Date.h"
#include "SparseList.h"
#include "Tree.h"
#include "DateOperations.h"
#include "doctest.h"

TEST_CASE("date and time") {
	Date dem = { Year(1944),Month(6),Day(6),Hour(6),Minute(30),Second(0) };
	Date dem1 = { Year(2020),Month(10),Day(1),Hour(14),Minute(14),Second(14) };
	DateOperations demo = { dem, dem1 };
	CHECK(dem.Print() == "1944.6.6 6:30:0\n");
	CHECK(dem1.Print() == "2020.10.1 14:14:14\n");
	CHECK(dem.DayOfTheWeek() == "Tuesday\n");
	CHECK(dem1.DayOfTheWeek() == "Thursday\n");
	CHECK(demo.DateDifference() == "Difference is: 27876 days and 27854 seconds\n");
	demo.Arithmetic(0, 1);
	CHECK(demo.Print(1) == "1868.2.8 22:45:46\n");
	demo.Arithmetic(1, 0);
	CHECK(demo.Print(0) == "2173.5.25 5:42:42\n");
	CHECK(demo.DayOfTheWeek(1) == "Saturday\n");
	CHECK(demo.DayOfTheWeek(0) == "Tuesday\n");
	Date dem2 = { Year(2021),Month(3),Day(5),Hour(23),Minute(0),Second(0) };
	Date dem3 = { Year(2021),Month(3),Day(5),Hour(23),Minute(32),Second(14) };
	DateOperations demo1 = { dem2, dem3 };
	CHECK(demo1.DateDifference() == "Difference is: 0 days and 1934 seconds\n");
}

TEST_CASE("sparse list") {
	SUBCASE("int") {
		SparseList<int> dem;
		dem.Add(-8);
		dem.Add(0);
		dem.Add(0);
		dem.Add(8);
		dem.Add(3);
		dem.Add(0);
		dem.Add(0);
		dem.Add(0);
		dem.Add(0);
		dem.Add(2);
		dem.Add(0);
		dem.Add(14);
		dem.Add(12);
		dem.Add(9);
		dem.Add(0);
		dem.Add(0);
		dem.Add(0);
		dem.Add(1);
		dem.Add(1);
		CHECK(dem.PrintAll() == "-8 0 0 8 3 0 0 0 0 2 0 14 12 9 0 0 0 1 1 ");
		CHECK(dem.GetValue(11) == 14);
		CHECK(dem.GetValue(12) == 12);
		CHECK(dem.GetIndex(0) == 1);
		CHECK(dem.GetIndex(1) == 17);
		CHECK(dem.list_size == 19);
		dem.Add(-8);
		CHECK(dem.list_size == 20);
		CHECK(dem.GetIndex(-8) == 0);
		dem.DeleteList();
	}
	SUBCASE("double") {
		SparseList<double> dem;
		dem.Add(24.5);
		dem.Add(-12.3);
		dem.Add(4.01);
		dem.Add(0);
		dem.Add(0);
		dem.Add(0);
		dem.Add(0);
		dem.Add(0);
		dem.Add(-99.99);
		dem.Add(0);
		dem.Add(2.28);
		dem.Add(0);
		dem.Add(0);
		dem.Add(3.22);
		dem.Add(9);
		dem.Add(0);
		dem.Add(0);
		dem.Add(0);
		dem.Add(0);
		dem.Add(10.01);
		CHECK(dem.list_size == 20);
		CHECK(dem.PrintAll() == "24.500000 -12.300000 4.010000 0 0 0 0 0 -99.990000 0 2.280000 0 0 3.220000 9.000000 0 0 0 0 10.010000 ");
		CHECK(dem.GetIndex(4.01) == 2);
		CHECK(dem.GetIndex(0) == 3);
		CHECK(dem.GetValue(10) == 2.28);
		dem.DeleteList();
	}
}

TEST_CASE("tree") {
	Tree<int> dem;
	dem.root = dem.BuildRandomBST(0);
	dem.SearchInsert(dem.root, -8);
	dem.PrintTreeInOrder(dem.root);
	CHECK(dem.Output() == "-8 6 ");
	dem.SearchInsert(dem.root, 9);
	dem.PrintTreeAsTree(dem.root, 0);
	CHECK( dem.Output() == "   9\n6\n   -8\n");
	dem.SearchInsert(dem.root, 9);
	dem.SearchInsert(dem.root, 3);
	dem.SearchInsert(dem.root, 21);
	dem.SearchInsert(dem.root, 10);
	dem.SearchInsert(dem.root, -11);
	dem.SearchInsert(dem.root, -10);
	dem.PrintTreeInOrder(dem.root);
	CHECK(dem.Output() == "-11 -10 -8 3 6 9 10 21 ");
	dem.DeleteByValue(-11, dem.root);
	dem.PrintTreeInOrder(dem.root);
	CHECK(dem.Output() == "-8 3 6 9 10 21 ");
	dem.Find(21, dem.root);
	dem.DeleteByAdress(dem.root, dem.found_node);
	dem.PrintTreeInOrder(dem.root);
	CHECK(dem.Output() == "-8 3 6 9 ");
}