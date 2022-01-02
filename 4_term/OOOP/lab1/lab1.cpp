#include "Date.h"
#include "SparseList.h"
#include "Matrix.h"
#include "Tree.h"
#include "Menu.h"
#include "DateOperations.h"

namespace test {
	int main_test(int argc, char* argv[]);
}

using namespace std;

int main(int argc, char* argv[]) {

	test::main_test(argc, argv);

	system("pause");
	int enter;
	srand((unsigned)time(0));
	do {
		system("cls");
		enter = enter_menu();
		switch (enter) {
		case 0: {
			int demo_menu;
			do {
				system("cls");
				demo_menu = menu();
				switch (demo_menu) {
				case 0: {
					Date dem = { Year(1944),Month(6),Day(6),Hour(6),Minute(30),Second(0) };
					Date dem1 = { Year(2020),Month(10),Day(1),Hour(14),Minute(14),Second(14) };
					DateOperations demo = { dem, dem1 };
					cout << dem.Print();
					cout << dem.DayOfTheWeek();
					cout << dem1.Print();
					cout << dem1.DayOfTheWeek();
					cout << demo.DateDifference();
					cout << endl << "##Take away difference beetwen default dates from first date##" << endl << endl;
					demo.Arithmetic(0, 1);
					cout << demo.Print(1);
					cout << endl << "##Add difference beetwen default dates to second date##" << endl << endl;
					demo.Arithmetic(1, 0);
					cout << demo.Print(0);
					system("pause");
					break;
				}
				case 1: {
					Matrix dem;
					cout << "#Set random matrix 15x15#" << endl;
					dem.GetRandomMatrix(15);
					cout << dem.PrintMatrix();
					cout << endl << "#Get value in 7 row and 3 column#" << endl;
					dem.GetByIndex(7, 3);
					cout << endl << "#Get row and column of the first 0#" << endl;
					dem.GetByValue(0);
					cout << endl << "#Summation with random matrix#" << endl;
					dem.Sum();
					cout << endl << "#Multiplication by random matrix#" << endl;
					dem.MultiplicationByMatrix();
					cout << endl << "#Multiplication by random vector#" << endl;
					dem.MultiplicationByVector();
					cout << endl << "#Matrix transponation#" << endl;
					dem.Transponation();
					system("pause");
					break;
				}
				case 2: {
					cout << "###Int demo###" << endl;
					SparseList<int> dem;
					dem.GetRandomList(25);
					cout << dem.PrintAll();
					cout << endl << "#Print value with index 13#" << endl;
					int value = dem.GetValue(13);
					if (value == -1) {
						cout << "This index is larger then list max index: " << dem.list_size - 1 << "!" << endl;
					}
					else {
						cout << "Value for this index is: " << value << endl;
					}					
					cout << endl << "#Print index for first 2#" << endl;					
					int index = dem.GetIndex(2);
					if (index == -1) {
						cout << "There is no index for such value!" << endl;
					}
					else {
						cout << "Index for this value is: " << index << endl;
					}
					cout << endl << "#Search for first value: mod(value + index, 3) = 0 and value!=0 #" << endl;
					Node<int>* cur = dem.pbeg;
					bool is = false;
					while (cur) {
						if ((cur->index + cur->value) % 3 == 0) {
							is = true;
							cout << "[ " << cur->index << " ] " << cur->value << endl;
							break;
						}
						cur = cur->next;
					}
					if (!is) {
						cout << "No values to such condition" << endl;
					}
					cout << endl;
					dem.DeleteList();
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
					dem.Add(0);
					dem.Add(1);
					cout << dem.PrintAll();
					cout << endl << "#Search for first value: mod(value + index, 3) = 0 and value!=0 #" << endl;
					cur = dem.pbeg;
					is = false;
					while (cur) {
						if ((cur->index + cur->value) % 3 == 0) {
							is = true;
							cout << "[ " << cur->index << " ] " << cur->value << endl;
							break;
						}
						cur = cur->next;
					}
					if (!is) {
						cout << "No values to such condition" << endl;
					}
					cout << endl << endl << "###Double demo###" << endl;
					SparseList<double> dem1;
					dem1.DeleteList();
					dem1.Add(24.5);
					dem1.Add(-12.3);
					dem1.Add(4.01);
					dem1.Add(0);
					dem1.Add(0);
					dem1.Add(0);
					dem1.Add(0);
					dem1.Add(0);
					dem1.Add(-99.99);
					dem1.Add(0);
					dem1.Add(2.28);
					dem1.Add(0);
					dem1.Add(0);
					dem1.Add(3.22);
					dem1.Add(9);
					dem1.Add(0);
					dem1.Add(0);
					dem1.Add(0);
					dem1.Add(0);
					dem1.Add(10.01);
					cout << dem1.PrintAll();
					cout << endl << "#Print value with index 12#" << endl;
					value = dem1.GetValue(12);
					if (value == -1) {
						cout << "This index is larger then list max index: " << dem1.list_size - 1 << "!" << endl;
					}
					else {
						cout << "Value for this index is: " << value << endl;
					}
					cout << endl << "#Print index for first 0#" << endl;
					index = dem1.GetIndex(0);
					if (index == -1) {
						cout << "There is no index for such value!" << endl;
					}
					else {
						cout << "Index for this value is: " << index << endl;
					}
					system("pause");
					break;
				}
				case 3: {
					Tree<int> dem;
					cout << "Binary tree: " << endl;
					dem.root = dem.BuildRandomTree(5);
					cout << "\tTree form: " << endl;
					dem.PrintTreeAsTree(dem.root, 0);
					cout << dem.Output();
					cout << "\tInOrder travestal form: " << endl;
					dem.PrintTreeInOrder(dem.root);
					cout << dem.Output();
					cout << endl << "#Find and delete by parent node last node with value 5#" << endl;
					dem.Find(5, dem.root);
					dem.root = dem.DeleteByAdress(dem.root, dem.found_node);
					dem.PrintTreeAsTree(dem.root, 0);
					cout << dem.Output();
					cout << endl << "#Delete all nodes with value 6#" << endl;
					dem.root = dem.DeleteByValue(6, dem.root);
					dem.PrintTreeAsTree(dem.root, 0);
					cout << dem.Output();
					cout << endl << "#Addition(BST-type) of 3, 5, 8, -4, 78 to the tree#";
					dem.SearchInsert(dem.root, 3);
					dem.SearchInsert(dem.root, 5);
					dem.SearchInsert(dem.root, 8);
					dem.SearchInsert(dem.root, -4);
					dem.SearchInsert(dem.root, 78);
					cout << "#Tree after all operations#" << endl;
					dem.PrintTreeInOrder(dem.root);
					cout << dem.Output();
					cout << endl;
					dem.PrintTreeAsTree(dem.root, 0);
					cout << dem.Output();
					cout << endl << endl;
					cout << "BST: " << endl;
					dem.root = dem.BuildRandomBST(20);
					cout << "\tTree form: " << endl;
					dem.PrintTreeAsTree(dem.root, 0);
					cout << dem.Output();
					cout << "\tInOrder travestal form: " << endl;
					dem.PrintTreeInOrder(dem.root);
					cout << dem.Output();
					cout << endl << "#Delete node with value 33#" << endl;
					dem.root = dem.DeleteByValue(33, dem.root);
					dem.PrintTreeAsTree(dem.root, 0);
					cout << dem.Output();
					cout << endl << "#Addition(BST-type) of 3, 5, 8, -4, 78 to the tree#" << endl;
					dem.SearchInsert(dem.root, 3);
					dem.SearchInsert(dem.root, 5);
					dem.SearchInsert(dem.root, 8);
					dem.SearchInsert(dem.root, -4);
					dem.SearchInsert(dem.root, 78);
					cout << "#Tree after all operations#" << endl;
					dem.PrintTreeInOrder(dem.root);
					cout << dem.Output();
					cout << endl;
					dem.PrintTreeAsTree(dem.root, 0);
					cout << dem.Output();
					system("pause");
					break;
				}
				}
			} while (demo_menu != 4);
			break;
		}
		case 1: {
			int theme;
			do {
				system("cls");
				theme = menu();
				switch (theme) {
				case 0: {
					int date;
					int number;
					Date date1;
					Date date2;
					cout << "Input first full date: " << endl;
					date1.Fill();
					cout << "Input second full date: " << endl;
					date2.Fill();
					DateOperations data = { date1, date2 };
					do {
						system("cls");
						date = date_menu();
						switch (date) {
						case 0: {
							system("cls");
							number = date_choice_menu();
							switch (number) {
							case 0: {
								data.ChangeDate(0);
								break;
							}
							case 1: {
								data.ChangeDate(0);
								break;
							}
							}
							system("pause");
							break;
						}
						case 1: {
							system("cls");
							int dif = difference_menu();
							switch (dif) {
							case 0: {
								number = date_choice_menu();
								switch (number) {
								case 0: {
									data.Arithmetic(0, 1);
									cout << "New first date is: " << data.Print(1);
									break;
								}
								case 1: {
									data.Arithmetic(0, 0);
									cout << "New second date is: " << data.Print(0);
									break;
								}
								}
								break;
							}
							case 1: {
								number = date_choice_menu();
								switch (number) {
								case 0: {
									data.Arithmetic(1, 1);
									cout << "New first date is: " << data.Print(1);
									break;
								}
								case 1: {
									data.Arithmetic(1, 0);
									cout << "New second date is: " << data.Print(0);
									break;
								}
								}
								break;
							}
							}
							system("pause");
							break;
						}
						case 2: {
							system("cls");
							number = date_choice_menu();
							switch (number) {
							case 0: {
								data.DayOfTheWeek(1);
								break;
							}
							case 1: {
								data.DayOfTheWeek(0);
								break;
							}
							}
							system("pause");
							break;
						}
						case 3: {
							system("cls");
							number = date_choice_menu();
							switch (number) {
							case 0: {
								cout << data.Print(1);
								break;
							}
							case 1: {
								cout << data.Print(0);
								break;
							}
							}
							system("pause");
							break;
						}
						case 4: {
							system("cls");
							cout << data.DateDifference();
							system("pause");
							break;
						}
						}
					} while (date != 5);
					break;
				}
				case 1: {
					int answer;
					Matrix matrix;
					matrix.GetRandomMatrix(10);
					do {
						system("cls");
						answer = matrix_menu();
						switch (answer) {
						case 0: {
							int n;
							cout << "Input matrix dimension: ";
							cin >> n;
							matrix.GetRandomMatrix(n);
							break;
						}
						case 1: {
							int n;
							cout << "Input matrix dimension: ";
							cin >> n;
							matrix.GetMatrix(n);
							break;
						}
						case 2: {
							cout << matrix.PrintMatrix();
							system("pause");
							break;
						}
						case 3: {
							matrix.Sum();
							system("pause");
							break;
						}
						case 4: {
							matrix.MultiplicationByMatrix();
							system("pause");
							break;
						}
						case 5: {
							matrix.MultiplicationByVector();
							system("pause");
							break;
						}
						case 6: {
							matrix.Transponation();
							system("pause");
							break;
						}
						case 7: {
							int x, y;
							cout << "Input row and column to search value: ";
							cin >> x >> y;
							matrix.GetByIndex(x, y);
							system("pause");
							break;
						}
						case 8: {
							int n;
							cout << "Input value (0-4) to search indexes: ";
							cin >> n;
							matrix.GetByValue(n);
							system("pause");
							break;
						}
						}
					} while (answer != 9);
					break;
				}
				case 2: {
					int list;
					SparseList<int> sparse_list;
					sparse_list.GetRandomList(25);
					do {
						system("cls");
						list = list_menu();
						switch (list) {
						case 0: {
							int val;
							cout << "Input value to add: ";
							cin >> val;
							sparse_list.Add(val);
							break;
						}
						case 1: {
							int n;
							cout << "Input list lenth: ";
							cin >> n;
							sparse_list.GetList(n);
							break;
						}
						case 2: {
							int n;
							cout << "Input list lenth: ";
							cin >> n;
							sparse_list.GetRandomList(n);
							break;
						}
						case 3: {
							cout << sparse_list.PrintAll();
							system("pause");
							break;
						}
						case 4: {
							size_t n;
							cout << "Input index to search: ";
							cin >> n;
							int value = sparse_list.GetValue(n);
							if (value == -1) {
								cout << "This index is larger then list max index: " << sparse_list.list_size - 1 << "!" << endl;
							}
							else {
								cout << "Value for this index is: " << value << endl;
							}
							system("pause");
							break;
						}
						case 5: {
							int n;
							cout << "Input value to search: ";
							cin >> n;
							int index = sparse_list.GetIndex(n);
							if (index == -1) {
								cout << "There is no index for such value!" << endl;
							}
							else {
								cout << "Index for this value is: " << index << endl;
							}
							system("pause");
							break;
						}
						}
					} while (list != 6);
					break;
				}
				case 3: {
					int tree;
					Tree<int> bin_tree;
					bin_tree.root = bin_tree.BuildRandomTree(5);
					do {
						system("cls");
						tree = binary_tree_menu();
						switch (tree) {
						case 0: {
							bin_tree.PrintTreeInOrder(bin_tree.root);
							cout << bin_tree.Output();
							system("pause");
							break;
						}
						case 1: {
							bin_tree.PrintTreeAsTree(bin_tree.root, 0);
							cout << bin_tree.Output();
							system("pause");
							break;
						}
						case 2: {
							size_t height;
							cout << "Input tree height: ";
							cin >> height;
							cout << "Input " << pow(2, height) - 1 << " values for this tree: ";
							bin_tree.root = bin_tree.BuildTree(height);
							break;
						}
						case 3: {
							size_t height;
							cout << "Input tree height: ";
							cin >> height;
							bin_tree.root = bin_tree.BuildRandomTree(height);
							break;
						}
						case 4: {
							size_t count;
							cout << "Input number of values: ";
							cin >> count;
							cout << "Input " << count << " values for this tree: ";
							bin_tree.root = bin_tree.BuildBST(count);
							break;
						}
						case 5: {
							size_t count;
							cout << "Input number of values: ";
							cin >> count;
							bin_tree.root = bin_tree.BuildRandomBST(count);
							break;
						}
						case 6: {
							int val;
							cout << "Input value to add: ";
							cin >> val;
							bin_tree.SearchInsert(bin_tree.root, val);
							break;
						}
						case 7: {
							int val;
							cout << "Input value to delete node: ";
							cin >> val;
							bin_tree.root = bin_tree.DeleteByValue(val, bin_tree.root);
							break;
						}
						case 8: {
							bin_tree.root = bin_tree.DeleteByAdress(bin_tree.root, bin_tree.found_node);
							break;
						}
						case 9: {
							int val;
							cout << "Input value to search: ";
							cin >> val;
							bin_tree.found_node = nullptr;
							bin_tree.Find(val, bin_tree.root);
							if (bin_tree.found_node) {
								cout << "Adress of found node: " << bin_tree.found_node << endl;
							}
							else {
								cout << "Any node with such value don`t exist!" << endl;
							}
							system("pause");
							break;
						}
						}
					} while (tree != 10);
				}
				}
			} while (theme != 4);
			break;
		}
		}
	} while (enter != 2);
	return 0;
}