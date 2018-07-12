#include<iostream>
#include<fstream>
#include<string>
using namespace std;

class deque{
public:
	void push_front(char num){
		size++;
		for (int j = size-1; j >0; j--)
		{
			array[j] = array[j - 1];
		}
		array[0] = num;
	};
	void push_back(char num){
		array[size] = num;
		size++;
	};
	void pop_front(char &num){
		num = array[0];
		size--;
		for (int j = 0; j < size; j++)
		{
			array[j] = array[j + 1];
		}
	};
	void pop_back(char &num){
		size--;
		num = array[size];
	};
	void print_deque(ofstream &fout){
		for (int j = 0; j < size; j++)
		{
			fout << array[j];
		}
	}
	int deque_size(){
		return size;
	};
private:
	char array[100];
	int size = 0;
};

struct node{
	int name;
	deque data;
	node* clockwise;
	node* anti_clockwise;
};


int main(int argc, char* argv[]){
	ifstream fin;
	ofstream fout;
	fin.open("case.txt");
	fout.open("ans.txt");
	node* n,* first,* end,* now;
	int who_turn,name,num=0;
	fin >> who_turn;
	while (fin >> name){
		if (name < 0)
			break;
		n = new node;
		n->name = name;
		if (name == who_turn)
			now = n;
		if (num == 0){
			first = n;
			end = n;
			n->clockwise = NULL;
			n->anti_clockwise = NULL;
		}
		else{
			end->clockwise = n;
			n->anti_clockwise = end;
			n->clockwise = first;
			first->anti_clockwise = n;
			end = n;
		}
		num++;
	}
	
	fin.get();
	string direction = "clockwise";
	char get,pre_get;
	node* pre_now;
	while (1)
	{
		if (num == 1)
			break;
		get = fin.get();
		if (int(get) == 10 || fin.eof()){
			pre_now->clockwise->anti_clockwise = pre_now->anti_clockwise;//刪除node
			pre_now->anti_clockwise->clockwise = pre_now->clockwise;
			num--;
			if (pre_get == 'a' || pre_get == 'e' || pre_get == 'i' || pre_get == 'o' || pre_get == 'u');//母音不轉換方向
			else{//子音轉換方向
				if (direction == "clockwise"){
					direction = "anti_clockwise";
					now = now->anti_clockwise;
				}
				else if (direction == "anti_clockwise"){
					direction = "clockwise";
					now = now->clockwise;
				}
			}
			fout << pre_now->name<<' ';
			pre_now->data.print_deque(fout);
			fout << endl;
		}
		else{
			pre_now = now;
			if (direction == "clockwise"){
				now->data.push_back(get);
				now = now->clockwise;
			}
			else if (direction == "anti_clockwise"){
				now->data.push_front(get);
				now = now->anti_clockwise;
			}
		}
		pre_get = get;
	}
	fout << now->name << ' ';
	now->data.print_deque(fout);
	fout << endl;
	fin.close();
	fout.close();
}