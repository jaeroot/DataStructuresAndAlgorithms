#include <iostream>
#include <sstream>
#include <algorithm>

using namespace std;

template <typename T>
class dynamic_array
{
	T* data;
	size_t n;

public:
	dynamic_array(int n)
	{
		this->n = n;
		data = new T[n];
	}

	dynamic_array(const dynamic_array<T>& other)
	{
		n = other.n;
		data = new T[n];

		for (int i = 0; i < n; i++)
			data[i] = other[i];
	}

	T& operator[](int index)
	{
		return data[index];
	}

	const T& operator[](int index) const
	{
		return data[index];
	}

	T& at(int index)
	{
		if (index < n)
			return data[index];
		throw "Index out of range";
	}

	size_t size() const
	{
		return n;
	}

	~dynamic_array()
	{
		delete[] data;
	}

	T* begin() { return data; }
	const T* begin() const { return data; }
	T* end() { return data + n; }
	const T* end() const { return data + n; }

	friend dynamic_array<T> operator+(const dynamic_array<T>& arr1, const dynamic_array<T>& arr2)
	{
		dynamic_array<T> result(arr1.size() + arr2.size());
		copy(arr1.begin(), arr1.end(), result.begin());
		copy(arr2.begin(), arr2.end(), result.begin() + arr1.size());

		return result;
	}

	string to_string(const string& sep = ", ")
	{
		if (n == 0)
			return "";

		ostringstream os;
		os << data[0];

		for (int i = 1; i < n; i++)
			os << sep << data[i];

		return os.str();
	}
};

struct student
{
	string name;
	int standard;
};

ostream& operator<<(ostream& os, const student& s)
{
	return (os << "[" << s.name << ", " << s.standard << "]");
}

int main()
{
	int nStudents;
	cout << "1반 학생 수를 입력하세요: ";
	cin >> nStudents;

	dynamic_array<student> class1(nStudents);
	for (int i = 0; i < nStudents; i++)
	{
		string name;
		int standard;
		cout << i + 1 << "번째 학생 이름과 나이를 입력하세요: ";
		cin >> name >> standard;
		class1[i] = student{ name, standard };
	}

	// 배열 크기보다 큰 인덱스의 학생에 접근
	try
	{
		// class1[nStudents] = student{ "John", 8 };
		class1.at(nStudents) = student{ "John", 8 };
	}
	catch (...)
	{
		cout << "예외 발생!" << endl;
	}

	// 깊은 복사
	auto class2 = class1;
	cout << "1반을 복사하여 2반 생성: " << class2.to_string() << endl;

	// 두 학급을 합쳐서 새로운 큰 학급을 생성
	auto class3 = class1 + class2;
	cout << "1반과 2반을 합쳐 3반 생성: " << class3.to_string() << endl;

	return 0;
}