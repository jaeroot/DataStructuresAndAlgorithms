#include <iostream>
#include <array>

using namespace std;

void print1(array<int, 5> arr)
{
	for (auto ele : arr)
		cout << ele << ", ";
	cout << endl;
}

template <size_t N>
void print2(const array<int, N>& arr)
{
	for (auto ele : arr)
		cout << ele << ", ";
	cout << endl;
}

int main()
{
	// 1. std::array
	// 
	// std::array는 자동으로 메모리를 할당하고 해제함
	// std::array는 원소의 타입과 배열 크기를 매개변수로 사용하는 클래스 템플릿임

	array<int, 10> arr1;	// 크기가 10인 int 타입 배열 선언
	arr1[0] = 1;	// 첫 번째 원소를 1로 설정
	cout << "arr1 배열의 첫 번째 원소: " << arr1[0] << endl;	// arr1 배열의 첫 번째 원소: 1

	array<int, 4> arr2 = { 1,2,3,4 };
	cout << "arr2의 모든 원소: ";
	for (int i = 0; i < arr2.size(); i++)
		cout << arr2[i] << " ";
	cout << endl;	// arr2의 모든 원소: 1 2 3 4


	// 2. std::array의 접근 방법과 예외 처리
	// 
	// std::array는 배열 원소에 접근할 수 있는 [] 연산자 제공
	// [] 연산자에 접근하고자 하는 배열 원소 index를 지정할 경우, 빠른 동작을 위해 전달된 인덱스 값이 배열의 크기보다 작은지를 검사하지는 않음
	// std::array는 at(index) 형식의 함수를 제공하며, 이 함수는 index 값이 유효하지 않으면 std::out_of_range 예외를 발생시킴
	// at() 함수가 []연산자보다 조금 느린 편이지만 at() 함수를 이용해 예외 처리 가능

	std::array<int, 4> arr3 = { 1,2,3,4 };
	try
	{
		cout << arr3.at(3) << endl;	// 에러 아님
		cout << arr3.at(4) << endl; // std::out_of_range 예외 발생
	}
	catch (const out_of_range& ex)
	{
		cerr << ex.what() << endl;	// invalid array<T, N> subscript
	}



	// 3. std::array 인자 전달
	// 
	// std::array 객체를 다른 함수에 전달할 때 기본 데이터 타입을 전달하는 것처럼 값 또는 참조, const를 사용할 수 있음
	// C 스타일 배열처럼 포인터 연산을 사용하거나 참조/역참조 연산을 하지 않아도 됨

	array<int, 5> arr4 = { 1,2,3,4,5 };
	print1(arr4);	// 1, 2, 3, 4, 5,



	// 4. 다양한 크기의 std::array 인자 전달
	//
	// 다양한 크기의 std::array 객체에 대해 함수가 동적으로 작동하게 하려면 함수를 템플릿으로 선언하고, 배열 크기를 템플릿 매개변수로 전달
	// std:array를 함수에 전달할 경우, 기본적으로 새로운 배열에 모든 원소가 복사됨 (깊은 복사 수행)
	// 복사를 피하고 싶다면 참조 혹은 const 참조를 사용

	array<int, 7> arr5 = { 1,2,3,4,5,6,7 };
	print2(arr4);



	// 5. 범위 기반 for문과 iterator
	// 
	// std::array는 반복자(iterator)와 범위 기반 for문을 사용해 원소에 차례대로 접근할 수 있음
	// 반복자를 사용하기에 범위 기반 for문을 사용해 std::array의 원소에 접근할 수 있음
	// std::array는 begin()과 end()라는 함수를 제공, 가장 첫 번째 원소와 가장 마지막 원소의 위치(마지막 원소 다음 위치)를 반환함
	// 특정 원소 위치에서 다음 위치로 이동하려면 증감(++), 덧셈(+)과 같은 연산자를 수행할 수 있음
	// 범위 기반 for문은 begin()부터 증가 연산자(++)를 통해 원소를 이동하다 end() 위치에 도달하면 종료함
	// const_iterator, reverse_iterator같은 형태도 사용 가능

	array<int, 5> arr6 = { 1,2,3,4,5 };
	for (auto element : arr6)
	{
		cout << element << " ";
	}
	cout << endl;

	// 위의 for 문과 아래의 for문은 동일한 내용임
	for (auto it = arr6.begin(); it != arr6.end(); it++)
	{
		auto element = (*it);
		cout << element << " ";
	}
	cout << endl;



	// 6. std::array의 원소 접근 함수들
	//
	// front() : 배열의 첫 번째 원소에 대한 참조 반환
	// back() : 배열의 마지막 원소에 대한 참조 반환
	// data() : 배열 객체 내부에서 실제 데이터 메모리 버퍼를 가리키는 포인터 반환

	array<int, 5> arr7 = { 1,2,3,4,5 };
	cout << arr7.front() << endl;			// 1
	cout << arr7.back() << endl;			// 5
	cout << *(arr7.data() + 1) << endl;		// 2
	


	// 7. 관계 연산자, 복사 할당 연산자
	//
	// std::array는 깊은 비교를 위한 관계 연산자, 깊은 복사를 위환 복사 할당 연산자를 지원함
	// std::array에 저장되는 데이터 타입에서 크기 비교 (<, >, <=, >=, ==, !=)를 지원할 경우, 이들 관계 연산자를 이용해서 두 std::array 배열을 비교할 수 있음
	// C 스타일 배열에서도 관계 연산자를 사용할 수 있으나, 값이 아닌 포인터 주소 값을 비교함
	// 즉, C 스타일 배열은 깊은 비교 대신 얕은 비교를 수행함
	// 할당에 대해서도 C 스타일 배열은 메모리를 새로 생성하여 값을 복사하지 않으며, 단순히 같은 배열 데이터를 가리키는 새로운 포인터를 생성함
	// 
	// 단, std::array에서 관계 연산자를 사용할 경우, 두 배열의 크기가 같아야 함
	// std::array로 만든 배열 객체는 배열의 크기도 데이터 타입의 일부로 동작하기 때문


	return 0;
}