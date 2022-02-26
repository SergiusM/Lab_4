#include <iostream>
#include <chrono>
#define N 10000
#define M 1000
class Timer
{
private:
	using clock_t = std::chrono::high_resolution_clock;
	using second_t = std::chrono::duration<double, std::ratio<1> >;

	std::chrono::time_point<clock_t> m_beg;

public:
	Timer() : m_beg(clock_t::now())
	{
	}

	void reset()
	{
		m_beg = clock_t::now();
	}

	double elapsed() const
	{
		return std::chrono::duration_cast<second_t>(clock_t::now() - m_beg).count();
	}
};
struct T_List
{
	T_List* next;
	int n;
};
void Add(T_List* head, int age)
{
	T_List* p = new T_List;
	p->n = age;

	p->next = head->next;
	head->next = p;
}

void Print(T_List* head)
{
	T_List* p = head->next;
	while (p != nullptr)
	{
		std::cout << p->n << std::endl;
		p = p->next;
	}
}

void Delete(T_List* head,int k)
{
	T_List* tmp;
	T_List* p = head;
	while (p->next != nullptr)
	{
		if (p->next->n==k)
		{
			tmp = p->next;
			p->next = p->next->next;
			delete tmp;
		}
		else
			p = p->next;
	}
}

int main()
{
	srand(time(0));
	T_List* head = new T_List;
	head->next = nullptr;
	int k;
	int mas[N];
	std::cin >> k;
	for (int i = 0; i < N; i++)
		Add(head, (rand() % 10));

	Timer A;
	for (int j = 0; j < M; j++)
		Delete(head,k);
	std::cout << "Del List = " << A.elapsed() << std::endl;
	for (int i = 0; i < N; i++)
	{
		mas[i]=(rand()%10);
	}
	int n = N;
	Timer B;
	for (int j = 0; j < M; j++)
	{
		for (int i = 0; i < N; i++)
		{
			if (mas[i] == k)
			{
				for (int j = i; j <= n - 1; j++)
					mas[j] = mas[j + 1];
				n--;
				i--;
			}
		}
	}
	std::cout << "Del Mas = " << B.elapsed() << std::endl;
	delete[] mas;
	delete head;
	return 0;
}
