#include <iostream>
using namespace std;

// 링크드 리스트를 이용한 큐 +a

class Shape  // Line - Circle - Rect - Line 123
{
	Shape* next;
protected:
	virtual void draw() = 0;
public:
	Shape() { next = NULL; }
	virtual ~Shape() { }
	virtual int type() = 0;
	Shape* getNext()
	{
		return next;
	}
	void setnext(Shape* p)
	{
		this->next = p;
	}
	void prepareend();
};
class Line : public Shape
{
protected:
	void draw()
	{
		cout << "Line" << endl;
	}
public:
	int type()
	{
		return 1;
	}
};
class Circle : public Shape
{
protected:
	void draw()
	{
		cout << "Circle" << endl;
	}
public:
	int type()
	{
		return 2;
	}
};
class Rect : public Shape
{
protected:
	void draw()
	{
		cout << "Rectangle" << endl;

	}
public:
	int type()
	{
		return 3;
	}
};

/// ////////////////////////////////////////////////////////////////////////// 전역변수


Shape* pStart; // 가장 오래전에 생성된 노드의 주소를 저장. 삭제(pop), 모두보기(print), 종료(prepareend)에 사용됨
Shape* pLast; // 마지막에 생성된 노드의 주소를 저장. 삽입(push)에 사용됨
int  nowsize = 0; // 노드가 모두 몇 개 생성되어 있는지


/// //////////////////////////////////////////////////////////////////////////
void Shape::prepareend() // 종료(전 준비)
{
	--nowsize;
	if (nowsize > 0) // 현재 사이즈가 1이상
	{
		next->prepareend();
		delete this;
	}
	else // 0
	{
		delete this;
		pStart = pLast = NULL;
	}
}


class UI {
public:
	static int menu() 
	{
		int num;
		cout << "삽입:1, 삭제:2, 모두보기:3, 종료:4 >> ";
		cin >> num;

		switch (num)
		{
		case 1: // 삽입
			shape_choose();
			break;
		case 2: // 삭제
			del_menu();
			break;
		case 3: // 모두보기
			print();
			break;
		case 4: // 종료
			cout << "프로그램을 종료합니다." << endl;
			pStart->prepareend();
			exit(0);

		default: // 입력오류
			cout << "입력오류" << endl;
			break;
		}

		return num;
	}
	static void shape_choose()  // 삽입
	{
		int num;
		cout << "선:1, 원:2, 사각형:3 >> ";
		cin >> num;

		if (!nowsize) // 현재 배열의 사이즈가 0일때
		{
			switch (num)
			{
			case 1: // 선
				pStart = pLast = new Line();
				cout << "선 삽입" << std::endl;
				break;
			case 2: // 원
				pStart = pLast = new Circle();
				cout << "원 삽입" << endl;
				break;
			case 3: // 사각형
				pStart = pLast = new Rect();
				cout << "사각형 삽입" << endl;
				break;
			}
			nowsize = 1;
		}
		else // 현재 배열의 사이즈가 0 이 아닐때
		{
			Shape* newshape;
			switch (num)
			{
			case 1: // 선
				newshape = new Line();
				pLast->setnext(newshape);
				pLast = newshape;
				cout << "선 삽입" << std::endl;
				break;
			case 2: // 원
				newshape = new Circle();
				pLast->setnext(newshape);
				pLast = newshape;
				cout << "원 삽입" << std::endl;
				break;
			case 3: // 사각형
				newshape = new Rect();
				pLast->setnext(newshape);
				pLast = newshape;
				cout << "사각형 삽입" << std::endl;
				break;
			}
			nowsize++;
		}

		return;
	}
	static void del_menu()  // 삭제
	{
		Shape* fronttemp;
		Shape* reartemp;
		Shape* finder;
		int num;
		int i;

		cout << "삭제하고자 하는 도형의 인덱스 >> ";
		cin >> num;

		if (num >= nowsize)
		{
			cout << "인덱스는 배열의 크기보다 클 수 없습니다" << endl;
			exit(4);
		}
		else if (num == 0)
		{
			cout << "인덱스 0 삭제" << endl;

			if (nowsize == 1) // 배열의 크기가 1일때
			{
				delete pStart;
				
				pStart = pLast = NULL;

				--nowsize;

				return;
			}
			else // 배열의 크기가 2 이상일 때
			{
				reartemp = pStart->getNext();
			
				delete pStart;
			
				pStart = reartemp;

				--nowsize;

				return;
			}
		}

		fronttemp = NULL; // 삭제할 노드의 앞을 저장할 변수
		reartemp = NULL; // 삭제할 노드의 뒤를 저장할 변수
		finder = pStart;
		for (i = 0; i < num; ++i)
		{
			if (i == num - 1)
			{
				fronttemp = finder;
			}
			finder = finder->getNext();
		}
		if (pLast == finder) // 삭제할 노드가 배열의 마지막일때
		{
			delete finder;

			fronttemp->setnext(NULL);

			pLast = fronttemp;
		}
		else
		{
			reartemp = finder->getNext();

			delete finder;

			fronttemp->setnext(reartemp);
		}
		
		--nowsize;

		return;
	}
	static void print() // 모두보기
	{
		Shape* finder;
		int i;


		finder = pStart;
		for (i = 0; i < nowsize; ++i)
		{
			cout << i << " : ";
			switch (finder->type())
			{
			case 1: // 선
				cout << "Line" << endl;
				break;
			case 2: // 원
				cout << "Circle" << endl;
				break;
			case 3: // 사각형
				cout << "Rect" << endl;
				break;
			default:
				cout << "타입오류" << endl;
				exit(3);
			}

			finder = finder->getNext();
		}
	}
};

class GraphicEditor
{
	UI handle;
	 
public:
	GraphicEditor();
};
GraphicEditor::GraphicEditor()
{
	cout << "그래픽 에디터입니다." << std::endl;

	while (1) // 메인 프로시져
	{
		handle.menu();
	}
}


int main() 
{
	GraphicEditor* start;
	

	start = new GraphicEditor;
	
	delete start;

	return 0;
}
