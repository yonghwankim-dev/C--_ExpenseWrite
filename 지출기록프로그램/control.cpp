#include "control.h"
#include "AccountException.h"
#include "expense_info.h"
#include "stream.h"

control::control() : num(0)
{

}

void control::write(stream * io)
{
	expense_info exin;	// 지출 정보가 들어있는 객체

	exin.expense_input();	// 지출정보를 입력받아 멤버에 저장
	

	try {
		string temp = exin.getDate().substr(5, 2);
		if (temp < "01" || temp >"12")
			throw DateException(exin.getDate());

		temp = exin.getDate().substr(8, 2);
		if (temp < "01" || temp>"31")
			throw DateException(exin.getDate());
		if (exin.getMoney() < 0)
			throw MinusException(exin.getMoney());
		if (exin.getCategory() < 1 || exin.getCategory()>12)
			throw CategoryException(exin.getCategory());

		io->input(exin);
	}
	catch (ExpenseException &expn)
	{
		expn.ShowExceptionReason();
	}
	
}

void control::ShowAllExpense(stream * io)
{
	io->print();
	io->printSum();
}

void control::ShowMoneySum(stream * io)
{
	io->printSum();
}

void control::ShowDateSearch(string year)
{
	string temp;
	int sum = 0;
	for (int i = 0;i < num;i++)
	{
		temp = arr[i]->GetDate();
		if (temp.substr(0, 4) == year)
		{
			arr[i]->ShowExpenseInfo();
			sum += arr[i]->GetMoney();
		}
	}
	cout << "금액 총합 : " << sum << endl;
}

void control::ShowDateSearch(string year,string month)
{
	string temp;
	int sum = 0;
	for (int i = 0;i < num;i++)
	{
		temp = arr[i]->GetDate();
		if (temp.substr(0, 4) == year && temp.substr(5,2)==month)
		{
			arr[i]->ShowExpenseInfo();
			sum += arr[i]->GetMoney();
		}
	}
	cout << "금액 총합 : " << sum << endl;
}

void control::ShowDateSearch(string year, string month, string day)
{
	string temp;
	int sum = 0;
	for (int i = 0;i < num;i++)
	{
		temp = arr[i]->GetDate();
		if (temp.substr(0, 4) == year && temp.substr(5, 2) == month && temp.substr(8,2)==day)
		{
			arr[i]->ShowExpenseInfo();
			sum += arr[i]->GetMoney();
		}
	}
	cout << "금액 총합 : " << sum << endl;
}

void control::ShowMenu() const
{
	cout << "1. 지출기록" << endl;
	cout << "2. 지출전체검색" << endl;
	cout << "3. 지출검색" << endl;
	cout << "4. 종료" << endl;
}

void control::ShowSearchMenu() const
{
	cout << "1. 날짜별 검색" << endl;
	cout << "2. 금액별 검색" << endl;
	cout << "3. 분류별 검색" << endl;
	cout << "4. 뒤로가기" << endl;
	cout << "5. 종료" << endl;
}

void control::ShowDateSearch()
{
	int number;
	string date;

	cout << "1. 연도별 검색" << endl;
	cout << "2. 월별 검색" << endl;
	cout << "3. 일별 검색" << endl;
	cout << "4.종료" << endl;
	cin >> number;

	if (number == 1)
	{
		cout << "원하시는 연도를 입력해주세요.(2019)" << endl;
		cin >> date;
		ShowDateSearch(date);
	}
	else if (number == 2)
	{
		cout << "연도와 월을 입력해주세요.(2019-02)" << endl;
		cin >> date;
		ShowDateSearch(date.substr(0, 4), date.substr(5, 2));
	}
	else if (number == 3)
	{
		cout << "연도와 월과 일을 입력해주세요(2019-02-02)" << endl;
		cin >> date;
		ShowDateSearch(date.substr(0, 4), date.substr(5, 2),date.substr(8,2));
	}
	else if (number == 4)
	{
		exit(1);
	}
	else {
		return;
	}
}

void control::ShowMoneySearch()
{
	int m;
	cout << "검색하고싶은 금액이상을 입력해주세요." << endl;
	cin >> m;

	int sum = 0;
	for (int i = 0;i < num;i++)
	{
		if (arr[i]->GetMoney() >= m)
		{
			arr[i]->ShowExpenseInfo();
			sum += arr[i]->GetMoney();
		}
	}
	cout << "금액 총합 : " << sum << endl;
}

void control::ShowCategorySearch()
{
	int c,sum=0;
	cout << "검색하고 싶은 분류를 입력해주세요." << endl;
	cout << "분류 : 1.식비 2.교통비 3.통신비 4.간식비 5.유흥비 6.생활비 7.도서비 8.교육비 9.문구비 10.의료비 11.의류비 12.기타" << endl;
	cin >> c;
	
	for (int i = 0;i < num;i++)
	{
		if (arr[i]->GetCategory() == c)
		{
			arr[i]->ShowExpenseInfo();
			sum += arr[i]->GetMoney();
		}
	}
	cout << "금액 총합 : " << sum << endl;
}