#include <iostream>
#include <string> 
#include <sstream>
using namespace std;



//Chin-Chia Leong
class Currency 
{
private:
	double amount;

public:
	//constructors
	Currency() : amount(0)
	{}
	Currency(int d, int c)
	{
		amount = d + (c * 0.01);
	}
	Currency(double amt)
	{
		amount = amt;
	}

	//access functions
	int getDollars()
	{
		return static_cast<int>(amount);
	}

	int getCents()
	{
		return static_cast<int>((amount - getDollars()) * 100);
	}

	Currency Add(Currency c);
	Currency Multiply(double amt);
	Currency operator++(int){
		Currency c = *this;
		++* this;

		return c;
	}

	Currency& operator++(){	
		static_cast<int>(amount++);

		return *this;
	}

	bool operator==(Currency c)
	{
		return (amount == c.amount);
	}

	bool operator>(Currency c)
	{
		return amount > c.amount;
	}

	bool operator<(Currency c)
	{
		return amount < c.amount;
	}

	//mutator/modifier functions
	void setDollars(int d)
	{
		amount = d + (getCents() * 0.01);
	}

	void setCents(int c)
	{
		amount = getDollars() + (c * 0.01);
	}

	void AddTo(Currency c);

	

	//input and output functions
	friend istream& operator>>(istream& s, Currency& c);
	friend ostream& operator<<(ostream& s, const Currency& c);
};

Currency Currency::Add(Currency c)
{
	Currency result;

	result.amount = amount + c.amount;

	return result;
}

Currency Currency::Multiply(double amt)
{
	Currency result;

	result.amount = amount * amt;

	return result;
}

void Currency::AddTo(Currency c)
{
	amount += c.amount;
}

istream& operator>>(istream& s, Currency& c)
{
	s >> c.amount;

	return s;
}

ostream& operator<<(ostream& s, const Currency& c)
{
	s << c.amount;

	return s;
}

class InventoryItem
{
private:
	string item_name;
	int item_number;
	Currency unit_price;
	int quantity;

public:
	// constuctors
	InventoryItem()
	{
		item_name = "";
		item_number = 0;
		unit_price = 0.0;
		quantity = 0;
	}

	InventoryItem(string n, int iNum, Currency up, int q)
	{
		item_name = n;
		item_number = iNum;
		unit_price = up;
		quantity = q;
	}

	//access functions
	string getName()
	{
		return item_name;
	}

	double getItemNum()
	{
		return item_number;
	}

	Currency getUnitPrice()
	{
		return unit_price;
	}

	int getQuantity()
	{
		return quantity;
	}

	Currency getTotalValue()
	{
		return unit_price.Multiply(quantity);
	}

	//modifier functions
	void setName(string n)
	{
		item_name = n;
	}

	void setItemNum(int n)
	{
		item_number = n;
	}

	void setUnitPrice(Currency u)
	{
		unit_price = u;
	}

	void setQuantity(int q)
	{
		quantity = q;
	}

	//I/O functions
	void Read();
	void Write();

};

void InventoryItem::Read()
{
	cout << "Item Name: ";
	cin >> item_name;
	cout << "Item Number: ";
	cin >> item_number;
	cout << "Unit Price: ";
	cin >> unit_price;
	cout << "Quantity: ";
	cin >> quantity;
}

void InventoryItem::Write()  
{
	cout << "\nItem Name: " << item_name;
	cout << "\tItem Number: " << item_number;
	cout << "\tUnit Price: ";
	cout << unit_price;
	cout << "\nQuantity: " << quantity;
	cout << "\tTotal Item Value: " << unit_price.Multiply(quantity) << endl;
}

//new functions for A6
void GetItems(InventoryItem list[], int& count)
{
	cout << "How many values are to be sorted? ";
	cin >> count;
	for (int i = 0; i < count; i++) {
		cout << "Enter the following information for Item " << i+1 << "\n";
		list[i].Read();
	}
}

void Sort(InventoryItem list[], int count, char order)
{
	cout << "Specify sort order, \"A\" for ascending, \"D\" for descending: ";
	cin >> order;

	if (order == 'A' || order == 'a')
	{
		for (int i = 0; i < count; i++)
			for (int j = 0; j < count-1; j++)
				if (list[j].getTotalValue() > list[j + 1].getTotalValue())
					swap(list[j], list[j + 1]);
	}

	if (order == 'D' || order == 'd')
	{


		for (int i = 0; i < count; i++)
			for (int j = 0; j < count-1; j++)
				if (list[j].getTotalValue() < list[j + 1].getTotalValue())
					swap(list[j], list[j + 1]);
	}
}

int main()
{	
	InventoryItem inv_item[100];
	int item_numb;
	char sort_way = '\0';

	GetItems(inv_item, item_numb);
	Sort(inv_item, item_numb, sort_way);
	for (int i = 0; i < item_numb; i++)
		inv_item[i].Write();
}