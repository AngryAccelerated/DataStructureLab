#include "application.h"




void Application::executeListTestCase()
{
	
	std::cout << "===>testing creating list<===" << std::endl;
	LinkedList linkedlistA{2, 3, 4, 5};
	LinkedList linkedlistB;
	for (int i = 1; i <= 16; i += 1)
		linkedlistA.append(i);
	for (int i = 1; i <= 16; i += 1)
		linkedlistB.append(i);


	std::cout << "===>testing append<===" << std::endl;

	linkedlistA.append(233);
	linkedlistB.append(456);

	std::cout << "===>testing insert forward<===" << std::endl;

	linkedlistA.insert(1, 789, InsertDirection::Forward);
	linkedlistB.insert(2, 1024, InsertDirection::Forward);


	std::cout << "===>testing insert backward<===" << std::endl;

	linkedlistA.insert(1, 111, InsertDirection::Backward);
	linkedlistB.insert(2, 333, InsertDirection::Backward);
	std::cout << linkedlistA << std::endl;


	std::cout << "===>testing contains<===" << std::endl;
	std::cout << "List A contain 1 :" << linkedlistA.contains(1) << std::endl;
	std::cout << "List A contain 258 :" << linkedlistA.contains(258) << std::endl;
	std::cout << "List B contain 2 :" << linkedlistB.contains(2) << std::endl;
	std::cout << "List B contain 369 :" << linkedlistB.contains(369) << std::endl;


	std::cout << "===>testing remove<===" << std::endl;
	std::cout << "remove 1 from A: " << linkedlistA.remove(1) << std::endl;
	std::cout << "remove 147 from A: " << linkedlistA.remove(147) << std::endl;
	std::cout << "remove 2 from B: " << linkedlistB.remove(2) << std::endl;
	std::cout << "remove 1256 from B: " << linkedlistB.remove(1256) << std::endl;

	std::cout << "===>testing circularize<===" << std::endl;
	std::cout << "circularize list A: " << linkedlistA.circularize() << std::endl;
	std::cout << "circularize list B: " << linkedlistB.circularize() << std::endl;

	std::cout << "===>testing decircularize<===" << std::endl;
	std::cout << "decircularize list A: " << linkedlistA.decircularize() << std::endl;
	std::cout << "decircularize list B: " << linkedlistB.decircularize() << std::endl;

	std::cout << "===>testing append initialized_list count<===" << std::endl;
	linkedlistA.append({7, 8, 9});
	std::cout << "===>testing insert initialized_list count<===" << std::endl;
	linkedlistA.insert(2, {55, 35, 98}, InsertDirection::Backward);
	linkedlistA.insert(3, {256, 789, 1024}, InsertDirection::Forward);
	std::cout << "===>testing count<===" << std::endl;
	std::cout << "count of A: " << linkedlistA.count() << std::endl;
	std::cout << "count of B: " << linkedlistB.count() << std::endl;
}

void Application::executeArrayTestCase()
{
	
	std::cout << "===>testing creating array<===" << std::endl;
	DynamicArray arrayA(8, 1);
	DynamicArray arrayB(8, 1);
	for (int i = 1; i <= 16; i += 1)
		arrayA.append(i);
	for (int i = 1; i <= 16; i += 2)
		arrayB.append(i);


	std::cout << "===>testing array insert forward<===" << std::endl;

	arrayA.insert(2, 345, InsertDirection::Forward);
	arrayA.insert(3, 7641, InsertDirection::Forward);
	arrayB.insert(6, 4899, InsertDirection::Forward);
	arrayB.insert(7, 68, InsertDirection::Forward);


	std::cout << "===>testing array insert backward<===" << std::endl;

	arrayA.insert(1, 159, InsertDirection::Backward);
	arrayA.insert(3, 954, InsertDirection::Backward);
	arrayB.insert(5, 353, InsertDirection::Backward);
	arrayB.insert(7, 154, InsertDirection::Backward);


	std::cout << "===>testing array contains<===" << std::endl;
	std::cout << "Array A contains 1: " << arrayA.contains(1) << std::endl;
	std::cout << "Array A contains 233: " << arrayA.contains(233) << std::endl;
	std::cout << "Array B contains 2: " << arrayB.contains(2) << std::endl;
	std::cout << "Array B contains 1024: " << arrayB.contains(1024) << std::endl;

	std::cout << "===>testing array remove<===" << std::endl;

	std::cout << "Array A removes 1: " << arrayA.remove(1) << std::endl;
	std::cout << "Array A removes 233: " << arrayA.remove(233) << std::endl;
	std::cout << "Array B removes 6: " << arrayB.remove(6) << std::endl;
	std::cout << "Array B removes 1024: " << arrayB.remove(6) << std::endl;


	std::cout << "===>Array A and B removes all of its data<===" << std::endl;
	int index = 0;
	int c = arrayA.count();
	for (int index = 0; index < c; index++)
		arrayA.remove(arrayA[0]);
	c = arrayB.count();
	for (int index = 0; index < c; index++)
		arrayB.remove(arrayB[0]);

	std::cout << "===>Array A and B squeeze<===" << std::endl;
	arrayA.squeeze();
	arrayB.squeeze();
	std::cout << "===>testing appending again to A<===" << std::endl;
	for (int i = 1; i <= 8; i += 1)
		arrayA.append(i);



	std::cout << "===>testing setArray again to A<===" << std::endl;
	int array[7] = {1, 3, 5, 7, 9, 10, 11};
	arrayA.setArray({1, 3, 5, 7, 9, 10, 11});

	std::cout << "===>testing appending array(initializer_list) to A<===" << std::endl;
	arrayA.append({13, 15, 17});

	std::cout << "===>testing inserting array(initializer_list) to A<===" << std::endl;
	arrayA.insert(1, {13, 15, 17}, InsertDirection::Backward);
	std::cout << "===>testing array count<===" << std::endl;
	std::cout << "Array A count: " << arrayA.count() << std::endl;
	
	std::cout << "Array B count: " << arrayB.count() << std::endl;
	std::cout << arrayA << std::endl;
}

void Application::executeSetCase()
{


	
	std::cout << "===>testing set creation<====" << std::endl;
	Set<> setA{7, 3, 9, 1, 11, 5};
	Set<> setB{2, 3, 4, 5, 6, 8, 10, 11 };
	
	std::cout << "set A: " << setA << std::endl;
	std::cout << "set B: " << setB << std::endl;
	std::cout << "===>testing set A sort<====" << std::endl;
	setA.sort();
	std::cout << "set A: " << setA << std::endl;

	std::cout << "===>testing set A unite set B <====" << std::endl;
	setA.unite(setB);
	std::cout << "set A: " << setA << std::endl;
	
	std::cout << "===>testing set A intersect set B <====" << std::endl;
	setA.intersect(setB);
	std::cout << "set A: " << setA << std::endl;

	std::cout << "===>testing set A subtract set B <====" << std::endl;
	setA.subtract(setB);
	std::cout << "set A: " << setA << std::endl;

	Set<> result;
	std::cout << "===>testing intersection <====" << std::endl;
	Set<>::Intersection({2,3,5,6,7,8,1,0,99,14}, {5,8,9,7,1,11,567,48}, result);
	std::cout << "result: " << result << std::endl;
	result.removeAll();
	
	std::cout << "===>testing difference <====" << std::endl;
	Set<>::Difference({ 132,456,724,21154,247 }, { 724,247,456,111,6579,49 }, result);
	std::cout << "result: " << result << std::endl;
	result.removeAll();
	
	std::cout << "===>testing union <====" << std::endl;
	Set<>::Union({ 2,3,5,6,7,8,1,0,99,14 }, { 5,8,9,7,1,11,567,48 }, result);
	std::cout << "result: " << result << std::endl;
	result.removeAll();
	
}

int Application::exec()
{
	//executeListTestCase();
	//executeArrayTestCase();
	//executeSetCase();
	printHelp();
	Set<> setA { 1, 3, 5, 7, 9, 10, 11 };
	Set<> setB { 2, 3, 4, 5, 6, 8, 10, 11 };
	while (true)
	{
		std::cout << "Enter Command ===>";
		std::string command;
		std::getline(std::cin, command);
		std::string op = command.substr(0, 2);
		
		if (op == "Q")
			return m_result;
		if (op == "IA")
		{
			if (command.size() < 4)
			{
				std::cout << "Please input element to be inserted." << std::endl;
			}
			else
			{
				setA.add(std::stoi(command.substr(3, command.size() - 2)));
				std::cout << "set A: " << setA << std::endl;
			}
		}
		else if (op == "DA")
		{
			if (command.size() < 4)
			{
				std::cout << "Please input element to be removed." << std::endl;
			}
			else
			{
				setA.remove(std::stoi(command.substr(3, command.size() - 2)));
				std::cout << "set A: " << setA << std::endl;
			}
		}
		else if (op == "IB")
		{
			if (command.size() < 4)
			{
				std::cout << "Please input element to be inserted." << std::endl;
			}
			else
			{
				setB.add(std::stoi(command.substr(3, command.size() - 2)));
				std::cout << "set B: " << setB << std::endl;
			}
		}
		else if (op == "DB")
		{
			if (command.size() < 4)
			{
				std::cout << "Please input element to be removed." << std::endl;
			}
			else
			{
				setB.remove(std::stoi(command.substr(3, command.size() - 2)));
				std::cout << "set B: " << setA << std::endl;
			}
		}
		else if (op == "OU")
		{
			Set<> result;
			Set<>::Union(setA, setB, result);
			std::cout << "result: " << result << std::endl;
		}
		else if (op == "OI")
		{
			Set<> result;
			Set<>::Intersection(setA, setB, result);
			std::cout << "result: " << result << std::endl;
		}
		else if (op == "OD")
		{
			Set<> result;
			Set<>::Difference(setA, setB, result);
			std::cout << "result: " << result << std::endl;
		}
		else
		{
			std::cout << ">>>>Command does not exist." << std::endl;
		}
	}
}
void Application::printHelp()
{
	std::cout << "\t\t\tMenu\t\t\t" << std::endl;
	std::cout << "IA : Insert into Set A\t\tDA : Delete from Set A " << std::endl;
	std::cout << "IB : Insert into Set B\t\tDB : Delete from Set B" << std::endl;
	std::cout << "OU : Union\t\t\tOI : Intersection" << std::endl;
	std::cout << "OD : Difference\t\t\tQ : Quit" << std::endl;
}
